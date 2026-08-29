"""Explicit one-way migration from the legacy map-local task store.

Runtime execution never falls back to ``maps/<id>/versions/<rev>/tasks``.  This
module exists only for an operator-invoked migration into the mutable Task
Library at ``tasks/<site>/<revision>``.
"""

from __future__ import annotations

from dataclasses import dataclass
import json
from pathlib import Path
from typing import Callable

import yaml

from .site_task_binding import ValidatedSiteBinding, normalize_sha256
from .task_group import TaskGroup, TaskGroupError, _write_bytes_atomic
from .task_registry import TaskRegistry, TaskRegistryError


SiteBindingResolver = Callable[[str, str], ValidatedSiteBinding]


class LegacyTaskMigrationError(RuntimeError):
    def __init__(self, code: str, message: str) -> None:
        super().__init__(message)
        self.code = str(code)
        self.message = str(message)


@dataclass(frozen=True)
class LegacyTaskMigrationReport:
    map_id: str
    map_version_id: str
    source_directory: Path
    destination_directory: Path
    migrated_task_ids: tuple[str, ...] = ()
    skipped_task_ids: tuple[str, ...] = ()
    migrated_route_binding_ids: tuple[str, ...] = ()
    skipped_route_binding_ids: tuple[str, ...] = ()
    dry_run: bool = True


def _migration_error(code: str, message: str, exc: Exception | None = None):
    error = LegacyTaskMigrationError(code, message)
    if exc is None:
        raise error
    raise error from exc


def _safe_identity(map_id: str, map_version_id: str) -> tuple[str, str]:
    try:
        return (
            TaskRegistry.safe_component(str(map_id), "map_id"),
            TaskRegistry.safe_component(str(map_version_id), "map_version_id"),
        )
    except TaskRegistryError as exc:
        _migration_error("INVALID_IDENTITY", exc.problem.technical_message, exc)


def _resolve_binding(
    resolver: SiteBindingResolver,
    map_id: str,
    map_version_id: str,
) -> ValidatedSiteBinding:
    try:
        binding = resolver(map_id, map_version_id)
    except Exception as exc:
        _migration_error("SITE_VALIDATION_FAILED", f"cannot validate destination Site: {exc}", exc)
    if not isinstance(binding, ValidatedSiteBinding):
        _migration_error(
            "SITE_VALIDATION_FAILED", "site binding resolver returned an unsupported value"
        )
    if binding.map_id != map_id or binding.map_version_id != map_version_id:
        _migration_error(
            "SITE_VALIDATION_FAILED",
            "validated Site identity does not match requested migration identity",
        )
    return binding


def _read_legacy_task(
    path: Path,
    *,
    map_id: str,
    map_version_id: str,
    site_binding: ValidatedSiteBinding,
) -> tuple[TaskGroup, str]:
    if path.is_symlink() or not path.is_file():
        _migration_error("UNSAFE_LEGACY_SOURCE", f"legacy task must be a regular file: {path}")
    try:
        raw = path.read_text(encoding="utf-8")
        task = TaskGroup.from_dict(json.loads(raw))
    except (OSError, UnicodeError, json.JSONDecodeError, TaskGroupError) as exc:
        _migration_error("INVALID_LEGACY_TASK", f"cannot validate legacy task {path.name}: {exc}", exc)
    if task.task_group_id != path.stem:
        _migration_error(
            "INVALID_LEGACY_TASK",
            f"legacy task_group_id {task.task_group_id} does not match file name {path.name}",
        )
    if task.map_binding.map_id != map_id or task.map_binding.map_version_id != map_version_id:
        _migration_error(
            "INVALID_LEGACY_TASK",
            f"legacy task {task.task_group_id} is bound to a different Site revision",
        )
    try:
        TaskRegistry._validate_task_site_binding(task, site_binding)
    except TaskRegistryError as exc:
        _migration_error(
            "INVALID_LEGACY_TASK",
            f"legacy task {task.task_group_id} does not match validated Site: {exc}",
            exc,
        )
    return task, raw


