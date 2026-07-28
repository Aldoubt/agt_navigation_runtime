import asyncio
from pathlib import Path
import time

from agt_mission_manager.audit_log import AuditLog
from agt_mission_manager.mission_executor import (
    EventInbox, MissionExecutor, WaypointCursor, WaypointResult,
)
from agt_mission_manager.mission_model import (
    GateSnapshot, MapBinding, Mission, MissionEventRecord, MissionState, MissionStep, StepType,
)
from agt_mission_manager.mission_storage import MissionStorage


HASH = "sha256:" + "a" * 64


def mission_with(*steps):
    return Mission(
        mission_id="demo",
        mission_version="v1",
        content_sha256=HASH,
        map_binding=MapBinding("map_a", "v1", HASH),
        steps=tuple(steps),
    )


def ready_gates():
    return GateSnapshot(
        map_id="map_a",
        map_version_id="v1",
        manifest_sha256=HASH,
        localization_ready=True,
        task_ready=True,
    )


class SuccessfulRunner:
    async def run(self, _task_file, _cursor, feedback):
        feedback(WaypointCursor(0, 1, 2))
        return WaypointResult(True)

    async def cancel(self):
        return True


class FailingRunner(SuccessfulRunner):
    async def run(self, _task_file, _cursor, feedback):
        feedback(WaypointCursor(0, 0, 2))
        return WaypointResult(False, error_code=42, message="child failed", missed_waypoints=(1,))


class BlockingRunner(SuccessfulRunner):
    def __init__(self):
        self.started = asyncio.Event()
        self.canceled = asyncio.Event()

    async def run(self, _task_file, cursor, feedback):
        feedback(WaypointCursor(cursor.loop_index, 1, 3))
        self.started.set()
        await self.canceled.wait()
        return WaypointResult(
            False, error_code=50, message="canceled", canceled=True, cancel_confirmed=True
        )

    async def cancel(self):
        self.canceled.set()
        return True


def executor(tmp_path, mission_runner=None, gates=ready_gates):
    return MissionExecutor(
        storage=MissionStorage(tmp_path),
        audit=AuditLog(tmp_path / "audit.jsonl"),
        waypoint_runner=mission_runner or SuccessfulRunner(),
        gate_provider=gates,
        event_inbox=EventInbox(),
        poll_period_s=0.005,
    )


def test_waypoint_child_success_and_failure_are_authoritative(tmp_path):
    mission = mission_with(MissionStep("route", StepType.WAYPOINT_TASK, task_file="tasks/route.json"))
    success = asyncio.run(executor(tmp_path / "ok").execute(mission, lambda _step: "route.json"))
    failure = asyncio.run(
        executor(tmp_path / "fail", FailingRunner()).execute(mission, lambda _step: "route.json")
    )
    assert success.state == MissionState.SUCCEEDED
    assert failure.state == MissionState.FAILED
    assert failure.message == "child failed"


def test_wait_duration_pause_preserves_remaining_time(tmp_path):
    async def scenario():
        current = executor(tmp_path)
        mission = mission_with(MissionStep("wait", StepType.WAIT_DURATION, duration_s=0.15))
        task = asyncio.create_task(current.execute(mission, lambda _step: ""))
        while current.status.state != MissionState.WAITING_DURATION:
            await asyncio.sleep(0.002)
        await asyncio.sleep(0.02)
        assert current.request_pause()[0]
        while current.status.state != MissionState.PAUSED:
            await asyncio.sleep(0.002)
        remaining = current.status.step_remaining_s
        await asyncio.sleep(0.03)
        assert current.status.step_remaining_s == remaining
        assert 0.0 < remaining < 0.15
        assert current.request_resume()[0]
        return await task

    assert asyncio.run(scenario()).state == MissionState.SUCCEEDED


def test_wait_event_rejects_stale_event_and_times_out(tmp_path):
    current = executor(tmp_path)
    current.event_inbox.push(
        MissionEventRecord(
            stamp_s=time.time() - 10.0, event_type="arm.finished", source="arm"
        )
    )
    mission = mission_with(
        MissionStep(
            "event", StepType.WAIT_EVENT, event_type="arm.finished",
            event_source="arm", timeout_s=0.03,
        )
    )
    status = asyncio.run(current.execute(mission, lambda _step: ""))
    assert status.state == MissionState.FAILED
    assert "timed out" in status.message


