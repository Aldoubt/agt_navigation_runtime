#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image

from agt_interfaces.srv import CaptureImage


class MockCameraServer(Node):
    def __init__(self) -> None:
        super().__init__("agt_mock_camera")
        self._service = self.create_service(
            CaptureImage,
            "/agt/camera/capture",
            self._capture,
        )

    def _capture(self, request, response):
        if not request.request_id or not request.camera_id:
            response.success = False
            response.error_code = CaptureImage.Response.ERROR_INVALID_REQUEST
            response.message = "request_id and camera_id are required"
            return response

        image = Image()
        image.header.stamp = self.get_clock().now().to_msg()
        image.header.frame_id = "mock_camera_optical_frame"
        image.height = 16
        image.width = 16
        image.encoding = "rgb8"
        image.is_bigendian = 0
        image.step = image.width * 3
        image.data = bytes(
            ((x * 17 + y * 11 + channel * 53) % 256)
            for y in range(image.height)
            for x in range(image.width)
            for channel in range(3)
        )

        response.success = True
        response.error_code = CaptureImage.Response.ERROR_NONE
        response.image = image
        response.image_uri = ""
        response.message = "mock 16x16 rgb8 capture"
        return response


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MockCameraServer()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
