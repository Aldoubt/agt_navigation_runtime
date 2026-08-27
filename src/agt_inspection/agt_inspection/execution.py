from __future__ import annotations

import asyncio
from dataclasses import dataclass
from enum import IntEnum
from typing import Awaitable, Callable, Protocol

from .model import InspectionPoint, InspectionTask


class InspectionErrorCode(IntEnum):
    NONE = 0
    INVALID_TASK = 1
    MAP_MISMATCH = 2
    NAVIGATION = 3
    NOT_STATIONARY = 4
    GIMBAL = 5
    CAPTURE = 6
    INFERENCE = 7
    CANCELED = 8
    INTERNAL = 255


@dataclass(frozen=True)
class ChildResult:
    success: bool
    error_code: int = 0
    message: str = ""
    canceled: bool = False
    cancel_confirmed: bool = False


@dataclass(frozen=True)
class CaptureResult:
    success: bool
    error_code: int = 0
    message: str = ""
    image_bytes: bytes = b""
    image_uri: str = ""


@dataclass(frozen=True)
class VisionResult:
    success: bool
    error_code: int = 0
    message: str = ""
    model_id: str = ""
    model_version: str = ""
    inference_time_ms: float = 0.0
    primary_confidence: float = 0.0
    result_json: str = "{}"
    canceled: bool = False
    cancel_confirmed: bool = False


@dataclass(frozen=True)
class InspectionResult:
    success: bool
    error_code: int
    message: str
    evidence_root_uri: str
    canceled: bool = False


class NavigationRunner(Protocol):
    async def run(self, point: InspectionPoint) -> ChildResult: ...
    async def cancel(self) -> bool: ...


class GimbalRunner(Protocol):
    async def move(self, point: InspectionPoint) -> ChildResult: ...
    async def cancel(self) -> bool: ...


class CameraRunner(Protocol):
    async def capture(
        self, point: InspectionPoint, capture_index: int, request_id: str
    ) -> CaptureResult: ...


class VisionRunner(Protocol):
    async def inspect(
        self, point: InspectionPoint, capture: CaptureResult, request_id: str
    ) -> VisionResult: ...
    async def cancel(self) -> bool: ...


class StationaryProvider(Protocol):
    def sample(self) -> tuple[float, float, float]: ...


class EvidenceWriterProtocol(Protocol):
    def start_session(self, task: InspectionTask, session_id: str) -> str: ...
    def persist_capture(
        self,
        task: InspectionTask,
        session_id: str,
        point: InspectionPoint,
        capture_index: int,
        request_id: str,
        capture: CaptureResult,
        vision: VisionResult,
    ) -> str: ...
    def finish_session(
        self,
        task: InspectionTask,
        session_id: str,
        *,
        success: bool,
        error_code: int,
        message: str,
        canceled: bool = False,
    ) -> None: ...


