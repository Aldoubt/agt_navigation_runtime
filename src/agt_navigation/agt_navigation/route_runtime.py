"""Pure Route Asset -> odom RuntimePath core for V25-09B.

This module deliberately has no Nav2 global-planner dependency. A persistent
Route Asset lives in ``map``. Only the active segment is projected to ``odom``
at a controlled boundary and handed to a vehicle tracker adapter.
"""

from __future__ import annotations

from dataclasses import dataclass, field
import csv
import hashlib
import math
from pathlib import Path
from typing import Protocol

import yaml


class RouteRuntimeError(ValueError):
    """Stable fail-closed error for Route runtime preparation."""

    def __init__(self, code: str, message: str):
        super().__init__(message)
        self.code = str(code)


def _sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return f"sha256:{digest.hexdigest()}"


def _normalize_angle(value: float) -> float:
    return math.atan2(math.sin(value), math.cos(value))


@dataclass(frozen=True)
class RoutePoint:
    seq: int
    segment_id: str
    x: float
    y: float
    yaw: float
    direction: str
    v_ref: float
    curvature: float
    clearance: float
    semantic_ref: str = ""
    event_ref: str = ""


@dataclass(frozen=True)
class RouteSegment:
    segment_id: str
    direction: str
    points: tuple[RoutePoint, ...]
    event_refs: tuple[str, ...]


@dataclass(frozen=True)
class RouteAsset:
    route_id: str
    revision: int
    frame_id: str
    map_id: str
    map_version_id: str
    map_content_sha256: str
    vehicle_profile_sha256: str
    route_dir: Path
    segments: tuple[RouteSegment, ...]


@dataclass(frozen=True)
class MapOdomSnapshot:
    """Frozen TF snapshot with odom origin expressed in map coordinates.

    ``odom_origin_*_in_map`` and ``yaw_map_from_odom`` are the planar
    ``map -> odom`` transform as represented by TF (parent map, child odom).
    ``map_pose_to_odom`` applies its inverse to map-frame route geometry.
    """

    odom_origin_x_in_map: float
    odom_origin_y_in_map: float
    yaw_map_from_odom: float
    generation: int = 0

    def map_pose_to_odom(self, x: float, y: float, yaw: float) -> tuple[float, float, float]:
        values = (x, y, yaw, self.odom_origin_x_in_map, self.odom_origin_y_in_map, self.yaw_map_from_odom)
        if not all(math.isfinite(float(value)) for value in values):
            raise RouteRuntimeError("non_finite_transform", "map/odom transform and route pose must be finite")
        dx = float(x) - float(self.odom_origin_x_in_map)
        dy = float(y) - float(self.odom_origin_y_in_map)
        c = math.cos(self.yaw_map_from_odom)
        s = math.sin(self.yaw_map_from_odom)
        odom_x = c * dx + s * dy
        odom_y = -s * dx + c * dy
        odom_yaw = _normalize_angle(float(yaw) - float(self.yaw_map_from_odom))
        return odom_x, odom_y, odom_yaw


@dataclass(frozen=True)
class RuntimePathPoint:
    x: float
    y: float
    yaw: float
    direction: str
    v_ref: float
    semantic_ref: str
    event_ref: str


@dataclass(frozen=True)
class RuntimePath:
    frame_id: str
    route_id: str
    revision: int
    segment_id: str
    direction: str
    alignment_generation: int
    points: tuple[RuntimePathPoint, ...]


@dataclass(frozen=True)
class TrackerFeedback:
    status: str
    active_segment_id: str
    path_index: int = 0
    cross_track_error_m: float = 0.0
    heading_error_rad: float = 0.0
    remaining_distance_m: float = 0.0
    failure_reason: str = ""


@dataclass(frozen=True)
class SegmentCompletion:
    segment_id: str
    event_refs: tuple[str, ...]
    route_complete: bool


class VehicleTrackerAdapter(Protocol):
    """Vehicle-specific tracking boundary; no planning, TF or Mission ownership."""

    def start(self, path: RuntimePath) -> None:
        ...

    def cancel(self) -> None:
        ...


@dataclass
class RouteRuntimeMetrics:
    segment_projections: int = 0
    tracker_starts: int = 0
    # ROUTE mode must never call the global planner. This counter exists as an
    # explicit integration-test invariant and is intentionally never incremented.
    global_planner_requests: int = 0


