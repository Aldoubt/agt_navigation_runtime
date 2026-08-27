import copy
import math

import pytest

from agt_inspection.schema import InspectionTaskError, canonical_hash, parse_inspection_task


HASH_A = "sha256:" + "1" * 64
HASH_B = "sha256:" + "2" * 64


def valid_document():
    value = {
        "schema_version": 1,
        "inspection_task_id": "greenhouse_camera_route_01",
        "name": "Greenhouse camera route 01",
        "description": "Stop-and-inspect route",
        "revision": 1,
        "content_sha256": HASH_A,
        "map_binding": {
            "map_id": "greenhouse_01",
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
                    "stable_duration_s": 0.8,
                    "timeout_s": 5.0,
                },
                "gimbal": {
                    "pan_rad": 0.35,
                    "tilt_rad": -0.2,
                    "timeout_s": 5.0,
                    "settle_duration_s": 0.5,
                },
                "camera": {
                    "camera_id": "front_inspection",
                    "capture_count": 1,
                    "capture_interval_s": 0.0,
                },
                "vision": {
                    "task_id": "crop_disease_detection",
                    "model_profile": "default",
                    "minimum_confidence": 0.7,
                    "timeout_s": 10.0,
                },
                "retry": {
                    "navigation": 1,
                    "gimbal": 1,
                    "capture": 2,
                    "inference": 1,
                },
            }
        ],
    }
    value["content_sha256"] = canonical_hash(value)
    return value


def test_valid_task_parses_to_typed_model():
    task = parse_inspection_task(valid_document())
    assert task.inspection_task_id == "greenhouse_camera_route_01"
    assert task.revision == 1
    assert task.map_binding.map_id == "greenhouse_01"
    assert task.points[0].navigation.task_group_id == "inspection-P001-nav"
    assert task.points[0].camera.capture_count == 1
    assert task.points[0].vision.minimum_confidence == pytest.approx(0.7)


def test_hash_mismatch_and_invalid_hash_are_rejected():
    mismatch = valid_document()
    mismatch["name"] = "mutated without rehash"
    with pytest.raises(InspectionTaskError, match="content_sha256"):
        parse_inspection_task(mismatch)

    invalid = valid_document()
    invalid["content_sha256"] = "abc"
    with pytest.raises(InspectionTaskError, match="sha256"):
        parse_inspection_task(invalid)


def test_unknown_keys_and_duplicate_point_ids_are_rejected():
    unknown = valid_document()
    unknown["extra"] = True
    unknown["content_sha256"] = canonical_hash(unknown)
    with pytest.raises(InspectionTaskError, match="unknown"):
        parse_inspection_task(unknown)

    duplicate = valid_document()
    duplicate["points"].append(copy.deepcopy(duplicate["points"][0]))
    duplicate["content_sha256"] = canonical_hash(duplicate)
    with pytest.raises(InspectionTaskError, match="duplicate point id"):
        parse_inspection_task(duplicate)


@pytest.mark.parametrize(
    "mutate, pattern",
    [
        (lambda value: value["points"].clear(), "points"),
        (lambda value: value["points"][0]["camera"].__setitem__("capture_count", 0), "capture_count"),
        (lambda value: value["points"][0]["vision"].__setitem__("minimum_confidence", 1.1), "minimum_confidence"),
        (lambda value: value["points"][0]["gimbal"].__setitem__("pan_rad", math.inf), "pan_rad"),
        (lambda value: value["points"][0]["stabilization"].__setitem__("timeout_s", -1.0), "timeout_s"),
        (lambda value: value["points"][0]["retry"].__setitem__("capture", 11), "retry.capture"),
        (lambda value: value["points"][0]["navigation"].__setitem__("task_revision", 0), "task_revision"),
    ],
)
def test_invalid_numeric_or_bounded_values_are_rejected(mutate, pattern):
    value = valid_document()
    mutate(value)
    value["content_sha256"] = canonical_hash(value)
    with pytest.raises(InspectionTaskError, match=pattern):
        parse_inspection_task(value)
