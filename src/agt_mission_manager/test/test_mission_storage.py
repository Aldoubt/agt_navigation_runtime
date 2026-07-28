import json

from agt_mission_manager.audit_log import AuditLog
from agt_mission_manager.mission_model import MissionState
from agt_mission_manager.mission_storage import MissionStorage


def test_restart_marks_active_execution_interrupted(tmp_path):
    storage = MissionStorage(tmp_path)
    storage.write_execution_state({"state": int(MissionState.RUNNING), "mission_id": "demo"})
    recovered = storage.recover_interrupted()
    assert recovered["state"] == int(MissionState.INTERRUPTED)
    assert json.loads(storage.execution_state_path().read_text())["state"] == int(MissionState.INTERRUPTED)


def test_audit_append_leaves_complete_json_lines(tmp_path):
    path = tmp_path / "audit.jsonl"
    audit = AuditLog(path)
    audit.append("first", {"step": 1})
    audit.append("second", {"step": 2})
    records = [json.loads(line) for line in path.read_text().splitlines()]
    assert [item["event"] for item in records] == ["first", "second"]
    assert not path.with_suffix(".jsonl.tmp").exists()
