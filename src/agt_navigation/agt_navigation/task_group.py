"""Versioned offline waypoint task groups and their map-bound validation.

This module deliberately has no ROS or Qt dependency.  It is the portable
contract used by the project Action server and by headless tooling; the Qt
frontend implements the same JSON contract in C++.
"""

from __future__ import annotations

from dataclasses import dataclass, field
import copy
from datetime import datetime, timezone
import hashlib
import json
import math
import os
from pathlib import Path
import re
import shutil
import tempfile

import yaml


SCHEMA_VERSION = 1
MAP_FRAME = "map"
DEFAULT_MAXIMUM_POINTS = 200
DEFAULT_MAXIMUM_LOOPS = 10
UNKNOWN_POLICIES = {"reject", "warn", "allow"}
SAFE_COMPONENT_RE = re.compile(r"^[A-Za-z0-9._-]+$")
TASK_GROUP_KEYS = {
    "schema_version", "task_group_id", "name", "description", "created_at",
    "updated_at", "revision", "content_sha256", "frame_id", "map_binding",
    "execution", "points",
}
MAP_BINDING_KEYS = {
    "map_id", "map_version_id", "map_yaml_path", "map_yaml_sha256",
    "map_image_sha256", "localization_pcd_sha256", "resolution", "width",
    "height", "origin",
}
WAYPOINT_KEYS = {"id", "name", "x", "y", "yaw", "enabled", "note"}


class TaskGroupError(ValueError):
    """Raised when a task group cannot be safely loaded or saved."""


@dataclass(frozen=True)
class Waypoint:
    id: str
    name: str
    x: float
    y: float
    yaw: float
    enabled: bool = True
    note: str = ""

    @property
    def theta(self) -> float:
        """Legacy name used by the old Qt task-chain adapter."""
        return self.yaw


@dataclass(frozen=True)
class MapBinding:
    map_id: str
    map_version_id: str
    map_yaml_path: str = ""
    map_yaml_sha256: str = ""
    map_image_sha256: str = ""
    localization_pcd_sha256: str = ""
    resolution: float = 0.0
    width: int = 0
    height: int = 0
    origin: tuple[float, float, float] = (0.0, 0.0, 0.0)

    @classmethod
    def from_dict(cls, value: object) -> "MapBinding":
        if not isinstance(value, dict):
            raise TaskGroupError("map_binding must be an object")
        _require_keys(value, MAP_BINDING_KEYS, MAP_BINDING_KEYS, "map_binding")
        origin = value.get("origin", [0.0, 0.0, 0.0])
        if not isinstance(origin, (list, tuple)) or len(origin) != 3:
            raise TaskGroupError("map_binding.origin must contain x, y, and yaw")
        if any(isinstance(item, bool) or not isinstance(item, (int, float)) for item in origin):
            raise TaskGroupError("map_binding.origin must contain numeric values")
        resolution = value.get("resolution")
        width = value.get("width")
        height = value.get("height")
        if isinstance(resolution, bool) or not isinstance(resolution, (int, float)):
            raise TaskGroupError("map_binding.resolution must be numeric")
        if isinstance(width, bool) or not isinstance(width, int):
            raise TaskGroupError("map_binding.width must be an integer")
        if isinstance(height, bool) or not isinstance(height, int):
            raise TaskGroupError("map_binding.height must be an integer")
        try:
            return cls(
                map_id=_required_text(value, "map_id"),
                map_version_id=_required_text(value, "map_version_id"),
                map_yaml_path=_required_string(value, "map_yaml_path"),
                map_yaml_sha256=_required_string(value, "map_yaml_sha256"),
                map_image_sha256=_required_string(value, "map_image_sha256"),
                localization_pcd_sha256=_required_string(
                    value, "localization_pcd_sha256"
                ),
                resolution=float(resolution),
                width=width,
                height=height,
                origin=tuple(float(item) for item in origin),
            )
        except TaskGroupError:
            raise
        except (TypeError, ValueError) as exc:
            raise TaskGroupError("map_binding contains an invalid numeric field") from exc

    def to_dict(self) -> dict:
        return {
            "map_id": self.map_id,
            "map_version_id": self.map_version_id,
            "map_yaml_path": self.map_yaml_path,
            "map_yaml_sha256": self.map_yaml_sha256,
            "map_image_sha256": self.map_image_sha256,
            "localization_pcd_sha256": self.localization_pcd_sha256,
            "resolution": self.resolution,
            "width": self.width,
            "height": self.height,
            "origin": list(self.origin),
        }


