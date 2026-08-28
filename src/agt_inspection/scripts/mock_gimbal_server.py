#!/usr/bin/env python3

import time

import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
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
            callback_group=ReentrantCallbackGroup(),
        )

    def _goal(self, request: MoveGimbal.Goal) -> GoalResponse:
        if not request.request_id or request.timeout_s <= 0.0:
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def _cancel(self, _goal_handle) -> CancelResponse:
        return CancelResponse.ACCEPT

    def _execute(self, goal_handle):
        request = goal_handle.request
        result = MoveGimbal.Result()
        deadline = time.monotonic() + max(self._delay_s, 0.0)
        while True:
            if goal_handle.is_cancel_requested:
                goal_handle.canceled()
                result.success = False
                result.error_code = MoveGimbal.Result.ERROR_CANCELED
                result.message = "mock gimbal canceled"
                return result
            remaining = deadline - time.monotonic()
            if remaining <= 0.0:
                break
            step = min(0.01, remaining)
            time.sleep(step)

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

    def destroy_node(self):
        self._server.destroy()
        return super().destroy_node()


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MockGimbalServer()
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
