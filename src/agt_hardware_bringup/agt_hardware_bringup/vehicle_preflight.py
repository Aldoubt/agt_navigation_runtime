from __future__ import annotations

import argparse
import json
import re
import subprocess
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Callable, Sequence


Runner = Callable[[Sequence[str], float], Any]
_SENSOR_NAME_RE = re.compile(r"^\s*-?\s*name:\s*agt_sensor_monitor/([A-Za-z0-9_-]+)\s*$")
_ANY_NAME_RE = re.compile(r"^\s*-?\s*name:\s*(\S.*)\s*$")
_DIAG_KEY_RE = re.compile(r"^\s*-?\s*key:\s*(\S.*)\s*$")
_DIAG_VALUE_RE = re.compile(r"^\s*value:\s*(.*)\s*$")
_SIMPLE_FIELD_RE = re.compile(r"^\s*([A-Za-z0-9_]+):\s*(.*?)\s*$")
_INT_RE = re.compile(r"^[+-]?\d+$")
_FLOAT_RE = re.compile(
    r"^[+-]?(?:\d+\.\d*|\d*\.\d+|\d+)(?:[eE][+-]?\d+)?$"
)


def make_check(
    name: str,
    *,
    required: bool,
    ok: bool,
    evidence: str = "",
    reason: str = "",
    metrics: dict[str, Any] | None = None,
) -> dict[str, Any]:
    check: dict[str, Any] = {
        "name": name,
        "required": required,
        "status": "PASS" if ok else ("FAIL" if required else "OPTIONAL_MISSING"),
        "evidence": evidence,
        "reason": reason,
    }
    if metrics is not None:
        check["metrics"] = metrics
    return check


def summarize_checks(checks: list[dict[str, Any]]) -> dict[str, Any]:
    ready = not any(
        check["required"] and check["status"] != "PASS" for check in checks
    )
    return {
        "schema": "agt.hardware.preflight/v2",
        "timestamp": datetime.now(timezone.utc).isoformat(),
        "ready": ready,
        "result": "PASS" if ready else "BLOCKED",
        "blockers": [
            check["name"]
            for check in checks
            if check["required"] and check["status"] != "PASS"
        ],
        "checks": checks,
    }


def _parse_scalar(raw: str) -> Any:
    value = raw.strip()
    if len(value) >= 2 and value[0] == value[-1] and value[0] in ("'", '"'):
        value = value[1:-1]
    lowered = value.lower()
    if lowered == "true":
        return True
    if lowered == "false":
        return False
    if lowered in ("none", "null", "~"):
        return None
    if _INT_RE.fullmatch(value):
        try:
            return int(value)
        except ValueError:
            pass
    if _FLOAT_RE.fullmatch(value):
        try:
            return float(value)
        except ValueError:
            pass
    return value


def parse_std_bool_echo(text: str) -> bool | None:
    match = re.search(r"(?:^|\n)\s*data:\s*(true|false)\s*(?:\n|$)", text, re.I)
    if not match:
        return None
    return match.group(1).lower() == "true"


def parse_sensor_monitor_diagnostics(text: str) -> dict[str, dict[str, Any]]:
    """Extract `agt_sensor_monitor/*` key/value diagnostics from ROS YAML output."""
    statuses: dict[str, dict[str, Any]] = {}
    current: str | None = None
    pending_key: str | None = None

    for line in text.splitlines():
        name_match = _SENSOR_NAME_RE.match(line)
        if name_match:
            current = name_match.group(1)
            statuses.setdefault(current, {})
            pending_key = None
            continue

        other_name = _ANY_NAME_RE.match(line)
        if other_name:
            current = None
            pending_key = None
            continue

        if current is None:
            continue

        key_match = _DIAG_KEY_RE.match(line)
        if key_match:
            pending_key = str(_parse_scalar(key_match.group(1)))
            continue

        value_match = _DIAG_VALUE_RE.match(line)
        if value_match and pending_key:
            statuses[current][pending_key] = _parse_scalar(value_match.group(1))
            pending_key = None

    return statuses


def sensor_summary_healthy(text: str) -> bool | None:
    summary = parse_sensor_monitor_diagnostics(text).get("summary")
    if not summary:
        return None
    value = summary.get("required_streams_healthy")
    return value if isinstance(value, bool) else None


def _sensor_quality_metrics(status: dict[str, Any]) -> dict[str, Any]:
    keys = (
        "received_once",
        "received_count",
        "rate_hz",
        "min_rate_hz",
        "rate_ok",
        "message_age_sec",
        "receive_age_sec",
        "max_stale_sec",
        "stale",
        "timestamp_monotonic",
        "rollback_count",
        "duplicate_stamp_count",
        "healthy",
    )
    return {key: status[key] for key in keys if key in status}


