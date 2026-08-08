"""Nav2 FollowPath implementation of the internal VehicleTrackerAdapter boundary."""

from __future__ import annotations

import math
from typing import Callable

from action_msgs.msg import GoalStatus
from builtin_interfaces.msg import Time
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import FollowPath
from nav_msgs.msg import Path
from rclpy.action import ActionClient

from .route_runtime import RouteRuntimeError, RuntimePath, TrackerFeedback


def runtime_path_to_nav_path(runtime_path: RuntimePath, stamp: Time | None = None) -> Path:
    if runtime_path.frame_id != "odom":
        raise RouteRuntimeError("runtime_path_frame_invalid", "Nav2 tracker accepts odom RuntimePath only")
    if not runtime_path.points:
        raise RouteRuntimeError("runtime_path_empty", "Nav2 tracker requires a non-empty RuntimePath")
    message = Path()
    message.header.frame_id = "odom"
    message.header.stamp = stamp or Time()
    for point in runtime_path.points:
        pose = PoseStamped()
        pose.header = message.header
        pose.pose.position.x = float(point.x)
        pose.pose.position.y = float(point.y)
        pose.pose.orientation.z = math.sin(float(point.yaw) / 2.0)
        pose.pose.orientation.w = math.cos(float(point.yaw) / 2.0)
        message.poses.append(pose)
    return message


class Nav2FollowPathTrackerAdapter:
    """Asynchronous FollowPath client used only as a Route segment tracker.

    The adapter never requests a global path. F/R semantics stay at the Route
    layer and may select different controller IDs for the same FollowPath action.
    """

    def __init__(
        self,
        node=None,
        *,
        action_client=None,
        action_name: str = "follow_path",
        controller_id_forward: str = "",
        controller_id_reverse: str = "",
        goal_checker_id: str = "",
        progress_checker_id: str = "",
        wait_timeout_sec: float = 2.0,
        feedback_sink: Callable[[TrackerFeedback], None] | None = None,
        stamp_provider: Callable[[], Time] | None = None,
    ):
        if action_client is None and node is None:
            raise ValueError("node or action_client is required")
        self._node = node
        self._client = action_client or ActionClient(node, FollowPath, action_name)
        self._controller_forward = str(controller_id_forward)
        self._controller_reverse = str(controller_id_reverse)
        self._goal_checker_id = str(goal_checker_id)
        self._progress_checker_id = str(progress_checker_id)
        self._wait_timeout = float(wait_timeout_sec)
        if self._wait_timeout <= 0.0:
            raise ValueError("wait_timeout_sec must be positive")
        self._feedback_sink = feedback_sink
        self._stamp_provider = stamp_provider or self._default_stamp
        self._segment_id = ""
        self._goal_handle = None
        self._send_future = None
        self._cancel_requested = False

    def set_feedback_sink(self, sink: Callable[[TrackerFeedback], None] | None) -> None:
        self._feedback_sink = sink

    @property
    def active_segment_id(self) -> str:
        return self._segment_id

    def start(self, path: RuntimePath) -> None:
        if self._segment_id:
            raise RouteRuntimeError("tracker_already_active", "FollowPath tracker already has an active segment")
        if not self._client.wait_for_server(timeout_sec=self._wait_timeout):
            raise RouteRuntimeError("nav2_follow_path_unavailable", "Nav2 FollowPath action is unavailable")
        goal = self.build_goal(path)
        self._segment_id = path.segment_id
        self._cancel_requested = False
        self._send_future = self._client.send_goal_async(goal, feedback_callback=self._feedback_callback)
        self._send_future.add_done_callback(self._goal_response_done)

    def cancel(self) -> None:
        if not self._segment_id:
            return
        self._cancel_requested = True
        if self._goal_handle is not None:
            self._goal_handle.cancel_goal_async()

    def build_goal(self, path: RuntimePath) -> FollowPath.Goal:
        goal = FollowPath.Goal()
        goal.path = runtime_path_to_nav_path(path, self._stamp_provider())
        controller_id = self._controller_reverse if path.direction == "R" else self._controller_forward
        goal.controller_id = controller_id
        goal.goal_checker_id = self._goal_checker_id
        if hasattr(goal, "progress_checker_id"):
            goal.progress_checker_id = self._progress_checker_id
        return goal

    def _default_stamp(self) -> Time:
        if self._node is None:
            return Time()
        return self._node.get_clock().now().to_msg()

    def _emit(self, feedback: TrackerFeedback) -> None:
        if self._feedback_sink is not None:
            self._feedback_sink(feedback)

    def _feedback_callback(self, message) -> None:
        feedback = message.feedback
        remaining = float(getattr(feedback, "distance_to_goal", 0.0))
        self._emit(
            TrackerFeedback(
                "RUNNING",
                self._segment_id,
                remaining_distance_m=max(0.0, remaining),
            )
        )

    def _goal_response_done(self, future) -> None:
        try:
            handle = future.result()
        except Exception as exc:  # pragma: no cover - middleware-specific failure
            self._emit_terminal_failure(f"FollowPath goal response failed: {exc}")
            return
        if handle is None or not handle.accepted:
            self._emit_terminal_failure("Nav2 rejected FollowPath segment")
            return
        self._goal_handle = handle
        if self._cancel_requested:
            handle.cancel_goal_async()
        result_future = handle.get_result_async()
        result_future.add_done_callback(self._result_done)

    def _result_done(self, future) -> None:
        segment_id = self._segment_id
        try:
            wrapped = future.result()
            status = int(wrapped.status)
            result = wrapped.result
            error_code = int(getattr(result, "error_code", 0))
            error_msg = str(getattr(result, "error_msg", ""))
        except Exception as exc:  # pragma: no cover - middleware-specific failure
            self._emit_terminal_failure(f"FollowPath result failed: {exc}")
            return
        self._clear_active()
        if status == GoalStatus.STATUS_SUCCEEDED and error_code == 0:
            self._emit(TrackerFeedback("SUCCEEDED", segment_id))
        else:
            reason = error_msg or f"FollowPath failed status={status} error_code={error_code}"
            self._emit(TrackerFeedback("FAILED", segment_id, failure_reason=reason))

    def _emit_terminal_failure(self, reason: str) -> None:
        segment_id = self._segment_id
        self._clear_active()
        self._emit(TrackerFeedback("FAILED", segment_id, failure_reason=str(reason)))

    def _clear_active(self) -> None:
        self._segment_id = ""
        self._goal_handle = None
        self._send_future = None
        self._cancel_requested = False
