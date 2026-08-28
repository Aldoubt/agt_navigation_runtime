from __future__ import annotations

import csv
import json
import math
import struct
import zlib
from pathlib import Path

import yaml

NEGATIVE_BRIDGE_TYPES = {"mixed_bridge", "clearance_only_bridge"}
RESULT_MODES = {"expectation_match", "reference_probe"}


def _radius(payload, name):
    try:
        value = float(payload["radius_m"])
    except Exception as exc:
        raise ValueError(f"{name} radius_m is required") from exc
    if not math.isfinite(value) or value <= 0:
        raise ValueError(f"{name} radius_m must be positive and finite")
    return value


def _pose(value, label):
    if not isinstance(value, dict):
        raise ValueError(f"{label} pose must be an object")
    out = {}
    for key in ("x", "y", "yaw"):
        try:
            out[key] = float(value[key])
        except Exception as exc:
            raise ValueError(f"{label} pose requires finite {key}") from exc
        if not math.isfinite(out[key]):
            raise ValueError(f"{label} pose requires finite {key}")
    return out


def _request(test, direction, expected, reason, radius):
    case = str(test.get("id") or f"{test['pair_id']}-{test['side']}")
    segment = test.get(direction)
    if not isinstance(segment, dict):
        raise ValueError(f"{case} is missing {direction} start/goal")
    return {
        "request_id": f"{case}-{direction}",
        "case_id": case,
        "pair_id": str(test["pair_id"]),
        "side": str(test["side"]),
        "direction": direction,
        "radius_m": radius,
        "expected_success": bool(expected),
        "expectation_class": "positive" if expected else "negative_control",
        "negative_reason": reason,
        "baseline_connected": bool(test.get("baseline_connected", False)),
        "conservative_connected": bool(test.get("conservative_connected", False)),
        "start": _pose(segment.get("start"), f"{case} {direction} start"),
        "goal": _pose(segment.get("goal"), f"{case} {direction} goal"),
    }


def build_smoke_manifest(planner_pairs, gap_diagnostics):
    pr = _radius(planner_pairs, "planner_pairs")
    dr = _radius(gap_diagnostics, "gap_diagnostics")
    if not math.isclose(pr, dr, rel_tol=0, abs_tol=1e-9):
        raise ValueError(
            f"planner_pairs radius {pr} does not match diagnostics radius {dr}"
        )
    tests = planner_pairs.get("tests")
    records = gap_diagnostics.get("records")
    if not isinstance(tests, list) or not isinstance(records, list):
        raise ValueError("planner_pairs.tests and gap_diagnostics.records must be lists")

    by_case = {}
    for test in tests:
        case = str(test.get("id") or f"{test.get('pair_id')}-{test.get('side')}")
        if case in by_case:
            raise ValueError(f"duplicate planner pair test id: {case}")
        by_case[case] = test

    positive = [
        test
        for test in tests
        if bool(test.get("enabled")) and bool(test.get("conservative_connected"))
    ]
    negative = []
    reasons = {}
    for record in records:
        bridge = str(record.get("bridge_type", ""))
        if (
            str(record.get("evaluation_status")) != "evaluated"
            or bool(record.get("strict_connected"))
            or bridge not in NEGATIVE_BRIDGE_TYPES
        ):
            continue
        case = f"{record.get('pair_id')}-{record.get('side')}"
        if case not in by_case:
            raise ValueError(f"negative diagnostic case {case} has no planner pair poses")
        if case in reasons:
            raise ValueError(f"duplicate negative diagnostic case: {case}")
        negative.append(by_case[case])
        reasons[case] = bridge

    requests = []
    seen = set()
    for test, expected in [(item, True) for item in positive] + [
        (item, False) for item in negative
    ]:
        case = str(test.get("id") or f"{test['pair_id']}-{test['side']}")
        for direction in ("forward", "reverse"):
            item = _request(
                test,
                direction,
                expected,
                None if expected else reasons[case],
                pr,
            )
            if item["request_id"] in seen:
                raise ValueError(f"duplicate request id: {item['request_id']}")
            seen.add(item["request_id"])
            requests.append(item)

    counts = {
        "positive_pair_sides": len(positive),
        "negative_pair_sides": len(negative),
        "positive_requests": 2 * len(positive),
        "negative_requests": 2 * len(negative),
        "request_count": len(requests),
    }
    return {
        "schema_version": 1,
        "method": "nav2_headland_planner_smoke_manifest",
        "radius_m": pr,
        "planner_pair_method": planner_pairs.get("method"),
        "gap_diagnostic_method": gap_diagnostics.get("method"),
        "negative_bridge_types": sorted(NEGATIVE_BRIDGE_TYPES),
        "counts": counts,
        "requests": requests,
    }


