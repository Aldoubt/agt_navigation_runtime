from __future__ import annotations

import asyncio
from pathlib import Path

from action_msgs.msg import GoalStatus
from camera_gimbal_interfaces.action import AcquireView
from rclpy.action import ActionClient
from rclpy.callback_groups import ReentrantCallbackGroup

from .camera_gimbal_adapter import (
    CameraGimbalResultError,
    make_acquire_view_goal,
    map_vendor_error_code,
    normalize_acquire_view_result,
)
from .execution import CaptureResult, InspectionErrorCode
from .multiview_execution import ViewAcquireResult


async def _wait_future(future, poll_s: float = 0.01):
    while not future.done():
        await asyncio.sleep(poll_s)
    exception = future.exception()
    if exception is not None:
        raise exception
    return future.result()


def _stamp_seconds(stamp) -> float:
    return float(stamp.sec) + float(stamp.nanosec) * 1.0e-9


class RosCameraGimbalAcquireRunner:
    """ROS binding for the frozen atomic camera-gimbal AcquireView capability."""

    def __init__(self, node, *, action_name: str = "/camera_gimbal/acquire_view") -> None:
        self._client = ActionClient(
            node,
            AcquireView,
            action_name,
            callback_group=ReentrantCallbackGroup(),
        )
        self._goal_handle = None
        self._capture_stamps = {}
        self._last_feedback: tuple[float, float, float] | None = None

    async def acquire(self, point, view, request_id: str) -> ViewAcquireResult:
        self._last_feedback = None
        self._capture_stamps.pop(request_id, None)
        if not self._client.wait_for_server(timeout_sec=2.0):
            return ViewAcquireResult(
                False,
                error_code=int(InspectionErrorCode.GIMBAL),
                message="camera-gimbal AcquireView action unavailable",
            )

        spec = make_acquire_view_goal(
            pan_rad=view.gimbal.pan_rad,
            tilt_rad=view.gimbal.tilt_rad,
            roll_rad=0.0,
            timeout_s=max(float(view.gimbal.timeout_s), 0.1),
            settle_time_s=max(float(view.gimbal.settle_duration_s), 0.0),
            tag=request_id,
        )
        goal = AcquireView.Goal()
        goal.heading = spec.heading_deg
        goal.roll = spec.roll_deg
        goal.pitch = spec.pitch_deg
        goal.tolerance = spec.tolerance_deg
        goal.timeout = spec.timeout_s
        goal.stable_samples = spec.stable_samples
        goal.settle_time = spec.settle_time_s
        goal.image_timeout = spec.image_timeout_s
        goal.save_image = spec.save_image
        goal.tag = spec.tag

        handle = await _wait_future(self._client.send_goal_async(goal))
        if handle is None or not handle.accepted:
            return ViewAcquireResult(
                False,
                error_code=int(InspectionErrorCode.GIMBAL),
                message="camera-gimbal AcquireView goal rejected",
            )
        self._goal_handle = handle
        try:
            wrapped = await _wait_future(handle.get_result_async())
        finally:
            self._goal_handle = None

        result = wrapped.result
        canceled = (
            int(wrapped.status) == int(GoalStatus.STATUS_CANCELED)
            or int(result.error_code) == 400
        )
        if not bool(result.success) or int(result.error_code) != 0:
            return ViewAcquireResult(
                False,
                error_code=int(map_vendor_error_code(int(result.error_code))),
                message=str(result.message),
                canceled=canceled,
                cancel_confirmed=canceled,
            )

        try:
            normalized = normalize_acquire_view_result(
                success=bool(result.success),
                error_code=int(result.error_code),
                message=str(result.message),
                reached_stamp_s=_stamp_seconds(result.reached_stamp),
                image_stamp_s=_stamp_seconds(result.image_stamp),
                actual_heading_deg=float(result.actual_heading),
                actual_roll_deg=float(result.actual_roll),
                actual_pitch_deg=float(result.actual_pitch),
                image_path=str(result.image_path),
                tag=str(result.tag),
            )
            image_path = Path(normalized.image_uri).expanduser()
            image_bytes = image_path.read_bytes()
        except (CameraGimbalResultError, OSError) as exc:
            return ViewAcquireResult(
                False,
                error_code=int(InspectionErrorCode.CAPTURE),
                message=f"camera-gimbal evidence unavailable: {exc}",
            )

        self._capture_stamps[request_id] = result.image_stamp
        self._last_feedback = (
            normalized.actual_pan_rad,
            normalized.actual_tilt_rad,
            normalized.actual_roll_rad,
        )
        suffix = image_path.suffix.lower() or ".jpg"
        return ViewAcquireResult(
            True,
            capture=CaptureResult(
                True,
                image_bytes=image_bytes,
                image_uri=normalized.image_uri,
                image_suffix=suffix,
            ),
        )

    def capture_stamp(self, request_id: str):
        return self._capture_stamps.pop(request_id, None)

    def last_feedback(self) -> tuple[float, float, float] | None:
        return self._last_feedback

    async def cancel(self) -> bool:
        handle = self._goal_handle
        if handle is None:
            return True
        response = await _wait_future(handle.cancel_goal_async())
        return bool(response.goals_canceling)
