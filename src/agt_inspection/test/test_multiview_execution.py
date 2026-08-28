import asyncio
import json

from agt_inspection.execution import CaptureResult, ChildResult, VisionResult
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
from agt_inspection.multiview_evidence import InspectionEvidenceStore
from agt_inspection.multiview_execution import (
    AggregationResult,
    MultiviewInspectionExecutor,
)


HASH_A = "sha256:" + "a" * 64
HASH_B = "sha256:" + "b" * 64
HASH_C = "sha256:" + "c" * 64


class FakeClock:
    def __init__(self):
        self.now = 100.0

    def monotonic(self):
        return self.now

    async def sleep(self, seconds):
        self.now += max(float(seconds), 0.001)
        await asyncio.sleep(0)


class Stationary:
    def __init__(self, clock):
        self.clock = clock

    def sample(self):
        return self.clock.monotonic(), 0.0, 0.0


class Navigation:
    def __init__(self, events):
        self.events = events
        self.calls = 0

    async def run(self, point):
        self.calls += 1
        self.events.append(("navigate", point.id))
        return ChildResult(True)

    async def cancel(self):
        return True


class Gimbal:
    def __init__(self, events):
        self.events = events

    async def move(self, point):
        self.events.append(("gimbal", point.id, point.gimbal.pan_rad))
        return ChildResult(True)

    async def cancel(self):
        return True


class Camera:
    def __init__(self, events):
        self.events = events

    async def capture(self, point, capture_index, request_id):
        self.events.append(("capture", request_id))
        return CaptureResult(True, image_bytes=b"rgb-pixels", image_uri="")


class Vision:
    def __init__(self, events, *, fail_view=""):
        self.events = events
        self.fail_view = fail_view

    async def inspect(self, point, capture, request_id):
        del point, capture
        self.events.append(("vision", request_id))
        if self.fail_view and self.fail_view in request_id:
            return VisionResult(False, message="single-view inference failed")
        raw_count = {"view_left": 2, "view_center": 3, "view_right": 1}.get(
            request_id.rsplit(":", 1)[-1], 1
        )
        return VisionResult(
            True,
            model_id="mock-flower-seg",
            model_version="1",
            inference_time_ms=5.0,
            primary_confidence=0.93,
            result_json=json.dumps(
                {
                    "raw_count": raw_count,
                    "instances": [
                        {"local_instance_id": f"I{index + 1:04d}"}
                        for index in range(raw_count)
                    ],
                }
            ),
        )

    async def cancel(self):
        return True


class VisualVision(Vision):
    async def inspect(self, point, capture, request_id):
        del point, capture
        self.events.append(("vision", request_id))
        return VisionResult(
            True,
            model_id="mock-flower-seg",
            model_version="1",
            weights_sha256=HASH_A,
            inference_time_ms=5.0,
            primary_confidence=0.93,
            result_json=json.dumps(
                {
                    "raw_count": 1,
                    "instances": [{"local_instance_id": "I0001"}],
                }
            ),
            overlay_bytes=b"overlay-jpeg-bytes",
            mask_bytes=b"mask-png-bytes",
        )


class ContextProvider:
    def snapshot(self, task, point, view, request_id):
        del request_id
        return {
            "capture_stamp": "2026-08-28T10:32:12.351+08:00",
            "robot_pose_map": {"x": 12.3, "y": 4.8, "z": 0.0, "yaw": 1.57},
            "gimbal": {
                "pan_rad": view.gimbal.pan_rad,
                "tilt_rad": view.gimbal.tilt_rad,
                "feedback_valid": True,
            },
            "camera": {
                "camera_id": point.camera.camera_id,
                "calibration_id": "camera_calib_v1",
                "calibration_sha256": HASH_C,
            },
            "camera_pose_valid": False,
            "camera_pose_map": {},
        }


class Aggregator:
    def __init__(self, *, fail=False):
        self.fail = fail
        self.calls = []

    async def aggregate(self, task, point, observations):
        self.calls.append((task.inspection_task_id, point.id, [item["view_id"] for item in observations]))
        if self.fail:
            return AggregationResult(False, error_code=5, message="association unavailable")
        return AggregationResult(
            True,
            aggregator_id="mock-association",
            aggregator_version="1",
            raw_instance_count=6,
            unique_instance_count=4,
            ambiguous_instance_count=1,
            association_confidence=0.9,
            result_json=json.dumps(
                {
                    "global_instances": [
                        {
                            "global_instance_id": "G0001",
                            "status": "MATCHED",
                            "association_confidence": 0.92,
                            "members": [
                                {"view_id": "view_left", "local_instance_id": "I0001"},
                                {"view_id": "view_center", "local_instance_id": "I0001"},
                            ],
                        }
                    ],
                    "warnings": [],
                }
            ),
        )

    async def cancel(self):
        return True


