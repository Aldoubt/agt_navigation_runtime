import json
from pathlib import Path
import sys

import pytest

PACKAGE_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PACKAGE_ROOT))

from agt_navigation.task_group import MapBinding, TaskGroup, Waypoint  # noqa: E402
from agt_navigation.task_registry import TaskRegistry, TaskRegistryError  # noqa: E402


def _ready_version(root: Path, map_id="site", version_id="v1") -> Path:
    version = root / map_id / "versions" / version_id
    (version / "navigation").mkdir(parents=True)
    (version / "pointcloud").mkdir()
    (version / "tasks").mkdir()
    (version / "navigation" / "map.yaml").write_text("image: map.pgm\n", encoding="utf-8")
    (version / "navigation" / "map.pgm").write_bytes(b"P5\n1 1\n255\n\xff")
    (version / "pointcloud" / "localization_map.pcd").write_bytes(b"pcd")
    (version / "manifest.yaml").write_text(
        "\n".join(
            (
                "schema_version: 1",
                f"map_id: {map_id}",
                f"map_version_id: {version_id}",
                "state: READY",
            )
        ),
        encoding="utf-8",
    )
    return version


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
            map_yaml_sha256="sha256:" + "1" * 64,
            map_image_sha256="sha256:" + "2" * 64,
            localization_pcd_sha256="sha256:" + "3" * 64,
            resolution=1.0,
            width=10,
            height=10,
        ),
        points=[Waypoint("wp_0001", "A", x, 0.5, 0.0)],
    )
    task.content_sha256 = task.canonical_hash()
    return json.dumps(task.to_dict(), ensure_ascii=False)


def test_put_get_update_archive_and_index(tmp_path):
    root = tmp_path / "maps"
    version = _ready_version(root)
    registry = TaskRegistry(root)

    created = registry.put_task(
        _task_json(revision=1),
        map_id="site",
        map_version_id="v1",
        expected_revision=0,
        client_request_id="put_1",
    )
    assert created.task.revision == 1
    assert registry.get_task("site", "v1", "route", 1).task.content_sha256

    updated = registry.put_task(
        _task_json(revision=2, x=1.5),
        map_id="site",
        map_version_id="v1",
        expected_revision=1,
        client_request_id="put_2",
    )
    assert updated.task.revision == 2
    index = json.loads((version / "tasks" / "task_index.json").read_text(encoding="utf-8"))
    assert index["tasks"][0]["revision"] == 2

    archived = registry.archive_task(
        "site", "v1", "route", expected_revision=2, client_request_id="archive_1"
    )
    assert archived.archived_revision == 2
    assert (version / archived.archived_relative_path).is_file()
    index = json.loads((version / "tasks" / "task_index.json").read_text(encoding="utf-8"))
    assert index["tasks"] == []


def test_revision_conflict_and_duplicate_request(tmp_path):
    root = tmp_path / "maps"
    _ready_version(root)
    registry = TaskRegistry(root)
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


def test_content_hash_and_schema_are_strict(tmp_path):
    root = tmp_path / "maps"
    _ready_version(root)
    registry = TaskRegistry(root)
    value = json.loads(_task_json())
    value["content_sha256"] = "sha256:" + "0" * 64
    with pytest.raises(TaskRegistryError) as exc:
        registry.put_task(json.dumps(value), map_id="site", map_version_id="v1", expected_revision=0)
    assert exc.value.problem.code == "TASK_CONTENT_HASH_MISMATCH"

    value = json.loads(_task_json())
    value["unexpected"] = True
    value["content_sha256"] = ""
    with pytest.raises(TaskRegistryError) as exc:
        registry.put_task(json.dumps(value), map_id="site", map_version_id="v1", expected_revision=0)
    assert exc.value.problem.code == "TASK_SCHEMA_INVALID"


def test_rejects_unsafe_components_and_symlink_escape(tmp_path):
    root = tmp_path / "maps"
    version = _ready_version(root)
    registry = TaskRegistry(root)
    with pytest.raises(TaskRegistryError) as exc:
        registry.list_tasks("..", "v1")
    assert exc.value.problem.code == "INVALID_REQUEST"

    (version / "tasks").rmdir()
    outside = tmp_path / "outside"
    outside.mkdir()
    (version / "tasks").symlink_to(outside, target_is_directory=True)
    with pytest.raises(TaskRegistryError) as exc:
        registry.list_tasks("site", "v1")
    assert exc.value.problem.code == "MAP_NOT_READY"


def test_atomic_failure_restores_previous_task_and_ready_assets(tmp_path, monkeypatch):
    root = tmp_path / "maps"
    version = _ready_version(root)
    registry = TaskRegistry(root)
    registry.put_task(_task_json(revision=1), map_id="site", map_version_id="v1", expected_revision=0)
    task_path = version / "tasks" / "route.json"
    before_task = task_path.read_bytes()
    ready_assets = {
        path: path.read_bytes()
        for path in (
            version / "navigation" / "map.yaml",
            version / "navigation" / "map.pgm",
            version / "pointcloud" / "localization_map.pcd",
        )
    }

    def fail_index(*_args, **_kwargs):
        raise RuntimeError("simulated index failure")

    monkeypatch.setattr(registry, "_write_index", fail_index)
    with pytest.raises(TaskRegistryError) as exc:
        registry.put_task(_task_json(revision=2, x=2.5), map_id="site", map_version_id="v1", expected_revision=1)
    assert exc.value.problem.code == "TASK_NOT_SYNCED"
    assert task_path.read_bytes() == before_task
    assert {path: path.read_bytes() for path in ready_assets} == ready_assets
