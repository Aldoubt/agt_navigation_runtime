import math

import pytest

from agt_inspection.camera_gimbal_adapter import (
    CameraGimbalResultError,
    make_acquire_view_goal,
    map_vendor_error_code,
    normalize_acquire_view_result,
)
from agt_inspection.execution import InspectionErrorCode


def test_runtime_radians_are_converted_once_to_vendor_degrees():
    goal = make_acquire_view_goal(
        pan_rad=-math.pi / 6,
        tilt_rad=-math.pi / 18,
        roll_rad=0.0,
        timeout_s=20.0,
        settle_time_s=0.5,
        tag="P001_center",
    )
    assert goal.heading_deg == pytest.approx(-30.0)
    assert goal.pitch_deg == pytest.approx(-10.0)
    assert goal.roll_deg == pytest.approx(0.0)
    assert goal.timeout_s == 20.0
    assert goal.settle_time_s == 0.5
    assert goal.save_image is True


@pytest.mark.parametrize(
    "vendor_code, runtime_code",
    [
        (0, InspectionErrorCode.NONE),
        (100, InspectionErrorCode.INVALID_TASK),
        (101, InspectionErrorCode.GIMBAL),
        (200, InspectionErrorCode.GIMBAL),
        (201, InspectionErrorCode.GIMBAL),
        (202, InspectionErrorCode.GIMBAL),
        (300, InspectionErrorCode.CAPTURE),
        (301, InspectionErrorCode.CAPTURE),
        (302, InspectionErrorCode.CAPTURE),
        (400, InspectionErrorCode.CANCELED),
        (900, InspectionErrorCode.INTERNAL),
        (65535, InspectionErrorCode.INTERNAL),
    ],
)
def test_vendor_error_codes_map_without_parsing_message(vendor_code, runtime_code):
    assert map_vendor_error_code(vendor_code) == runtime_code


def test_success_result_uses_actual_feedback_and_requires_post_settle_image():
    result = normalize_acquire_view_result(
        success=True,
        error_code=0,
        message="ignored for control",
        reached_stamp_s=100.25,
        image_stamp_s=100.40,
        actual_heading_deg=2.0,
        actual_roll_deg=-1.0,
        actual_pitch_deg=-9.5,
        image_path="/tmp/P001_center.jpg",
        tag="P001_center",
    )

    assert result.image_stamp_s > result.reached_stamp_s
    assert result.actual_pan_rad == pytest.approx(math.radians(2.0))
    assert result.actual_roll_rad == pytest.approx(math.radians(-1.0))
    assert result.actual_tilt_rad == pytest.approx(math.radians(-9.5))
    assert result.image_uri == "/tmp/P001_center.jpg"
    assert result.tag == "P001_center"


def test_success_result_rejects_stale_or_pre_reached_image():
    with pytest.raises(CameraGimbalResultError, match="image_stamp"):
        normalize_acquire_view_result(
            success=True,
            error_code=0,
            message="",
            reached_stamp_s=100.25,
            image_stamp_s=100.25,
            actual_heading_deg=0.0,
            actual_roll_deg=0.0,
            actual_pitch_deg=0.0,
            image_path="/tmp/image.jpg",
            tag="P001_center",
        )


def test_failed_vendor_result_cannot_be_normalized_as_success():
    with pytest.raises(CameraGimbalResultError, match="vendor acquire failed"):
        normalize_acquire_view_result(
            success=False,
            error_code=301,
            message="timeout text is diagnostic only",
            reached_stamp_s=100.25,
            image_stamp_s=0.0,
            actual_heading_deg=0.0,
            actual_roll_deg=0.0,
            actual_pitch_deg=0.0,
            image_path="",
            tag="P001_center",
        )