def sensor_stream_quality_check(
    stream_name: str,
    status: dict[str, Any] | None,
    *,
    required: bool,
) -> dict[str, Any]:
    metrics = _sensor_quality_metrics(status or {})
    problems: list[str] = []
    if not status:
        problems.append("sensor-monitor status missing")
    else:
        if status.get("received_once") is not True:
            problems.append("no message received")
        if status.get("rate_ok") is not True:
            problems.append("rate below configured minimum or unavailable")
        if status.get("stale") is True:
            problems.append("stream is stale")
        if status.get("timestamp_monotonic") is not True:
            problems.append("timestamp is not monotonic")
        if status.get("healthy") is not True:
            problems.append("sensor-monitor marks stream unhealthy")

    ok = not problems
    return make_check(
        f"sensor_quality:{stream_name}",
        required=required,
        ok=ok,
        evidence=(
            f"rate_hz={metrics.get('rate_hz')}, "
            f"message_age_sec={metrics.get('message_age_sec')}, "
            f"timestamp_monotonic={metrics.get('timestamp_monotonic')}"
            if metrics
            else ""
        ),
        reason="; ".join(problems),
        metrics=metrics,
    )


def _parse_simple_fields(text: str) -> dict[str, Any]:
    fields: dict[str, Any] = {}
    for line in text.splitlines():
        match = _SIMPLE_FIELD_RE.match(line)
        if not match:
            continue
        fields[match.group(1)] = _parse_scalar(match.group(2))
    return fields


def camera_gimbal_health_check(text: str, *, required: bool) -> dict[str, Any]:
    """Match the frozen C1 inspection admission gate exactly."""
    fields = _parse_simple_fields(text)
    expected = {
        "state": 1,
        "camera_alive": True,
        "gimbal_serial_connected": True,
        "gimbal_feedback_alive": True,
        "move_action_ready": True,
        "busy": False,
    }
    problems = [
        f"{key}={fields.get(key)!r}, expected {value!r}"
        for key, value in expected.items()
        if fields.get(key) != value
    ]
    return make_check(
        "camera_gimbal_health",
        required=required,
        ok=not problems,
        evidence="READY" if not problems else "",
        reason="; ".join(problems),
        metrics={key: fields.get(key) for key in expected},
    )


def topic_presence_check(
    topic: str, topics: set[str], *, required: bool
) -> dict[str, Any]:
    exists = topic in topics
    return make_check(
        f"topic:{topic}",
        required=required,
        ok=exists,
        evidence="present" if exists else "",
        reason="" if exists else "topic missing",
    )


def _default_runner(command: Sequence[str], timeout: float):
    return subprocess.run(
        list(command),
        check=False,
        capture_output=True,
        text=True,
        timeout=timeout,
    )


def _run(
    runner: Runner, command: Sequence[str], timeout: float
) -> tuple[bool, str, str]:
    try:
        result = runner(command, timeout)
    except FileNotFoundError:
        return False, "", "ros2 executable not found"
    except subprocess.TimeoutExpired:
        return False, "", f"command timeout after {timeout:.1f}s"
    except OSError as exc:
        return False, "", f"command failed: {exc.__class__.__name__}"
    returncode = int(getattr(result, "returncode", 0))
    stdout = str(getattr(result, "stdout", "") or "")
    stderr = str(getattr(result, "stderr", "") or "")
    if returncode != 0:
        return False, stdout, stderr.strip() or f"returncode {returncode}"
    return True, stdout, ""


def _echo_check(
    runner: Runner,
    topic: str,
    *,
    timeout: float,
    required: bool,
) -> dict[str, Any]:
    ok, _, reason = _run(
        runner, ["ros2", "topic", "echo", "--once", topic], timeout
    )
    return make_check(
        f"data:{topic}",
        required=required,
        ok=ok,
        evidence="message received" if ok else "",
        reason=reason,
    )


def _collect_sensor_monitor_diagnostics(
    runner: Runner,
    *,
    timeout: float,
    max_samples: int,
) -> tuple[dict[str, dict[str, Any]], str]:
    last_reason = "sensor-monitor diagnostics not observed"
    for _ in range(max(1, max_samples)):
        ok, text, reason = _run(
            runner,
            ["ros2", "topic", "echo", "--once", "/diagnostics"],
            timeout,
        )
        if not ok:
            last_reason = reason
            continue
        statuses = parse_sensor_monitor_diagnostics(text)
        if "summary" in statuses:
            return statuses, ""
        last_reason = "sample belonged to another diagnostics publisher"
    return {}, last_reason


