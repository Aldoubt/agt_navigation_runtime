from __future__ import annotations

import importlib.util
from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parents[1]
MODULE = ROOT / "agt_hardware_bringup" / "vehicle_preflight.py"


def load_module():
    spec = importlib.util.spec_from_file_location("vehicle_preflight", MODULE)
    if spec is None or spec.loader is None:
        raise RuntimeError("unable to load vehicle_preflight module")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def test_summary_fails_closed_only_on_required_checks():
    module = load_module()
    checks = [
        module.make_check("lidar", required=True, ok=True, evidence="message received"),
        module.make_check("camera", required=False, ok=False, reason="topic missing"),
    ]
    report = module.summarize_checks(checks)
    assert report["ready"] is True
    assert report["checks"][1]["status"] == "OPTIONAL_MISSING"

    checks.append(module.make_check("imu", required=True, ok=False, reason="topic missing"))
    assert module.summarize_checks(checks)["ready"] is False


def test_std_bool_echo_parser_handles_connected_state():
    module = load_module()
    assert module.parse_std_bool_echo("data: true\n---\n") is True
    assert module.parse_std_bool_echo("data: false\n---\n") is False
    assert module.parse_std_bool_echo("garbled") is None


def test_sensor_summary_parser_requires_named_summary_and_true_health():
    module = load_module()
    healthy = """status:\n- name: agt_sensor_monitor/summary\n  level: 0\n  values:\n  - key: required_streams_healthy\n    value: 'true'\n"""
    unhealthy = healthy.replace("'true'", "'false'")
    assert module.sensor_summary_healthy(healthy) is True
    assert module.sensor_summary_healthy(unhealthy) is False
    assert module.sensor_summary_healthy("status: []") is None


def test_optional_camera_absence_does_not_block_but_required_camera_does():
    module = load_module()
    topics = {"/agt/sensors/lidar/custom", "/agt/sensors/imu/data"}
    optional = module.topic_presence_check(
        "/agt/sensors/camera/image", topics, required=False
    )
    required = module.topic_presence_check(
        "/agt/sensors/camera/image", topics, required=True
    )
    assert optional["status"] == "OPTIONAL_MISSING"
    assert required["status"] == "FAIL"


def test_missing_ros2_cli_becomes_required_failure_instead_of_exception():
    module = load_module()

    def missing_runner(command, timeout):
        raise FileNotFoundError("ros2")

    report = module.run_vehicle_preflight(runner=missing_runner)
    assert report["ready"] is False
    assert report["checks"][0]["name"] == "ros2_cli"
    assert report["checks"][0]["status"] == "FAIL"
    assert "not found" in report["checks"][0]["reason"].lower()


def test_source_contains_no_motion_or_mission_dispatch():
    text = MODULE.read_text(encoding="utf-8") if MODULE.exists() else ""
    forbidden = (
        "ros2 topic pub",
        "/cmd_vel",
        "NavigateToPose",
        "ExecuteMission",
        "SetMissionRunState",
        "MoveGimbal",
    )
    for token in forbidden:
        assert token not in text
