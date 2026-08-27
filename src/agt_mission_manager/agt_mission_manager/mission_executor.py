from __future__ import annotations

import asyncio
from dataclasses import asdict, dataclass
import threading
import time
from typing import Awaitable, Callable, Protocol

from .audit_log import AuditLog
from .mission_fsm import MissionFsm
from .mission_model import (
    GateSnapshot,
    Mission,
    MissionErrorCode,
    MissionEventRecord,
    MissionRuntimeStatus,
    MissionState,
    MissionStep,
    StepType,
)
from .mission_storage import MissionStorage


@dataclass(frozen=True)
class WaypointCursor:
    loop_index: int = 0
    waypoint_index: int = 0
    total_waypoints: int = 0


@dataclass(frozen=True)
class WaypointResult:
    success: bool
    error_code: int = 0
    message: str = ""
    canceled: bool = False
    cancel_confirmed: bool = False
    missed_waypoints: tuple[int, ...] = ()


@dataclass(frozen=True)
class InspectionChildResult:
    success: bool
    error_code: int = 0
    message: str = ""
    canceled: bool = False
    cancel_confirmed: bool = False


class WaypointRunner(Protocol):
    async def run(
        self,
        task_file: str,
        cursor: WaypointCursor,
        feedback: Callable[[WaypointCursor], None],
    ) -> WaypointResult: ...

    async def cancel(self) -> bool: ...


class InspectionRunner(Protocol):
    async def run(self, mission: Mission, step: MissionStep) -> InspectionChildResult: ...
    async def cancel(self) -> bool: ...


class EventInbox:
    def __init__(self) -> None:
        self._events: list[MissionEventRecord] = []
        self._lock = threading.Lock()

    def push(self, event: MissionEventRecord) -> None:
        if event.stamp_s <= 0.0:
            return
        with self._lock:
            self._events.append(event)
            if len(self._events) > 1000:
                self._events = self._events[-1000:]

    def consume_matching(
        self, step: MissionStep, *, mission_id: str, not_before_s: float
    ) -> MissionEventRecord | None:
        with self._lock:
            for index, event in enumerate(self._events):
                if (
                    event.stamp_s < not_before_s
                    or event.event_type != step.event_type
                ):
                    continue
                if step.event_source and event.source != step.event_source:
                    continue
                if (
                    step.correlation_id
                    and event.correlation_id != step.correlation_id
                ):
                    continue
                if event.mission_id and event.mission_id != mission_id:
                    continue
                return self._events.pop(index)
        return None


