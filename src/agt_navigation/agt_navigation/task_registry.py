from __future__ import annotations

from collections import OrderedDict
from dataclasses import dataclass
from datetime import datetime, timezone
import json
import os
from pathlib import Path
from typing import Any, Callable

from agt_navigation.navigation_errors import Blocker, blocker
from agt_navigation.site_task_binding import (
    SiteTaskBindingError,
    ValidatedSiteBinding,
    normalize_sha256,
)
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
SiteBindingResolver = Callable[[str, str], ValidatedSiteBinding]


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
    """Robot-side authority for mutable, versioned waypoint task JSON.

    ``tasks_root`` is deliberately separate from immutable deployed Site assets.
    The public compatibility names ``map_id`` and ``map_version_id`` identify the
    Site id/revision. Every operation resolves the current validated Site content
    identity and compares it with the task-store sidecar before reading or
    writing task data.
    """

    def __init__(
        self,
        tasks_root: str | Path,
        *,
        site_binding_resolver: SiteBindingResolver,
        maximum_task_bytes: int = DEFAULT_MAXIMUM_TASK_BYTES,
        backup_count: int = 5,
        recent_request_limit: int = 256,
    ) -> None:
        self.root = Path(tasks_root).expanduser().resolve()
        self.site_binding_resolver = site_binding_resolver
        self.maximum_task_bytes = int(maximum_task_bytes)
        self.backup_count = int(backup_count)
        self.recent_request_limit = int(recent_request_limit)
        if not callable(self.site_binding_resolver):
            raise ValueError("site_binding_resolver must be callable")
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

    def _task_version_root(self, map_id: str, map_version_id: str) -> Path:
        safe_map = self.safe_component(map_id, "map_id")
        safe_version = self.safe_component(map_version_id, "map_version_id")
        map_root = self.root / safe_map
        candidate = map_root / safe_version
        if map_root.is_symlink() or candidate.is_symlink():
            raise TaskRegistryError(
                blocker("INVALID_REQUEST", "task store identity path must not be a symlink")
            )
        resolved = candidate.resolve(strict=False)
        try:
            resolved.relative_to(self.root)
        except ValueError as exc:
            raise TaskRegistryError(
                blocker("INVALID_REQUEST", "task version path escapes tasks_root")
            ) from exc
        return resolved

    def _resolve_site_binding(self, map_id: str, map_version_id: str) -> ValidatedSiteBinding:
        try:
            binding = self.site_binding_resolver(map_id, map_version_id)
        except SiteTaskBindingError as exc:
            code = exc.code
            if code not in {"MAP_NOT_READY", "MAP_VERSION_MISMATCH"}:
                code = "TASK_SITE_BINDING_MISMATCH"
            raise TaskRegistryError(blocker(code, str(exc))) from exc
        except Exception as exc:
            raise TaskRegistryError(
                blocker("MAP_NOT_READY", f"cannot resolve validated Site binding: {exc}")
            ) from exc
        if not isinstance(binding, ValidatedSiteBinding):
            raise TaskRegistryError(
                blocker(
                    "TASK_SITE_BINDING_MISMATCH",
                    "site binding resolver returned an unsupported value",
                )
            )
        if binding.map_id != map_id or binding.map_version_id != map_version_id:
            raise TaskRegistryError(
                blocker(
                    "MAP_VERSION_MISMATCH",
                    "validated Site identity differs from requested task identity",
                )
            )
        return binding

    def _binding_path(self, version_root: Path) -> Path:
        return version_root / "site_binding.json"

    def _validate_or_write_binding(
        self,
        version_root: Path,
        binding: ValidatedSiteBinding,
        *,
        create: bool,
    ) -> None:
        binding_path = self._binding_path(version_root)
        if binding_path.is_symlink():
            raise TaskRegistryError(
                blocker("INVALID_REQUEST", "site_binding.json must not be a symlink")
            )
        if binding_path.exists():
            try:
                stored_value = json.loads(binding_path.read_text(encoding="utf-8"))
                stored = ValidatedSiteBinding.from_dict(stored_value)
            except (OSError, UnicodeError, json.JSONDecodeError, SiteTaskBindingError) as exc:
                raise TaskRegistryError(
                    blocker(
                        "TASK_SITE_BINDING_MISMATCH",
                        f"cannot validate persisted Site binding: {exc}",
                    )
                ) from exc
            if stored != binding:
                raise TaskRegistryError(
                    blocker(
                        "TASK_SITE_BINDING_MISMATCH",
                        "task store Site identity/content no longer matches deployed Site",
                    )
                )
            return
        if version_root.exists() and not create:
            raise TaskRegistryError(
                blocker(
                    "TASK_SITE_BINDING_MISMATCH",
                    "existing task version directory is missing site_binding.json",
                )
            )
        if create:
            try:
                version_root.mkdir(parents=True, exist_ok=True)
                _write_json_atomic(binding_path, binding.to_dict(), backup_count=0)
            except Exception as exc:
                raise TaskRegistryError(
                    blocker("TASK_NOT_SYNCED", f"cannot persist Site binding: {exc}")
                ) from exc

    def _context(
        self, map_id: str, map_version_id: str, *, create: bool = False
    ) -> tuple[Path, ValidatedSiteBinding]:
        version_root = self._task_version_root(map_id, map_version_id)
        binding = self._resolve_site_binding(map_id, map_version_id)
        if version_root.exists() or create:
            self._validate_or_write_binding(version_root, binding, create=create)
        return version_root, binding

    @staticmethod
    def _validate_task_site_binding(
        task: TaskGroup, binding: ValidatedSiteBinding
    ) -> None:
        if (
            task.map_binding.map_id != binding.map_id
            or task.map_binding.map_version_id != binding.map_version_id
        ):
            raise TaskRegistryError(
                blocker(
                    "TASK_MAP_BINDING_MISMATCH",
                    "task JSON is bound to a different Site revision",
                )
            )
        expected = (
            ("map_yaml_sha256", binding.navigation_yaml_sha256),
            ("map_image_sha256", binding.navigation_image_sha256),
            ("localization_pcd_sha256", binding.localization_pcd_sha256),
        )
        for field_name, expected_digest in expected:
            try:
                actual_digest = normalize_sha256(getattr(task.map_binding, field_name))
            except SiteTaskBindingError as exc:
                raise TaskRegistryError(
                    blocker(
                        "TASK_SITE_BINDING_MISMATCH",
                        f"task {field_name} is not a valid Site asset digest",
                    )
                ) from exc
            if actual_digest != expected_digest:
                raise TaskRegistryError(
                    blocker(
                        "TASK_SITE_BINDING_MISMATCH",
                        f"task {field_name} differs from the validated Site revision",
                    )
                )

    def _task_path(self, version_root: Path, task_group_id: str) -> Path:
        task_id = self.safe_component(task_group_id, "task_group_id")
        path = version_root / f"{task_id}.json"
        if path.is_symlink():
            raise TaskRegistryError(blocker("TASK_NOT_FOUND", "task path is a symlink"))
        try:
            path.parent.resolve(strict=False).relative_to(self.root)
        except ValueError as exc:
            raise TaskRegistryError(
                blocker("INVALID_REQUEST", "task path escapes tasks_root")
            ) from exc
        return path

    def _read_task_file(self, path: Path) -> str:
        if not path.is_file():
            raise TaskRegistryError(blocker("TASK_NOT_FOUND", "task JSON does not exist"))
        size = path.stat().st_size
        if size > self.maximum_task_bytes:
            raise TaskRegistryError(
                blocker(
                    "TASK_SCHEMA_INVALID",
                    f"task JSON exceeds {self.maximum_task_bytes} bytes",
                )
            )
        try:
            return path.read_text(encoding="utf-8")
        except (OSError, UnicodeError) as exc:
            raise TaskRegistryError(
                blocker("TASK_SCHEMA_INVALID", f"cannot read task JSON: {exc}")
            ) from exc

    def _parse_task_json(self, task_json: str) -> TaskGroup:
        try:
            payload = task_json.encode("utf-8")
        except UnicodeError as exc:
            raise TaskRegistryError(
                blocker("TASK_SCHEMA_INVALID", f"task JSON is not UTF-8: {exc}")
            ) from exc
        if len(payload) > self.maximum_task_bytes:
            raise TaskRegistryError(
                blocker(
                    "TASK_SCHEMA_INVALID",
                    f"task JSON exceeds {self.maximum_task_bytes} bytes",
                )
            )
        try:
            document = json.loads(task_json)
        except json.JSONDecodeError as exc:
            raise TaskRegistryError(
                blocker("TASK_SCHEMA_INVALID", f"task JSON parse failed: {exc}")
            ) from exc
        try:
            task = TaskGroup.from_dict(document)
        except TaskGroupError as exc:
            code = (
                "TASK_CONTENT_HASH_MISMATCH"
                if "content_sha256" in str(exc)
                else "TASK_SCHEMA_INVALID"
            )
            raise TaskRegistryError(blocker(code, str(exc))) from exc
        if not task.content_sha256:
            raise TaskRegistryError(
                blocker(
                    "TASK_CONTENT_HASH_MISMATCH",
                    "task JSON is missing content_sha256",
                )
            )
        return task

    @staticmethod
    def _canonical_json(task: TaskGroup) -> str:
        return _task_payload(task).decode("utf-8")

    def list_tasks(self, map_id: str, map_version_id: str) -> list[TaskGroup]:
        version_root, binding = self._context(map_id, map_version_id)
        if not version_root.exists():
            return []
        result: list[TaskGroup] = []
        for path in sorted(version_root.glob("*.json")):
            if path.name in {"task_index.json", "site_binding.json"}:
                continue
            try:
                task = self._parse_task_json(self._read_task_file(path))
                if task.task_group_id != path.stem:
                    raise TaskRegistryError(
                        blocker(
                            "TASK_SCHEMA_INVALID",
                            "task_group_id does not match file name",
                        )
                    )
                self._validate_task_site_binding(task, binding)
                result.append(task)
            except TaskRegistryError:
                continue
        return result

    def get_task(
        self, map_id: str, map_version_id: str, task_group_id: str, revision: int = 0
    ) -> StoredTask:
        version_root, binding = self._context(map_id, map_version_id)
        path = self._task_path(version_root, task_group_id)
        task_json = self._read_task_file(path)
        task = self._parse_task_json(task_json)
        self._validate_task_site_binding(task, binding)
        if task.task_group_id != task_group_id:
            raise TaskRegistryError(
                blocker("TASK_SCHEMA_INVALID", "task_group_id does not match file name")
            )
        if revision and task.revision != int(revision):
            raise TaskRegistryError(
                blocker(
                    "TASK_REVISION_CONFLICT",
                    f"requested revision {revision} but stored revision is {task.revision}",
                )
            )
        return StoredTask(task=task, task_json=task_json, path=path)

    def resolve_task(
        self, map_id: str, map_version_id: str, task_group_id: str, revision: int
    ) -> StoredTask:
        if int(revision) <= 0:
            raise TaskRegistryError(
                blocker("TASK_REVISION_CONFLICT", "task_revision must be positive")
            )
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
        if client_request_id and not self.valid_client_request_id(client_request_id):
            raise TaskRegistryError(
                blocker("INVALID_REQUEST", "client_request_id contains unsafe characters")
            )
        version_root, binding = self._context(map_id, map_version_id, create=True)
        if client_request_id:
            cached = self._recent_puts.get(client_request_id)
            if cached is not None:
                self._validate_task_site_binding(cached.task, binding)
                return PutTaskResult(cached.task, cached.task_json, duplicate_request=True)

        task = self._parse_task_json(task_json)
        requested_task_id = task_group_id or task.task_group_id
        if task.task_group_id != requested_task_id:
            raise TaskRegistryError(
                blocker(
                    "TASK_SCHEMA_INVALID",
                    "request task_group_id does not match task JSON",
                )
            )
        self._validate_task_site_binding(task, binding)
        target = self._task_path(version_root, task.task_group_id)

        current_revision = 0
        current_json = b""
        if target.exists():
            current = self.get_task(map_id, map_version_id, task.task_group_id)
            current_revision = current.task.revision
            current_json = current.task_json.encode("utf-8")
            if int(expected_revision) != current_revision:
                raise TaskRegistryError(
                    blocker(
                        "TASK_REVISION_CONFLICT",
                        f"expected revision {expected_revision} but stored revision is {current_revision}",
                    )
                )
            if current_revision == task.revision and current.task.content_sha256 == task.content_sha256:
                result = PutTaskResult(current.task, current.task_json)
                self._remember(self._recent_puts, client_request_id, result)
                return result
        if int(expected_revision) != current_revision:
            raise TaskRegistryError(
                blocker(
                    "TASK_REVISION_CONFLICT",
                    f"expected revision {expected_revision} but stored revision is {current_revision}",
                )
            )
        if task.revision <= current_revision:
            raise TaskRegistryError(
                blocker(
                    "TASK_REVISION_CONFLICT", "task revision must increase monotonically"
                )
            )

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
            raise TaskRegistryError(
                blocker("TASK_NOT_SYNCED", f"task write failed: {exc}")
            ) from exc
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
        if client_request_id and not self.valid_client_request_id(client_request_id):
            raise TaskRegistryError(
                blocker("INVALID_REQUEST", "client_request_id contains unsafe characters")
            )
        version_root, _binding = self._context(map_id, map_version_id)
        if client_request_id:
            cached = self._recent_archives.get(client_request_id)
            if cached is not None:
                return ArchiveTaskResult(
                    **{**cached.__dict__, "duplicate_request": True}
                )
        stored = self.get_task(map_id, map_version_id, task_group_id)
        if int(expected_revision) != stored.task.revision:
            raise TaskRegistryError(
                blocker(
                    "TASK_REVISION_CONFLICT",
                    f"expected revision {expected_revision} but stored revision is {stored.task.revision}",
                )
            )
        archive_dir = version_root / "archive"
        if archive_dir.is_symlink():
            raise TaskRegistryError(
                blocker("INVALID_REQUEST", "archive directory is a symlink")
            )
        archive_dir.mkdir(parents=True, exist_ok=True)
        archived = archive_dir / f"{stored.path.stem}.{_now_stamp()}.json"
        try:
            os.replace(stored.path, archived)
            self._write_index(map_id, map_version_id)
        except Exception as exc:
            if archived.exists():
                os.replace(archived, stored.path)
            raise TaskRegistryError(
                blocker("TASK_NOT_SYNCED", f"task archive failed: {exc}")
            ) from exc
        for backup_path in version_root.glob(f"{stored.path.name}.bak.*"):
            backup_path.unlink(missing_ok=True)
        relative = archived.relative_to(version_root).as_posix()
        result = ArchiveTaskResult(
            map_id,
            map_version_id,
            task_group_id,
            stored.task.revision,
            relative,
        )
        self._remember(self._recent_archives, client_request_id, result)
        return result

    def _write_index(self, map_id: str, map_version_id: str) -> None:
        version_root, _binding = self._context(map_id, map_version_id, create=True)
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
            version_root / "task_index.json",
            {
                "schema_version": 1,
                "map_id": map_id,
                "map_version_id": map_version_id,
                "site_binding": _binding.to_dict(),
                "tasks": entries,
            },
            backup_count=self.backup_count,
        )