@dataclass
class TaskGroup:
    task_group_id: str
    name: str
    description: str
    created_at: str
    updated_at: str
    map_binding: MapBinding
    points: list[Waypoint] = field(default_factory=list)
    frame_id: str = MAP_FRAME
    loop: bool = False
    loop_count: int = 1
    revision: int = 1
    content_sha256: str = ""

    @classmethod
    def from_dict(cls, value: object, *, allow_legacy: bool = False) -> "TaskGroup":
        if not isinstance(value, dict):
            raise TaskGroupError("task JSON must contain an object")
        if "schema_version" not in value:
            if allow_legacy and isinstance(value.get("points"), list):
                raise TaskGroupError("legacy points JSON needs an explicit map binding")
            raise TaskGroupError("task group is missing schema_version")
        if value.get("schema_version") != SCHEMA_VERSION:
            raise TaskGroupError(
                f"unsupported task group schema_version: {value.get('schema_version')}"
            )
        _require_keys(
            value,
            TASK_GROUP_KEYS,
            {
                "schema_version", "task_group_id", "name", "description",
                "created_at", "updated_at", "frame_id", "map_binding",
                "execution", "points",
            },
            "task group",
        )
        execution = value.get("execution", {})
        if not isinstance(execution, dict):
            raise TaskGroupError("execution must be an object")
        _require_keys(execution, {"loop", "loop_count"}, {"loop", "loop_count"}, "execution")
        loop_value = execution.get("loop", False)
        loop_count_value = execution.get("loop_count", 1)
        if not isinstance(loop_value, bool) or not isinstance(loop_count_value, int) or isinstance(loop_count_value, bool):
            raise TaskGroupError("execution.loop must be boolean and loop_count must be an integer")
        revision_value = value.get("revision", 1)
        if not isinstance(revision_value, int) or isinstance(revision_value, bool):
            raise TaskGroupError("revision must be an integer")
        raw_points = value.get("points")
        if not isinstance(raw_points, list):
            raise TaskGroupError("task group must contain a points array")
        points = [_waypoint_from_dict(item, index) for index, item in enumerate(raw_points)]
        try:
            task = cls(
                task_group_id=_required_text(value, "task_group_id"),
                name=_required_text(value, "name"),
                description=_required_string(value, "description"),
                created_at=_required_text(value, "created_at"),
                updated_at=_required_text(value, "updated_at"),
                frame_id=_required_string(value, "frame_id"),
                map_binding=MapBinding.from_dict(value.get("map_binding")),
                loop=loop_value,
                loop_count=loop_count_value,
                points=points,
                revision=revision_value,
                content_sha256=_optional_string(value, "content_sha256"),
            )
        except TypeError as exc:
            raise TaskGroupError("task group contains an invalid field") from exc
        task.validate()
        if task.content_sha256 and task.content_sha256 != task.canonical_hash():
            raise TaskGroupError("task group content_sha256 does not match its content")
        return task

    @classmethod
    def from_json(cls, path: str | Path) -> "TaskGroup":
        path = Path(path)
        try:
            value = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, UnicodeError, json.JSONDecodeError) as exc:
            raise TaskGroupError(f"cannot read task group JSON: {exc}") from exc
        return cls.from_dict(value)

    @property
    def execution_loop(self) -> bool:
        return self.loop

    @execution_loop.setter
    def execution_loop(self, value: bool) -> None:
        self.loop = value

    @property
    def enabled_points(self) -> list[Waypoint]:
        return [point for point in self.points if point.enabled]

    def validate(
        self,
        *,
        maximum_points: int = DEFAULT_MAXIMUM_POINTS,
        maximum_loops: int = DEFAULT_MAXIMUM_LOOPS,
    ) -> None:
        if self.frame_id != MAP_FRAME:
            raise TaskGroupError("frame_id must be map")
        if not self.task_group_id.strip() or not self.name.strip():
            raise TaskGroupError("task_group_id and name must not be empty")
        if not SAFE_COMPONENT_RE.fullmatch(self.task_group_id):
            raise TaskGroupError("task_group_id contains an unsafe character")
        if self.revision <= 0:
            raise TaskGroupError("revision must be a positive integer")
        if not self.points:
            raise TaskGroupError("task group contains no waypoints")
        if len(self.points) > maximum_points:
            raise TaskGroupError(
                f"task contains {len(self.points)} waypoints; limit is {maximum_points}"
            )
        if self.loop_count <= 0 or self.loop_count > maximum_loops:
            raise TaskGroupError(
                f"loop_count must be in 1..{maximum_loops}; got {self.loop_count}"
            )
        if not self.enabled_points:
            raise TaskGroupError("task group must contain at least one enabled waypoint")
        seen_ids: set[str] = set()
        for index, point in enumerate(self.points):
            if not point.id.strip() or not SAFE_COMPONENT_RE.fullmatch(point.id) or point.id in seen_ids:
                raise TaskGroupError(f"waypoint {index} has a duplicate or empty id")
            seen_ids.add(point.id)
            if not point.name.strip():
                raise TaskGroupError(f"waypoint {index} has no valid name")
            if not all(math.isfinite(value) for value in (point.x, point.y, point.yaw)):
                raise TaskGroupError(f"waypoint {index} contains a non-finite coordinate")
            if index and _same_pose(self.points[index - 1], point):
                raise TaskGroupError(f"waypoint {index} duplicates the preceding waypoint")
        if _has_repeated_whole_pattern(self.enabled_points):
            raise TaskGroupError(
                "task is an exact repeated pattern; save it to a new file because "
                "the vendor GUI may have appended an earlier chain"
            )
        _validate_map_binding(self.map_binding)

    def to_dict(self, *, include_content_hash: bool = True) -> dict:
        value = {
            "schema_version": SCHEMA_VERSION,
            "task_group_id": self.task_group_id,
            "name": self.name,
            "description": self.description,
            "created_at": self.created_at,
            "updated_at": self.updated_at,
            "revision": self.revision,
            "frame_id": self.frame_id,
            "map_binding": self.map_binding.to_dict(),
            "execution": {"loop": self.loop, "loop_count": self.loop_count},
            "points": [
                {
                    "id": point.id,
                    "name": point.name,
                    "x": point.x,
                    "y": point.y,
                    "yaw": normalize_yaw(point.yaw),
                    "enabled": point.enabled,
                    "note": point.note,
                }
                for point in self.points
            ],
        }
        if include_content_hash and self.content_sha256:
            value["content_sha256"] = self.content_sha256
        return value

    def canonical_hash(self) -> str:
        payload = json.dumps(
            self.to_dict(include_content_hash=False),
            ensure_ascii=False,
            sort_keys=True,
            separators=(",", ":"),
        ).encode("utf-8")
        return "sha256:" + hashlib.sha256(payload).hexdigest()

    def to_legacy_dict(self) -> dict:
        return {
            "points": [
                {
                    "name": point.name,
                    "x": point.x,
                    "y": point.y,
                    "theta": normalize_yaw(point.yaw),
                }
                for point in self.enabled_points
            ]
        }


