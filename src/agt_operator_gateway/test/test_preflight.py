from __future__ import annotations

from pathlib import Path

from agt_operator_gateway.preflight import (
    EXPECTED_API_VERSION,
    EXPECTED_ROBOT_STATE_TYPE,
    classify_write_probe_status,
    validate_gateway_payloads,
    validate_robot_state_topic_type,
)

ROOT = Path(__file__).resolve().parents[1]


def valid_payloads():
    health = {
        'apiVersion': EXPECTED_API_VERSION,
        'timestampMs': 1000,
        'gateway': {'state': 'OK', 'startedAtMs': 500},
        'runtime': {'connected': True, 'adapter': 'agt_system_manager'},
    }
    capabilities = {
        'apiVersion': EXPECTED_API_VERSION,
        'capabilities': {'localization': True, 'navigation': True},
    }
    robot = {
        'apiVersion': EXPECTED_API_VERSION,
        'snapshot': {'identity': {'id': 'agt-01'}},
        'navigation': {'robotPose': {'x': 1.0, 'y': 2.0, 'yawRad': 0.1}},
    }
    mission = {
        'apiVersion': EXPECTED_API_VERSION,
        'mission': {'id': '__none__'},
    }
    return health, capabilities, robot, mission


def test_topic_type_must_match_authoritative_robot_state() -> None:
    assert validate_robot_state_topic_type(EXPECTED_ROBOT_STATE_TYPE) == []
    assert validate_robot_state_topic_type('std_msgs/msg/String') == [
        'robot state topic type mismatch: expected agt_interfaces/msg/RobotState, got std_msgs/msg/String'
    ]


def test_valid_gateway_payloads_pass_preflight_contract() -> None:
    assert validate_gateway_payloads(*valid_payloads()) == []


def test_preflight_rejects_disconnected_or_incompatible_gateway() -> None:
    health, capabilities, robot, mission = valid_payloads()
    health['runtime']['connected'] = False
    robot['apiVersion'] = 'agt.operator.gateway/v0'
    errors = validate_gateway_payloads(health, capabilities, robot, mission)
    assert 'gateway runtime is not connected' in errors
    assert any('robot apiVersion mismatch' in error for error in errors)


def test_preflight_rejects_nonfinite_navigation_pose() -> None:
    health, capabilities, robot, mission = valid_payloads()
    robot['navigation']['robotPose']['x'] = float('nan')
    errors = validate_gateway_payloads(health, capabilities, robot, mission)
    assert 'navigation.robotPose.x must be finite' in errors


def test_write_probe_only_accepts_auth_gate_or_disabled_gate() -> None:
    assert classify_write_probe_status(401) == ('enabled_auth_required', [])
    assert classify_write_probe_status(403) == ('disabled', [])
    state, errors = classify_write_probe_status(202)
    assert state == 'unsafe_or_unexpected'
    assert errors == ['unauthenticated write probe returned unexpected HTTP 202']


def test_field_script_checks_ros_topic_all_reads_and_safe_write_surface() -> None:
    source = (ROOT / 'scripts' / 'operator_gateway_preflight.py').read_text()
    assert "'ros2', 'topic', 'type'" in source
    assert "'ros2', 'topic', 'echo'" in source
    for path in ('/api/v1/health', '/api/v1/capabilities', '/api/v1/robot', '/api/v1/mission'):
        assert path in source
    for path in (
        '/api/v1/mission/start',
        '/api/v1/mission/pause',
        '/api/v1/mission/resume',
        '/api/v1/mission/cancel',
    ):
        assert path in source
    assert '--expect-write-enabled' in source
    assert '--skip-write-probe' in source
    assert '--skip-ros' in source
    assert '--json-output' in source

    # The preflight must never accept or load command credentials: its POST
    # probe stays unauthenticated, so it can only hit the 401/403 guard before
    # any request parsing or ROS dispatch.
    assert '--command-token' not in source
    assert 'AGT_OPERATOR_COMMAND_TOKEN' not in source
