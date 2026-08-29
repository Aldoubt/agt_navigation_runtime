import asyncio

from agt_mission_manager.audit_log import AuditLog
from agt_mission_manager.mission_executor import (
    EventInbox,
    InspectionChildResult,
    MissionExecutor,
    WaypointResult,
)
from agt_mission_manager.mission_model import (
    GateSnapshot,
    MapBinding,
    Mission,
    MissionErrorCode,
    MissionState,
    MissionStep,
    StepType,
)
from agt_mission_manager.mission_storage import MissionStorage


HASH = "sha256:" + "a" * 64
TASK_HASH = "sha256:" + "b" * 64


class UnusedWaypointRunner:
    async def run(self, *_args):
        return WaypointResult(True)

    async def cancel(self):
        return True


class InspectionRunner:
    def __init__(self, result=None, block=False):
        self.result = result or InspectionChildResult(True)
        self.calls = []
        self.cancel_calls = 0
        self.block = block
        self.started = asyncio.Event()
        self.canceled = asyncio.Event()

    async def run(self, mission, step):
        self.calls.append((mission.map_binding.map_id, step.inspection_task_id))
        self.started.set()
        if self.block:
            await self.canceled.wait()
            return InspectionChildResult(
                False,
                error_code=8,
                message="canceled",
                canceled=True,
                cancel_confirmed=True,
            )
        return self.result

    async def cancel(self):
        self.cancel_calls += 1
        self.canceled.set()
        return True


def _mission():
    return Mission(
        mission_id="inspection_mission",
        mission_version="v1",
        content_sha256=HASH,
        map_binding=MapBinding("map_a", "v1", HASH),
        steps=(
            MissionStep(
                "inspect",
                StepType.INSPECTION_TASK,
                inspection_task_id="inspection_01",
                inspection_task_revision=1,
                expected_content_sha256=TASK_HASH,
            ),
        ),
    )


def _gates():
    return GateSnapshot(
        map_id="map_a",
        map_version_id="v1",
        manifest_sha256=HASH,
        localization_ready=True,
        task_ready=True,
    )


def _executor(tmp_path, runner):
    return MissionExecutor(
        storage=MissionStorage(tmp_path),
        audit=AuditLog(tmp_path / "audit.jsonl"),
        waypoint_runner=UnusedWaypointRunner(),
        inspection_runner=runner,
        gate_provider=_gates,
        event_inbox=EventInbox(),
        poll_period_s=0.002,
    )


def test_inspection_step_delegates_to_inspection_runner(tmp_path):
    runner = InspectionRunner()
    status = asyncio.run(_executor(tmp_path, runner).execute(_mission(), lambda _step: ""))
    assert status.state == MissionState.SUCCEEDED
    assert runner.calls == [("map_a", "inspection_01")]


def test_inspection_asset_rejection_maps_to_child_rejected(tmp_path):
    runner = InspectionRunner(
        InspectionChildResult(False, error_code=1, message="invalid task")
    )
    status = asyncio.run(_executor(tmp_path, runner).execute(_mission(), lambda _step: ""))
    assert status.state == MissionState.FAILED
    assert status.error_code == MissionErrorCode.CHILD_REJECTED


def test_inspection_runtime_failure_maps_to_child_failed(tmp_path):
    runner = InspectionRunner(
        InspectionChildResult(False, error_code=6, message="capture failed")
    )
    status = asyncio.run(_executor(tmp_path, runner).execute(_mission(), lambda _step: ""))
    assert status.state == MissionState.FAILED
    assert status.error_code == MissionErrorCode.CHILD_FAILED


def test_parent_cancel_waits_for_inspection_child_confirmation(tmp_path):
    async def scenario():
        runner = InspectionRunner(block=True)
        current = _executor(tmp_path, runner)
        task = asyncio.create_task(current.execute(_mission(), lambda _step: ""))
        await runner.started.wait()
        current.request_cancel()
        status = await task
        return status, runner

    status, runner = asyncio.run(scenario())
    assert status.state == MissionState.CANCELED
    assert runner.cancel_calls == 1
