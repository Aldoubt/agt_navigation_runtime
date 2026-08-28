import ast
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
PACKAGE = ROOT / "src/agt_site_runtime"
NODE = PACKAGE / "scripts/site_runtime_node.py"
LAUNCH = PACKAGE / "launch/site_runtime.launch.py"
CMAKE = PACKAGE / "CMakeLists.txt"
PACKAGE_XML = PACKAGE / "package.xml"
CONFIG = PACKAGE / "config/site_runtime.yaml"
README = PACKAGE / "README.md"


def test_site_runtime_ros_package_files_exist():
    for path in (NODE, LAUNCH, CMAKE, PACKAGE_XML, CONFIG, README):
        assert path.is_file(), f"missing production site-runtime file: {path}"


def test_site_runtime_python_sources_parse():
    ast.parse(NODE.read_text(encoding="utf-8"))
    ast.parse(LAUNCH.read_text(encoding="utf-8"))


def test_site_runtime_owns_only_read_only_map_runtime_api():
    source = NODE.read_text(encoding="utf-8")
    for name in (
        "/agt/maps/active",
        "/agt/maps/list",
        "/agt/maps/validate",
        "/agt/maps/activate",
    ):
        assert f'"{name}"' in source

    for interface in (
        "MapVersionSummary",
        "ListMapVersions",
        "ValidateMapVersion",
        "ActivateMapVersion",
    ):
        assert interface in source

    forbidden = (
        "ManageMapVersion",
        "/agt/maps/manage",
        "/agt/maps/import",
        "/agt/maps/delete",
        "/agt/maps/archive",
        "/agt/maps/purge",
        "/agt/maps/pin",
        "/agt/maps/unpin",
    )
    for token in forbidden:
        assert token not in source


def test_active_map_publisher_is_reliable_transient_local_depth_one():
    source = NODE.read_text(encoding="utf-8")
    assert "QoSProfile(depth=1)" in source
    assert "ReliabilityPolicy.RELIABLE" in source
    assert "DurabilityPolicy.TRANSIENT_LOCAL" in source
    assert '"/agt/maps/active"' in source


def test_startup_restore_can_publish_tombstone_to_revoke_stale_authority():
    source = NODE.read_text(encoding="utf-8")
    assert ".restore()" in source
    assert "revoke_active" in source
    assert "STATE_UNKNOWN" in source
    assert "_publish_tombstone" in source


def test_site_runtime_uses_installed_contract_package_not_repository_schemas():
    source = NODE.read_text(encoding="utf-8")
    assert 'get_package_share_directory("agt_runtime_contracts")' in source
    assert "vehicle_profile.schema.json" in source
    assert "site_package.schema.json" in source
    assert "../../schemas" not in source
    assert "tools.runtime_contracts" not in source


def test_package_declares_required_runtime_dependencies_and_no_gateway_dependency():
    package_xml = PACKAGE_XML.read_text(encoding="utf-8").lower()
    cmake = CMAKE.read_text(encoding="utf-8").lower()
    combined = package_xml + "\n" + cmake
    for dependency in (
        "agt_interfaces",
        "agt_runtime_contracts",
        "ament_cmake_python",
        "ament_index_python",
        "rclpy",
    ):
        assert dependency in combined
    assert "gateway" not in combined
    assert "websocket" not in combined
    assert "http" not in combined


def test_site_runtime_installs_executable_copy_for_symlink_install():
    cmake = CMAKE.read_text(encoding="utf-8")
    assert "generated_scripts" in cmake
    assert "file(COPY" in cmake
    assert "FILE_PERMISSIONS" in cmake
    assert "OWNER_EXECUTE" in cmake
    assert "GROUP_EXECUTE" in cmake
    assert "WORLD_EXECUTE" in cmake
    assert "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts/site_runtime_node.py" in cmake


def test_launch_is_thin_and_does_not_start_navigation_or_localization():
    source = LAUNCH.read_text(encoding="utf-8")
    assert 'package="agt_site_runtime"' in source
    assert 'executable="site_runtime_node.py"' in source
    assert "site_runtime.yaml" in source
    assert "IncludeLaunchDescription" not in source
    assert "nav2" not in source.lower()
    assert "localization" not in source.lower()


def test_default_config_exposes_only_deployment_and_selection_inputs():
    source = CONFIG.read_text(encoding="utf-8")
    for key in ("sites_root:", "state_root:", "vehicle_profile:", "recent_request_limit:"):
        assert key in source
    for forbidden in ("v2", "workspace", "import", "delete", "archive", "purge"):
        assert forbidden not in source.lower()
