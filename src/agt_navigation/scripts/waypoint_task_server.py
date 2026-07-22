#!/usr/bin/env python3

import json
import math
import threading
import time

from action_msgs.msg import GoalStatus
from agt_interfaces.action import ExecuteWaypointTask
from agt_interfaces.msg import LocalizationStatus, TaskReadiness
from diagnostic_msgs.msg import DiagnosticArray
from agt_navigation.qt_task_chain import (
    TaskChainError,
    Waypoint,
    load_qt_task_chain,
    point_inside_map,
)
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import FollowWaypoints
from nav_msgs.msg import OccupancyGrid
import rclpy
from rclpy.action import ActionClient, ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy
from std_msgs.msg import String


ERROR_NONE = 0
ERROR_INVALID_REQUEST = 10
ERROR_TASK_INVALID = 20
ERROR_MAP_UNAVAILABLE = 30
ERROR_POINT_OUTSIDE_MAP = 31
ERROR_SAFETY_NOT_READY = 35
ERROR_LOCALIZATION_NOT_READY = 36
ERROR_TASK_READINESS_NOT_READY = 37
ERROR_NAV2_UNAVAILABLE = 40
ERROR_NAV2_REJECTED = 41
ERROR_NAV2_FAILED = 42
ERROR_CANCELED = 50


