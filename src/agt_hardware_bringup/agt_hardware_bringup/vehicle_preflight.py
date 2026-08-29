from __future__ import annotations

import argparse
import json
import re
import subprocess
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Callable, Sequence


Runner = Callable[[Sequence[str], float], Any]


def make_check(
    name: str,
    *,
    required: bool,
    ok: bool,
    evidence: str = "",
    reason: str = "",
) -> dict[str, Any]:
    return {
        "name": name,
        "required": required,
        "status": "PASS" if ok else ("FAIL" if required else "OPTIONAL_MISSING"),
        "evidence": evidence,
        "reason": reason,
    }


def summarize_checks(checks: list[dict[str, Any]]) -> dict[str, Any]:
    return {
        "schema": "agt.hardware.preflight/v1",
        "timestamp": datetime.now(timezone.utc).isoformat(),
        "ready": not any(
            check["required"] and check["status"] != "PASS" for check in checks
        ),
        "checks": checks,
    }


def parse_std_bool_echo(text: str) -> bool | None:
    match = re.search(r"(?:^|\n)\s*data:\s*(true|false)\s*(?:\n|$)", text, re.I)
    if not match:
        return None
    return match.group(1).lower() == "true"


def sensor_summary_healthy(text: str) -> bool | None:
    marker = "name: agt_sensor_monitor/summary"
    start = text.find(marker)
    if start < 0:
        return None
    segment = text[start:]
    next_status = segment.find("\n- name:", len(marker))
    if next_status >= 0:
        segment = segment[:next_status]
    match = re.search(
        r"key:\s*required_streams_healthy\s*\n\s*value:\s*['\"]?(true|false)['\"]?",
        segment,
        re.I,
    )
    if not match:
        return None
    return match.group(1).lower() == "true"


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
    ok, stdout, reason = _run(
        runner, ["ros2", "topic", "echo", "--once", topic], timeout
    )
    return make_check(
        f"data:{topic}",
        required=required,
        ok=ok,
        evidence="message received" if ok else "",
        reason=reason,
    )


def run_vehicle_preflight(
    *,
    require_camera: bool = False,
    require_gimbal: bool = False,
    topic_timeout: float = 3.0,
    runner: Runner = _default_runner,
) -> dict[str, Any]:
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
    required_streams = (
        "/agt/sensors/lidar/custom",
        "/agt/sensors/imu/data",
        "/agt/chassis/status/raw",
        "/agt/chassis/connected",
        "/diagnostics",
    )
    for topic in required_streams:
        checks.append(topic_presence_check(topic, topics, required=True))

    for topic in (
        "/agt/sensors/lidar/custom",
        "/agt/sensors/imu/data",
        "/agt/chassis/status/raw",
    ):
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

    diagnostics_topic = "/diagnostics"
    if diagnostics_topic in topics:
        diag_ok, diag_text, diag_reason = _run(
            runner,
            ["ros2", "topic", "echo", "--once", diagnostics_topic],
            topic_timeout,
        )
        healthy = sensor_summary_healthy(diag_text) if diag_ok else None
        checks.append(
            make_check(
                "sensor_monitor_summary",
                required=True,
                ok=healthy is True,
                evidence=(
                    f"required_streams_healthy={healthy}"
                    if healthy is not None
                    else ""
                ),
                reason=(
                    diag_reason
                    if not diag_ok
                    else "summary missing/unparseable or unhealthy"
                    if healthy is not True
                    else ""
                ),
            )
        )

    optional_topics = (
        ("/agt/sensors/camera/image", require_camera),
        ("/agt/sensors/camera/camera_info", require_camera),
        ("/agt/gimbal/state", require_gimbal),
    )
    for topic, required in optional_topics:
        checks.append(topic_presence_check(topic, topics, required=required))
        if topic in topics:
            checks.append(
                _echo_check(runner, topic, timeout=topic_timeout, required=required)
            )

    return summarize_checks(checks)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Read-only first-vehicle ROS preflight")
    parser.add_argument("--require-camera", action="store_true")
    parser.add_argument("--require-gimbal", action="store_true")
    parser.add_argument("--topic-timeout", type=float, default=3.0)
    parser.add_argument("--json-output", default="hardware_preflight.json")
    args = parser.parse_args(argv)

    report = run_vehicle_preflight(
        require_camera=args.require_camera,
        require_gimbal=args.require_gimbal,
        topic_timeout=args.topic_timeout,
    )
    encoded = json.dumps(report, indent=2, sort_keys=True)
    print(encoded)
    if args.json_output:
        Path(args.json_output).write_text(encoded + "\n", encoding="utf-8")
    return 0 if report["ready"] else 2


if __name__ == "__main__":
    raise SystemExit(main())
