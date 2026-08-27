#!/usr/bin/env python3

import asyncio

import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.node import Node

from agt_interfaces.action import MoveGimbal


class MockGimbalServer(Node):
    def __init__(self) -> None:
        super().__init__("agt_mock_gimbal")
        self._delay_s = float(self.declare_parameter("delay_s", 0.05).value)
        self._server = ActionServer(
            self,
            MoveGimbal,
            "/agt/gimbal/move",
            execute_callback=self._execute,
            goal_callback=self._goal,
            cancel_callback=self._cancel,
        )

    def _goal(self, request: MoveGimbal.Goal) -> GoalResponse:
        if not request.request_id or request.timeout_s <= 0.0:
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def _cancel(self, _goal_handle) -> CancelResponse:
        return CancelResponse.ACCEPT

    async def _execute(self, goal_handle):
        request = goal_handle.request
        result = MoveGimbal.Result()
        elapsed = 0.0
        while elapsed < self._delay_s:
            if goal_handle.is_cancel_requested:
                goal_handle.canceled()
                result.success = False
                result.error_code = MoveGimbal.Result.ERROR_CANCELED
                result.message = "mock gimbal canceled"
                return result
            step = min(0.01, self._delay_s - elapsed)
            await asyncio.sleep(step)
            elapsed += step

        feedback = MoveGimbal.Feedback()
        feedback.state = "AT_TARGET"
        feedback.current_pan_rad = request.pan_rad
        feedback.current_tilt_rad = request.tilt_rad
        goal_handle.publish_feedback(feedback)
        goal_handle.succeed()
        result.success = True
        result.error_code = MoveGimbal.Result.ERROR_NONE
        result.final_pan_rad = request.pan_rad
        result.final_tilt_rad = request.tilt_rad
        result.message = "mock gimbal reached target"
        return result


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MockGimbalServer()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
