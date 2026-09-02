import json
import sys
from pathlib import Path

from agt_navigation.field_capture import FieldCaptureRun, Pose2D
from agt_inspection_exporter import export_run, validate_dataset


def _metadata_run(tmp_path: Path) -> Path:
    run = FieldCaptureRun(tmp_path / "inspection_runs", session_id="20260901_001",
                          map_id="map", map_version_id="v1", task_group_id="task")
    run.start(Pose2D(0, 0, 0))
    point = run.point_dir(1, "P01")
    image = run.write_placeholder_image(point)
    run.record_waypoint(
        index=1, waypoint_id="P01", target=Pose2D(1, 2, 0), capture=Pose2D(1, 2, 0),
        image_path=image, navigation_success=True, capture_success=True,
        image_timestamp=1788192000.123,
        robot_pose={"timestamp": 1788192000.120, "frame": "map", "x": 1, "y": 2,
                    "z": 0, "qx": 0, "qy": 0, "qz": .7, "qw": .7},
        gimbal={"timestamp": 1788192000.110, "yaw": -30, "pitch": 10, "roll": 0},
        capture_view={"name": "overview", "yaw": 0.0, "pitch": 0.0, "roll": 0.0},
    )
    return run.run_dir


def test_capture_metadata_contains_all_three_timestamps(tmp_path):
    run = _metadata_run(tmp_path)
    metadata = json.loads((run / "metadata/P01.json").read_text())
    assert metadata["image"]["timestamp"] == 1788192000.123
    assert metadata["robot_pose"]["timestamp"] == 1788192000.120
    assert metadata["gimbal"]["timestamp"] == 1788192000.110
    assert metadata["capture_view"] == {
        "name": "overview", "yaw": 0.0,
        "pitch": 0.0, "roll": 0.0,
    }
    assert (run / "images/image_1788192000.123.jpg").is_file()


def test_exporter_and_validator(tmp_path):
    dataset = tmp_path / "inspection_dataset"
    export_run(_metadata_run(tmp_path), dataset)
    assert (dataset / "images/image_1788192000.123.jpg").is_file()
    assert (dataset / "pose.csv").read_text().splitlines()[0] == "timestamp,x,y,z,qx,qy,qz,qw,frame"
    report = validate_dataset(dataset)
    assert report["valid"] is True
    assert report["matched_pose"] == report["matched_gimbal"] == 1
    assert (dataset / "dataset_validation_report.json").is_file()


def test_validator_detects_bad_time_delta(tmp_path):
    dataset = tmp_path / "dataset"
    export_run(_metadata_run(tmp_path), dataset)
    (dataset / "pose.csv").write_text(
        "timestamp,x,y,z,qx,qy,qz,qw,frame\n1788192001.0,1,2,0,0,0,.7,.7,map\n"
    )
    report = validate_dataset(dataset, tolerance_ms=50)
    assert report["matched_pose"] == 0
    assert report["matched_gimbal"] == 1
    assert report["valid"] is False


def test_vision_runtime_reader_compatibility(tmp_path):
    """Exercise the sibling runtime's reader when that checkout is available."""
    vision_root = Path(__file__).resolve().parents[3].parent / "agt_vision_runtime"
    if not (vision_root / "vision_runtime").is_dir():
        return
    sys.path.insert(0, str(vision_root))
    from vision_runtime.dataset import discover_images, image_timestamp, read_log

    dataset = tmp_path / "inspection_dataset"
    export_run(_metadata_run(tmp_path), dataset)
    images = discover_images(dataset)
    assert len(images) == 1
    assert image_timestamp(images[0]) == 1788192000.123
    assert len(read_log(dataset / "pose.csv")[0]) == 1
    assert len(read_log(dataset / "gimbal.csv")[0]) == 1