@dataclass(frozen=True)
class MapSnapshot:
    map_id: str
    map_version_id: str
    yaml_path: Path
    image_path: Path
    resolution: float
    width: int
    height: int
    origin: tuple[float, float, float]
    map_yaml_sha256: str
    map_image_sha256: str
    localization_pcd_sha256: str = ""
    version_root: Path | None = None

    def binding(self) -> MapBinding:
        return MapBinding(
            map_id=self.map_id,
            map_version_id=self.map_version_id,
            map_yaml_path=_relative_path(self.yaml_path, self.version_root),
            map_yaml_sha256=self.map_yaml_sha256,
            map_image_sha256=self.map_image_sha256,
            localization_pcd_sha256=self.localization_pcd_sha256,
            resolution=self.resolution,
            width=self.width,
            height=self.height,
            origin=self.origin,
        )


@dataclass(frozen=True)
class TaskValidationReport:
    errors: tuple[str, ...] = ()
    warnings: tuple[str, ...] = ()
    binding_state: str = "UNVERIFIED"

    @property
    def ok(self) -> bool:
        return not self.errors


class TaskRepository:
    """Persist task groups below one immutable map version directory."""

    def __init__(self, runtime_maps_root: str | Path, map_id: str, map_version_id: str):
        self.root = Path(runtime_maps_root).expanduser().resolve()
        self.map_id = _safe_component(map_id, "map_id")
        self.map_version_id = _safe_component(map_version_id, "map_version_id")
        self.directory = self.root / self.map_id / "versions" / self.map_version_id / "tasks"

    def list_tasks(self) -> list[dict]:
        entries = []
        for path in sorted(self.directory.glob("*.json")):
            if path.name == "task_index.json":
                continue
            try:
                task = TaskGroup.from_json(path)
            except TaskGroupError as exc:
                entries.append(
                    {
                        "task_group_id": path.stem,
                        "name": path.stem,
                        "relative_path": path.name,
                        "updated_at": "",
                        "point_count": 0,
                        "map_version_id": self.map_version_id,
                        "validation_state": "INVALID",
                        "validation_error": str(exc),
                    }
                )
                continue
            entries.append(self._index_entry(path, task, "VALID"))
        return entries

    def load(self, task_group_id: str) -> TaskGroup:
        path = self.path_for(task_group_id)
        return TaskGroup.from_json(path)

    def path_for(self, task_group_id: str) -> Path:
        component = _safe_component(task_group_id, "task_group_id")
        return self.directory / f"{component}.json"

    def save(self, task: TaskGroup, *, backup_count: int = 5) -> Path:
        task.validate()
        if task.map_binding.map_id != self.map_id or task.map_binding.map_version_id != self.map_version_id:
            raise TaskGroupError("task map binding does not match repository map version")
        self.directory.mkdir(parents=True, exist_ok=True)
        target = self.path_for(task.task_group_id)
        existed = target.exists()
        candidate = copy.deepcopy(task)
        candidate.updated_at = _now_iso()
        candidate.revision = (
            max(1, candidate.revision + 1)
            if existed
            else max(1, candidate.revision)
        )
        candidate.content_sha256 = candidate.canonical_hash()
        previous = target.read_bytes() if target.exists() else None
        _rotate_backups(target, backup_count)
        try:
            _write_json_atomic(target, candidate.to_dict(), backup_count=0)
            self._write_index_atomic()
        except Exception as exc:
            # A task file and its index are one logical repository update. If
            # the index replacement fails, restore the task file so a stale
            # index cannot point at a newer, partially committed task.
            try:
                if previous is None:
                    target.unlink(missing_ok=True)
                else:
                    _write_bytes_atomic(target, previous)
            except Exception as restore_exc:
                raise TaskGroupError(
                    f"task repository update failed and restore failed: {restore_exc}"
                ) from exc
            raise TaskGroupError(f"task repository update failed: {exc}") from exc
        task.updated_at = candidate.updated_at
        task.revision = candidate.revision
        task.content_sha256 = candidate.content_sha256
        return target

    def copy(self, source_id: str, destination_id: str) -> TaskGroup:
        destination = self.path_for(destination_id)
        if destination.exists():
            raise TaskGroupError("destination task_group_id already exists")
        source = self.load(source_id)
        source.task_group_id = _safe_component(destination_id, "task_group_id")
        source.name = f"{source.name} copy"
        source.revision = 1
        source.content_sha256 = ""
        self.save(source)
        return source

    def archive(self, task_group_id: str) -> Path:
        target = self.path_for(task_group_id)
        if not target.is_file():
            raise TaskGroupError("task file does not exist")
        archive_directory = self.directory / "archive"
        archive_directory.mkdir(parents=True, exist_ok=True)
        suffix = datetime.now(timezone.utc).strftime("%Y%m%d_%H%M%S_%f")
        archived = archive_directory / f"{target.stem}.{suffix}.json"
        try:
            os.replace(target, archived)
            self._write_index_atomic()
        except Exception as exc:
            try:
                if archived.exists():
                    os.replace(archived, target)
            except OSError as restore_exc:
                raise TaskGroupError(
                    f"task archive failed and restore failed: {restore_exc}"
                ) from exc
            raise TaskGroupError(f"task archive failed: {exc}") from exc
        for backup in self.directory.glob(f"{target.name}.bak.*"):
            backup.unlink(missing_ok=True)
        return archived

    def import_legacy(
        self,
        source_path: str | Path,
        *,
        task_group_id: str,
        name: str,
        map_binding: MapBinding,
    ) -> TaskGroup:
        task_group_id = _safe_component(task_group_id, "task_group_id")
        if self.path_for(task_group_id).exists():
            raise TaskGroupError("destination task_group_id already exists")
        source = Path(source_path)
        try:
            value = json.loads(source.read_text(encoding="utf-8"))
        except (OSError, UnicodeError, json.JSONDecodeError) as exc:
            raise TaskGroupError(f"cannot read legacy task JSON: {exc}") from exc
        raw_points = value.get("points") if isinstance(value, dict) else None
        if not isinstance(raw_points, list) or not raw_points:
            raise TaskGroupError("legacy task JSON must contain a non-empty points array")
        points = []
        for index, raw in enumerate(raw_points):
            if not isinstance(raw, dict):
                raise TaskGroupError(f"legacy waypoint {index} must be an object")
            try:
                x = float(raw["x"])
                y = float(raw["y"])
                yaw = float(raw.get("theta", raw.get("yaw")))
            except (KeyError, TypeError, ValueError) as exc:
                raise TaskGroupError(f"legacy waypoint {index} has invalid x/y/theta") from exc
            points.append(
                Waypoint(
                    id=f"wp_{index + 1:04d}",
                    name=str(raw.get("name", f"Waypoint {index + 1}")).strip(),
                    x=x,
                    y=y,
                    yaw=normalize_yaw(yaw),
                    enabled=bool(raw.get("enabled", True)),
                    note=str(raw.get("note", "")),
                )
            )
        now = _now_iso()
        task = TaskGroup(
            task_group_id=task_group_id,
            name=name.strip(),
            description="Imported from legacy Qt points JSON",
            created_at=now,
            updated_at=now,
            map_binding=map_binding,
            points=points,
        )
        task.validate()
        return task

    def export_legacy(self, task: TaskGroup, destination: str | Path) -> Path:
        task.validate()
        destination = Path(destination)
        _write_json_atomic(destination, task.to_legacy_dict(), backup_count=0)
        return destination

    def _index_entry(self, path: Path, task: TaskGroup, state: str) -> dict:
        return {
            "task_group_id": task.task_group_id,
            "name": task.name,
            "relative_path": path.name,
            "updated_at": task.updated_at,
            "point_count": len(task.enabled_points),
            "map_version_id": task.map_binding.map_version_id,
            "validation_state": state,
        }

    def _write_index_atomic(self) -> None:
        index = {"schema_version": 1, "map_id": self.map_id, "map_version_id": self.map_version_id, "tasks": self.list_tasks()}
        _write_json_atomic(self.directory / "task_index.json", index, backup_count=5)


