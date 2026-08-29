from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
HARDWARE = ROOT / "src/agt_hardware_bringup/launch/bunker_mid360.launch.py"
INSPECTION_LAUNCH = ROOT / "src/agt_inspection/launch/camera_gimbal_inspection.launch.py"
INSPECTION_PACKAGE = ROOT / "src/agt_inspection/package.xml"
HARDWARE_PACKAGE = ROOT / "src/agt_hardware_bringup/package.xml"


def test_hardware_bringup_keeps_inspection_disabled_by_default():
    source = HARDWARE.read_text(encoding="utf-8")
    assert 'DeclareLaunchArgument("start_inspection", default_value="false")' in source
    assert 'get_package_share_directory("agt_inspection")' in source
    assert 'LaunchConfiguration("start_inspection")' in source
    assert "camera_gimbal_inspection.launch.py" in source
    assert "start_inspection cannot be combined with start_camera/start_gimbal" in source


def test_inspection_launch_composes_frozen_vendor_and_runtime_server():
    source = INSPECTION_LAUNCH.read_text(encoding="utf-8")
    assert "autolabor_c1_bringup" in source
    assert "autolabor_c1.launch.py" in source
    assert "inspection_task_server.py" in source
    assert '"view_backend": "camera_gimbal"' in source
    assert 'DeclareLaunchArgument("camera_device_path"' in source
    assert 'DeclareLaunchArgument("camera_gimbal_port"' in source
    assert 'DeclareLaunchArgument("camera_width", default_value="1920")' in source
    assert 'DeclareLaunchArgument("camera_height", default_value="1080")' in source
    assert 'DeclareLaunchArgument("camera_fps", default_value="30.0")' in source
    assert '"gui": "false"' in source
    assert "capture_output_root" in source
    assert "evidence_root" in source
    assert "camera_calibration_id" in source
    assert "camera_calibration_sha256" in source


def test_package_dependencies_make_inspection_composition_explicit():
    inspection_package = INSPECTION_PACKAGE.read_text(encoding="utf-8")
    hardware_package = HARDWARE_PACKAGE.read_text(encoding="utf-8")
    assert "<depend>camera_gimbal_interfaces</depend>" in inspection_package
    assert "<exec_depend>autolabor_c1_bringup</exec_depend>" in inspection_package
    assert "<exec_depend>agt_inspection</exec_depend>" in hardware_package
