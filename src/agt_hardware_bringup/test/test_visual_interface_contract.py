from pathlib import Path

import yaml


ROOT = Path(__file__).resolve().parents[1]
CONTRACT = ROOT / "config" / "visual_interface_contract.yaml"


def load_contract():
    return yaml.safe_load(CONTRACT.read_text(encoding="utf-8"))


def test_camera_contract_preserves_known_legacy_source_and_runtime_target():
    data = load_contract()
    camera = data["camera"]
    assert camera["integration_status"] == "pending_driver_delivery"
    assert camera["legacy_ros_generation"] == "ros1"
    assert camera["source_image_topic"] == "/cv_camera0/image_raw"
    assert camera["target_image_topic"] == "/agt/sensors/camera/image"
    assert camera["target_camera_info_topic"] == "/agt/sensors/camera/camera_info"
    assert camera["source_camera_info_topic"] == "UNVERIFIED"
    assert camera["device"] == "UNVERIFIED"


def test_gimbal_contract_preserves_known_feedback_and_marks_control_unknown():
    data = load_contract()
    gimbal = data["gimbal"]
    assert gimbal["integration_status"] == "pending_driver_delivery"
    assert gimbal["legacy_ros_generation"] == "ros1"
    assert gimbal["source_feedback_topic"] == "/pantilt_camera_serial0/pantilt_angle_info"
    assert gimbal["source_feedback_fields"] == ["heading", "roll", "pitch"]
    assert gimbal["target_state_topic"] == "/agt/gimbal/state"
    assert gimbal["control_interface"] == "UNVERIFIED"
    assert gimbal["serial_device"] == "UNVERIFIED"
    assert gimbal["baudrate"] == "UNVERIFIED"
    assert gimbal["angle_unit"] == "UNVERIFIED"
    assert gimbal["limits"] == "UNVERIFIED"
    assert gimbal["settle_tolerance"] == "UNVERIFIED"
    assert gimbal["settle_time"] == "UNVERIFIED"
