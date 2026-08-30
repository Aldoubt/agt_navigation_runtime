from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Mapping

from agt_navigation.task_group import MapSnapshot, TaskGroup, TaskGroupError, Waypoint, load_map_snapshot


def _now_iso() -> str:
    return datetime.now(timezone.utc).isoformat()


def _required_text(payload: Mapping[str, Any], key: str) -> str:
    value = payload.get(key)
    if not isinstance(value, str) or not value.strip():
        raise ValueError(f"{key} must be a non-empty string")
    return value.strip()


def _expected_revision(payload: Mapping[str, Any]) -> int:
    value = payload.get("expectedRevision", 0)
    if isinstance(value, bool) or not isinstance(value, int) or value < 0:
        raise ValueError("expectedRevision must be a non-negative integer")
    return value


def _loop(payload: Mapping[str, Any]) -> tuple[bool, int]:
    enabled = payload.get("loop", False)
    count = payload.get("loopCount", 1)
    if not isinstance(enabled, bool):
        raise ValueError("loop must be boolean")
    if isinstance(count, bool) or not isinstance(count, int) or count <= 0:
        raise ValueError("loopCount must be a positive integer")
    return enabled, count


@dataclass(frozen=True)
class ActiveTaskSite:
    site_id: str
    site_revision: str
    snapshot: MapSnapshot
    site_hash: str = ""

    @classmethod
    def from_files(
        cls,
        *,
        site_id: str,
        site_revision: str,
        navigation_yaml: str | Path,
        localization_pcd: str | Path | None,
        site_hash: str = "",
    ) -> "ActiveTaskSite":
        normalized_site = str(site_id).strip()
        normalized_revision = str(site_revision).strip()
        normalized_hash = str(site_hash).strip()
        if not normalized_site or not normalized_revision:
            raise ValueError("active Site id and revision must be non-empty")
        yaml_path = Path(navigation_yaml).expanduser().resolve()
        pcd_path = (
            Path(localization_pcd).expanduser().resolve()
            if localization_pcd is not None and str(localization_pcd).strip()
            else None
        )
        try:
            snapshot = load_map_snapshot(
                yaml_path,
                map_id=normalized_site,
                map_version_id=normalized_revision,
                localization_pcd_path=pcd_path,
            )
        except TaskGroupError as exc:
            raise ValueError(f"cannot load active Site navigation map: {exc}") from exc
        return cls(normalized_site, normalized_revision, snapshot, normalized_hash)

    @property
    def image_path(self) -> Path:
        return self.snapshot.image_path

    def context(self) -> dict[str, Any]:
        return {
            "siteId": self.site_id,
            "siteRevision": self.site_revision,
            "width": int(self.snapshot.width),
            "height": int(self.snapshot.height),
            "resolution": float(self.snapshot.resolution),
            "origin": [float(item) for item in self.snapshot.origin],
            "imageUrl": "/api/v1/tasks/map/image",
        }

    def validate_payload_identity(self, payload: Mapping[str, Any]) -> None:
        if (
            _required_text(payload, "siteId") != self.site_id
            or _required_text(payload, "siteRevision") != self.site_revision
        ):
            raise ValueError("task request does not match the active Site revision")


def build_task_document(site: ActiveTaskSite, payload: Mapping[str, Any]) -> TaskGroup:
    site.validate_payload_identity(payload)
    task_id = _required_text(payload, "taskId")
    expected_revision = _expected_revision(payload)
    loop, loop_count = _loop(payload)
    raw_waypoints = payload.get("waypoints")
    if not isinstance(raw_waypoints, list) or not raw_waypoints:
        raise ValueError("waypoints must be a non-empty array")

    points: list[Waypoint] = []
    for index, raw in enumerate(raw_waypoints):
        if not isinstance(raw, Mapping):
            raise ValueError(f"waypoints[{index}] must be an object")
        waypoint_id = _required_text(raw, "id")
        dwell = raw.get("dwellS", 0.0)
        if isinstance(dwell, bool) or not isinstance(dwell, (int, float)):
            raise ValueError(f"waypoints[{index}].dwellS must be numeric")
        if abs(float(dwell)) > 1e-9:
            raise ValueError(
                "dwellS is not persisted by the current Runtime TaskGroup schema; use 0 until the execution contract supports it"
            )
        try:
            x = float(raw["x"])
            y = float(raw["y"])
            yaw = float(raw["yaw"])
        except (KeyError, TypeError, ValueError) as exc:
            raise ValueError(f"waypoints[{index}] must contain numeric x, y and yaw") from exc
        points.append(
            Waypoint(
                id=waypoint_id,
                name=waypoint_id,
                x=x,
                y=y,
                yaw=yaw,
                enabled=True,
                note="",
            )
        )

    stamp = _now_iso()
    task = TaskGroup(
        task_group_id=task_id,
        name=task_id,
        description="Created by AGT Operator HMI",
        created_at=stamp,
        updated_at=stamp,
        map_binding=site.snapshot.binding(),
        points=points,
        loop=loop,
        loop_count=loop_count,
        revision=expected_revision + 1,
    )
    try:
        task.validate()
    except TaskGroupError as exc:
        raise ValueError(str(exc)) from exc
    task.content_sha256 = task.canonical_hash()
    return task


def build_single_point_task(
    site: ActiveTaskSite,
    *,
    inspection_task_id: str,
    point: Mapping[str, Any],
    expected_revision: int,
) -> TaskGroup:
    point_id = _required_text(point, "id")
    task_group_id = f"{inspection_task_id}-{point_id}-nav"
    return build_task_document(
        site,
        {
            "taskId": task_group_id,
            "siteId": site.site_id,
            "siteRevision": site.site_revision,
            "expectedRevision": expected_revision,
            "loop": False,
            "loopCount": 1,
            "waypoints": [
                {
                    "id": point_id,
                    "x": point["x"],
                    "y": point["y"],
                    "yaw": point["yaw"],
                    "dwellS": 0.0,
                }
            ],
        },
    )
