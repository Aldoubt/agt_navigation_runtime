from __future__ import annotations

from pathlib import Path

PACKAGE_ROOT = Path(__file__).resolve().parents[1]
INTERFACE_ROOT = PACKAGE_ROOT.parent / 'agt_interfaces' / 'msg'


def _interface(name: str) -> str:
    path = INTERFACE_ROOT / f'{name}.msg'
    assert path.is_file(), f'missing authoritative interface: {path}'
    return path.read_text(encoding='utf-8')


def _assert_tokens(name: str, tokens: tuple[str, ...]) -> None:
    text = _interface(name)
    missing = [token for token in tokens if token not in text]
    assert not missing, f'{name}.msg missing gateway-required tokens: {missing}'


def test_robot_state_interface_contains_gateway_read_model_contract() -> None:
    _assert_tokens('RobotState', (
        'MODE_NAVIGATION',
        'NAV2_ACTIVE',
        'CHASSIS_MODE_CONTROL',
        'uint64 revision',
        'uint8 system_mode',
        'string active_profile',
        'bool system_health_known',
        'SystemHealth system_health',
        'bool task_readiness_known',
        'TaskReadiness task_readiness',
        'bool active_map_known',
        'MapVersionSummary active_map',
        'bool localization_status_known',
        'LocalizationStatus localization',
        'bool mission_status_known',
        'MissionStatus mission',
        'uint8 nav2_state',
        'bool safety_status_known',
        'bool safety_motion_enabled',
        'bool emergency_stop',
        'bool estop_latched',
        'bool navigation_ready',
        'bool chassis_status_known',
        'bool chassis_connected',
        'uint8 chassis_control_mode',
        'string[] blocker_codes',
        'string[] blocker_messages',
    ))


def test_nested_interfaces_contain_mock_and_projection_fields() -> None:
    _assert_tokens('SystemHealth', (
        'STATE_OK',
        'uint8 overall_state',
        'uint64 revision',
    ))
    _assert_tokens('TaskReadiness', (
        'bool ready',
        'string active_mode',
        'string map_id',
        'string map_version_id',
        'string localization_state',
        'string[] blocker_codes',
        'string[] warning_codes',
    ))
    _assert_tokens('MapVersionSummary', (
        'STATE_READY',
        'string map_id',
        'string map_version_id',
        'uint8 state',
        'bool active',
        'bool valid',
        'string map_hash',
        'string manifest_sha256',
    ))
    _assert_tokens('LocalizationStatus', (
        'STATE_TRACKING',
        'ERROR_NONE',
        'bool pose_valid',
        'bool localization_accepted',
        'bool has_converged',
        'string backend',
        'string map_id',
        'string map_hash',
        'geometry_msgs/PoseWithCovarianceStamped global_pose',
    ))
    _assert_tokens('MissionStatus', (
        'STATE_RUNNING',
        'string mission_id',
        'string mission_version',
        'string content_sha256',
        'string map_id',
        'string map_version_id',
        'uint32 current_step_index',
        'uint32 total_steps',
        'string current_step_id',
        'uint32 current_waypoint',
        'uint32 total_waypoints',
    ))


def test_gateway_package_declares_launch_and_transport_runtime_dependencies() -> None:
    package_xml = (PACKAGE_ROOT / 'package.xml').read_text(encoding='utf-8')
    for dependency in (
        'agt_interfaces',
        'ament_index_python',
        'launch',
        'launch_ros',
        'rclpy',
        'python3-aiohttp',
    ):
        assert f'<exec_depend>{dependency}</exec_depend>' in package_xml
