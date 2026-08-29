import json
from pathlib import Path

import pytest
import yaml

from agt_navigation.legacy_task_migration import (
    LegacyTaskMigrationError,
    migrate_legacy_task_store,
)
from agt_navigation.site_task_binding import ValidatedSiteBinding
from agt_navigation.task_group import MapBinding, TaskGroup, Waypoint


def _digest(char: str) -> str:
    return "sha256:" + char * 64


def _binding() -> ValidatedSiteBinding:
    return ValidatedSiteBinding(
        map_id="orchard_a",
        map_version_id="r01",
        map_hash=_digest("a"),
        manifest_sha256=_digest("b"),
        navigation_yaml_sha256=_digest("c"),
        navigation_image_sha256=_digest("d"),
        localization_pcd_sha256=_digest("e"),
    )


def _resolver(map_id: str, map_version_id: str) -> ValidatedSiteBinding:
    binding = _binding()
    assert map_id == binding.map_id
    assert map_version_id == binding.map_version_id
    return binding


def _legacy_task(root: Path, *, task_id: str = "inspection", revision: int = 3):
    legacy_dir = root / "maps" / "orchard_a" / "versions" / "r01" / "tasks"
    legacy_dir.mkdir(parents=True, exist_ok=True)
    task = TaskGroup(
        task_group_id=task_id,
        name="Inspection",
        description="legacy task",
        created_at="2026-08-08T00:00:00+00:00",
        updated_at="2026-08-08T00:00:00+00:00",
        revision=revision,
        map_binding=MapBinding(
            map_id="orchard_a",
            map_version_id="r01",
            map_yaml_path="navigation/map.yaml",
            map_yaml_sha256=_digest("c"),
            map_image_sha256=_digest("d"),
            localization_pcd_sha256=_digest("e"),
            resolution=0.05,
            width=100,
            height=100,
            origin=(0.0, 0.0, 0.0),
        ),
        points=[Waypoint("wp_1", "A", 1.0, 2.0, 0.0)],
    )
    task.content_sha256 = task.canonical_hash()
    task_path = legacy_dir / f"{task_id}.json"
    task_path.write_text(json.dumps(task.to_dict(), ensure_ascii=False), encoding="utf-8")
    return task, legacy_dir, task_path


def _route_binding(task: TaskGroup, legacy_dir: Path) -> Path:
    path = legacy_dir / f"{task.task_group_id}.route.yaml"
    path.write_text(
        yaml.safe_dump(
            {
                "schema_version": 1,
                "status": "READY",
                "backend": "ROUTE",
                "task_binding": {
                    "task_group_id": task.task_group_id,
                    "task_revision": task.revision,
                    "task_content_sha256": task.content_sha256,
                },
                "route_binding": {
                    "route_id": "route_main",
                    "revision": 1,
                    "route_manifest_sha256": _digest("f"),
                },
            },
            sort_keys=False,
        ),
        encoding="utf-8",
    )
    return path


def test_dry_run_validates_without_writing(tmp_path):
    task, legacy_dir, _task_path = _legacy_task(tmp_path)
    _route_binding(task, legacy_dir)
    tasks_root = tmp_path / "tasks"

    report = migrate_legacy_task_store(
        legacy_maps_root=tmp_path / "maps",
        tasks_root=tasks_root,
        map_id="orchard_a",
        map_version_id="r01",
        site_binding_resolver=_resolver,
        dry_run=True,
    )

    assert report.migrated_task_ids == ("inspection",)
    assert report.migrated_route_binding_ids == ("inspection",)
    assert report.dry_run is True
    assert not tasks_root.exists()


