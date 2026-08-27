from pathlib import Path
import xml.etree.ElementTree as ET


ROOT = Path(__file__).resolve().parents[3]
PACKAGE = ROOT / "src" / "agt_bringup"


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
    forbidden_tokens = (
        "agt_navigation_v2/install",
        "agt_navigation_v2/src",
        "/home/yangxuan",
    )
    for path in PACKAGE.rglob("*"):
        if not path.is_file() or path.suffix not in {".py", ".xml", ".txt", ".md"}:
            continue
        text = path.read_text(encoding="utf-8")
        for token in forbidden_tokens:
            assert token not in text, f"{path}: forbidden runtime dependency {token}"


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
    assert '"publish_driver_odom_tf": "false"' in source
    assert "agt_navigation_v2" not in source


def test_navigation_requires_localization_in_p0_launch_contract():
    source = (PACKAGE / "launch" / "system.launch.py").read_text(encoding="utf-8")
    assert "navigation requires start_localization:=true" in source
    assert "navigation_map must be a file" in source
    assert "global_map_pcd must be a file" in source
    assert "global_map_processing_record must be a file" in source
