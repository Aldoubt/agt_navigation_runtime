#!/usr/bin/env python3

import math

import rclpy
from action_msgs.msg import GoalStatus
from geometry_msgs.msg import PoseArray, PoseStamped
from nav2_msgs.action import ComputePathToPose
from nav_msgs.msg import Path
from rclpy.action import ActionClient
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy
from std_msgs.msg import String


def valid_pose(pose):
    values = (
        pose.position.x,
        pose.position.y,
        pose.position.z,
        pose.orientation.x,
        pose.orientation.y,
        pose.orientation.z,
        pose.orientation.w,
    )
    return all(math.isfinite(value) for value in values)


def append_segment(joined, segment):
    poses = list(segment.poses)
    if joined and poses:
        poses = poses[1:]
    joined.extend(poses)


class WaypointPreviewPlanner(Node):
    """Planner-only multi-point preview; it never sends motion commands."""

    def __init__(self):
        super().__init__("agt_waypoint_preview_planner")
        self.declare_parameter("request_topic", "/agt/navigation/waypoint_preview_request")
        self.declare_parameter("path_topic", "/plan")
        self.declare_parameter("planner_action", "/compute_path_to_pose")
        self.declare_parameter("planner_id", "GridBased")
        qos = QoSProfile(depth=1)
        qos.reliability = ReliabilityPolicy.RELIABLE
        qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self._path_pub = self.create_publisher(
            Path, str(self.get_parameter("path_topic").value), qos
        )
        self._status_pub = self.create_publisher(
            String, "/agt/navigation/waypoint_preview_status", 10
        )
        self._client = ActionClient(
            self,
            ComputePathToPose,
            str(self.get_parameter("planner_action").value),
        )
        self.create_subscription(
            PoseArray,
            str(self.get_parameter("request_topic").value),
            self._on_request,
            10,
        )
        self._busy = False
        self._poses = []
        self._segment_index = 0
        self._joined = []

    def _status(self, value):
        message = String()
        message.data = value
        self._status_pub.publish(message)

    def _publish_empty(self):
        message = Path()
        message.header.frame_id = "map"
        message.header.stamp = self.get_clock().now().to_msg()
        self._path_pub.publish(message)

    def _fail(self, reason):
        self.get_logger().warning(reason)
        self._busy = False
        self._publish_empty()
        self._status(f"failed:{reason}")

    def _on_request(self, request):
        if self._busy:
            self._status("rejected:preview already running")
            return
        if request.header.frame_id not in {"", "map"}:
            self._fail("preview request must use map frame")
            return
        if len(request.poses) < 2:
            self._fail("preview requires at least two task points")
            return
        if not all(valid_pose(pose) for pose in request.poses):
            self._fail("preview contains a non-finite pose")
            return
        if not self._client.wait_for_server(timeout_sec=0.2):
            self._fail("ComputePathToPose is unavailable")
            return
        self._publish_empty()
        self._busy = True
        self._poses = list(request.poses)
        self._segment_index = 1
        self._joined = []
        self._status("planning")
        self._send_segment()

    def _stamped(self, pose):
        stamped = PoseStamped()
        stamped.header.frame_id = "map"
        stamped.header.stamp = self.get_clock().now().to_msg()
        stamped.pose = pose
        return stamped

    def _send_segment(self):
        goal = ComputePathToPose.Goal()
        goal.start = self._stamped(self._poses[self._segment_index - 1])
        goal.goal = self._stamped(self._poses[self._segment_index])
        goal.use_start = True
        goal.planner_id = str(self.get_parameter("planner_id").value)
        future = self._client.send_goal_async(goal)
        future.add_done_callback(self._goal_response)

    def _goal_response(self, future):
        try:
            handle = future.result()
        except Exception as exc:  # pragma: no cover - ROS transport boundary
            self._fail(f"planner goal error: {exc}")
            return
        if not handle.accepted:
            self._fail(f"segment {self._segment_index} rejected")
            return
        result = handle.get_result_async()
        result.add_done_callback(self._segment_result)

    def _segment_result(self, future):
        try:
            wrapped = future.result()
        except Exception as exc:  # pragma: no cover - ROS transport boundary
            self._fail(f"planner result error: {exc}")
            return
        if wrapped.status != GoalStatus.STATUS_SUCCEEDED:
            self._fail(
                f"segment {self._segment_index} failed with status {wrapped.status}"
            )
            return
        append_segment(self._joined, wrapped.result.path)
        self._segment_index += 1
        if self._segment_index < len(self._poses):
            self._send_segment()
            return
        output = Path()
        output.header.frame_id = "map"
        output.header.stamp = self.get_clock().now().to_msg()
        output.poses = self._joined
        self._path_pub.publish(output)
        self._busy = False
        self._status(f"succeeded:{len(output.poses)} poses")


def main(args=None):
    rclpy.init(args=args)
    node = WaypointPreviewPlanner()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
