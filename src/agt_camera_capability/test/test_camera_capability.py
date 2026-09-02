import asyncio

from agt_camera_capability.backend.mock_camera_backend import MockCameraBackend
from agt_camera_capability.interfaces.camera import CaptureRequest


def test_capture_request_carries_waypoint_orientation_and_tag():
    request = CaptureRequest(
        request_id="run-P01",
        waypoint_id="P01",
        target_heading=-0.5,
        target_pitch=0.2,
        capture_tag="row_01_left",
        save_image=True,
    )
    assert request.waypoint_id == "P01"
    assert request.target_heading == -0.5
    assert request.target_pitch == 0.2
    assert request.capture_tag == "row_01_left"


def test_capture_request_strategy_fields_are_backward_compatible():
    request = CaptureRequest(
        "run-P01", "P01", target_heading=0.2, target_pitch=0.3,
        view_name="overview", target_yaw=0.4, target_roll=0.1,
    )
    assert request.view_name == "overview"
    assert request.yaw == 0.4
    assert request.target_pitch == 0.3
    assert request.target_roll == 0.1


def test_mock_backend_returns_image_and_actual_angles():
    request = CaptureRequest("r1", "P01", target_heading=-0.5, target_pitch=0.2)
    result = asyncio.run(MockCameraBackend().capture(request))
    assert result.success
    assert result.image_bytes.startswith(b"P5")
    assert result.actual_heading == -0.5
    assert result.actual_pitch == 0.2


def test_mock_backend_receives_strategy_view_angles():
    request = CaptureRequest(
        "r2", "P01", target_heading=0.0, target_pitch=0.7853981633974483,
        view_name="overview", target_yaw=0.4, target_roll=0.0,
    )
    result = asyncio.run(MockCameraBackend().capture(request))
    assert result.actual_heading == 0.4
    assert result.actual_pitch == 0.7853981633974483
