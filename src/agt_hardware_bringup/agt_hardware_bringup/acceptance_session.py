from __future__ import annotations

import argparse
import json
import re
import subprocess
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Callable, Sequence


Runner = Callable[[Sequence[str], float], Any]
_SAFE_LABEL_RE = re.compile(r"[^a-z0-9]+")
_PREFLIGHT_ACCEPTED_RETURN_CODES = {0, 2}


def _default_runner(command: Sequence[str], timeout: float):
    return subprocess.run(
        list(command),
        capture_output=True,
        text=True,
        timeout=timeout,
        check=False,
    )


def _utc_now(now: datetime | None = None) -> datetime:
    value = now or datetime.now(timezone.utc)
    if value.tzinfo is None:
        return value.replace(tzinfo=timezone.utc)
    return value.astimezone(timezone.utc)


def _sanitize_label(label: str) -> str:
    return _SAFE_LABEL_RE.sub("-", label.strip().lower()).strip("-")


def create_session_directory(
    output_root: str | Path,
    *,
    now: datetime | None = None,
    label: str = "",
) -> Path:
    timestamp = _utc_now(now).strftime("%Y%m%dT%H%M%SZ")
    suffix = _sanitize_label(label)
    name = f"{timestamp}-{suffix}" if suffix else timestamp
    session_dir = Path(output_root).expanduser() / name
    session_dir.mkdir(parents=True, exist_ok=False)
    return session_dir


def _run_command(
    runner: Runner,
    command: Sequence[str],
    *,
    timeout: float,
) -> dict[str, Any]:
    try:
        result = runner(list(command), timeout)
        return {
            "command": list(command),
            "returncode": int(result.returncode),
            "stdout": str(result.stdout or ""),
            "stderr": str(result.stderr or ""),
            "error": "",
        }
    except subprocess.TimeoutExpired as exc:
        return {
            "command": list(command),
            "returncode": None,
            "stdout": str(exc.stdout or ""),
            "stderr": str(exc.stderr or ""),
            "error": f"timeout after {timeout:.1f}s",
        }
    except OSError as exc:
        return {
            "command": list(command),
            "returncode": None,
            "stdout": "",
            "stderr": "",
            "error": f"{exc.__class__.__name__}: {exc}",
        }


def _read_preflight_result(path: Path) -> str | None:
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return None
    result = payload.get("result")
    return str(result) if result is not None else None


def _write_capture(path: Path, result: dict[str, Any]) -> None:
    text = result["stdout"]
    if result["stderr"]:
        text += ("" if text.endswith("\n") or not text else "\n") + result["stderr"]
    path.write_text(text, encoding="utf-8")


def _notes_template(session_time: datetime, label: str) -> str:
    label_line = label.strip() or "(none)"
    return (
        "# Vehicle acceptance notes\n\n"
        f"- Session UTC: `{session_time.isoformat()}`\n"
        f"- Label: `{label_line}`\n"
        "- Physical checklist vocabulary: `PASS / FAIL / UNVERIFIED / NOT_APPLICABLE`\n\n"
        "## Physical observations\n\n"
        "- CAN interface / bitrate: UNVERIFIED\n"
        "- MID360 network / stream quality: UNVERIFIED\n"
        "- MID360 physical extrinsic / RViz orientation: UNVERIFIED\n"
        "- BUNKER forward/angular/odometry signs: UNVERIFIED\n"
        "- Camera/gimbal hardware (when connected): UNVERIFIED\n\n"
        "## Operator notes\n\n"
        "- \n"
    )


