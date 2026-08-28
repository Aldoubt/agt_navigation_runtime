"""Pure artifact and result helpers for planner-only headland smoke tests."""

from __future__ import annotations

import csv
import json
import math
import struct
import zlib
from pathlib import Path

import yaml

NEGATIVE_BRIDGE_TYPES = frozenset({"mixed_bridge", "clearance_only_bridge"})


def _radius(payload, name):
    try:
        value = float(payload["radius_m"])
    except (KeyError, TypeError, ValueError) as exc:
        raise ValueError(f"{name} radius_m is required") from exc
    if not math.isfinite(value) or value <= 0.0:
        raise ValueError(f"{name} radius_m must be positive and finite")
    return value


def _pose(value, label):
    if not isinstance(value, dict):
        raise ValueError(f"{label} pose must be an object")
    result = {}
    for key in ("x", "y", "yaw"):
        try:
            number = float(value[key])
        except (KeyError, TypeError, ValueError) as exc:
            raise ValueError(f"{label} pose requires finite {key}") from exc
        if not math.isfinite(number):
            raise ValueError(f"{label} pose requires finite {key}")
        result[key] = number
    return result


def _direction_request(test, direction, expected_success, negative_reason, radius_m):
    case_id = str(test.get("id") or f"{test['pair_id']}-{test['side']}")
    segment = test.get(direction)
    if not isinstance(segment, dict):
        raise ValueError(f"{case_id} is missing {direction} start/goal")
    return {
        "request_id": f"{case_id}-{direction}",
        "case_id": case_id,
        "pair_id": str(test["pair_id"]),
        "side": str(test["side"]),
        "direction": direction,
        "radius_m": float(radius_m),
        "expected_success": bool(expected_success),
        "expectation_class": "positive" if expected_success else "negative_control",
        "negative_reason": negative_reason,
        "baseline_connected": bool(test.get("baseline_connected", False)),
        "conservative_connected": bool(test.get("conservative_connected", False)),
        "start": _pose(segment.get("start"), f"{case_id} {direction} start"),
        "goal": _pose(segment.get("goal"), f"{case_id} {direction} goal"),
    }