def _read_route_binding(path: Path, task: TaskGroup) -> bytes:
    if path.is_symlink() or not path.is_file():
        _migration_error(
            "UNSAFE_LEGACY_SOURCE", f"legacy route binding must be a regular file: {path}"
        )
    try:
        payload = path.read_bytes()
        value = yaml.safe_load(payload.decode("utf-8")) or {}
    except (OSError, UnicodeError, yaml.YAMLError) as exc:
        _migration_error(
            "INVALID_ROUTE_BINDING", f"cannot read legacy route binding {path.name}: {exc}", exc
        )
    if not isinstance(value, dict):
        _migration_error("INVALID_ROUTE_BINDING", f"{path.name} must contain a mapping")
    if int(value.get("schema_version", 0)) != 1:
        _migration_error("INVALID_ROUTE_BINDING", f"{path.name} has unsupported schema_version")
    if str(value.get("status", "")).upper() != "READY":
        _migration_error("INVALID_ROUTE_BINDING", f"{path.name} is not READY")
    if str(value.get("backend", "")).upper() != "ROUTE":
        _migration_error("INVALID_ROUTE_BINDING", f"{path.name} backend is not ROUTE")
    task_binding = value.get("task_binding") or {}
    expected = {
        "task_group_id": task.task_group_id,
        "task_revision": int(task.revision),
        "task_content_sha256": task.content_sha256,
    }
    for key, expected_value in expected.items():
        if task_binding.get(key) != expected_value:
            _migration_error(
                "INVALID_ROUTE_BINDING",
                f"{path.name} {key} does not match legacy task {task.task_group_id}",
            )
    route_binding = value.get("route_binding") or {}
    if not isinstance(route_binding, dict) or not str(route_binding.get("route_id", "")):
        _migration_error("INVALID_ROUTE_BINDING", f"{path.name} has no route_id")
    try:
        if int(route_binding.get("revision", 0)) <= 0:
            raise ValueError("revision must be positive")
        normalize_sha256(str(route_binding.get("route_manifest_sha256", "")))
    except Exception as exc:
        _migration_error(
            "INVALID_ROUTE_BINDING", f"{path.name} has invalid route identity/hash: {exc}", exc
        )
    return payload


def _destination_root(tasks_root: str | Path, map_id: str, map_version_id: str) -> Path:
    root = Path(tasks_root).expanduser().resolve()
    map_root = root / map_id
    destination = map_root / map_version_id
    if root.is_symlink() or map_root.is_symlink() or destination.is_symlink():
        _migration_error("DESTINATION_CONFLICT", "destination task identity path must not be a symlink")
    resolved = destination.resolve(strict=False)
    try:
        resolved.relative_to(root)
    except ValueError as exc:
        _migration_error("DESTINATION_CONFLICT", "destination escapes tasks_root", exc)
    return resolved


def _validate_existing_site_binding(
    destination: Path, expected: ValidatedSiteBinding
) -> None:
    if not destination.exists():
        return
    binding_path = destination / "site_binding.json"
    if not binding_path.is_file() or binding_path.is_symlink():
        _migration_error(
            "DESTINATION_CONFLICT",
            "existing destination is missing a regular site_binding.json",
        )
    try:
        current = ValidatedSiteBinding.from_dict(
            json.loads(binding_path.read_text(encoding="utf-8"))
        )
    except Exception as exc:
        _migration_error(
            "DESTINATION_CONFLICT", f"cannot validate destination site_binding.json: {exc}", exc
        )
    if current != expected:
        _migration_error(
            "DESTINATION_CONFLICT",
            "existing destination is bound to different Site content",
        )


