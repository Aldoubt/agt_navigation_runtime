from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RUNTIME_SRC = ROOT.parent


def read(relative: str) -> str:
    return (ROOT / relative).read_text(encoding='utf-8')


def test_mission_ros_adapter_uses_only_project_mission_interfaces() -> None:
    source = read('agt_operator_gateway/mission_ros_adapter.py')
    assert 'from action_msgs.srv import CancelGoal' in source
    assert 'from agt_interfaces.action import ExecuteMission' in source
    assert 'from agt_interfaces.srv import SetMissionRunState' in source
    assert 'from rclpy.action import ActionClient' in source
    assert "'/agt/missions/execute'" in source
    assert "'/agt/missions/set_run_state'" in source
    assert "'/agt/missions/execute/_action/cancel_goal'" in source

    forbidden = (
        'nav2_msgs',
        'NavigateToPose',
        'FollowPath',
        '/cmd_vel',
        'agt_chassis',
        '/agt/chassis',
    )
    for token in forbidden:
        assert token not in source


def test_start_builds_exact_execute_mission_goal_without_waiting_for_completion() -> None:
    source = read('agt_operator_gateway/mission_ros_adapter.py')
    for token in (
        'ExecuteMission.Goal()',
        'goal.mission_id = mission_id',
        'goal.mission_version = mission_version',
        'goal.expected_content_sha256 = expected_hash',
        'send_goal_async(goal)',
    ):
        assert token in source
    assert 'get_result_async' not in source


def test_pause_resume_use_set_run_state_constants_and_requested_mission_id() -> None:
    source = read('agt_operator_gateway/mission_ros_adapter.py')
    assert 'SetMissionRunState.Request()' in source
    assert 'SetMissionRunState.Request.COMMAND_PAUSE' in source
    assert 'SetMissionRunState.Request.COMMAND_RESUME' in source
    assert 'request.mission_id = mission_id' in source


def test_cancel_is_restart_safe_cancel_all_not_retained_goal_handle_cancel() -> None:
    source = read('agt_operator_gateway/mission_ros_adapter.py')
    assert 'CancelGoal.Request()' in source
    assert 'cancel_request.goal_info.goal_id.uuid' not in source
    assert 'cancel_request.goal_info.stamp' not in source
    assert 'cancel_goal_async' not in source
    assert 'goals_canceling' in source
    assert 'CancelGoal.Response.ERROR_NONE' in source


def test_every_ros_wait_is_finite_and_adapter_exposes_no_background_motion_loop() -> None:
    source = read('agt_operator_gateway/mission_ros_adapter.py')
    assert 'wait_for_server(timeout_sec=self._timeout_s)' in source
    assert source.count('wait_for_service(timeout_sec=self._timeout_s)') >= 2
    assert 'event.wait(self._timeout_s)' in source
    assert 'while True' not in source


def test_gateway_pins_current_mission_manager_single_active_goal_contract() -> None:
    manager = (
        RUNTIME_SRC / 'agt_mission_manager' / 'scripts' / 'mission_manager_node.py'
    ).read_text(encoding='utf-8')
    assert 'self._active = False' in manager
    assert 'if self._active:' in manager
    assert 'return GoalResponse.REJECT' in manager
    assert 'self._active = True' in manager


def test_node_only_enables_write_ros_clients_with_explicit_flag_and_secret() -> None:
    script = read('scripts/operator_gateway_node.py')
    config = read('config/operator_gateway.yaml')
    package = read('package.xml')

    assert 'AGT_OPERATOR_COMMAND_TOKEN' in script
    assert 'MissionCommandAdapter' in script
    assert 'node.write_api_enabled' in script
    assert 'mission_commands = None' in script
    assert 'if node.write_api_enabled:' in script
    assert 'command_token' in script
    assert 'write_api_enabled: false' in config
    assert 'mission_command_timeout_s:' in config
    assert '<exec_depend>action_msgs</exec_depend>' in package


def test_ros_read_adapter_exposes_write_enable_and_timeout_parameters_only_as_config() -> None:
    adapter = read('agt_operator_gateway/ros_adapter.py')
    assert "'write_api_enabled'" in adapter
    assert "'mission_command_timeout_s'" in adapter
    assert 'def write_api_enabled' in adapter
    assert 'def mission_command_timeout_s' in adapter
    assert 'ActionClient(' not in adapter
    assert 'create_client(' not in adapter