def path_length_m(path_xy):
    points = list(path_xy or [])
    total = 0.0
    previous = None
    for index, point in enumerate(points):
        if not isinstance(point, (list, tuple)) or len(point) < 2:
            raise ValueError(f"path point {index} must contain x and y")
        x, y = float(point[0]), float(point[1])
        if not math.isfinite(x) or not math.isfinite(y):
            raise ValueError(f"path point {index} must be finite")
        if previous is not None:
            total += math.hypot(x - previous[0], y - previous[1])
        previous = (x, y)
    return total


def _reference_probe_class(expected, success, infrastructure_error):
    if infrastructure_error:
        return "infrastructure_error"
    if expected and success:
        return "reference_positive_survives"
    if expected and not success:
        return "reference_positive_rejected"
    if not expected and success:
        return "reference_negative_plannable"
    return "reference_negative_rejected"


def finalize_smoke_results(manifest, outcomes, result_mode="expectation_match"):
    result_mode = str(result_mode)
    if result_mode not in RESULT_MODES:
        raise ValueError(
            f"unsupported result_mode {result_mode!r}; expected one of {sorted(RESULT_MODES)}"
        )

    by_id = {item["request_id"]: item for item in manifest.get("requests", [])}
    results = []
    seen = set()
    for outcome in outcomes:
        request_id = str(outcome.get("request_id"))
        if request_id not in by_id:
            raise ValueError(f"outcome references unknown request: {request_id}")
        if request_id in seen:
            raise ValueError(f"duplicate outcome: {request_id}")
        seen.add(request_id)

        request = by_id[request_id]
        success = bool(outcome.get("planner_success"))
        expected = bool(request["expected_success"])
        infrastructure_error = bool(outcome.get("infrastructure_error", False))

        if result_mode == "expectation_match":
            if infrastructure_error:
                expectation_met = False
                mismatch_type = "infrastructure_error"
            elif success == expected:
                expectation_met = True
                mismatch_type = None
            else:
                expectation_met = False
                mismatch_type = "unexpected_failure" if expected else "unexpected_success"
            probe_class = None
        else:
            expectation_met = None
            mismatch_type = None
            probe_class = _reference_probe_class(
                expected, success, infrastructure_error
            )

        path = [
            [float(point[0]), float(point[1])]
            for point in (outcome.get("path_xy") or [])
        ]
        item = dict(request)
        item.update(
            {
                "planner_success": success,
                "infrastructure_error": infrastructure_error,
                "expectation_met": expectation_met,
                "mismatch_type": mismatch_type,
                "probe_class": probe_class,
                "path_xy": path,
                "path_pose_count": len(path),
                "path_length_m": path_length_m(path),
                "planning_time_ms": outcome.get("planning_time_ms"),
                "wall_time_ms": outcome.get("wall_time_ms"),
                "error_code": outcome.get("error_code"),
                "nav2_status": outcome.get("nav2_status"),
                "failure_reason": outcome.get("failure_reason"),
            }
        )
        results.append(item)

    expected_count = int(
        manifest.get("counts", {}).get("request_count", len(by_id))
    )
    summary = {
        "expected_request_count": expected_count,
        "outcome_count": len(results),
        "planner_success": sum(item["planner_success"] for item in results),
        "planner_failure": sum(not item["planner_success"] for item in results),
        "infrastructure_error": sum(
            item["infrastructure_error"] for item in results
        ),
    }
    summary["complete"] = len(results) == expected_count

    if result_mode == "expectation_match":
        summary.update(
            {
                "expectation_met": sum(
                    bool(item["expectation_met"]) for item in results
                ),
                "expectation_mismatch": sum(
                    not bool(item["expectation_met"]) for item in results
                ),
                "unexpected_success": sum(
                    item["mismatch_type"] == "unexpected_success" for item in results
                ),
                "unexpected_failure": sum(
                    item["mismatch_type"] == "unexpected_failure" for item in results
                ),
            }
        )
        summary["all_expectations_met"] = (
            summary["complete"] and summary["expectation_mismatch"] == 0
        )
    else:
        for classification in (
            "reference_positive_survives",
            "reference_positive_rejected",
            "reference_negative_plannable",
            "reference_negative_rejected",
        ):
            summary[classification] = sum(
                item["probe_class"] == classification for item in results
            )
        summary["probe_valid"] = (
            summary["complete"] and summary["infrastructure_error"] == 0
        )

    return {
        "schema_version": 1,
        "method": "nav2_headland_planner_smoke_results",
        "result_mode": result_mode,
        "radius_m": float(manifest["radius_m"]),
        "manifest_counts": dict(manifest.get("counts") or {}),
        "summary": summary,
        "results": results,
    }