def load_task_group(
    path: str | Path,
    *,
    maximum_points: int = DEFAULT_MAXIMUM_POINTS,
    maximum_loops: int = DEFAULT_MAXIMUM_LOOPS,
) -> TaskGroup:
    task = TaskGroup.from_json(path)
    task.validate(maximum_points=maximum_points, maximum_loops=maximum_loops)
    return task


def load_qt_task_chain(path: str | Path, *, maximum_points: int = DEFAULT_MAXIMUM_POINTS) -> list[Waypoint]:
    """Load either schema v1 or the legacy Qt ``points/theta`` document."""
    task_path = Path(path).expanduser()
    if not task_path.is_absolute():
        raise TaskGroupError("task_file must be an absolute path")
    try:
        document = json.loads(task_path.read_text(encoding="utf-8"))
    except (OSError, UnicodeError, json.JSONDecodeError) as exc:
        raise TaskGroupError(f"cannot read task JSON: {exc}") from exc
    if isinstance(document, dict) and document.get("schema_version") == SCHEMA_VERSION:
        task = TaskGroup.from_dict(document)
        task.validate(maximum_points=maximum_points)
        return task.enabled_points
    return _load_legacy_points(document, maximum_points=maximum_points)


def compare_map_binding(binding: MapBinding, current: MapBinding) -> str:
    geometry_fields = ("resolution", "width", "height", "origin")
    for field_name in geometry_fields:
        expected = getattr(binding, field_name)
        actual = getattr(current, field_name)
        if field_name == "resolution":
            if not math.isclose(expected, actual, rel_tol=0.0, abs_tol=1.0e-9):
                return "GEOMETRY_MISMATCH"
        elif field_name == "origin":
            if any(not math.isclose(a, b, rel_tol=0.0, abs_tol=1.0e-9) for a, b in zip(expected, actual)):
                return "GEOMETRY_MISMATCH"
        elif expected != actual:
            return "GEOMETRY_MISMATCH"
    content_fields = (
        "map_id",
        "map_version_id",
        "map_yaml_sha256",
        "map_image_sha256",
        "localization_pcd_sha256",
    )
    return "MATCHED" if all(getattr(binding, item) == getattr(current, item) for item in content_fields) else "CONTENT_CHANGED"


