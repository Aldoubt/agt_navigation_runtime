from pathlib import Path

import pytest
import yaml

from agt_experiment_manager.manager import ExperimentError, ExperimentManager


class FakePlaybackProcess:
    _next_pid = 21000

    def __init__(self, command, **_kwargs):
        self.command = command
        self.pid = self._next_pid
        type(self)._next_pid += 1
        self.returncode = None

    def poll(self):
        return self.returncode

    def wait(self, timeout=None):
        del timeout
        self.returncode = 0
        return self.returncode


def test_experiment_manifest_events_and_recovery(tmp_path):
    manager = ExperimentManager(tmp_path / "experiments")
    experiment_id = manager.create(title="Map Trial", tags=["mapping"], active_map={"map_id": "greenhouse_01"})
    manager.start(experiment_id, {"overall_state": "UNKNOWN"})
    manager.add_event(experiment_id, "manual_intervention", {"reason": "initial pose"})
    manager.record_localization_result(experiment_id, {"success": True, "runtime_ms": 10.0})
    assert manager.inspect(experiment_id)["state"] == "RUNNING"
    summary = manager.finalize(experiment_id, {"overall_state": "OK"})
    assert summary["localization_success_rate"] == 1.0
    assert (tmp_path / "experiments" / experiment_id / "report.md").is_file()
    events = (tmp_path / "experiments" / experiment_id / "events.jsonl").read_text(encoding="utf-8").splitlines()
    assert len(events) == 3

    interrupted = manager.create(title="Interrupted")
    manager.start(interrupted)
    assert manager.recover_interrupted() == [interrupted]
    assert manager.inspect(interrupted)["state"] == "INTERRUPTED"


def test_bag_profile_requires_explicit_topics(tmp_path):
    manager = ExperimentManager(tmp_path / "experiments")
    experiment_id = manager.create(title="Bag")
    manager.start(experiment_id)
    with pytest.raises(ExperimentError):
        manager.start_bag(experiment_id, "bad", {})


def test_invalid_experiment_is_not_reported_as_success(tmp_path):
    manager = ExperimentManager(tmp_path / "experiments")
    experiment_id = manager.create(title="Invalid")
    manager.start(experiment_id)
    manager.mark_invalid(experiment_id, "operator rejected map")
    assert manager.inspect(experiment_id)["result_status"] == "INVALID"


def test_bag_listing_and_playback_use_only_complete_runtime_bundles(tmp_path):
    rosbag_root = tmp_path / "rosbag"
    bag_path = rosbag_root / "mapping_trial"
    bag_path.mkdir(parents=True)
    (bag_path / "metadata.yaml").write_text(
        yaml.safe_dump({
            "rosbag2_bagfile_information": {
                "duration": {"nanoseconds": 123456789},
                "message_count": 42,
                "storage_identifier": "sqlite3",
            }
        }),
        encoding="utf-8",
    )
    manager = ExperimentManager(
        tmp_path / "experiments",
        rosbag_root=rosbag_root,
        popen_factory=FakePlaybackProcess,
    )

    bags = manager.list_bags()
    assert bags[0]["bag_id"] == "mapping_trial"
    assert bags[0]["message_count"] == 42
    result = manager.start_playback("mapping_trial", rate=1.5)
    assert result["command"][:5] == ["ros2", "bag", "play", "--clock", "--rate"]
    assert result["command"][5] == "1.5"
    assert result["command"][6] == str(bag_path.resolve())
    assert result["playback_profile"] == "all"
    assert manager.playback_status()["playing"] is True
    with pytest.raises(ExperimentError, match="already playing"):
        manager.start_playback("mapping_trial")
    manager.stop_playback()
    assert manager.playback_status()["playing"] is False


def test_mapping_playback_filters_algorithm_outputs(tmp_path):
    rosbag_root = tmp_path / "rosbag"
    bag_path = rosbag_root / "mapping_trial"
    bag_path.mkdir(parents=True)
    (bag_path / "metadata.yaml").write_text(
        yaml.safe_dump({"rosbag2_bagfile_information": {"topics_with_message_count": []}}),
        encoding="utf-8",
    )
    manager = ExperimentManager(
        tmp_path / "experiments",
        rosbag_root=rosbag_root,
        popen_factory=FakePlaybackProcess,
    )
    result = manager.start_playback("mapping_trial", playback_profile="mapping_inputs")
    assert result["replayed_topics"] == [
        "/clock",
        "/tf_static",
        "/agt/sensors/lidar/custom",
        "/agt/sensors/imu/data",
    ]
    assert "--topics" in result["command"]
    assert "/agt/mapping/odometry" not in result["command"]