def build_smoke_manifest(planner_pairs, gap_diagnostics):
    """Expand frozen pair-side artifacts into directional planner expectations."""
    if not isinstance(planner_pairs, dict) or not isinstance(gap_diagnostics, dict):
        raise ValueError("planner_pairs and gap_diagnostics must be objects")
    pair_radius = _radius(planner_pairs, "planner_pairs")
    diag_radius = _radius(gap_diagnostics, "gap_diagnostics")
    if not math.isclose(pair_radius, diag_radius, rel_tol=0.0, abs_tol=1e-9):
        raise ValueError(
            f"planner_pairs radius {pair_radius} does not match diagnostics radius {diag_radius}"
        )

    tests = planner_pairs.get("tests")
    if not isinstance(tests, list):
        raise ValueError("planner_pairs.tests must be a list")
    by_case = {}
    for test in tests:
        if not isinstance(test, dict):
            raise ValueError("planner_pairs.tests entries must be objects")
        case_id = str(test.get("id") or f"{test.get('pair_id')}-{test.get('side')}")
        if case_id in by_case:
            raise ValueError(f"duplicate planner pair test id: {case_id}")
        by_case[case_id] = test

    positive_tests = [
        test
        for test in tests
        if bool(test.get("enabled")) and bool(test.get("conservative_connected"))
    ]

    negative_tests = []
    negative_reason_by_case = {}
    records = gap_diagnostics.get("records")
    if not isinstance(records, list):
        raise ValueError("gap_diagnostics.records must be a list")
    for record in records:
        if not isinstance(record, dict):
            continue
        bridge_type = str(record.get("bridge_type", ""))
        if (
            str(record.get("evaluation_status")) != "evaluated"
            or bool(record.get("strict_connected"))
            or bridge_type not in NEGATIVE_BRIDGE_TYPES
        ):
            continue
        case_id = f"{record.get('pair_id')}-{record.get('side')}"
        test = by_case.get(case_id)
        if test is None:
            raise ValueError(f"negative diagnostic case {case_id} has no planner pair poses")
        if case_id in negative_reason_by_case:
            raise ValueError(f"duplicate negative diagnostic case: {case_id}")
        negative_tests.append(test)
        negative_reason_by_case[case_id] = bridge_type

    requests = []
    seen_request_ids = set()
    for test in positive_tests:
        for direction in ("forward", "reverse"):
            request = _direction_request(test, direction, True, None, pair_radius)
            if request["request_id"] in seen_request_ids:
                raise ValueError(f"duplicate request id: {request['request_id']}")
            seen_request_ids.add(request["request_id"])
            requests.append(request)
    for test in negative_tests:
        case_id = str(test.get("id") or f"{test['pair_id']}-{test['side']}")
        reason = negative_reason_by_case[case_id]
        for direction in ("forward", "reverse"):
            request = _direction_request(test, direction, False, reason, pair_radius)
            if request["request_id"] in seen_request_ids:
                raise ValueError(f"duplicate request id: {request['request_id']}")
            seen_request_ids.add(request["request_id"])
            requests.append(request)

    counts = {
        "positive_pair_sides": len(positive_tests),
        "negative_pair_sides": len(negative_tests),
        "positive_requests": 2 * len(positive_tests),
        "negative_requests": 2 * len(negative_tests),
        "request_count": len(requests),
    }
    return {
        "schema_version": 1,
        "method": "nav2_headland_planner_smoke_manifest",
        "radius_m": pair_radius,
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
    return float(total)


def finalize_smoke_results(manifest, outcomes):
    requests = list(manifest.get("requests") or [])
    by_id = {item["request_id"]: item for item in requests}
    seen = set()
    results = []
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
        met = success == expected
        mismatch_type = None
        if not met:
            mismatch_type = "unexpected_failure" if expected else "unexpected_success"
        raw_path = list(outcome.get("path_xy") or [])
        path = [[float(point[0]), float(point[1])] for point in raw_path]
        record = dict(request)
        record.update(
            {
                "planner_success": success,
                "expectation_met": met,
                "mismatch_type": mismatch_type,
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
        results.append(record)

    summary = {
        "expected_request_count": int(manifest.get("counts", {}).get("request_count", len(requests))),
        "outcome_count": len(results),
        "planner_success": sum(item["planner_success"] for item in results),
        "planner_failure": sum(not item["planner_success"] for item in results),
        "expectation_met": sum(item["expectation_met"] for item in results),
        "expectation_mismatch": sum(not item["expectation_met"] for item in results),
        "unexpected_success": sum(item["mismatch_type"] == "unexpected_success" for item in results),
        "unexpected_failure": sum(item["mismatch_type"] == "unexpected_failure" for item in results),
    }
    summary["complete"] = summary["outcome_count"] == summary["expected_request_count"]
    summary["all_expectations_met"] = bool(
        summary["complete"] and summary["expectation_mismatch"] == 0
    )
    return {
        "schema_version": 1,
        "method": "nav2_headland_planner_smoke_results",
        "radius_m": float(manifest["radius_m"]),
        "manifest_counts": dict(manifest.get("counts") or {}),
        "summary": summary,
        "results": results,
    }


def _tokenize_pgm(data):
    tokens = []
    index = 0
    length = len(data)
    while index < length and len(tokens) < 4:
        while index < length and chr(data[index]).isspace():
            index += 1
        if index < length and data[index] == ord("#"):
            while index < length and data[index] not in (10, 13):
                index += 1
            continue
        start = index
        while index < length and not chr(data[index]).isspace() and data[index] != ord("#"):
            index += 1
        if start < index:
            tokens.append(data[start:index].decode("ascii"))
    while index < length and chr(data[index]).isspace():
        index += 1
    return tokens, index


def _read_pgm(path):
    data = Path(path).read_bytes()
    tokens, payload_start = _tokenize_pgm(data)
    if len(tokens) < 4:
        raise ValueError(f"invalid PGM header: {path}")
    magic, width_text, height_text, maxval_text = tokens[:4]
    width, height, maxval = int(width_text), int(height_text), int(maxval_text)
    if width <= 0 or height <= 0 or maxval <= 0 or maxval > 255:
        raise ValueError("only 8-bit PGM maps are supported")
    count = width * height
    if magic == "P5":
        pixels = data[payload_start : payload_start + count]
        if len(pixels) != count:
            raise ValueError("PGM payload length does not match dimensions")
        return width, height, bytes(pixels)
    if magic == "P2":
        text = data[payload_start:].decode("ascii")
        values = []
        for line in text.splitlines():
            line = line.split("#", 1)[0]
            values.extend(line.split())
        if len(values) < count:
            raise ValueError("PGM payload length does not match dimensions")
        pixels = bytes(int(round(int(value) * 255.0 / maxval)) for value in values[:count])
        return width, height, pixels
    raise ValueError(f"unsupported PGM magic: {magic}")


def _png_chunk(kind, payload):
    return (
        struct.pack(">I", len(payload))
        + kind
        + payload
        + struct.pack(">I", zlib.crc32(kind + payload) & 0xFFFFFFFF)
    )


def _write_rgb_png(path, width, height, rgb):
    if len(rgb) != width * height * 3:
        raise ValueError("RGB payload size does not match image dimensions")
    rows = []
    stride = width * 3
    for row in range(height):
        start = row * stride
        rows.append(b"\x00" + bytes(rgb[start : start + stride]))
    signature = b"\x89PNG\r\n\x1a\n"
    ihdr = struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0)
    payload = signature + _png_chunk(b"IHDR", ihdr)
    payload += _png_chunk(b"IDAT", zlib.compress(b"".join(rows), 9))
    payload += _png_chunk(b"IEND", b"")
    Path(path).write_bytes(payload)


def _draw_pixel(rgb, width, height, x, y, color, radius=1):
    for dy in range(-radius, radius + 1):
        for dx in range(-radius, radius + 1):
            xx, yy = x + dx, y + dy
            if xx < 0 or yy < 0 or xx >= width or yy >= height:
                continue
            index = (yy * width + xx) * 3
            rgb[index : index + 3] = bytes(color)


def _draw_line(rgb, width, height, start, goal, color):
    x0, y0 = start
    x1, y1 = goal
    dx = abs(x1 - x0)
    sx = 1 if x0 < x1 else -1
    dy = -abs(y1 - y0)
    sy = 1 if y0 < y1 else -1
    err = dx + dy
    while True:
        _draw_pixel(rgb, width, height, x0, y0, color, radius=1)
        if x0 == x1 and y0 == y1:
            break
        twice = 2 * err
        if twice >= dy:
            err += dy
            x0 += sx
        if twice <= dx:
            err += dx
            y0 += sy


def _load_map_spec(map_yaml_path):
    path = Path(map_yaml_path).expanduser().resolve()
    payload = yaml.safe_load(path.read_text(encoding="utf-8"))
    if not isinstance(payload, dict):
        raise ValueError("map YAML must be an object")
    resolution = float(payload["resolution"])
    origin = list(payload["origin"])
    if not math.isfinite(resolution) or resolution <= 0.0 or len(origin) < 3:
        raise ValueError("map YAML resolution/origin is invalid")
    origin = [float(value) for value in origin[:3]]
    if not all(math.isfinite(value) for value in origin):
        raise ValueError("map YAML origin must be finite")
    if abs(origin[2]) > 1e-9:
        raise ValueError("planner smoke overlay currently requires zero map-origin yaw")
    image = Path(str(payload["image"]))
    if not image.is_absolute():
        image = (path.parent / image).resolve()
    return path, image, resolution, origin


def _world_to_image(x, y, width, height, resolution, origin):
    grid_x = int(round((float(x) - origin[0]) / resolution))
    grid_y = int(round((float(y) - origin[1]) / resolution))
    return grid_x, height - 1 - grid_y


def _write_overlay(result, map_yaml_path, output_path):
    _, image_path, resolution, origin = _load_map_spec(map_yaml_path)
    width, height, pixels = _read_pgm(image_path)
    rgb = bytearray(width * height * 3)
    for index, value in enumerate(pixels):
        rgb[index * 3 : index * 3 + 3] = bytes((value, value, value))
    for item in result.get("results", []):
        if not item.get("planner_success"):
            continue
        path = item.get("path_xy") or []
        if len(path) < 2:
            continue
        color = (0, 170, 0) if item.get("expected_success") else (220, 0, 0)
        image_points = [
            _world_to_image(x, y, width, height, resolution, origin) for x, y in path
        ]
        for start, goal in zip(image_points, image_points[1:]):
            _draw_line(rgb, width, height, start, goal, color)
        _draw_pixel(rgb, width, height, *image_points[0], (0, 80, 220), radius=2)
        _draw_pixel(rgb, width, height, *image_points[-1], (220, 120, 0), radius=2)
    _write_rgb_png(output_path, width, height, rgb)


def _geojson(result):
    features = []
    for item in result.get("results", []):
        path = item.get("path_xy") or []
        if not item.get("planner_success") or len(path) < 2:
            continue
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
                "negative_reason",
                "path_length_m",
                "planning_time_ms",
            )
        }
        features.append(
            {
                "type": "Feature",
                "geometry": {
                    "type": "LineString",
                    "coordinates": [[float(x), float(y)] for x, y in path],
                },
                "properties": properties,
            }
        )
    return {"type": "FeatureCollection", "features": features}