def test_apply_preserves_revision_hash_and_moves_route_sidecar_authority(tmp_path):
    task, legacy_dir, _task_path = _legacy_task(tmp_path)
    legacy_route = _route_binding(task, legacy_dir)
    tasks_root = tmp_path / "tasks"

    report = migrate_legacy_task_store(
        legacy_maps_root=tmp_path / "maps",
        tasks_root=tasks_root,
        map_id="orchard_a",
        map_version_id="r01",
        site_binding_resolver=_resolver,
        dry_run=False,
    )

    target_dir = tasks_root / "orchard_a" / "r01"
    migrated = TaskGroup.from_json(target_dir / "inspection.json")
    assert migrated.revision == task.revision
    assert migrated.content_sha256 == task.content_sha256
    assert (target_dir / "site_binding.json").is_file()
    assert (target_dir / "inspection.route.yaml").read_bytes() == legacy_route.read_bytes()
    assert report.migrated_task_ids == ("inspection",)
    assert report.migrated_route_binding_ids == ("inspection",)


def test_rerun_is_idempotent_for_identical_destination(tmp_path):
    task, legacy_dir, _task_path = _legacy_task(tmp_path)
    _route_binding(task, legacy_dir)
    tasks_root = tmp_path / "tasks"

    kwargs = dict(
        legacy_maps_root=tmp_path / "maps",
        tasks_root=tasks_root,
        map_id="orchard_a",
        map_version_id="r01",
        site_binding_resolver=_resolver,
        dry_run=False,
    )
    migrate_legacy_task_store(**kwargs)
    second = migrate_legacy_task_store(**kwargs)

    assert second.migrated_task_ids == ()
    assert second.skipped_task_ids == ("inspection",)
    assert second.migrated_route_binding_ids == ()
    assert second.skipped_route_binding_ids == ("inspection",)


def test_conflicting_destination_fails_before_writing_other_tasks(tmp_path):
    first, _legacy_dir, _task_path = _legacy_task(tmp_path, task_id="a")
    _legacy_task(tmp_path, task_id="b")
    tasks_root = tmp_path / "tasks"
    target = tasks_root / "orchard_a" / "r01"
    target.mkdir(parents=True, exist_ok=True)
    conflict = TaskGroup.from_dict(first.to_dict())
    conflict.revision = first.revision + 1
    conflict.content_sha256 = conflict.canonical_hash()
    (target / "a.json").write_text(
        json.dumps(conflict.to_dict(), ensure_ascii=False), encoding="utf-8"
    )
    (target / "site_binding.json").write_text(
        json.dumps(_binding().to_dict()), encoding="utf-8"
    )

    with pytest.raises(LegacyTaskMigrationError) as exc:
        migrate_legacy_task_store(
            legacy_maps_root=tmp_path / "maps",
            tasks_root=tasks_root,
            map_id="orchard_a",
            map_version_id="r01",
            site_binding_resolver=_resolver,
            dry_run=False,
        )

    assert exc.value.code == "DESTINATION_CONFLICT"
    assert not (target / "b.json").exists()


def test_orphan_route_binding_is_rejected(tmp_path):
    legacy_dir = tmp_path / "maps" / "orchard_a" / "versions" / "r01" / "tasks"
    legacy_dir.mkdir(parents=True)
    (legacy_dir / "ghost.route.yaml").write_text("schema_version: 1\n", encoding="utf-8")

    with pytest.raises(LegacyTaskMigrationError) as exc:
        migrate_legacy_task_store(
            legacy_maps_root=tmp_path / "maps",
            tasks_root=tmp_path / "tasks",
            map_id="orchard_a",
            map_version_id="r01",
            site_binding_resolver=_resolver,
            dry_run=True,
        )
    assert exc.value.code == "ORPHAN_ROUTE_BINDING"


def test_legacy_source_symlink_is_rejected(tmp_path):
    task, _legacy_dir, task_path = _legacy_task(tmp_path)
    real_path = task_path.with_suffix(".real.json")
    task_path.rename(real_path)
    task_path.symlink_to(real_path)

    with pytest.raises(LegacyTaskMigrationError) as exc:
        migrate_legacy_task_store(
            legacy_maps_root=tmp_path / "maps",
            tasks_root=tmp_path / "tasks",
            map_id=task.map_binding.map_id,
            map_version_id=task.map_binding.map_version_id,
            site_binding_resolver=_resolver,
            dry_run=True,
        )
    assert exc.value.code == "UNSAFE_LEGACY_SOURCE"
