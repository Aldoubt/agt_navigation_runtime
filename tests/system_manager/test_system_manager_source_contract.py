import ast
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
PACKAGE = ROOT / "src/agt_system_manager"
NODE = PACKAGE / "scripts/system_manager_node.py"
LAUNCH = PACKAGE / "launch/system_manager.launch.py"
CMAKE = PACKAGE / "CMakeLists.txt"
PACKAGE_XML = PACKAGE / "package.xml"
CONFIG = PACKAGE / "config/system_manager.yaml"


def test_system_manager_ros_package_files_exist():
    for path in (NODE, LAUNCH, CMAKE, PACKAGE_XML, CONFIG):
        assert path.is_file(), f"missing production system-manager file: {path}"


def test_system_manager_python_sources_parse():
    ast.parse(NODE.read_text(encoding="utf-8"))
    ast.parse(LAUNCH.read_text(encoding="utf-8"))


def test_system_manager_owns_authoritative_read_model_topics_and_services():
    source = NODE.read_text(encoding="utf-8")
    for topic in (
        "/agt/system/health",
        "/agt/system/task_readiness",
        "/agt/system/robot_state",
    ):
        assert f'"{topic}"' in source

    for service in (
        "/agt/system/health/get",
        "/agt/system/task_readiness/evaluate",
        "/agt/system/robot_state/get",
    ):
        assert f'"{service}"' in source

    for input_topic in (
        "/diagnostics",
        "/agt/maps/active",
        "/agt/localization/status",
        "/agt/missions/status",
        "/agt/safety/status",
        "/agt/chassis/status",
        "/agt/chassis/connected",
        "/agt/data/bags/status",
    ):
        assert f'"{input_topic}"' in source


def test_system_manager_uses_project_interfaces_and_pure_readiness_core():
    source = NODE.read_text(encoding="utf-8")
    for interface in (
        "GetSystemHealth",
        "EvaluateTaskReadiness",
        "GetRobotState",
        "SystemHealth",
        "TaskReadiness",
        "RobotState",
    ):
        assert interface in source
    assert "evaluate_navigation_readiness" in source
    assert "authoritative_map_known" in source
    assert "MapVersionSummary.STATE_UNKNOWN" in source
    assert '"agt_safety/controller"' in source


def test_system_manager_package_has_no_gateway_or_web_business_dependency():
    package_xml = PACKAGE_XML.read_text(encoding="utf-8").lower()
    cmake = CMAKE.read_text(encoding="utf-8").lower()
    combined = package_xml + "\n" + cmake
    assert "agt_interfaces" in combined
    assert "rclpy" in package_xml
    assert "gateway" not in combined
    assert "websocket" not in combined
    assert "http" not in combined


def test_system_manager_installs_executable_copy_for_symlink_install():
    cmake = CMAKE.read_text(encoding="utf-8")
    assert "generated_scripts" in cmake
    assert "file(COPY" in cmake
    assert "FILE_PERMISSIONS" in cmake
    assert "OWNER_EXECUTE" in cmake
    assert "GROUP_EXECUTE" in cmake
    assert "WORLD_EXECUTE" in cmake
    assert "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts/system_manager_node.py" in cmake


def test_launch_installs_configured_node_without_other_runtime_owners():
    source = LAUNCH.read_text(encoding="utf-8")
    assert 'package="agt_system_manager"' in source
    assert 'executable="system_manager_node.py"' in source
    assert "system_manager.yaml" in source
    assert "IncludeLaunchDescription" not in source
