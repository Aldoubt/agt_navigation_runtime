from pathlib import Path

ROOT = Path(__file__).parents[1]
SOURCE = (ROOT / "src/is_task_ready.cpp").read_text()
HEADER = (ROOT / "include/agt_bt_executor/is_task_ready.hpp").read_text()


def test_uses_authoritative_readiness_service():
    assert "EvaluateTaskReadiness" in HEADER
    assert '"/agt/system/evaluate_task_readiness"' in SOURCE
    assert "request->validate_task = true" in SOURCE


def test_readiness_is_fail_closed_and_exports_blockers():
    assert "readiness.ready" in SOURCE
    assert "NodeStatus::FAILURE" in SOURCE
    assert '"last_blocker_code"' in SOURCE
    assert '"last_blocker_message"' in SOURCE
