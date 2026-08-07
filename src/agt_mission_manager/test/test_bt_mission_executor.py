import asyncio
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

import pytest

from agt_mission_manager.audit_log import AuditLog
from agt_mission_manager.bt_mission_executor import BehaviorTreeMissionExecutor
from agt_mission_manager.mission_model import MapBinding, Mission, MissionError, MissionState, MissionStep, StepType
from agt_mission_manager.mission_storage import MissionStorage


HASH = "sha256:" + "a" * 64


class Runner:
    cancel_timeout_s = 0.05

    def __init__(self, result=(True, 0, "ok", "", "")):
        self.result = result
        self.execution_id = ""
        self.calls = 0

    async def run(self, _task, execution_id, _feedback):
        self.calls += 1
        self.execution_id = execution_id
        return self.result

    async def cancel(self):
        return True


def mission(*steps):
    return Mission("mission", "v1", HASH, MapBinding("map", "version", HASH), tuple(steps))


def task():
    return SimpleNamespace(
        map_binding=SimpleNamespace(map_id="map", map_version_id="version"),
        task_group_id="rows", revision=1, loop=False, loop_count=1,
        content_sha256=HASH, canonical_hash=lambda: HASH,
    )


def execute(tmp_path, value, runner):
    executor = BehaviorTreeMissionExecutor(
        storage=MissionStorage(tmp_path), audit=AuditLog(tmp_path / "audit.jsonl"),
        runner=runner, status_callback=lambda _status: None)
    with patch("agt_mission_manager.bt_mission_executor.load_task_group", return_value=task()):
        return asyncio.run(executor.execute(value, "tasks/rows.json"))


def test_shape_is_rejected_before_steps_are_indexed(tmp_path):
    with pytest.raises(MissionError, match="BT_BACKEND_UNSUPPORTED_MISSION_SHAPE"):
        execute(tmp_path, mission(), Runner())


def test_generates_safe_per_execution_id_and_succeeds(tmp_path):
    runner = Runner()
    status = execute(tmp_path, mission(MissionStep("route", StepType.WAYPOINT_TASK)), runner)
    assert status.state == MissionState.SUCCEEDED
    assert runner.calls == 1
    assert runner.execution_id.startswith("bt_")
    assert ":" not in runner.execution_id


def test_readiness_blocker_is_preserved_and_not_localization_guess(tmp_path):
    runner = Runner((False, 6, "tree failed", "SENSOR_INPUT_UNHEALTHY", "sensor unhealthy"))
    status = execute(tmp_path, mission(MissionStep("route", StepType.WAYPOINT_TASK)), runner)
    assert status.state == MissionState.FAILED
    assert status.error_code == 3
    assert status.blocker_codes == ["SENSOR_INPUT_UNHEALTHY"]
    assert status.blocker_messages == ["sensor unhealthy"]


def test_task_readiness_failure_then_relocalize_failure_is_child_failed(tmp_path):
    """A stale TaskExecution blocker must not classify a Relocalize failure."""
    class ReadinessThenRelocalizeFailure(Runner):
        def __init__(self):
            super().__init__()
            self.previous_readiness_blocker = "TASK_EXECUTION_NOT_READY"

        async def run(self, _task, execution_id, _feedback):
            self.execution_id = execution_id
            # The Relocalize BT node clears the shared blocker outputs before
            # its action starts; the final result therefore has no blocker.
            return False, 6, "relocalize failed: no candidates", "", ""

    status = execute(
        tmp_path, mission(MissionStep("route", StepType.WAYPOINT_TASK)),
        ReadinessThenRelocalizeFailure())
    assert status.state == MissionState.FAILED
    assert status.error_code == 6
    assert status.error_code != 3  # READINESS_LOST
