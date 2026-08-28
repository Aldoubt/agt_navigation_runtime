import json
from pathlib import Path

import pytest
import yaml

from agt_navigation.headland_planner_smoke import (
    build_smoke_manifest,
    finalize_smoke_results,
    path_length_m,
    write_smoke_bundle,
)


def _pose(x, y, yaw=0.0):
    return {"x": float(x), "y": float(y), "yaw": float(yaw)}


def _planner_test(pair_id, side, *, enabled):
    index = int(pair_id.split("A")[-1]) if pair_id.startswith("A") and "-" not in pair_id else 0
    base_x = float(index)
    return {
        "id": f"{pair_id}-{side}",
        "pair_id": pair_id,
        "side": side,
        "radius_m": 0.2,
        "enabled": bool(enabled),
        "baseline_connected": bool(enabled),
        "conservative_connected": bool(enabled),
        "gained_by_trusted_overlay": False,
        "forward": {
            "start": _pose(base_x, 1.0, 0.0),
            "goal": _pose(base_x + 1.0, 1.0, 3.14159),
        },
        "reverse": {
            "start": _pose(base_x + 1.0, 1.0, 0.0),
            "goal": _pose(base_x, 1.0, 3.14159),
        },
    }


def _frozen_like_payloads():
    positives = [
        _planner_test(f"P{i:02d}-P{i + 1:02d}", "entry" if i % 2 else "exit", enabled=True)
        for i in range(1, 12)
    ]
    negatives = [
        _planner_test("A02-A03", "exit", enabled=False),
        _planner_test("A11-A12", "exit", enabled=False),
        _planner_test("A13-A14", "exit", enabled=False),
    ]
    ignored = _planner_test("A09-A10", "entry", enabled=False)
    planner_pairs = {
        "schema_version": 1,
        "method": "nav2_headland_adjacent_pair_smoke_tests",
        "radius_m": 0.2,
        "bidirectional": True,
        "tests": positives + negatives + [ignored],
    }
    diagnostics = {
        "schema_version": 2,
        "method": "scoped_headland_gap_diagnostics",
        "radius_m": 0.2,
        "records": [
            {
                "pair_id": "A02-A03",
                "side": "exit",
                "evaluation_status": "evaluated",
                "strict_connected": False,
                "bridge_type": "mixed_bridge",
                "failure_class": "no_overlay_in_domain",
            },
            {
                "pair_id": "A11-A12",
                "side": "exit",
                "evaluation_status": "evaluated",
                "strict_connected": False,
                "bridge_type": "clearance_only_bridge",
                "failure_class": "no_overlay_in_domain",
            },
            {
                "pair_id": "A13-A14",
                "side": "exit",
                "evaluation_status": "evaluated",
                "strict_connected": False,
                "bridge_type": "mixed_bridge",
                "failure_class": "no_overlay_in_domain",
            },
            {
                "pair_id": "A09-A10",
                "side": "entry",
                "evaluation_status": "evaluated",
                "strict_connected": False,
                "bridge_type": "not_available",
                "failure_class": "hard_or_finite_headland_blocked",
            },
        ],
    }
    return planner_pairs, diagnostics


def test_frozen_like_artifacts_expand_to_22_positive_and_6_negative_requests():
    planner_pairs, diagnostics = _frozen_like_payloads()
    manifest = build_smoke_manifest(planner_pairs, diagnostics)

    assert manifest["radius_m"] == 0.2
    assert manifest["counts"] == {
        "positive_pair_sides": 11,
        "negative_pair_sides": 3,
        "positive_requests": 22,
        "negative_requests": 6,
        "request_count": 28,
    }
    requests = manifest["requests"]
    assert len(requests) == 28
    assert sum(item["expected_success"] for item in requests) == 22
    assert sum(not item["expected_success"] for item in requests) == 6
    assert {item["direction"] for item in requests} == {"forward", "reverse"}

    negative_cases = {
        (item["pair_id"], item["side"], item["negative_reason"])
        for item in requests
        if not item["expected_success"]
    }
    assert negative_cases == {
        ("A02-A03", "exit", "mixed_bridge"),
        ("A11-A12", "exit", "clearance_only_bridge"),
        ("A13-A14", "exit", "mixed_bridge"),
    }
    assert all(item["pair_id"] != "A09-A10" for item in requests)


def test_request_poses_preserve_exported_forward_and_reverse_direction():
    planner_pairs, diagnostics = _frozen_like_payloads()
    manifest = build_smoke_manifest(planner_pairs, diagnostics)
    source = planner_pairs["tests"][0]
    case_id = source["id"]
    by_id = {item["request_id"]: item for item in manifest["requests"]}

    assert by_id[f"{case_id}-forward"]["start"] == source["forward"]["start"]
    assert by_id[f"{case_id}-forward"]["goal"] == source["forward"]["goal"]
    assert by_id[f"{case_id}-reverse"]["start"] == source["reverse"]["start"]
    assert by_id[f"{case_id}-reverse"]["goal"] == source["reverse"]["goal"]


def test_manifest_rejects_radius_mismatch():
    planner_pairs, diagnostics = _frozen_like_payloads()
    diagnostics["radius_m"] = 0.25
    with pytest.raises(ValueError, match="radius"):
        build_smoke_manifest(planner_pairs, diagnostics)


