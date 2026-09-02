import json
from pathlib import Path

from agt_navigation.field_capture import FieldCaptureRun, Pose2D


def test_field_capture_run_records_navigation_and_capture_separately(tmp_path: Path):
    run = FieldCaptureRun(
        tmp_path,
        session_id="session-001",
        map_id="orchard",
        map_version_id="map-v1",
        task_group_id="inspection-main",
    )
    home = Pose2D(1.0, 2.0, 0.25)
    run.start(home)

    point_dir = run.point_dir(1, "tree/a")
    image_path = run.write_placeholder_image(point_dir)
    run.record_waypoint(
        index=1,
        waypoint_id="tree/a",
        target=Pose2D(3.0, 4.0, 1.0),
        capture=Pose2D(3.1, 4.1, 1.05),
        image_path=image_path,
        navigation_success=True,
        navigation_message="arrived",
        capture_success=True,
        capture_retry_count=0,
        capture_message="captured",
    )
    summary_path = run.finish(
        success=True,
        return_home_success=True,
        completed_waypoints=1,
        total_waypoints=1,
    )

    assert run.run_dir.name == "session-001"
    assert point_dir.name == "P01_tree_a"
    assert image_path.name == "image.pgm"
    assert image_path.exists()

    result = json.loads((point_dir / "result.json").read_text(encoding="utf-8"))
    assert result["schema_version"] == 2
    assert result["waypoint_id"] == "tree/a"
    assert result["target_pose"] == {"x": 3.0, "y": 4.0, "yaw": 1.0}
    assert result["capture_pose"] == {"x": 3.1, "y": 4.1, "yaw": 1.05}
    assert result["image"] == "P01_tree_a/image.pgm"
    assert result["navigation"] == {"success": True, "message": "arrived"}
    assert result["capture"] == {
        "success": True,
        "retry_count": 0,
        "message": "captured",
    }
    assert "status" not in result

    summary = json.loads(summary_path.read_text(encoding="utf-8"))
    assert summary["success"] is True
    assert summary["return_home_success"] is True
    assert summary["completed_waypoints"] == 1
    assert summary["total_waypoints"] == 1
    assert summary["images_dir"] == str(run.run_dir)


def test_field_capture_can_record_navigation_success_with_capture_failure(tmp_path: Path):
    run = FieldCaptureRun(
        tmp_path,
        session_id="session-capture-failed",
        map_id="orchard",
        map_version_id="map-v1",
        task_group_id="inspection-main",
    )
    run.start(Pose2D(0.0, 0.0, 0.0))

    result_path = run.record_waypoint(
        index=1,
        waypoint_id="tree_01",
        target=Pose2D(2.0, 1.0, 0.5),
        capture=Pose2D(2.0, 1.0, 0.5),
        image_path=None,
        navigation_success=True,
        navigation_message="arrived",
        capture_success=False,
        capture_retry_count=2,
        capture_message="CAMERA_TIMEOUT",
    )

    result = json.loads(result_path.read_text(encoding="utf-8"))
    assert result["navigation"]["success"] is True
    assert result["capture"] == {
        "success": False,
        "retry_count": 2,
        "message": "CAMERA_TIMEOUT",
    }
    assert result["image"] is None


def test_field_capture_start_preserves_home_and_task_identity(tmp_path: Path):
    run = FieldCaptureRun(
        tmp_path,
        session_id="session-002",
        map_id="orchard",
        map_version_id="map-v2",
        task_group_id="route-a",
    )
    run.start(Pose2D(-1.5, 0.2, -0.5))

    mission = json.loads((run.run_dir / "mission.json").read_text(encoding="utf-8"))
    assert mission["map_id"] == "orchard"
    assert mission["map_version_id"] == "map-v2"
    assert mission["task_group_id"] == "route-a"
    assert mission["home_pose"] == {"x": -1.5, "y": 0.2, "yaw": -0.5}
