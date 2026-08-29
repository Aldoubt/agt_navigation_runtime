import csv
import json

from agt_inspection.multiview_evidence import InspectionEvidenceStore


def _session():
    return {
        "schema_version": 1,
        "session_id": "session_001",
        "inspection_task_id": "litchi_flower_count",
        "task_revision": 1,
        "task_content_sha256": "sha256:" + "a" * 64,
        "map_id": "orchard_01",
        "map_version_id": "v1",
        "map_manifest_sha256": "sha256:" + "b" * 64,
        "count_target": "litchi_flower",
    }


def _view(view_id, raw_count, x, pan):
    return {
        "schema_version": 1,
        "view_id": view_id,
        "capture_id": f"capture_{view_id}",
        "capture_stamp": "2026-08-28T10:32:12.351+08:00",
        "robot_pose_map": {"x": x, "y": 4.84, "z": 0.0, "yaw": 1.566},
        "gimbal": {"pan_rad": pan, "tilt_rad": -0.1745, "feedback_valid": True},
        "camera": {
            "camera_id": "inspection_camera",
            "calibration_id": "camera_calib_v2",
            "calibration_sha256": "sha256:" + "c" * 64,
        },
        "evidence": {"image": "original.bin", "overlay": "overlay.bin", "mask": "mask.bin"},
        "vision": {
            "model_id": "litchi_flower_instance_seg",
            "model_version": "v1.0",
            "raw_count": raw_count,
            "inference_time_ms": 82.3,
            "result_json": {"instances": []},
        },
        "warnings": [],
    }


def test_multiview_evidence_layout_and_report_are_deterministic(tmp_path):
    store = InspectionEvidenceStore(tmp_path)
    session_root = store.start_session(_session())

    store.write_view(
        "P001",
        "view_001",
        _view("view_001", 3, 12.29, -0.5236),
        image_bytes=b"image-a",
        overlay_bytes=b"overlay-a",
        mask_bytes=b"mask-a",
    )
    store.write_view(
        "P001",
        "view_002",
        _view("view_002", 4, 12.30, 0.0),
        image_bytes=b"image-b",
        overlay_bytes=b"overlay-b",
        mask_bytes=b"mask-b",
    )
    store.write_aggregation(
        "P001",
        {
            "schema_version": 1,
            "aggregation_scope": "POINT_LOCAL",
            "aggregator_id": "mock-association",
            "aggregator_version": "1",
            "raw_instance_count": 7,
            "unique_instance_count": 5,
            "ambiguous_instance_count": 1,
            "association_confidence": 0.9,
            "global_instances": [
                {
                    "global_instance_id": "G0001",
                    "status": "MATCHED",
                    "association_confidence": 0.92,
                    "members": [
                        {"view_id": "view_001", "local_instance_id": "I0001"},
                        {"view_id": "view_002", "local_instance_id": "I0003"},
                    ],
                }
            ],
            "warnings": [],
        },
    )

    report_uri = store.build_report()

    assert session_root == tmp_path / "litchi_flower_count" / "session_001"
    view_root = session_root / "points" / "P001" / "view_001"
    assert (view_root / "original.bin").read_bytes() == b"image-a"
    assert (view_root / "overlay.bin").is_file()
    assert (view_root / "mask.bin").is_file()
    assert (view_root / "result.json").is_file()
    assert (session_root / "points" / "P001" / "aggregation" / "result.json").is_file()

    report_root = session_root / "report"
    assert report_uri == str(report_root / "report.json")
    report = json.loads((report_root / "report.json").read_text(encoding="utf-8"))
    assert report["count_mode"] == "POINT_DEDUP"
    assert report["totals"]["raw_instance_count"] == 7
    assert report["totals"]["unique_instance_count"] == 5
    assert report["totals"]["ambiguous_instance_count"] == 1

    with open(report_root / "points.csv", newline="", encoding="utf-8") as stream:
        rows = list(csv.DictReader(stream))
    assert rows == [
        {
            "point_id": "P001",
            "views": "2",
            "raw_count": "7",
            "unique_count": "5",
            "ambiguous_count": "1",
        }
    ]

    with open(report_root / "views.csv", newline="", encoding="utf-8") as stream:
        rows = list(csv.DictReader(stream))
    assert [row["view_id"] for row in rows] == ["view_001", "view_002"]
    assert [row["raw_count"] for row in rows] == ["3", "4"]

    with open(report_root / "instances.csv", newline="", encoding="utf-8") as stream:
        rows = list(csv.DictReader(stream))
    assert len(rows) == 2
    assert {row["global_instance_id"] for row in rows} == {"G0001"}
