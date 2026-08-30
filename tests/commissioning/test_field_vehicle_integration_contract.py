from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
FIELD_NAV = ROOT / "src" / "agt_field_commissioning" / "launch" / "field_navigation.launch.py"
HARDWARE = ROOT / "src" / "agt_hardware_bringup" / "launch" / "bunker_mid360.launch.py"
BUNKER_LAUNCH = ROOT / "src" / "agt_chassis_bunker" / "launch" / "bunker.launch.py"
AUTO_PERMIT = ROOT / "src" / "agt_chassis_bunker" / "scripts" / "bunker_rc_auto_permit.py"
SAFETY = ROOT / "src" / "agt_safety" / "scripts" / "safety_controller.py"
RUN_ADAPTER = ROOT / "src" / "agt_operator_gateway" / "agt_operator_gateway" / "run_ros_adapter.py"


def text(path: Path) -> str:
    return path.read_text(encoding="utf-8")


def test_field_navigation_has_single_safety_owner_and_forwards_inspection_hardware() -> None:
    source = text(FIELD_NAV)
    assert '"start_safety": "false"' in source
    assert '"start_inspection": LaunchConfiguration("start_inspection").perform(context)' in source
    for token in (
        '"inspection_camera_device_path": LaunchConfiguration("inspection_camera_device_path").perform(context)',
        '"inspection_camera_gimbal_port": LaunchConfiguration("inspection_camera_gimbal_port").perform(context)',
        '"inspection_camera_calibration_id": LaunchConfiguration("inspection_camera_calibration_id").perform(context)',
        '"inspection_camera_calibration_sha256": LaunchConfiguration("inspection_camera_calibration_sha256").perform(context)',
        'DeclareLaunchArgument("start_inspection", default_value="true")',
    ):
        assert token in source


def test_hardware_bringup_can_delegate_safety_ownership_to_field_navigation() -> None:
    source = text(HARDWARE)
    assert 'DeclareLaunchArgument("start_safety", default_value="true")' in source
    assert '"start_safety": LaunchConfiguration("start_safety").perform(context)' in source


def test_bunker_launch_exposes_fail_closed_rc_auto_permit_adapter() -> None:
    source = text(BUNKER_LAUNCH)
    assert 'DeclareLaunchArgument("start_auto_permit", default_value="false")' in source
    assert 'executable="bunker_rc_auto_permit.py"' in source
    assert '"switch_name": LaunchConfiguration("auto_permit_switch")' in source
    assert '"enabled_value": LaunchConfiguration("auto_permit_enabled_value")' in source
    assert '"input_topic": "/agt/chassis/rc_state"' in source
    assert '"output_topic": "/agt/chassis/auto_permit"' in source


def test_rc_auto_permit_adapter_requires_explicit_switch_mapping_and_fresh_input() -> None:
    source = text(AUTO_PERMIT)
    assert "BunkerRCState" in source
    assert '"switch_name", ""' in source
    assert '"enabled_value", -1' in source
    assert '"status_timeout", 0.5' in source
    assert "switch_name must be one of" in source
    assert "enabled_value must be configured explicitly" in source
    assert '"/agt/chassis/auto_permit"' in source
    assert "Bool(data=permit)" in source


def test_safety_navigation_path_requires_fresh_auto_permit_when_enabled() -> None:
    source = text(SAFETY)
    for token in (
        '"require_auto_permit", False',
        '"auto_permit_timeout", 0.5',
        '"/agt/chassis/auto_permit"',
        '"auto_permit_unavailable"',
        'key="auto_permit_ready"',
        'key="auto_permit_required"',
    ):
        assert token in source


def test_run_readiness_consumes_real_auto_permit_instead_of_hard_coding_false() -> None:
    source = text(RUN_ADAPTER)
    assert "from std_msgs.msg import Bool" in source
    assert '"/agt/chassis/auto_permit"' in source
    assert "self._auto_permit" in source
    assert "self._auto_permit_stamp" in source
    assert "self._auto_permit_freshness_s" in source
    assert '"AUTO_PERMIT_NOT_READY"' in source
    assert '"AUTO_PERMIT_SOURCE_UNAVAILABLE"' not in source
    assert '"autoPermit": auto_permit' in source
    assert '"ready": not blockers' in source
