from __future__ import annotations

from array import array
from dataclasses import asdict, dataclass
import hashlib
import json
import math
from pathlib import Path
import struct
import sys
from typing import Any, Mapping

import yaml


_MAGIC = b"AGTRAY01"
_SCHEMA_VERSION = 1
_HEADER_LENGTH = struct.Struct("<I")
_UINT16_MAX = 65535


@dataclass(frozen=True)
class RaycastConfig:
    schema_version: int = 1
    frame_id: str = "camera_init"
    resolution_m: float = 0.05
    free_logodds_delta: float = -0.45
    hit_logodds_delta: float = 0.85
    min_logodds: float = -4.0
    max_logodds: float = 4.0
    free_threshold: float = -0.9
    occupied_threshold: float = 1.7
    min_observation_count: int = 2
    min_ray_range_m: float = 0.5
    max_ray_range_m: float = 40.0
    cloud_stride: int = 1
    point_stride: int = 8
    pose_max_age_s: float = 0.15

    def __post_init__(self) -> None:
        if int(self.schema_version) != _SCHEMA_VERSION:
            raise ValueError(f"unsupported raycast config schema_version: {self.schema_version}")
        if not str(self.frame_id).strip():
            raise ValueError("frame_id must be non-empty")
        if not (0.001 <= float(self.resolution_m) <= 5.0):
            raise ValueError("resolution_m must be within [0.001, 5.0]")
        if not (float(self.free_logodds_delta) < 0.0):
            raise ValueError("free_logodds_delta must be negative")
        if not (float(self.hit_logodds_delta) > 0.0):
            raise ValueError("hit_logodds_delta must be positive")
        if not (float(self.min_logodds) < 0.0 < float(self.max_logodds)):
            raise ValueError("log-odds clamp must straddle zero")
        if not (float(self.min_logodds) <= float(self.free_threshold) < 0.0):
            raise ValueError("free_threshold must be negative and within the clamp")
        if not (0.0 < float(self.occupied_threshold) <= float(self.max_logodds)):
            raise ValueError("occupied_threshold must be positive and within the clamp")
        if int(self.min_observation_count) < 1:
            raise ValueError("min_observation_count must be >= 1")
        if not (0.0 <= float(self.min_ray_range_m) < float(self.max_ray_range_m)):
            raise ValueError("ray range limits are invalid")
        if int(self.cloud_stride) < 1 or int(self.point_stride) < 1:
            raise ValueError("cloud_stride and point_stride must be >= 1")
        if float(self.pose_max_age_s) <= 0.0:
            raise ValueError("pose_max_age_s must be > 0")

    @classmethod
    def from_mapping(cls, value: Mapping[str, Any]) -> "RaycastConfig":
        fields = cls.__dataclass_fields__
        unknown = sorted(set(value) - set(fields))
        if unknown:
            raise ValueError(f"unknown raycast config keys: {', '.join(unknown)}")
        return cls(**{key: value[key] for key in value})


def load_config(path: str | Path) -> RaycastConfig:
    document = yaml.safe_load(Path(path).read_text(encoding="utf-8"))
    if not isinstance(document, dict):
        raise ValueError("raycast config must be a mapping")
    return RaycastConfig.from_mapping(document)


@dataclass
class RaycastStats:
    accepted_rays: int = 0
    rejected_range: int = 0
    rejected_nonfinite: int = 0


@dataclass(frozen=True)
class CellEvidence:
    log_odds: float
    observation_count: int


@dataclass(frozen=True)
class RaycastEvidenceArtifact:
    binary: Path
    record: Path


