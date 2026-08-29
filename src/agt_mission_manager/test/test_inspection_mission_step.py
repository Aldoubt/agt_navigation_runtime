import copy

import pytest

from agt_mission_manager.mission_model import MissionError, StepType
from agt_mission_manager.mission_schema import canonical_hash, parse_mission


def _document():
    value = {
        "schema_version": 1,
        "mission_id": "inspection_mission_01",
        "mission_version": "v1",
        "map_binding": {
            "map_id": "greenhouse_a",
            "map_version_id": "v12",
            "manifest_sha256": "sha256:" + "a" * 64,
        },
        "steps": [
            {
                "id": "inspect_greenhouse",
                "type": "INSPECTION_TASK",
                "inspection_task_id": "greenhouse_camera_route_01",
                "inspection_task_revision": 1,
                "expected_content_sha256": "sha256:" + "b" * 64,
            }
        ],
    }
    value["content_sha256"] = canonical_hash(value)
    return value


def test_inspection_step_is_map_bound_reference_not_a_file_or_pose_payload():
    mission = parse_mission(_document())
    step = mission.steps[0]
    assert step.type == StepType.INSPECTION_TASK
    assert step.inspection_task_id == "greenhouse_camera_route_01"
    assert step.inspection_task_revision == 1
    assert step.expected_content_sha256 == "sha256:" + "b" * 64
    assert step.task_file == ""


@pytest.mark.parametrize(
    "mutation, expected",
    [
        (
            lambda step: step.__setitem__("inspection_task_revision", 0),
            "inspection_task_revision",
        ),
        (
            lambda step: step.__setitem__("inspection_task_id", "../bad"),
            "inspection_task_id",
        ),
        (
            lambda step: step.__setitem__("expected_content_sha256", "bad"),
            "expected_content_sha256",
        ),
        (
            lambda step: step.__setitem__("extra", True),
            "keys are invalid",
        ),
    ],
)
def test_invalid_inspection_step_is_rejected(mutation, expected):
    value = _document()
    mutation(value["steps"][0])
    value["content_sha256"] = canonical_hash(value)
    with pytest.raises(MissionError, match=expected):
        parse_mission(value)
