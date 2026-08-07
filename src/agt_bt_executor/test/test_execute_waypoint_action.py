from pathlib import Path

ROOT = Path(__file__).parents[1]
SOURCE = (ROOT / "src/execute_waypoint_task_action.cpp").read_text()
HEADER = (ROOT / "include/agt_bt_executor/execute_waypoint_task_action.hpp").read_text()
ACTION = (ROOT.parent / "agt_interfaces/action/ExecuteWaypointTask.action").read_text()


def test_uses_formal_project_waypoint_action_and_typed_ports():
    assert "agt_interfaces/action/execute_waypoint_task.hpp" in HEADER
    assert '"/agt/navigation/execute_waypoint_task"' in SOURCE
    for port in ("map_id", "map_version_id", "task_group_id", "task_revision",
                 "expected_content_sha256", "loop_count", "client_request_id"):
        assert f'"{port}"' in SOURCE


def test_deprecated_goal_inputs_are_not_populated():
    assert "task_file" in ACTION and "poses" in ACTION and "bool loop" in ACTION
    goal_builder = SOURCE.split("bool ExecuteWaypointTask::makeGoal", 1)[1]
    assert "task_file" not in goal_builder
    assert "poses" not in goal_builder
    assert "goal.loop =" not in goal_builder