def validate_task_group(
    task: TaskGroup,
    *,
    snapshot: MapSnapshot | None = None,
    unknown_cell_policy: str = "reject",
    line_check_step_ratio: float = 0.5,
    maximum_points: int = DEFAULT_MAXIMUM_POINTS,
    maximum_loops: int = DEFAULT_MAXIMUM_LOOPS,
) -> TaskValidationReport:
    errors: list[str] = []
    warnings: list[str] = []
    try:
        task.validate(maximum_points=maximum_points, maximum_loops=maximum_loops)
    except TaskGroupError as exc:
        errors.append(str(exc))
    if unknown_cell_policy not in UNKNOWN_POLICIES:
        errors.append(f"unknown_cell_policy must be one of {sorted(UNKNOWN_POLICIES)}")
    if not math.isfinite(line_check_step_ratio) or line_check_step_ratio <= 0.0:
        errors.append("line_check_step_ratio must be positive")
    binding_state = "UNVERIFIED"
    raster = None
    if snapshot is not None:
        binding_state = compare_map_binding(task.map_binding, snapshot.binding())
        if binding_state == "GEOMETRY_MISMATCH":
            errors.append("task map binding has a geometry mismatch")
        elif binding_state == "CONTENT_CHANGED":
            warnings.append(
                "task map identity or content changed; revalidate and explicitly rebind before execution"
            )
        try:
            raster = _load_map_raster(snapshot)
        except TaskGroupError as exc:
            errors.append(str(exc))
    for index, point in enumerate(task.enabled_points):
        if raster is None:
            continue
        cell = raster.world_to_grid(point.x, point.y)
        if cell is None:
            errors.append(f"waypoint {point.id} is outside the map")
            continue
        cell_state = raster.cell_state(*cell)
        if cell_state == "occupied":
            errors.append(f"waypoint {point.id} is on an occupied cell")
        elif cell_state == "unknown":
            message = f"waypoint {point.id} is on an unknown cell"
            if unknown_cell_policy == "reject":
                errors.append(message)
            elif unknown_cell_policy == "warn":
                warnings.append(message)
        if index == 0:
            continue
        previous = task.enabled_points[index - 1]
        length = math.hypot(point.x - previous.x, point.y - previous.y)
        steps = max(1, math.ceil(length / (raster.resolution * line_check_step_ratio)))
        for step in range(steps + 1):
            ratio = step / steps
            x = previous.x + ratio * (point.x - previous.x)
            y = previous.y + ratio * (point.y - previous.y)
            segment_cell = raster.world_to_grid(x, y)
            if segment_cell is None:
                errors.append(f"path segment {previous.id}->{point.id} leaves the map")
                break
            segment_state = raster.cell_state(*segment_cell)
            if segment_state == "occupied":
                errors.append(f"path segment {previous.id}->{point.id} crosses an occupied cell")
                break
            if segment_state == "unknown":
                message = f"path segment {previous.id}->{point.id} crosses an unknown cell"
                if unknown_cell_policy == "reject":
                    errors.append(message)
                    break
                if unknown_cell_policy == "warn":
                    warnings.append(message)
                    break
    return TaskValidationReport(tuple(dict.fromkeys(errors)), tuple(dict.fromkeys(warnings)), binding_state)


