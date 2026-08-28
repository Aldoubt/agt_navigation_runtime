#!/usr/bin/env python3

import json
import time

import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from sensor_msgs.msg import Image

from agt_interfaces.action import InspectImage
from agt_inspection.mock_visual import (
    MOCK_MODEL_ID,
    MOCK_MODEL_VERSION,
    MOCK_WEIGHTS_SHA256,
    build_mock_level1_payload,
)


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
            callback_group=ReentrantCallbackGroup(),
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

    @staticmethod
    def _overlay_image(source: Image) -> Image:
        """Return a deterministic mock overlay using the captured pixels unchanged."""
        overlay = Image()
        overlay.header = source.header
        overlay.height = source.height
        overlay.width = source.width
        overlay.encoding = source.encoding
        overlay.is_bigendian = source.is_bigendian
        overlay.step = source.step
        overlay.data = bytes(source.data)
        return overlay

    @staticmethod
    def _mask_image(source: Image) -> Image:
        """Return a deterministic mono8 checker mask for codec/E2E verification."""
        mask = Image()
        mask.header = source.header
        mask.height = source.height
        mask.width = source.width
        mask.encoding = "mono8"
        mask.is_bigendian = 0
        mask.step = source.width
        mask.data = bytes(
            255 if (x + y) % 2 == 0 else 0
            for y in range(source.height)
            for x in range(source.width)
        )
        return mask

    def _execute(self, goal_handle):
        result = InspectImage.Result()
        deadline = time.monotonic() + max(self._delay_s, 0.0)
        while True:
            if goal_handle.is_cancel_requested:
                goal_handle.canceled()
                result.success = False
                result.error_code = InspectImage.Result.ERROR_CANCELED
                result.message = "mock vision canceled"
                return result
            remaining = deadline - time.monotonic()
            if remaining <= 0.0:
                break
            step = min(0.01, remaining)
            time.sleep(step)

        feedback = InspectImage.Feedback()
        feedback.stage = "INFERENCING"
        feedback.progress = 1.0
        goal_handle.publish_feedback(feedback)

        source_image = goal_handle.request.image
        payload = build_mock_level1_payload()

        goal_handle.succeed()
        result.success = True
        result.error_code = InspectImage.Result.ERROR_NONE
        result.model_id = MOCK_MODEL_ID
        result.model_version = MOCK_MODEL_VERSION
        result.weights_sha256 = MOCK_WEIGHTS_SHA256
        result.inference_time_ms = self._delay_s * 1000.0
        result.primary_confidence = 0.93
        result.result_json = json.dumps(payload, separators=(",", ":"))
        result.overlay_image = self._overlay_image(source_image)
        result.mask_image = self._mask_image(source_image)
        result.message = "mock inference completed"
        return result

    def destroy_node(self):
        self._server.destroy()
        return super().destroy_node()


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MockVisionServer()
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
