#!/usr/bin/env python3

import json
import math

import rclpy
from action_msgs.msg import GoalStatus
from geometry_msgs.msg import Point32, PolygonStamped, PoseArray, PoseStamped
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


def validated_segment_timeout(value):
    timeout_s = float(value)
    if not math.isfinite(timeout_s) or timeout_s <= 0.0:
        raise ValueError("segment_timeout_s must be a positive finite value")
    return timeout_s


def planning_progress(segment_index, pose_count):
    return f"planning:{segment_index}/{pose_count - 1}"


def next_segment_start(requested_poses, joined, segment_index):
    """Keep successive plans connected when Nav2 applies goal tolerance."""
    if joined:
        return joined[-1].pose
    return requested_poses[segment_index - 1]


def goal_status_name(status):
    names = {
        GoalStatus.STATUS_UNKNOWN: "unknown",
        GoalStatus.STATUS_ACCEPTED: "accepted",
        GoalStatus.STATUS_EXECUTING: "executing",
        GoalStatus.STATUS_CANCELING: "canceling",
        GoalStatus.STATUS_SUCCEEDED: "succeeded",
        GoalStatus.STATUS_CANCELED: "canceled",
        GoalStatus.STATUS_ABORTED: "aborted",
    }
    return names.get(status, f"status {status}")


class WaypointPreviewPlanner(Node):
    """Planner-only multi-point preview; it never sends motion commands."""

    def __init__(self):
        super().__init__("agt_waypoint_preview_planner")
        self.declare_parameter("request_topic", "/agt/navigation/waypoint_preview_request")
        self.declare_parameter("path_topic", "/plan")
        self.declare_parameter("planner_action", "/compute_path_to_pose")
        self.declare_parameter("planner_id", "GridBased")
        self.declare_parameter("footprint_json", "[]")
        self.declare_parameter("segment_timeout_s", 30.0)
        qos = QoSProfile(depth=1)
        qos.reliability = ReliabilityPolicy.RELIABLE
        qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self._path_pub = self.create_publisher(
            Path, str(self.get_parameter("path_topic").value), qos
        )
        self._status_pub = self.create_publisher(
            String, "/agt/navigation/waypoint_preview_status", 10
        )
        self._footprint_pub = self.create_publisher(
            PolygonStamped,
            "/agt/navigation/preview_footprint",
            qos,
        )
        self._footprint = json.loads(
            str(self.get_parameter("footprint_json").value)
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
        self._segment_timeout_s = validated_segment_timeout(
            self.get_parameter("segment_timeout_s").value
        )
        self._segment_generation = 0
        self._segment_timer = None

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
        self._segment_generation += 1
        self._cancel_segment_timer()
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
        self._publish_footprint(request.poses[0])
        self._status("planning")
        self._send_segment()

    def _publish_footprint(self, pose):
        output = PolygonStamped()
        output.header.frame_id = "map"
        output.header.stamp = self.get_clock().now().to_msg()
        q = pose.orientation
        yaw = math.atan2(
            2.0 * (q.w * q.z + q.x * q.y),
            1.0 - 2.0 * (q.y * q.y + q.z * q.z),
        )
        cosine, sine = math.cos(yaw), math.sin(yaw)
        for x, y in self._footprint:
            point = Point32()
            point.x = float(pose.position.x + cosine * x - sine * y)
            point.y = float(pose.position.y + sine * x + cosine * y)
            point.z = 0.05
            output.polygon.points.append(point)
        self._footprint_pub.publish(output)

    def _stamped(self, pose):
        stamped = PoseStamped()
        stamped.header.frame_id = "map"
        stamped.header.stamp = self.get_clock().now().to_msg()
        stamped.pose = pose
        return stamped

    def _send_segment(self):
        self._segment_generation += 1
        generation = self._segment_generation
        segment_index = self._segment_index
        self._status(planning_progress(segment_index, len(self._poses)))
        goal = ComputePathToPose.Goal()
        goal.start = self._stamped(
            next_segment_start(self._poses, self._joined, self._segment_index)
        )
        goal.goal = self._stamped(self._poses[self._segment_index])
        goal.use_start = True
        goal.planner_id = str(self.get_parameter("planner_id").value)
        self._arm_segment_timer(generation, segment_index)
        try:
            future = self._client.send_goal_async(goal)
        except Exception as exc:  # pragma: no cover - ROS transport boundary
            self._fail(f"planner send error: {exc}")
            return
        future.add_done_callback(
            lambda result: self._goal_response(result, generation, segment_index)
        )

    def _goal_response(self, future, generation, segment_index):
        if not self._segment_is_current(generation, segment_index):
            return
        try:
            handle = future.result()
        except Exception as exc:  # pragma: no cover - ROS transport boundary
            self._fail(f"planner goal error: {exc}")
            return
        if not handle.accepted:
            self._fail(f"segment {segment_index} rejected")
            return
        result = handle.get_result_async()
        result.add_done_callback(
            lambda value: self._segment_result(value, generation, segment_index)
        )

    def _segment_result(self, future, generation, segment_index):
        if not self._segment_is_current(generation, segment_index):
            return
        self._cancel_segment_timer()
        try:
            wrapped = future.result()
        except Exception as exc:  # pragma: no cover - ROS transport boundary
            self._fail(f"planner result error: {exc}")
            return
        if wrapped.status != GoalStatus.STATUS_SUCCEEDED:
            self._fail(
                f"segment {segment_index} {goal_status_name(wrapped.status)}"
            )
            return
        if not wrapped.result.path.poses:
            self._fail(f"segment {segment_index} returned an empty path")
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

    def _segment_is_current(self, generation, segment_index):
        return (
            self._busy
            and generation == self._segment_generation
            and segment_index == self._segment_index
        )

    def _arm_segment_timer(self, generation, segment_index):
        self._cancel_segment_timer()
        self._segment_timer = self.create_timer(
            self._segment_timeout_s,
            lambda: self._segment_timed_out(generation, segment_index),
        )

    def _cancel_segment_timer(self):
        if self._segment_timer is None:
            return
        timer = self._segment_timer
        self._segment_timer = None
        timer.cancel()
        self.destroy_timer(timer)

    def _segment_timed_out(self, generation, segment_index):
        if not self._segment_is_current(generation, segment_index):
            return
        self._fail(
            f"segment {segment_index} timed out after {self._segment_timeout_s:.1f}s"
        )


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