def load_route_asset(
    route_dir: str | Path,
    *,
    expected_map_content_sha256: str | None = None,
    expected_vehicle_profile_sha256: str | None = None,
) -> RouteAsset:
    """Load one immutable READY Route Asset and validate its self-identity."""
    root = Path(route_dir).expanduser().resolve()
    manifest_path = root / "route.yaml"
    csv_path = root / "route.csv"
    if not manifest_path.is_file() or not csv_path.is_file():
        raise RouteRuntimeError("route_asset_missing", "route.yaml and route.csv are required")

    try:
        manifest = yaml.safe_load(manifest_path.read_text(encoding="utf-8")) or {}
    except (OSError, UnicodeError, yaml.YAMLError) as exc:
        raise RouteRuntimeError("route_manifest_invalid", "route.yaml is unreadable") from exc
    if not isinstance(manifest, dict):
        raise RouteRuntimeError("route_manifest_invalid", "route.yaml must contain a mapping")
    if str(manifest.get("status", "")).upper() != "READY":
        raise RouteRuntimeError("route_not_ready", "runtime accepts READY Route revisions only")
    if str(manifest.get("frame_id", "")) != "map":
        raise RouteRuntimeError("route_frame_invalid", "persistent Route Asset frame_id must be map")

    frozen_csv_hash = str(manifest.get("route_csv_sha256", ""))
    actual_csv_hash = _sha256_file(csv_path)
    if not frozen_csv_hash or frozen_csv_hash != actual_csv_hash:
        raise RouteRuntimeError("route_csv_hash_mismatch", "route.csv differs from the frozen Route manifest")

    map_binding = manifest.get("map_binding") or {}
    vehicle_binding = manifest.get("vehicle_binding") or {}
    map_content_hash = str(map_binding.get("map_content_sha256", ""))
    vehicle_profile_hash = str(vehicle_binding.get("platform_profile_sha256", ""))
    if expected_map_content_sha256 is not None and map_content_hash != str(expected_map_content_sha256):
        raise RouteRuntimeError("route_map_binding_mismatch", "Route Asset does not match the active map content identity")
    if expected_vehicle_profile_sha256 is not None and vehicle_profile_hash != str(expected_vehicle_profile_sha256):
        raise RouteRuntimeError("route_vehicle_binding_mismatch", "Route Asset does not match the selected execution vehicle")

    points = _load_route_points(csv_path)
    segments = _group_segments(points)
    return RouteAsset(
        route_id=str(manifest.get("route_id", "")),
        revision=int(manifest.get("revision", 0)),
        frame_id="map",
        map_id=str(map_binding.get("map_id", "")),
        map_version_id=str(map_binding.get("map_version_id", "")),
        map_content_sha256=map_content_hash,
        vehicle_profile_sha256=vehicle_profile_hash,
        route_dir=root,
        segments=segments,
    )


def _load_route_points(path: Path) -> tuple[RoutePoint, ...]:
    required = {
        "seq", "segment_id", "x", "y", "yaw", "direction", "v_ref",
        "curvature", "clearance", "semantic_ref", "event_ref",
    }
    try:
        with path.open("r", encoding="utf-8", newline="") as stream:
            reader = csv.DictReader(stream)
            if reader.fieldnames is None or not required.issubset(reader.fieldnames):
                raise RouteRuntimeError("route_csv_schema_invalid", "route.csv is missing canonical columns")
            rows = list(reader)
    except (OSError, UnicodeError, csv.Error) as exc:
        raise RouteRuntimeError("route_csv_invalid", "route.csv is unreadable") from exc
    if not rows:
        raise RouteRuntimeError("route_empty", "Route Asset contains no path samples")

    points: list[RoutePoint] = []
    previous_seq: int | None = None
    for row in rows:
        try:
            point = RoutePoint(
                seq=int(row["seq"]),
                segment_id=str(row["segment_id"]).strip(),
                x=float(row["x"]),
                y=float(row["y"]),
                yaw=float(row["yaw"]),
                direction=str(row["direction"]).strip().upper(),
                v_ref=float(row["v_ref"]),
                curvature=float(row["curvature"]),
                clearance=float(row["clearance"]),
                semantic_ref=str(row.get("semantic_ref", "")).strip(),
                event_ref=str(row.get("event_ref", "")).strip(),
            )
        except (TypeError, ValueError) as exc:
            raise RouteRuntimeError("route_csv_value_invalid", "route.csv contains an invalid numeric value") from exc
        if not point.segment_id:
            raise RouteRuntimeError("route_segment_missing", "every Route sample requires segment_id")
        if point.direction not in {"F", "R"}:
            raise RouteRuntimeError("route_direction_invalid", "Route direction must be F or R")
        if not all(math.isfinite(value) for value in (point.x, point.y, point.yaw, point.v_ref, point.curvature, point.clearance)):
            raise RouteRuntimeError("route_value_non_finite", "Route numeric values must be finite")
        if previous_seq is not None and point.seq <= previous_seq:
            raise RouteRuntimeError("route_sequence_invalid", "Route seq must be strictly increasing")
        previous_seq = point.seq
        points.append(point)
    return tuple(points)


