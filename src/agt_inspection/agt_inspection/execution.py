from __future__ import annotations

import asyncio
from dataclasses import dataclass
from typing import Awaitable, Callable, Protocol

from .model import InspectionPoint, InspectionTask


@dataclass(frozen=True)
class ChildResult:
    success: bool
    error_code: int = 0
    message: str = ""


@dataclass(frozen=True)
class CaptureResult:
    success: bool
    error_code: int = 0
    image_payload: bytes = b""
    image_uri: str = ""
    message: str = ""


@dataclass(frozen=True)
class VisionResult:
    success: bool
    error_code: int = 0
    model_id: str = ""
    model_version: str = ""
    inference_time_ms: float = 0.0
    primary_confidence: float = 0.0
    result_json: str = "{}"
    message: str = ""


@dataclass(frozen=True)
class InspectionResult:
    success: bool
    error_code: int
    message: str
    evidence_root_uri: str


class NavigationRunner(Protocol):
    async def run(self, point: InspectionPoint) -> ChildResult: ...
    async def cancel(self) -> bool: ...


class GimbalRunner(Protocol):
    async def move(self, point: InspectionPoint) -> ChildResult: ...
    async def cancel(self) -> bool: ...


class CameraRunner(Protocol):
    async def capture(self, point: InspectionPoint, capture_index: int) -> CaptureResult: ...


class VisionRunner(Protocol):
    async def inspect(self, point: InspectionPoint, capture: CaptureResult) -> VisionResult: ...
    async def cancel(self) -> bool: ...


class StationaryProvider(Protocol):
    def sample(self) -> tuple[float, float, float]: ...


class EvidenceWriter(Protocol):
    def start_session(self, task: InspectionTask, session_id: str) -> str: ...
    def persist_capture(
        self,
        task: InspectionTask,
        point: InspectionPoint,
        capture_index: int,
        request_id: str,
        capture: CaptureResult,
        vision: VisionResult,
    ) -> None: ...
    def finish_session(
        self,
        task: InspectionTask,
        session_id: str,
        success: bool,
        error_code: int,
        message: str,
    ) -> None: ...


