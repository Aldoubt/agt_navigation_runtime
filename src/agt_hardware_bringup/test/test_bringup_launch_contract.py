from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
LAUNCH = ROOT / "launch" / "bunker_mid360.launch.py"


def source() -> str:
    return LAUNCH.read_text(encoding="utf-8")


def test_unified_launch_defaults_to_monitor_mode():
    text = source()
    assert 'DeclareLaunchArgument("operation_mode", default_value="monitor"' in text


def test_unified_launch_composes_existing_runtime_owners():
    text = source()
    assert 'get_package_share_directory("agt_chassis_bunker")' in text
    assert 'get_package_share_directory("agt_sensor_adapters")' in text
    assert 'get_package_share_directory("agt_sensor_monitor")' in text
    assert '"bunker.launch.py"' in text
    assert '"mid360.launch.py"' in text
    assert '"sensor_monitor.launch.py"' in text


def test_unified_launch_exposes_only_known_sensor_profiles():
    text = source()
    assert 'choices=["hardware_check", "navigation"]' in text
    assert "sensor_monitor.hardware_check.yaml" in text
    assert "sensor_monitor.navigation.yaml" in text


def test_unified_launch_has_read_only_can_preflight_gate():
    text = source()
    assert 'DeclareLaunchArgument("run_can_preflight", default_value="true")' in text
    assert 'DeclareLaunchArgument("expected_can_bitrate", default_value="0")' in text
    assert "run_preflight" in text
    assert "SocketCAN preflight failed" in text
    assert "ip link set" not in text


def test_camera_and_gimbal_are_explicit_optional_external_hooks():
    text = source()
    assert 'DeclareLaunchArgument("start_camera", default_value="false")' in text
    assert 'DeclareLaunchArgument("camera_launch_file", default_value="")' in text
    assert 'DeclareLaunchArgument("start_gimbal", default_value="false")' in text
    assert 'DeclareLaunchArgument("gimbal_launch_file", default_value="")' in text
    assert "/agt/sensors/camera/image" not in text
    assert "/agt/gimbal/state" not in text


def test_new_launch_does_not_own_chassis_motion_topics():
    text = source()
    assert "/cmd_vel" not in text
    assert "NavigateToPose" not in text
    assert "FollowPath" not in text