def _read_pgm(path):
    data = Path(path).read_bytes()
    index = 0
    tokens = []
    while len(tokens) < 4:
        while index < len(data) and chr(data[index]).isspace():
            index += 1
        if index < len(data) and data[index] == 35:
            while index < len(data) and data[index] not in (10, 13):
                index += 1
            continue
        end = index
        while index < len(data) and not chr(data[index]).isspace():
            index += 1
        tokens.append(data[end:index].decode("ascii"))
    while index < len(data) and chr(data[index]).isspace():
        index += 1

    magic, width, height, maximum = (
        tokens[0],
        int(tokens[1]),
        int(tokens[2]),
        int(tokens[3]),
    )
    if width <= 0 or height <= 0 or not 0 < maximum <= 255:
        raise ValueError("only 8-bit PGM maps are supported")
    count = width * height
    if magic == "P5":
        pixels = data[index : index + count]
    elif magic == "P2":
        values = data[index:].decode("ascii").split()
        pixels = bytes(round(int(value) * 255 / maximum) for value in values[:count])
    else:
        raise ValueError(f"unsupported PGM magic: {magic}")
    if len(pixels) != count:
        raise ValueError("PGM payload length does not match dimensions")
    return width, height, bytes(pixels)


def _chunk(kind, payload):
    return (
        struct.pack(">I", len(payload))
        + kind
        + payload
        + struct.pack(">I", zlib.crc32(kind + payload) & 0xFFFFFFFF)
    )


def _write_png(path, width, height, rgb):
    stride = width * 3
    raw = b"".join(
        b"\0" + bytes(rgb[row * stride : (row + 1) * stride])
        for row in range(height)
    )
    payload = (
        b"\x89PNG\r\n\x1a\n"
        + _chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0))
        + _chunk(b"IDAT", zlib.compress(raw, 9))
        + _chunk(b"IEND", b"")
    )
    Path(path).write_bytes(payload)


def _pixel(rgb, width, height, x, y, color, radius=1):
    for dy in range(-radius, radius + 1):
        for dx in range(-radius, radius + 1):
            xx, yy = x + dx, y + dy
            if 0 <= xx < width and 0 <= yy < height:
                offset = (yy * width + xx) * 3
                rgb[offset : offset + 3] = bytes(color)


def _line(rgb, width, height, start, goal, color):
    x0, y0 = start
    x1, y1 = goal
    dx = abs(x1 - x0)
    sx = 1 if x0 < x1 else -1
    dy = -abs(y1 - y0)
    sy = 1 if y0 < y1 else -1
    error = dx + dy
    while True:
        _pixel(rgb, width, height, x0, y0, color)
        if (x0, y0) == (x1, y1):
            break
        doubled = 2 * error
        if doubled >= dy:
            error += dy
            x0 += sx
        if doubled <= dx:
            error += dx
            y0 += sy


