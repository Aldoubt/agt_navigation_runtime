#!/usr/bin/env python3

import time

import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node

from agt_interfaces.action import ExecuteWaypointTask
from agt_interfaces.msg import NavigationSessionStatus


class MockWaypointTaskServer(Node):
    def __init__(self) -> None:
        super().__init__("agt_mock_waypoint_task_server")
        self._delay_s = float(self.declare_parameter("delay_s", 0.05).value)
        self._server = ActionServer(
            self,
            ExecuteWaypointTask,
            "/agt/navigation/execute_waypoint_task",
            execute_callback=self._execute,
            goal_callback=self._goal,
            cancel_callback=lambda _goal: CancelResponse.ACCEPT,
            callback_group=ReentrantCallbackGroup(),
        )

    def _goal(self, request: ExecuteWaypointTask.Goal) -> GoalResponse:
        formal = (
            request.map_id
            and request.map_version_id
            and request.task_group_id
            and request.task_revision > 0
            and request.expected_content_sha256
            and request.loop_count == 1
            and request.client_request_id
        )
        deprecated_empty = not request.task_file and not request.poses and not request.loop
        return GoalResponse.ACCEPT if formal and deprecated_empty else GoalResponse.REJECT

    def _execute(self, goal_handle):
        request = goal_handle.request
        result = ExecuteWaypointTask.Result()
        deadline = time.monotonic() + max(self._delay_s, 0.0)
        while True:
            if goal_handle.is_cancel_requested:
                goal_handle.canceled()
                result.success = False
                result.error_code = 8
                result.message = "mock navigation canceled"
                result.session_id = request.client_request_id
                return result
            remaining = deadline - time.monotonic()
            if remaining <= 0.0:
                break
            step = min(0.01, remaining)
            time.sleep(step)

        status = NavigationSessionStatus()
        status.header.stamp = self.get_clock().now().to_msg()
        status.session_id = request.client_request_id
        status.client_request_id = request.client_request_id
        status.map_id = request.map_id
        status.map_version_id = request.map_version_id
        status.task_group_id = request.task_group_id
        status.task_revision = request.task_revision
        status.task_content_sha256 = request.expected_content_sha256
        status.state = NavigationSessionStatus.STATE_RUNNING
        status.current_waypoint = 1
        status.total_waypoints = 1

        feedback = ExecuteWaypointTask.Feedback()
        feedback.state = "RUNNING"
        feedback.current_waypoint = 1
        feedback.total_waypoints = 1
        feedback.status = status
        goal_handle.publish_feedback(feedback)

        status.state = NavigationSessionStatus.STATE_SUCCEEDED
        status.terminal = True
        status.success = True
        result.success = True
        result.error_code = 0
        result.message = "mock waypoint completed"
        result.session_id = request.client_request_id
        result.final_status = status
        goal_handle.succeed()
        return result

    def destroy_node(self):
        self._server.destroy()
        return super().destroy_node()


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MockWaypointTaskServer()
    executor = MultiThreadedExecutor(num_threads=2)
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
