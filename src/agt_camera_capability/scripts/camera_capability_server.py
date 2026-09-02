#!/usr/bin/env python3
from __future__ import annotations

import asyncio

import rclpy
from agt_interfaces.srv import CaptureCamera
from rclpy.node import Node

from agt_camera_capability.backend.autolabor_c1_backend import AutolaborC1Backend
from agt_camera_capability.backend.mock_camera_backend import MockCameraBackend
from agt_camera_capability.interfaces.camera import CaptureRequest


class CameraCapabilityServer(Node):
    def __init__(self):
        super().__init__("agt_camera_capability_server")
        backend_name = str(self.declare_parameter("backend", "mock").value).strip().lower()
        service_name = str(self.declare_parameter("service_name", "/agt/camera/capability/capture").value)
        if backend_name == "mock":
            self._backend = MockCameraBackend()
        elif backend_name == "autolabor_c1":
            self._backend = AutolaborC1Backend(self)
        else:
            raise ValueError(f"unsupported camera backend: {backend_name}")
        self._service = self.create_service(CaptureCamera, service_name, self._capture)

    def _capture(self, request, response):
        if not request.request_id or not request.waypoint_id:
            response.success = False
            response.error_code = CaptureCamera.Response.ERROR_INVALID_REQUEST
            response.message = "request_id and waypoint_id are required"
            return response
        capability_request = CaptureRequest(
            request_id=request.request_id, camera_id=request.camera_id,
            waypoint_id=request.waypoint_id, target_heading=request.target_heading,
            target_pitch=request.target_pitch, capture_tag=request.capture_tag,
            save_image=request.save_image,
        )
        result = asyncio.run(self._backend.capture(capability_request))
        response.success = result.success
        response.error_code = int(result.error_code)
        response.message = result.message
        response.image_uri = result.image_uri
        response.actual_heading = float(result.actual_heading or request.target_heading)
        response.actual_pitch = float(result.actual_pitch or request.target_pitch)
        if result.image_bytes:
            response.image.data = list(result.image_bytes)
        return response


def main(args=None):
    rclpy.init(args=args)
    node = CameraCapabilityServer()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
