from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def test_mock_publisher_and_launch_assets_exist() -> None:
    publisher = ROOT / 'scripts' / 'mock_robot_state_publisher.py'
    launch = ROOT / 'launch' / 'operator_gateway_mock.launch.py'
    assert publisher.is_file()
    assert launch.is_file()


def test_mock_publisher_uses_authoritative_robot_state_topic_and_latched_qos() -> None:
    source = (ROOT / 'scripts' / 'mock_robot_state_publisher.py').read_text()
    assert 'RobotState' in source
    assert '/agt/system/robot_state' in source
    assert 'ReliabilityPolicy.RELIABLE' in source
    assert 'DurabilityPolicy.TRANSIENT_LOCAL' in source
    assert 'create_publisher' in source
    assert 'create_subscription' not in source


def test_mock_publisher_contains_ready_map_localization_and_mission_evidence() -> None:
    source = (ROOT / 'scripts' / 'mock_robot_state_publisher.py').read_text()
    for token in (
        'MapVersionSummary.STATE_READY',
        'LocalizationStatus.STATE_TRACKING',
        'MissionStatus.STATE_RUNNING',
        'task_readiness.ready = True',
        'navigation_ready = True',
        'chassis_connected = True',
    ):
        assert token in source


def test_mock_launch_starts_only_mock_state_publisher_and_gateway() -> None:
    source = (ROOT / 'launch' / 'operator_gateway_mock.launch.py').read_text()
    assert "executable='mock_robot_state_publisher.py'" in source
    assert "executable='operator_gateway_node.py'" in source
    assert 'agt_navigation' not in source
    assert 'agt_chassis' not in source


def test_cmake_installs_mock_publisher_and_runs_mock_contract_test() -> None:
    cmake = (ROOT / 'CMakeLists.txt').read_text()
    assert 'scripts/mock_robot_state_publisher.py' in cmake
    assert 'test_mock_gateway_contract' in cmake
