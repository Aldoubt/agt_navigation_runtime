from ..interfaces.camera import CaptureRequest, CaptureResult


class MockCameraBackend:
    def ready(self):
        return True, "mock camera ready"

    async def capture(self, request: CaptureRequest) -> CaptureResult:
        return CaptureResult(
            success=True,
            image_bytes=b"P5\n1 1\n255\n\x80",
            image_suffix=".pgm",
            message="mock camera capture",
            actual_heading=request.yaw,
            actual_pitch=request.target_pitch,
        )

    async def cancel(self):
        return True