def _map_spec(map_yaml):
    path = Path(map_yaml).expanduser().resolve()
    config = yaml.safe_load(path.read_text())
    resolution = float(config["resolution"])
    origin = [float(value) for value in config["origin"][:3]]
    if (
        resolution <= 0
        or not math.isfinite(resolution)
        or not all(math.isfinite(value) for value in origin)
        or abs(origin[2]) > 1e-9
    ):
        raise ValueError("map YAML resolution/origin is invalid or rotated")
    image = Path(str(config["image"]))
    image = image if image.is_absolute() else (path.parent / image).resolve()
    return image, resolution, origin


def _overlay(result, map_yaml, output):
    image, resolution, origin = _map_spec(map_yaml)
    width, height, gray = _read_pgm(image)
    rgb = bytearray(width * height * 3)
    for index, value in enumerate(gray):
        rgb[index * 3 : index * 3 + 3] = bytes((value, value, value))

    def convert(point):
        return (
            int(round((point[0] - origin[0]) / resolution)),
            height - 1 - int(round((point[1] - origin[1]) / resolution)),
        )

    for item in result.get("results", []):
        path = item.get("path_xy") or []
        if not item.get("planner_success") or len(path) < 2:
            continue
        points = [convert(point) for point in path]
        color = (0, 170, 0) if item.get("expected_success") else (220, 0, 0)
        for start, goal in zip(points, points[1:]):
            _line(rgb, width, height, start, goal, color)
        _pixel(rgb, width, height, *points[0], (0, 80, 220), radius=2)
        _pixel(rgb, width, height, *points[-1], (220, 120, 0), radius=2)
    _write_png(output, width, height, rgb)


def write_smoke_bundle(result, map_yaml_path, output_dir):
    output = Path(output_dir).expanduser().resolve()
    if output.exists() and any(output.iterdir()):
        raise FileExistsError(f"output directory is not empty: {output}")
    output.mkdir(parents=True, exist_ok=True)

    json_path = output / "planner_smoke_results.json"
    json_path.write_text(json.dumps(result, indent=2) + "\n")

    fields = [
        "request_id",
        "pair_id",
        "side",
        "direction",
        "expected_success",
        "expectation_class",
        "negative_reason",
        "planner_success",
        "infrastructure_error",
        "expectation_met",
        "mismatch_type",
        "probe_class",
        "path_pose_count",
        "path_length_m",
        "planning_time_ms",
        "wall_time_ms",
        "error_code",
        "nav2_status",
        "failure_reason",
    ]
    csv_path = output / "summary.csv"
    with csv_path.open("w", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=fields)
        writer.writeheader()
        for item in result.get("results", []):
            writer.writerow({key: item.get(key) for key in fields})

    features = []
    for item in result.get("results", []):
        path = item.get("path_xy") or []
        if item.get("planner_success") and len(path) >= 2:
            properties = {
                key: item.get(key)
                for key in (
                    "request_id",
                    "pair_id",
                    "side",
                    "direction",
                    "expected_success",
                    "expectation_met",
                    "mismatch_type",
                    "probe_class",
                    "negative_reason",
                    "path_length_m",
                    "planning_time_ms",
                )
            }
            features.append(
                {
                    "type": "Feature",
                    "geometry": {"type": "LineString", "coordinates": path},
                    "properties": properties,
                }
            )
    geojson_path = output / "planner_paths.geojson"
    geojson_path.write_text(
        json.dumps({"type": "FeatureCollection", "features": features}, indent=2)
        + "\n"
    )

    overlay_path = output / "planner_overlay.png"
    _overlay(result, map_yaml_path, overlay_path)
    return {
        "json": json_path,
        "csv": csv_path,
        "geojson": geojson_path,
        "overlay": overlay_path,
    }
