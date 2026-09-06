from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
NAVIGATION_LAUNCH = ROOT / "src" / "agt_navigation" / "launch" / "navigation.launch.py"
OFFLINE_LAUNCH = ROOT / "src" / "agt_navigation" / "launch" / "offline_navigation.launch.py"
COMMISSIONING_LAUNCH = (
    ROOT / "src" / "agt_field_commissioning" / "launch" / "field_navigation.launch.py"
)


def test_production_navigation_declares_direct_goal_bridge_disabled_by_default():
    text = NAVIGATION_LAUNCH.read_text(encoding="utf-8")

    assert 'DeclareLaunchArgument("enable_rviz_goal_bridge", default_value="false")' in text
    assert 'executable="goal_pose_bridge.py"' in text
    assert 'condition=IfCondition(LaunchConfiguration("enable_rviz_goal_bridge"))' in text


def test_formal_waypoint_capability_remains_fail_closed_for_direct_pose_goals():
    text = NAVIGATION_LAUNCH.read_text(encoding="utf-8")

    assert (
        'DeclareLaunchArgument(\n'
        '                "capability_executable", default_value="navigation_capability_server.py"\n'
        '            )'
    ) in text
    assert 'executable=LaunchConfiguration("capability_executable")' in text
    assert '"allow_direct_pose_goals": False' in text

    capability_node = text.split(
        'executable=LaunchConfiguration("capability_executable")', 1
    )[1].split('executable="task_registry_node.py"', 1)[0]
    assert 'condition=IfCondition(LaunchConfiguration("enable_rviz_goal_bridge"))' not in capability_node


def test_offline_simulation_explicitly_keeps_direct_goal_bridge_enabled():
    text = OFFLINE_LAUNCH.read_text(encoding="utf-8")

    assert '"enable_rviz_goal_bridge": "true"' in text


def test_field_commissioning_can_explicitly_opt_in_but_defaults_off():
    text = COMMISSIONING_LAUNCH.read_text(encoding="utf-8")

    assert 'DeclareLaunchArgument("enable_rviz_goal_bridge", default_value="false")' in text
    assert '"enable_rviz_goal_bridge": LaunchConfiguration("enable_rviz_goal_bridge").perform(context)' in text


def test_field_commissioning_selects_capture_capability_without_changing_navigation_default():
    text = COMMISSIONING_LAUNCH.read_text(encoding="utf-8")

    assert '"capability_executable": "field_capture_capability_server.py"' in text


def test_commissioning_opt_in_does_not_create_a_second_direct_goal_bridge():
    text = COMMISSIONING_LAUNCH.read_text(encoding="utf-8")

    assert "goal_pose_bridge.py" not in text
    assert "navigate_to_pose" not in text
