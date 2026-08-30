from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
SCRIPT = ROOT / "src" / "agt_field_commissioning" / "scripts" / "raycast_free_space_node.py"
MAPPING_ARTIFACTS = (
    ROOT
    / "src"
    / "agt_field_commissioning"
    / "agt_field_commissioning"
    / "mapping_artifacts.py"
)


def test_raycast_observer_is_read_only_and_uses_registered_cloud_plus_odometry():
    text = SCRIPT.read_text(encoding="utf-8")

    assert "sensor_msgs_py" in text
    assert "PointCloud2" in text
    assert "Odometry" in text
    assert "RaycastEvidenceGrid" in text
    assert "save_evidence" in text
    assert "create_subscription" in text
    assert "create_publisher" not in text
    assert "cmd_vel" not in text
    assert "auto_permit" not in text
    assert "TransformBroadcaster" not in text


def test_raycast_observer_has_bounded_pose_history_and_nearest_pose_age_gate():
    text = SCRIPT.read_text(encoding="utf-8")

    assert "deque" in text
    assert "maxlen=" in text
    assert "pose_max_age_s" in text
    assert "nearest" in text.lower()
    assert "cloud_stride" in text
    assert "point_stride" in text
    assert "max_ray_range_m" in text


def test_mapping_artifacts_allocate_run_scoped_observation_directory():
    text = MAPPING_ARTIFACTS.read_text(encoding="utf-8")

    assert "observation_dir" in text
    assert 'run_root / "observation"' in text
