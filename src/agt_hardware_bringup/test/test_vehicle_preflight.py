from __future__ import annotations

import importlib.util
from pathlib import Path
import subprocess
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


HEALTHY_DIAGNOSTICS = """header:
  stamp:
    sec: 1
    nanosec: 0
status:
- level: 0
  name: agt_sensor_monitor/lidar
  message: healthy
  hardware_id: ''
  values:
  - key: enabled
    value: 'true'
  - key: required
    value: 'true'
  - key: received_once
    value: 'true'
  - key: received_count
    value: '250'
  - key: rate_hz
    value: '10.020000'
  - key: min_rate_hz
    value: '8.000000'
  - key: rate_ok
    value: 'true'
  - key: message_age_sec
    value: '0.020000'
  - key: receive_age_sec
    value: '0.010000'
  - key: max_stale_sec
    value: '0.500000'
  - key: stale
    value: 'false'
  - key: timestamp_monotonic
    value: 'true'
  - key: rollback_count
    value: '0'
  - key: duplicate_stamp_count
    value: '0'
  - key: healthy
    value: 'true'
- level: 0
  name: agt_sensor_monitor/imu
  message: healthy
  hardware_id: ''
  values:
  - key: enabled
    value: 'true'
  - key: required
    value: 'true'
  - key: received_once
    value: 'true'
  - key: received_count
    value: '5000'
  - key: rate_hz
    value: '199.800000'
  - key: min_rate_hz
    value: '150.000000'
  - key: rate_ok
    value: 'true'
  - key: message_age_sec
    value: '0.004000'
  - key: receive_age_sec
    value: '0.003000'
  - key: max_stale_sec
    value: '0.200000'
  - key: stale
    value: 'false'
  - key: timestamp_monotonic
    value: 'true'
  - key: rollback_count
    value: '0'
  - key: duplicate_stamp_count
    value: '0'
  - key: healthy
    value: 'true'
- level: 0
  name: agt_sensor_monitor/summary
  message: OK
  hardware_id: ''
  values:
  - key: required_streams_healthy
    value: 'true'
"""

READY_CAMERA_GIMBAL = """state: 1
camera_alive: true
gimbal_serial_connected: true
gimbal_feedback_alive: true
move_action_ready: true
busy: false
"""


class Result:
    def __init__(self, returncode=0, stdout="", stderr=""):
        self.returncode = returncode
        self.stdout = stdout
        self.stderr = stderr


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


def test_sensor_monitor_parser_exposes_lidar_and_imu_quality_metrics():
    module = load_module()
    statuses = module.parse_sensor_monitor_diagnostics(HEALTHY_DIAGNOSTICS)

    assert statuses["summary"]["required_streams_healthy"] is True
    assert statuses["lidar"]["healthy"] is True
    assert statuses["lidar"]["rate_hz"] == 10.02
    assert statuses["lidar"]["message_age_sec"] == 0.02
    assert statuses["lidar"]["timestamp_monotonic"] is True
    assert statuses["lidar"]["rollback_count"] == 0
    assert statuses["imu"]["rate_hz"] == 199.8
    assert statuses["imu"]["received_count"] == 5000


def test_sensor_stream_check_fails_on_timestamp_rollback_even_when_topic_exists():
    module = load_module()
    unhealthy = HEALTHY_DIAGNOSTICS.replace(
        "- key: timestamp_monotonic\n    value: 'true'\n  - key: rollback_count\n    value: '0'",
        "- key: timestamp_monotonic\n    value: 'false'\n  - key: rollback_count\n    value: '1'",
        1,
    ).replace(
        "- key: healthy\n    value: 'true'",
        "- key: healthy\n    value: 'false'",
        1,
    )
    status = module.parse_sensor_monitor_diagnostics(unhealthy)["lidar"]

    check = module.sensor_stream_quality_check("lidar", status, required=True)

    assert check["status"] == "FAIL"
    assert check["metrics"]["timestamp_monotonic"] is False
    assert check["metrics"]["rollback_count"] == 1
    assert "timestamp" in check["reason"].lower()


