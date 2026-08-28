import asyncio

import pytest

from agt_mission_manager.audit_log import AuditLog
from agt_mission_manager.mission_executor import (
    EventInbox,
    InspectionChildResult,
    MissionExecutor,
    TaskGroupChildResult,
    WaypointResult,
)
from agt_mission_manager.mission_model import (
    GateSnapshot,
    MapBinding,
    Mission,
    MissionError,
    MissionState,
    MissionStep,
    StepType,
)
from agt_mission_manager.mission_schema import canonical_hash, parse_mission
from agt_mission_manager.mission_storage import MissionStorage


MAP_HASH = "sha256:" + "a" * 64
INSPECTION_HASH = "sha256:" + "b" * 64
HOME_HASH = "sha256:" + "c" * 64
MISSION_HASH = "sha256:" + "d" * 64


def _document():
    value = {
        "schema_version": 1,
        "mission_id": "flower_inspection",
        "mission_version": "v1",
        "content_sha256": "sha256:" + "0" * 64,
        "map_binding": {
            "map_id": "mock_map",
            "map_version_id": "v1",
            "manifest_sha256": MAP_HASH,
        },
        "steps": [
            {
                "id": "inspect",
                "type": "INSPECTION_TASK",
                "inspection_task_id": "inspection_multiview_two_point",
                "inspection_task_revision": 1,
                "expected_content_sha256": INSPECTION_HASH,
            },
            {
                "id": "return_home",
                "type": "RETURN_HOME",
                "task_group_id": "home_mock",
                "task_group_revision": 1,
                "expected_content_sha256": HOME_HASH,
            },
        ],
    }
    value["content_sha256"] = canonical_hash(value)
    return value


def test_return_home_schema_uses_formal_task_group_binding_and_must_be_last():
    mission = parse_mission(_document())
    home = mission.steps[-1]
    assert home.type == StepType.RETURN_HOME
    assert home.task_group_id == "home_mock"
    assert home.task_group_revision == 1
    assert home.expected_content_sha256 == HOME_HASH

    bad = _document()
    bad["steps"] = [bad["steps"][1], bad["steps"][0]]
    bad["content_sha256"] = canonical_hash(bad)
    with pytest.raises(MissionError, match="RETURN_HOME must be the final mission step"):
        parse_mission(bad)


def test_return_home_may_appear_at_most_once():
    bad = _document()
    duplicate = dict(bad["steps"][-1])
    duplicate["id"] = "return_home_again"
    bad["steps"].append(duplicate)
    bad["content_sha256"] = canonical_hash(bad)
    with pytest.raises(MissionError, match="RETURN_HOME may appear at most once"):
        parse_mission(bad)


class UnusedWaypointRunner:
    async def run(self, *_args):
        return WaypointResult(True)

    async def cancel(self):
        return True


class InspectionRunner:
    def __init__(self, order):
        self.order = order

    async def run(self, mission, step):
        self.order.append(("inspection", step.inspection_task_id))
        return InspectionChildResult(
            True,
            session_id="inspection_session_01",
            evidence_root_uri="/tmp/inspection_evidence_01",
        )

    async def cancel(self):
        return True


class TaskGroupRunner:
    def __init__(self, order):
        self.order = order
        self.calls = []

    async def run(self, mission, step):
        self.order.append(("home", step.task_group_id))
        self.calls.append(
            (
                mission.map_binding.map_id,
                mission.map_binding.map_version_id,
                step.task_group_id,
                step.task_group_revision,
                step.expected_content_sha256,
            )
        )
        return TaskGroupChildResult(True, message="home reached")

    async def cancel(self):
        return True


def _mission():
    return Mission(
        mission_id="flower_inspection",
        mission_version="v1",
        content_sha256=MISSION_HASH,
        map_binding=MapBinding("mock_map", "v1", MAP_HASH),
        steps=(
            MissionStep(
                "inspect",
                StepType.INSPECTION_TASK,
                inspection_task_id="inspection_multiview_two_point",
                inspection_task_revision=1,
                expected_content_sha256=INSPECTION_HASH,
            ),
            MissionStep(
                "return_home",
                StepType.RETURN_HOME,
                task_group_id="home_mock",
                task_group_revision=1,
                expected_content_sha256=HOME_HASH,
            ),
        ),
    )


def _gates():
    return GateSnapshot(
        map_id="mock_map",
        map_version_id="v1",
        manifest_sha256=MAP_HASH,
        localization_ready=True,
        task_ready=True,
    )


def test_successful_inspection_runs_formal_home_task_afterwards(tmp_path):
    order = []
    home = TaskGroupRunner(order)
    executor = MissionExecutor(
        storage=MissionStorage(tmp_path),
        audit=AuditLog(tmp_path / "audit.jsonl"),
        waypoint_runner=UnusedWaypointRunner(),
        inspection_runner=InspectionRunner(order),
        task_group_runner=home,
        gate_provider=_gates,
        event_inbox=EventInbox(),
        poll_period_s=0.002,
    )
    status = asyncio.run(executor.execute(_mission(), lambda _step: ""))
    assert status.state == MissionState.SUCCEEDED
    assert order == [
        ("inspection", "inspection_multiview_two_point"),
        ("home", "home_mock"),
    ]
    assert home.calls == [
        ("mock_map", "v1", "home_mock", 1, HOME_HASH)
    ]
