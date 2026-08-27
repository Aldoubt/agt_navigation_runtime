from pathlib import Path


PACKAGE = Path(__file__).resolve().parents[1]


def _read(relative: str) -> str:
    return (PACKAGE / relative).read_text(encoding="utf-8")


def test_inspection_interfaces_are_registered_with_sensor_msgs_dependency():
    cmake = _read("CMakeLists.txt")
    package = _read("package.xml")

    for path in (
        "msg/InspectionStatus.msg",
        "action/ExecuteInspectionTask.action",
        "action/MoveGimbal.action",
        "action/InspectImage.action",
        "srv/CaptureImage.srv",
    ):
        assert f'"{path}"' in cmake

    assert "find_package(sensor_msgs REQUIRED)" in cmake
    assert "sensor_msgs" in cmake.split("DEPENDENCIES", 1)[1]
    assert "<depend>sensor_msgs</depend>" in package


def test_capture_and_vision_interfaces_transport_one_captured_image():
    capture = _read("srv/CaptureImage.srv")
    vision = _read("action/InspectImage.action")

    assert "string request_id" in capture
    assert "string camera_id" in capture
    assert "sensor_msgs/Image image" in capture
    assert "string image_uri" in capture

    assert "string request_id" in vision
    assert "string task_id" in vision
    assert "string model_profile" in vision
    assert "string camera_id" in vision
    assert "sensor_msgs/Image image" in vision
    assert "string metadata_json" in vision
    assert "string model_id" in vision
    assert "string model_version" in vision
    assert "float64 inference_time_ms" in vision
    assert "float64 primary_confidence" in vision
    assert "string result_json" in vision
    assert "float32 progress" in vision


def test_inspection_task_action_has_map_bound_revisioned_goal_and_stage_feedback():
    action = _read("action/ExecuteInspectionTask.action")
    status = _read("msg/InspectionStatus.msg")

    for token in (
        "string map_id",
        "string map_version_id",
        "string inspection_task_id",
        "uint32 task_revision",
        "string expected_content_sha256",
        "string client_request_id",
        "string session_id",
        "string evidence_root_uri",
        "uint32 current_point",
        "uint32 total_points",
        "string point_id",
        "string stage",
        "agt_interfaces/InspectionStatus final_status",
        "agt_interfaces/InspectionStatus status",
    ):
        assert token in action

    for token in (
        "uint8 STATE_VALIDATING=1",
        "uint8 STATE_RUNNING=2",
        "uint8 STATE_CANCELING=3",
        "uint8 STATE_SUCCEEDED=4",
        "uint8 STATE_FAILED=5",
        "uint8 STATE_CANCELED=6",
        "uint16 ERROR_MAP_MISMATCH=2",
        "uint16 ERROR_NOT_STATIONARY=4",
        "uint16 ERROR_INFERENCE=7",
    ):
        assert token in status


def test_gimbal_action_is_orientation_only_and_bounded():
    action = _read("action/MoveGimbal.action")
    for token in (
        "string request_id",
        "float64 pan_rad",
        "float64 tilt_rad",
        "float64 timeout_s",
        "float64 final_pan_rad",
        "float64 final_tilt_rad",
        "float64 current_pan_rad",
        "float64 current_tilt_rad",
        "uint16 ERROR_TIMEOUT=2",
        "uint16 ERROR_HARDWARE=3",
        "uint16 ERROR_CANCELED=4",
    ):
        assert token in action
