from __future__ import annotations

from threading import Event, Lock
from typing import Any

from action_msgs.srv import CancelGoal
from agt_interfaces.action import ExecuteMission
from agt_interfaces.srv import SetMissionRunState
from rclpy.action import ActionClient
from rclpy.node import Node

from .mission_commands import MissionCommandResult


class MissionCommandAdapter:
    """Thin synchronous facade over the authoritative Mission ROS interfaces.

    Methods are invoked from Gateway worker threads while the owning ROS node is
    spun by the main executor thread. Futures therefore signal a threading Event
    instead of attempting a second spin on the same node.
    """

    def __init__(self, node: Node, *, timeout_s: float = 5.0) -> None:
        if timeout_s <= 0.0:
            raise ValueError('timeout_s must be > 0')
        self._node = node
        self._timeout_s = float(timeout_s)
        self._lock = Lock()
        self._execute_client = ActionClient(
            node,
            ExecuteMission,
            '/agt/missions/execute',
        )
        self._run_state_client = node.create_client(
            SetMissionRunState,
            '/agt/missions/set_run_state',
        )
        self._cancel_client = node.create_client(
            CancelGoal,
            '/agt/missions/execute/_action/cancel_goal',
        )

    def _wait_future(self, future: Any) -> Any:
        event = Event()
        future.add_done_callback(lambda _future: event.set())
        if not event.wait(self._timeout_s):
            raise TimeoutError('ROS command future timed out')
        if future.cancelled():
            raise RuntimeError('ROS command future was canceled')
        exception = future.exception()
        if exception is not None:
            raise RuntimeError(f'ROS command future failed: {exception}')
        return future.result()

    def start(
        self,
        mission_id: str,
        mission_version: str,
        expected_hash: str,
    ) -> MissionCommandResult:
        with self._lock:
            if not self._execute_client.wait_for_server(timeout_sec=self._timeout_s):
                return MissionCommandResult.unavailable_result(
                    'ExecuteMission action server is unavailable'
                )

            goal = ExecuteMission.Goal()
            goal.mission_id = mission_id
            goal.mission_version = mission_version
            goal.expected_content_sha256 = expected_hash
            try:
                goal_handle = self._wait_future(
                    self._execute_client.send_goal_async(goal)
                )
            except TimeoutError:
                return MissionCommandResult.timeout_result(
                    'ExecuteMission goal acceptance timed out'
                )
            except RuntimeError as exc:
                return MissionCommandResult.unavailable_result(str(exc))

            if goal_handle is None or not bool(goal_handle.accepted):
                return MissionCommandResult.rejected_result(
                    0,
                    'mission goal rejected by Mission Manager',
                )
            return MissionCommandResult.accepted_result('mission goal accepted')

    def pause(self, mission_id: str) -> MissionCommandResult:
        return self._set_run_state(
            mission_id,
            SetMissionRunState.Request.COMMAND_PAUSE,
        )

    def resume(self, mission_id: str) -> MissionCommandResult:
        return self._set_run_state(
            mission_id,
            SetMissionRunState.Request.COMMAND_RESUME,
        )

    def _set_run_state(
        self,
        mission_id: str,
        command: int,
    ) -> MissionCommandResult:
        with self._lock:
            if not self._run_state_client.wait_for_service(timeout_sec=self._timeout_s):
                return MissionCommandResult.unavailable_result(
                    'SetMissionRunState service is unavailable'
                )
            request = SetMissionRunState.Request()
            request.command = int(command)
            request.mission_id = mission_id
            try:
                response = self._wait_future(
                    self._run_state_client.call_async(request)
                )
            except TimeoutError:
                return MissionCommandResult.timeout_result(
                    'SetMissionRunState response timed out'
                )
            except RuntimeError as exc:
                return MissionCommandResult.unavailable_result(str(exc))

            if response is None:
                return MissionCommandResult.unavailable_result(
                    'SetMissionRunState returned no response'
                )
            if bool(response.success):
                return MissionCommandResult.accepted_result(str(response.message))
            return MissionCommandResult.rejected_result(
                int(response.error_code),
                str(response.message),
            )

    def cancel(self, mission_id: str) -> MissionCommandResult:
        # mission_id is intentionally validated by the HTTP layer against a
        # fresh authoritative RobotState before this cancel-all request is sent.
        del mission_id
        with self._lock:
            if not self._cancel_client.wait_for_service(timeout_sec=self._timeout_s):
                return MissionCommandResult.unavailable_result(
                    'Mission cancel service is unavailable'
                )
            cancel_request = CancelGoal.Request()
            try:
                response = self._wait_future(
                    self._cancel_client.call_async(cancel_request)
                )
            except TimeoutError:
                return MissionCommandResult.timeout_result(
                    'Mission cancel response timed out'
                )
            except RuntimeError as exc:
                return MissionCommandResult.unavailable_result(str(exc))

            if response is None:
                return MissionCommandResult.unavailable_result(
                    'Mission cancel service returned no response'
                )
            if (
                int(response.return_code) == CancelGoal.Response.ERROR_NONE
                and bool(response.goals_canceling)
            ):
                return MissionCommandResult.accepted_result(
                    'active mission cancel accepted'
                )
            if int(response.return_code) == CancelGoal.Response.ERROR_NONE:
                return MissionCommandResult.rejected_result(
                    int(response.return_code),
                    'no active mission goal accepted cancellation',
                )
            return MissionCommandResult.rejected_result(
                int(response.return_code),
                'Mission Manager rejected cancel request',
            )
