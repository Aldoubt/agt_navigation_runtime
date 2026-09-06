from __future__ import annotations

import importlib.util
from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parents[1]
MODULE = ROOT / "agt_hardware_bringup" / "vehicle_preflight.py"


def load_module():
    spec = importlib.util.spec_from_file_location("vehicle_preflight_environment", MODULE)
    if spec is None or spec.loader is None:
        raise RuntimeError("unable to load vehicle_preflight module")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


TF_STATIC = """transforms:
- header:
    frame_id: base_footprint
  child_frame_id: base_link
- header:
    frame_id: base_link
  child_frame_id: lidar_link
- header:
    frame_id: lidar_link
  child_frame_id: livox_frame
- header:
    frame_id: lidar_link
  child_frame_id: imu_link
"""


def test_summary_distinguishes_warn_from_blocker():
    module = load_module()
    report = module.summarize_checks(
        [
            module.make_check("lidar", required=True, ok=True),
            module.make_warning_check("disk", ok=False, reason="low disk"),
        ]
    )
    assert report["ready"] is True
    assert report["result"] == "PASS_WITH_WARNINGS"
    assert report["warnings"] == ["disk"]
    assert report["blockers"] == []


def test_host_health_is_evidence_plus_warn_not_motion_blocker():
    module = load_module()
    checks = module.host_health_checks(
        {
            "cpu_count": 8,
            "load_1m": 2.0,
            "memory_available_mib": 512.0,
            "disk_free_gib": 2.0,
            "max_temperature_c": 92.0,
        },
        min_memory_available_mib=1024.0,
        min_disk_free_gib=5.0,
        max_temperature_c=90.0,
    )
    by_name = {check["name"]: check for check in checks}
    assert by_name["host:cpu"]["status"] == "PASS"
    assert by_name["host:memory"]["status"] == "WARN"
    assert by_name["host:disk"]["status"] == "WARN"
    assert by_name["host:temperature"]["status"] == "WARN"
    assert all(check["required"] is False for check in checks)


def test_tf_static_parser_and_required_bunker_mid360_topology():
    module = load_module()
    pairs = module.parse_tf_static_pairs(TF_STATIC)
    assert ("base_footprint", "base_link") in pairs
    assert ("base_link", "lidar_link") in pairs
    assert ("lidar_link", "livox_frame") in pairs
    assert ("lidar_link", "imu_link") in pairs

    check = module.static_tf_topology_check(TF_STATIC, required=True)
    assert check["status"] == "PASS"
    assert check["metrics"]["expected_edges"] == 4
    assert check["metrics"]["missing_edges"] == []


def test_tf_static_missing_lidar_edge_blocks_when_required():
    module = load_module()
    text = TF_STATIC.replace(
        "- header:\n    frame_id: base_link\n  child_frame_id: lidar_link\n", ""
    )
    check = module.static_tf_topology_check(text, required=True)
    assert check["status"] == "FAIL"
    assert "base_link->lidar_link" in check["metrics"]["missing_edges"]


def test_calibration_verified_is_separate_from_tf_existence():
    module = load_module()
    provisional = module.calibration_verification_check(
        "/**:\n  ros__parameters:\n    calibration_verified: false\n",
        required=False,
    )
    strict = module.calibration_verification_check(
        "/**:\n  ros__parameters:\n    calibration_verified: false\n",
        required=True,
    )
    verified = module.calibration_verification_check(
        "/**:\n  ros__parameters:\n    calibration_verified: true\n",
        required=True,
    )

    assert provisional["status"] == "WARN"
    assert strict["status"] == "FAIL"
    assert verified["status"] == "PASS"
    assert strict["metrics"]["calibration_verified"] is False
