import json
from pathlib import Path
import sys

import pytest

PACKAGE_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PACKAGE_ROOT))

from agt_navigation.site_task_binding import ValidatedSiteBinding  # noqa: E402
from agt_navigation.task_group import MapBinding, TaskGroup, Waypoint  # noqa: E402
from agt_navigation.task_registry import TaskRegistry, TaskRegistryError  # noqa: E402


def _digest(char: str) -> str:
    return "sha256:" + char * 64


def _binding(map_id="site", version_id="v1", *, map_hash_char="a"):
    return ValidatedSiteBinding(
        map_id=map_id,
        map_version_id=version_id,
        map_hash=_digest(map_hash_char),
        manifest_sha256=_digest("b"),
        navigation_yaml_sha256=_digest("1"),
        navigation_image_sha256=_digest("2"),
        localization_pcd_sha256=_digest("3"),
    )


def _resolver(state):
    def resolve(map_id: str, version_id: str):
        binding = state["binding"]
        assert map_id == binding.map_id
        assert version_id == binding.map_version_id
        return binding

    return resolve


def _immutable_site(root: Path) -> Path:
    site = root / "site" / "v1"
    (site / "navigation").mkdir(parents=True)
    (site / "pointcloud").mkdir()
    (site / "navigation" / "map.yaml").write_text("image: map.pgm\n", encoding="utf-8")
    (site / "navigation" / "map.pgm").write_bytes(b"P5\n1 1\n255\n\xff")
    (site / "pointcloud" / "localization_map.pcd").write_bytes(b"pcd")
    (site / "manifest.yaml").write_text("immutable site\n", encoding="utf-8")
    return site


def _tree_bytes(root: Path):
    return {
        path.relative_to(root).as_posix(): path.read_bytes()
        for path in sorted(root.rglob("*"))
        if path.is_file()
    }


def _task_json(map_id="site", version_id="v1", task_id="route", revision=1, x=0.5) -> str:
    task = TaskGroup(
        task_group_id=task_id,
        name="Route",
        description="",
        created_at="2026-07-29T00:00:00+00:00",
        updated_at="2026-07-29T00:00:00+00:00",
        revision=revision,
        map_binding=MapBinding(
            map_id,
            version_id,
            map_yaml_path="navigation/map.yaml",
            map_yaml_sha256=_digest("1"),
            map_image_sha256=_digest("2"),
            localization_pcd_sha256=_digest("3"),
            resolution=1.0,
            width=10,
            height=10,
        ),
        points=[Waypoint("wp_0001", "A", x, 0.5, 0.0)],
    )
    task.content_sha256 = task.canonical_hash()
    return json.dumps(task.to_dict(), ensure_ascii=False)


def test_put_get_update_archive_and_index_use_separate_task_root(tmp_path):
    tasks_root = tmp_path / "tasks"
    site_root = _immutable_site(tmp_path / "sites")
    site_before = _tree_bytes(site_root)
    state = {"binding": _binding()}
    registry = TaskRegistry(tasks_root, site_binding_resolver=_resolver(state))

    created = registry.put_task(
        _task_json(revision=1),
        map_id="site",
        map_version_id="v1",
        expected_revision=0,
        client_request_id="put_1",
    )
    assert created.task.revision == 1
    assert registry.get_task("site", "v1", "route", 1).task.content_sha256

    version = tasks_root / "site" / "v1"
    assert (version / "route.json").is_file()
    sidecar = json.loads((version / "site_binding.json").read_text(encoding="utf-8"))
    assert sidecar == state["binding"].to_dict()

    updated = registry.put_task(
        _task_json(revision=2, x=1.5),
        map_id="site",
        map_version_id="v1",
        expected_revision=1,
        client_request_id="put_2",
    )
    assert updated.task.revision == 2
    index = json.loads((version / "task_index.json").read_text(encoding="utf-8"))
    assert index["tasks"][0]["revision"] == 2

    archived = registry.archive_task(
        "site", "v1", "route", expected_revision=2, client_request_id="archive_1"
    )
    assert archived.archived_revision == 2
    assert (version / archived.archived_relative_path).is_file()
    index = json.loads((version / "task_index.json").read_text(encoding="utf-8"))
    assert index["tasks"] == []

    assert _tree_bytes(site_root) == site_before
    assert not (site_root / "tasks").exists()


