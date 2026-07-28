from pathlib import Path

import pytest
import yaml

from agt_experiment_manager.facade import (
    ExperimentBusinessFacade, load_bag_profiles,
)
from agt_experiment_manager.manager import ExperimentError, ExperimentManager


def test_profiles_require_explicit_topics_and_reject_record_all(tmp_path):
    valid = tmp_path / "valid.yaml"
    valid.write_text("profiles:\n  mapping:\n    topics: [/tf, /clock]\n", encoding="utf-8")
    assert set(load_bag_profiles(valid)) == {"mapping"}
    invalid = tmp_path / "invalid.yaml"
    invalid.write_text("profiles:\n  bad:\n    topics: [-a]\n", encoding="utf-8")
    with pytest.raises(ExperimentError, match="invalid"):
        load_bag_profiles(invalid)


def test_create_experiment_supports_explicit_start_and_snapshots_bindings(tmp_path):
    runtime = tmp_path / "runtime"
    profile = tmp_path / "platform.yaml"
    profile.write_text("platform: bunker\n", encoding="utf-8")
    manager = ExperimentManager(runtime / "experiments", rosbag_root=runtime / "rosbag")
    facade = ExperimentBusinessFacade(manager, {"mapping": {"topics": ["/tf"]}})
    manifest = facade.create_experiment({
        "experiment_title": "Mission Trial",
        "mission_id": "mission_a",
        "mission_version": "v1",
        "mission_sha256": "sha256:" + "1" * 64,
        "map_id": "map_a",
        "map_version_id": "map_v1",
        "map_sha256": "sha256:" + "2" * 64,
        "platform_profile": str(profile),
        "calibration_profile": "",
        "nav2_profile": "",
    }, start=True)
    assert manifest["state"] == "RUNNING"
    assert manifest["active_map"]["map_version_id"] == "map_v1"
    assert manifest["launch_arguments"]["mission_id"] == "mission_a"
    assert manager.inspect(manifest["experiment_id"])["config_files"][0]["sha256"].startswith("sha256:")
    with pytest.raises(ExperimentError, match="already exists"):
        facade.create_experiment({"experiment_title": "Second"})


def test_created_experiment_remains_created_until_explicit_start(tmp_path):
    manager = ExperimentManager(tmp_path / "experiments")
    facade = ExperimentBusinessFacade(manager, {})
    created = facade.manage(5, {"experiment_title": "Web Trial"})
    experiment_id = created["experiment_id"]
    assert manager.inspect(experiment_id)["state"] == "CREATED"
    started = facade.manage(8, {"experiment_id": experiment_id})
    assert started["experiment_id"] == experiment_id
    assert manager.inspect(experiment_id)["state"] == "RUNNING"
    facade.manage(10, {
        "experiment_id": experiment_id,
        "event_type": "operator_note",
        "metadata_json": '{"note": "checked"}',
    })
    assert "operator_note" in (manager._path(experiment_id) / "events.jsonl").read_text()


def test_list_sessions_includes_standalone_and_experiment_bags(tmp_path):
    runtime = tmp_path / "runtime"
    standalone = runtime / "rosbag" / "standalone"
    experiment = runtime / "experiments" / "exp_01" / "rosbag" / "mapping_01"
    for path in (standalone, experiment):
        path.mkdir(parents=True)
        (path / "metadata.yaml").write_text(
            yaml.safe_dump({
                "rosbag2_bagfile_information": {
                    "message_count": 2,
                    "duration": {"nanoseconds": 10},
                    "topics_with_message_count": [],
                }
            }),
            encoding="utf-8",
        )
    manager = ExperimentManager(runtime / "experiments", rosbag_root=runtime / "rosbag")
    facade = ExperimentBusinessFacade(manager, {})
    sessions = facade.list_sessions()
    assert {item["bag_id"] for item in sessions} == {
        "standalone", "experiments/exp_01/rosbag/mapping_01"
    }
    assert facade.list_sessions(experiment_id="exp_01")[0]["experiment_id"] == "exp_01"


def test_experiment_bag_path_cannot_escape_runtime(tmp_path):
    manager = ExperimentManager(tmp_path / "experiments", rosbag_root=tmp_path / "rosbag")
    with pytest.raises(ExperimentError):
        manager._resolve_bag_path("experiments/../outside")
    with pytest.raises(ExperimentError):
        manager._resolve_bag_path("experiments/exp/other/bag")


def test_interrupt_is_explicit_and_terminal(tmp_path):
    manager = ExperimentManager(tmp_path / "experiments")
    experiment_id = manager.create(title="Interrupt")
    manager.start(experiment_id)
    result = manager.interrupt(experiment_id, "operator")
    assert result["state"] == "INTERRUPTED"
    assert manager.inspect(experiment_id)["result_status"] == "INTERRUPTED"


def test_unexpected_recorder_exit_is_not_reported_as_idle(tmp_path):
    class ExitedProcess:
        pid = 42

        @staticmethod
        def poll():
            return 9

    manager = ExperimentManager(tmp_path / "experiments")
    manager._bag_process = ExitedProcess()
    manager._bag_profile = "mapping"
    manager._bag_experiment_id = "exp_01"
    manager._bag_path = tmp_path / "experiments" / "exp_01" / "rosbag" / "bag"
    status = ExperimentBusinessFacade(manager, {}).status()
    assert status["state"] == "ERROR"
    assert status["experiment_id"] == "exp_01"
    assert "exited with 9" in status["message"]
