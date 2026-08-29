import asyncio
import json

import pytest

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
from agt_inspection.multiview_evidence import InspectionEvidenceStore
from agt_inspection.multiview_execution import MultiviewInspectionExecutor
from agt_inspection.schema import InspectionTaskError, canonical_hash, parse_inspection_task


HASH_A = "sha256:" + "a" * 64
HASH_B = "sha256:" + "b" * 64


def _document(execution_mode=None):
    vision = {
        "task_id": "litchi_flower_instance_seg",
        "model_profile": "default",
        "minimum_confidence": 0.6,
        "timeout_s": 10.0,
    }
    if execution_mode is not None:
        vision["execution_mode"] = execution_mode
    value = {
        "schema_version": 2,
        "inspection_task_id": "litchi_route_deferred",
        "name": "Deferred litchi capture",
        "description": "capture first, infer later",
        "revision": 1,
        "content_sha256": HASH_A,
        "count_target": "litchi_flower",
        "map_binding": {
            "map_id": "orchard_01",
            "map_version_id": "v1",
            "manifest_sha256": HASH_B,
        },
        "points": [
            {
                "id": "P001",
                "navigation": {
                    "task_group_id": "inspection-P001-nav",
                    "task_revision": 1,
                    "expected_content_sha256": HASH_A,
                },
                "stabilization": {
                    "linear_velocity_max_mps": 0.02,
                    "angular_velocity_max_radps": 0.03,
                    "stable_duration_s": 0.1,
                    "timeout_s": 2.0,
                },
                "camera": {
                    "camera_id": "inspection_camera",
                    "capture_count": 1,
                    "capture_interval_s": 0.0,
                },
                "vision": vision,
                "retry": {
                    "navigation": 0,
                    "gimbal": 0,
                    "capture": 0,
                    "inference": 0,
                },
                "aggregation": {
                    "enabled": True,
                    "aggregation_profile": "default",
                },
                "views": [
                    {
                        "id": "center",
                        "gimbal": {
                            "pan_rad": 0.0,
                            "tilt_rad": -0.1,
                            "timeout_s": 2.0,
                            "settle_duration_s": 0.0,
                        },
                    }
                ],
            }
        ],
    }
    value["content_sha256"] = canonical_hash(value)
    return value


def test_missing_execution_mode_remains_inline_for_compatibility():
    task = parse_inspection_task(_document())
    assert task.points[0].vision.execution_mode == "INLINE"


def test_explicit_deferred_mode_is_parsed_and_invalid_mode_is_rejected():
    task = parse_inspection_task(_document("DEFERRED"))
    assert task.points[0].vision.execution_mode == "DEFERRED"

    bad = _document("BACKGROUND_MAGIC")
    with pytest.raises(InspectionTaskError, match="execution_mode"):
        parse_inspection_task(bad)


class Clock:
    def __init__(self):
        self.now = 10.0

    def monotonic(self):
        return self.now

    async def sleep(self, seconds):
        self.now += max(float(seconds), 0.01)
        await asyncio.sleep(0)


class Stationary:
    def __init__(self, clock):
        self.clock = clock

    def sample(self):
        return self.clock.monotonic(), 0.0, 0.0


class Navigation:
    async def run(self, point):
        del point
        return ChildResult(True)

    async def cancel(self):
        return True


class Gimbal:
    async def move(self, point):
        del point
        return ChildResult(True)

    async def cancel(self):
        return True


class Camera:
    async def capture(self, point, capture_index, request_id):
        del point, capture_index, request_id
        return CaptureResult(True, image_bytes=b"jpeg", image_suffix=".jpg")


class VisionMustNotRun:
    def __init__(self):
        self.calls = 0

    async def inspect(self, point, capture, request_id):
        del point, capture, request_id
        self.calls += 1
        raise AssertionError("DEFERRED mode must not call online vision")

    async def cancel(self):
        return True


class AggregatorMustNotRun:
    def __init__(self):
        self.calls = 0

    async def aggregate(self, task, point, observations):
        del task, point, observations
        self.calls += 1
        raise AssertionError("DEFERRED mode must not run view aggregation")

    async def cancel(self):
        return True


class Context:
    def snapshot(self, task, point, view, request_id):
        del task, request_id
        return {
            "capture_stamp": "2026-08-30T08:00:00.123+08:00",
            "robot_pose_map": {
                "x": 1.2,
                "y": 3.4,
                "z": 0.0,
                "yaw": 0.5,
            },
            "gimbal": {
                "pan_rad": 0.012,
                "tilt_rad": -0.095,
                "feedback_valid": True,
            },
            "camera": {
                "camera_id": point.camera.camera_id,
                "calibration_id": "c1_calib_v1",
                "calibration_sha256": HASH_B,
            },
            "camera_pose_valid": False,
            "camera_pose_map": {},
        }


def _task_deferred():
    return InspectionTask(
        inspection_task_id="litchi_route_deferred",
        name="Deferred litchi capture",
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
                stabilization=StabilizationPolicy(0.02, 0.03, 0.1, 2.0),
                gimbal=None,
                camera=CameraPolicy("inspection_camera", 1, 0.0),
                vision=VisionPolicy(
                    "litchi_flower_instance_seg",
                    "default",
                    0.6,
                    10.0,
                    execution_mode="DEFERRED",
                ),
                retry=RetryPolicy(0, 0, 0, 0),
                views=(InspectionView("center", GimbalPose(0.0, -0.1, 2.0, 0.0)),),
                aggregation=AggregationPolicy(True, "default"),
            ),
        ),
    )


def test_deferred_capture_succeeds_without_vision_or_aggregation_and_does_not_fake_counts(tmp_path):
    clock = Clock()
    vision = VisionMustNotRun()
    aggregator = AggregatorMustNotRun()
    executor = MultiviewInspectionExecutor(
        navigation=Navigation(),
        gimbal=Gimbal(),
        camera=Camera(),
        vision=vision,
        stationary=Stationary(clock),
        evidence_store=InspectionEvidenceStore(tmp_path),
        aggregator=aggregator,
        context_provider=Context(),
        monotonic=clock.monotonic,
        sleep=clock.sleep,
        poll_period_s=0.01,
    )

    result = asyncio.run(executor.execute(_task_deferred(), session_id="session_deferred"))

    assert result.success is True
    assert vision.calls == 0
    assert aggregator.calls == 0

    root = tmp_path / "litchi_route_deferred" / "session_deferred"
    observation = json.loads(
        (root / "points" / "P001" / "center" / "result.json").read_text(encoding="utf-8")
    )
    assert observation["vision_status"] == "PENDING_OFFLINE"
    assert "raw_count" not in observation["vision"]
    assert observation["robot_pose_map"]["x"] == 1.2
    assert observation["gimbal"]["pan_rad"] == 0.012

    report = json.loads((root / "report" / "report.json").read_text(encoding="utf-8"))
    assert report["count_mode"] == "PENDING_OFFLINE"
    assert report["totals"]["raw_instance_count"] is None
    assert report["totals"]["unique_instance_count"] is None
    assert report["points"][0]["raw_instance_count"] is None
