from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def read(relative: str) -> str:
    return (ROOT / relative).read_text(encoding="utf-8")


def test_run_adapter_uses_project_relocalize_action_only() -> None:
    source = read("agt_operator_gateway/run_ros_adapter.py")
    assert "from agt_interfaces.action import Relocalize" in source
    assert "from rclpy.action import ActionClient" in source
    assert "'/agt/localization/relocalize'" in source
    for forbidden in (
        "nav2_msgs",
        "NavigateToPose",
        "FollowPath",
        "/cmd_vel",
        "agt_chassis",
    ):
        assert forbidden not in source


def test_relocalize_request_is_explicit_bounded_auto_search() -> None:
    source = read("agt_operator_gateway/run_ros_adapter.py")
    for token in (
        "goal = Relocalize.Goal()",
        "goal.mode = Relocalize.Goal.MODE_AUTO_SEARCH",
        "goal.use_initial_pose = False",
        "goal.use_last_valid_pose = True",
        "goal.use_configured_candidates = True",
        "goal.use_external_coarse_pose = True",
        "goal.max_candidates = self._max_candidates",
        "goal.timeout_s = self._relocalize_timeout_s",
        "send_goal_async(goal)",
    ):
        assert token in source
    assert "MODE_SINGLE_INITIAL_POSE" not in source


def test_run_readiness_is_fail_closed_on_physical_auto_permit() -> None:
    source = read("agt_operator_gateway/run_ros_adapter.py")
    assert "self._robot_state_provider" in source
    assert "state = self._robot_state_provider()" in source
    assert "from std_msgs.msg import Bool" in source
    assert 'auto_permit_topic: str = "/agt/chassis/auto_permit"' in source
    assert "self._auto_permit_freshness_s" in source
    assert '"AUTO_PERMIT_NOT_READY"' in source
    assert '"AUTO_PERMIT_SOURCE_UNAVAILABLE"' not in source
    assert '"autoPermit": auto_permit' in source
    assert '"ready": not blockers' in source
    assert "self._lidar_component_id" in source
    assert "self._camera_gimbal_component_id" in source
    assert "component.component_id == component_id" in source
    assert "LocalizationStatus.STATE_TRACKING" in source
    assert "RobotState.NAV2_ACTIVE" in source
    assert "state.navigation_ready" in source
    assert "state.emergency_stop" in source
    assert "state.estop_latched" in source


def test_robot_state_adapter_retains_authoritative_raw_snapshot_for_run_gates() -> None:
    source = read("agt_operator_gateway/ros_adapter.py")
    assert "self._latest_robot_state" in source
    assert "self._robot_state_lock" in source
    assert "def latest_robot_state" in source
    assert "copy.deepcopy" in source
