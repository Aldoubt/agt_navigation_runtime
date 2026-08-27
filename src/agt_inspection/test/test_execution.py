import asyncio
import json

from agt_inspection.evidence import EvidenceWriter
from agt_inspection.execution import (
    CaptureResult,
    ChildResult,
    InspectionErrorCode,
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


class FakeClock:
    def __init__(self):
        self.now = 100.0

    def monotonic(self):
        return self.now

    async def sleep(self, seconds):
        self.now += max(float(seconds), 0.001)
        await asyncio.sleep(0)


class StaticStationaryProvider:
    def __init__(self, clock, linear=0.0, angular=0.0, stale=False):
        self.clock = clock
        self.linear = linear
        self.angular = angular
        self.stale = stale

    def sample(self):
        stamp = self.clock.monotonic() - (2.0 if self.stale else 0.0)
        return stamp, self.linear, self.angular


class FakeNavigation:
    def __init__(self, events, fail_count=0):
        self.events = events
        self.fail_count = fail_count
        self.calls = 0
        self.cancel_calls = 0
        self.block = False
        self._cancelled = False

    async def run(self, point):
        self.events.append("navigate")
        self.calls += 1
        if self.block:
            while not self._cancelled:
                await asyncio.sleep(0)
            return ChildResult(False, canceled=True, cancel_confirmed=True, message="canceled")
        if self.calls <= self.fail_count:
            return ChildResult(False, error_code=3, message="nav failed")
        return ChildResult(True)

    async def cancel(self):
        self.cancel_calls += 1
        self._cancelled = True
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
        return True


class FakeCamera:
    def __init__(self, events, fail_count=0):
        self.events = events
        self.fail_count = fail_count
        self.calls = 0

    async def capture(self, point, capture_index, request_id):
        self.events.append("capture")
        self.calls += 1
        if self.calls <= self.fail_count:
            return CaptureResult(False, error_code=6, message="capture failed")
        return CaptureResult(True, image_bytes=b"mock-image", image_uri="")


class FakeVision:
    def __init__(self, events, confidence=0.93):
        self.events = events
        self.confidence = confidence
        self.cancel_calls = 0

    async def inspect(self, point, capture, request_id):
        self.events.append("vision")
        return VisionResult(
            True,
            model_id="mock-vision",
            model_version="1",
            inference_time_ms=5.0,
            primary_confidence=self.confidence,
            result_json='{"class":"test_target","confidence":0.93}',
        )

    async def cancel(self):
        self.cancel_calls += 1
        return True


def point(retry=None):
    return InspectionPoint(
        id="P001",
        navigation=NavigationBinding("inspection-P001-nav", 1, "sha256:" + "1" * 64),
        stabilization=StabilizationPolicy(0.02, 0.03, 0.3, 1.0),
        gimbal=GimbalPose(0.2, -0.1, 1.0, 0.2),
        camera=CameraPolicy("front_inspection", 1, 0.0),
        vision=VisionPolicy("crop_disease_detection", "default", 0.7, 1.0),
        retry=retry or RetryPolicy(0, 0, 0, 0),
    )


def task(the_point=None):
    return InspectionTask(
        inspection_task_id="inspection_01",
        name="Inspection",
        description="",
        revision=1,
        content_sha256="sha256:" + "a" * 64,
        map_binding=MapBinding("greenhouse_01", "v1", "sha256:" + "b" * 64),
        points=(the_point or point(),),
    )


def executor(tmp_path, *, stationary=None, navigation=None, camera=None, vision=None):
    events = []
    stages = []
    clock = FakeClock()
    nav = navigation or FakeNavigation(events)
    cam = camera or FakeCamera(events)
    vis = vision or FakeVision(events)
    instance = InspectionExecutor(
        navigation=nav,
        gimbal=FakeGimbal(events),
        camera=cam,
        vision=vis,
        stationary=stationary or StaticStationaryProvider(clock),
        evidence=EvidenceWriter(tmp_path),
        stage_callback=lambda stage, _point_id: stages.append(stage),
        monotonic=clock.monotonic,
        sleep=clock.sleep,
        poll_period_s=0.1,
        stationary_freshness_s=0.5,
    )
    return instance, events, stages, nav, cam, vis, clock


def test_capture_is_gated_by_stationary_and_gimbal_settle_and_persists_evidence(tmp_path):
    instance, events, stages, *_ = executor(tmp_path)
    result = asyncio.run(instance.execute(task(), session_id="session_01"))

    assert result.success is True
    assert events == ["navigate", "gimbal", "capture", "vision"]
    assert stages == [
        "NAVIGATING",
        "WAITING_ROBOT_STABLE",
        "MOVING_GIMBAL",
        "WAITING_GIMBAL_STABLE",
        "CAPTURING",
        "INFERENCING",
        "SAVING_RESULT",
    ]
    result_path = tmp_path / "inspection_01" / "session_01" / "P001" / "capture_0001.result.json"
    assert result_path.is_file()
    payload = json.loads(result_path.read_text(encoding="utf-8"))
    assert payload["model_id"] == "mock-vision"
    assert payload["primary_confidence"] == 0.93


def test_unstable_or_stale_odometry_fails_before_gimbal_and_capture(tmp_path):
    for stale, linear in ((False, 0.2), (True, 0.0)):
        clock = FakeClock()
        stationary = StaticStationaryProvider(clock, linear=linear, stale=stale)
        events = []
        instance = InspectionExecutor(
            navigation=FakeNavigation(events),
            gimbal=FakeGimbal(events),
            camera=FakeCamera(events),
            vision=FakeVision(events),
            stationary=stationary,
            evidence=EvidenceWriter(tmp_path / ("stale" if stale else "moving")),
            monotonic=clock.monotonic,
            sleep=clock.sleep,
            poll_period_s=0.1,
        )
        result = asyncio.run(instance.execute(task(), session_id="session"))
        assert result.success is False
        assert result.error_code == InspectionErrorCode.NOT_STATIONARY
        assert events == ["navigate"]


def test_capture_retry_budget_is_finite(tmp_path):
    events = []
    clock = FakeClock()
    camera = FakeCamera(events, fail_count=1)
    instance = InspectionExecutor(
        navigation=FakeNavigation(events),
        gimbal=FakeGimbal(events),
        camera=camera,
        vision=FakeVision(events),
        stationary=StaticStationaryProvider(clock),
        evidence=EvidenceWriter(tmp_path),
        monotonic=clock.monotonic,
        sleep=clock.sleep,
        poll_period_s=0.1,
    )
    result = asyncio.run(
        instance.execute(
            task(point(RetryPolicy(0, 0, 1, 0))),
            session_id="session_retry",
        )
    )
    assert result.success is True
    assert camera.calls == 2


def test_cancel_confirms_active_navigation_child_before_returning(tmp_path):
    async def scenario():
        events = []
        clock = FakeClock()
        navigation = FakeNavigation(events)
        navigation.block = True
        instance = InspectionExecutor(
            navigation=navigation,
            gimbal=FakeGimbal(events),
            camera=FakeCamera(events),
            vision=FakeVision(events),
            stationary=StaticStationaryProvider(clock),
            evidence=EvidenceWriter(tmp_path),
            monotonic=clock.monotonic,
            sleep=clock.sleep,
            poll_period_s=0.01,
        )
        running = asyncio.create_task(instance.execute(task(), session_id="session_cancel"))
        while not events:
            await asyncio.sleep(0)
        instance.request_cancel()
        result = await running
        return result, navigation

    result, navigation = asyncio.run(scenario())
    assert result.canceled is True
    assert result.error_code == InspectionErrorCode.CANCELED
    assert navigation.cancel_calls == 1
