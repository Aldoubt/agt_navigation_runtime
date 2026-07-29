from __future__ import annotations

from collections import OrderedDict
from dataclasses import dataclass
from datetime import datetime, timezone
import json
import os
from pathlib import Path
from typing import Any, Mapping

import yaml

from agt_navigation.navigation_errors import Blocker, blocker
from agt_navigation.task_group import (
    SAFE_COMPONENT_RE,
    TaskGroup,
    TaskGroupError,
    _rotate_backups,
    _safe_component,
    _write_bytes_atomic,
    _write_json_atomic,
)


DEFAULT_MAXIMUM_TASK_BYTES = 1024 * 1024


class TaskRegistryError(RuntimeError):
    def __init__(self, problem: Blocker) -> None:
        super().__init__(problem.technical_message)
        self.problem = problem


@dataclass(frozen=True)
class StoredTask:
    task: TaskGroup
    task_json: str
    path: Path


@dataclass(frozen=True)
class PutTaskResult:
    task: TaskGroup
    task_json: str
    duplicate_request: bool = False


@dataclass(frozen=True)
class ArchiveTaskResult:
    map_id: str
    map_version_id: str
    task_group_id: str
    archived_revision: int
    archived_relative_path: str
    duplicate_request: bool = False


def _now_stamp() -> str:
    return datetime.now(timezone.utc).strftime("%Y%m%d_%H%M%S_%f")


def _task_payload(task: TaskGroup) -> bytes:
    return (
        json.dumps(task.to_dict(), ensure_ascii=False, indent=2, allow_nan=False)
        + "\n"
    ).encode("utf-8")