@dataclass(frozen=True)
class _MapRaster:
    pixels: bytes
    width: int
    height: int
    resolution: float
    origin: tuple[float, float, float]
    negate: bool
    occupied_thresh: float
    free_thresh: float

    def world_to_grid(self, x: float, y: float) -> tuple[int, int] | None:
        dx = x - self.origin[0]
        dy = y - self.origin[1]
        cos_yaw = math.cos(self.origin[2])
        sin_yaw = math.sin(self.origin[2])
        local_x = cos_yaw * dx + sin_yaw * dy
        local_y = -sin_yaw * dx + cos_yaw * dy
        grid_x = math.floor(local_x / self.resolution)
        grid_y = math.floor(local_y / self.resolution)
        if not (0 <= grid_x < self.width and 0 <= grid_y < self.height):
            return None
        return grid_x, grid_y

    def cell_state(self, grid_x: int, grid_y: int) -> str:
        image_y = self.height - 1 - grid_y
        pixel = self.pixels[image_y * self.width + grid_x] / 255.0
        occupied = 1.0 - pixel if not self.negate else pixel
        if occupied >= self.occupied_thresh:
            return "occupied"
        if occupied <= self.free_thresh:
            return "free"
        return "unknown"


def load_map_snapshot(
    map_yaml_path: str | Path,
    *,
    map_id: str,
    map_version_id: str,
    localization_pcd_path: str | Path | None = None,
    version_root: str | Path | None = None,
) -> MapSnapshot:
    yaml_path = Path(map_yaml_path).expanduser().resolve()
    try:
        metadata = yaml.safe_load(yaml_path.read_text(encoding="utf-8"))
    except (OSError, UnicodeError, yaml.YAMLError) as exc:
        raise TaskGroupError(f"cannot read map YAML: {exc}") from exc
    if not isinstance(metadata, dict):
        raise TaskGroupError("map YAML must contain an object")
    image_value = metadata.get("image")
    if not isinstance(image_value, str) or not image_value:
        raise TaskGroupError("map YAML image is missing")
    image_path = Path(image_value)
    if not image_path.is_absolute():
        image_path = yaml_path.parent / image_path
    image_path = image_path.resolve()
    pixels, width, height = _read_raster(image_path)
    origin = metadata.get("origin", [0.0, 0.0, 0.0])
    if not isinstance(origin, list) or len(origin) != 3:
        raise TaskGroupError("map YAML origin must contain x, y, and yaw")
    try:
        resolution = float(metadata["resolution"])
        origin_tuple = tuple(float(item) for item in origin)
    except TaskGroupError:
        raise
    except (KeyError, TypeError, ValueError) as exc:
        raise TaskGroupError("map YAML contains invalid resolution or origin") from exc
    if resolution <= 0.0 or not all(math.isfinite(item) for item in origin_tuple):
        raise TaskGroupError("map YAML resolution and origin must be finite and positive")
    resolved_version_root = (
        Path(version_root).expanduser().resolve() if version_root is not None else None
    )
    if resolved_version_root is None and yaml_path.parent.name == "navigation":
        candidate = yaml_path.parent.parent
        if (candidate / "manifest.yaml").is_file():
            resolved_version_root = candidate
    pcd_hash = ""
    if localization_pcd_path is not None:
        pcd_hash = _sha256_file(Path(localization_pcd_path).expanduser().resolve())
    elif resolved_version_root is not None:
        pcd_hash = _pcd_hash_from_manifest(resolved_version_root)
    return MapSnapshot(
        map_id=map_id,
        map_version_id=map_version_id,
        yaml_path=yaml_path,
        image_path=image_path,
        resolution=resolution,
        width=width,
        height=height,
        origin=origin_tuple,
        map_yaml_sha256=_sha256_file(yaml_path),
        map_image_sha256=_sha256_file(image_path),
        localization_pcd_sha256=pcd_hash,
        version_root=resolved_version_root,
    )


def _waypoint_from_dict(value: object, index: int) -> Waypoint:
    if not isinstance(value, dict):
        raise TaskGroupError(f"waypoint {index} must be an object")
    _require_keys(value, WAYPOINT_KEYS, WAYPOINT_KEYS, f"waypoint {index}")
    try:
        yaw_value = value["yaw"]
        return Waypoint(
            id=_required_text(value, "id"),
            name=_required_text(value, "name"),
            x=float(value["x"]),
            y=float(value["y"]),
            yaw=normalize_yaw(float(yaw_value)),
            enabled=_strict_bool(value.get("enabled", True), f"waypoint {index} enabled"),
            note=_required_string(value, "note"),
        )
    except TaskGroupError:
        raise
    except (KeyError, TypeError, ValueError) as exc:
        raise TaskGroupError(f"waypoint {index} has invalid id/name/x/y/yaw") from exc


