import pytest

from agt_experiment_manager.manager import ExperimentError, ExperimentManager


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