@dataclass(frozen=True)
class RaycastEvidenceSnapshot:
    frame_id: str
    resolution_m: float
    origin_ix: int
    origin_iy: int
    width: int
    height: int
    log_odds: tuple[float, ...]
    observation_counts: tuple[int, ...]
    free_threshold: float
    occupied_threshold: float
    min_observation_count: int
    config: RaycastConfig
    stats: Mapping[str, int]

    def __post_init__(self) -> None:
        expected = int(self.width) * int(self.height)
        if self.width <= 0 or self.height <= 0:
            raise ValueError("evidence dimensions must be positive")
        if len(self.log_odds) != expected or len(self.observation_counts) != expected:
            raise ValueError("evidence raster size does not match dimensions")

    @property
    def origin_x_m(self) -> float:
        return self.origin_ix * self.resolution_m

    @property
    def origin_y_m(self) -> float:
        return self.origin_iy * self.resolution_m

    def _offset(self, ix: int, iy: int) -> int | None:
        x = int(ix) - self.origin_ix
        y = int(iy) - self.origin_iy
        if x < 0 or y < 0 or x >= self.width or y >= self.height:
            return None
        return y * self.width + x

    def cell_evidence(self, ix: int, iy: int) -> CellEvidence:
        offset = self._offset(ix, iy)
        if offset is None:
            return CellEvidence(0.0, 0)
        return CellEvidence(
            float(self.log_odds[offset]),
            int(self.observation_counts[offset]),
        )

    def classify_cell(self, ix: int, iy: int) -> str:
        evidence = self.cell_evidence(ix, iy)
        if evidence.observation_count < self.min_observation_count:
            return "unknown"
        if evidence.log_odds >= self.occupied_threshold:
            return "occupied"
        if evidence.log_odds <= self.free_threshold:
            return "free"
        return "unknown"

    def classify_world(self, xy: tuple[float, float]) -> str:
        ix, iy = world_to_cell(xy, self.resolution_m)
        return self.classify_cell(ix, iy)


class RaycastEvidenceGrid:
    def __init__(self, config: RaycastConfig | None = None) -> None:
        self.config = config or RaycastConfig()
        self._cells: dict[tuple[int, int], list[float | int]] = {}
        self.stats = RaycastStats()

    def _update(self, cell: tuple[int, int], delta: float) -> None:
        previous = self._cells.get(cell)
        if previous is None:
            log_odds = 0.0
            count = 0
        else:
            log_odds = float(previous[0])
            count = int(previous[1])
        log_odds = min(
            self.config.max_logodds,
            max(self.config.min_logodds, log_odds + float(delta)),
        )
        self._cells[cell] = [log_odds, count + 1]

    def observe_ray(
        self,
        origin_xy: tuple[float, float],
        endpoint_xy: tuple[float, float],
    ) -> bool:
        ox, oy = float(origin_xy[0]), float(origin_xy[1])
        ex, ey = float(endpoint_xy[0]), float(endpoint_xy[1])
        if not all(math.isfinite(value) for value in (ox, oy, ex, ey)):
            self.stats.rejected_nonfinite += 1
            return False
        distance = math.hypot(ex - ox, ey - oy)
        if distance < self.config.min_ray_range_m or distance > self.config.max_ray_range_m:
            self.stats.rejected_range += 1
            return False

        start = world_to_cell((ox, oy), self.config.resolution_m)
        end = world_to_cell((ex, ey), self.config.resolution_m)
        cells = grid_ray_cells(start, end)
        if not cells:
            self.stats.rejected_range += 1
            return False
        for cell in cells[:-1]:
            self._update(cell, self.config.free_logodds_delta)
        self._update(cells[-1], self.config.hit_logodds_delta)
        self.stats.accepted_rays += 1
        return True

    def cell_evidence(self, ix: int, iy: int) -> CellEvidence:
        raw = self._cells.get((int(ix), int(iy)))
        if raw is None:
            return CellEvidence(0.0, 0)
        return CellEvidence(float(raw[0]), int(raw[1]))

    def classify_cell(self, ix: int, iy: int) -> str:
        evidence = self.cell_evidence(ix, iy)
        if evidence.observation_count < self.config.min_observation_count:
            return "unknown"
        if evidence.log_odds >= self.config.occupied_threshold:
            return "occupied"
        if evidence.log_odds <= self.config.free_threshold:
            return "free"
        return "unknown"

    def classify_world(self, xy: tuple[float, float]) -> str:
        ix, iy = world_to_cell(xy, self.config.resolution_m)
        return self.classify_cell(ix, iy)

    def snapshot(self) -> RaycastEvidenceSnapshot:
        if not self._cells:
            raise RuntimeError("cannot materialize empty raycast evidence")
        xs = [cell[0] for cell in self._cells]
        ys = [cell[1] for cell in self._cells]
        origin_ix = min(xs)
        origin_iy = min(ys)
        max_ix = max(xs)
        max_iy = max(ys)
        width = max_ix - origin_ix + 1
        height = max_iy - origin_iy + 1
        size = width * height
        log_odds = [0.0] * size
        counts = [0] * size
        for (ix, iy), raw in self._cells.items():
            offset = (iy - origin_iy) * width + (ix - origin_ix)
            log_odds[offset] = float(raw[0])
            counts[offset] = min(_UINT16_MAX, int(raw[1]))
        return RaycastEvidenceSnapshot(
            frame_id=self.config.frame_id,
            resolution_m=self.config.resolution_m,
            origin_ix=origin_ix,
            origin_iy=origin_iy,
            width=width,
            height=height,
            log_odds=tuple(log_odds),
            observation_counts=tuple(counts),
            free_threshold=self.config.free_threshold,
            occupied_threshold=self.config.occupied_threshold,
            min_observation_count=self.config.min_observation_count,
            config=self.config,
            stats={
                "accepted_rays": self.stats.accepted_rays,
                "rejected_range": self.stats.rejected_range,
                "rejected_nonfinite": self.stats.rejected_nonfinite,
            },
        )


