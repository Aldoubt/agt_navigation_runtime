from __future__ import annotations

import asyncio
from dataclasses import asdict
import threading
import uuid
from pathlib import Path
from typing import Callable

from agt_interfaces.action import ExecuteBehaviorTree
from rclpy.action import ActionClient

from .audit_log import AuditLog
from .mission_model import Mission, MissionError, MissionErrorCode, MissionRuntimeStatus, MissionState, StepType
from agt_navigation.task_group import load_task_group


class RosBehaviorTreeRunner:
    """Internal BT execution-engine client; it never owns public Mission state."""
    def __init__(self, node, callback_group, *, server_wait_timeout_s: float,
                 goal_response_timeout_s: float = 5.0, result_timeout_s: float = 3700.0,
                 cancel_timeout_s: float = 2.0):
        self._node = node
        self._client = ActionClient(node, ExecuteBehaviorTree, "/agt/internal/bt/execute", callback_group=callback_group)
        self._server_wait_timeout_s = server_wait_timeout_s
        self._goal_response_timeout_s = goal_response_timeout_s
        self._result_timeout_s = result_timeout_s
        self._cancel_timeout_s = min(cancel_timeout_s, 2.0)
        self._child = None
        self._lock = threading.RLock()

    @property
    def cancel_timeout_s(self) -> float:
        return self._cancel_timeout_s

    async def run(self, task, execution_id: str, feedback: Callable) -> tuple[bool, int, str, str, str]:
        if not self._client.wait_for_server(timeout_sec=self._server_wait_timeout_s):
            return False, int(MissionErrorCode.INTERNAL), "BT executor action server is unavailable", "", ""
        goal = ExecuteBehaviorTree.Goal()
        goal.tree_id = "v25_06_waypoint_mission"
        goal.execution_id = execution_id
        goal.map_id = task.map_binding.map_id
        goal.map_version_id = task.map_binding.map_version_id
        goal.task_group_id = task.task_group_id
        goal.task_revision = int(task.revision)
        goal.expected_content_sha256 = task.content_sha256
        goal.loop_count = int(task.loop_count if task.loop else 1)
        goal.client_request_id = execution_id

        def on_feedback(message):
            feedback(message.feedback)

        handle = await self._await(self._client.send_goal_async(goal, feedback_callback=on_feedback), self._goal_response_timeout_s)
        if not handle.accepted:
            return False, int(MissionErrorCode.CHILD_REJECTED), "BT execution request rejected", "", ""
        with self._lock:
            self._child = handle
        result = await self._await(handle.get_result_async(), self._result_timeout_s)
        with self._lock:
            self._child = None
        if result.result.success:
            return True, 0, result.result.message, "", ""
        code = int(result.result.error_code)
        mapped = {
            ExecuteBehaviorTree.Goal.ERROR_CANCELED: MissionErrorCode.CANCELED,
            ExecuteBehaviorTree.Goal.ERROR_INVALID_REQUEST: MissionErrorCode.INVALID_MISSION,
            ExecuteBehaviorTree.Goal.ERROR_TREE_NOT_ALLOWED: MissionErrorCode.INVALID_MISSION,
            ExecuteBehaviorTree.Goal.ERROR_INTERNAL: MissionErrorCode.INTERNAL,
            ExecuteBehaviorTree.Goal.ERROR_TREE_FAILED: MissionErrorCode.CHILD_FAILED,
        }.get(code, MissionErrorCode.INTERNAL)
        return False, int(mapped), result.result.message, result.result.blocker_code, result.result.blocker_message

    @staticmethod
    async def _await(future, timeout_s: float | None = None):
        deadline = None if timeout_s is None else asyncio.get_running_loop().time() + timeout_s
        while not future.done():
            await asyncio.sleep(0.005)
            if deadline is not None and asyncio.get_running_loop().time() >= deadline:
                raise TimeoutError("BT action future timeout")
        if future.exception():
            raise future.exception()
        return future.result()

    async def cancel(self) -> bool:
        with self._lock:
            child = self._child
        if child is None:
            return True
        response = await self._await(child.cancel_goal_async(), self._cancel_timeout_s)
        return bool(response.goals_canceling)

    def destroy(self):
        self._client.destroy()


