from __future__ import annotations

import asyncio
import threading
import uuid

from action_msgs.msg import GoalStatus
from agt_interfaces.action import ExecuteWaypointTask
from rclpy.action import ActionClient

from .mission_executor import TaskGroupChildResult


class RosTaskGroupRunner:
    """Execute one registry-bound TaskGroup without deprecated pose/path inputs."""

    def __init__(
        self,
        node,
        callback_group,
        *,
        action_name: str = "/agt/navigation/execute_waypoint_task",
        server_wait_timeout_s: float = 5.0,
    ) -> None:
        self._client = ActionClient(
            node,
            ExecuteWaypointTask,
            action_name,
            callback_group=callback_group,
        )
        self._server_wait_timeout_s = float(server_wait_timeout_s)
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

    async def run(self, mission, step) -> TaskGroupChildResult:
        if not self._client.wait_for_server(timeout_sec=self._server_wait_timeout_s):
            return TaskGroupChildResult(
                False,
                error_code=40,
                message="ExecuteWaypointTask server is unavailable",
            )

        goal = ExecuteWaypointTask.Goal()
        goal.map_id = mission.map_binding.map_id
        goal.map_version_id = mission.map_binding.map_version_id
        goal.task_group_id = step.task_group_id
        goal.task_revision = step.task_group_revision
        goal.expected_content_sha256 = step.expected_content_sha256
        goal.loop_count = 1
        goal.client_request_id = (
            f"{mission.mission_id}:{step.id}:home:{uuid.uuid4().hex}"
        )

        handle = await self._await_ros_future(self._client.send_goal_async(goal))
        if not handle.accepted:
            return TaskGroupChildResult(
                False,
                error_code=41,
                message="ExecuteWaypointTask rejected return-home goal",
            )
        with self._lock:
            self._child = handle
        wrapped = await self._await_ros_future(handle.get_result_async())
        with self._lock:
            self._child = None
        canceled = wrapped.status == GoalStatus.STATUS_CANCELED
        return TaskGroupChildResult(
            success=(
                wrapped.status == GoalStatus.STATUS_SUCCEEDED
                and bool(wrapped.result.success)
                and not wrapped.result.missed_waypoints
            ),
            error_code=int(wrapped.result.error_code),
            message=str(wrapped.result.message),
            canceled=canceled,
            cancel_confirmed=canceled,
            session_id=str(wrapped.result.session_id),
        )

    async def cancel(self) -> bool:
        with self._lock:
            child = self._child
        if child is None:
            return True
        response = await self._await_ros_future(child.cancel_goal_async())
        return bool(response.goals_canceling)

    def destroy(self) -> None:
        self._client.destroy()