def write_smoke_bundle(result, map_yaml_path, output_dir):
    output = Path(output_dir).expanduser().resolve()
    if output.exists() and any(output.iterdir()):
        raise FileExistsError(f"output directory is not empty: {output}")
    output.mkdir(parents=True, exist_ok=True)

    json_path = output / "planner_smoke_results.json"
    json_path.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")

    fields = [
        "request_id",
        "pair_id",
        "side",
        "direction",
        "expected_success",
        "expectation_class",
        "negative_reason",
        "planner_success",
        "expectation_met",
        "mismatch_type",
        "path_pose_count",
        "path_length_m",
        "planning_time_ms",
        "wall_time_ms",
        "error_code",
        "nav2_status",
        "failure_reason",
    ]
    csv_path = output / "summary.csv"
    with csv_path.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=fields)
        writer.writeheader()
        for item in result.get("results", []):
            writer.writerow({field: item.get(field) for field in fields})

    geojson_path = output / "planner_paths.geojson"
    geojson_path.write_text(json.dumps(_geojson(result), indent=2) + "\n", encoding="utf-8")

    overlay_path = output / "planner_overlay.png"
    _write_overlay(result, map_yaml_path, overlay_path)

    return {
        "json": json_path,
        "csv": csv_path,
        "geojson": geojson_path,
        "overlay": overlay_path,
    }
