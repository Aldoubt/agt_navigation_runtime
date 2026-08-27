import copy

import pytest

from agt_inspection.schema import InspectionTaskError, canonical_hash, parse_inspection_task


HASH_A = "sha256:" + "1" * 64
HASH_B = "sha256:" + "2" * 64


def valid_v2_document():
    value = {
        "schema_version": 2,
        "inspection_task_id": "litchi_flower_route_01",
        "name": "Litchi flower multi-view route",
        "description": "One navigation stop, three ordered gimbal views",
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
                    "stable_duration_s": 0.8,
                    "timeout_s": 5.0,
                },
                "camera": {
                    "camera_id": "inspection_camera",
                    "capture_count": 1,
                    "capture_interval_s": 0.0,
                },
                "vision": {
                    "task_id": "litchi_flower_instance_seg",
                    "model_profile": "default",
                    "minimum_confidence": 0.6,
                    "timeout_s": 10.0,
                },
                "retry": {
                    "navigation": 1,
                    "gimbal": 1,
                    "capture": 2,
                    "inference": 1,
                },
                "aggregation": {
                    "enabled": True,
                    "aggregation_profile": "default",
                },
                "views": [
                    {
                        "id": "view_left",
                        "gimbal": {
                            "pan_rad": -0.5236,
                            "tilt_rad": -0.1745,
                            "timeout_s": 5.0,
                            "settle_duration_s": 0.5,
                        },
                    },
                    {
                        "id": "view_center",
                        "gimbal": {
                            "pan_rad": 0.0,
                            "tilt_rad": -0.1745,
                            "timeout_s": 5.0,
                            "settle_duration_s": 0.5,
                        },
                    },
                    {
                        "id": "view_right",
                        "gimbal": {
                            "pan_rad": 0.5236,
                            "tilt_rad": -0.1745,
                            "timeout_s": 5.0,
                            "settle_duration_s": 0.5,
                        },
                    },
                ],
            }
        ],
    }
    value["content_sha256"] = canonical_hash(value)
    return value


def test_schema_v2_parses_ordered_views_without_reinterpreting_capture_count():
    task = parse_inspection_task(valid_v2_document())
    point = task.points[0]

    assert task.schema_version == 2
    assert task.count_target == "litchi_flower"
    assert point.gimbal is None
    assert point.camera.capture_count == 1
    assert [view.id for view in point.views] == ["view_left", "view_center", "view_right"]
    assert [view.gimbal.pan_rad for view in point.views] == pytest.approx([-0.5236, 0.0, 0.5236])
    assert point.aggregation.enabled is True
    assert point.aggregation.aggregation_profile == "default"


def test_schema_v1_remains_supported_as_a_distinct_legacy_shape():
    from test_schema import valid_document

    task = parse_inspection_task(valid_document())
    assert task.schema_version == 1
    assert task.count_target == ""
    assert task.points[0].gimbal is not None
    assert task.points[0].views == ()
    assert task.points[0].aggregation is None


@pytest.mark.parametrize(
    "mutate, pattern",
    [
        (lambda value: value["points"][0]["views"].clear(), "views"),
        (
            lambda value: value["points"][0]["views"].append(
                copy.deepcopy(value["points"][0]["views"][0])
            ),
            "duplicate view id",
        ),
        (
            lambda value: value["points"][0]["camera"].__setitem__("capture_count", 2),
            "capture_count.*1",
        ),
        (
            lambda value: value.__setitem__("count_target", "bad/count"),
            "count_target",
        ),
        (
            lambda value: value["points"][0]["aggregation"].__setitem__(
                "aggregation_profile", ""
            ),
            "aggregation_profile",
        ),
    ],
)
def test_schema_v2_rejects_ambiguous_multiview_assets(mutate, pattern):
    value = valid_v2_document()
    mutate(value)
    value["content_sha256"] = canonical_hash(value)
    with pytest.raises(InspectionTaskError, match=pattern):
        parse_inspection_task(value)