def test_revision_conflict_and_duplicate_request(tmp_path):
    state = {"binding": _binding()}
    registry = TaskRegistry(tmp_path / "tasks", site_binding_resolver=_resolver(state))
    first = registry.put_task(
        _task_json(revision=1),
        map_id="site",
        map_version_id="v1",
        expected_revision=0,
        client_request_id="same_request",
    )
    duplicate = registry.put_task(
        _task_json(revision=1),
        map_id="site",
        map_version_id="v1",
        expected_revision=0,
        client_request_id="same_request",
    )
    assert duplicate.duplicate_request
    assert duplicate.task.content_sha256 == first.task.content_sha256

    with pytest.raises(TaskRegistryError) as exc:
        registry.put_task(
            _task_json(revision=2),
            map_id="site",
            map_version_id="v1",
            expected_revision=0,
        )
    assert exc.value.problem.code == "TASK_REVISION_CONFLICT"


def test_content_hash_schema_and_site_asset_hashes_are_strict(tmp_path):
    state = {"binding": _binding()}
    registry = TaskRegistry(tmp_path / "tasks", site_binding_resolver=_resolver(state))
    value = json.loads(_task_json())
    value["content_sha256"] = _digest("0")
    with pytest.raises(TaskRegistryError) as exc:
        registry.put_task(json.dumps(value), map_id="site", map_version_id="v1", expected_revision=0)
    assert exc.value.problem.code == "TASK_CONTENT_HASH_MISMATCH"

    value = json.loads(_task_json())
    value["unexpected"] = True
    value["content_sha256"] = ""
    with pytest.raises(TaskRegistryError) as exc:
        registry.put_task(json.dumps(value), map_id="site", map_version_id="v1", expected_revision=0)
    assert exc.value.problem.code == "TASK_SCHEMA_INVALID"

    value = json.loads(_task_json())
    value["map_binding"]["map_yaml_sha256"] = _digest("9")
    value["content_sha256"] = ""
    task = TaskGroup.from_dict(value)
    task.content_sha256 = task.canonical_hash()
    with pytest.raises(TaskRegistryError) as exc:
        registry.put_task(
            json.dumps(task.to_dict()), map_id="site", map_version_id="v1", expected_revision=0
        )
    assert exc.value.problem.code == "TASK_SITE_BINDING_MISMATCH"


def test_rejects_unsafe_components_and_symlink_escape(tmp_path):
    state = {"binding": _binding()}
    tasks_root = tmp_path / "tasks"
    registry = TaskRegistry(tasks_root, site_binding_resolver=_resolver(state))
    with pytest.raises(TaskRegistryError) as exc:
        registry.list_tasks("..", "v1")
    assert exc.value.problem.code == "INVALID_REQUEST"

    (tasks_root / "site").mkdir(parents=True)
    outside = tmp_path / "outside"
    outside.mkdir()
    (tasks_root / "site" / "v1").symlink_to(outside, target_is_directory=True)
    with pytest.raises(TaskRegistryError) as exc:
        registry.list_tasks("site", "v1")
    assert exc.value.problem.code == "INVALID_REQUEST"


def test_site_binding_change_is_fail_closed_and_does_not_modify_task(tmp_path):
    state = {"binding": _binding()}
    tasks_root = tmp_path / "tasks"
    registry = TaskRegistry(tasks_root, site_binding_resolver=_resolver(state))
    registry.put_task(_task_json(revision=1), map_id="site", map_version_id="v1", expected_revision=0)
    task_path = tasks_root / "site" / "v1" / "route.json"
    before = task_path.read_bytes()

    state["binding"] = _binding(map_hash_char="f")
    with pytest.raises(TaskRegistryError) as exc:
        registry.get_task("site", "v1", "route")
    assert exc.value.problem.code == "TASK_SITE_BINDING_MISMATCH"
    assert task_path.read_bytes() == before


def test_atomic_failure_restores_previous_task_and_site_binding(tmp_path, monkeypatch):
    state = {"binding": _binding()}
    tasks_root = tmp_path / "tasks"
    registry = TaskRegistry(tasks_root, site_binding_resolver=_resolver(state))
    registry.put_task(_task_json(revision=1), map_id="site", map_version_id="v1", expected_revision=0)
    version = tasks_root / "site" / "v1"
    task_path = version / "route.json"
    binding_path = version / "site_binding.json"
    before_task = task_path.read_bytes()
    before_binding = binding_path.read_bytes()

    def fail_index(*_args, **_kwargs):
        raise RuntimeError("simulated index failure")

    monkeypatch.setattr(registry, "_write_index", fail_index)
    with pytest.raises(TaskRegistryError) as exc:
        registry.put_task(_task_json(revision=2, x=2.5), map_id="site", map_version_id="v1", expected_revision=1)
    assert exc.value.problem.code == "TASK_NOT_SYNCED"
    assert task_path.read_bytes() == before_task
    assert binding_path.read_bytes() == before_binding
