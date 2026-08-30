from __future__ import annotations

import argparse
import json
import re
import subprocess
from pathlib import Path
from typing import Any


_HEADER_RE = re.compile(r"^\d+:\s+([^:@]+)(?:@[^:]+)?:.*\bstate\s+(\S+)")
_BITRATE_RE = re.compile(r"\bbitrate\s+(\d+)\b")
_CAN_STATE_RE = re.compile(r"\bcan state\s+([A-Z-]+)")
_BERR_RE = re.compile(r"berr-counter\s+tx\s+(\d+)\s+rx\s+(\d+)")


def _parse_error_counter(lines: list[str], prefix: str) -> int | None:
    for index, line in enumerate(lines):
        if line.strip().startswith(prefix) and index + 1 < len(lines):
            values = lines[index + 1].split()
            if len(values) >= 3:
                try:
                    return int(values[2])
                except ValueError:
                    return None
    return None


def parse_ip_link_details(text: str) -> dict[str, Any]:
    """Parse the small SocketCAN health subset emitted by `ip -details -statistics`."""
    details: dict[str, Any] = {
        "is_can": "link/can" in text,
    }
    lines = text.splitlines()
    if lines:
        header = _HEADER_RE.search(lines[0])
        if header:
            details["interface"] = header.group(1)
            details["oper_state"] = header.group(2)

    match = _CAN_STATE_RE.search(text)
    if match:
        details["can_state"] = match.group(1)
    match = _BITRATE_RE.search(text)
    if match:
        details["bitrate"] = int(match.group(1))
    match = _BERR_RE.search(text)
    if match:
        details["berr_tx"] = int(match.group(1))
        details["berr_rx"] = int(match.group(2))

    details["rx_errors"] = _parse_error_counter(lines, "RX:")
    details["tx_errors"] = _parse_error_counter(lines, "TX:")
    return details


def evaluate_can_link(
    details: dict[str, Any], expected_bitrate: int = 0
) -> tuple[bool, list[str]]:
    blockers: list[str] = []
    if not details.get("interface"):
        return False, ["missing_interface_evidence"]
    if not details.get("is_can"):
        blockers.append("not_can_interface")

    oper_state = str(details.get("oper_state", "UNKNOWN"))
    if oper_state != "UP":
        blockers.append(f"oper_state:{oper_state}")

    can_state = details.get("can_state")
    if can_state == "BUS-OFF":
        blockers.append("can_state:BUS-OFF")

    if expected_bitrate > 0:
        observed = details.get("bitrate")
        if observed != expected_bitrate:
            blockers.append(f"bitrate_mismatch:{observed}!={expected_bitrate}")

    return not blockers, blockers


def collect_can_evidence(interface: str) -> tuple[dict[str, Any], list[str]]:
    sysfs = Path("/sys/class/net") / interface
    if not sysfs.exists():
        return {}, [f"interface_missing:{interface}"]
    try:
        result = subprocess.run(
            ["ip", "-details", "-statistics", "link", "show", interface],
            check=False,
            capture_output=True,
            text=True,
            timeout=3.0,
        )
    except (OSError, subprocess.TimeoutExpired) as exc:
        return {}, [f"ip_link_failed:{exc.__class__.__name__}"]
    if result.returncode != 0:
        return {}, [f"ip_link_returncode:{result.returncode}"]
    return parse_ip_link_details(result.stdout), []


def run_preflight(interface: str, expected_bitrate: int = 0) -> dict[str, Any]:
    details, collection_errors = collect_can_evidence(interface)
    if collection_errors:
        return {
            "interface": interface,
            "ready": False,
            "blockers": collection_errors,
            "evidence": details,
        }
    ready, blockers = evaluate_can_link(details, expected_bitrate)
    return {
        "interface": interface,
        "expected_bitrate": expected_bitrate or None,
        "ready": ready,
        "blockers": blockers,
        "evidence": details,
    }


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Read-only SocketCAN health preflight")
    parser.add_argument("--interface", default="can0")
    parser.add_argument("--expected-bitrate", type=int, default=0)
    parser.add_argument("--json-output", default="")
    args = parser.parse_args(argv)

    report = run_preflight(args.interface, args.expected_bitrate)
    encoded = json.dumps(report, indent=2, sort_keys=True)
    print(encoded)
    if args.json_output:
        Path(args.json_output).write_text(encoded + "\n", encoding="utf-8")
    return 0 if report["ready"] else 2


if __name__ == "__main__":
    raise SystemExit(main())