def task():
    return InspectionTask(
        inspection_task_id="litchi_flower_route_01",
        name="Litchi flower route",
        description="",
        revision=1,
        content_sha256=HASH_A,
        map_binding=MapBinding("orchard_01", "v1", HASH_B),
        count_target="litchi_flower",
        schema_version=2,
        points=(
            InspectionPoint(
                id="P001",
                navigation=NavigationBinding("inspection-P001-nav", 1, HASH_A),
                stabilization=StabilizationPolicy(0.02, 0.03, 0.2, 2.0),
                gimbal=None,
                camera=CameraPolicy("inspection_camera", 1, 0.0),
                vision=VisionPolicy("litchi_flower_instance_seg", "default", 0.6, 10.0),
                retry=RetryPolicy(0, 0, 0, 0),
                views=(
                    InspectionView("view_left", GimbalPose(-0.5, -0.1, 2.0, 0.1)),
                    InspectionView("view_center", GimbalPose(0.0, -0.1, 2.0, 0.1)),
                    InspectionView("view_right", GimbalPose(0.5, -0.1, 2.0, 0.1)),
                ),
                aggregation=AggregationPolicy(True, "default"),
            ),
        ),
    )


def make_executor(tmp_path, *, aggregator=None, vision=None):
    events = []
    stages = []
    clock = FakeClock()
    nav = Navigation(events)
    agg = aggregator or Aggregator()
    executor = MultiviewInspectionExecutor(
        navigation=nav,
        gimbal=Gimbal(events),
        camera=Camera(events),
        vision=vision or Vision(events),
        stationary=Stationary(clock),
        evidence_store=InspectionEvidenceStore(tmp_path),
        aggregator=agg,
        context_provider=ContextProvider(),
        monotonic=clock.monotonic,
        sleep=clock.sleep,
        poll_period_s=0.05,
        stage_callback=lambda stage, point_id: stages.append((stage, point_id)),
    )
    return executor, events, stages, nav, agg


def test_one_navigation_stop_executes_all_ordered_views_then_point_local_aggregation(tmp_path):
    executor, events, stages, nav, aggregator = make_executor(tmp_path)
    result = asyncio.run(executor.execute(task(), session_id="session_001"))

    assert result.success is True
    assert nav.calls == 1
    assert [event[2] for event in events if event[0] == "gimbal"] == [-0.5, 0.0, 0.5]
    assert len([event for event in events if event[0] == "capture"]) == 3
    assert len([event for event in events if event[0] == "vision"]) == 3
    assert aggregator.calls == [
        ("litchi_flower_route_01", "P001", ["view_left", "view_center", "view_right"])
    ]
    assert ("AGGREGATING_VIEWS", "P001") in stages

    report_path = (
        tmp_path
        / "litchi_flower_route_01"
        / "session_001"
        / "report"
        / "report.json"
    )
    report = json.loads(report_path.read_text(encoding="utf-8"))
    assert report["count_mode"] == "POINT_DEDUP"
    assert report["totals"] == {
        "raw_instance_count": 6,
        "unique_instance_count": 4,
        "ambiguous_instance_count": 1,
    }


def test_visual_evidence_bytes_and_model_hash_are_handed_to_store(tmp_path):
    events = []
    executor, _, _, _, _ = make_executor(tmp_path, vision=VisualVision(events))

    result = asyncio.run(executor.execute(task(), session_id="session_visual"))

    assert result.success is True
    view_root = (
        tmp_path
        / "litchi_flower_route_01"
        / "session_visual"
        / "points"
        / "P001"
        / "view_left"
    )
    assert (view_root / "overlay.bin").read_bytes() == b"overlay-jpeg-bytes"
    assert (view_root / "mask.bin").read_bytes() == b"mask-png-bytes"
    payload = json.loads((view_root / "result.json").read_text(encoding="utf-8"))
    assert payload["vision"]["weights_sha256"] == HASH_A


def test_aggregation_failure_is_nonblocking_and_preserves_level1_view_raw_report(tmp_path):
    executor, _, stages, _, aggregator = make_executor(tmp_path, aggregator=Aggregator(fail=True))
    result = asyncio.run(executor.execute(task(), session_id="session_raw_only"))

    assert result.success is True
    assert len(aggregator.calls) == 1
    assert ("AGGREGATION_FAILED_NONBLOCKING", "P001") in stages

    report_path = (
        tmp_path
        / "litchi_flower_route_01"
        / "session_raw_only"
        / "report"
        / "report.json"
    )
    report = json.loads(report_path.read_text(encoding="utf-8"))
    assert report["count_mode"] == "VIEW_RAW"
    assert report["totals"]["raw_instance_count"] == 6
    assert report["totals"]["unique_instance_count"] is None


def test_single_view_failure_blocks_point_before_aggregation(tmp_path):
    events = []
    failing_vision = Vision(events, fail_view="view_center")
    executor, _, _, _, aggregator = make_executor(tmp_path, vision=failing_vision)
    result = asyncio.run(executor.execute(task(), session_id="session_level1_fail"))

    assert result.success is False
    assert result.error_code == executor.ERROR_INFERENCE
    assert aggregator.calls == []
