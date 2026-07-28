#!/usr/bin/env python3

from __future__ import annotations

import asyncio
import copy
import math
from pathlib import Path
import threading
import time
from typing import Callable

from action_msgs.msg import GoalStatus
from agt_interfaces.action import ExecuteMission, ExecuteWaypointTask
from agt_interfaces.msg import (
    LocalizationStatus, MapVersionSummary, MissionEvent, MissionStatus, TaskReadiness,
)
from agt_interfaces.srv import SetMissionRunState
from agt_navigation.task_group import TaskGroupError, load_task_group
from geometry_msgs.msg import PoseStamped
import rclpy
from rclpy.action import ActionClient, ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy

from agt_mission_manager.audit_log import AuditLog
from agt_mission_manager.mission_executor import (
    EventInbox, MissionExecutor, WaypointCursor, WaypointResult,
)
from agt_mission_manager.mission_model import (
    GateSnapshot, MissionError, MissionEventRecord, MissionRuntimeStatus, MissionState, StepType,
)
from agt_mission_manager.mission_storage import MissionStorage


class RosWaypointRunner:
    def __init__(
        self,
        node: Node,
        callback_group: ReentrantCallbackGroup,
        *,
        action_name: str,
        server_wait_timeout_s: float,
    ) -> None:
        self._node = node
        self._client = ActionClient(
            node, ExecuteWaypointTask, action_name, callback_group=callback_group
        )
        self._server_wait_timeout_s = server_wait_timeout_s
        self._child = None
        self._lock = threading.RLock()

    @staticmethod
    async def _await_ros_future(future):
        while not future.done():
            await asyncio.sleep(0.005)
        exception = future.exception()
        if exception is not None:
            raise exception
        return future.result()

    @staticmethod
    def _pose(point, stamp) -> PoseStamped:
        message = PoseStamped()
        message.header.frame_id = "map"
        message.header.stamp = stamp
        message.pose.position.x = point.x
        message.pose.position.y = point.y
        message.pose.orientation.z = math.sin(point.yaw / 2.0)
        message.pose.orientation.w = math.cos(point.yaw / 2.0)
        return message

    async def run(
        self,
        task_file: str,
        cursor: WaypointCursor,
        feedback: Callable[[WaypointCursor], None],
    ) -> WaypointResult:
        try:
            task = load_task_group(task_file)
        except TaskGroupError as exc:
            return WaypointResult(False, error_code=20, message=str(exc))
        points = list(task.enabled_points)
        total = len(points)
        loop_count = task.loop_count if task.loop else 1
        start_loop = min(cursor.loop_index, loop_count - 1)
        start_waypoint = min(cursor.waypoint_index, total - 1)
        if not self._client.wait_for_server(timeout_sec=self._server_wait_timeout_s):
            return WaypointResult(False, error_code=40, message="ExecuteWaypointTask server is unavailable")

        for loop_index in range(start_loop, loop_count):
            offset = start_waypoint if loop_index == start_loop else 0
            requested_points = points[offset:]
            request = ExecuteWaypointTask.Goal()
            stamp = self._node.get_clock().now().to_msg()
            request.poses = [self._pose(point, stamp) for point in requested_points]
            request.loop = False
            request.loop_count = 1

            def on_feedback(message, loop_index=loop_index, offset=offset):
                feedback(
                    WaypointCursor(
                        loop_index=loop_index,
                        waypoint_index=min(offset + int(message.feedback.current_waypoint), total - 1),
                        total_waypoints=total,
                    )
                )

            handle = await self._await_ros_future(
                self._client.send_goal_async(request, feedback_callback=on_feedback)
            )
            if not handle.accepted:
                return WaypointResult(False, error_code=41, message="ExecuteWaypointTask rejected child goal")
            with self._lock:
                self._child = handle
            feedback(WaypointCursor(loop_index, offset, total))
            wrapped = await self._await_ros_future(handle.get_result_async())
            with self._lock:
                self._child = None
            canceled = wrapped.status == GoalStatus.STATUS_CANCELED
            if canceled:
                return WaypointResult(
                    False,
                    error_code=int(wrapped.result.error_code),
                    message=str(wrapped.result.message),
                    canceled=True,
                    cancel_confirmed=True,
                    missed_waypoints=tuple(wrapped.result.missed_waypoints),
                )
            if wrapped.status != GoalStatus.STATUS_SUCCEEDED or not wrapped.result.success:
                return WaypointResult(
                    False,
                    error_code=int(wrapped.result.error_code),
                    message=str(wrapped.result.message),
                    missed_waypoints=tuple(wrapped.result.missed_waypoints),
                )
            if wrapped.result.missed_waypoints:
                return WaypointResult(
                    False,
                    error_code=int(wrapped.result.error_code),
                    message="waypoint child reported missed waypoints",
                    missed_waypoints=tuple(wrapped.result.missed_waypoints),
                )
            feedback(WaypointCursor(loop_index + 1, 0, total))
        return WaypointResult(True, message="waypoint task completed")

    async def cancel(self) -> bool:
        with self._lock:
            child = self._child
        if child is None:
            return True
        response = await self._await_ros_future(child.cancel_goal_async())
        return bool(response.goals_canceling)