def test_fresh_correlated_event_completes_wait(tmp_path):
    async def scenario():
        current = executor(tmp_path)
        mission = mission_with(
            MissionStep(
                "event", StepType.WAIT_EVENT, event_type="arm.finished",
                event_source="arm", correlation_id="op-1", timeout_s=0.2,
            )
        )
        task = asyncio.create_task(current.execute(mission, lambda _step: ""))
        while current.status.state != MissionState.WAITING_EVENT:
            await asyncio.sleep(0.002)
        current.event_inbox.push(
            MissionEventRecord(
                stamp_s=time.time(), event_type="arm.finished", source="arm",
                correlation_id="op-1", mission_id="demo",
            )
        )
        return await task

    assert asyncio.run(scenario()).state == MissionState.SUCCEEDED


def test_parent_cancel_waits_for_waypoint_child_confirmation(tmp_path):
    async def scenario():
        runner = BlockingRunner()
        current = executor(tmp_path, runner)
        mission = mission_with(MissionStep("route", StepType.WAYPOINT_TASK, task_file="tasks/route.json"))
        task = asyncio.create_task(current.execute(mission, lambda _step: "route.json"))
        await runner.started.wait()
        current.request_cancel()
        status = await task
        return status, runner.canceled.is_set()

    status, child_canceled = asyncio.run(scenario())
    assert child_canceled
    assert status.state == MissionState.CANCELED


def test_map_binding_mismatch_blocks_before_child_goal(tmp_path):
    called = False

    class NeverRunner(SuccessfulRunner):
        async def run(self, *args):
            nonlocal called
            called = True
            return await super().run(*args)

    gates = lambda: GateSnapshot(
        map_id="map_b", map_version_id="v2", manifest_sha256=HASH,
        localization_ready=True, task_ready=True,
    )
    mission = mission_with(MissionStep("route", StepType.WAYPOINT_TASK, task_file="tasks/route.json"))
    status = asyncio.run(
        executor(tmp_path, NeverRunner(), gates).execute(mission, lambda _step: "route.json")
    )
    assert status.state == MissionState.FAILED
    assert not called


def test_gates_are_rechecked_after_wait_before_waypoint(tmp_path):
    snapshots = [ready_gates()]
    called = False

    class NeverRunner(SuccessfulRunner):
        async def run(self, *args):
            nonlocal called
            called = True
            return await super().run(*args)

    def gates():
        if len(snapshots) == 1:
            snapshots.append(
                GateSnapshot(
                    map_id="map_a", map_version_id="v1", manifest_sha256=HASH,
                    localization_ready=False, task_ready=False,
                )
            )
            return snapshots[0]
        return snapshots[-1]

    mission = mission_with(
        MissionStep("wait", StepType.WAIT_DURATION, duration_s=0.01),
        MissionStep("route", StepType.WAYPOINT_TASK, task_file="tasks/route.json"),
    )
    status = asyncio.run(
        executor(tmp_path, NeverRunner(), gates).execute(mission, lambda _step: "route.json")
    )
    assert status.state == MissionState.FAILED
    assert not called


def test_pause_between_steps_does_not_start_next_child(tmp_path):
    async def scenario():
        runner = SuccessfulRunner()
        current = executor(tmp_path, runner)
        mission = mission_with(
            MissionStep("wait", StepType.WAIT_DURATION, duration_s=0.02),
            MissionStep("route", StepType.WAYPOINT_TASK, task_file="tasks/route.json"),
        )
        task = asyncio.create_task(current.execute(mission, lambda _step: "route.json"))
        while current.status.state != MissionState.WAITING_DURATION:
            await asyncio.sleep(0.002)
        current.request_pause()
        while current.status.state != MissionState.PAUSED:
            await asyncio.sleep(0.002)
        current.request_resume()
        return await task

    assert asyncio.run(scenario()).state == MissionState.SUCCEEDED
