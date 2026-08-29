from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
VENDOR = ROOT / "third_party/autolabor_c1_camera_gimbal"


def test_frozen_camera_gimbal_vendor_snapshot_is_present():
    required = [
        VENDOR / "CAPABILITY_INTERFACE.md",
        VENDOR / "README.md",
        VENDOR / "src/camera_gimbal_interfaces/action/AcquireView.action",
        VENDOR / "src/camera_gimbal_capability/camera_gimbal_capability/capability_node.py",
        VENDOR / "src/pantilt_camera_serial/src/pantilt_serial_control.cpp",
    ]
    missing = [str(path.relative_to(ROOT)) for path in required if not path.is_file()]
    assert not missing, f"missing frozen camera-gimbal vendor files: {missing}"


def test_acquire_view_result_exposes_authoritative_observation_fields():
    action = (VENDOR / "src/camera_gimbal_interfaces/action/AcquireView.action").read_text(
        encoding="utf-8"
    )
    for fragment in (
        "uint16 ERROR_OK=0",
        "uint16 ERROR_CANCELED=400",
        "builtin_interfaces/Time reached_stamp",
        "builtin_interfaces/Time image_stamp",
        "float64 actual_heading",
        "float64 actual_roll",
        "float64 actual_pitch",
        "string image_path",
    ):
        assert fragment in action
