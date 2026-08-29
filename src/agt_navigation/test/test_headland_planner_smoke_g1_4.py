from pathlib import Path
import importlib.util

import pytest


ROOT = Path(__file__).resolve().parents[1]


def _core_api():
    try:
        from agt_navigation.headland_planner_smoke import (
            validate_vehicle_request_derivation,
        )
    except ImportError as exc:
        pytest.fail(f"P1-G1.4 request-derivation validator is missing: {exc}")
    return validate_vehicle_request_derivation


def _load_runner_module():
    script = ROOT / "scripts" / "headland_planner_smoke.py"
    spec = importlib.util.spec_from_file_location("headland_planner_smoke_runner_g1_4", script)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def _manifest(*, request_count=16, radius_m=0.2):
    return {
        "schema_version": 1,
        "method": "nav2_headland_planner_smoke_manifest",
        "radius_m": radius_m,
        "counts": {
            "positive_pair_sides": 6,
            "negative_pair_sides": 2,
            "positive_requests": 12,
            "negative_requests": 4,
            "request_count": request_count,
        },
        "requests": [
            {"request_id": f"request-{index:02d}"}
            for index in range(request_count)
        ],
    }


def _derivation(**overrides):
    payload = {
        "schema_version": 1,
        "method": "p1_g1_3_vehicle_planner_request_derivation",
        "source_topology_radius_m": 0.2,
        "radius_role": "source_topology_clearance_proxy",
        "summary": {
            "source_pair_side_count": 14,
            "ready_pair_side_count": 8,
            "excluded_pair_side_count": 6,
            "positive_pair_side_count": 6,
            "negative_pair_side_count": 2,
            "directional_request_count": 16,
            "positive_requests": 12,
            "negative_requests": 4,
        },
    }
    payload.update(overrides)
    return payload


def test_g1_4_accepts_frozen_g1_3_derivation_for_exactly_16_vehicle_ready_requests():
    validate = _core_api()

    provenance = validate(_manifest(), _derivation())

    assert provenance == {
        "method": "p1_g1_3_vehicle_planner_request_derivation",
        "source_topology_radius_m": 0.2,
        "radius_role": "source_topology_clearance_proxy",
        "source_pair_side_count": 14,
        "ready_pair_side_count": 8,
        "excluded_pair_side_count": 6,
        "positive_pair_side_count": 6,
        "negative_pair_side_count": 2,
        "directional_request_count": 16,
        "positive_requests": 12,
        "negative_requests": 4,
    }


def test_g1_4_rejects_non_g1_3_derivation_method():
    validate = _core_api()
    bad = _derivation(method="some_other_derivation")

    with pytest.raises(ValueError, match="p1_g1_3_vehicle_planner_request_derivation"):
        validate(_manifest(), bad)


def test_g1_4_rejects_radius_role_that_reinterprets_topology_proxy_as_vehicle_radius():
    validate = _core_api()
    bad = _derivation(radius_role="vehicle_radius")

    with pytest.raises(ValueError, match="source_topology_clearance_proxy"):
        validate(_manifest(), bad)


def test_g1_4_rejects_manifest_and_derivation_request_count_mismatch():
    validate = _core_api()
    bad = _derivation()
    bad["summary"] = dict(bad["summary"], directional_request_count=14)

    with pytest.raises(ValueError, match="directional_request_count"):
        validate(_manifest(), bad)


def test_g1_4_rejects_source_topology_radius_mismatch():
    validate = _core_api()
    bad = _derivation(source_topology_radius_m=0.25)

    with pytest.raises(ValueError, match="source_topology_radius_m"):
        validate(_manifest(radius_m=0.2), bad)


def test_g1_4_runner_accepts_derivation_and_freezes_vehicle_probe_contract():
    runner = _load_runner_module()
    args = runner._parse_cli_args(
        [
            "--planner-pairs",
            "/tmp/vehicle_planner_pairs.yaml",
            "--gap-diagnostics",
            "/tmp/vehicle_ready_gap_diagnostics.json",
            "--request-derivation",
            "/tmp/vehicle_planner_request_derivation.json",
            "--map-yaml",
            "/tmp/navigation_base_map.yaml",
            "--output",
            "/tmp/g1_4_hybrid_probe",
            "--planner-contract",
            "mk_mini_g1_4_vehicle_ready_hybrid_dubin",
            "--result-mode",
            "reference_probe",
        ]
    )

    assert args.request_derivation == "/tmp/vehicle_planner_request_derivation.json"
    assert args.planner_contract == "mk_mini_g1_4_vehicle_ready_hybrid_dubin"
    assert args.result_mode == "reference_probe"

    source = (ROOT / "scripts" / "headland_planner_smoke.py").read_text(
        encoding="utf-8"
    )
    assert "validate_vehicle_request_derivation" in source
    assert '"request_derivation"' in source


def test_g1_4_launch_forwards_request_derivation_without_changing_hybrid_config():
    source = (ROOT / "launch" / "headland_planner_smoke.launch.py").read_text(
        encoding="utf-8"
    )

    assert 'DeclareLaunchArgument("request_derivation"' in source
    assert '"--request-derivation"' in source
    assert 'LaunchConfiguration("request_derivation")' in source

    config = (
        ROOT
        / "config"
        / "headland_planner_smoke_nav2_mk_mini_hybrid_dubin.yaml"
    ).read_text(encoding="utf-8")
    assert "motion_model_for_search: DUBIN" in config
    assert "minimum_turning_radius: 1.50" in config
    assert "allow_unknown: false" in config
    assert "inflate_around_unknown: false" in config
    assert "REEDS_SHEPP" not in config
