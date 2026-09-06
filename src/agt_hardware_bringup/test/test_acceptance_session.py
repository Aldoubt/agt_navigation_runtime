from __future__ import annotations

import importlib.util
import json
from datetime import datetime, timezone
from pathlib import Path
from types import SimpleNamespace


ROOT = Path(__file__).resolve().parents[1]
MODULE_PATH = ROOT / "agt_hardware_bringup" / "acceptance_session.py"
WRAPPER_PATH = ROOT / "scripts" / "acceptance_session.py"


def load_module():
    assert MODULE_PATH.exists(), "acceptance_session.py production module is not implemented yet"
    spec = importlib.util.spec_from_file_location("acceptance_session_under_test", MODULE_PATH)
    assert spec is not None and spec.loader is not None
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def test_session_directory_is_timestamped_and_label_is_sanitized(tmp_path):
    module = load_module()
    session_dir = module.create_session_directory(
        tmp_path,
        now=datetime(2026, 8, 31, 1, 2, 3, tzinfo=timezone.utc),
        label="BUNKER field #1",
    )
    assert session_dir == tmp_path / "20260831T010203Z-bunker-field-1"
    assert session_dir.is_dir()


def test_collect_session_runs_only_read_only_evidence_commands_and_keeps_blocked_reports(tmp_path):
    module = load_module()
    calls = []

    def runner(command, timeout):
        calls.append((list(command), timeout))
        text = ""
        if "socketcan_preflight.py" in command:
            output = Path(command[command.index("--json-output") + 1])
            output.write_text('{"ready": true, "result": "PASS"}\n', encoding="utf-8")
        elif "vehicle_preflight.py" in command:
            output = Path(command[command.index("--json-output") + 1])
            strict = "--require-calibration-verified" in command
            payload = {"ready": not strict, "result": "BLOCKED" if strict else "PASS"}
            output.write_text(json.dumps(payload) + "\n", encoding="utf-8")
            if strict:
                return SimpleNamespace(returncode=2, stdout=json.dumps(payload), stderr="")
        elif command[:3] == ["ros2", "topic", "list"]:
            text = "/diagnostics\n/tf_static\n"
        elif "/diagnostics" in command:
            text = "status: []\n"
        elif "/tf_static" in command:
            text = "transforms: []\n"
        return SimpleNamespace(returncode=0, stdout=text, stderr="")

    session_dir = module.collect_acceptance_session(
        output_root=tmp_path,
        label="bench",
        can_interface="can0",
        expected_can_bitrate=500000,
        observation_sec=1.0,
        runner=runner,
        now=datetime(2026, 8, 31, 1, 2, 3, tzinfo=timezone.utc),
    )

    assert (session_dir / "can_preflight.json").is_file()
    assert (session_dir / "hardware_preflight.json").is_file()
    assert (session_dir / "mapping_preflight.json").is_file()
    assert (session_dir / "ros2_topic_list.txt").read_text(encoding="utf-8") == "/diagnostics\n/tf_static\n"
    assert (session_dir / "diagnostics.txt").read_text(encoding="utf-8") == "status: []\n"
    assert (session_dir / "tf_snapshot.txt").read_text(encoding="utf-8") == "transforms: []\n"
    assert "PASS / FAIL / UNVERIFIED / NOT_APPLICABLE" in (session_dir / "notes.md").read_text(encoding="utf-8")

    manifest = json.loads((session_dir / "session.json").read_text(encoding="utf-8"))
    assert manifest["schema"] == "agt.hardware.acceptance-session/v1"
    assert manifest["collection_complete"] is True
    assert manifest["preflight_results"]["mapping"] == "BLOCKED"
    assert manifest["commands"]["mapping_preflight"]["returncode"] == 2

    flattened = [token for command, _ in calls for token in command]
    forbidden = ("cmd_vel", "set_motion_enabled", "ip link set", "mission")
    for token in forbidden:
        assert all(token not in value for value in flattened)


def test_collect_session_marks_collection_incomplete_for_command_execution_failure(tmp_path):
    module = load_module()

    def runner(command, timeout):
        if command[:3] == ["ros2", "topic", "list"]:
            return SimpleNamespace(returncode=127, stdout="", stderr="ros2 missing")
        output_flag = "--json-output" in command
        if output_flag:
            output = Path(command[command.index("--json-output") + 1])
            output.write_text('{"ready": true, "result": "PASS"}\n', encoding="utf-8")
        return SimpleNamespace(returncode=0, stdout="", stderr="")

    session_dir = module.collect_acceptance_session(
        output_root=tmp_path,
        runner=runner,
        now=datetime(2026, 8, 31, 1, 2, 3, tzinfo=timezone.utc),
    )
    manifest = json.loads((session_dir / "session.json").read_text(encoding="utf-8"))
    assert manifest["collection_complete"] is False
    assert "ros2_topic_list" in manifest["collection_failures"]


def test_package_contract_installs_acceptance_session_wrapper():
    cmake = (ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
    assert "scripts/acceptance_session.py" in cmake
    assert WRAPPER_PATH.is_file()
