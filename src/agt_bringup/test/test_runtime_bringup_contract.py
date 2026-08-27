from pathlib import Path
import xml.etree.ElementTree as ET


ROOT = Path(__file__).resolve().parents[3]
PACKAGE = ROOT / "src" / "agt_bringup"


def _forbidden_runtime_paths():
    v2_root = "agt_navigation_v2"
    return (
        v2_root + "/install",
        v2_root + "/src",
        "/home/" + "yangxuan",
    )


def test_runtime_bringup_package_exists_and_is_runtime_only():
    package_xml = PACKAGE / "package.xml"
    assert package_xml.is_file()
    root = ET.parse(package_xml).getroot()
    assert root.findtext("name") == "agt_bringup"

    dependencies = {
        element.text
        for element in root
        if element.tag in {"depend", "exec_depend", "buildtool_depend"}
    }
    required = {
        "ament_cmake",
        "agt_chassis",
        "agt_description",
        "agt_experiment_manager",
        "agt_interfaces",
        "agt_localization",
        "agt_mapping",
        "agt_navigation",
        "agt_perception",
        "agt_safety",
        "agt_sensor_adapters",
        "agt_sensor_monitor",
        "launch",
        "launch_ros",
        "nav2_msgs",
        "rclpy",
    }
    assert required <= dependencies
    forbidden = {
        "agt_coverage_planning",
        "agt_map_processing",
        "agt_teach_repeat",
        "agt_ui_bridge",
    }
    assert not (dependencies & forbidden)


def test_runtime_bringup_sources_do_not_reference_v2_workspace():
    forbidden_tokens = _forbidden_runtime_paths()
    for path in PACKAGE.rglob("*"):
        if not path.is_file() or path.suffix not in {".py", ".xml", ".txt", ".md"}:
            continue
        text = path.read_text(encoding="utf-8")
        for token in forbidden_tokens:
            assert token not in text, f"{path}: forbidden runtime dependency {token}"


def test_runtime_source_tree_has_no_v2_workspace_dependency_hints():
    forbidden_tokens = _forbidden_runtime_paths()[:2]
    runtime_src = ROOT / "src"
    for path in runtime_src.rglob("*"):
        if not path.is_file() or path.suffix not in {
            ".py",
            ".xml",
            ".txt",
            ".md",
            ".yaml",
            ".yml",
            ".launch",
        }:
            continue
        text = path.read_text(encoding="utf-8", errors="ignore")
        for token in forbidden_tokens:
            assert token not in text, f"{path}: forbidden V2 workspace hint {token}"


def test_system_launch_composes_only_runtime_packages_and_is_motion_safe_by_default():
    launch_path = PACKAGE / "launch" / "system.launch.py"
    source = launch_path.read_text(encoding="utf-8")

    for package in (
        "agt_description",
        "agt_sensor_adapters",
        "agt_sensor_monitor",
        "agt_mapping",
        "agt_perception",
        "agt_localization",
        "agt_navigation",
        "agt_chassis",
    ):
        assert f'get_package_share_directory("{package}")' in source

    assert 'DeclareLaunchArgument("platform", default_value="bunker")' in source
    assert 'DeclareLaunchArgument("start_localization", default_value="false")' in source
    assert 'DeclareLaunchArgument("start_navigation", default_value="false")' in source
    assert 'DeclareLaunchArgument("start_chassis", default_value="false")' in source
    assert 'DeclareLaunchArgument("start_gnss", default_value="false")' in source
    assert 'DeclareLaunchArgument("gnss_input_topic", default_value="")' in source
    assert '"publish_driver_odom_tf": "false"' in source
    assert '"autostart": "false"' in source
    assert "navigation_autostart" not in source
    assert 'package="agt_bringup"' in source
    assert 'executable="localization_navigation_gate.py"' in source
    assert "gnss_navsat.launch.py" in source
    assert "agt_navigation_v2" not in source


def test_gnss_is_opt_in_and_fail_closed_on_invalid_input_topic():
    source = (PACKAGE / "launch" / "system.launch.py").read_text(encoding="utf-8")
    assert 'if _enabled(context, "start_gnss"):' in source
    assert "start_gnss requires an absolute gnss_input_topic" in source
    assert "gnss_input_topic must not equal canonical GNSS output" in source
    assert '"gnss_enabled": LaunchConfiguration("start_gnss")' in source


