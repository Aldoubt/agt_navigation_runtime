from __future__ import annotations

from dataclasses import dataclass
import math

from .execution import InspectionErrorCode


class CameraGimbalResultError(ValueError):
    """Raised when a vendor AcquireView result cannot be trusted as evidence."""


@dataclass(frozen=True)
class AcquireViewGoalSpec:
    heading_deg: float
    roll_deg: float
    pitch_deg: float
    tolerance_deg: float
    timeout_s: float
    stable_samples: int
    settle_time_s: float
    image_timeout_s: float
    save_image: bool
    tag: str


@dataclass(frozen=True)
class NormalizedAcquireViewResult:
    image_uri: str
    reached_stamp_s: float
    image_stamp_s: float
    actual_pan_rad: float
    actual_roll_rad: float
    actual_tilt_rad: float
    tag: str


def _finite(value: float, name: str) -> float:
    result = float(value)
    if not math.isfinite(result):
        raise ValueError(f"{name} must be finite")
    return result


def make_acquire_view_goal(
    *,
    pan_rad: float,
    tilt_rad: float,
    roll_rad: float = 0.0,
    timeout_s: float = 20.0,
    settle_time_s: float = 0.5,
    tolerance_deg: float = 3.0,
    stable_samples: int = 2,
    image_timeout_s: float = 5.0,
    save_image: bool = True,
    tag: str = "",
) -> AcquireViewGoalSpec:
    pan = _finite(pan_rad, "pan_rad")
    tilt = _finite(tilt_rad, "tilt_rad")
    roll = _finite(roll_rad, "roll_rad")
    timeout = _finite(timeout_s, "timeout_s")
    settle = _finite(settle_time_s, "settle_time_s")
    tolerance = _finite(tolerance_deg, "tolerance_deg")
    image_timeout = _finite(image_timeout_s, "image_timeout_s")
    if timeout <= 0.0:
        raise ValueError("timeout_s must be positive")
    if settle < 0.0:
        raise ValueError("settle_time_s must be non-negative")
    if tolerance <= 0.0:
        raise ValueError("tolerance_deg must be positive")
    if image_timeout <= 0.0:
        raise ValueError("image_timeout_s must be positive")
    if isinstance(stable_samples, bool) or not isinstance(stable_samples, int) or stable_samples <= 0:
        raise ValueError("stable_samples must be a positive integer")
    if not isinstance(tag, str):
        raise ValueError("tag must be a string")
    return AcquireViewGoalSpec(
        heading_deg=math.degrees(pan),
        roll_deg=math.degrees(roll),
        pitch_deg=math.degrees(tilt),
        tolerance_deg=tolerance,
        timeout_s=timeout,
        stable_samples=stable_samples,
        settle_time_s=settle,
        image_timeout_s=image_timeout,
        save_image=bool(save_image),
        tag=tag,
    )


def map_vendor_error_code(error_code: int) -> InspectionErrorCode:
    code = int(error_code)
    mapping = {
        0: InspectionErrorCode.NONE,
        100: InspectionErrorCode.INVALID_TASK,
        101: InspectionErrorCode.GIMBAL,
        200: InspectionErrorCode.GIMBAL,
        201: InspectionErrorCode.GIMBAL,
        202: InspectionErrorCode.GIMBAL,
        300: InspectionErrorCode.CAPTURE,
        301: InspectionErrorCode.CAPTURE,
        302: InspectionErrorCode.CAPTURE,
        400: InspectionErrorCode.CANCELED,
        900: InspectionErrorCode.INTERNAL,
    }
    return mapping.get(code, InspectionErrorCode.INTERNAL)


def normalize_acquire_view_result(
    *,
    success: bool,
    error_code: int,
    message: str,
    reached_stamp_s: float,
    image_stamp_s: float,
    actual_heading_deg: float,
    actual_roll_deg: float,
    actual_pitch_deg: float,
    image_path: str,
    tag: str,
) -> NormalizedAcquireViewResult:
    code = int(error_code)
    if not success or code != 0:
        runtime_code = map_vendor_error_code(code)
        raise CameraGimbalResultError(
            f"vendor acquire failed: error_code={code}, runtime_error={int(runtime_code)}"
        )

    reached = _finite(reached_stamp_s, "reached_stamp_s")
    image = _finite(image_stamp_s, "image_stamp_s")
    if image <= reached:
        raise CameraGimbalResultError(
            f"image_stamp must be newer than reached_stamp: image_stamp={image}, reached_stamp={reached}"
        )
    if not isinstance(image_path, str) or not image_path:
        raise CameraGimbalResultError("successful saved acquisition requires non-empty image_path")
    if not isinstance(tag, str):
        raise CameraGimbalResultError("tag must be a string")

    heading = _finite(actual_heading_deg, "actual_heading_deg")
    roll = _finite(actual_roll_deg, "actual_roll_deg")
    pitch = _finite(actual_pitch_deg, "actual_pitch_deg")
    return NormalizedAcquireViewResult(
        image_uri=image_path,
        reached_stamp_s=reached,
        image_stamp_s=image,
        actual_pan_rad=math.radians(heading),
        actual_roll_rad=math.radians(roll),
        actual_tilt_rad=math.radians(pitch),
        tag=tag,
    )
