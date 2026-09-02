"""Pure task-draft state for the RViz field-acceptance frontend.

RViz is only an editor. This module deliberately owns no ROS clients, files or
Nav2 actions. Saved tasks remain the existing TaskGroup v1 contract, and formal
execution is allowed only for the exact last-saved revision/hash.
"""

from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime, timezone
import copy
import math

from .task_group import MapBinding, TaskGroup, Waypoint, normalize_yaw


class DraftStateError(RuntimeError):
    """Raised when an edit/save/start transition is not valid."""


@dataclass(frozen=True)
class SavedTaskRef:
    task_group_id: str
    revision: int
    content_sha256: str


class RvizTaskDraft:
    """Ordered, in-memory waypoint draft with an explicit saved boundary."""

    def __init__(self) -> None:
        self._points: list[Waypoint] = []
        self._dirty = False
        self._saved: SavedTaskRef | None = None
        self._loaded_created_at = ""

    @property
    def points(self) -> tuple[Waypoint, ...]:
        return tuple(self._points)

    @property
    def dirty(self) -> bool:
        return self._dirty

    def add(self, x: float, y: float, yaw: float) -> Waypoint:
        values = (float(x), float(y), float(yaw))
        if not all(math.isfinite(value) for value in values):
            raise ValueError("RViz task point coordinates must be finite")
        index = len(self._points) + 1
        point_id = f"P{index:02d}"
        point = Waypoint(
            id=point_id,
            name=point_id,
            x=values[0],
            y=values[1],
            yaw=normalize_yaw(values[2]),
            enabled=True,
            note="",
        )
        self._points.append(point)
        self._dirty = True
        return point

    def undo(self) -> bool:
        if not self._points:
            return False
        self._points.pop()
        self._dirty = True
        return True

    def clear(self) -> None:
        self._points.clear()
        self._dirty = True

    def load_task(self, task: TaskGroup) -> None:
        task.validate()
        if not task.content_sha256:
            raise DraftStateError("loaded task has no saved content hash")
        if task.content_sha256 != task.canonical_hash():
            raise DraftStateError("loaded task content hash does not match content")
        self._points = [copy.deepcopy(point) for point in task.points]
        self._saved = SavedTaskRef(
            task_group_id=task.task_group_id,
            revision=int(task.revision),
            content_sha256=task.content_sha256,
        )
        self._loaded_created_at = task.created_at
        self._dirty = False

    def build_task(
        self,
        *,
        map_binding: MapBinding,
        task_group_id: str,
        name: str,
        description: str,
        revision: int,
        created_at: str | None = None,
        updated_at: str | None = None,
    ) -> TaskGroup:
        if not self._points:
            raise DraftStateError("draft has no waypoints")
        revision_value = int(revision)
        if revision_value <= 0:
            raise ValueError("task revision must be positive")
        now = datetime.now(timezone.utc).isoformat(timespec="seconds")
        task = TaskGroup(
            task_group_id=str(task_group_id),
            name=str(name),
            description=str(description),
            created_at=str(created_at or self._loaded_created_at or now),
            updated_at=str(updated_at or now),
            revision=revision_value,
            map_binding=copy.deepcopy(map_binding),
            points=[copy.deepcopy(point) for point in self._points],
            frame_id="map",
            loop=False,
            loop_count=1,
        )
        task.validate()
        task.content_sha256 = task.canonical_hash()
        return task

    def mark_saved(self, task: TaskGroup) -> None:
        task.validate()
        if not task.content_sha256:
            raise DraftStateError("saved task has no content hash")
        if task.content_sha256 != task.canonical_hash():
            raise DraftStateError("saved task content hash does not match content")
        self._points = [copy.deepcopy(point) for point in task.points]
        self._saved = SavedTaskRef(
            task_group_id=task.task_group_id,
            revision=int(task.revision),
            content_sha256=task.content_sha256,
        )
        self._loaded_created_at = task.created_at
        self._dirty = False

    def execution_ref(self) -> SavedTaskRef:
        if self._saved is None:
            raise DraftStateError("save the RViz task before START")
        if self._dirty:
            raise DraftStateError("save the RViz task after edits before START")
        return self._saved