def collect_acceptance_session(
    *,
    output_root: str | Path = "vehicle_acceptance",
    label: str = "",
    can_interface: str = "can0",
    expected_can_bitrate: int = 0,
    observation_sec: float = 5.0,
    require_camera: bool = False,
    require_gimbal: bool = False,
    command_timeout: float = 10.0,
    runner: Runner = _default_runner,
    now: datetime | None = None,
) -> Path:
    session_time = _utc_now(now)
    session_dir = create_session_directory(output_root, now=session_time, label=label)
    commands: dict[str, dict[str, Any]] = {}
    collection_failures: list[str] = []
    preflight_results: dict[str, str | None] = {}

    preflight_timeout = max(command_timeout, observation_sec + 5.0)
    preflights: list[tuple[str, Path, list[str]]] = [
        (
            "can_preflight",
            session_dir / "can_preflight.json",
            [
                "ros2",
                "run",
                "agt_hardware_bringup",
                "socketcan_preflight.py",
                "--interface",
                can_interface,
                "--expected-bitrate",
                str(expected_can_bitrate),
                "--observation-sec",
                str(observation_sec),
                "--json-output",
                str(session_dir / "can_preflight.json"),
            ],
        ),
        (
            "hardware_preflight",
            session_dir / "hardware_preflight.json",
            [
                "ros2",
                "run",
                "agt_hardware_bringup",
                "vehicle_preflight.py",
                "--json-output",
                str(session_dir / "hardware_preflight.json"),
            ],
        ),
        (
            "mapping_preflight",
            session_dir / "mapping_preflight.json",
            [
                "ros2",
                "run",
                "agt_hardware_bringup",
                "vehicle_preflight.py",
                "--require-calibration-verified",
                "--json-output",
                str(session_dir / "mapping_preflight.json"),
            ],
        ),
    ]

    if require_camera or require_gimbal:
        inspection_command = [
            "ros2",
            "run",
            "agt_hardware_bringup",
            "vehicle_preflight.py",
        ]
        if require_camera:
            inspection_command.append("--require-camera")
        if require_gimbal:
            inspection_command.append("--require-gimbal")
        inspection_path = session_dir / "inspection_hardware_preflight.json"
        inspection_command.extend(["--json-output", str(inspection_path)])
        preflights.append(("inspection_preflight", inspection_path, inspection_command))

    for name, output_path, command in preflights:
        result = _run_command(runner, command, timeout=preflight_timeout)
        commands[name] = result
        preflight_name = name.replace("_preflight", "")
        preflight_results[preflight_name] = _read_preflight_result(output_path)
        if (
            result["returncode"] not in _PREFLIGHT_ACCEPTED_RETURN_CODES
            or not output_path.is_file()
            or preflight_results[preflight_name] is None
        ):
            collection_failures.append(name)

    snapshots = (
        ("ros2_topic_list", session_dir / "ros2_topic_list.txt", ["ros2", "topic", "list"]),
        (
            "diagnostics",
            session_dir / "diagnostics.txt",
            ["ros2", "topic", "echo", "--once", "/diagnostics"],
        ),
        (
            "tf_snapshot",
            session_dir / "tf_snapshot.txt",
            [
                "ros2",
                "topic",
                "echo",
                "--qos-durability",
                "transient_local",
                "--once",
                "/tf_static",
            ],
        ),
    )
    for name, output_path, command in snapshots:
        result = _run_command(runner, command, timeout=command_timeout)
        commands[name] = result
        _write_capture(output_path, result)
        if result["returncode"] != 0:
            collection_failures.append(name)

    (session_dir / "notes.md").write_text(
        _notes_template(session_time, label), encoding="utf-8"
    )

    manifest = {
        "schema": "agt.hardware.acceptance-session/v1",
        "timestamp": session_time.isoformat(),
        "label": label,
        "session_dir": str(session_dir),
        "collection_complete": not collection_failures,
        "collection_failures": collection_failures,
        "preflight_results": preflight_results,
        "commands": commands,
    }
    (session_dir / "session.json").write_text(
        json.dumps(manifest, indent=2, sort_keys=True) + "\n",
        encoding="utf-8",
    )
    return session_dir


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Collect an immutable read-only first-vehicle acceptance evidence session"
    )
    parser.add_argument("--output-root", default="vehicle_acceptance")
    parser.add_argument("--label", default="")
    parser.add_argument("--can-interface", default="can0")
    parser.add_argument("--expected-can-bitrate", type=int, default=0)
    parser.add_argument("--observation-sec", type=float, default=5.0)
    parser.add_argument("--command-timeout", type=float, default=10.0)
    parser.add_argument("--require-camera", action="store_true")
    parser.add_argument("--require-gimbal", action="store_true")
    args = parser.parse_args(argv)
    if args.expected_can_bitrate < 0:
        parser.error("--expected-can-bitrate must be >= 0")
    if args.observation_sec < 0:
        parser.error("--observation-sec must be >= 0")
    if args.command_timeout <= 0:
        parser.error("--command-timeout must be > 0")

    try:
        session_dir = collect_acceptance_session(
            output_root=args.output_root,
            label=args.label,
            can_interface=args.can_interface,
            expected_can_bitrate=args.expected_can_bitrate,
            observation_sec=args.observation_sec,
            require_camera=args.require_camera,
            require_gimbal=args.require_gimbal,
            command_timeout=args.command_timeout,
        )
    except FileExistsError as exc:
        parser.error(f"session directory already exists: {exc.filename}")

    manifest = json.loads((session_dir / "session.json").read_text(encoding="utf-8"))
    print(json.dumps({
        "session_dir": str(session_dir),
        "collection_complete": manifest["collection_complete"],
        "collection_failures": manifest["collection_failures"],
        "preflight_results": manifest["preflight_results"],
    }, indent=2, sort_keys=True))
    return 0 if manifest["collection_complete"] else 3


if __name__ == "__main__":
    raise SystemExit(main())