class TaskRegistry:
    """Robot-side authority for versioned waypoint task JSON.

    The registry resolves all task paths from map/task identifiers. It never
    accepts an arbitrary client file path and never mutates READY navigation,
    PGM, YAML, or PCD assets.
    """

    def __init__(
        self,
        runtime_maps_root: str | Path,
        *,
        maximum_task_bytes: int = DEFAULT_MAXIMUM_TASK_BYTES,
        backup_count: int = 5,
        recent_request_limit: int = 256,
    ) -> None:
        self.root = Path(runtime_maps_root).expanduser().resolve()
        self.maximum_task_bytes = int(maximum_task_bytes)
        self.backup_count = int(backup_count)
        self.recent_request_limit = int(recent_request_limit)
        if self.maximum_task_bytes <= 0 or self.backup_count < 0 or self.recent_request_limit <= 0:
            raise ValueError("task registry limits must be positive")
        self._recent_puts: OrderedDict[str, PutTaskResult] = OrderedDict()
        self._recent_archives: OrderedDict[str, ArchiveTaskResult] = OrderedDict()

    @staticmethod
    def safe_component(value: str, field_name: str) -> str:
        try:
            return _safe_component(value, field_name)
        except TaskGroupError as exc:
            raise TaskRegistryError(blocker("INVALID_REQUEST", str(exc))) from exc

    @staticmethod
    def valid_client_request_id(value: str) -> bool:
        return bool(value and len(value) <= 128 and SAFE_COMPONENT_RE.fullmatch(value))

    def _remember(self, cache: OrderedDict[str, Any], key: str, value: Any) -> None:
        if not key:
            return
        cache[key] = value
        cache.move_to_end(key)
        while len(cache) > self.recent_request_limit:
            cache.popitem(last=False)

    def _version_root(self, map_id: str, map_version_id: str) -> Path:
        safe_map = self.safe_component(map_id, "map_id")
        safe_version = self.safe_component(map_version_id, "map_version_id")
        candidate = self.root / safe_map / "versions" / safe_version
        resolved = candidate.resolve(strict=False)
        try:
            resolved.relative_to(self.root)
        except ValueError as exc:
            raise TaskRegistryError(
                blocker("INVALID_REQUEST", "map version path escapes runtime maps root")
            ) from exc
        return resolved

    def _manifest(self, map_id: str, map_version_id: str) -> tuple[Path, Mapping[str, Any]]:
        version_root = self._version_root(map_id, map_version_id)
        manifest_path = version_root / "manifest.yaml"
        if manifest_path.is_symlink():
            raise TaskRegistryError(blocker("MAP_NOT_READY", "manifest.yaml is a symlink"))
        try:
            manifest = yaml.safe_load(manifest_path.read_text(encoding="utf-8"))
        except FileNotFoundError as exc:
            raise TaskRegistryError(blocker("MAP_NOT_READY", "map version manifest is missing")) from exc
        except (OSError, UnicodeError, yaml.YAMLError) as exc:
            raise TaskRegistryError(blocker("MAP_NOT_READY", f"cannot read map manifest: {exc}")) from exc
        if not isinstance(manifest, Mapping):
            raise TaskRegistryError(blocker("MAP_NOT_READY", "map manifest must be a mapping"))
        if str(manifest.get("map_id", "")) != map_id or str(manifest.get("map_version_id", "")) != map_version_id:
            raise TaskRegistryError(blocker("MAP_VERSION_MISMATCH", "manifest identity does not match requested map version"))
        if str(manifest.get("state", "")).upper() != "READY":
            raise TaskRegistryError(blocker("MAP_NOT_READY", "task registry accepts only READY map versions"))
        return version_root, manifest

    def _tasks_dir(self, map_id: str, map_version_id: str, *, create: bool = False) -> Path:
        version_root, _manifest = self._manifest(map_id, map_version_id)
        tasks = version_root / "tasks"
        if tasks.is_symlink():
            raise TaskRegistryError(blocker("MAP_NOT_READY", "tasks directory is a symlink"))
        if create:
            tasks.mkdir(parents=True, exist_ok=True)
        resolved = tasks.resolve(strict=False)
        try:
            resolved.relative_to(version_root)
        except ValueError as exc:
            raise TaskRegistryError(blocker("INVALID_REQUEST", "tasks directory escapes map version root")) from exc
        return resolved

    def _task_path(self, map_id: str, map_version_id: str, task_group_id: str) -> Path:
        task_id = self.safe_component(task_group_id, "task_group_id")
        tasks = self._tasks_dir(map_id, map_version_id)
        path = tasks / f"{task_id}.json"
        if path.is_symlink():
            raise TaskRegistryError(blocker("TASK_NOT_FOUND", "task path is a symlink"))
        resolved_parent = path.parent.resolve(strict=False)
        try:
            resolved_parent.relative_to(tasks)
        except ValueError as exc:
            raise TaskRegistryError(blocker("INVALID_REQUEST", "task path escapes tasks directory")) from exc
        return path

    def _read_task_file(self, path: Path) -> str:
        if not path.is_file():
            raise TaskRegistryError(blocker("TASK_NOT_FOUND", "task JSON does not exist"))
        size = path.stat().st_size
        if size > self.maximum_task_bytes:
            raise TaskRegistryError(blocker("TASK_SCHEMA_INVALID", f"task JSON exceeds {self.maximum_task_bytes} bytes"))
        try:
            return path.read_text(encoding="utf-8")
        except (OSError, UnicodeError) as exc:
            raise TaskRegistryError(blocker("TASK_SCHEMA_INVALID", f"cannot read task JSON: {exc}")) from exc

    def _parse_task_json(self, task_json: str) -> TaskGroup:
        try:
            payload = task_json.encode("utf-8")
        except UnicodeError as exc:
            raise TaskRegistryError(blocker("TASK_SCHEMA_INVALID", f"task JSON is not UTF-8: {exc}")) from exc
        if len(payload) > self.maximum_task_bytes:
            raise TaskRegistryError(blocker("TASK_SCHEMA_INVALID", f"task JSON exceeds {self.maximum_task_bytes} bytes"))
        try:
            document = json.loads(task_json)
        except json.JSONDecodeError as exc:
            raise TaskRegistryError(blocker("TASK_SCHEMA_INVALID", f"task JSON parse failed: {exc}")) from exc
        try:
            task = TaskGroup.from_dict(document)
        except TaskGroupError as exc:
            code = "TASK_CONTENT_HASH_MISMATCH" if "content_sha256" in str(exc) else "TASK_SCHEMA_INVALID"
            raise TaskRegistryError(blocker(code, str(exc))) from exc
        if not task.content_sha256:
            raise TaskRegistryError(
                blocker("TASK_CONTENT_HASH_MISMATCH", "task JSON is missing content_sha256")
            )
        return task

    @staticmethod
    def _canonical_json(task: TaskGroup) -> str:
        return _task_payload(task).decode("utf-8")

    def list_tasks(self, map_id: str, map_version_id: str) -> list[TaskGroup]:
        tasks = self._tasks_dir(map_id, map_version_id)
        if not tasks.exists():
            return []
        result: list[TaskGroup] = []
        for path in sorted(tasks.glob("*.json")):
            if path.name == "task_index.json":
                continue
            try:
                result.append(self.get_task(map_id, map_version_id, path.stem).task)
            except TaskRegistryError:
                continue
        return result

    def get_task(
        self, map_id: str, map_version_id: str, task_group_id: str, revision: int = 0
    ) -> StoredTask:
        path = self._task_path(map_id, map_version_id, task_group_id)
        task_json = self._read_task_file(path)
        task = self._parse_task_json(task_json)
        if task.map_binding.map_id != map_id or task.map_binding.map_version_id != map_version_id:
            raise TaskRegistryError(blocker("TASK_MAP_BINDING_MISMATCH", "task map binding does not match requested map version"))
        if task.task_group_id != task_group_id:
            raise TaskRegistryError(blocker("TASK_SCHEMA_INVALID", "task_group_id does not match file name"))
        if revision and task.revision != int(revision):
            raise TaskRegistryError(blocker("TASK_REVISION_CONFLICT", f"requested revision {revision} but stored revision is {task.revision}"))
        return StoredTask(task=task, task_json=task_json, path=path)

    def resolve_task(
        self, map_id: str, map_version_id: str, task_group_id: str, revision: int
    ) -> StoredTask:
        if int(revision) <= 0:
            raise TaskRegistryError(blocker("TASK_REVISION_CONFLICT", "task_revision must be positive"))
        return self.get_task(map_id, map_version_id, task_group_id, int(revision))

    def put_task(
        self,
        task_json: str,
        *,
        map_id: str,
        map_version_id: str,
        task_group_id: str = "",
        expected_revision: int,
        client_request_id: str = "",
    ) -> PutTaskResult:
        if client_request_id:
            if not self.valid_client_request_id(client_request_id):
                raise TaskRegistryError(blocker("INVALID_REQUEST", "client_request_id contains unsafe characters"))
            cached = self._recent_puts.get(client_request_id)
            if cached is not None:
                return PutTaskResult(cached.task, cached.task_json, duplicate_request=True)
        task = self._parse_task_json(task_json)
        requested_task_id = task_group_id or task.task_group_id
        if task.task_group_id != requested_task_id:
            raise TaskRegistryError(blocker("TASK_SCHEMA_INVALID", "request task_group_id does not match task JSON"))
        if task.map_binding.map_id != map_id or task.map_binding.map_version_id != map_version_id:
            raise TaskRegistryError(blocker("TASK_MAP_BINDING_MISMATCH", "task JSON is bound to a different map version"))
        tasks = self._tasks_dir(map_id, map_version_id, create=True)
        target = tasks / f"{self.safe_component(task.task_group_id, 'task_group_id')}.json"
        if target.is_symlink():
            raise TaskRegistryError(blocker("TASK_NOT_FOUND", "task path is a symlink"))

        current_revision = 0
        current_json = b""
        if target.exists():
            current = self.get_task(map_id, map_version_id, task.task_group_id)
            current_revision = current.task.revision
            current_json = current.task_json.encode("utf-8")
            if int(expected_revision) != current_revision:
                raise TaskRegistryError(blocker("TASK_REVISION_CONFLICT", f"expected revision {expected_revision} but stored revision is {current_revision}"))
            if current_revision == task.revision and current.task.content_sha256 == task.content_sha256:
                result = PutTaskResult(current.task, current.task_json)
                self._remember(self._recent_puts, client_request_id, result)
                return result
        if int(expected_revision) != current_revision:
            raise TaskRegistryError(blocker("TASK_REVISION_CONFLICT", f"expected revision {expected_revision} but stored revision is {current_revision}"))
        if task.revision <= current_revision:
            raise TaskRegistryError(blocker("TASK_REVISION_CONFLICT", "task revision must increase monotonically"))

        payload = _task_payload(task)
        _rotate_backups(target, self.backup_count)
        try:
            _write_bytes_atomic(target, payload)
            self._write_index(map_id, map_version_id)
        except Exception as exc:
            if current_json:
                _write_bytes_atomic(target, current_json)
            else:
                target.unlink(missing_ok=True)
            raise TaskRegistryError(blocker("TASK_NOT_SYNCED", f"task write failed: {exc}")) from exc
        stored_json = payload.decode("utf-8")
        result = PutTaskResult(task, stored_json)
        self._remember(self._recent_puts, client_request_id, result)
        return result

    def archive_task(
        self,
        map_id: str,
        map_version_id: str,
        task_group_id: str,
        *,
        expected_revision: int,
        client_request_id: str = "",
    ) -> ArchiveTaskResult:
        if client_request_id:
            if not self.valid_client_request_id(client_request_id):
                raise TaskRegistryError(blocker("INVALID_REQUEST", "client_request_id contains unsafe characters"))
            cached = self._recent_archives.get(client_request_id)
            if cached is not None:
                return ArchiveTaskResult(**{**cached.__dict__, "duplicate_request": True})
        stored = self.get_task(map_id, map_version_id, task_group_id)
        if int(expected_revision) != stored.task.revision:
            raise TaskRegistryError(blocker("TASK_REVISION_CONFLICT", f"expected revision {expected_revision} but stored revision is {stored.task.revision}"))
        archive_dir = stored.path.parent / "archive"
        if archive_dir.is_symlink():
            raise TaskRegistryError(blocker("INVALID_REQUEST", "archive directory is a symlink"))
        archive_dir.mkdir(parents=True, exist_ok=True)
        archived = archive_dir / f"{stored.path.stem}.{_now_stamp()}.json"
        try:
            os.replace(stored.path, archived)
            self._write_index(map_id, map_version_id)
        except Exception as exc:
            if archived.exists():
                os.replace(archived, stored.path)
            raise TaskRegistryError(blocker("TASK_NOT_SYNCED", f"task archive failed: {exc}")) from exc
        for backup_path in stored.path.parent.glob(f"{stored.path.name}.bak.*"):
            backup_path.unlink(missing_ok=True)
        relative = archived.relative_to(self._version_root(map_id, map_version_id)).as_posix()
        result = ArchiveTaskResult(map_id, map_version_id, task_group_id, stored.task.revision, relative)
        self._remember(self._recent_archives, client_request_id, result)
        return result

    def _write_index(self, map_id: str, map_version_id: str) -> None:
        tasks_dir = self._tasks_dir(map_id, map_version_id, create=True)
        entries = []
        for task in self.list_tasks(map_id, map_version_id):
            entries.append(
                {
                    "task_group_id": task.task_group_id,
                    "name": task.name,
                    "relative_path": f"{task.task_group_id}.json",
                    "updated_at": task.updated_at,
                    "revision": task.revision,
                    "content_sha256": task.content_sha256,
                    "point_count": len(task.enabled_points),
                    "map_version_id": task.map_binding.map_version_id,
                    "validation_state": "VALID",
                }
            )
        _write_json_atomic(
            tasks_dir / "task_index.json",
            {"schema_version": 1, "map_id": map_id, "map_version_id": map_version_id, "tasks": entries},
            backup_count=self.backup_count,
        )
