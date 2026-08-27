import json

import pytest

from agt_inspection.repository import InspectionRepository
from agt_inspection.schema import InspectionTaskError, canonical_hash


HASH_A = "sha256:" + "1" * 64
HASH_B = "sha256:" + "2" * 64


def _valid_document():
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


def _write_task(root, document):
    path = (
        root
        / document["map_binding"]["map_id"]
        / "versions"
        / document["map_binding"]["map_version_id"]
        / "inspections"
        / f'{document["inspection_task_id"]}.json'
    )
    path.parent.mkdir(parents=True)
    path.write_text(json.dumps(document), encoding="utf-8")
    return path


def test_repository_loads_exact_map_revision_and_hash(tmp_path):
    document = _valid_document()
    _write_task(tmp_path, document)
    repo = InspectionRepository(tmp_path, "greenhouse_01", "v1")

    task = repo.load(
        "greenhouse_camera_route_01",
        expected_revision=1,
        expected_content_sha256=document["content_sha256"],
    )
    assert task.map_binding.map_id == "greenhouse_01"
    assert task.map_binding.map_version_id == "v1"


def test_repository_rejects_revision_hash_and_internal_map_mismatch(tmp_path):
    document = _valid_document()
    _write_task(tmp_path, document)
    repo = InspectionRepository(tmp_path, "greenhouse_01", "v1")

    with pytest.raises(InspectionTaskError, match="revision"):
        repo.load("greenhouse_camera_route_01", expected_revision=2)
    with pytest.raises(InspectionTaskError, match="content hash"):
        repo.load(
            "greenhouse_camera_route_01",
            expected_content_sha256="sha256:" + "f" * 64,
        )

    mismatched = _valid_document()
    mismatched["map_binding"]["map_version_id"] = "v2"
    mismatched["content_sha256"] = canonical_hash(mismatched)
    expected_path = (
        tmp_path
        / "greenhouse_01"
        / "versions"
        / "v1"
        / "inspections"
        / "greenhouse_camera_route_01.json"
    )
    expected_path.parent.mkdir(parents=True, exist_ok=True)
    expected_path.write_text(json.dumps(mismatched), encoding="utf-8")
    with pytest.raises(InspectionTaskError, match="map binding"):
        repo.load("greenhouse_camera_route_01")


def test_repository_rejects_unsafe_path_components(tmp_path):
    with pytest.raises(InspectionTaskError):
        InspectionRepository(tmp_path, "../escape", "v1")
    repo = InspectionRepository(tmp_path, "greenhouse_01", "v1")
    for value in ("../escape", "/absolute", "bad/name", ""):
        with pytest.raises(InspectionTaskError):
            repo.path_for(value)
