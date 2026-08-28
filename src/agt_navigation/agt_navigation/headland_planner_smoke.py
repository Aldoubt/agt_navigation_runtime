from __future__ import annotations

import csv, json, math, struct, zlib
from pathlib import Path
import yaml

NEGATIVE_BRIDGE_TYPES = {"mixed_bridge", "clearance_only_bridge"}


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
        "request_id": f"{case}-{direction}", "case_id": case,
        "pair_id": str(test["pair_id"]), "side": str(test["side"]),
        "direction": direction, "radius_m": radius,
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
        raise ValueError(f"planner_pairs radius {pr} does not match diagnostics radius {dr}")
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
    positive = [t for t in tests if bool(t.get("enabled")) and bool(t.get("conservative_connected"))]
    negative = []
    reasons = {}
    for record in records:
        bridge = str(record.get("bridge_type", ""))
        if str(record.get("evaluation_status")) != "evaluated" or bool(record.get("strict_connected")) or bridge not in NEGATIVE_BRIDGE_TYPES:
            continue
        case = f"{record.get('pair_id')}-{record.get('side')}"
        if case not in by_case:
            raise ValueError(f"negative diagnostic case {case} has no planner pair poses")
        if case in reasons:
            raise ValueError(f"duplicate negative diagnostic case: {case}")
        negative.append(by_case[case]); reasons[case] = bridge
    requests, seen = [], set()
    for test, expected in [(t, True) for t in positive] + [(t, False) for t in negative]:
        case = str(test.get("id") or f"{test['pair_id']}-{test['side']}")
        for direction in ("forward", "reverse"):
            item = _request(test, direction, expected, None if expected else reasons[case], pr)
            if item["request_id"] in seen:
                raise ValueError(f"duplicate request id: {item['request_id']}")
            seen.add(item["request_id"]); requests.append(item)
    counts = {
        "positive_pair_sides": len(positive), "negative_pair_sides": len(negative),
        "positive_requests": 2 * len(positive), "negative_requests": 2 * len(negative),
        "request_count": len(requests),
    }
    return {
        "schema_version": 1, "method": "nav2_headland_planner_smoke_manifest",
        "radius_m": pr, "planner_pair_method": planner_pairs.get("method"),
        "gap_diagnostic_method": gap_diagnostics.get("method"),
        "negative_bridge_types": sorted(NEGATIVE_BRIDGE_TYPES), "counts": counts,
        "requests": requests,
    }


def path_length_m(path_xy):
    points = list(path_xy or []); total = 0.0; prev = None
    for i, point in enumerate(points):
        if not isinstance(point, (list, tuple)) or len(point) < 2:
            raise ValueError(f"path point {i} must contain x and y")
        x, y = float(point[0]), float(point[1])
        if not math.isfinite(x) or not math.isfinite(y):
            raise ValueError(f"path point {i} must be finite")
        if prev is not None: total += math.hypot(x - prev[0], y - prev[1])
        prev = (x, y)
    return total


def finalize_smoke_results(manifest, outcomes):
    by_id = {r["request_id"]: r for r in manifest.get("requests", [])}
    results, seen = [], set()
    for outcome in outcomes:
        rid = str(outcome.get("request_id"))
        if rid not in by_id: raise ValueError(f"outcome references unknown request: {rid}")
        if rid in seen: raise ValueError(f"duplicate outcome: {rid}")
        seen.add(rid); request = by_id[rid]
        success = bool(outcome.get("planner_success")); expected = bool(request["expected_success"])
        infra = bool(outcome.get("infrastructure_error", False))
        if infra: met, mismatch = False, "infrastructure_error"
        elif success == expected: met, mismatch = True, None
        else: met, mismatch = False, "unexpected_failure" if expected else "unexpected_success"
        path = [[float(p[0]), float(p[1])] for p in (outcome.get("path_xy") or [])]
        item = dict(request)
        item.update({
            "planner_success": success, "infrastructure_error": infra,
            "expectation_met": met, "mismatch_type": mismatch,
            "path_xy": path, "path_pose_count": len(path), "path_length_m": path_length_m(path),
            "planning_time_ms": outcome.get("planning_time_ms"), "wall_time_ms": outcome.get("wall_time_ms"),
            "error_code": outcome.get("error_code"), "nav2_status": outcome.get("nav2_status"),
            "failure_reason": outcome.get("failure_reason"),
        }); results.append(item)
    expected_count = int(manifest.get("counts", {}).get("request_count", len(by_id)))
    summary = {
        "expected_request_count": expected_count, "outcome_count": len(results),
        "planner_success": sum(r["planner_success"] for r in results),
        "planner_failure": sum(not r["planner_success"] for r in results),
        "expectation_met": sum(r["expectation_met"] for r in results),
        "expectation_mismatch": sum(not r["expectation_met"] for r in results),
        "unexpected_success": sum(r["mismatch_type"] == "unexpected_success" for r in results),
        "unexpected_failure": sum(r["mismatch_type"] == "unexpected_failure" for r in results),
        "infrastructure_error": sum(r["mismatch_type"] == "infrastructure_error" for r in results),
    }
    summary["complete"] = len(results) == expected_count
    summary["all_expectations_met"] = summary["complete"] and summary["expectation_mismatch"] == 0
    return {"schema_version": 1, "method": "nav2_headland_planner_smoke_results", "radius_m": float(manifest["radius_m"]), "manifest_counts": dict(manifest.get("counts") or {}), "summary": summary, "results": results}


