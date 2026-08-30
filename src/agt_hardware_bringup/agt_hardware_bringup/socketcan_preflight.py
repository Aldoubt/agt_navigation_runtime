from __future__ import annotations

import argparse
import json
import re
import subprocess
import time
from pathlib import Path
from typing import Any, Callable


_HEADER_RE = re.compile(r"^\d+:\s+([^:@]+)(?:@[^:]+)?:.*\bstate\s+(\S+)")
_BITRATE_RE = re.compile(r"\bbitrate\s+(\d+)\b")
_CAN_STATE_RE = re.compile(r"\bcan state\s+([A-Z-]+)")
_BERR_RE = re.compile(r"berr-counter\s+tx\s+(\d+)\s+rx\s+(\d+)")
_CONTROLLER_ERROR_COUNTERS = ("berr_tx", "berr_rx")
_CUMULATIVE_LINK_COUNTERS = (
    "rx_errors",
    "tx_errors",
    "rx_dropped",
    "tx_dropped",
)
Collector = Callable[[str], tuple[dict[str, Any], list[str]]]
Sleeper = Callable[[float], None]


def _parse_link_stats(lines: list[str], prefix: str) -> tuple[int | None, int | None]:
    """Return the `errors` and `dropped` columns from an ip-link RX/TX block."""
    for index, line in enumerate(lines):
        if line.strip().startswith(prefix) and index + 1 < len(lines):
            values = lines[index + 1].split()
            if len(values) >= 4:
                try:
                    return int(values[2]), int(values[3])
                except ValueError:
                    return None, None
    return None, None


def parse_ip_link_details(text: str) -> dict[str, Any]:
    """Parse the SocketCAN health subset emitted by `ip -details -statistics`."""
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

    details["rx_errors"], details["rx_dropped"] = _parse_link_stats(lines, "RX:")
    details["tx_errors"], details["tx_dropped"] = _parse_link_stats(lines, "TX:")
    return details


def evaluate_can_link(
    details: dict[str, Any], expected_bitrate: int = 0
) -> tuple[bool, list[str]]:
    """Evaluate one read-only SocketCAN snapshot.

    A healthy field CAN link must be UP and, when the kernel reports a CAN
    controller state, ERROR-ACTIVE. `expected_bitrate == 0` intentionally
    means that the bitrate is not asserted yet.
    """
    blockers: list[str] = []
    if not details.get("interface"):
        return False, ["missing_interface_evidence"]
    if not details.get("is_can"):
        blockers.append("not_can_interface")

    oper_state = str(details.get("oper_state", "UNKNOWN"))
    if oper_state != "UP":
        blockers.append(f"oper_state:{oper_state}")

    can_state = details.get("can_state")
    if can_state and can_state != "ERROR-ACTIVE":
        blockers.append(f"can_state:{can_state}")

    if expected_bitrate > 0:
        observed = details.get("bitrate")
        if observed != expected_bitrate:
            blockers.append(f"bitrate_mismatch:{observed}!={expected_bitrate}")

    return not blockers, blockers


def _counter_deltas(
    before: dict[str, Any], after: dict[str, Any]
) -> tuple[dict[str, int], list[str]]:
    """Compare dynamic CAN controller counters and cumulative link counters.

    SocketCAN's `berr-counter` fields are the controller TEC/REC values. They
    are allowed to decrease as successful CAN traffic recovers the controller;
    only an increase during the observation window is a blocker.

    RX/TX error/drop fields from the link statistics are cumulative. An
    increase means new transport errors/drops, while a decrease means the
    interface/statistics were reset during the acceptance window. Both make
    that observation unsuitable as clean acceptance evidence.
    """
    deltas: dict[str, int] = {}
    blockers: list[str] = []

    for field in _CONTROLLER_ERROR_COUNTERS:
        start = before.get(field)
        end = after.get(field)
        if not isinstance(start, int) or not isinstance(end, int):
            continue
        delta = end - start
        deltas[field] = delta
        if delta > 0:
            blockers.append(f"counter_increase:{field}:+{delta}")

    for field in _CUMULATIVE_LINK_COUNTERS:
        start = before.get(field)
        end = after.get(field)
        if not isinstance(start, int) or not isinstance(end, int):
            continue
        delta = end - start
        deltas[field] = delta
        if delta < 0:
            blockers.append(f"counter_reset:{field}:{start}->{end}")
        elif delta > 0:
            blockers.append(f"counter_increase:{field}:+{delta}")

    return deltas, blockers


