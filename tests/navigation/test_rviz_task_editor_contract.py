from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
EDITOR = ROOT / "src" / "agt_navigation" / "scripts" / "rviz_task_editor.py"
CMAKE = ROOT / "src" / "agt_navigation" / "CMakeLists.txt"
PACKAGE = ROOT / "src" / "agt_navigation" / "package.xml"
FIELD_LAUNCH = ROOT / "src" / "agt_field_commissioning" / "launch" / "field_navigation.launch.py"
FIELD_RVIZ = ROOT / "src" / "agt_field_commissioning" / "rviz" / "field_navigation.rviz"


def test_field_rviz_clicks_edit_draft_instead_of_sending_direct_nav2_goal():
    text = FIELD_RVIZ.read_text(encoding="utf-8")

    assert "Topic: /agt/rviz/task_point" in text
    assert "Topic: /goal_pose" not in text
    assert "rviz_default_plugins/MarkerArray" in text
    assert "Value: /agt/navigation/task_markers" in text


def test_editor_is_a_thin_registry_and_formal_action_adapter():
    assert EDITOR.is_file()
    text = EDITOR.read_text(encoding="utf-8")

    for expected in (
        "RvizTaskDraft",
        "GetTaskGroup",
        "PutTaskGroup",
        "ExecuteWaypointTask",
        '"/agt/rviz/task_point"',
        '"/agt/navigation/task_markers"',
        '"/agt/navigation/waypoint_preview_request"',
        '"/agt/navigation/tasks/get"',
        '"/agt/navigation/tasks/put"',
        '"/agt/navigation/execute_waypoint_task"',
    ):
        assert expected in text

    assert "NavigateToPose" not in text
    assert '"/goal_pose"' not in text


def test_editor_exposes_only_small_explicit_acceptance_commands():
    text = EDITOR.read_text(encoding="utf-8")

    for service in (
        "/agt/rviz/task/undo",
        "/agt/rviz/task/clear",
        "/agt/rviz/task/preview",
        "/agt/rviz/task/save",
        "/agt/rviz/task/load",
        "/agt/rviz/task/start",
    ):
        assert service in text
    assert "std_srvs.srv import Trigger" in text
    assert "execution_ref()" in text


def test_field_navigation_starts_editor_but_keeps_human_start_explicit():
    text = FIELD_LAUNCH.read_text(encoding="utf-8")

    assert 'executable="rviz_task_editor.py"' in text
    assert 'DeclareLaunchArgument("start_rviz_task_editor", default_value="true")' in text
    assert 'DeclareLaunchArgument("rviz_task_group_id", default_value="field_inspection")' in text
    assert '"map_id": assets.site_id' in text
    assert '"map_version_id": assets.site_revision' in text
    assert '"task_group_id": LaunchConfiguration("rviz_task_group_id").perform(context)' in text
    # Launching the editor must never imply task execution.
    assert "auto_start" not in text


def test_editor_is_installed_with_only_required_ros_message_dependencies():
    cmake = CMAKE.read_text(encoding="utf-8")
    package = PACKAGE.read_text(encoding="utf-8")

    assert "rviz_task_editor.py" in cmake
    assert "<exec_depend>std_srvs</exec_depend>" in package
    assert "<exec_depend>visualization_msgs</exec_depend>" in package