def _read_pgm(path):
    data = Path(path).read_bytes(); i = 0; tokens = []
    while len(tokens) < 4:
        while i < len(data) and chr(data[i]).isspace(): i += 1
        if i < len(data) and data[i] == 35:
            while i < len(data) and data[i] not in (10, 13): i += 1
            continue
        j = i
        while i < len(data) and not chr(data[i]).isspace(): i += 1
        tokens.append(data[j:i].decode("ascii"))
    while i < len(data) and chr(data[i]).isspace(): i += 1
    magic, w, h, maxv = tokens[0], int(tokens[1]), int(tokens[2]), int(tokens[3])
    if w <= 0 or h <= 0 or not 0 < maxv <= 255: raise ValueError("only 8-bit PGM maps are supported")
    count = w * h
    if magic == "P5": pixels = data[i:i + count]
    elif magic == "P2":
        values = data[i:].decode("ascii").split(); pixels = bytes(round(int(v) * 255 / maxv) for v in values[:count])
    else: raise ValueError(f"unsupported PGM magic: {magic}")
    if len(pixels) != count: raise ValueError("PGM payload length does not match dimensions")
    return w, h, bytes(pixels)


def _chunk(kind, payload):
    return struct.pack(">I", len(payload)) + kind + payload + struct.pack(">I", zlib.crc32(kind + payload) & 0xFFFFFFFF)


def _write_png(path, w, h, rgb):
    stride = w * 3; raw = b"".join(b"\0" + bytes(rgb[y * stride:(y + 1) * stride]) for y in range(h))
    payload = b"\x89PNG\r\n\x1a\n" + _chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 2, 0, 0, 0)) + _chunk(b"IDAT", zlib.compress(raw, 9)) + _chunk(b"IEND", b"")
    Path(path).write_bytes(payload)


def _pixel(rgb, w, h, x, y, color, radius=1):
    for dy in range(-radius, radius + 1):
        for dx in range(-radius, radius + 1):
            xx, yy = x + dx, y + dy
            if 0 <= xx < w and 0 <= yy < h:
                k = (yy * w + xx) * 3; rgb[k:k + 3] = bytes(color)


def _line(rgb, w, h, a, b, color):
    x0, y0 = a; x1, y1 = b; dx = abs(x1 - x0); sx = 1 if x0 < x1 else -1; dy = -abs(y1 - y0); sy = 1 if y0 < y1 else -1; err = dx + dy
    while True:
        _pixel(rgb, w, h, x0, y0, color)
        if (x0, y0) == (x1, y1): break
        e = 2 * err
        if e >= dy: err += dy; x0 += sx
        if e <= dx: err += dx; y0 += sy


def _map_spec(map_yaml):
    path = Path(map_yaml).expanduser().resolve(); cfg = yaml.safe_load(path.read_text())
    res = float(cfg["resolution"]); origin = [float(v) for v in cfg["origin"][:3]]
    if res <= 0 or not math.isfinite(res) or not all(math.isfinite(v) for v in origin) or abs(origin[2]) > 1e-9: raise ValueError("map YAML resolution/origin is invalid or rotated")
    image = Path(str(cfg["image"])); image = image if image.is_absolute() else (path.parent / image).resolve()
    return image, res, origin


def _overlay(result, map_yaml, out):
    image, res, origin = _map_spec(map_yaml); w, h, gray = _read_pgm(image); rgb = bytearray(w * h * 3)
    for i, v in enumerate(gray): rgb[i * 3:i * 3 + 3] = bytes((v, v, v))
    def convert(p): return int(round((p[0] - origin[0]) / res)), h - 1 - int(round((p[1] - origin[1]) / res))
    for item in result.get("results", []):
        path = item.get("path_xy") or []
        if not item.get("planner_success") or len(path) < 2: continue
        pts = [convert(p) for p in path]; color = (0, 170, 0) if item.get("expected_success") else (220, 0, 0)
        for a, b in zip(pts, pts[1:]): _line(rgb, w, h, a, b, color)
        _pixel(rgb, w, h, *pts[0], (0, 80, 220), radius=2); _pixel(rgb, w, h, *pts[-1], (220, 120, 0), radius=2)
    _write_png(out, w, h, rgb)


def write_smoke_bundle(result, map_yaml_path, output_dir):
    out = Path(output_dir).expanduser().resolve()
    if out.exists() and any(out.iterdir()): raise FileExistsError(f"output directory is not empty: {out}")
    out.mkdir(parents=True, exist_ok=True)
    json_path = out / "planner_smoke_results.json"; json_path.write_text(json.dumps(result, indent=2) + "\n")
    fields = ["request_id", "pair_id", "side", "direction", "expected_success", "expectation_class", "negative_reason", "planner_success", "infrastructure_error", "expectation_met", "mismatch_type", "path_pose_count", "path_length_m", "planning_time_ms", "wall_time_ms", "error_code", "nav2_status", "failure_reason"]
    csv_path = out / "summary.csv"
    with csv_path.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fields); writer.writeheader()
        for item in result.get("results", []): writer.writerow({k: item.get(k) for k in fields})
    features = []
    for item in result.get("results", []):
        path = item.get("path_xy") or []
        if item.get("planner_success") and len(path) >= 2:
            props = {k: item.get(k) for k in ("request_id", "pair_id", "side", "direction", "expected_success", "expectation_met", "mismatch_type", "negative_reason", "path_length_m", "planning_time_ms")}
            features.append({"type": "Feature", "geometry": {"type": "LineString", "coordinates": path}, "properties": props})
    geo = out / "planner_paths.geojson"; geo.write_text(json.dumps({"type": "FeatureCollection", "features": features}, indent=2) + "\n")
    overlay = out / "planner_overlay.png"; _overlay(result, map_yaml_path, overlay)
    return {"json": json_path, "csv": csv_path, "geojson": geo, "overlay": overlay}
