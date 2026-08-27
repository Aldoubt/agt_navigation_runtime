#!/usr/bin/env python3

import asyncio
import json

import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.node import Node

from agt_interfaces.action import InspectImage


class MockVisionServer(Node):
    def __init__(self) -> None:
        super().__init__("agt_mock_vision")
        self._delay_s = float(self.declare_parameter("delay_s", 0.05).value)
        self._server = ActionServer(
            self,
            InspectImage,
            "/agt/vision/inspect",
            execute_callback=self._execute,
            goal_callback=self._goal,
            cancel_callback=self._cancel,
        )

    def _goal(self, request: InspectImage.Goal) -> GoalResponse:
        if (
            not request.request_id
            or not request.task_id
            or not request.camera_id
            or request.image.width == 0
            or request.image.height == 0
        ):
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def _cancel(self, _goal_handle) -> CancelResponse:
        return CancelResponse.ACCEPT

    async def _execute(self, goal_handle):
        result = InspectImage.Result()
        elapsed = 0.0
        while elapsed < self._delay_s:
            if goal_handle.is_cancel_requested:
                goal_handle.canceled()
                result.success = False
                result.error_code = InspectImage.Result.ERROR_CANCELED
                result.message = "mock vision canceled"
                return result
            step = min(0.01, self._delay_s - elapsed)
            await asyncio.sleep(step)
            elapsed += step

        feedback = InspectImage.Feedback()
        feedback.stage = "INFERENCING"
        feedback.progress = 1.0
        goal_handle.publish_feedback(feedback)

        goal_handle.succeed()
        result.success = True
        result.error_code = InspectImage.Result.ERROR_NONE
        result.model_id = "mock-vision"
        result.model_version = "1"
        result.inference_time_ms = self._delay_s * 1000.0
        result.primary_confidence = 0.93
        result.result_json = json.dumps(
            {
                "class": "test_target",
                "confidence": 0.93,
                "raw_count": 3,
                "instances": [
                    {"local_instance_id": "I0001", "confidence": 0.93},
                    {"local_instance_id": "I0002", "confidence": 0.91},
                    {"local_instance_id": "I0003", "confidence": 0.89},
                ],
                "overlay_uri": "",
                "mask_uri": "",
            },
            separators=(",", ":"),
        )
        result.message = "mock inference completed"
        return result


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MockVisionServer()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