class BehaviorTreeMissionExecutor:
    def __init__(self, *, storage, audit: AuditLog, runner: RosBehaviorTreeRunner, status_callback: Callable):
        self.storage = storage
        self.audit = audit
        self.runner = runner
        self.status_callback = status_callback
        self._cancel = threading.Event()
        self.status = MissionRuntimeStatus()

    def request_cancel(self):
        self._cancel.set()

    def request_pause(self):
        return False, "pause/resume unsupported for V25-06 behavior_tree backend; cancel and restart the mission"

    def request_resume(self):
        return False, "pause/resume unsupported for V25-06 behavior_tree backend; cancel and restart the mission"

    def _publish(self, message: str):
        self.status.message = message
        state = asdict(self.status)
        state["state"] = int(self.status.state)
        state["current_step_type"] = int(self.status.current_step_type)
        state["error_code"] = int(self.status.error_code)
        self.storage.write_execution_state(state)
        self.status_callback(self.status)

    async def execute(self, mission: Mission, task_path: str) -> MissionRuntimeStatus:
        self.status = MissionRuntimeStatus.for_mission(mission)
        self._publish("validating behavior tree mission")
        if len(mission.steps) != 1 or mission.steps[0].type != StepType.WAYPOINT_TASK:
            raise MissionError("BT_BACKEND_UNSUPPORTED_MISSION_SHAPE")
        self.status.current_step_index = 0
        self.status.current_step_id = mission.steps[0].id
        self.status.current_step_type = mission.steps[0].type
        task = load_task_group(task_path)
        if not task.content_sha256 or task.content_sha256 != task.canonical_hash():
            raise MissionError("BT task content_sha256 is missing or does not match canonical content")
        if (task.map_binding.map_id != mission.map_binding.map_id or
                task.map_binding.map_version_id != mission.map_binding.map_version_id):
            raise MissionError("waypoint task map binding does not match mission")
        self.status.state = MissionState.RUNNING
        self.audit.append("bt_backend_started", {"tree_id": "v25_06_waypoint_mission"})
        self.audit.append("bt_tree_started", {"task_group_id": task.task_group_id})
        self._publish("behavior tree running")
        def feedback(value):
            self.status.current_waypoint = int(value.current_waypoint)
            self.status.total_waypoints = int(value.total_waypoints)
            self._publish("behavior tree waypoint task running")
        execution_id = f"bt_{uuid.uuid4().hex}"
        child = asyncio.create_task(self.runner.run(task, execution_id, feedback))
        while not child.done():
            if self._cancel.is_set():
                confirmed = await self.runner.cancel()
                if not confirmed:
                    self.status.state = MissionState.FAILED
                    self.status.error_code = MissionErrorCode.INTERNAL
                    self.audit.append("bt_tree_cancel_failed")
                    self._publish("behavior tree cancel was not confirmed")
                    return self.status
                try:
                    await asyncio.wait_for(asyncio.shield(child), timeout=self.runner.cancel_timeout_s)
                except asyncio.TimeoutError:
                    self.status.state = MissionState.FAILED
                    self.status.error_code = MissionErrorCode.INTERNAL
                    self.audit.append("bt_tree_cancel_timeout")
                    self._publish("behavior tree did not finish cancellation within the configured bound")
                    return self.status
                break
            await asyncio.sleep(0.02)
        success, code, message, blocker_code, blocker_message = await child
        if blocker_code:
            self.status.blocker_codes = [blocker_code]
            self.status.blocker_messages = [blocker_message] if blocker_message else []
            if code == int(MissionErrorCode.CHILD_FAILED):
                code = int(MissionErrorCode.READINESS_LOST)
        if self._cancel.is_set() or code == int(MissionErrorCode.CANCELED):
            self.status.state = MissionState.CANCELED; self.status.error_code = MissionErrorCode.CANCELED
            self.audit.append("bt_tree_canceled"); self._publish("behavior tree canceled"); return self.status
        if not success:
            self.status.state = MissionState.FAILED
            self.status.error_code = code if code in {int(item) for item in MissionErrorCode} else MissionErrorCode.INTERNAL
            self.audit.append("bt_tree_failed", {"message": message}); self._publish(message or "behavior tree failed"); return self.status
        self.status.state = MissionState.SUCCEEDED; self.status.error_code = MissionErrorCode.NONE
        self.audit.append("bt_tree_succeeded"); self._publish(message or "behavior tree succeeded"); return self.status