class InspectionExecutor:
    ERROR_NONE = 0
    ERROR_INVALID_TASK = 1
    ERROR_MAP_MISMATCH = 2
    ERROR_NAVIGATION = 3
    ERROR_NOT_STATIONARY = 4
    ERROR_GIMBAL = 5
    ERROR_CAPTURE = 6
    ERROR_INFERENCE = 7
    ERROR_CANCELED = 8
    ERROR_INTERNAL = 255

    def __init__(
        self,
        *,
        navigation: NavigationRunner,
        gimbal: GimbalRunner,
        camera: CameraRunner,
        vision: VisionRunner,
        stationary: StationaryProvider,
        evidence: EvidenceWriter,
        monotonic: Callable[[], float],
        sleep: Callable[[float], Awaitable[None]] = asyncio.sleep,
        stage_callback: Callable[[str], None] | None = None,
        stationary_poll_s: float = 0.05,
        stationary_sample_max_age_s: float = 0.5,
    ) -> None:
        self._navigation = navigation
        self._gimbal = gimbal
        self._camera = camera
        self._vision = vision
        self._stationary = stationary
        self._evidence = evidence
        self._monotonic = monotonic
        self._sleep = sleep
        self._stage_callback = stage_callback or (lambda _stage: None)
        self._stationary_poll_s = max(float(stationary_poll_s), 0.01)
        self._stationary_sample_max_age_s = max(float(stationary_sample_max_age_s), 0.01)
        self._cancel_requested = False
        self._active_child = ""

    async def cancel(self) -> bool:
        self._cancel_requested = True
        if self._active_child == "navigation":
            return bool(await self._navigation.cancel())
        if self._active_child == "gimbal":
            return bool(await self._gimbal.cancel())
        if self._active_child == "vision":
            return bool(await self._vision.cancel())
        return True

    async def execute(self, task: InspectionTask, session_id: str) -> InspectionResult:
        self._cancel_requested = False
        root = self._evidence.start_session(task, session_id)
        try:
            for point in task.points:
                if self._cancel_requested:
                    return self._finish(task, session_id, root, False, self.ERROR_CANCELED, "canceled")

                navigation = await self._retry_child(
                    "navigation", point.retry.navigation, lambda: self._navigation.run(point)
                )
                if not navigation.success:
                    error_code = (
                        self.ERROR_CANCELED
                        if navigation.error_code == self.ERROR_CANCELED
                        else self.ERROR_NAVIGATION
                    )
                    return self._finish(
                        task, session_id, root, False, error_code,
                        navigation.message or "navigation failed",
                    )

                if not await self._wait_stationary(point):
                    if self._cancel_requested:
                        return self._finish(task, session_id, root, False, self.ERROR_CANCELED, "canceled")
                    return self._finish(
                        task, session_id, root, False, self.ERROR_NOT_STATIONARY,
                        "robot did not remain stationary for the required window",
                    )

                gimbal = await self._retry_child(
                    "gimbal", point.retry.gimbal, lambda: self._gimbal.move(point)
                )
                if not gimbal.success:
                    error_code = (
                        self.ERROR_CANCELED
                        if gimbal.error_code == self.ERROR_CANCELED
                        else self.ERROR_GIMBAL
                    )
                    return self._finish(
                        task, session_id, root, False, error_code,
                        gimbal.message or "gimbal move failed",
                    )

                await self._sleep(point.gimbal.settle_duration_s)
                self._stage_callback("gimbal_settle")

                for capture_index in range(point.camera.capture_count):
                    capture = await self._retry_capture(point, capture_index)
                    if not capture.success:
                        error_code = (
                            self.ERROR_CANCELED
                            if capture.error_code == self.ERROR_CANCELED
                            else self.ERROR_CAPTURE
                        )
                        return self._finish(
                            task, session_id, root, False, error_code,
                            capture.message or "capture failed",
                        )

                    request_id = f"{session_id}:{point.id}:{capture_index}"
                    vision = await self._retry_vision(point, capture)
                    if not vision.success or vision.primary_confidence < point.vision.minimum_confidence:
                        error_code = (
                            self.ERROR_CANCELED
                            if vision.error_code == self.ERROR_CANCELED
                            else self.ERROR_INFERENCE
                        )
                        return self._finish(
                            task, session_id, root, False, error_code,
                            vision.message or "vision inference failed or below confidence threshold",
                        )

                    self._evidence.persist_capture(
                        task, point, capture_index, request_id, capture, vision
                    )
                    self._stage_callback("persist")

                    if capture_index + 1 < point.camera.capture_count:
                        await self._sleep(point.camera.capture_interval_s)

            return self._finish(task, session_id, root, True, self.ERROR_NONE, "inspection completed")
        except Exception as exc:  # execution boundary must fail closed
            return self._finish(task, session_id, root, False, self.ERROR_INTERNAL, str(exc))
        finally:
            self._active_child = ""

    def _finish(
        self,
        task: InspectionTask,
        session_id: str,
        root: str,
        success: bool,
        error_code: int,
        message: str,
    ) -> InspectionResult:
        self._evidence.finish_session(task, session_id, success, error_code, message)
        return InspectionResult(success, error_code, message, root)

    async def _retry_child(self, name: str, retries: int, operation) -> ChildResult:
        last = ChildResult(False, self.ERROR_INTERNAL, f"{name} not attempted")
        for _ in range(int(retries) + 1):
            if self._cancel_requested:
                return ChildResult(False, self.ERROR_CANCELED, "canceled")
            self._active_child = name
            self._stage_callback(name)
            last = await operation()
            self._active_child = ""
            if last.success:
                return last
        return last

    async def _retry_capture(self, point: InspectionPoint, capture_index: int) -> CaptureResult:
        last = CaptureResult(False, self.ERROR_CAPTURE, message="capture not attempted")
        for _ in range(point.retry.capture + 1):
            if self._cancel_requested:
                return CaptureResult(False, self.ERROR_CANCELED, message="canceled")
            self._stage_callback("capture")
            last = await self._camera.capture(point, capture_index)
            if last.success:
                return last
        return last

    async def _retry_vision(self, point: InspectionPoint, capture: CaptureResult) -> VisionResult:
        last = VisionResult(False, self.ERROR_INFERENCE, message="inference not attempted")
        for _ in range(point.retry.inference + 1):
            if self._cancel_requested:
                return VisionResult(False, self.ERROR_CANCELED, message="canceled")
            self._active_child = "vision"
            self._stage_callback("vision")
            last = await self._vision.inspect(point, capture)
            self._active_child = ""
            if last.success and last.primary_confidence >= point.vision.minimum_confidence:
                return last
        return last

    async def _wait_stationary(self, point: InspectionPoint) -> bool:
        deadline = self._monotonic() + point.stabilization.timeout_s
        stable_since = None
        while self._monotonic() <= deadline:
            if self._cancel_requested:
                return False
            now = self._monotonic()
            stamp, linear_x, angular_z = self._stationary.sample()
            fresh = 0.0 <= now - stamp <= self._stationary_sample_max_age_s
            under_limits = (
                abs(linear_x) <= point.stabilization.linear_velocity_max_mps
                and abs(angular_z) <= point.stabilization.angular_velocity_max_radps
            )
            if fresh and under_limits:
                if stable_since is None:
                    stable_since = now
                if now - stable_since >= point.stabilization.stable_duration_s:
                    self._stage_callback("stationary")
                    return True
            else:
                stable_since = None
            await self._sleep(self._stationary_poll_s)
        return False