def _load_legacy_points(value: object, *, maximum_points: int) -> list[Waypoint]:
    if not isinstance(value, dict) or not isinstance(value.get("points"), list):
        raise TaskGroupError("task JSON must contain a points array")
    raw_points = value["points"]
    if not raw_points:
        raise TaskGroupError("task contains no waypoints")
    if len(raw_points) > maximum_points:
        raise TaskGroupError(f"task contains {len(raw_points)} waypoints; limit is {maximum_points}")
    points = []
    for index, raw in enumerate(raw_points):
        if not isinstance(raw, dict):
            raise TaskGroupError(f"waypoint {index} must be an object")
        try:
            point = Waypoint(
            id=str(raw.get("id", f"wp_{index + 1:04d}")),
                name=_required_text(raw, "name"),
                x=float(raw["x"]),
                y=float(raw["y"]),
                yaw=normalize_yaw(float(raw["theta"] if "theta" in raw else raw["yaw"])),
                enabled=bool(raw.get("enabled", True)),
                note=str(raw.get("note", "")),
            )
        except (KeyError, TypeError, ValueError) as exc:
            raise TaskGroupError(f"waypoint {index} has invalid x/y/theta") from exc
        if not all(math.isfinite(item) for item in (point.x, point.y, point.yaw)):
            raise TaskGroupError(f"waypoint {index} contains a non-finite coordinate")
        if points and _same_pose(points[-1], point):
            raise TaskGroupError(f"waypoint {index} duplicates the preceding waypoint")
        points.append(point)
    if _has_repeated_whole_pattern(points):
        raise TaskGroupError(
            "task is an exact repeated pattern; save it to a new file because the vendor GUI may have appended an earlier chain"
        )
    return points


def normalize_yaw(value: float) -> float:
    if not math.isfinite(value):
        raise TaskGroupError("yaw must be finite")
    return (value + math.pi) % (2.0 * math.pi) - math.pi


