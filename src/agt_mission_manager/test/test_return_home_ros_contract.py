from pathlib import Path


PACKAGE = Path(__file__).resolve().parents[1]
ROOT = PACKAGE.parents[1]


def _read(relative: str) -> str:
    return (PACKAGE / relative).read_text(encoding="utf-8")


def test_mission_status_and_action_expose_return_home_and_report_uri():
    status = (ROOT / "agt_interfaces" / "msg" / "MissionStatus.msg").read_text(encoding="utf-8")
    action = (ROOT / "agt_interfaces" / "action" / "ExecuteMission.action").read_text(encoding="utf-8")

    assert "STEP_RETURN_HOME=5" in status
    assert "string report_uri" in action


def test_return_home_runner_uses_formal_task_registry_fields_only():
    node = _read("scripts/mission_manager_node.py")
    start = node.index("class RosTaskGroupRunner:")
    end = node.index("class MissionManagerNode:")
    runner = node[start:end]

    assert '"/agt/navigation/execute_waypoint_task"' in node
    assert "goal.map_id = mission.map_binding.map_id" in runner
    assert "goal.map_version_id = mission.map_binding.map_version_id" in runner
    assert "goal.task_group_id = step.task_group_id" in runner
    assert "goal.task_revision = step.task_group_revision" in runner
    assert "goal.expected_content_sha256 = step.expected_content_sha256" in runner
    assert "goal.loop_count = 1" in runner
    assert "goal.client_request_id" in runner

    assert "goal.task_file" not in runner
    assert "goal.poses" not in runner
    assert "goal.loop =" not in runner