def test_manifest_rejects_non_finite_pose():
    planner_pairs, diagnostics = _frozen_like_payloads()
    planner_pairs["tests"][0]["forward"]["goal"]["x"] = float("nan")
    with pytest.raises(ValueError, match="finite"):
        build_smoke_manifest(planner_pairs, diagnostics)


def test_path_length_and_expectation_summary():
    planner_pairs, diagnostics = _frozen_like_payloads()
    manifest = build_smoke_manifest(planner_pairs, diagnostics)
    positive = next(item for item in manifest["requests"] if item["expected_success"])
    negative = next(item for item in manifest["requests"] if not item["expected_success"])

    assert path_length_m([[0.0, 0.0], [3.0, 4.0], [6.0, 4.0]]) == pytest.approx(8.0)

    outcomes = [
        {
            "request_id": positive["request_id"],
            "planner_success": True,
            "path_xy": [[0.0, 0.0], [3.0, 4.0]],
            "planning_time_ms": 12.5,
            "wall_time_ms": 14.0,
            "error_code": 0,
            "failure_reason": None,
        },
        {
            "request_id": negative["request_id"],
            "planner_success": False,
            "path_xy": [],
            "planning_time_ms": None,
            "wall_time_ms": 8.0,
            "error_code": 208,
            "failure_reason": "no valid path",
        },
    ]
    result = finalize_smoke_results(manifest, outcomes)
    assert result["summary"]["outcome_count"] == 2
    assert result["summary"]["planner_success"] == 1
    assert result["summary"]["planner_failure"] == 1
    assert result["summary"]["expectation_met"] == 2
    assert result["summary"]["expectation_mismatch"] == 0
    assert result["results"][0]["path_length_m"] == pytest.approx(5.0)
    assert result["results"][0]["path_pose_count"] == 2


def test_unexpected_positive_failure_and_negative_success_are_mismatches():
    planner_pairs, diagnostics = _frozen_like_payloads()
    manifest = build_smoke_manifest(planner_pairs, diagnostics)
    positive = next(item for item in manifest["requests"] if item["expected_success"])
    negative = next(item for item in manifest["requests"] if not item["expected_success"])
    outcomes = [
        {
            "request_id": positive["request_id"],
            "planner_success": False,
            "path_xy": [],
            "failure_reason": "aborted",
        },
        {
            "request_id": negative["request_id"],
            "planner_success": True,
            "path_xy": [[1.0, 1.0], [2.0, 1.0]],
            "failure_reason": None,
        },
    ]
    result = finalize_smoke_results(manifest, outcomes)
    assert result["summary"]["expectation_mismatch"] == 2
    assert result["summary"]["unexpected_failure"] == 1
    assert result["summary"]["unexpected_success"] == 1
    mismatch_types = {item["mismatch_type"] for item in result["results"]}
    assert mismatch_types == {"unexpected_failure", "unexpected_success"}


def _write_p5(path: Path, width=8, height=6, value=254):
    payload = bytes([value] * width * height)
    path.write_bytes(f"P5\n{width} {height}\n255\n".encode("ascii") + payload)


def test_bundle_writes_json_csv_geojson_and_png_without_extra_plotting_dependencies(tmp_path):
    planner_pairs, diagnostics = _frozen_like_payloads()
    manifest = build_smoke_manifest(planner_pairs, diagnostics)
    request = next(item for item in manifest["requests"] if item["expected_success"])
    outcome = {
        "request_id": request["request_id"],
        "planner_success": True,
        "path_xy": [[1.0, 1.0], [2.0, 1.0], [3.0, 2.0]],
        "planning_time_ms": 5.0,
        "wall_time_ms": 7.0,
        "error_code": 0,
        "failure_reason": None,
    }
    result = finalize_smoke_results(manifest, [outcome])

    pgm = tmp_path / "map.pgm"
    _write_p5(pgm)
    map_yaml = tmp_path / "map.yaml"
    map_yaml.write_text(
        yaml.safe_dump(
            {
                "image": pgm.name,
                "mode": "trinary",
                "resolution": 1.0,
                "origin": [0.0, 0.0, 0.0],
                "negate": 0,
                "occupied_thresh": 0.65,
                "free_thresh": 0.196,
            },
            sort_keys=False,
        ),
        encoding="utf-8",
    )
    output = tmp_path / "out"
    paths = write_smoke_bundle(result, map_yaml, output)

    assert set(paths) == {"json", "csv", "geojson", "overlay"}
    assert {path.name for path in output.iterdir()} == {
        "planner_smoke_results.json",
        "summary.csv",
        "planner_paths.geojson",
        "planner_overlay.png",
    }
    payload = json.loads((output / "planner_smoke_results.json").read_text(encoding="utf-8"))
    assert payload["summary"]["expectation_met"] == 1
    geojson = json.loads((output / "planner_paths.geojson").read_text(encoding="utf-8"))
    assert geojson["type"] == "FeatureCollection"
    assert len(geojson["features"]) == 1
    assert geojson["features"][0]["geometry"]["type"] == "LineString"
    assert (output / "summary.csv").read_text(encoding="utf-8").startswith("request_id,")
    assert (output / "planner_overlay.png").read_bytes().startswith(b"\x89PNG\r\n\x1a\n")