class MissionManagerNode(Node):
    def __init__(self) -> None:
        super().__init__("agt_mission_manager")
        runtime_dir = Path(str(self.declare_parameter("runtime_dir", "runtime").value)).expanduser()
        mission_root_value = str(self.declare_parameter("mission_root", "").value).strip()
        map_root_value = str(self.declare_parameter("map_root", "").value).strip()
        self._mission_root = (
            Path(mission_root_value).expanduser() if mission_root_value else runtime_dir / "missions"
        ).resolve()
        self._map_root = (
            Path(map_root_value).expanduser() if map_root_value else runtime_dir / "maps"
        ).resolve()
        self._maximum_duration_s = float(self.declare_parameter("maximum_duration_s", 86400.0).value)
        self._maximum_event_timeout_s = float(
            self.declare_parameter("maximum_event_timeout_s", 86400.0).value
        )
        self._maximum_steps = int(self.declare_parameter("maximum_steps", 100).value)
        server_wait = float(self.declare_parameter("waypoint_server_wait_timeout_s", 5.0).value)
        self._localization_timeout_s = float(
            self.declare_parameter("localization_status_timeout_s", 10.0).value
        )
        self._readiness_timeout_s = float(
            self.declare_parameter("task_readiness_timeout_s", 3.0).value
        )
        if min(
            self._maximum_duration_s,
            self._maximum_event_timeout_s,
            server_wait,
            self._localization_timeout_s,
            self._readiness_timeout_s,
        ) <= 0.0 or self._maximum_steps <= 0:
            raise ValueError("mission limits and timeouts must be positive")

        self._storage = MissionStorage(self._mission_root)
        self._events = EventInbox()
        self._map = None
        self._localization = None
        self._localization_seen = float("-inf")
        self._readiness = None
        self._readiness_seen = float("-inf")
        self._executor = None
        self._active = False
        self._status = MissionRuntimeStatus()
        self._lock = threading.RLock()
        callback_group = ReentrantCallbackGroup()
        latched = QoSProfile(depth=1)
        latched.reliability = ReliabilityPolicy.RELIABLE
        latched.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self._publisher = self.create_publisher(
            MissionStatus, "/agt/missions/status", latched
        )
        self.create_subscription(
            MapVersionSummary, "/agt/maps/active", self._map_callback, latched, callback_group=callback_group
        )
        self.create_subscription(
            LocalizationStatus, "/agt/localization/status", self._localization_callback, 10, callback_group=callback_group
        )
        self.create_subscription(
            TaskReadiness, "/agt/system/task_readiness", self._readiness_callback, 10, callback_group=callback_group
        )
        self.create_subscription(
            MissionEvent, "/agt/missions/events", self._event_callback, 10, callback_group=callback_group
        )
        self._waypoint_runner = RosWaypointRunner(
            self,
            callback_group,
            action_name=str(
                self.declare_parameter(
                    "waypoint_action_name", "/agt/navigation/execute_waypoint_task"
                ).value
            ),
            server_wait_timeout_s=server_wait,
        )
        self.create_service(
            SetMissionRunState,
            "/agt/missions/set_run_state",
            self._set_run_state,
            callback_group=callback_group,
        )
        self._server = ActionServer(
            self,
            ExecuteMission,
            "/agt/missions/execute",
            execute_callback=self._execute,
            goal_callback=self._goal_callback,
            cancel_callback=self._cancel_callback,
            callback_group=callback_group,
        )
        self._restore_interrupted_status()
        self._publish_status(self._status)

    def _restore_interrupted_status(self) -> None:
        try:
            recovered = self._storage.recover_interrupted()
        except MissionError as exc:
            self.get_logger().error(str(exc))
            return
        if not recovered or int(recovered.get("state", 0)) != int(MissionState.INTERRUPTED):
            return
        self._status.state = MissionState.INTERRUPTED
        self._status.mission_id = str(recovered.get("mission_id", ""))
        self._status.mission_version = str(recovered.get("mission_version", ""))
        self._status.message = str(recovered.get("message", "mission execution interrupted"))

    def _map_callback(self, message) -> None:
        self._map = message

    def _localization_callback(self, message) -> None:
        self._localization = message
        self._localization_seen = time.monotonic()

    def _readiness_callback(self, message) -> None:
        self._readiness = message
        self._readiness_seen = time.monotonic()

    def _event_callback(self, message) -> None:
        stamp_s = float(message.header.stamp.sec) + float(message.header.stamp.nanosec) * 1.0e-9
        self._events.push(
            MissionEventRecord(
                stamp_s=stamp_s,
                event_type=str(message.event_type),
                source=str(message.source),
                correlation_id=str(message.correlation_id),
                mission_id=str(message.mission_id),
            )
        )

    @staticmethod
    def _localization_ready(message) -> bool:
        return bool(
            message is not None
            and message.state == LocalizationStatus.STATE_TRACKING
            and message.pose_valid
            and message.localization_accepted
            and message.error_code == LocalizationStatus.ERROR_NONE
            and not message.status_stale
        )

    def _gate_snapshot(self) -> GateSnapshot:
        active_map = self._map
        now = time.monotonic()
        localization = (
            self._localization
            if now - self._localization_seen <= self._localization_timeout_s
            else None
        )
        readiness = (
            self._readiness
            if now - self._readiness_seen <= self._readiness_timeout_s
            else None
        )
        return GateSnapshot(
            map_id=str(active_map.map_id) if active_map is not None and active_map.active else "",
            map_version_id=(
                str(active_map.map_version_id) if active_map is not None and active_map.active else ""
            ),
            manifest_sha256=(
                str(active_map.manifest_sha256) if active_map is not None and active_map.active else ""
            ),
            localization_ready=self._localization_ready(localization),
            task_ready=bool(readiness is not None and readiness.ready),
            blocker_codes=tuple(readiness.blocker_codes) if readiness is not None else ("READINESS_UNKNOWN",),
            blocker_messages=tuple(readiness.blocker_messages) if readiness is not None else ("TaskReadiness has not been received",),
        )

    def _task_path(self, mission, step) -> str:
        root = (
            self._map_root
            / mission.map_binding.map_id
            / "versions"
            / mission.map_binding.map_version_id
        ).resolve()
        path = (root / step.task_file).resolve()
        try:
            path.relative_to(root / "tasks")
        except ValueError as exc:
            raise MissionError("mission task path escapes the bound map tasks directory") from exc
        if not path.is_file():
            raise MissionError(f"mission task asset does not exist: {step.task_file}")
        task = load_task_group(path)
        if (
            task.map_binding.map_id != mission.map_binding.map_id
            or task.map_binding.map_version_id != mission.map_binding.map_version_id
        ):
            raise MissionError("waypoint task map binding does not match mission")
        return str(path)

    def _to_message(self, value: MissionRuntimeStatus) -> MissionStatus:
        message = MissionStatus()
        message.header.stamp = self.get_clock().now().to_msg()
        message.state = int(value.state)
        message.mission_id = value.mission_id
        message.mission_version = value.mission_version
        message.content_sha256 = value.content_sha256
        message.map_id = value.map_id
        message.map_version_id = value.map_version_id
        message.map_manifest_sha256 = value.map_manifest_sha256
        message.current_step_index = value.current_step_index
        message.total_steps = value.total_steps
        message.current_step_id = value.current_step_id
        message.current_step_type = int(value.current_step_type)
        message.current_waypoint = value.current_waypoint
        message.total_waypoints = value.total_waypoints
        message.step_elapsed_s = value.step_elapsed_s
        message.step_remaining_s = value.step_remaining_s
        message.error_code = int(value.error_code)
        message.blocker_codes = list(value.blocker_codes)
        message.blocker_messages = list(value.blocker_messages)
        message.message = value.message
        return message

    def _publish_status(self, value: MissionRuntimeStatus) -> None:
        self._status = copy.deepcopy(value)
        self._publisher.publish(self._to_message(value))

    def _goal_callback(self, request):
        with self._lock:
            if self._active:
                return GoalResponse.REJECT
        try:
            self._storage.mission_path(request.mission_id, request.mission_version)
        except MissionError:
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def _cancel_callback(self, _goal_handle):
        executor = self._executor
        if executor is not None:
            executor.request_cancel()
        return CancelResponse.ACCEPT

    def _set_run_state(self, request, response):
        executor = self._executor
        if executor is None or (request.mission_id and request.mission_id != self._status.mission_id):
            response.success = False
            response.error_code = MissionStatus.ERROR_INVALID_MISSION
            response.status = self._to_message(self._status)
            response.message = "no matching active mission"
            return response
        if request.command == SetMissionRunState.Request.COMMAND_PAUSE:
            success, message = executor.request_pause()
        elif request.command == SetMissionRunState.Request.COMMAND_RESUME:
            success, message = executor.request_resume()
        else:
            success, message = False, "unsupported run-state command"
        response.success = success
        response.error_code = MissionStatus.ERROR_NONE if success else MissionStatus.ERROR_INVALID_MISSION
        response.status = self._to_message(self._status)
        response.message = message
        return response

    def _execute(self, goal_handle):
        result = ExecuteMission.Result()
        with self._lock:
            self._active = True
        audit_path = self._mission_root / "audit" / goal_handle.request.mission_id / goal_handle.request.mission_version / "audit.jsonl"
        try:
            mission = self._storage.load(
                goal_handle.request.mission_id,
                goal_handle.request.mission_version,
                maximum_duration_s=self._maximum_duration_s,
                maximum_event_timeout_s=self._maximum_event_timeout_s,
                maximum_steps=self._maximum_steps,
            )
            if (
                goal_handle.request.expected_content_sha256
                and goal_handle.request.expected_content_sha256 != mission.content_sha256
            ):
                raise MissionError("expected_content_sha256 does not match stored mission")
            resolved_paths = {step.id: self._task_path(mission, step) for step in mission.steps if step.type == StepType.WAYPOINT_TASK}
            executor = MissionExecutor(
                storage=self._storage,
                audit=AuditLog(audit_path),
                waypoint_runner=self._waypoint_runner,
                gate_provider=self._gate_snapshot,
                event_inbox=self._events,
                wall_time=lambda: self.get_clock().now().nanoseconds * 1.0e-9,
                status_callback=lambda status: (
                    self._publish_status(status),
                    goal_handle.publish_feedback(ExecuteMission.Feedback(status=self._to_message(status))),
                ),
            )
            self._executor = executor
            status = asyncio.run(
                executor.execute(mission, lambda step: resolved_paths[step.id])
            )
            final_message = self._to_message(status)
            result.success = status.state == MissionState.SUCCEEDED
            result.error_code = int(status.error_code)
            result.final_status = final_message
            result.audit_log_uri = str(audit_path)
            result.message = status.message
            if status.state == MissionState.SUCCEEDED:
                goal_handle.succeed()
            elif status.state == MissionState.CANCELED or goal_handle.is_cancel_requested:
                goal_handle.canceled()
            else:
                goal_handle.abort()
        except (MissionError, TaskGroupError) as exc:
            failed = MissionRuntimeStatus(
                state=MissionState.FAILED,
                mission_id=str(goal_handle.request.mission_id),
                mission_version=str(goal_handle.request.mission_version),
                error_code=MissionStatus.ERROR_INVALID_MISSION,
                message=str(exc),
            )
            self._publish_status(failed)
            result.success = False
            result.error_code = MissionStatus.ERROR_INVALID_MISSION
            result.final_status = self._to_message(failed)
            result.audit_log_uri = str(audit_path)
            result.message = str(exc)
            AuditLog(audit_path).append("mission_rejected", {"message": str(exc)})
            goal_handle.abort()
        except Exception as exc:
            self.get_logger().error(f"mission failed unexpectedly: {exc}")
            failed = MissionRuntimeStatus(
                state=MissionState.FAILED,
                mission_id=str(goal_handle.request.mission_id),
                mission_version=str(goal_handle.request.mission_version),
                error_code=MissionStatus.ERROR_INTERNAL,
                message=str(exc),
            )
            self._publish_status(failed)
            result.success = False
            result.error_code = MissionStatus.ERROR_INTERNAL
            result.final_status = self._to_message(failed)
            result.audit_log_uri = str(audit_path)
            result.message = str(exc)
            goal_handle.abort()
        finally:
            self._executor = None
            with self._lock:
                self._active = False
        return result


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MissionManagerNode()
    executor = MultiThreadedExecutor(num_threads=4)
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        executor.shutdown()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
