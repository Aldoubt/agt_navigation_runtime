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