def _has_repeated_whole_pattern(points: list[Waypoint]) -> bool:
    count = len(points)
    if count < 2:
        return False
    signatures = [(p.name, p.x, p.y, normalize_yaw(p.yaw)) for p in points]
    for period in range(1, count // 2 + 1):
        if count % period == 0 and signatures == signatures[:period] * (count // period):
            return True
    return False


def _same_pose(first: Waypoint, second: Waypoint) -> bool:
    return first.x == second.x and first.y == second.y and normalize_yaw(first.yaw) == normalize_yaw(second.yaw)


def _validate_map_binding(binding: MapBinding) -> None:
    if not binding.map_id.strip() or not binding.map_version_id.strip():
        raise TaskGroupError("map_binding must identify map_id and map_version_id")
    if binding.resolution <= 0.0 or binding.width <= 0 or binding.height <= 0:
        raise TaskGroupError("map_binding geometry must be positive")
    if not all(math.isfinite(item) for item in (binding.resolution, *binding.origin)):
        raise TaskGroupError("map_binding geometry must be finite")


def _required_text(value: dict, key: str) -> str:
    item = value.get(key)
    if not isinstance(item, str) or not item.strip():
        raise TaskGroupError(f"{key} must be a non-empty string")
    return item.strip()


def _strict_bool(value: object, field_name: str) -> bool:
    if not isinstance(value, bool):
        raise TaskGroupError(f"{field_name} must be boolean")
    return value


def _safe_component(value: str, field_name: str) -> str:
    if (
        not isinstance(value, str)
        or not value.strip()
        or Path(value).name != value
        or value in {".", ".."}
        or not SAFE_COMPONENT_RE.fullmatch(value)
    ):
        raise TaskGroupError(f"{field_name} contains an unsafe path component")
    return value.strip()


def _required_string(value: dict, key: str) -> str:
    item = value.get(key)
    if not isinstance(item, str):
        raise TaskGroupError(f"{key} must be a string")
    return item


def _optional_string(value: dict, key: str) -> str:
    if key not in value:
        return ""
    return _required_string(value, key)


def _require_keys(
    value: dict,
    allowed: set[str],
    required: set[str],
    field_name: str,
) -> None:
    missing = sorted(required - value.keys())
    if missing:
        raise TaskGroupError(f"{field_name} is missing required field: {missing[0]}")
    unexpected = sorted(value.keys() - allowed)
    if unexpected:
        raise TaskGroupError(f"{field_name} contains unsupported field: {unexpected[0]}")


def _now_iso() -> str:
    return datetime.now(timezone.utc).isoformat(timespec="seconds")


def _relative_path(path: Path, root: Path | None = None) -> str:
    if root is not None:
        try:
            return path.relative_to(root).as_posix()
        except ValueError:
            pass
    try:
        return path.relative_to(Path.cwd()).as_posix()
    except ValueError:
        return path.name


def _pcd_hash_from_manifest(version_root: Path) -> str:
    manifest_path = version_root / "manifest.yaml"
    try:
        manifest = yaml.safe_load(manifest_path.read_text(encoding="utf-8"))
    except (OSError, UnicodeError, yaml.YAMLError) as exc:
        raise TaskGroupError(f"cannot read map manifest: {exc}") from exc
    if not isinstance(manifest, dict):
        raise TaskGroupError("map manifest must contain an object")
    if str(manifest.get("state", "")).upper() != "READY":
        return ""
    asset = (manifest.get("assets") or {}).get("localization_pcd")
    if not isinstance(asset, dict):
        return ""
    declared_hash = str(asset.get("sha256", ""))
    if not re.fullmatch(r"sha256:[0-9a-f]{64}", declared_hash):
        return ""
    asset_path = version_root / str(asset.get("path", ""))
    if not asset_path.is_file():
        raise TaskGroupError("map manifest localization PCD does not exist")
    return declared_hash


def _sha256_file(path: Path) -> str:
    try:
        digest = hashlib.sha256()
        with path.open("rb") as stream:
            for chunk in iter(lambda: stream.read(1024 * 1024), b""):
                digest.update(chunk)
        return "sha256:" + digest.hexdigest()
    except OSError as exc:
        raise TaskGroupError(f"cannot hash file {path}: {exc}") from exc


def _write_json_atomic(path: Path, value: dict, *, backup_count: int) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if backup_count:
        _rotate_backups(path, backup_count)
    payload = json.dumps(value, ensure_ascii=False, indent=2, allow_nan=False) + "\n"
    _write_bytes_atomic(path, payload.encode("utf-8"))


def _write_bytes_atomic(path: Path, payload: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    descriptor, temporary_name = tempfile.mkstemp(prefix=f".{path.name}.", suffix=".tmp", dir=path.parent)
    try:
        with os.fdopen(descriptor, "wb") as stream:
            stream.write(payload)
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary_name, path)
        directory_fd = os.open(path.parent, os.O_RDONLY)
        try:
            os.fsync(directory_fd)
        finally:
            os.close(directory_fd)
    except (OSError, UnicodeError) as exc:
        try:
            os.unlink(temporary_name)
        except OSError:
            pass
        raise TaskGroupError(f"cannot atomically write {path}: {exc}") from exc


def _rotate_backups(path: Path, backup_count: int) -> None:
    if backup_count <= 0 or not path.exists():
        return
    oldest = path.with_name(f"{path.name}.bak.{backup_count}")
    if oldest.exists():
        oldest.unlink()
    for index in range(backup_count - 1, 0, -1):
        source = path.with_name(f"{path.name}.bak.{index}")
        target = path.with_name(f"{path.name}.bak.{index + 1}")
        if source.exists():
            os.replace(source, target)
    shutil.copy2(path, path.with_name(f"{path.name}.bak.1"))


def _read_raster(path: Path) -> tuple[bytes, int, int]:
    try:
        data = path.read_bytes()
    except OSError as exc:
        raise TaskGroupError(f"cannot read map image {path}: {exc}") from exc
    if data.startswith((b"P2", b"P5")):
        return _read_pgm(data, path)
    try:
        from PIL import Image

        with Image.open(path) as image:
            image = image.convert("L")
            return image.tobytes(), image.width, image.height
    except (ImportError, OSError, ValueError) as exc:
        raise TaskGroupError(f"unsupported or invalid map image {path}: {exc}") from exc


def _read_pgm(data: bytes, path: Path) -> tuple[bytes, int, int]:
    tokens: list[bytes] = []
    index = 0
    while len(tokens) < 4:
        while index < len(data) and data[index:index + 1].isspace():
            index += 1
        if index < len(data) and data[index:index + 1] == b"#":
            newline = data.find(b"\n", index)
            index = len(data) if newline < 0 else newline + 1
            continue
        end = index
        while end < len(data) and not data[end:end + 1].isspace():
            end += 1
        if end == index:
            break
        tokens.append(data[index:end])
        index = end
    if len(tokens) != 4 or tokens[0] not in (b"P2", b"P5"):
        raise TaskGroupError(f"invalid PGM header: {path}")
    try:
        width, height, maximum = (int(item) for item in tokens[1:])
    except ValueError as exc:
        raise TaskGroupError(f"invalid PGM dimensions: {path}") from exc
    if width <= 0 or height <= 0 or not 0 < maximum <= 65535:
        raise TaskGroupError(f"invalid PGM dimensions or max value: {path}")
    if tokens[0] == b"P2":
        values = [int(item) for item in data[index:].split() if not item.startswith(b"#")]
        if len(values) != width * height:
            raise TaskGroupError(f"invalid PGM raster length: {path}")
        return bytes(round(item * 255 / maximum) for item in values), width, height
    while index < len(data) and data[index:index + 1].isspace():
        index += 1
    size = width * height * (2 if maximum > 255 else 1)
    raw = data[index:index + size]
    if len(raw) != size:
        raise TaskGroupError(f"invalid PGM raster length: {path}")
    if maximum <= 255:
        return raw, width, height
    values = [raw[pos] * 256 + raw[pos + 1] for pos in range(0, len(raw), 2)]
    return bytes(round(item * 255 / maximum) for item in values), width, height


def _load_map_raster(snapshot: MapSnapshot) -> _MapRaster:
    metadata = yaml.safe_load(snapshot.yaml_path.read_text(encoding="utf-8"))
    pixels, width, height = _read_raster(snapshot.image_path)
    return _MapRaster(
        pixels=pixels,
        width=width,
        height=height,
        resolution=snapshot.resolution,
        origin=snapshot.origin,
        negate=bool(int(metadata.get("negate", 0))),
        occupied_thresh=float(metadata.get("occupied_thresh", 0.65)),
        free_thresh=float(metadata.get("free_thresh", 0.196)),
    )
