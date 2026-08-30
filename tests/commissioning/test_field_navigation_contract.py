from pathlib import Path
import shutil

import pytest

from agt_field_commissioning.frozen_site import resolve_active_frozen_site


ROOT = Path(__file__).resolve().parents[2]
COMMISSIONING = ROOT / "src" / "agt_field_commissioning"
NAV_LAUNCH = COMMISSIONING / "launch" / "field_navigation.launch.py"
FIXTURE = ROOT / "tests" / "contracts" / "fixtures" / "site_valid"
VEHICLE = ROOT / "profiles" / "platforms" / "mk_mini.yaml"
VEHICLE_SCHEMA = ROOT / "schemas" / "vehicle_profile.schema.json"
SITE_SCHEMA = ROOT / "schemas" / "site_package.schema.json"


def _deploy_fixture(tmp_path: Path):
    sites_root = tmp_path / "sites"
    deployed = sites_root / "greenhouse_test" / "r01"
    shutil.copytree(FIXTURE, deployed)
    state_root = tmp_path / "state"
    state_root.mkdir(parents=True)
    (state_root / "active_site.yaml").write_text(
        "schema_version: '1.0'\nsite_id: greenhouse_test\nrevision: r01\n",
        encoding="utf-8",
    )
    return sites_root, state_root, deployed


def test_frozen_site_resolver_requires_exact_persisted_active_selection(tmp_path):
    sites_root, state_root, _ = _deploy_fixture(tmp_path)

    with pytest.raises(RuntimeError, match="active Site mismatch"):
        resolve_active_frozen_site(
            sites_root=sites_root,
            state_root=state_root,
            site_id="greenhouse_test",
            site_revision="r02",
            vehicle_profile=VEHICLE,
            vehicle_schema=VEHICLE_SCHEMA,
            site_schema=SITE_SCHEMA,
        )


def test_frozen_site_resolver_returns_validated_immutable_assets(tmp_path):
    sites_root, state_root, deployed = _deploy_fixture(tmp_path)

    assets = resolve_active_frozen_site(
        sites_root=sites_root,
        state_root=state_root,
        site_id="greenhouse_test",
        site_revision="r01",
        vehicle_profile=VEHICLE,
        vehicle_schema=VEHICLE_SCHEMA,
        site_schema=SITE_SCHEMA,
    )

    assert assets.site_id == "greenhouse_test"
    assert assets.site_revision == "r01"
    assert assets.navigation_yaml == (deployed / "map" / "navigation.yaml").resolve()
    assert assets.localization_pcd == (deployed / "map" / "localization_map.pcd").resolve()
    assert len(assets.site_hash) == 64
    assert len(assets.navigation_yaml_sha256) == 64
    assert len(assets.navigation_image_sha256) == 64
    assert len(assets.localization_pcd_sha256) == 64


def test_phase_c_uses_current_frozen_site_runtime_stack_only():
    text = NAV_LAUNCH.read_text(encoding="utf-8")

    for expected in (
        '"bunker_mid360.launch.py"',
        '"fast_livo2_odometry.launch.py"',
        '"relocalization.launch.py"',
        '"site_navigation_binding.launch.py"',
        '"navigation_runtime_status.launch.py"',
        '"navigation.launch.py"',
        '"safety.launch.py"',
        '"system_manager.launch.py"',
        "resolve_active_frozen_site",
    ):
        assert expected in text

    assert "agt_bringup" not in text
    assert "field_mapping.launch.py" not in text
    assert '"pcd_save.pcd_save_en": True' not in text
    assert "/commissioning/" not in text


def test_phase_c_starts_delivery_gateway_with_run_control_not_map_commissioning():
    text = NAV_LAUNCH.read_text(encoding="utf-8")

    assert 'package="agt_operator_gateway"' in text
    assert 'executable="operator_delivery_gateway_node.py"' in text
    assert '"commissioning_enabled": False' in text
    assert '"run_control_enabled": True' in text
    assert '"run_lidar_component_id": LaunchConfiguration("run_lidar_component_id").perform(context)' in text
    assert '"run_camera_gimbal_component_id": LaunchConfiguration("run_camera_gimbal_component_id").perform(context)' in text
    assert 'DeclareLaunchArgument("start_operator_gateway", default_value="true")' in text
    assert 'DeclareLaunchArgument("gateway_write_api_enabled", default_value="true")' in text


def test_phase_c_passes_site_derived_hashes_not_operator_map_paths():
    text = NAV_LAUNCH.read_text(encoding="utf-8")

    assert '"map": str(assets.navigation_yaml)' in text
    assert '"global_map_pcd": str(assets.localization_pcd)' in text
    assert '"map_hash": assets.localization_pcd_sha256' in text
    assert '"current_map_yaml_sha256": assets.navigation_yaml_sha256' in text
    assert '"current_map_image_sha256": assets.navigation_image_sha256' in text
    assert '"current_localization_pcd_sha256": assets.localization_pcd_sha256' in text
    assert 'DeclareLaunchArgument("global_map_pcd"' not in text
    assert 'DeclareLaunchArgument("navigation_map"' not in text