def test_bunker_monitor_mode_is_command_inert_but_control_mode_keeps_command_topic():
    source = (
        ROOT / "src" / "agt_chassis" / "launch" / "bunker.launch.py"
    ).read_text(encoding="utf-8")
    assert "/agt/chassis/monitor_only_cmd_vel_disabled" in source
    assert 'LaunchConfiguration("command_topic")' in source
    assert 'LaunchConfiguration("operation_mode")' in source


def test_sensor_monitor_keeps_gnss_optional_when_enabled():
    source = (
        ROOT / "src" / "agt_sensor_monitor" / "launch" / "sensor_monitor.launch.py"
    ).read_text(encoding="utf-8")
    assert 'DeclareLaunchArgument("gnss_enabled", default_value="false")' in source
    assert '"gnss.enabled"' in source
    assert '"gnss.required": False' in source


def test_calibration_capture_is_fixed_to_motion_safe_monitor_composition():
    source = (PACKAGE / "launch" / "calibration_capture.launch.py").read_text(
        encoding="utf-8"
    )
    for literal in (
        '"start_sensor": "true"',
        '"start_sensor_monitor": "true"',
        '"start_odometry": "true"',
        '"start_perception": "false"',
        '"start_localization": "false"',
        '"start_navigation": "false"',
        '"start_chassis": "true"',
        '"chassis_operation_mode": "monitor"',
    ):
        assert literal in source
    assert "system.launch.py" in source
    assert "experiment_manager.launch.py" in source
    assert 'DeclareLaunchArgument("start_gnss", default_value="false")' in source
    assert 'DeclareLaunchArgument("gnss_input_topic", default_value="")' in source
    assert 'DeclareLaunchArgument("runtime_dir", default_value="runtime")' in source
    assert "start_navigation" not in source.replace('"start_navigation": "false"', "")
    assert "chassis_operation_mode" not in source.replace(
        '"chassis_operation_mode": "monitor"', ""
    )


def test_navigation_package_does_not_depend_back_on_bringup():
    navigation_launch = (
        ROOT / "src" / "agt_navigation" / "launch" / "navigation.launch.py"
    ).read_text(encoding="utf-8")
    navigation_manifest = (
        ROOT / "src" / "agt_navigation" / "package.xml"
    ).read_text(encoding="utf-8")
    assert 'package="agt_bringup"' not in navigation_launch
    assert "<exec_depend>agt_bringup</exec_depend>" not in navigation_manifest


def test_bringup_installs_gate_with_executable_permissions_under_symlink_builds():
    cmake = (PACKAGE / "CMakeLists.txt").read_text(encoding="utf-8")
    assert "AGT_BRINGUP_GENERATED_SCRIPT_DIR" in cmake
    assert "OWNER_EXECUTE" in cmake
    assert "GROUP_EXECUTE" in cmake
    assert "WORLD_EXECUTE" in cmake


def test_navigation_requires_localization_in_p0_launch_contract():
    source = (PACKAGE / "launch" / "system.launch.py").read_text(encoding="utf-8")
    assert "navigation requires start_localization:=true" in source
    assert 'required_files.append("navigation_map")' in source
    assert '"global_map_pcd", "global_map_processing_record"' in source
    assert 'raise RuntimeError(f"{name} must be a file: {path}")' in source


def test_root_readme_declares_runtime_bringup_and_no_v2_overlay_requirement():
    root_readme = (ROOT / "README.md").read_text(encoding="utf-8")
    assert "agt_bringup" in root_readme
    assert "ros2 launch agt_bringup system.launch.py" in root_readme
    v2_install_setup = "agt_navigation_v2" + "/install/setup.bash"
    assert f"must build without sourcing `{v2_install_setup}`" in root_readme


def test_mapping_readme_uses_runtime_bringup_as_runtime_owner():
    mapping_readme = (ROOT / "src" / "agt_mapping" / "README.md").read_text(
        encoding="utf-8"
    )
    assert "ros2 launch agt_bringup system.launch.py" in mapping_readme
    assert "V2.5 默认" not in mapping_readme
