from __future__ import annotations

import asyncio
import math
from pathlib import Path

from ..interfaces.camera import CaptureRequest, CaptureResult


class AutolaborC1Backend:
    """Adapter for the first hardware backend; vendor imports stay here."""

    def __init__(self, node, action_name="/camera_gimbal/acquire_view"):
        from camera_gimbal_interfaces.action import AcquireView
        from rclpy.action import ActionClient

        self._node = node
        self._action_type = AcquireView
        self._client = ActionClient(node, AcquireView, action_name)
        self._goal = None

    def ready(self):
        ready = self._client.wait_for_server(timeout_sec=0.1)
        return ready, "camera capability ready" if ready else "camera backend unavailable"

    async def capture(self, request: CaptureRequest) -> CaptureResult:
        if not self._client.wait_for_server(timeout_sec=2.0):
            return CaptureResult(False, message="camera backend unavailable", error_code=2)
        goal = self._action_type.Goal()
        goal.heading = math.degrees(request.yaw)
        goal.pitch = math.degrees(request.target_pitch)
        goal.roll = 0.0
        goal.tolerance = 3.0
        goal.timeout = 20.0
        goal.stable_samples = 2
        goal.settle_time = 0.5
        goal.image_timeout = 5.0
        goal.save_image = request.save_image
        goal.tag = request.capture_tag or request.request_id
        handle = await self._client.send_goal_async(goal)
        if not handle.accepted:
            return CaptureResult(False, message="camera backend rejected capture", error_code=3)
        self._goal = handle
        wrapped = await handle.get_result_async()
        self._goal = None
        result = wrapped.result
        if not result.success or int(result.error_code) != 0:
            return CaptureResult(False, message=str(result.message), error_code=3)
        image_uri = str(result.image_path)
        try:
            payload = Path(image_uri).read_bytes()
        except OSError as exc:
            return CaptureResult(False, message=f"camera image unavailable: {exc}", error_code=3)
        return CaptureResult(
            True, image_bytes=payload, image_uri=image_uri,
            image_suffix=Path(image_uri).suffix or ".img",
            message=str(result.message), actual_heading=math.radians(float(result.actual_heading)),
            actual_pitch=math.radians(float(result.actual_pitch)),
        )

    async def cancel(self):
        if self._goal is None:
            return True
        response = await self._goal.cancel_goal_async()
        self._goal = None
        return bool(response.goals_canceling)