def test_teach_repeat_result_and_failure_case_are_auditable(tmp_path):
    repository = tmp_path / "repository"
    repository.mkdir()
    teach_manifest = tmp_path / "teach_manifest.yaml"
    teach_manifest.write_text("schema_version: 1\n", encoding="utf-8")
    config = tmp_path / "teach_repeat.yaml"
    config.write_text("maximum_linear_speed_mps: 0.2\n", encoding="utf-8")
    manager = ExperimentManager(tmp_path / "experiments", repository_root=repository)
    experiment_id = manager.create(title="Teach Repeat", active_map={"map_id": "map_01"})
    manager.start(experiment_id)
    manager.snapshot_config(experiment_id, [config])
    result = manager.record_teach_repeat_result(
        experiment_id,
        demo_id="route_01",
        run_id="run_01",
        teach_manifest=str(teach_manifest),
        reference_path_hash="sha256:" + "1" * 64,
        map_identity={"map_id": "map_01", "localization_pcd_sha256": "sha256:" + "2" * 64},
        repeatability_metrics={"lateral_rmse_m": 0.05},
        localization_summary={"tracking_lost_count": 0},
        execution_result={"state": "SUCCEEDED"},
    )
    assert result.is_file()
    assert manager.inspect(experiment_id)["teach_repeat_runs"][0]["run_id"] == "run_01"
    with pytest.raises(ValueError):
        manager.record_teach_repeat_result(
            experiment_id,
            demo_id="route_01",
            run_id="run_nan",
            teach_manifest=str(teach_manifest),
            reference_path_hash="sha256:" + "1" * 64,
            map_identity={"map_id": "map_01"},
            repeatability_metrics={"lateral_rmse_m": float("nan")},
            localization_summary={},
            execution_result={"state": "FAILED"},
        )
    assert not (
        tmp_path
        / "experiments"
        / experiment_id
        / "teach_repeat/route_01/run_nan"
    ).exists()
    failure = manager.record_failure_case(
        experiment_id,
        demo_id="route_01",
        run_id="run_01",
        category="LOCALIZATION_LOST",
        reference_progress=2.5,
        lateral_error_m=0.2,
    )
    assert failure["repository"]["commit"] is None
    assert "LOCALIZATION_LOST" in (
        tmp_path / "experiments" / experiment_id / "failure_cases.jsonl"
    ).read_text(encoding="utf-8")
    summary = manager.finalize(experiment_id)
    assert summary["teach_repeat_results"][0]["reference_path_hash"].endswith(
        "1" * 64
    )
    report = (
        tmp_path / "experiments" / experiment_id / "report.md"
    ).read_text(encoding="utf-8")
    assert "Reference path hash" in report
    assert "localization_pcd_sha256" in report
    assert "teach_repeat.yaml" in report


def test_mapping_and_navigation_bag_profiles_keep_replay_and_task_evidence():
    profile_path = (
        Path(__file__).resolve().parents[1] / "config" / "bag_profiles.yaml"
    )
    profiles = yaml.safe_load(profile_path.read_text(encoding="utf-8"))["profiles"]
    mapping = profiles["mapping"]["topics"]
    navigation = profiles["navigation"]["topics"]

    assert len(mapping) == len(set(mapping))
    assert {
        "/agt/sensors/lidar/custom",
        "/agt/sensors/lidar/custom_filtered",
        "/agt/sensors/imu/data",
        "/agt/mapping/odometry",
        "/agt/mapping/octomap_points",
        "/agt/map/mapping_occupancy",
        "/agt/mapping/manage_session/_action/status",
        "/diagnostics",
    } <= set(mapping)
    assert {
        "/agt/system/health",
        "/agt/system/task_readiness",
        "/agt/localization/status",
        "/agt/navigation/execute_waypoint_task/_action/feedback",
        "/agt/navigation/execute_waypoint_task/_action/status",
        "/follow_waypoints/_action/feedback",
        "/agt/safety/status",
        "/agt/safety/emergency_stop",
        "/agt/chassis/odometry",
        "/diagnostics",
    } <= set(navigation)