def evaluate_can_observation(
    before: dict[str, Any],
    after: dict[str, Any],
    expected_bitrate: int = 0,
) -> tuple[bool, list[str], dict[str, int]]:
    """Evaluate CAN stability across two read-only snapshots."""
    _, before_blockers = evaluate_can_link(before, expected_bitrate)
    _, after_blockers = evaluate_can_link(after, expected_bitrate)
    deltas, delta_blockers = _counter_deltas(before, after)

    blockers: list[str] = []
    for blocker in (*before_blockers, *after_blockers, *delta_blockers):
        if blocker not in blockers:
            blockers.append(blocker)
    return not blockers, blockers, deltas


def collect_can_evidence(interface: str) -> tuple[dict[str, Any], list[str]]:
    """Read SocketCAN state without changing the network interface."""
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


def run_preflight(
    interface: str,
    expected_bitrate: int = 0,
    *,
    observation_sec: float = 0.0,
    collector: Collector = collect_can_evidence,
    sleeper: Sleeper = time.sleep,
) -> dict[str, Any]:
    """Run a read-only SocketCAN preflight.

    The Python API defaults to a snapshot because the hardware launch invokes
    it synchronously before composing drivers. The CLI opts into a time window
    by default so field acceptance can detect newly accumulating bus errors.
    """
    before, collection_errors = collector(interface)
    if collection_errors:
        return {
            "interface": interface,
            "expected_bitrate": expected_bitrate or None,
            "observation_sec": max(0.0, observation_sec),
            "ready": False,
            "blockers": collection_errors,
            "evidence": before,
        }

    if observation_sec <= 0.0:
        ready, blockers = evaluate_can_link(before, expected_bitrate)
        return {
            "interface": interface,
            "expected_bitrate": expected_bitrate or None,
            "observation_sec": 0.0,
            "ready": ready,
            "blockers": blockers,
            "evidence": before,
        }

    sleeper(observation_sec)
    after, after_errors = collector(interface)
    if after_errors:
        return {
            "interface": interface,
            "expected_bitrate": expected_bitrate or None,
            "observation_sec": observation_sec,
            "ready": False,
            "blockers": after_errors,
            "evidence": {"before": before, "after": after, "delta": {}},
        }

    ready, blockers, deltas = evaluate_can_observation(
        before, after, expected_bitrate
    )
    return {
        "interface": interface,
        "expected_bitrate": expected_bitrate or None,
        "observation_sec": observation_sec,
        "ready": ready,
        "blockers": blockers,
        "evidence": {
            "before": before,
            "after": after,
            "delta": deltas,
        },
    }


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Read-only SocketCAN health preflight")
    parser.add_argument("--interface", default="can0")
    parser.add_argument("--expected-bitrate", type=int, default=0)
    parser.add_argument(
        "--observation-sec",
        type=float,
        default=5.0,
        help="read-only error-counter observation window; 0 performs one snapshot",
    )
    parser.add_argument("--json-output", default="")
    args = parser.parse_args(argv)
    if args.observation_sec < 0.0:
        parser.error("--observation-sec must be >= 0")

    report = run_preflight(
        args.interface,
        args.expected_bitrate,
        observation_sec=args.observation_sec,
    )
    encoded = json.dumps(report, indent=2, sort_keys=True)
    print(encoded)
    if args.json_output:
        Path(args.json_output).write_text(encoded + "\n", encoding="utf-8")
    return 0 if report["ready"] else 2


if __name__ == "__main__":
    raise SystemExit(main())