def migrate_legacy_task_store(
    *,
    legacy_maps_root: str | Path,
    tasks_root: str | Path,
    map_id: str,
    map_version_id: str,
    site_binding_resolver: SiteBindingResolver,
    dry_run: bool = True,
) -> LegacyTaskMigrationReport:
    """Preflight and optionally migrate one legacy Site revision task directory.

    The operation is intentionally explicit and idempotent. All source files and
    destination conflicts are checked before the first write. Existing identical
    task/route files are skipped; any non-identical destination is a hard error.
    """

    safe_map, safe_version = _safe_identity(map_id, map_version_id)
    maps_root = Path(legacy_maps_root).expanduser().resolve()
    source = maps_root / safe_map / "versions" / safe_version / "tasks"
    if source.is_symlink():
        _migration_error("UNSAFE_LEGACY_SOURCE", "legacy task directory must not be a symlink")
    if not source.is_dir():
        _migration_error("LEGACY_SOURCE_MISSING", f"legacy task directory does not exist: {source}")
    try:
        source.resolve().relative_to(maps_root)
    except ValueError as exc:
        _migration_error("UNSAFE_LEGACY_SOURCE", "legacy task directory escapes maps_root", exc)

    site_binding = _resolve_binding(site_binding_resolver, safe_map, safe_version)
    destination = _destination_root(tasks_root, safe_map, safe_version)
    _validate_existing_site_binding(destination, site_binding)

    tasks: dict[str, tuple[TaskGroup, str]] = {}
    for path in sorted(source.glob("*.json")):
        if path.name == "task_index.json":
            continue
        task, raw = _read_legacy_task(
            path,
            map_id=safe_map,
            map_version_id=safe_version,
            site_binding=site_binding,
        )
        if task.task_group_id in tasks:
            _migration_error(
                "INVALID_LEGACY_TASK", f"duplicate task_group_id: {task.task_group_id}"
            )
        tasks[task.task_group_id] = (task, raw)

    route_sources: dict[str, tuple[Path, bytes]] = {}
    for path in sorted(source.glob("*.route.yaml")):
        task_id = path.name[: -len(".route.yaml")]
        if task_id not in tasks:
            _migration_error(
                "ORPHAN_ROUTE_BINDING",
                f"route binding has no matching legacy task JSON: {path.name}",
            )
        route_sources[task_id] = (path, _read_route_binding(path, tasks[task_id][0]))

    migrate_tasks: list[str] = []
    skip_tasks: list[str] = []
    migrate_routes: list[str] = []
    skip_routes: list[str] = []

    for task_id, (task, _raw) in tasks.items():
        target = destination / f"{task_id}.json"
        if target.is_symlink():
            _migration_error("DESTINATION_CONFLICT", f"destination task is a symlink: {target}")
        if target.exists():
            try:
                current = TaskGroup.from_json(target)
            except TaskGroupError as exc:
                _migration_error("DESTINATION_CONFLICT", f"invalid destination task {target}: {exc}", exc)
            if (
                current.task_group_id == task.task_group_id
                and current.revision == task.revision
                and current.content_sha256 == task.content_sha256
            ):
                skip_tasks.append(task_id)
            else:
                _migration_error(
                    "DESTINATION_CONFLICT",
                    f"destination task differs from legacy task: {task_id}",
                )
        else:
            migrate_tasks.append(task_id)

    for task_id, (_source_path, payload) in route_sources.items():
        target = destination / f"{task_id}.route.yaml"
        if target.is_symlink():
            _migration_error("DESTINATION_CONFLICT", f"destination route binding is a symlink: {target}")
        if target.exists():
            try:
                current_payload = target.read_bytes()
            except OSError as exc:
                _migration_error("DESTINATION_CONFLICT", f"cannot read destination route binding: {exc}", exc)
            if current_payload == payload:
                skip_routes.append(task_id)
            else:
                _migration_error(
                    "DESTINATION_CONFLICT",
                    f"destination route binding differs from legacy source: {task_id}",
                )
        else:
            migrate_routes.append(task_id)

    report = LegacyTaskMigrationReport(
        map_id=safe_map,
        map_version_id=safe_version,
        source_directory=source,
        destination_directory=destination,
        migrated_task_ids=tuple(migrate_tasks),
        skipped_task_ids=tuple(skip_tasks),
        migrated_route_binding_ids=tuple(migrate_routes),
        skipped_route_binding_ids=tuple(skip_routes),
        dry_run=bool(dry_run),
    )
    if dry_run:
        return report

    registry = TaskRegistry(
        tasks_root,
        site_binding_resolver=site_binding_resolver,
    )
    for task_id in migrate_tasks:
        task, raw = tasks[task_id]
        try:
            registry.put_task(
                raw,
                map_id=safe_map,
                map_version_id=safe_version,
                task_group_id=task_id,
                expected_revision=0,
                client_request_id="",
            )
        except TaskRegistryError as exc:
            _migration_error(
                "TASK_WRITE_FAILED", f"cannot migrate task {task_id}: {exc}", exc
            )

    # A task write creates the destination and validated site_binding.json. If a
    # store contains only idempotently skipped tasks, the directory already
    # existed by preflight. Therefore route sidecars can now be written safely.
    for task_id in migrate_routes:
        _source_path, payload = route_sources[task_id]
        target = destination / f"{task_id}.route.yaml"
        try:
            _write_bytes_atomic(target, payload)
        except Exception as exc:
            _migration_error(
                "ROUTE_BINDING_WRITE_FAILED",
                f"cannot migrate route binding {task_id}: {exc}",
                exc,
            )

    return report