class InspectionExecutor:
    ERROR_NONE = InspectionErrorCode.NONE
    ERROR_INVALID_TASK = InspectionErrorCode.INVALID_TASK
    ERROR_MAP_MISMATCH = InspectionErrorCode.MAP_MISMATCH
    ERROR_NAVIGATION = InspectionErrorCode.NAVIGATION
    ERROR_NOT_STATIONARY = InspectionErrorCode.NOT_STATIONARY
    ERROR_GIMBAL = InspectionErrorCode.GIMBAL
    ERROR_CAPTURE = InspectionErrorCode.CAPTURE
    ERROR_INFERENCE = InspectionErrorCode.INFERENCE
    ERROR_CANCELED = InspectionErrorCode.CANCELED
    ERROR_INTERNAL = InspectionErrorCode.INTERNAL

    def __init__(
        self,
        *,
        navigation: NavigationRunner,
        gimbal: GimbalRunner,
        camera: CameraRunner,
        vision: VisionRunner,
        stationary: StationaryProvider,
        evidence: EvidenceWriterProtocol,
        monotonic: Callable[[], float],
        sleep: Callable[[float], Awaitable[None]] = asyncio.sleep,
        stage_callback: Callable[[str, str], None] | None = None,
        poll_period_s: float = 0.05,
        stationary_freshness_s: float = 0.5,
    ) -> None:
        self._navigation = navigation
        self._gimbal = gimbal
        self._camera = camera
        self._vision = vision
        self._stationary = stationary
        self._evidence = evidence
        self._monotonic = monotonic
        self._sleep = sleep
        self._stage_callback = stage_callback or (lambda _stage, _point_id: None)
        self._poll_period_s = max(float(poll_period_s), 0.001)
        self._stationary_freshness_s = max(float(stationary_freshness_s), 0.001)
        self._cancel_requested = False
        self._active_child = ""

    def request_cancel(self) -> None:
        self._cancel_requested = True

    async def cancel(self) -> bool:
        self.request_cancel()
        return True

    def _stage(self, stage: str, point: InspectionPoint) -> None:
        self._stage_callback(stage, point.id)

    def _finish(
        self,
        task: InspectionTask,
        session_id: str,
        root: str,
        success: bool,
        error_code: int,
        message: str,
        *,
        canceled: bool = False,
    ) -> InspectionResult:
        self._evidence.finish_session(
            task,
            session_id,
            success=success,
            error_code=int(error_code),
            message=message,
            canceled=canceled,
        )
        return InspectionResult(success, int(error_code), message, root, canceled)

    def _finish_canceled(
        self, task: InspectionTask, session_id: str, root: str
    ) -> InspectionResult:
        return self._finish(
            task,
            session_id,
            root,
            False,
            InspectionErrorCode.CANCELED,
            "canceled",
            canceled=True,
        )

    async def _run_cancelable_child(
        self,
        name: str,
        operation: Callable[[], Awaitable[ChildResult]],
        cancel_operation: Callable[[], Awaitable[bool]],
    ) -> ChildResult:
        self._active_child = name
        child = asyncio.create_task(operation())
        try:
            while not child.done():
                if self._cancel_requested:
                    request_confirmed = bool(await cancel_operation())
                    result = await child
                    result_confirmed = bool(result.canceled and result.cancel_confirmed)
                    if request_confirmed and result_confirmed:
                        return ChildResult(
                            False,
                            int(InspectionErrorCode.CANCELED),
                            result.message or "canceled",
                            canceled=True,
                            cancel_confirmed=True,
                        )
                    return ChildResult(
                        False,
                        int(InspectionErrorCode.INTERNAL),
                        f"{name} child did not confirm cancellation",
                    )
                await asyncio.sleep(0)
            return await child
        finally:
            self._active_child = ""

    async def _navigate_and_stabilize(self, point: InspectionPoint) -> tuple[ChildResult, bool]:
        """Run navigation and the stationary gate under one finite retry budget."""
        last = ChildResult(False, int(InspectionErrorCode.NAVIGATION), "navigation failed")
        for attempt in range(point.retry.navigation + 1):
            if self._cancel_requested:
                return ChildResult(
                    False,
                    int(InspectionErrorCode.CANCELED),
                    "canceled",
                    canceled=True,
                    cancel_confirmed=True,
                ), False
            self._stage("NAVIGATING", point)
            last = await self._run_cancelable_child(
                "navigation", lambda: self._navigation.run(point), self._navigation.cancel
            )
            if last.canceled or last.error_code == int(InspectionErrorCode.INTERNAL):
                return last, False
            if not last.success:
                if attempt < point.retry.navigation:
                    continue
                return last, False

            self._stage("WAITING_ROBOT_STABLE", point)
            if await self._wait_stationary(point):
                return last, True
            if self._cancel_requested:
                return ChildResult(
                    False,
                    int(InspectionErrorCode.CANCELED),
                    "canceled",
                    canceled=True,
                    cancel_confirmed=True,
                ), False
            if attempt >= point.retry.navigation:
                return ChildResult(
                    False,
                    int(InspectionErrorCode.NOT_STATIONARY),
                    "robot did not remain stationary for the required window",
                ), False
        return last, False

    async def _retry_gimbal(self, point: InspectionPoint) -> ChildResult:
        last = ChildResult(False, int(InspectionErrorCode.GIMBAL), "gimbal move failed")
        for _ in range(point.retry.gimbal + 1):
            if self._cancel_requested:
                return ChildResult(
                    False,
                    int(InspectionErrorCode.CANCELED),
                    "canceled",
                    canceled=True,
                    cancel_confirmed=True,
                )
            self._stage("MOVING_GIMBAL", point)
            last = await self._run_cancelable_child(
                "gimbal", lambda: self._gimbal.move(point), self._gimbal.cancel
            )
            if last.success or last.canceled or last.error_code == int(InspectionErrorCode.INTERNAL):
                return last
        return last

    async def _retry_capture(
        self, point: InspectionPoint, capture_index: int, request_id: str
    ) -> CaptureResult:
        last = CaptureResult(
            False, int(InspectionErrorCode.CAPTURE), message="capture not attempted"
        )
        for _ in range(point.retry.capture + 1):
            if self._cancel_requested:
                return CaptureResult(
                    False, int(InspectionErrorCode.CANCELED), message="canceled"
                )
            self._stage("CAPTURING", point)
            last = await self._camera.capture(point, capture_index, request_id)
            if last.success:
                return last
        return last

    async def _retry_vision(
        self, point: InspectionPoint, capture: CaptureResult, request_id: str
    ) -> VisionResult:
        last = VisionResult(
            False, int(InspectionErrorCode.INFERENCE), message="inference not attempted"
        )
        for _ in range(point.retry.inference + 1):
            if self._cancel_requested:
                return VisionResult(
                    False,
                    int(InspectionErrorCode.CANCELED),
                    message="canceled",
                    canceled=True,
                    cancel_confirmed=True,
                )
            self._stage("INFERENCING", point)
            self._active_child = "vision"
            child = asyncio.create_task(self._vision.inspect(point, capture, request_id))
            try:
                while not child.done():
                    if self._cancel_requested:
                        request_confirmed = bool(await self._vision.cancel())
                        result = await child
                        if request_confirmed and result.canceled and result.cancel_confirmed:
                            return VisionResult(
                                False,
                                int(InspectionErrorCode.CANCELED),
                                message=result.message or "canceled",
                                canceled=True,
                                cancel_confirmed=True,
                            )
                        return VisionResult(
                            False,
                            int(InspectionErrorCode.INTERNAL),
                            message="vision child did not confirm cancellation",
                        )
                    await asyncio.sleep(0)
                last = await child
            finally:
                self._active_child = ""
            if last.success and last.primary_confidence >= point.vision.minimum_confidence:
                return last
        return last

    async def _wait_stationary(self, point: InspectionPoint) -> bool:
        deadline = self._monotonic() + point.stabilization.timeout_s
        stable_since: float | None = None
        while self._monotonic() <= deadline:
            if self._cancel_requested:
                return False
            now = self._monotonic()
            stamp, linear_x, angular_z = self._stationary.sample()
            age = now - float(stamp)
            fresh = 0.0 <= age <= self._stationary_freshness_s
            under_limits = (
                abs(float(linear_x)) <= point.stabilization.linear_velocity_max_mps
                and abs(float(angular_z)) <= point.stabilization.angular_velocity_max_radps
            )
            if fresh and under_limits:
                if stable_since is None:
                    stable_since = now
                if now - stable_since >= point.stabilization.stable_duration_s:
                    return True
            else:
                stable_since = None
            await self._sleep(self._poll_period_s)
        return False

    async def _sleep_cancelable(self, duration: float) -> bool:
        remaining = max(float(duration), 0.0)
        while remaining > 0.0:
            if self._cancel_requested:
                return False
            chunk = min(self._poll_period_s, remaining)
            await self._sleep(chunk)
            remaining = max(0.0, remaining - chunk)
        return not self._cancel_requested

    async def execute(self, task: InspectionTask, *, session_id: str) -> InspectionResult:
        self._cancel_requested = False
        root = self._evidence.start_session(task, session_id)
        try:
            for point in task.points:
                if self._cancel_requested:
                    return self._finish_canceled(task, session_id, root)

                navigation, stationary = await self._navigate_and_stabilize(point)
                if not stationary:
                    if navigation.canceled:
                        return self._finish_canceled(task, session_id, root)
                    code = (
                        InspectionErrorCode.INTERNAL
                        if navigation.error_code == int(InspectionErrorCode.INTERNAL)
                        else InspectionErrorCode.NOT_STATIONARY
                        if navigation.error_code == int(InspectionErrorCode.NOT_STATIONARY)
                        else InspectionErrorCode.NAVIGATION
                    )
                    return self._finish(
                        task,
                        session_id,
                        root,
                        False,
                        code,
                        navigation.message or "navigation/stationary gate failed",
                    )

                gimbal = await self._retry_gimbal(point)
                if gimbal.canceled:
                    return self._finish_canceled(task, session_id, root)
                if not gimbal.success:
                    code = (
                        InspectionErrorCode.INTERNAL
                        if gimbal.error_code == int(InspectionErrorCode.INTERNAL)
                        else InspectionErrorCode.GIMBAL
                    )
                    return self._finish(
                        task,
                        session_id,
                        root,
                        False,
                        code,
                        gimbal.message or "gimbal move failed",
                    )

                self._stage("WAITING_GIMBAL_STABLE", point)
                if not await self._sleep_cancelable(point.gimbal.settle_duration_s):
                    return self._finish_canceled(task, session_id, root)

                for capture_index in range(1, point.camera.capture_count + 1):
                    request_id = f"{session_id}:{point.id}:{capture_index}"
                    capture = await self._retry_capture(point, capture_index, request_id)
                    if self._cancel_requested or capture.error_code == int(InspectionErrorCode.CANCELED):
                        return self._finish_canceled(task, session_id, root)
                    if not capture.success:
                        return self._finish(
                            task,
                            session_id,
                            root,
                            False,
                            InspectionErrorCode.CAPTURE,
                            capture.message or "capture failed",
                        )

                    vision = await self._retry_vision(point, capture, request_id)
                    if vision.canceled:
                        return self._finish_canceled(task, session_id, root)
                    if vision.error_code == int(InspectionErrorCode.INTERNAL):
                        return self._finish(
                            task,
                            session_id,
                            root,
                            False,
                            InspectionErrorCode.INTERNAL,
                            vision.message,
                        )
                    if not vision.success or vision.primary_confidence < point.vision.minimum_confidence:
                        return self._finish(
                            task,
                            session_id,
                            root,
                            False,
                            InspectionErrorCode.INFERENCE,
                            vision.message
                            or "vision inference failed or below confidence threshold",
                        )

                    self._stage("SAVING_RESULT", point)
                    self._evidence.persist_capture(
                        task,
                        session_id,
                        point,
                        capture_index,
                        request_id,
                        capture,
                        vision,
                    )

                    if capture_index < point.camera.capture_count:
                        if not await self._sleep_cancelable(point.camera.capture_interval_s):
                            return self._finish_canceled(task, session_id, root)

            return self._finish(
                task,
                session_id,
                root,
                True,
                InspectionErrorCode.NONE,
                "inspection completed",
            )
        except Exception as exc:
            return self._finish(
                task,
                session_id,
                root,
                False,
                InspectionErrorCode.INTERNAL,
                str(exc),
            )
        finally:
            self._active_child = ""
