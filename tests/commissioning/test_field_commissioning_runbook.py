from pathlib import Path

import yaml


ROOT = Path(__file__).resolve().parents[2]
RUNBOOK = ROOT / "docs" / "runbooks" / "field-navigation-commissioning.md"
BAG_PROFILES = ROOT / "src" / "agt_experiment_manager" / "config" / "bag_profiles.yaml"


def test_runbook_freezes_ordered_commissioning_flow():
    assert RUNBOOK.exists(), "P1-06 commissioning runbook is required"
    text = RUNBOOK.read_text(encoding="utf-8")

    ordered_markers = (
        "Phase A mapping",
        "field_mapping_commissioning",
        "normal Ctrl+C / ROS shutdown",
        "finalize_mapping_run.py",
        "offline reconstruction/export",
        "Site Package 1.0",
        "/agt/maps/validate",
        "deploy under sites_root",
        "/agt/maps/activate",
        "Phase C navigation",
    )
    offsets = []
    for marker in ordered_markers:
        assert marker in text, marker
        offsets.append(text.index(marker))
    assert offsets == sorted(offsets), "commissioning gates must stay in execution order"


def test_runbook_preserves_mutability_and_authority_boundaries():
    text = RUNBOOK.read_text(encoding="utf-8")

    for statement in (
        "commissioning output is mutable",
        "Site Package is immutable",
        "changing tasks never rebuilds the Site Package",
        "do not navigate directly from commissioning output",
        "feat/field-navigation-baseline",
        "feat/runtime-navigation-convergence-p1",
    ):
        assert statement in text

    assert "global_map_pcd:=$PCD" not in text
    assert "navigation_map:=$NAV_MAP" not in text


def test_runbook_uses_runtime_validation_and_lock_checked_activation():
    text = RUNBOOK.read_text(encoding="utf-8")

    assert "agt_interfaces/srv/ValidateMapVersion" in text
    assert "agt_interfaces/srv/ActivateMapVersion" in text
    assert "expected:" in text
    assert "map_hash:" in text
    assert "manifest_sha256:" in text
    assert "navigation_yaml_sha256:" in text
    assert "navigation_image_sha256:" in text
    assert "localization_pcd_sha256:" in text
    assert "field_navigation.launch.py" in text


def test_commissioning_bag_profile_records_commissioning_mapper_evidence():
    data = yaml.safe_load(BAG_PROFILES.read_text(encoding="utf-8"))
    profile = data["profiles"]["field_mapping_commissioning"]
    topics = set(profile["topics"])

    required = {
        "/clock",
        "/tf",
        "/tf_static",
        "/agt/sensors/lidar/custom",
        "/agt/sensors/lidar/custom_filtered",
        "/agt/sensors/imu/data",
        "/agt/commissioning/mapping/registered_points",
        "/agt/chassis/odometry",
        "/agt/chassis/status",
        "/agt/chassis/connected",
        "/diagnostics",
    }
    assert required <= topics
    assert "/agt/odometry/registered_points" not in topics
    assert "/agt/map/mapping_occupancy" not in topics
