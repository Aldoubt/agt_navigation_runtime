import asyncio

from agt_inspection.execution import CaptureResult, ChildResult
from agt_inspection.model import (
    AggregationPolicy,
    CameraPolicy,
    GimbalPose,
    InspectionPoint,
    InspectionTask,
    InspectionView,
    MapBinding,
    NavigationBinding,
    RetryPolicy,
    StabilizationPolicy,
    VisionPolicy,
)
from agt_inspection.multiview_execution import (
    MultiviewInspectionExecutor,
    ViewAcquireResult,
)


HASH = "sha256:" + "a" * 64


class Clock:
    def __init__(self):
        self.now = 1.0

    def monotonic(self):
        return self.now

    async def sleep(self, seconds):
        self.now += max(float(seconds), 0.01)
        await asyncio.sleep(0)


class Navigation:
    async def run(self, point):
        del point
        return ChildResult(True)

    async def cancel(self):
        return True


class Stationary:
    def __init__(self, clock):
        self.clock = clock

    def sample(self):
        return self.clock.monotonic(), 0.0, 0.0


class MustNotUseGimbal:
    async def move(self, point):
        del point
        raise AssertionError("atomic view backend must bypass legacy gimbal")

    async def cancel(self):
        raise AssertionError("atomic view backend must own cancellation")


class MustNotUseCamera:
    async def capture(self, point, capture_index, request_id):
        del point, capture_index, request_id
        raise AssertionError("atomic view backend must bypass legacy camera")


class MustNotUseVision:
    async def inspect(self, point, capture, request_id):
        del point, capture, request_id
        raise AssertionError("DEFERRED mode must not use online vision")

    async def cancel(self):
        return True


class AtomicAcquire:
    def __init__(self):
        self.calls = []
        self.cancel_calls = 0

    async def acquire(self, point, view, request_id):
        self.calls.append((point.id, view.id, request_id))
        return ViewAcquireResult(
            success=True,
            capture=CaptureResult(
                True,
                image_bytes=b"jpeg",
                image_uri="/tmp/P001_center.jpg",
                image_suffix=".jpg",
            ),
        )

    async def cancel(self):
        self.cancel_calls += 1
        return True


class Context:
    def snapshot(self, task, point, view, request_id):
        del task, point, view, request_id
        return {
            "capture_stamp": "100.400000000",
            "robot_pose_map": {"frame_id": "map", "x": 1.0, "y": 2.0, "z": 0.0, "yaw": 0.1},
            "gimbal": {
                "pan_rad": 0.02,
                "tilt_rad": -0.1,
                "roll_rad": 0.01,
                "feedback_valid": True,
            },
            "camera": {
                "camera_id": "inspection_camera",
                "calibration_id": "c1-v1",
                "calibration_sha256": HASH,
            },
            "camera_pose_valid": False,
            "camera_pose_map": {},
        }


class Evidence:
    def __init__(self):
        self.observations = []
        self.finished = None

    def start_session(self, session):
        del session
        return "/tmp/evidence"

    def write_view(self, point_id, view_id, observation, **kwargs):
        del point_id, view_id, kwargs
        self.observations.append(dict(observation))
        return "/tmp/evidence/result.json"

    def write_aggregation(self, *args, **kwargs):
        raise AssertionError("DEFERRED mode must not aggregate")

    def write_aggregation_failure(self, *args, **kwargs):
        raise AssertionError("DEFERRED mode must not aggregate")

    def build_report(self):
        return "/tmp/evidence/report/report.json"

    def finish_session(self, **kwargs):
        self.finished = dict(kwargs)


def _task():
    point = InspectionPoint(
        id="P001",
        navigation=NavigationBinding("P001-nav", 1, HASH),
        stabilization=StabilizationPolicy(0.02, 0.03, 0.05, 1.0),
        gimbal=None,
        camera=CameraPolicy("inspection_camera", 1, 0.0),
        vision=VisionPolicy("litchi_flower_instance_seg", "default", 0.6, 10.0, execution_mode="DEFERRED"),
        retry=RetryPolicy(0, 1, 2, 0),
        views=(InspectionView("center", GimbalPose(0.0, -0.1, 2.0, 0.5)),),
        aggregation=AggregationPolicy(True, "default"),
    )
    return InspectionTask(
        inspection_task_id="field_capture",
        name="field capture",
        description="",
        revision=1,
        content_sha256=HASH,
        map_binding=MapBinding("orchard", "v1", HASH),
        points=(point,),
        count_target="litchi_flower",
        schema_version=2,
    )


def test_atomic_view_backend_bypasses_separate_gimbal_camera_and_settle():
    clock = Clock()
    atomic = AtomicAcquire()
    evidence = Evidence()
    executor = MultiviewInspectionExecutor(
        navigation=Navigation(),
        gimbal=MustNotUseGimbal(),
        camera=MustNotUseCamera(),
        vision=MustNotUseVision(),
        stationary=Stationary(clock),
        evidence_store=evidence,
        aggregator=None,
        context_provider=Context(),
        view_acquirer=atomic,
        monotonic=clock.monotonic,
        sleep=clock.sleep,
        poll_period_s=0.01,
    )

    result = asyncio.run(executor.execute(_task(), session_id="session01"))

    assert result.success is True
    assert atomic.calls == [("P001", "center", "session01:P001:center")]
    assert evidence.observations[0]["vision_status"] == "PENDING_OFFLINE"
    assert evidence.observations[0]["gimbal"]["feedback_valid"] is True
    # Vendor AcquireView owns settle_time. The executor must not sleep another 0.5 s.
    assert clock.now < 1.2


class RetryAtomicAcquire:
    def __init__(self):
        self.calls = 0

    async def acquire(self, point, view, request_id):
        del point, view, request_id
        self.calls += 1
        if self.calls == 1:
            return ViewAcquireResult(False, error_code=5, message="gimbal transient")
        return ViewAcquireResult(
            True,
            capture=CaptureResult(True, image_bytes=b"jpeg", image_suffix=".jpg"),
        )

    async def cancel(self):
        return True


def test_atomic_view_backend_uses_task_owned_stage_retry_budget():
    clock = Clock()
    atomic = RetryAtomicAcquire()
    executor = MultiviewInspectionExecutor(
        navigation=Navigation(),
        gimbal=MustNotUseGimbal(),
        camera=MustNotUseCamera(),
        vision=MustNotUseVision(),
        stationary=Stationary(clock),
        evidence_store=Evidence(),
        aggregator=None,
        context_provider=Context(),
        view_acquirer=atomic,
        monotonic=clock.monotonic,
        sleep=clock.sleep,
        poll_period_s=0.01,
    )

    result = asyncio.run(executor.execute(_task(), session_id="session02"))
    assert result.success is True
    assert atomic.calls == 2
