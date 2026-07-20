"""Validation for task-chain JSON files written by ros_qt5_gui_app."""

from dataclasses import dataclass
import json
import math
from pathlib import Path


class TaskChainError(ValueError):
    """A task chain cannot safely be executed."""


@dataclass(frozen=True)
class Waypoint:
    name: str
    x: float
    y: float
    theta: float


def _signature(point):
    return (point.name, point.x, point.y, point.theta)


def _has_repeated_whole_pattern(points):
    """Detect the vendor GUI's append-on-save failure without editing its file."""
    count = len(points)
    for period in range(1, count // 2 + 1):
        if count % period:
            continue
        signatures = [_signature(point) for point in points]
        if signatures == signatures[:period] * (count // period):
            return True
    return False


def load_qt_task_chain(path, *, maximum_points=200):
    task_path = Path(path).expanduser()
    if not task_path.is_absolute():
        raise TaskChainError("task_file must be an absolute path")
    if not task_path.is_file():
        raise TaskChainError(f"task file does not exist: {task_path}")
    try:
        document = json.loads(task_path.read_text(encoding="utf-8"))
    except (OSError, UnicodeError, json.JSONDecodeError) as exc:
        raise TaskChainError(f"cannot read task JSON: {exc}") from exc
    if not isinstance(document, dict) or not isinstance(document.get("points"), list):
        raise TaskChainError("task JSON must contain a points array")
    raw_points = document["points"]
    if not raw_points:
        raise TaskChainError("task contains no waypoints")
    if len(raw_points) > maximum_points:
        raise TaskChainError(
            f"task contains {len(raw_points)} waypoints; limit is {maximum_points}"
        )

    points = []
    for index, raw in enumerate(raw_points):
        if not isinstance(raw, dict):
            raise TaskChainError(f"waypoint {index} must be an object")
        name = raw.get("name")
        if not isinstance(name, str) or not name.strip():
            raise TaskChainError(f"waypoint {index} has no valid name")
        try:
            x, y, theta = (float(raw[key]) for key in ("x", "y", "theta"))
        except (KeyError, TypeError, ValueError) as exc:
            raise TaskChainError(f"waypoint {index} has invalid x/y/theta") from exc
        if not all(math.isfinite(value) for value in (x, y, theta)):
            raise TaskChainError(f"waypoint {index} contains a non-finite coordinate")
        point = Waypoint(name=name.strip(), x=x, y=y, theta=theta)
        if points and _signature(points[-1]) == _signature(point):
            raise TaskChainError(f"waypoint {index} duplicates the preceding waypoint")
        points.append(point)

    if _has_repeated_whole_pattern(points):
        raise TaskChainError(
            "task is an exact repeated pattern; save it to a new file because the "
            "vendor GUI may have appended an earlier chain"
        )
    return points


def point_inside_map(point, map_info):
    """Return whether a world point lies in an OccupancyGrid, including origin yaw."""
    q = map_info.origin.orientation
    yaw = math.atan2(
        2.0 * (q.w * q.z + q.x * q.y),
        1.0 - 2.0 * (q.y * q.y + q.z * q.z),
    )
    dx = point.x - map_info.origin.position.x
    dy = point.y - map_info.origin.position.y
    local_x = math.cos(yaw) * dx + math.sin(yaw) * dy
    local_y = -math.sin(yaw) * dx + math.cos(yaw) * dy
    return (
        map_info.resolution > 0.0
        and 0.0 <= local_x < map_info.width * map_info.resolution
        and 0.0 <= local_y < map_info.height * map_info.resolution
    )