class MissionExecutor:
    def __init__(
        self,
        *,
        storage: MissionStorage,
        audit: AuditLog,
        waypoint_runner: WaypointRunner,
        gate_provider: Callable[[], GateSnapshot],
        event_inbox: EventInbox,
        inspection_runner: InspectionRunner | None = None,
        status_callback: Callable[[MissionRuntimeStatus], None] | None = None,
        monotonic: Callable[[], float] = time.monotonic,
        wall_time: Callable[[], float] = time.time,
        sleep: Callable[[float], Awaitable[None]] = asyncio.sleep,
        poll_period_s: float = 0.05,
    ) -> None:
        self.storage = storage
        self.audit = audit
        self.waypoint_runner = waypoint_runner
        self.inspection_runner = inspection_runner
        self.gate_provider = gate_provider
        self.event_inbox = event_inbox
        self.status_callback = status_callback or (lambda _status: None)
        self.monotonic = monotonic
        self.wall_time = wall_time
        self.sleep = sleep
        self.poll_period_s = poll_period_s
        self.status = MissionRuntimeStatus()
        self._fsm = MissionFsm()
        self._pause_requested = threading.Event()
        self._resume_requested = threading.Event()
        self._cancel_requested = threading.Event()

    def request_pause(self) -> tuple[bool, str]:
        if self.status.state not in {
            MissionState.RUNNING,
            MissionState.WAITING_DURATION,
            MissionState.WAITING_EVENT,
        }:
            return False, "mission is not pausable in its current state"
        self._pause_requested.set()
        return True, "pause requested"

    def request_resume(self) -> tuple[bool, str]:
        if self.status.state != MissionState.PAUSED:
            return False, "mission is not paused"
        self._resume_requested.set()
        return True, "resume requested"

    def request_cancel(self) -> None:
        self._cancel_requested.set()
        self._resume_requested.set()

    def _checkpoint(self, message: str | None = None) -> None:
        if message is not None:
            self.status.message = message
        self.status.state = self._fsm.state
        serializable = asdict(self.status)
        serializable["state"] = int(self.status.state)
        serializable["current_step_type"] = int(self.status.current_step_type)
        serializable["error_code"] = int(self.status.error_code)
        self.storage.write_execution_state(serializable)
        self.status_callback(self.status)

    def _transition(self, state: MissionState, message: str) -> None:
        self._fsm.transition(state)
        self._checkpoint(message)
        self.audit.append(
            "state_transition",
            {
                "state": state.name,
                "message": message,
                "step_id": self.status.current_step_id,
            },
        )

    def _fail(
        self,
        code: MissionErrorCode,
        message: str,
        gates: GateSnapshot | None = None,
    ) -> MissionRuntimeStatus:
        if self._fsm.state not in {
            MissionState.FAILED,
            MissionState.CANCELED,
            MissionState.SUCCEEDED,
        }:
            self._fsm.transition(MissionState.FAILED)
        self.status.error_code = code
        if gates is not None:
            self.status.blocker_codes = list(gates.blocker_codes)
            self.status.blocker_messages = list(gates.blocker_messages)
        self._checkpoint(message)
        self.audit.append(
            "mission_failed",
            {"error_code": int(code), "message": message},
        )
        return self.status

    def _gates_ready(
        self, mission: Mission
    ) -> tuple[bool, MissionErrorCode, str, GateSnapshot]:
        gates = self.gate_provider()
        ready, code, message = gates.validate(mission.map_binding)
        return ready, code, message, gates

    async def _pause_until_resumed(self, mission: Mission) -> bool:
        self._pause_requested.clear()
        while not self._resume_requested.is_set():
            if self._cancel_requested.is_set():
                return False
            await self.sleep(self.poll_period_s)
        self._resume_requested.clear()
        self._transition(MissionState.RESUMING, "revalidating mission gates")
        ready, code, message, gates = self._gates_ready(mission)
        if not ready:
            self._fail(
                MissionErrorCode.RESUME_BLOCKED
                if code == MissionErrorCode.NONE
                else code,
                message,
                gates,
            )
            return False
        self._transition(MissionState.RUNNING, "mission resumed")
        self.audit.append(
            "mission_resumed", {"step_id": self.status.current_step_id}
        )
        return True

    async def _cancel_terminal(self) -> MissionRuntimeStatus:
        if self._fsm.state != MissionState.CANCELING:
            self._transition(MissionState.CANCELING, "canceling mission")
        self._transition(MissionState.CANCELED, "mission canceled")
        self.status.error_code = MissionErrorCode.CANCELED
        self._checkpoint()
        self.audit.append(
            "mission_canceled", {"step_id": self.status.current_step_id}
        )
        return self.status

    async def _pause_between_steps(self, mission: Mission) -> bool:
        if not self._pause_requested.is_set():
            return True
        self._transition(
            MissionState.PAUSING, "pausing between mission steps"
        )
        self._transition(
            MissionState.PAUSED, "mission paused between steps"
        )
        if await self._pause_until_resumed(mission):
            return True
        if self.status.state != MissionState.FAILED:
            await self._cancel_terminal()
        return False

    async def _run_waypoint(
        self, mission: Mission, step: MissionStep, task_file: str
    ) -> bool:
        cursor = WaypointCursor()
        while True:
            self.status.current_waypoint = cursor.waypoint_index
            self.status.total_waypoints = cursor.total_waypoints

            def feedback(value: WaypointCursor) -> None:
                nonlocal cursor
                cursor = value
                self.status.current_waypoint = value.waypoint_index
                self.status.total_waypoints = value.total_waypoints
                self._checkpoint("waypoint task running")

            child_task = asyncio.create_task(
                self.waypoint_runner.run(task_file, cursor, feedback)
            )
            while not child_task.done():
                if (
                    self._cancel_requested.is_set()
                    or self._pause_requested.is_set()
                ):
                    pause = (
                        self._pause_requested.is_set()
                        and not self._cancel_requested.is_set()
                    )
                    self._transition(
                        MissionState.PAUSING
                        if pause
                        else MissionState.CANCELING,
                        "canceling active waypoint child",
                    )
                    confirmed = await self.waypoint_runner.cancel()
                    result = await child_task
                    if not confirmed or not result.cancel_confirmed:
                        self._fail(
                            MissionErrorCode.CHILD_FAILED,
                            "waypoint child did not confirm cancellation",
                        )
                        return False
                    if not pause:
                        await self._cancel_terminal()
                        return False
                    self._transition(
                        MissionState.PAUSED,
                        "mission paused after child cancellation",
                    )
                    self.audit.append(
                        "waypoint_child_paused",
                        {
                            "loop_index": cursor.loop_index,
                            "waypoint_index": cursor.waypoint_index,
                        },
                    )
                    if not await self._pause_until_resumed(mission):
                        if self.status.state != MissionState.FAILED:
                            await self._cancel_terminal()
                        return False
                    self.audit.append(
                        "resume_generated_child_goal",
                        {
                            "loop_index": cursor.loop_index,
                            "waypoint_index": cursor.waypoint_index,
                        },
                    )
                    break
                await self.sleep(self.poll_period_s)
            else:
                result = await child_task
                if self._cancel_requested.is_set():
                    await self._cancel_terminal()
                    return False
                if result.success and not result.missed_waypoints:
                    return True
                if result.canceled and self._cancel_requested.is_set():
                    await self._cancel_terminal()
                    return False
                code = (
                    MissionErrorCode.CHILD_REJECTED
                    if result.error_code in {40, 41}
                    else MissionErrorCode.CHILD_FAILED
                )
                self._fail(
                    code,
                    result.message or "waypoint child failed",
                )
                return False

    async def _run_inspection(
        self, mission: Mission, step: MissionStep
    ) -> bool:
        if self.inspection_runner is None:
            self._fail(
                MissionErrorCode.CHILD_REJECTED,
                "inspection runner is unavailable",
            )
            return False

        while True:
            child_task = asyncio.create_task(
                self.inspection_runner.run(mission, step)
            )
            while not child_task.done():
                if (
                    self._cancel_requested.is_set()
                    or self._pause_requested.is_set()
                ):
                    pause = (
                        self._pause_requested.is_set()
                        and not self._cancel_requested.is_set()
                    )
                    self._transition(
                        MissionState.PAUSING
                        if pause
                        else MissionState.CANCELING,
                        "canceling active inspection child",
                    )
                    confirmed = await self.inspection_runner.cancel()
                    result = await child_task
                    if not confirmed or not result.cancel_confirmed:
                        self._fail(
                            MissionErrorCode.CHILD_FAILED,
                            "inspection child did not confirm cancellation",
                        )
                        return False
                    if not pause:
                        await self._cancel_terminal()
                        return False
                    self._transition(
                        MissionState.PAUSED,
                        "mission paused after inspection cancellation",
                    )
                    self.audit.append(
                        "inspection_child_paused",
                        {"step_id": step.id},
                    )
                    if not await self._pause_until_resumed(mission):
                        if self.status.state != MissionState.FAILED:
                            await self._cancel_terminal()
                        return False
                    self.audit.append(
                        "resume_generated_inspection_goal",
                        {"step_id": step.id},
                    )
                    break
                await self.sleep(self.poll_period_s)
            else:
                result = await child_task
                if self._cancel_requested.is_set():
                    await self._cancel_terminal()
                    return False
                if result.success:
                    return True
                if result.canceled and self._cancel_requested.is_set():
                    await self._cancel_terminal()
                    return False
                # Inspection errors 1/2 are asset/map validation failures.
                code = (
                    MissionErrorCode.CHILD_REJECTED
                    if result.error_code in {1, 2, 40, 41}
                    else MissionErrorCode.CHILD_FAILED
                )
                self._fail(
                    code,
                    result.message or "inspection child failed",
                )
                return False

    async def _run_duration(
        self, mission: Mission, step: MissionStep
    ) -> bool:
        remaining = step.duration_s
        self._transition(
            MissionState.WAITING_DURATION, "waiting for duration"
        )
        while remaining > 0.0:
            if self._cancel_requested.is_set():
                await self._cancel_terminal()
                return False
            if self._pause_requested.is_set():
                self.status.step_remaining_s = remaining
                self._transition(
                    MissionState.PAUSED, "duration wait paused"
                )
                if not await self._pause_until_resumed(mission):
                    if self.status.state != MissionState.FAILED:
                        await self._cancel_terminal()
                    return False
                self._transition(
                    MissionState.WAITING_DURATION,
                    "continuing remaining duration",
                )
            start = self.monotonic()
            await self.sleep(min(self.poll_period_s, remaining))
            elapsed = max(0.0, self.monotonic() - start)
            remaining = max(0.0, remaining - elapsed)
            self.status.step_elapsed_s = step.duration_s - remaining
            self.status.step_remaining_s = remaining
            self._checkpoint()
        self._transition(
            MissionState.RUNNING, "duration wait completed"
        )
        return True

    async def _run_event(self, mission: Mission, step: MissionStep) -> bool:
        remaining = step.timeout_s
        not_before = self.wall_time()
        self._transition(
            MissionState.WAITING_EVENT, "waiting for mission event"
        )
        while remaining > 0.0:
            if self._cancel_requested.is_set():
                await self._cancel_terminal()
                return False
            event = self.event_inbox.consume_matching(
                step,
                mission_id=mission.mission_id,
                not_before_s=not_before,
            )
            if event is not None:
                self.audit.append(
                    "event_consumed",
                    {
                        "event_type": event.event_type,
                        "source": event.source,
                        "stamp_s": event.stamp_s,
                    },
                )
                self._transition(
                    MissionState.RUNNING, "mission event received"
                )
                return True
            if self._pause_requested.is_set():
                self.status.step_remaining_s = remaining
                self._transition(
                    MissionState.PAUSED, "event wait paused"
                )
                if not await self._pause_until_resumed(mission):
                    if self.status.state != MissionState.FAILED:
                        await self._cancel_terminal()
                    return False
                self._transition(
                    MissionState.WAITING_EVENT,
                    "continuing event wait",
                )
            start = self.monotonic()
            await self.sleep(min(self.poll_period_s, remaining))
            elapsed = max(0.0, self.monotonic() - start)
            remaining = max(0.0, remaining - elapsed)
            self.status.step_elapsed_s = step.timeout_s - remaining
            self.status.step_remaining_s = remaining
            self._checkpoint()
        self._fail(
            MissionErrorCode.EVENT_TIMEOUT,
            f"event wait timed out: {step.event_type}",
        )
        return False

    async def execute(
        self,
        mission: Mission,
        task_path_resolver: Callable[[MissionStep], str],
    ) -> MissionRuntimeStatus:
        self._pause_requested.clear()
        self._resume_requested.clear()
        self._cancel_requested.clear()
        self._fsm = MissionFsm()
        self.status = MissionRuntimeStatus.for_mission(mission)
        self._fsm.transition(MissionState.VALIDATING)
        self._checkpoint()
        self.audit.append(
            "mission_validating",
            {
                "mission_id": mission.mission_id,
                "version": mission.mission_version,
            },
        )
        ready, code, message, gates = self._gates_ready(mission)
        if not ready:
            return self._fail(code, message, gates)
        self._transition(MissionState.RUNNING, "mission running")

        for index, step in enumerate(mission.steps):
            if self._cancel_requested.is_set():
                return await self._cancel_terminal()
            if not await self._pause_between_steps(mission):
                return self.status
            self.status.current_step_index = index
            self.status.current_step_id = step.id
            self.status.current_step_type = step.type
            self.status.current_waypoint = 0
            self.status.total_waypoints = 0
            self.status.step_elapsed_s = 0.0
            self.status.step_remaining_s = step.duration_s or step.timeout_s
            self._checkpoint(f"starting step {step.id}")
            self.audit.append(
                "step_started",
                {"step_id": step.id, "step_type": step.type.name},
            )

            if step.type in {
                StepType.WAYPOINT_TASK,
                StepType.INSPECTION_TASK,
            }:
                ready, code, message, gates = self._gates_ready(mission)
                if not ready:
                    return self._fail(code, message, gates)

            if step.type == StepType.WAYPOINT_TASK:
                completed = await self._run_waypoint(
                    mission, step, task_path_resolver(step)
                )
            elif step.type == StepType.INSPECTION_TASK:
                completed = await self._run_inspection(mission, step)
            elif step.type == StepType.WAIT_DURATION:
                completed = await self._run_duration(mission, step)
            elif step.type == StepType.WAIT_EVENT:
                completed = await self._run_event(mission, step)
            else:
                return self._fail(
                    MissionErrorCode.INVALID_MISSION,
                    "unsupported mission step",
                )

            if not completed:
                return self.status
            self.audit.append("step_completed", {"step_id": step.id})

        if self._cancel_requested.is_set():
            return await self._cancel_terminal()
        if not await self._pause_between_steps(mission):
            return self.status
        self._transition(MissionState.SUCCEEDED, "mission completed")
        self.audit.append(
            "mission_succeeded", {"mission_id": mission.mission_id}
        )
        return self.status
