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
