from pathlib import Path

from agt_inspection.execution import CaptureResult, VisionResult
from agt_inspection.multiview_evidence import InspectionEvidenceStore


PACKAGE = Path(__file__).resolve().parents[1]
HASH_A = "sha256:" + "a" * 64
HASH_B = "sha256:" + "b" * 64


def _session():
    return {
        "schema_version": 1,
        "session_id": "session_visual_files",
        "inspection_task_id": "inspection_visual_files",
        "task_revision": 1,
        "task_content_sha256": HASH_A,
        "map_id": "mock_map",
        "map_version_id": "v1",
        "map_manifest_sha256": HASH_B,
        "count_target": "litchi_flower",
    }


def _observation():
    return {
        "schema_version": 1,
        "view_id": "view_center",
        "capture_id": "capture_001",
        "capture_stamp": "2026-08-28T10:30:00+08:00",
        "robot_pose_map": {"x": 1.0, "y": 2.0, "z": 0.0, "yaw": 0.0},
        "gimbal": {"pan_rad": 0.0, "tilt_rad": 0.0, "feedback_valid": True},
        "camera": {
            "camera_id": "inspection_camera",
            "calibration_id": "mock_calib",
            "calibration_sha256": HASH_A,
        },
        "camera_pose_valid": False,
        "camera_pose_map": {},
        "evidence": {},
        "vision": {
            "model_id": "mock-flower-seg",
            "model_version": "1",
            "weights_sha256": HASH_A,
            "raw_count": 1,
            "inference_time_ms": 5.0,
            "primary_confidence": 0.93,
            "result_json": {"raw_count": 1, "instances": [{"local_instance_id": "I0001"}]},
        },
        "warnings": [],
    }


def test_result_models_carry_explicit_encoded_media_suffixes():
    capture = CaptureResult(
        True,
        image_bytes=b"\xff\xd8jpeg",
        image_suffix=".jpg",
    )
    vision = VisionResult(
        True,
        weights_sha256=HASH_A,
        overlay_bytes=b"\xff\xd8overlay",
        mask_bytes=b"\x89PNG\r\n\x1a\nmask",
        overlay_suffix=".jpg",
        mask_suffix=".png",
    )

    assert capture.image_suffix == ".jpg"
    assert vision.overlay_suffix == ".jpg"
    assert vision.mask_suffix == ".png"


def test_store_persists_canonical_visual_file_names_and_records_them(tmp_path):
    store = InspectionEvidenceStore(tmp_path)
    store.start_session(_session())
    result_uri = store.write_view(
        "P001",
        "view_center",
        _observation(),
        image_bytes=b"\xff\xd8jpeg",
        overlay_bytes=b"\xff\xd8overlay",
        mask_bytes=b"\x89PNG\r\n\x1a\nmask",
        image_suffix=".jpg",
        overlay_suffix=".jpg",
        mask_suffix=".png",
    )

    view_root = Path(result_uri).parent
    assert (view_root / "original.jpg").read_bytes().startswith(b"\xff\xd8")
    assert (view_root / "overlay.jpg").read_bytes().startswith(b"\xff\xd8")
    assert (view_root / "mask.png").read_bytes().startswith(b"\x89PNG\r\n\x1a\n")

    import json

    payload = json.loads(Path(result_uri).read_text(encoding="utf-8"))
    assert payload["evidence"] == {
        "image": "original.jpg",
        "overlay": "overlay.jpg",
        "mask": "mask.png",
    }


def test_multiview_executor_and_ros_adapter_propagate_canonical_suffixes():
    executor = (PACKAGE / "agt_inspection" / "multiview_execution.py").read_text(encoding="utf-8")
    server = (PACKAGE / "scripts" / "inspection_task_server.py").read_text(encoding="utf-8")
    compact_server = "".join(server.split())

    assert "image_suffix=capture.image_suffix" in executor
    assert "overlay_suffix=vision.overlay_suffix" in executor
    assert "mask_suffix=vision.mask_suffix" in executor

    # Verify behavior rather than source formatting: CameraRunner must JPEG-encode
    # the captured ROS Image before declaring the .jpg media identity.
    assert "image_bytes=encode_jpeg(response.image)" in compact_server
    assert 'image_suffix=".jpg"' in server
    assert 'overlay_suffix=".jpg"' in server
    assert 'mask_suffix=".png"' in server
