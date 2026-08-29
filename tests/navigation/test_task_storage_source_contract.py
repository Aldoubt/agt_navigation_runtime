from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parents[2]
NAV_PACKAGE = ROOT / "src" / "agt_navigation"
sys.path.insert(0, str(NAV_PACKAGE))

from agt_navigation.task_group import TaskRepository  # noqa: E402


def test_task_repository_uses_mutable_task_root_without_versions_or_tasks_suffix(tmp_path):
    tasks_root = tmp_path / "runtime" / "tasks"
    repository = TaskRepository(tasks_root, "orchard_a", "r01")

    assert repository.root == tasks_root.resolve()
    assert repository.directory == tasks_root.resolve() / "orchard_a" / "r01"


def test_production_task_persistence_has_no_legacy_map_tree_writer():
    task_registry = (
        NAV_PACKAGE / "agt_navigation" / "task_registry.py"
    ).read_text(encoding="utf-8")
    task_group = (
        NAV_PACKAGE / "agt_navigation" / "task_group.py"
    ).read_text(encoding="utf-8")

    legacy_fragments = (
        '/ "versions" / self.map_version_id / "tasks"',
        '/ "versions" / safe_version / "tasks"',
    )
    for fragment in legacy_fragments:
        assert fragment not in task_registry
        assert fragment not in task_group


def test_task_registry_ros_node_uses_tasks_root_and_deployed_site_resolver():
    source = (NAV_PACKAGE / "scripts" / "task_registry_node.py").read_text(encoding="utf-8")

    assert 'declare_parameter("tasks_root", "")' in source
    assert 'declare_parameter("sites_root", "/opt/agt/sites")' in source
    assert '"site_vehicle_profile", "/opt/agt/profiles/bunker.yaml"' in source
    assert "FilesystemSiteBindingResolver" in source
    assert "site_binding_resolver=site_binding_resolver" in source
    assert "TaskRegistry(\n            tasks_root," in source
    assert "TaskRegistry(\n            maps_root," not in source


def test_waypoint_execution_registry_uses_active_site_authority_and_task_root():
    source = (NAV_PACKAGE / "scripts" / "waypoint_task_server.py").read_text(encoding="utf-8")

    assert 'declare_parameter("tasks_root", "")' in source
    assert "binding_from_map_version_summary" in source
    assert "def _resolve_active_site_binding(" in source
    assert "require_active=True" in source
    assert "site_binding_resolver=self._resolve_active_site_binding" in source
    assert "TaskRegistry(\n            self.tasks_root," in source
    assert "TaskRegistry(\n            self.maps_root," not in source


def test_route_binding_sidecar_uses_mutable_task_root_only():
    capability = (NAV_PACKAGE / "scripts" / "navigation_capability_server.py").read_text(
        encoding="utf-8"
    )
    resolver = (NAV_PACKAGE / "agt_navigation" / "route_task_binding.py").read_text(
        encoding="utf-8"
    )

    assert "RouteTaskResolver(self.maps_root, self.tasks_root)" in capability
    assert "return self._route_resolver.binding_path(task)" in capability
    assert "self.tasks_root" in resolver
    assert "def binding_path(" in resolver
    assert 'version_root / "tasks"' not in resolver
    assert '/ "versions"\n            / task.map_binding.map_version_id\n            / "tasks"' not in capability


def test_legacy_migration_is_explicit_dry_run_by_default_and_installed():
    script = (NAV_PACKAGE / "scripts" / "migrate_legacy_task_store.py").read_text(
        encoding="utf-8"
    )
    cmake = (NAV_PACKAGE / "CMakeLists.txt").read_text(encoding="utf-8")
    migration = (
        NAV_PACKAGE / "agt_navigation" / "legacy_task_migration.py"
    ).read_text(encoding="utf-8")

    assert 'parser.add_argument(\n        "--apply"' in script
    assert "dry_run=not args.apply" in script
    assert "Runtime nodes never call this script automatically" in script
    assert "migrate_legacy_task_store.py" in cmake
    assert 'maps/<id>/versions/<rev>/tasks' in migration
    assert "Runtime execution never falls back" in migration


def test_navigation_launch_forwards_single_task_store_and_site_validation_inputs():
    source = (NAV_PACKAGE / "launch" / "navigation.launch.py").read_text(encoding="utf-8")

    assert 'DeclareLaunchArgument("tasks_root", default_value="")' in source
    assert 'DeclareLaunchArgument("sites_root", default_value="/opt/agt/sites")' in source
    assert '"site_vehicle_profile", default_value="/opt/agt/profiles/bunker.yaml"' in source

    capability = source[source.index('executable="navigation_capability_server.py"'):]
    assert '"tasks_root": LaunchConfiguration("tasks_root")' in capability

    task_registry = source[source.index('executable="task_registry_node.py"'):]
    assert '"tasks_root": LaunchConfiguration("tasks_root")' in task_registry
    assert '"sites_root": LaunchConfiguration("sites_root")' in task_registry
    assert '"site_vehicle_profile": LaunchConfiguration("site_vehicle_profile")' in task_registry
