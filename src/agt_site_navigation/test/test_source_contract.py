import ast
from pathlib import Path


PACKAGE_ROOT = Path(__file__).resolve().parents[1]
REPO_ROOT = PACKAGE_ROOT.parents[1]
INTERFACES = REPO_ROOT / "src" / "agt_interfaces"


def test_typed_binding_interface_is_registered():
    message = INTERFACES / "msg" / "SiteNavigationBinding.msg"
    cmake = (INTERFACES / "CMakeLists.txt").read_text(encoding="utf-8")

    assert message.is_file()
    source = message.read_text(encoding="utf-8")
    for field in (
        "STATE_UNKNOWN=0",
        "STATE_READY=1",
        "STATE_BLOCKED=2",
        "STATE_ERROR=3",
        "string site_id",
        "string site_revision",
        "string site_hash",
        "string navigation_yaml",
        "string navigation_image",
        "string localization_pcd",
        "string[] blocker_codes",
    ):
        assert field in source
    assert '"msg/SiteNavigationBinding.msg"' in cmake


def test_typed_navigation_runtime_status_interface_is_registered():
    message = INTERFACES / "msg" / "NavigationRuntimeStatus.msg"
    cmake = (INTERFACES / "CMakeLists.txt").read_text(encoding="utf-8")

    assert message.is_file()
    source = message.read_text(encoding="utf-8")
    for field in (
        "STATE_UNKNOWN=0",
        "STATE_STARTING=1",
        "STATE_READY=2",
        "STATE_BLOCKED=3",
        "STATE_ERROR=4",
        "string site_id",
        "string site_revision",
        "string site_hash",
        "bool map_server_active",
        "bool planner_server_active",
        "bool smoother_server_active",
        "bool controller_server_active",
        "bool behavior_server_active",
        "bool bt_navigator_active",
        "bool waypoint_follower_active",
        "bool collision_monitor_active",
        "bool localization_bound",
        "bool map_identity_known",
        "bool map_identity_match",
        "string localization_map_id",
        "string localization_map_hash",
        "string[] blocker_codes",
    ):
        assert field in source
    assert '"msg/NavigationRuntimeStatus.msg"' in cmake


def test_site_navigation_package_installs_read_only_binding_node_and_launch():
    cmake = (PACKAGE_ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
    package = (PACKAGE_ROOT / "package.xml").read_text(encoding="utf-8")
    launch = (PACKAGE_ROOT / "launch" / "site_navigation_binding.launch.py").read_text(
        encoding="utf-8"
    )

    assert "ament_python_install_package" in cmake
    assert "site_navigation_binding_node.py" in cmake
    assert "test_resolver" in cmake
    assert "test_source_contract" in cmake
    for dependency in (
        "agt_interfaces",
        "agt_runtime_contracts",
        "agt_site_runtime",
        "ament_index_python",
        "rclpy",
    ):
        assert f"<depend>{dependency}</depend>" in package or f"<exec_depend>{dependency}</exec_depend>" in package
    assert 'DeclareLaunchArgument("sites_root", default_value="/opt/agt/sites")' in launch
    assert '"site_vehicle_profile", default_value="/opt/agt/profiles/bunker.yaml"' in launch


def test_binding_node_consumes_active_site_and_overwrites_latched_ready_on_blocker():
    source = (PACKAGE_ROOT / "scripts" / "site_navigation_binding_node.py").read_text(
        encoding="utf-8"
    )

    assert '"/agt/maps/active"' in source
    assert '"/agt/navigation/site_binding"' in source
    assert "DurabilityPolicy.TRANSIENT_LOCAL" in source
    assert "ReliabilityPolicy.RELIABLE" in source
    assert "ActiveSiteNavigationResolver" in source
    assert "SiteNavigationBinding.STATE_READY" in source
    assert "SiteNavigationBinding.STATE_BLOCKED" in source
    assert "SiteNavigationBinding.STATE_ERROR" in source
    assert "def _active_site_callback(" in source
    assert "self._publisher.publish(message)" in source

    # P1-04 is an asset binder only; these authorities belong elsewhere.
    forbidden = (
        "TransformBroadcaster",
        "StaticTransformBroadcaster",
        "ExecuteMission",
        "ActionServer",
        "ActionClient",
        "cmd_vel",
        "FollowPath",
        "FollowWaypoints",
        "write_text(",
        "write_bytes(",
    )
    for fragment in forbidden:
        assert fragment not in source


def test_navigation_runtime_node_is_installed_and_read_only():
    cmake = (PACKAGE_ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
    package = (PACKAGE_ROOT / "package.xml").read_text(encoding="utf-8")
    node_path = PACKAGE_ROOT / "scripts" / "navigation_runtime_status_node.py"
    launch_path = PACKAGE_ROOT / "launch" / "navigation_runtime_status.launch.py"

    assert node_path.is_file()
    assert launch_path.is_file()
    source = node_path.read_text(encoding="utf-8")
    launch = launch_path.read_text(encoding="utf-8")
    ast.parse(source)
    ast.parse(launch)

    assert "navigation_runtime_status_node.py" in cmake
    assert "test_runtime_status_policy" in cmake
    assert "<depend>lifecycle_msgs</depend>" in package
    assert '"/agt/navigation/site_binding"' in source
    assert '"/agt/localization/status"' in source
    assert '"/agt/navigation/runtime_status"' in source
    assert "NavigationRuntimeStatus" in source
    assert "SiteNavigationBinding" in source
    assert "LocalizationStatus" in source
    assert "GetState" in source
    assert "/get_state" in source
    assert "PRIMARY_STATE_ACTIVE" in source
    assert "DurabilityPolicy.TRANSIENT_LOCAL" in source
    assert "ReliabilityPolicy.RELIABLE" in source
    assert "evaluate_runtime_status" in source
    for required in (
        "map_server",
        "planner_server",
        "smoother_server",
        "controller_server",
        "behavior_server",
        "bt_navigator",
        "waypoint_follower",
        "collision_monitor",
    ):
        assert required in source

    forbidden = (
        "ChangeState",
        "/change_state",
        "TransformBroadcaster",
        "StaticTransformBroadcaster",
        "ActionServer",
        "ActionClient",
        "cmd_vel",
        "FollowPath",
        "FollowWaypoints",
        "write_text(",
        "write_bytes(",
    )
    for fragment in forbidden:
        assert fragment not in source


def test_runtime_status_launch_exposes_freshness_and_polling_policy():
    launch = (PACKAGE_ROOT / "launch" / "navigation_runtime_status.launch.py").read_text(
        encoding="utf-8"
    )

    assert 'DeclareLaunchArgument("localization_timeout_s"' in launch
    assert 'DeclareLaunchArgument("lifecycle_timeout_s"' in launch
    assert 'DeclareLaunchArgument("lifecycle_poll_period_s"' in launch
    assert 'executable="navigation_runtime_status_node.py"' in launch


def test_resolver_is_read_only_and_reuses_site_runtime_authority():
    source = (PACKAGE_ROOT / "agt_site_navigation" / "resolver.py").read_text(
        encoding="utf-8"
    )

    assert "SiteRegistry" in source
    assert "SiteValidator" in source
    assert "build_site_summary" in source
    assert "navigation_image_asset" in source
    assert "write_text(" not in source
    assert "write_bytes(" not in source
    assert "os.replace(" not in source