def _group_segments(points: tuple[RoutePoint, ...]) -> tuple[RouteSegment, ...]:
    groups: list[list[RoutePoint]] = []
    seen: set[str] = set()
    for point in points:
        if not groups or groups[-1][0].segment_id != point.segment_id:
            if point.segment_id in seen:
                raise RouteRuntimeError("route_segment_non_contiguous", "segment_id may not reappear after another segment")
            seen.add(point.segment_id)
            groups.append([point])
        else:
            groups[-1].append(point)

    segments: list[RouteSegment] = []
    for group in groups:
        directions = {point.direction for point in group}
        if len(directions) != 1:
            raise RouteRuntimeError("route_direction_change_inside_segment", "F/R changes require a segment boundary")
        event_refs: list[str] = []
        for point in group:
            if point.event_ref and point.event_ref not in event_refs:
                event_refs.append(point.event_ref)
        segments.append(RouteSegment(group[0].segment_id, group[0].direction, tuple(group), tuple(event_refs)))
    return tuple(segments)


def project_segment_to_odom(asset: RouteAsset, segment: RouteSegment, snapshot: MapOdomSnapshot) -> RuntimePath:
    points = []
    for point in segment.points:
        x, y, yaw = snapshot.map_pose_to_odom(point.x, point.y, point.yaw)
        points.append(RuntimePathPoint(x, y, yaw, point.direction, point.v_ref, point.semantic_ref, point.event_ref))
    return RuntimePath(
        frame_id="odom",
        route_id=asset.route_id,
        revision=asset.revision,
        segment_id=segment.segment_id,
        direction=segment.direction,
        alignment_generation=int(snapshot.generation),
        points=tuple(points),
    )


class RouteNavigationCore:
    """Segment-level ROUTE execution state machine independent of ROS transport."""

    def __init__(self, asset: RouteAsset, tracker: VehicleTrackerAdapter):
        if not asset.segments:
            raise RouteRuntimeError("route_empty", "Route Asset has no segments")
        self.asset = asset
        self.tracker = tracker
        self.metrics = RouteRuntimeMetrics()
        self.state = "IDLE"
        self._active_index = -1
        self._active_path: RuntimePath | None = None
        self._latest_snapshot: MapOdomSnapshot | None = None

    @property
    def active_path(self) -> RuntimePath | None:
        return self._active_path

    @property
    def active_segment(self) -> RouteSegment | None:
        if 0 <= self._active_index < len(self.asset.segments):
            return self.asset.segments[self._active_index]
        return None

    def start(self, snapshot: MapOdomSnapshot) -> RuntimePath:
        if self.state != "IDLE":
            raise RouteRuntimeError("route_session_already_started", "Route session may only be started once")
        self._latest_snapshot = snapshot
        self._active_index = 0
        self.state = "RUNNING"
        return self._project_and_start_tracker()

    def update_global_alignment(self, snapshot: MapOdomSnapshot) -> None:
        """Store a new correction for the next segment without moving the active path."""
        if self.state != "RUNNING":
            raise RouteRuntimeError("route_session_not_running", "alignment updates require a running Route session")
        self._latest_snapshot = snapshot

    def handle_tracker_feedback(self, feedback: TrackerFeedback) -> SegmentCompletion | None:
        if self.state != "RUNNING" or self.active_segment is None:
            raise RouteRuntimeError("route_session_not_running", "tracker feedback requires an active Route segment")
        if str(feedback.active_segment_id) != self.active_segment.segment_id:
            raise RouteRuntimeError("tracker_segment_mismatch", "tracker feedback does not match the active segment")
        status = str(feedback.status).upper()
        if status == "RUNNING":
            return None
        if status == "FAILED":
            self.state = "FAILED"
            self._active_path = None
            return None
        if status != "SUCCEEDED":
            raise RouteRuntimeError("tracker_status_invalid", "tracker status must be RUNNING, SUCCEEDED or FAILED")

        completed = self.active_segment
        route_complete = self._active_index + 1 >= len(self.asset.segments)
        completion = SegmentCompletion(completed.segment_id, completed.event_refs, route_complete)
        if route_complete:
            self.state = "COMPLETED"
            self._active_path = None
            return completion

        self._active_index += 1
        self._project_and_start_tracker()
        return completion

    def fail(self) -> None:
        """Abort the active Route because an external runtime boundary failed."""
        if self.state in {"COMPLETED", "FAILED", "CANCELED"}:
            return
        self.tracker.cancel()
        self.state = "FAILED"
        self._active_path = None

    def cancel(self) -> None:
        if self.state in {"COMPLETED", "FAILED", "CANCELED"}:
            return
        self.tracker.cancel()
        self.state = "CANCELED"
        self._active_path = None

    def _project_and_start_tracker(self) -> RuntimePath:
        if self._latest_snapshot is None or self.active_segment is None:
            raise RouteRuntimeError("route_projection_state_invalid", "segment projection requires an alignment snapshot")
        path = project_segment_to_odom(self.asset, self.active_segment, self._latest_snapshot)
        self.metrics.segment_projections += 1
        self._active_path = path
        self.tracker.start(path)
        self.metrics.tracker_starts += 1
        return path
