#!/usr/bin/env python3

"""Send one synthetic odom-frame path to the real Nav2 controller_server.

This is a software-only V25-09B gate. It deliberately bypasses the global
planner and Map/Route asset resolver so the test isolates the controller path:
RuntimePath-equivalent odom geometry -> FollowPath -> collision monitor ->
AGT safety -> simulator.
"""

from __future__ import annotations

import json
import math
import sys
import time

from action_msgs.msg import GoalStatus
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import FollowPath
from nav_msgs.msg import Odometry, Path
import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node


def _yaw_from_quaternion(q) -> float:
    return math.atan2(
        2.0 * (q.w * q.z + q.x * q.y),
        1.0 - 2.0 * (q.y * q.y + q.z * q.z),
    )


class RouteControllerSmoke(Node):
    def __init__(self) -> None:
        super().__init__("agt_route_controller_smoke")
        self.distance_m = float(self.declare_parameter("distance_m", 1.0).value)
        self.sample_spacing_m = float(
            self.declare_parameter("sample_spacing_m", 0.05).value
        )
        self.server_timeout_s = float(
            self.declare_parameter("server_timeout_s", 10.0).value
        )
        self.odom_timeout_s = float(
            self.declare_parameter("odom_timeout_s", 5.0).value
        )
        self.result_timeout_s = float(
            self.declare_parameter("result_timeout_s", 30.0).value
        )
        self.minimum_motion_m = float(
            self.declare_parameter("minimum_motion_m", 0.50).value
        )
        self.controller_id = str(
            self.declare_parameter("controller_id", "FollowPath").value
        )
        self.goal_checker_id = str(
            self.declare_parameter("goal_checker_id", "general_goal_checker").value
        )
        if (
            self.distance_m <= 0.0
            or self.sample_spacing_m <= 0.0
            or self.server_timeout_s <= 0.0
            or self.odom_timeout_s <= 0.0
            or self.result_timeout_s <= 0.0
            or self.minimum_motion_m < 0.0
        ):
            raise ValueError("route controller smoke parameters must be positive")

        self._odom = None
        self._client = ActionClient(self, FollowPath, "follow_path")
        self.create_subscription(
            Odometry, "/agt/mapping/odometry", self._odom_callback, 20
        )

    def _odom_callback(self, message: Odometry) -> None:
        self._odom = message

    def _wait_until(self, predicate, timeout_s: float) -> bool:
        deadline = time.monotonic() + timeout_s
        while rclpy.ok() and time.monotonic() < deadline:
            rclpy.spin_once(self, timeout_sec=0.05)
            if predicate():
                return True
        return bool(predicate())

    def _path_from_current_pose(self) -> tuple[Path, tuple[float, float]]:
        if self._odom is None:
            raise RuntimeError("odometry is unavailable")
        pose = self._odom.pose.pose
        x0 = float(pose.position.x)
        y0 = float(pose.position.y)
        yaw = _yaw_from_quaternion(pose.orientation)
        samples = max(2, int(math.ceil(self.distance_m / self.sample_spacing_m)) + 1)

        path = Path()
        path.header.frame_id = "odom"
        path.header.stamp = self.get_clock().now().to_msg()
        for index in range(samples):
            distance = self.distance_m * index / (samples - 1)
            item = PoseStamped()
            item.header = path.header
            item.pose.position.x = x0 + distance * math.cos(yaw)
            item.pose.position.y = y0 + distance * math.sin(yaw)
            item.pose.orientation.z = math.sin(yaw * 0.5)
            item.pose.orientation.w = math.cos(yaw * 0.5)
            path.poses.append(item)
        return path, (x0, y0)

    def run(self) -> dict:
        if not self._wait_until(lambda: self._odom is not None, self.odom_timeout_s):
            raise RuntimeError("timed out waiting for /agt/mapping/odometry")
        if not self._client.wait_for_server(timeout_sec=self.server_timeout_s):
            raise RuntimeError("timed out waiting for Nav2 FollowPath action")

        path, start_xy = self._path_from_current_pose()
        goal = FollowPath.Goal()
        goal.path = path
        goal.controller_id = self.controller_id
        goal.goal_checker_id = self.goal_checker_id

        send_future = self._client.send_goal_async(goal)
        if not self._wait_until(send_future.done, self.server_timeout_s):
            raise RuntimeError("timed out waiting for FollowPath goal response")
        handle = send_future.result()
        if handle is None or not handle.accepted:
            raise RuntimeError("Nav2 controller_server rejected FollowPath goal")

        result_future = handle.get_result_async()
        if not self._wait_until(result_future.done, self.result_timeout_s):
            handle.cancel_goal_async()
            raise RuntimeError("timed out waiting for FollowPath result")
        wrapped = result_future.result()
        if wrapped is None:
            raise RuntimeError("FollowPath returned no result")

        # Spin once more so the latest simulator odometry is reflected in the
        # measured displacement after the controller reports success.
        rclpy.spin_once(self, timeout_sec=0.05)
        end = self._odom.pose.pose.position if self._odom is not None else None
        end_xy = (
            (float(end.x), float(end.y)) if end is not None else start_xy
        )
        displacement = math.hypot(end_xy[0] - start_xy[0], end_xy[1] - start_xy[1])
        success = (
            int(wrapped.status) == GoalStatus.STATUS_SUCCEEDED
            and displacement >= self.minimum_motion_m
        )
        return {
            "success": success,
            "follow_path_status": int(wrapped.status),
            "controller_id": self.controller_id,
            "frame_id": path.header.frame_id,
            "path_samples": len(path.poses),
            "requested_distance_m": self.distance_m,
            "measured_displacement_m": displacement,
            "minimum_motion_m": self.minimum_motion_m,
            "global_planner_requests": 0,
        }


def main(args=None) -> None:
    rclpy.init(args=args)
    node = RouteControllerSmoke()
    exit_code = 1
    try:
        report = node.run()
        print(json.dumps(report, indent=2, sort_keys=True))
        exit_code = 0 if report["success"] else 2
    except Exception as exc:
        print(
            json.dumps(
                {
                    "success": False,
                    "error": str(exc),
                    "global_planner_requests": 0,
                },
                indent=2,
                sort_keys=True,
            ),
            file=sys.stderr,
        )
        exit_code = 1
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
    raise SystemExit(exit_code)


if __name__ == "__main__":
    main()
