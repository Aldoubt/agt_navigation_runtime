from __future__ import annotations

import asyncio

from agt_interfaces.srv import CaptureCamera, CaptureImage
from ..interfaces.camera import CaptureRequest, CaptureResult
from ..backend.mock_camera_backend import MockCameraBackend


class CameraCapability:
    """Stable application boundary; it knows no concrete camera hardware."""

    def __init__(self, node, *, service_name="/agt/camera/capability/capture", backend=None):
        self._node = node
        self._service_name = service_name
        self._backend = backend
        self._client = None if backend is not None else node.create_client(CaptureCamera, service_name)

    @classmethod
    def local_mock(cls, node):
        return cls(node, backend=MockCameraBackend())

    @classmethod
    def legacy_service(cls, node, service_name):
        """Compatibility client for the original minimal CaptureImage endpoint."""
        instance = cls.__new__(cls)
        instance._node = node
        instance._service_name = service_name
        instance._backend = None
        instance._legacy = True
        instance._client = node.create_client(CaptureImage, service_name)
        return instance

    def ready(self, timeout_s=2.0):
        if self._backend is not None:
            return self._backend.ready()
        ok = self._client.wait_for_service(timeout_sec=float(timeout_s))
        return ok, "camera capability service ready" if ok else f"camera capability service unavailable: {self._service_name}"

    async def capture(self, request: CaptureRequest) -> CaptureResult:
        if self._backend is not None:
            return await self._backend.capture(request)
        if getattr(self, "_legacy", False):
            message = CaptureImage.Request()
            message.request_id = request.request_id
            message.camera_id = request.camera_id
            response = await self._client.call_async(message)
            return CaptureResult(
                bool(response.success), bytes(response.image.data), str(response.image_uri),
                ".img", str(response.message), request.yaw,
                request.target_pitch, None, int(response.error_code),
            )
        message = CaptureCamera.Request()
        message.request_id = request.request_id
        message.camera_id = request.camera_id
        message.waypoint_id = request.waypoint_id
        message.target_heading = request.yaw
        message.target_pitch = request.target_pitch
        message.capture_tag = request.capture_tag
        message.save_image = request.save_image
        response = await self._client.call_async(message)
        stamp = float(response.capture_stamp.sec) + float(response.capture_stamp.nanosec) * 1e-9
        return CaptureResult(
            bool(response.success), bytes(response.image.data), str(response.image_uri),
            ".img", str(response.message), float(response.actual_heading),
            float(response.actual_pitch), stamp, int(response.error_code),
        )

    async def cancel(self):
        if self._backend is not None:
            return await self._backend.cancel()
        return True
