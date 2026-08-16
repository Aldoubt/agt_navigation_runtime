#!/usr/bin/env python3

"""Run the full software-only V25-09B ROUTE chain through ExecuteWaypointTask."""

from __future__ import annotations

import json
import math
from pathlib import Path
import sys
import time

from action_msgs.msg import GoalStatus
from agt_interfaces.action import ExecuteWaypointTask
from agt_interfaces.msg import MapVersionSummary
from agt_navigation.task_group import TaskGroup
from diagnostic_msgs.msg import DiagnosticArray
from nav_msgs.msg import Odometry
import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node
from std_msgs.msg import String


class RouteSystemSmoke(Node):
    def __init__(self) -> None:
        super().__init__("agt_route_system_smoke")
        self.maps_root = Path(
            str(self.declare_parameter("maps_root", "/tmp/agt_route_system_smoke/maps").value)
        ).expanduser().resolve()
        self.map_id = str(self.declare_parameter("map_id", "route_smoke_site").value)
        self.map_version_id = str(
            self.declare_parameter("map_version_id", "route_smoke_v1").value
        )
        self.task_group_id = str(
            self.declare_parameter("task_group_id", "route_smoke_task").value
        )
        self.server_timeout_s = float(
            self.declare_parameter("server_timeout_s", 10.0).value
        )
        self.readiness_timeout_s = float(
            self.declare_parameter("readiness_timeout_s", 10.0).value
        )
        self.result_timeout_s = float(
            self.declare_parameter("result_timeout_s", 45.0).value
        )
        self.minimum_motion_m = float(
            self.declare_parameter("minimum_motion_m", 1.0).value
        )
        if min(self.server_timeout_s, self.readiness_timeout_s, self.result_timeout_s) <= 0.0:
            raise ValueError("route system smoke timeouts must be positive")

        self._odom = None
        self._active_map = None
        self._safety_ready = False
        self._last_task_status = {}
        self._client = ActionClient(
            self,
            ExecuteWaypointTask,
            "/agt/navigation/execute_waypoint_task",
        )
        self.create_subscription(Odometry, "/agt/mapping/odometry", self._odom_cb, 20)
        self.create_subscription(
            MapVersionSummary, "/agt/maps/active", self._active_map_cb, 10
        )
        self.create_subscription(
            DiagnosticArray, "/agt/safety/status", self._safety_cb, 10
        )
        self.create_subscription(String, "/agt/navigation/task_status", self._status_cb, 10)

    def _odom_cb(self, message: Odometry) -> None:
        self._odom = message

    def _active_map_cb(self, message: MapVersionSummary) -> None:
        self._active_map = message

    def _safety_cb(self, message: DiagnosticArray) -> None:
        for status in message.status:
            if status.name != "agt_safety/tracked_controller":
                continue
            values = {item.key: item.value.lower() for item in status.values}
            self._safety_ready = (
                values.get("motion_enabled") == "true"
                and values.get("estop_latched") != "true"
            )
            return

    def _status_cb(self, message: String) -> None:
        try:
            value = json.loads(message.data)
        except json.JSONDecodeError:
            return
        if isinstance(value, dict):
            self._last_task_status = value

    def _wait_until(self, predicate, timeout_s: float) -> bool:
        deadline = time.monotonic() + timeout_s
        while rclpy.ok() and time.monotonic() < deadline:
            rclpy.spin_once(self, timeout_sec=0.05)
            if predicate():
                return True
        return bool(predicate())

    def _task_path(self) -> Path:
        return (
            self.maps_root
            / self.map_id
            / "versions"
            / self.map_version_id
            / "tasks"
            / f"{self.task_group_id}.json"
        )

    def _ready(self) -> bool:
        active = self._active_map
        return bool(
            self._odom is not None
            and self._safety_ready
            and active is not None
            and active.active
            and active.valid
            and active.state == MapVersionSummary.STATE_READY
            and active.map_id == self.map_id
            and active.map_version_id == self.map_version_id
            and self._task_path().is_file()
        )

    def run(self) -> dict:
        if not self._client.wait_for_server(timeout_sec=self.server_timeout_s):
            raise RuntimeError("timed out waiting for ExecuteWaypointTask")
        if not self._wait_until(self._ready, self.readiness_timeout_s):
            raise RuntimeError(
                "timed out waiting for synthetic READY map, safety, odometry, and task fixture"
            )

        task = TaskGroup.from_json(self._task_path())
        start = self._odom.pose.pose.position
        start_xy = (float(start.x), float(start.y))

        request = ExecuteWaypointTask.Goal()
        request.map_id = self.map_id
        request.map_version_id = self.map_version_id
        request.task_group_id = self.task_group_id
        request.task_revision = int(task.revision)
        request.expected_content_sha256 = task.content_sha256
        request.loop_count = 1
        request.client_request_id = f"route_system_smoke_{int(time.time() * 1000)}"

        send_future = self._client.send_goal_async(request)
        if not self._wait_until(send_future.done, self.server_timeout_s):
            raise RuntimeError("timed out waiting for ExecuteWaypointTask goal response")
        handle = send_future.result()
        if handle is None or not handle.accepted:
            raise RuntimeError("ExecuteWaypointTask rejected synthetic ROUTE request")

        result_future = handle.get_result_async()
        if not self._wait_until(result_future.done, self.result_timeout_s):
            handle.cancel_goal_async()
            raise RuntimeError("timed out waiting for ExecuteWaypointTask result")
        wrapped = result_future.result()
        if wrapped is None:
            raise RuntimeError("ExecuteWaypointTask returned no result")

        rclpy.spin_once(self, timeout_sec=0.10)
        end = self._odom.pose.pose.position if self._odom is not None else None
        end_xy = (float(end.x), float(end.y)) if end is not None else start_xy
        displacement = math.hypot(end_xy[0] - start_xy[0], end_xy[1] - start_xy[1])
        planner_requests = self._last_task_status.get("global_planner_requests")
        success = (
            int(wrapped.status) == GoalStatus.STATUS_SUCCEEDED
            and bool(wrapped.result.success)
            and displacement >= self.minimum_motion_m
            and planner_requests == 0
        )
        return {
            "success": success,
            "execute_waypoint_task_status": int(wrapped.status),
            "result_success": bool(wrapped.result.success),
            "blocker_code": str(wrapped.result.blocker_code),
            "technical_message": str(wrapped.result.technical_message),
            "map_id": self.map_id,
            "map_version_id": self.map_version_id,
            "task_group_id": self.task_group_id,
            "task_content_sha256": task.content_sha256,
            "measured_displacement_m": displacement,
            "minimum_motion_m": self.minimum_motion_m,
            "global_planner_requests": planner_requests,
            "terminal_task_status": self._last_task_status,
        }


def main(args=None) -> None:
    rclpy.init(args=args)
    node = RouteSystemSmoke()
    exit_code = 1
    try:
        report = node.run()
        print(json.dumps(report, indent=2, sort_keys=True))
        exit_code = 0 if report["success"] else 2
    except Exception as exc:
        print(
            json.dumps({"success": False, "error": str(exc)}, indent=2, sort_keys=True),
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
