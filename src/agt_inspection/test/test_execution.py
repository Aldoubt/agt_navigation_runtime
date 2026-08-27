import asyncio
from dataclasses import dataclass

from agt_inspection.execution import (
    CaptureResult,
    ChildResult,
    InspectionExecutor,
    VisionResult,
)
from agt_inspection.model import (
    CameraPolicy,
    GimbalPose,
    InspectionPoint,
    InspectionTask,
    MapBinding,
    NavigationBinding,
    RetryPolicy,
    StabilizationPolicy,
    VisionPolicy,
)


def _point(**overrides):
    values = dict(
        id="P001",
        navigation=NavigationBinding("nav_P001", 1, "sha256:" + "1" * 64),
        stabilization=StabilizationPolicy(0.02, 0.03, 0.10, 0.50),
        gimbal=GimbalPose(0.2, -0.1, 1.0, 0.05),
        camera=CameraPolicy("front", 1, 0.0),
        vision=VisionPolicy("crop_detect", "default", 0.70, 1.0),
        retry=RetryPolicy(1, 1, 1, 1),
    )
    values.update(overrides)
    return InspectionPoint(**values)


def _task(point=None):
    return InspectionTask(
        inspection_task_id="inspection_001",
        name="inspection",
        description="test",
        revision=1,
        content_sha256="sha256:" + "2" * 64,
        map_binding=MapBinding("map_01", "v1", "sha256:" + "3" * 64),
        points=(point or _point(),),
    )


class FakeNavigation:
    def __init__(self, events, results=None):
        self.events = events
        self.results = list(results or [ChildResult(True)])
        self.cancel_calls = 0

    async def run(self, point):
        self.events.append("navigate")
        return self.results.pop(0)

    async def cancel(self):
        self.cancel_calls += 1
        self.events.append("cancel_navigation")
        return True


class FakeGimbal:
    def __init__(self, events):
        self.events = events
        self.cancel_calls = 0

    async def move(self, point):
        self.events.append("gimbal")
        return ChildResult(True)

    async def cancel(self):
        self.cancel_calls += 1
        self.events.append("cancel_gimbal")
        return True


class FakeCamera:
    def __init__(self, events):
        self.events = events

    async def capture(self, point, capture_index):
        self.events.append("capture")
        return CaptureResult(True, image_payload=b"frame")


class FakeVision:
    def __init__(self, events, confidence=0.93):
        self.events = events
        self.confidence = confidence
        self.cancel_calls = 0

    async def inspect(self, point, capture):
        self.events.append("vision")
        return VisionResult(
            True,
            model_id="mock-vision",
            model_version="1",
            inference_time_ms=5.0,
            primary_confidence=self.confidence,
            result_json='{"class":"test_target"}',
        )

    async def cancel(self):
        self.cancel_calls += 1
        self.events.append("cancel_vision")
        return True


class FakeStationary:
    def __init__(self, clock, linear=0.0, angular=0.0, stale=False):
        self.clock = clock
        self.linear = linear
        self.angular = angular
        self.stale = stale

    def sample(self):
        stamp = self.clock.now - (1.0 if self.stale else 0.0)
        return stamp, self.linear, self.angular


class FakeClock:
    def __init__(self):
        self.now = 10.0

    def __call__(self):
        return self.now

    async def sleep(self, duration):
        self.now += max(float(duration), 0.01)


class FakeEvidence:
    def __init__(self, events):
        self.events = events
        self.records = []

    def start_session(self, task, session_id):
        return "runtime/inspections/" + session_id

    def persist_capture(self, task, point, capture_index, request_id, capture, vision):
        self.events.append("persist")
        self.records.append((point.id, capture_index, request_id))

    def finish_session(self, task, session_id, success, error_code, message):
        pass


def _executor(events, stationary=None, navigation=None, vision=None):
    clock = FakeClock()
    return InspectionExecutor(
        navigation=navigation or FakeNavigation(events),
        gimbal=FakeGimbal(events),
        camera=FakeCamera(events),
        vision=vision or FakeVision(events),
        stationary=stationary or FakeStationary(clock),
        evidence=FakeEvidence(events),
        monotonic=clock,
        sleep=clock.sleep,
        stationary_poll_s=0.05,
    )


def test_single_point_order_requires_stationary_before_capture():
    events = []
    executor = _executor(events)
    result = asyncio.run(executor.execute(_task(), "session_01"))
    assert result.success is True
    assert events == [
        "navigate",
        "stationary",
        "gimbal",
        "gimbal_settle",
        "capture",
        "vision",
        "persist",
    ]


def test_unstable_robot_never_reaches_capture():
    events = []
    clock = FakeClock()
    executor = InspectionExecutor(
        navigation=FakeNavigation(events),
        gimbal=FakeGimbal(events),
        camera=FakeCamera(events),
        vision=FakeVision(events),
        stationary=FakeStationary(clock, linear=0.20),
        evidence=FakeEvidence(events),
        monotonic=clock,
        sleep=clock.sleep,
        stationary_poll_s=0.05,
    )
    result = asyncio.run(executor.execute(_task(), "session_02"))
    assert result.success is False
    assert result.error_code == InspectionExecutor.ERROR_NOT_STATIONARY
    assert "capture" not in events
    assert "vision" not in events


def test_stale_stationary_sample_is_rejected():
    events = []
    clock = FakeClock()
    executor = InspectionExecutor(
        navigation=FakeNavigation(events),
        gimbal=FakeGimbal(events),
        camera=FakeCamera(events),
        vision=FakeVision(events),
        stationary=FakeStationary(clock, stale=True),
        evidence=FakeEvidence(events),
        monotonic=clock,
        sleep=clock.sleep,
        stationary_poll_s=0.05,
    )
    result = asyncio.run(executor.execute(_task(), "session_03"))
    assert result.success is False
    assert result.error_code == InspectionExecutor.ERROR_NOT_STATIONARY
    assert "capture" not in events


def test_navigation_retry_is_finite_and_then_succeeds():
    events = []
    nav = FakeNavigation(events, [ChildResult(False, 3, "retry"), ChildResult(True)])
    executor = _executor(events, navigation=nav)
    result = asyncio.run(executor.execute(_task(), "session_04"))
    assert result.success is True
    assert events.count("navigate") == 2


def test_low_confidence_never_persists_evidence():
    events = []
    vision = FakeVision(events, confidence=0.1)
    executor = _executor(events, vision=vision)
    result = asyncio.run(executor.execute(_task(), "session_05"))
    assert result.success is False
    assert result.error_code == InspectionExecutor.ERROR_INFERENCE
    assert events.count("vision") == 2
    assert "persist" not in events