def world_to_cell(xy: tuple[float, float], resolution_m: float) -> tuple[int, int]:
    resolution = float(resolution_m)
    if resolution <= 0.0:
        raise ValueError("resolution_m must be positive")
    return (
        math.floor(float(xy[0]) / resolution),
        math.floor(float(xy[1]) / resolution),
    )


def grid_ray_cells(start: tuple[int, int], end: tuple[int, int]) -> list[tuple[int, int]]:
    """Return an inclusive Bresenham traversal from start to end."""
    x0, y0 = int(start[0]), int(start[1])
    x1, y1 = int(end[0]), int(end[1])
    dx = abs(x1 - x0)
    sx = 1 if x0 < x1 else -1
    dy = -abs(y1 - y0)
    sy = 1 if y0 < y1 else -1
    error = dx + dy
    cells: list[tuple[int, int]] = []
    while True:
        cells.append((x0, y0))
        if x0 == x1 and y0 == y1:
            return cells
        twice = 2 * error
        if twice >= dy:
            error += dy
            x0 += sx
        if twice <= dx:
            error += dx
            y0 += sy


def _sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return f"sha256:{digest.hexdigest()}"


def _atomic_write_bytes(path: Path, payload: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_bytes(payload)
    temporary.replace(path)


def _atomic_write_text(path: Path, payload: str) -> None:
    _atomic_write_bytes(path, payload.encode("utf-8"))


def _array_bytes(values: array) -> bytes:
    if sys.byteorder != "little":
        copied = array(values.typecode, values)
        copied.byteswap()
        return copied.tobytes()
    return values.tobytes()


def _encode_snapshot(snapshot: RaycastEvidenceSnapshot) -> bytes:
    header = {
        "schema_version": _SCHEMA_VERSION,
        "frame_id": snapshot.frame_id,
        "resolution_m": snapshot.resolution_m,
        "origin_ix": snapshot.origin_ix,
        "origin_iy": snapshot.origin_iy,
        "origin_x_m": snapshot.origin_x_m,
        "origin_y_m": snapshot.origin_y_m,
        "width": snapshot.width,
        "height": snapshot.height,
        "config": asdict(snapshot.config),
        "stats": dict(snapshot.stats),
    }
    header_bytes = json.dumps(header, sort_keys=True, separators=(",", ":")).encode("utf-8")
    odds = array("f", snapshot.log_odds)
    counts = array("H", snapshot.observation_counts)
    return b"".join(
        [
            _MAGIC,
            _HEADER_LENGTH.pack(len(header_bytes)),
            header_bytes,
            _array_bytes(odds),
            _array_bytes(counts),
        ]
    )


def save_evidence(
    grid: RaycastEvidenceGrid,
    binary_path: str | Path,
    record_path: str | Path,
) -> RaycastEvidenceArtifact:
    snapshot = grid.snapshot()
    binary = Path(binary_path).expanduser().resolve()
    record = Path(record_path).expanduser().resolve()
    _atomic_write_bytes(binary, _encode_snapshot(snapshot))
    payload = {
        "schema_version": _SCHEMA_VERSION,
        "frame_id": snapshot.frame_id,
        "resolution_m": snapshot.resolution_m,
        "origin_ix": snapshot.origin_ix,
        "origin_iy": snapshot.origin_iy,
        "origin_x_m": snapshot.origin_x_m,
        "origin_y_m": snapshot.origin_y_m,
        "width": snapshot.width,
        "height": snapshot.height,
        "binary": str(binary),
        "binary_sha256": _sha256(binary),
        "config": asdict(snapshot.config),
        "stats": dict(snapshot.stats),
    }
    _atomic_write_text(record, json.dumps(payload, indent=2, sort_keys=True) + "\n")
    return RaycastEvidenceArtifact(binary=binary, record=record)


def _decode_snapshot(payload: bytes) -> RaycastEvidenceSnapshot:
    minimum = len(_MAGIC) + _HEADER_LENGTH.size
    if len(payload) < minimum:
        raise ValueError("raycast evidence binary is truncated")
    if payload[: len(_MAGIC)] != _MAGIC:
        raise ValueError("unsupported raycast evidence magic")
    header_size = _HEADER_LENGTH.unpack_from(payload, len(_MAGIC))[0]
    header_offset = minimum
    header_end = header_offset + header_size
    if header_end > len(payload):
        raise ValueError("raycast evidence header is truncated")
    try:
        header = json.loads(payload[header_offset:header_end].decode("utf-8"))
    except (UnicodeDecodeError, json.JSONDecodeError) as exc:
        raise ValueError("invalid raycast evidence header") from exc
    if header.get("schema_version") != _SCHEMA_VERSION:
        raise ValueError("unsupported raycast evidence schema")
    config_raw = header.get("config")
    if not isinstance(config_raw, dict):
        raise ValueError("raycast evidence config is missing")
    config = RaycastConfig.from_mapping(config_raw)
    width = int(header["width"])
    height = int(header["height"])
    count = width * height
    odds_bytes = count * 4
    count_bytes = count * 2
    expected_end = header_end + odds_bytes + count_bytes
    if expected_end != len(payload):
        raise ValueError("raycast evidence raster size mismatch")
    odds = array("f")
    odds.frombytes(payload[header_end : header_end + odds_bytes])
    counts = array("H")
    counts.frombytes(payload[header_end + odds_bytes : expected_end])
    if sys.byteorder != "little":
        odds.byteswap()
        counts.byteswap()
    stats = header.get("stats")
    if not isinstance(stats, dict):
        stats = {}
    return RaycastEvidenceSnapshot(
        frame_id=str(header["frame_id"]),
        resolution_m=float(header["resolution_m"]),
        origin_ix=int(header["origin_ix"]),
        origin_iy=int(header["origin_iy"]),
        width=width,
        height=height,
        log_odds=tuple(float(value) for value in odds),
        observation_counts=tuple(int(value) for value in counts),
        free_threshold=config.free_threshold,
        occupied_threshold=config.occupied_threshold,
        min_observation_count=config.min_observation_count,
        config=config,
        stats={str(key): int(value) for key, value in stats.items()},
    )


def load_evidence(
    binary_path: str | Path,
    record_path: str | Path,
) -> RaycastEvidenceSnapshot:
    binary = Path(binary_path).expanduser().resolve()
    record = Path(record_path).expanduser().resolve()
    if not binary.is_file() or not record.is_file():
        raise ValueError("raycast evidence binary/record is missing")
    try:
        metadata = json.loads(record.read_text(encoding="utf-8"))
    except json.JSONDecodeError as exc:
        raise ValueError("invalid raycast evidence record") from exc
    if not isinstance(metadata, dict) or metadata.get("schema_version") != _SCHEMA_VERSION:
        raise ValueError("unsupported raycast evidence record schema")
    expected_hash = metadata.get("binary_sha256")
    actual_hash = _sha256(binary)
    if not isinstance(expected_hash, str) or expected_hash != actual_hash:
        raise ValueError("raycast evidence checksum mismatch")
    snapshot = _decode_snapshot(binary.read_bytes())
    if metadata.get("frame_id") != snapshot.frame_id:
        raise ValueError("raycast evidence frame mismatch")
    if float(metadata.get("resolution_m", -1.0)) != snapshot.resolution_m:
        raise ValueError("raycast evidence resolution mismatch")
    return snapshot