class WaypointTaskServer(Node):
    def __init__(self, **kwargs):
        super().__init__("agt_waypoint_task_server", **kwargs)
        self.maximum_points = int(self.declare_parameter("maximum_points", 200).value)
        self.maximum_loops = int(self.declare_parameter("maximum_loops", 10).value)
        self.require_map = bool(self.declare_parameter("require_map", True).value)
        self.require_safety_ready = bool(
            self.declare_parameter("require_safety_ready", True).value
        )
        self.require_localization_valid = bool(
            self.declare_parameter("require_localization_valid", True).value
        )
        self.require_task_readiness = bool(
            self.declare_parameter("require_task_readiness", True).value
        )
        self.localization_status_timeout = float(
            self.declare_parameter("localization_status_timeout", 1.0).value
        )
        self.safety_status_timeout = float(
            self.declare_parameter("safety_status_timeout", 1.0).value
        )
        self.nav2_wait_timeout = float(
            self.declare_parameter("nav2_wait_timeout", 2.0).value
        )
        if (
            self.maximum_points <= 0
            or self.maximum_loops <= 0
            or self.safety_status_timeout <= 0.0
            or self.localization_status_timeout <= 0.0
            or self.nav2_wait_timeout <= 0.0
        ):
            raise ValueError("task limits and readiness timeouts must be positive")

        group = ReentrantCallbackGroup()
        self._map = None
        self._active = False
        self._child_goal_handle = None
        self._safety_ready = False
        self._safety_stamp = float("-inf")
        self._localization_ready = False
        self._localization_stamp = float("-inf")
        self._task_readiness = False
        self._task_readiness_stamp = float("-inf")
        self._lock = threading.RLock()
        map_qos = QoSProfile(depth=1)
        map_qos.reliability = ReliabilityPolicy.RELIABLE
        map_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self.create_subscription(
            OccupancyGrid,
            "/agt/map/global_occupancy",
            self._map_callback,
            map_qos,
            callback_group=group,
        )
        self.create_subscription(
            DiagnosticArray,
            "/agt/safety/status",
            self._safety_callback,
            10,
            callback_group=group,
        )
        self.create_subscription(
            LocalizationStatus,
            "/agt/localization/status",
            self._localization_callback,
            10,
            callback_group=group,
        )
        self.create_subscription(
            TaskReadiness,
            "/agt/system/task_readiness",
            self._task_readiness_callback,
            10,
            callback_group=group,
        )
        self._status = self.create_publisher(String, "/agt/navigation/task_status", 10)
        self._nav2 = ActionClient(
            self, FollowWaypoints, "follow_waypoints", callback_group=group
        )
        self._server = ActionServer(
            self,
            ExecuteWaypointTask,
            "/agt/navigation/execute_waypoint_task",
            execute_callback=self._execute,
            goal_callback=self._goal_callback,
            cancel_callback=self._cancel_callback,
            callback_group=group,
        )
        self.create_timer(0.2, self._safety_watchdog, callback_group=group)

    def _map_callback(self, message):
        self._map = message

    def _safety_callback(self, message):
        ready = False
        for status in message.status:
            if status.name != "agt_safety/tracked_controller":
                continue
            values = {item.key: item.value.lower() for item in status.values}
            ready = (
                values.get("motion_enabled") == "true"
                and values.get("estop_latched") == "false"
            )
            break
        with self._lock:
            self._safety_ready = ready
            self._safety_stamp = time.monotonic()
            child = self._child_goal_handle if self._active and not ready else None
        if child is not None:
            self.get_logger().error("Safety readiness was lost; canceling Nav2 task")
            child.cancel_goal_async()

    def _safety_is_ready(self):
        with self._lock:
            return self._safety_ready and (
                time.monotonic() - self._safety_stamp <= self.safety_status_timeout
            )

    @staticmethod
    def localization_status_is_ready(message):
        return (
            message.state == LocalizationStatus.STATE_TRACKING
            and message.pose_valid
            and message.localization_accepted
            and message.error_code == LocalizationStatus.ERROR_NONE
            and not message.status_stale
        )

    def _localization_callback(self, message):
        ready = self.localization_status_is_ready(message)
        with self._lock:
            self._localization_ready = ready
            self._localization_stamp = time.monotonic()
            child = self._child_goal_handle if self._active and not ready else None
        if child is not None:
            self.get_logger().error(
                "Localization readiness was lost; canceling Nav2 task"
            )
            child.cancel_goal_async()

    def _localization_is_ready(self):
        with self._lock:
            return self._localization_ready and (
                time.monotonic() - self._localization_stamp
                <= self.localization_status_timeout
            )

    def _task_readiness_callback(self, message):
        with self._lock:
            self._task_readiness = bool(message.ready)
            self._task_readiness_stamp = time.monotonic()
            child = self._child_goal_handle if self._active and not self._task_readiness else None
        if child is not None:
            self.get_logger().error("TaskReadiness was lost; canceling Nav2 task")
            child.cancel_goal_async()

    def _task_readiness_is_ready(self):
        with self._lock:
            return self._task_readiness and (
                time.monotonic() - self._task_readiness_stamp
                <= self.localization_status_timeout
            )

    def _safety_watchdog(self):
        if not self.require_safety_ready and not self.require_localization_valid and not self.require_task_readiness:
            return
        with self._lock:
            now = time.monotonic()
            safety_stale = now - self._safety_stamp > self.safety_status_timeout
            localization_stale = (
                now - self._localization_stamp > self.localization_status_timeout
            )
            unsafe = (
                (self.require_safety_ready and safety_stale)
                or (self.require_localization_valid and
                    (localization_stale or not self._localization_ready))
                or (self.require_task_readiness and not self._task_readiness_is_ready())
            )
            child = self._child_goal_handle if self._active and unsafe else None
            if self.require_safety_ready and safety_stale:
                self._safety_ready = False
            if self.require_localization_valid and localization_stale:
                self._localization_ready = False
        if child is not None:
            self.get_logger().error(
                "Safety or localization status became stale; canceling Nav2 task"
            )
            child.cancel_goal_async()

    def _publish_status(self, state, **values):
        message = String()
        message.data = json.dumps({"state": state, **values}, ensure_ascii=False)
        self._status.publish(message)

    def _goal_callback(self, request):
        with self._lock:
            if self._active:
                self.get_logger().warning("Rejecting task while another task is active")
                return GoalResponse.REJECT
        if self.require_localization_valid and not self._localization_is_ready():
            self.get_logger().warning(
                "Rejecting waypoint task because localization is not accepted"
            )
            return GoalResponse.REJECT
        if self.require_safety_ready and not self._safety_is_ready():
            self.get_logger().warning(
                "Rejecting waypoint task because agt_safety is not ready"
            )
            return GoalResponse.REJECT
        if self.require_task_readiness and not self._task_readiness_is_ready():
            self.get_logger().warning("Rejecting waypoint task because TaskReadiness is not ready")
            return GoalResponse.REJECT
        if request.loop and (request.loop_count == 0 or request.loop_count > self.maximum_loops):
            self.get_logger().warning(
                f"Rejecting unbounded/excessive loop request: {request.loop_count}"
            )
            return GoalResponse.REJECT
        with self._lock:
            self._active = True
        return GoalResponse.ACCEPT

    def _cancel_callback(self, _goal_handle):
        with self._lock:
            child = self._child_goal_handle
        if child is not None:
            child.cancel_goal_async()
        return CancelResponse.ACCEPT

    @staticmethod
    def _pose(point, stamp):
        pose = PoseStamped()
        pose.header.frame_id = "map"
        pose.header.stamp = stamp
        pose.pose.position.x = point.x
        pose.pose.position.y = point.y
        pose.pose.orientation.z = math.sin(point.theta / 2.0)
        pose.pose.orientation.w = math.cos(point.theta / 2.0)
        return pose

    def _load_points(self, request):
        if request.task_file and request.poses:
            raise TaskChainError("supply exactly one of task_file and poses")
        if request.task_file:
            return load_qt_task_chain(
                request.task_file, maximum_points=self.maximum_points
            )
        if not request.poses:
            raise TaskChainError("task_file or poses is required")
        if len(request.poses) > self.maximum_points:
            raise TaskChainError(
                f"task contains {len(request.poses)} waypoints; "
                f"limit is {self.maximum_points}"
            )
        points = []
        for index, pose in enumerate(request.poses):
            if pose.header.frame_id != "map":
                raise TaskChainError(f"pose {index} frame_id must be map")
            q = pose.pose.orientation
            values = (
                pose.pose.position.x,
                pose.pose.position.y,
                q.x,
                q.y,
                q.z,
                q.w,
            )
            if not all(math.isfinite(value) for value in values):
                raise TaskChainError(f"pose {index} contains a non-finite value")
            norm = math.sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w)
            if norm < 1.0e-9 or abs(norm - 1.0) > 1.0e-3:
                raise TaskChainError(
                    f"pose {index} orientation must be a normalized quaternion"
                )
            yaw = math.atan2(
                2.0 * (q.w * q.z + q.x * q.y),
                1.0 - 2.0 * (q.y * q.y + q.z * q.z),
            )
            points.append(
                Waypoint(
                    name=f"waypoint_{index:03d}",
                    x=pose.pose.position.x,
                    y=pose.pose.position.y,
                    theta=yaw,
                )
            )
        return points

    @staticmethod
    def _finish(result, success, error_code, message, missed=None):
        result.success = success
        result.error_code = error_code
        result.message = message
        result.missed_waypoints = list(missed or [])
        return result

    async def _execute(self, goal_handle):
        result = ExecuteWaypointTask.Result()
        try:
            try:
                points = self._load_points(goal_handle.request)
            except TaskChainError as exc:
                goal_handle.abort()
                self._publish_status("REJECTED", reason=str(exc))
                return self._finish(result, False, ERROR_TASK_INVALID, str(exc))

            current_map = self._map
            if self.require_map and current_map is None:
                goal_handle.abort()
                message = "global occupancy map has not been received"
                self._publish_status("REJECTED", reason=message)
                return self._finish(result, False, ERROR_MAP_UNAVAILABLE, message)
            if current_map is not None:
                outside = [point.name for point in points if not point_inside_map(point, current_map.info)]
                if outside:
                    goal_handle.abort()
                    message = "waypoints outside current map: " + ", ".join(outside)
                    self._publish_status("REJECTED", reason=message)
                    return self._finish(result, False, ERROR_POINT_OUTSIDE_MAP, message)

            if self.require_safety_ready and not self._safety_is_ready():
                goal_handle.abort()
                message = "agt_safety is stale, motion-disabled, or emergency-stopped"
                self._publish_status("REJECTED", reason=message)
                return self._finish(result, False, ERROR_SAFETY_NOT_READY, message)
            if self.require_localization_valid and not self._localization_is_ready():
                goal_handle.abort()
                message = "localization is stale, lost, or not accepted"
                self._publish_status("REJECTED", reason=message)
                return self._finish(
                    result, False, ERROR_LOCALIZATION_NOT_READY, message
                )
            if self.require_task_readiness and not self._task_readiness_is_ready():
                goal_handle.abort()
                message = "TaskReadiness is stale or blocked"
                self._publish_status("REJECTED", reason=message)
                return self._finish(result, False, ERROR_TASK_READINESS_NOT_READY, message)

            if not self._nav2.wait_for_server(timeout_sec=self.nav2_wait_timeout):
                goal_handle.abort()
                message = "Nav2 FollowWaypoints action is unavailable"
                self._publish_status("FAILED", reason=message)
                return self._finish(result, False, ERROR_NAV2_UNAVAILABLE, message)

            loop_count = goal_handle.request.loop_count if goal_handle.request.loop else 1
            all_missed = []
            for loop_index in range(loop_count):
                if goal_handle.is_cancel_requested:
                    goal_handle.canceled()
                    self._publish_status("CANCELED", loop_index=loop_index)
                    return self._finish(result, False, ERROR_CANCELED, "task canceled")

                nav_goal = FollowWaypoints.Goal()
                stamp = self.get_clock().now().to_msg()
                nav_goal.poses = [self._pose(point, stamp) for point in points]

                def feedback_callback(message, current_loop=loop_index):
                    feedback = ExecuteWaypointTask.Feedback()
                    feedback.state = "RUNNING"
                    feedback.loop_index = current_loop
                    feedback.current_waypoint = message.feedback.current_waypoint
                    feedback.total_waypoints = len(points)
                    goal_handle.publish_feedback(feedback)
                    self._publish_status(
                        "RUNNING",
                        loop_index=current_loop,
                        current_waypoint=message.feedback.current_waypoint,
                        total_waypoints=len(points),
                    )

                child_future = self._nav2.send_goal_async(
                    nav_goal, feedback_callback=feedback_callback
                )
                child_handle = await child_future
                if not child_handle.accepted:
                    goal_handle.abort()
                    message = "Nav2 rejected the waypoint chain"
                    self._publish_status("FAILED", reason=message)
                    return self._finish(result, False, ERROR_NAV2_REJECTED, message)

                with self._lock:
                    self._child_goal_handle = child_handle
                if goal_handle.is_cancel_requested:
                    cancel_response = await child_handle.cancel_goal_async()
                    if not cancel_response.goals_canceling:
                        goal_handle.abort()
                        message = "Nav2 did not accept task cancellation"
                        return self._finish(
                            result, False, ERROR_NAV2_FAILED, message
                        )
                    goal_handle.canceled()
                    return self._finish(result, False, ERROR_CANCELED, "task canceled")
                result_future = child_handle.get_result_async()
                wrapped = await result_future
                with self._lock:
                    self._child_goal_handle = None
                if goal_handle.is_cancel_requested:
                    goal_handle.canceled()
                    self._publish_status("CANCELED", loop_index=loop_index)
                    return self._finish(result, False, ERROR_CANCELED, "task canceled")
                if self.require_safety_ready and not self._safety_is_ready():
                    goal_handle.abort()
                    message = "agt_safety readiness was lost during task execution"
                    self._publish_status("FAILED", reason=message)
                    return self._finish(result, False, ERROR_SAFETY_NOT_READY, message)
                if self.require_localization_valid and not self._localization_is_ready():
                    goal_handle.abort()
                    message = "localization readiness was lost during task execution"
                    self._publish_status("FAILED", reason=message)
                    return self._finish(
                        result, False, ERROR_LOCALIZATION_NOT_READY, message
                    )
                if self.require_task_readiness and not self._task_readiness_is_ready():
                    goal_handle.abort()
                    message = "TaskReadiness was lost during task execution"
                    self._publish_status("FAILED", reason=message)
                    return self._finish(result, False, ERROR_TASK_READINESS_NOT_READY, message)
                missed = list(wrapped.result.missed_waypoints)
                all_missed.extend(missed)
                if wrapped.status != GoalStatus.STATUS_SUCCEEDED or missed:
                    goal_handle.abort()
                    message = (
                        f"Nav2 waypoint execution failed with status {wrapped.status}; "
                        f"missed={missed}"
                    )
                    self._publish_status("FAILED", reason=message)
                    return self._finish(result, False, ERROR_NAV2_FAILED, message, all_missed)

            goal_handle.succeed()
            self._publish_status("SUCCEEDED", loops=loop_count, waypoints=len(points))
            return self._finish(result, True, ERROR_NONE, "waypoint task completed")
        except Exception as exc:  # keep the Action boundary fail-closed
            self.get_logger().error(f"Waypoint task failed unexpectedly: {exc}")
            goal_handle.abort()
            self._publish_status("FAILED", reason=str(exc))
            return self._finish(result, False, ERROR_NAV2_FAILED, str(exc))
        finally:
            with self._lock:
                self._child_goal_handle = None
                self._active = False


def main(args=None):
    rclpy.init(args=args)
    node = WaypointTaskServer()
    executor = MultiThreadedExecutor(num_threads=2)
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
