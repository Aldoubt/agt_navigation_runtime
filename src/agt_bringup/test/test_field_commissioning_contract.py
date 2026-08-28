import re
from pathlib import Path

SRC_ROOT = Path(__file__).resolve().parents[2]
SYSTEM = SRC_ROOT / "agt_bringup" / "launch" / "system.launch.py"
FIELD_MAPPING = SRC_ROOT / "agt_bringup" / "launch" / "field_mapping.launch.py"
FIELD_NAVIGATION = SRC_ROOT / "agt_bringup" / "launch" / "field_navigation.launch.py"
BRINGUP_PACKAGE_XML = SRC_ROOT / "agt_bringup" / "package.xml"


def _declares_argument(source: str, name: str, default: str) -> bool:
    pattern = (
        rf'DeclareLaunchArgument\(\s*"{re.escape(name)}"\s*,\s*'
        rf'default_value="{re.escape(default)}"'
    )
    return re.search(pattern, source) is not None


def _declares_required_argument(source: str, name: str) -> bool:
    pattern = rf'DeclareLaunchArgument\(\s*"{re.escape(name)}"\s*\)'
    return re.search(pattern, source) is not None


def _has_frozen_asset_validation_loop(source: str) -> bool:
    pattern = (
        r'for\s+name\s+in\s*\(\s*'
        r'"global_map_pcd"\s*,\s*'
        r'"global_map_processing_record"\s*,\s*'
        r'"navigation_map"\s*,?\s*\)\s*:'
        r'.*?path\s*=\s*Path\(LaunchConfiguration\(name\)\.perform\(context\)\)'
        r'.*?if\s+not\s+path\.is_file\(\)\s*:'
        r'.*?raise\s+RuntimeError\(f"\{name\} must be a file: \{path\}"\)'
    )
    return re.search(pattern, source, flags=re.DOTALL) is not None


def test_system_exposes_safe_mapping_output_arguments():
    source = SYSTEM.read_text(encoding="utf-8")

    assert _declares_argument(source, "mapping_save_pcd", "false")
    assert _declares_argument(source, "mapping_pcd_save_interval", "-1")
    assert _declares_argument(
        source,
        "mapping_pcd_output_dir",
        "runtime/maps/fast_livo2",
    )

    assert '"save_pcd": LaunchConfiguration("mapping_save_pcd")' in source
    assert '"pcd_save_interval": LaunchConfiguration("mapping_pcd_save_interval")' in source
    assert '"pcd_output_dir": LaunchConfiguration("mapping_pcd_output_dir")' in source


def test_system_production_default_does_not_enable_pcd_save():
    source = SYSTEM.read_text(encoding="utf-8")

    assert _declares_argument(source, "mapping_save_pcd", "false")


def test_field_mapping_is_mapping_only_and_command_inert_by_default():
    assert FIELD_MAPPING.is_file(), "field_mapping.launch.py must exist"
    source = FIELD_MAPPING.read_text(encoding="utf-8")

    assert _declares_required_argument(source, "map_id")
    assert _declares_required_argument(source, "run_id")
    assert _declares_argument(source, "runtime_dir", "runtime")
    assert _declares_argument(source, "start_gnss", "false")
    assert _declares_argument(source, "start_chassis", "true")
    assert _declares_argument(source, "chassis_operation_mode", "monitor")

    assert '"start_sensor": "true"' in source
    assert '"start_sensor_monitor": "true"' in source
    assert '"start_odometry": "true"' in source
    assert '"start_perception": "false"' in source
    assert '"start_localization": "false"' in source
    assert '"start_navigation": "false"' in source
    assert '"mapping_save_pcd": "true"' in source
    assert '"mapping_pcd_save_interval": "-1"' in source
    assert '"mapping_pcd_output_dir": LaunchConfiguration("mapping_output_dir")' in source


def test_field_mapping_fails_closed_on_bad_identity_gnss_or_output_reuse():
    assert FIELD_MAPPING.is_file(), "field_mapping.launch.py must exist"
    source = FIELD_MAPPING.read_text(encoding="utf-8")

    assert "OpaqueFunction" in source
    assert "map_id must not be empty" in source
    assert "run_id must not be empty" in source
    assert "start_gnss requires an absolute gnss_input_topic" in source
    assert "gnss_input_topic must not equal canonical GNSS output" in source
    assert "refusing to reuse populated commissioning mapping directory" in source

    assert '"commissioning"' in source
    assert '"mapping"' in source
    assert 'SetLaunchConfiguration("mapping_output_dir"' in source


def test_system_forwards_rviz_goal_bridge_with_safe_default():
    source = SYSTEM.read_text(encoding="utf-8")

    assert _declares_argument(source, "enable_rviz_goal_bridge", "false")
    assert (
        '"enable_rviz_goal_bridge": LaunchConfiguration("enable_rviz_goal_bridge")'
        in source
    )


def test_field_navigation_uses_frozen_assets_and_explicit_commissioning_goal_bridge():
    assert FIELD_NAVIGATION.is_file(), "field_navigation.launch.py must exist"
    source = FIELD_NAVIGATION.read_text(encoding="utf-8")

    for name in (
        "global_map_pcd",
        "global_map_processing_record",
        "navigation_map",
        "map_id",
        "map_hash",
    ):
        assert _declares_required_argument(source, name)

    assert _declares_argument(source, "start_chassis", "false")
    assert _declares_argument(source, "chassis_operation_mode", "control")
    assert _declares_argument(source, "start_rviz", "true")

    assert '"start_sensor": "true"' in source
    assert '"start_sensor_monitor": "true"' in source
    assert '"start_odometry": "true"' in source
    assert '"mapping_save_pcd": "false"' in source
    assert '"start_perception": "true"' in source
    assert '"start_localization": "true"' in source
    assert '"start_navigation": "true"' in source
    assert '"enable_rviz_goal_bridge": "true"' in source
    assert '"global_map_pcd": LaunchConfiguration("global_map_pcd")' in source
    assert '"navigation_map": LaunchConfiguration("navigation_map")' in source
    assert '"map_id": LaunchConfiguration("map_id")' in source
    assert '"map_hash": LaunchConfiguration("map_hash")' in source

    assert 'package="rviz2"' in source
    assert 'executable="rviz2"' in source
    assert 'field_navigation.rviz' in source
    assert 'condition=IfCondition(LaunchConfiguration("start_rviz"))' in source
    assert "rtab" not in source.lower()


def test_field_navigation_fails_closed_on_asset_or_identity_mismatch():
    assert FIELD_NAVIGATION.is_file(), "field_navigation.launch.py must exist"
    source = FIELD_NAVIGATION.read_text(encoding="utf-8")

    assert "OpaqueFunction" in source
    assert "map_id must not be empty" in source
    assert _has_frozen_asset_validation_loop(source)
    assert "map_hash must match sha256:<64 lowercase hex>" in source


def test_bringup_declares_rviz2_runtime_dependency():
    package_xml = BRINGUP_PACKAGE_XML.read_text(encoding="utf-8")

    assert "<exec_depend>rviz2</exec_depend>" in package_xml
