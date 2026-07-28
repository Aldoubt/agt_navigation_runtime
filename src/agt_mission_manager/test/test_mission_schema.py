import copy

import pytest

from agt_mission_manager.mission_model import MissionError, StepType
from agt_mission_manager.mission_schema import canonical_hash, parse_mission


def mission_document():
    value = {
        "schema_version": 1,
        "mission_id": "greenhouse_demo_01",
        "mission_version": "v1",
        "map_binding": {
            "map_id": "greenhouse_a",
            "map_version_id": "v12",
            "manifest_sha256": "sha256:" + "a" * 64,
        },
        "steps": [
            {"id": "navigate", "type": "WAYPOINT_TASK", "task_file": "tasks/route.json"},
            {"id": "wait", "type": "WAIT_DURATION", "duration_s": 30},
            {
                "id": "arm",
                "type": "WAIT_EVENT",
                "event_type": "manipulator.task_finished",
                "event_source": "arm_controller",
                "correlation_id": "operation-42",
                "timeout_s": 300,
            },
        ],
    }
    value["content_sha256"] = canonical_hash(value)
    return value


def test_schema_parses_three_finite_step_types():
    mission = parse_mission(mission_document())
    assert [step.type for step in mission.steps] == [
        StepType.WAYPOINT_TASK, StepType.WAIT_DURATION, StepType.WAIT_EVENT
    ]


@pytest.mark.parametrize(
    "mutation, expected",
    [
        (lambda value: value["steps"].__setitem__(1, {"id": "wait", "type": "WAIT_DURATION", "duration_s": 0}), "duration_s"),
        (lambda value: value["steps"].__setitem__(0, {"id": "navigate", "type": "WAYPOINT_TASK", "task_file": "../route.json"}), "task_file"),
        (lambda value: value["steps"].append({"id": "wait", "type": "WAIT_DURATION", "duration_s": 1}), "duplicate step id"),
        (lambda value: value["steps"].append({"id": "shell", "type": "SHELL", "command": "true"}), "unsupported type"),
        (lambda value: value["steps"].__setitem__(2, {"id": "arm", "type": "WAIT_EVENT", "event_type": "event", "timeout_s": 999999}), "timeout_s"),
    ],
)
def test_invalid_contracts_are_rejected(mutation, expected):
    value = mission_document()
    mutation(value)
    value["content_sha256"] = canonical_hash(value)
    with pytest.raises(MissionError, match=expected):
        parse_mission(value)


def test_hash_mismatch_is_rejected():
    value = mission_document()
    value["mission_version"] = "v2"
    with pytest.raises(MissionError, match="content_sha256"):
        parse_mission(value)