def run_vehicle_preflight(
    *,
    require_camera: bool = False,
    require_gimbal: bool = False,
    topic_timeout: float = 3.0,
    diagnostics_samples: int = 5,
    include_host_checks: bool = True,
    runner: Runner = _default_runner,
) -> dict[str, Any]:
    # `include_host_checks` is intentionally accepted now so this read-only ROS
    # contract can be composed with host evidence without changing callers.
    # Host checks are added separately and never grant or change permissions.
    del include_host_checks

    checks: list[dict[str, Any]] = []
    ok, stdout, reason = _run(runner, ["ros2", "topic", "list"], topic_timeout)
    checks.append(
        make_check(
            "ros2_cli",
            required=True,
            ok=ok,
            evidence="topic list available" if ok else "",
            reason=reason,
        )
    )
    if not ok:
        return summarize_checks(checks)

    topics = {line.strip() for line in stdout.splitlines() if line.strip()}
    required_topics = (
        "/agt/sensors/lidar/custom",
        "/agt/sensors/imu/data",
        "/agt/chassis/status/raw",
        "/agt/chassis/connected",
        "/agt/chassis/rc_state",
        "/diagnostics",
    )
    for topic in required_topics:
        checks.append(topic_presence_check(topic, topics, required=True))

    for topic in ("/agt/chassis/status/raw", "/agt/chassis/rc_state"):
        if topic in topics:
            checks.append(
                _echo_check(runner, topic, timeout=topic_timeout, required=True)
            )

    connected_topic = "/agt/chassis/connected"
    if connected_topic in topics:
        echo_ok, connected_text, echo_reason = _run(
            runner,
            ["ros2", "topic", "echo", "--once", connected_topic],
            topic_timeout,
        )
        connected = parse_std_bool_echo(connected_text) if echo_ok else None
        checks.append(
            make_check(
                "bunker_connected",
                required=True,
                ok=connected is True,
                evidence=f"connected={connected}" if connected is not None else "",
                reason=(
                    echo_reason
                    if not echo_ok
                    else "connected is false or could not be parsed"
                    if connected is not True
                    else ""
                ),
            )
        )

    if "/diagnostics" in topics:
        statuses, diag_reason = _collect_sensor_monitor_diagnostics(
            runner,
            timeout=topic_timeout,
            max_samples=diagnostics_samples,
        )
        summary = statuses.get("summary", {})
        healthy = summary.get("required_streams_healthy")
        checks.append(
            make_check(
                "sensor_monitor_summary",
                required=True,
                ok=healthy is True,
                evidence=(
                    f"required_streams_healthy={healthy}"
                    if isinstance(healthy, bool)
                    else ""
                ),
                reason=(
                    diag_reason
                    if not statuses
                    else "required sensor streams are unhealthy or summary is incomplete"
                    if healthy is not True
                    else ""
                ),
                metrics=summary,
            )
        )
        checks.append(
            sensor_stream_quality_check(
                "lidar", statuses.get("lidar"), required=True
            )
        )
        checks.append(
            sensor_stream_quality_check("imu", statuses.get("imu"), required=True)
        )

    camera_topics = (
        "/agt/sensors/camera/image",
        "/agt/sensors/camera/camera_info",
    )
    for topic in camera_topics:
        checks.append(topic_presence_check(topic, topics, required=require_camera))
    if require_camera and "/agt/sensors/camera/camera_info" in topics:
        # CameraInfo is deliberately used as the small live-message proof;
        # dumping a full image through the CLI is expensive and adds no health
        # information beyond the frozen capability health gate.
        checks.append(
            _echo_check(
                runner,
                "/agt/sensors/camera/camera_info",
                timeout=topic_timeout,
                required=True,
            )
        )

    c1_health_topic = "/camera_gimbal/health"
    checks.append(
        topic_presence_check(c1_health_topic, topics, required=require_gimbal)
    )
    if require_gimbal and c1_health_topic in topics:
        health_ok, health_text, health_reason = _run(
            runner,
            ["ros2", "topic", "echo", "--once", c1_health_topic],
            topic_timeout,
        )
        if health_ok:
            checks.append(camera_gimbal_health_check(health_text, required=True))
        else:
            checks.append(
                make_check(
                    "camera_gimbal_health",
                    required=True,
                    ok=False,
                    reason=health_reason,
                )
            )

    return summarize_checks(checks)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Read-only first-vehicle ROS preflight")
    parser.add_argument("--require-camera", action="store_true")
    parser.add_argument("--require-gimbal", action="store_true")
    parser.add_argument("--topic-timeout", type=float, default=3.0)
    parser.add_argument(
        "--diagnostics-samples",
        type=int,
        default=5,
        help="maximum /diagnostics samples to inspect for agt_sensor_monitor",
    )
    parser.add_argument("--json-output", default="hardware_preflight.json")
    args = parser.parse_args(argv)
    if args.diagnostics_samples < 1:
        parser.error("--diagnostics-samples must be >= 1")

    report = run_vehicle_preflight(
        require_camera=args.require_camera,
        require_gimbal=args.require_gimbal,
        topic_timeout=args.topic_timeout,
        diagnostics_samples=args.diagnostics_samples,
    )
    encoded = json.dumps(report, indent=2, sort_keys=True)
    print(encoded)
    if args.json_output:
        Path(args.json_output).write_text(encoded + "\n", encoding="utf-8")
    return 0 if report["ready"] else 2


if __name__ == "__main__":
    raise SystemExit(main())
