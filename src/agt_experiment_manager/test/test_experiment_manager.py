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
