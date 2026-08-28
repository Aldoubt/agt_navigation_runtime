from pathlib import Path
import importlib.util

import yaml

from agt_navigation.headland_planner_smoke import finalize_smoke_results


ROOT = Path(__file__).resolve().parents[1]


def _load_runner_module():
    script = ROOT / "scripts" / "headland_planner_smoke.py"
    spec = importlib.util.spec_from_file_location("headland_planner_smoke_runner_g1", script)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def _request(request_id, expected_success):
    return {
        "request_id": request_id,
        "case_id": request_id.rsplit("-", 1)[0],
        "pair_id": "A01-A02",
        "side": "entry",
        "direction": "forward",
        "radius_m": 0.2,
        "expected_success": bool(expected_success),
        "expectation_class": "positive" if expected_success else "negative_control",
        "negative_reason": None if expected_success else "mixed_bridge",
        "baseline_connected": bool(expected_success),
        "conservative_connected": bool(expected_success),
        "start": {"x": 0.0, "y": 0.0, "yaw": 0.0},
        "goal": {"x": 1.0, "y": 0.0, "yaw": 0.0},
    }


def _reference_manifest():
    requests = [
        _request("positive-survives", True),
        _request("positive-rejected", True),
        _request("negative-plannable", False),
        _request("negative-rejected", False),
    ]
    return {
        "schema_version": 1,
        "method": "nav2_headland_planner_smoke_manifest",
        "radius_m": 0.2,
        "counts": {"request_count": len(requests)},
        "requests": requests,
    }


def test_g1_reference_probe_classifies_outcomes_without_expectation_mismatch():
    manifest = _reference_manifest()
    outcomes = [
        {"request_id": "positive-survives", "planner_success": True, "path_xy": [[0, 0], [1, 0]]},
        {"request_id": "positive-rejected", "planner_success": False, "path_xy": [], "failure_reason": "no path"},
        {"request_id": "negative-plannable", "planner_success": True, "path_xy": [[0, 0], [1, 0]]},
        {"request_id": "negative-rejected", "planner_success": False, "path_xy": [], "failure_reason": "no path"},
    ]

    result = finalize_smoke_results(manifest, outcomes, result_mode="reference_probe")

    assert result["result_mode"] == "reference_probe"
    assert result["summary"]["reference_positive_survives"] == 1
    assert result["summary"]["reference_positive_rejected"] == 1
    assert result["summary"]["reference_negative_plannable"] == 1
    assert result["summary"]["reference_negative_rejected"] == 1
    assert result["summary"]["infrastructure_error"] == 0
    assert result["summary"]["complete"] is True
    assert result["summary"]["probe_valid"] is True
    assert {item["probe_class"] for item in result["results"]} == {
        "reference_positive_survives",
        "reference_positive_rejected",
        "reference_negative_plannable",
        "reference_negative_rejected",
    }
    assert all(item.get("mismatch_type") is None for item in result["results"])


def test_g1_reference_probe_infrastructure_error_invalidates_probe():
    manifest = {
        **_reference_manifest(),
        "counts": {"request_count": 1},
        "requests": [_request("positive-infra", True)],
    }
    result = finalize_smoke_results(
        manifest,
        [
            {
                "request_id": "positive-infra",
                "planner_success": False,
                "infrastructure_error": True,
                "path_xy": [],
                "failure_reason": "planner timeout",
            }
        ],
        result_mode="reference_probe",
    )

    assert result["results"][0]["probe_class"] == "infrastructure_error"
    assert result["summary"]["infrastructure_error"] == 1
    assert result["summary"]["probe_valid"] is False


def test_g1_runner_accepts_reference_probe_result_mode():
    runner = _load_runner_module()
    args = runner._parse_cli_args(
        [
            "--planner-pairs",
            "/tmp/planner_pairs.yaml",
            "--gap-diagnostics",
            "/tmp/headland_gap_diagnostics.json",
            "--map-yaml",
            "/tmp/navigation_base_map.yaml",
            "--output",
            "/tmp/planner_smoke",
            "--result-mode",
            "reference_probe",
        ]
    )
    assert args.result_mode == "reference_probe"


def test_g1_launch_forwards_result_mode_to_runner():
    source = (ROOT / "launch" / "headland_planner_smoke.launch.py").read_text(
        encoding="utf-8"
    )
    assert '"--result-mode"' in source
    assert 'LaunchConfiguration("result_mode")' in source
    assert '"result_mode"' in source


def test_g1_mk_mini_hybrid_dubin_config_freezes_vehicle_preview_geometry():
    config = yaml.safe_load(
        (
            ROOT
            / "config"
            / "headland_planner_smoke_nav2_mk_mini_hybrid_dubin.yaml"
        ).read_text(encoding="utf-8")
    )

    planner = config["planner_server"]["ros__parameters"]
    plugin = planner["GridBased"]
    assert planner["planner_plugins"] == ["GridBased"]
    assert plugin["plugin"] == "nav2_smac_planner/SmacPlannerHybrid"
    assert plugin["motion_model_for_search"] == "DUBIN"
    assert plugin["minimum_turning_radius"] == 1.5
    assert plugin["angle_quantization_bins"] == 72
    assert plugin["allow_unknown"] is False
    assert plugin["tolerance"] == 0.0
    assert plugin["analytic_expansion_max_length"] >= 6.0

    costmap = config["global_costmap"]["global_costmap"]["ros__parameters"]
    assert "robot_radius" not in costmap
    assert yaml.safe_load(costmap["footprint"]) == [
        [0.420, 0.300],
        [0.420, -0.300],
        [-0.420, -0.300],
        [-0.420, 0.300],
    ]
    assert costmap["footprint_padding"] == 0.0
    assert costmap["track_unknown_space"] is True
    assert costmap["inflation_layer"]["inflate_unknown"] is False
    assert costmap["inflation_layer"]["inflate_around_unknown"] is False