def test_camera_gimbal_health_check_matches_frozen_capability_gate():
    module = load_module()
    ready = module.camera_gimbal_health_check(READY_CAMERA_GIMBAL, required=True)
    busy = module.camera_gimbal_health_check(
        READY_CAMERA_GIMBAL.replace("busy: false", "busy: true"), required=True
    )

    assert ready["status"] == "PASS"
    assert ready["metrics"]["state"] == 1
    assert ready["metrics"]["camera_alive"] is True
    assert ready["metrics"]["gimbal_feedback_alive"] is True
    assert busy["status"] == "FAIL"
    assert "busy" in busy["reason"].lower()


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


def test_vehicle_preflight_ignores_unrelated_diagnostics_until_sensor_monitor_arrives():
    module = load_module()
    topics = "\n".join(
        (
            "/agt/sensors/lidar/custom",
            "/agt/sensors/imu/data",
            "/agt/chassis/status/raw",
            "/agt/chassis/connected",
            "/agt/chassis/rc_state",
            "/diagnostics",
        )
    )
    unrelated = """status:\n- level: 0\n  name: another_node\n  message: OK\n  values: []\n"""
    diagnostics_calls = 0

    def runner(command, timeout):
        nonlocal diagnostics_calls
        if command == ["ros2", "topic", "list"]:
            return Result(stdout=topics)
        if command[-1] == "/agt/chassis/connected":
            return Result(stdout="data: true\n")
        if command[-1] == "/diagnostics":
            diagnostics_calls += 1
            return Result(stdout=unrelated if diagnostics_calls == 1 else HEALTHY_DIAGNOSTICS)
        return Result(stdout="message: received\n")

    report = module.run_vehicle_preflight(
        runner=runner,
        diagnostics_samples=3,
        include_host_checks=False,
    )

    assert diagnostics_calls == 2
    assert report["ready"] is True
    by_name = {check["name"]: check for check in report["checks"]}
    assert by_name["sensor_quality:lidar"]["metrics"]["rate_hz"] == 10.02
    assert by_name["sensor_quality:imu"]["metrics"]["rate_hz"] == 199.8
    assert by_name["data:/agt/chassis/rc_state"]["status"] == "PASS"


def test_required_gimbal_uses_camera_gimbal_health_not_legacy_state_topic():
    module = load_module()
    topics = "\n".join(
        (
            "/agt/sensors/lidar/custom",
            "/agt/sensors/imu/data",
            "/agt/chassis/status/raw",
            "/agt/chassis/connected",
            "/agt/chassis/rc_state",
            "/diagnostics",
            "/agt/sensors/camera/image",
            "/agt/sensors/camera/camera_info",
            "/camera_gimbal/health",
        )
    )

    def runner(command, timeout):
        if command == ["ros2", "topic", "list"]:
            return Result(stdout=topics)
        if command[-1] == "/agt/chassis/connected":
            return Result(stdout="data: true\n")
        if command[-1] == "/diagnostics":
            return Result(stdout=HEALTHY_DIAGNOSTICS)
        if command[-1] == "/camera_gimbal/health":
            return Result(stdout=READY_CAMERA_GIMBAL)
        return Result(stdout="message: received\n")

    report = module.run_vehicle_preflight(
        require_camera=True,
        require_gimbal=True,
        runner=runner,
        include_host_checks=False,
    )

    assert report["ready"] is True
    by_name = {check["name"]: check for check in report["checks"]}
    assert by_name["camera_gimbal_health"]["status"] == "PASS"
    assert "topic:/agt/gimbal/state" not in by_name


def test_missing_ros2_cli_becomes_required_failure_instead_of_exception():
    module = load_module()

    def missing_runner(command, timeout):
        raise FileNotFoundError("ros2")

    report = module.run_vehicle_preflight(
        runner=missing_runner,
        include_host_checks=False,
    )
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
        "ros2 service call /agt/safety/set_motion_enabled",
    )
    for token in forbidden:
        assert token not in text
