from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
from typing import Callable, Iterator

import numpy as np
import yaml

from .map_review import PgmMap
from .raycast_free_space import load_evidence
from .raycast_fusion import fuse_point_map_with_evidence


_PROJECTOR_PACKAGE = "agt_field_commissioning"
_UNKNOWN = 205
_FREE = 254
_OCCUPIED = 0


def _sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return f"sha256:{digest.hexdigest()}"


def _atomic_json(path: Path, payload: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_text(json.dumps(payload, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    temporary.replace(path)


def _atomic_text(path: Path, payload: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_text(payload, encoding="utf-8")
    temporary.replace(path)


def _default_runner(command: list[str]) -> int:
    return subprocess.run(command, check=False).returncode


def _resolve_executable(executable: str) -> str | None:
    candidate = Path(executable).expanduser()
    if candidate.is_absolute() or "/" in executable:
        return str(candidate.resolve()) if candidate.is_file() else None

    path_match = shutil.which(executable)
    if path_match:
        return path_match

    for raw_prefix in os.environ.get("AMENT_PREFIX_PATH", "").split(os.pathsep):
        prefix = raw_prefix.strip()
        if not prefix:
            continue
        ros_candidate = Path(prefix) / "lib" / _PROJECTOR_PACKAGE / executable
        if ros_candidate.is_file() and os.access(ros_candidate, os.X_OK):
            return str(ros_candidate.resolve())

    return None


@dataclass(frozen=True)
class ProjectionRequest:
    source_pcd: Path
    output_dir: Path
    resolution_m: float = 0.05
    max_ground_angle_deg: float = 35.0
    normal_k: int = 20
    min_ground_height_m: float = 0.0
    max_ground_height_m: float = 0.0
    max_obstacle_height_m: float = 0.0
    raycast_evidence: Path | None = None
    raycast_record: Path | None = None

    def validate(self) -> None:
        source = Path(self.source_pcd).expanduser()
        if not source.is_file() or source.stat().st_size <= 0:
            raise RuntimeError(f"source PCD is missing or empty: {source}")
        if not (0.01 <= float(self.resolution_m) <= 1.0):
            raise ValueError("resolution_m must be between 0.01 and 1.0")
        if not (0.0 < float(self.max_ground_angle_deg) < 90.0):
            raise ValueError("max_ground_angle_deg must be between 0 and 90")
        if int(self.normal_k) < 3:
            raise ValueError("normal_k must be >= 3")

        min_ground = float(self.min_ground_height_m)
        max_ground = float(self.max_ground_height_m)
        max_obstacle = float(self.max_obstacle_height_m)
        if min_ground != 0.0 and max_ground != 0.0 and min_ground >= max_ground:
            raise ValueError("min_ground_height_m must be less than max_ground_height_m when both are enabled")
        if min_ground != 0.0 and max_obstacle != 0.0 and max_obstacle <= min_ground:
            raise ValueError("max_obstacle_height_m must exceed min_ground_height_m when both are enabled")


@dataclass(frozen=True)
class ProjectionResult:
    backend: str
    pgm: Path
    yaml: Path
    record: Path
    projection_quality: str = "pcd_fallback"
    fallback_reason: str | None = None


def _write_map_yaml(
    destination: Path,
    image_name: str,
    resolution_m: float,
    origin_x: float,
    origin_y: float,
) -> None:
    payload = {
        "image": image_name,
        "resolution": float(resolution_m),
        "origin": [float(origin_x), float(origin_y), 0.0],
        "negate": 0,
        "occupied_thresh": 0.65,
        "free_thresh": 0.196,
        "mode": "trinary",
    }
    _atomic_text(destination, yaml.safe_dump(payload, sort_keys=False))


def _materialize_point_fallback(
    point_pgm: Path,
    point_yaml: Path,
    output_pgm: Path,
    output_yaml: Path,
) -> None:
    shutil.copy2(point_pgm, output_pgm)
    document = yaml.safe_load(point_yaml.read_text(encoding="utf-8"))
    if not isinstance(document, dict):
        raise RuntimeError("RTAB point-map YAML is invalid")
    document["image"] = output_pgm.name
    _atomic_text(output_yaml, yaml.safe_dump(document, sort_keys=False))


def _map_cell_metrics(pgm: PgmMap) -> tuple[dict[str, int], dict[str, float]]:
    occupied = sum(1 for value in pgm.pixels if value == _OCCUPIED)
    free = sum(1 for value in pgm.pixels if value == _FREE)
    unknown = len(pgm.pixels) - occupied - free
    counts = {"free": free, "occupied": occupied, "unknown": unknown}
    total = len(pgm.pixels)
    ratios = {key: value / total for key, value in counts.items()}
    return counts, ratios


@dataclass(frozen=True)
class _PcdLayout:
    source: Path
    data_kind: str
    data_offset: int
    fields: tuple[str, ...]
    sizes: tuple[int, ...]
    types: tuple[str, ...]
    counts: tuple[int, ...]
    points: int | None

    @classmethod
    def load(cls, source: Path) -> "_PcdLayout":
        header: dict[str, list[str]] = {}
        with source.open("rb") as stream:
            while True:
                line = stream.readline()
                if not line:
                    raise RuntimeError("PCD header is missing DATA declaration")
                stripped = line.strip()
                if not stripped or stripped.startswith(b"#"):
                    continue
                try:
                    tokens = stripped.decode("ascii").split()
                except UnicodeDecodeError as exc:
                    raise RuntimeError("PCD header is not ASCII") from exc
                key = tokens[0].upper()
                values = tokens[1:]
                if key == "DATA":
                    if len(values) != 1:
                        raise RuntimeError("invalid PCD DATA declaration")
                    data_kind = values[0].lower()
                    data_offset = stream.tell()
                    break
                header[key] = values

        fields = tuple(header.get("FIELDS", ()))
        if not fields:
            raise RuntimeError("PCD header is missing FIELDS")
        if not {"x", "y", "z"}.issubset(fields):
            raise RuntimeError("PCD must contain x, y, z fields")

        def _ints(key: str, default: int | None = None) -> tuple[int, ...]:
            raw = header.get(key)
            if raw is None:
                if default is None:
                    raise RuntimeError(f"PCD header is missing {key}")
                return tuple(default for _ in fields)
            try:
                values = tuple(int(value) for value in raw)
            except ValueError as exc:
                raise RuntimeError(f"invalid PCD {key}") from exc
            if len(values) != len(fields):
                raise RuntimeError(f"PCD {key} count does not match FIELDS")
            return values

        sizes = _ints("SIZE")
        types = tuple(value.upper() for value in header.get("TYPE", ()))
        if len(types) != len(fields):
            raise RuntimeError("PCD TYPE count does not match FIELDS")
        counts = _ints("COUNT", 1)
        if any(count <= 0 for count in counts):
            raise RuntimeError("PCD COUNT values must be positive")

        points: int | None = None
        raw_points = header.get("POINTS")
        if raw_points:
            try:
                points = int(raw_points[0])
            except ValueError as exc:
                raise RuntimeError("invalid PCD POINTS") from exc
        elif header.get("WIDTH") and header.get("HEIGHT"):
            try:
                points = int(header["WIDTH"][0]) * int(header["HEIGHT"][0])
            except ValueError as exc:
                raise RuntimeError("invalid PCD WIDTH/HEIGHT") from exc
        if points is not None and points <= 0:
            raise RuntimeError("PCD contains no points")
        if data_kind not in {"ascii", "binary"}:
            raise RuntimeError(f"unsupported PCD DATA encoding: {data_kind}")

        return cls(source, data_kind, data_offset, fields, sizes, types, counts, points)

    def _scalar_index(self, field: str) -> int:
        index = self.fields.index(field)
        return sum(self.counts[:index])

    def _byte_offset(self, field: str) -> int:
        index = self.fields.index(field)
        return sum(size * count for size, count in zip(self.sizes[:index], self.counts[:index]))

    @staticmethod
    def _numpy_format(type_code: str, size: int) -> str:
        table = {
            ("F", 4): "<f4",
            ("F", 8): "<f8",
            ("I", 1): "<i1",
            ("I", 2): "<i2",
            ("I", 4): "<i4",
            ("I", 8): "<i8",
            ("U", 1): "<u1",
            ("U", 2): "<u2",
            ("U", 4): "<u4",
            ("U", 8): "<u8",
        }
        try:
            return table[(type_code, size)]
        except KeyError as exc:
            raise RuntimeError(f"unsupported PCD scalar type: TYPE={type_code} SIZE={size}") from exc

    def iter_xyz(self, chunk_points: int) -> Iterator[tuple[np.ndarray, np.ndarray, np.ndarray]]:
        if self.data_kind == "binary":
            point_step = sum(size * count for size, count in zip(self.sizes, self.counts))
            formats = []
            offsets = []
            for name in ("x", "y", "z"):
                index = self.fields.index(name)
                if self.counts[index] != 1:
                    raise RuntimeError(f"PCD {name} field must have COUNT 1")
                formats.append(self._numpy_format(self.types[index], self.sizes[index]))
                offsets.append(self._byte_offset(name))
            dtype = np.dtype(
                {
                    "names": ["x", "y", "z"],
                    "formats": formats,
                    "offsets": offsets,
                    "itemsize": point_step,
                }
            )
            available_points = (self.source.stat().st_size - self.data_offset) // point_step
            point_count = self.points if self.points is not None else available_points
            if point_count > available_points:
                raise RuntimeError("binary PCD payload is truncated")
            data = np.memmap(
                self.source,
                dtype=dtype,
                mode="r",
                offset=self.data_offset,
                shape=(point_count,),
            )
            for start in range(0, point_count, chunk_points):
                chunk = data[start : start + chunk_points]
                yield chunk["x"], chunk["y"], chunk["z"]
            return

        usecols = tuple(self._scalar_index(name) for name in ("x", "y", "z"))
        with self.source.open("r", encoding="ascii", errors="strict") as stream:
            stream.seek(self.data_offset)
            while True:
                rows: list[str] = []
                for _ in range(chunk_points):
                    line = stream.readline()
                    if not line:
                        break
                    stripped = line.strip()
                    if stripped and not stripped.startswith("#"):
                        rows.append(stripped)
                if not rows:
                    break
                flat = np.fromstring("\n".join(rows), dtype=np.float64, sep=" ")
                column_count = sum(self.counts)
                if flat.size % column_count != 0:
                    raise RuntimeError("ASCII PCD row width does not match header")
                matrix = flat.reshape((-1, column_count))
                yield matrix[:, usecols[0]], matrix[:, usecols[1]], matrix[:, usecols[2]]
                if len(rows) < chunk_points:
                    break


class LightweightPcdGridBackend:
    """Stream a finalized PCD into a compact Nav2 occupancy grid.

    This is the field-delivery default. It intentionally depends only on NumPy
    and the runtime's existing map/evidence helpers, avoiding RTAB-Map/PCL ABI
    coupling. A cell is occupied when its observed vertical span reaches the
    configured threshold; observed low-span cells are free and unseen cells stay
    unknown. Optional raycast evidence can then refine free space.
    """

    backend_name = "lightweight_pcd_grid"

    def __init__(
        self,
        *,
        min_vertical_span_m: float = 0.15,
        chunk_points: int = 500_000,
        max_cells: int = 20_000_000,
    ) -> None:
        if float(min_vertical_span_m) <= 0.0:
            raise ValueError("min_vertical_span_m must be positive")
        if int(chunk_points) <= 0:
            raise ValueError("chunk_points must be positive")
        if int(max_cells) <= 0:
            raise ValueError("max_cells must be positive")
        self.min_vertical_span_m = float(min_vertical_span_m)
        self.chunk_points = int(chunk_points)
        self.max_cells = int(max_cells)

    def project(self, request: ProjectionRequest) -> ProjectionResult:
        request.validate()
        source = Path(request.source_pcd).expanduser().resolve()
        output_dir = Path(request.output_dir).expanduser().resolve()
        output_dir.mkdir(parents=True, exist_ok=True)
        pgm = output_dir / "raw_map.pgm"
        nav_yaml = output_dir / "raw_map.yaml"
        record = output_dir / "projection_record.json"

        layout = _PcdLayout.load(source)
        min_x = min_y = float("inf")
        max_x = max_y = float("-inf")
        valid_points = 0
        for x, y, z in layout.iter_xyz(self.chunk_points):
            finite = np.isfinite(x) & np.isfinite(y) & np.isfinite(z)
            if not np.any(finite):
                continue
            xf = np.asarray(x[finite], dtype=np.float64)
            yf = np.asarray(y[finite], dtype=np.float64)
            min_x = min(min_x, float(np.min(xf)))
            max_x = max(max_x, float(np.max(xf)))
            min_y = min(min_y, float(np.min(yf)))
            max_y = max(max_y, float(np.max(yf)))
            valid_points += int(np.count_nonzero(finite))
        if valid_points == 0:
            raise RuntimeError("PCD contains no finite x/y/z points")

        resolution = float(request.resolution_m)
        # Origins must be exact cell boundaries. Besides making the emitted
        # Nav2 YAML geometrically correct, this is required to align the PCD
        # raster with independently recorded raycast evidence.
        origin_ix = int(np.floor(min_x / resolution))
        origin_iy = int(np.floor(min_y / resolution))
        max_ix = int(np.floor(max_x / resolution))
        max_iy = int(np.floor(max_y / resolution))
        min_x = origin_ix * resolution
        min_y = origin_iy * resolution
        width = max_ix - origin_ix + 1
        height = max_iy - origin_iy + 1
        cell_count = width * height
        if cell_count <= 0 or cell_count > self.max_cells:
            raise RuntimeError(
                f"projected grid has unsafe size {width}x{height}={cell_count} cells; "
                f"limit is {self.max_cells}"
            )

        min_z = np.full(cell_count, np.inf, dtype=np.float32)
        max_z = np.full(cell_count, -np.inf, dtype=np.float32)
        observations = np.zeros(cell_count, dtype=np.uint32)
        for x, y, z in layout.iter_xyz(self.chunk_points):
            finite = np.isfinite(x) & np.isfinite(y) & np.isfinite(z)
            if not np.any(finite):
                continue
            xf = np.asarray(x[finite], dtype=np.float64)
            yf = np.asarray(y[finite], dtype=np.float64)
            zf = np.asarray(z[finite], dtype=np.float32)
            ix = np.floor((xf - min_x) / resolution).astype(np.int64)
            iy = np.floor((yf - min_y) / resolution).astype(np.int64)
            np.clip(ix, 0, width - 1, out=ix)
            np.clip(iy, 0, height - 1, out=iy)
            indices = iy * width + ix
            np.minimum.at(min_z, indices, zf)
            np.maximum.at(max_z, indices, zf)
            np.add.at(observations, indices, 1)

        seen = observations > 0
        occupied = seen & ((max_z - min_z) >= self.min_vertical_span_m)
        pixels_bottom_up = np.full(cell_count, _UNKNOWN, dtype=np.uint8)
        pixels_bottom_up[seen] = _FREE
        pixels_bottom_up[occupied] = _OCCUPIED
        pixels = np.flipud(pixels_bottom_up.reshape((height, width))).reshape(-1)
        PgmMap(width=width, height=height, max_value=255, pixels=pixels.tobytes()).write(pgm)
        _write_map_yaml(nav_yaml, pgm.name, resolution, min_x, min_y)

        projection_quality = "pcd_height_grid"
        raycast_evidence_sha256: str | None = None
        raycast_record_sha256: str | None = None
        fusion_config: dict = {
            "occupied_precedence": True,
            "endpoint_hit_requires_final_obstacle": True,
        }
        evidence_path = (
            Path(request.raycast_evidence).expanduser().resolve()
            if request.raycast_evidence is not None
            else None
        )
        evidence_record_path = (
            Path(request.raycast_record).expanduser().resolve()
            if request.raycast_record is not None
            else None
        )
        fallback_reason: str | None = None
        if evidence_path is not None and evidence_record_path is not None:
            try:
                evidence = load_evidence(evidence_path, evidence_record_path)
                fused = fuse_point_map_with_evidence(pgm, nav_yaml, evidence)
                fused.pgm.write(pgm)
                _write_map_yaml(nav_yaml, pgm.name, fused.resolution_m, fused.origin_x, fused.origin_y)
                projection_quality = "raycast_fused"
                raycast_evidence_sha256 = _sha256(evidence_path)
                raycast_record_sha256 = _sha256(evidence_record_path)
                fusion_config.update(
                    {
                        "free_threshold": evidence.free_threshold,
                        "occupied_threshold": evidence.occupied_threshold,
                        "min_observation_count": evidence.min_observation_count,
                    }
                )
            except (ValueError, RuntimeError, OSError) as exc:
                fallback_reason = f"raycast_evidence_invalid: {exc}"
        elif evidence_path is not None or evidence_record_path is not None:
            fallback_reason = "raycast_evidence_incomplete"

        parsed = PgmMap.load(pgm)
        counts, ratios = _map_cell_metrics(parsed)
        payload = {
            "schema_version": 2,
            "backend": self.backend_name,
            "projection_quality": projection_quality,
            "fallback_reason": fallback_reason,
            "created_at": datetime.now(timezone.utc).isoformat(),
            "source_pcd": str(source),
            "source_pcd_sha256": _sha256(source),
            "raycast_evidence": str(evidence_path) if evidence_path is not None else None,
            "raycast_evidence_sha256": raycast_evidence_sha256,
            "raycast_record": str(evidence_record_path) if evidence_record_path is not None else None,
            "raycast_record_sha256": raycast_record_sha256,
            "output_pgm": str(pgm),
            "output_pgm_sha256": _sha256(pgm),
            "output_yaml": str(nav_yaml),
            "output_yaml_sha256": _sha256(nav_yaml),
            "width": parsed.width,
            "height": parsed.height,
            "parameters": {
                "resolution_m": resolution,
                "min_vertical_span_m": self.min_vertical_span_m,
                "chunk_points": self.chunk_points,
                "valid_points": valid_points,
                "pcd_data_kind": layout.data_kind,
            },
            "fusion": fusion_config,
            "cell_counts": counts,
            "cell_ratios": ratios,
        }
        _atomic_json(record, payload)
        return ProjectionResult(
            self.backend_name,
            pgm,
            nav_yaml,
            record,
            projection_quality,
            fallback_reason,
        )


class RtabmapGridBackend:
    backend_name = "rtabmap_grid"

    def __init__(
        self,
        executable: str = "rtabmap_grid_projector",
        runner: Callable[[list[str]], int] | None = None,
    ) -> None:
        self.executable = str(executable)
        self._runner_injected = runner is not None
        self.runner = runner or _default_runner

    def project(self, request: ProjectionRequest) -> ProjectionResult:
        request.validate()
        if self._runner_injected:
            resolved_executable = self.executable
        else:
            resolved_executable = _resolve_executable(self.executable)
            if resolved_executable is None:
                raise RuntimeError(f"projector executable is not available: {self.executable}")

        source = Path(request.source_pcd).expanduser().resolve()
        output_dir = Path(request.output_dir).expanduser().resolve()
        output_dir.mkdir(parents=True, exist_ok=True)
        point_pgm = output_dir / "rtab_point_map.pgm"
        point_yaml = output_dir / "rtab_point_map.yaml"
        pgm = output_dir / "raw_map.pgm"
        nav_yaml = output_dir / "raw_map.yaml"
        record = output_dir / "projection_record.json"

        command = [
            resolved_executable,
            "--input", str(source),
            "--output-pgm", str(point_pgm),
            "--output-yaml", str(point_yaml),
            "--cell-size", str(float(request.resolution_m)),
            "--max-ground-angle-deg", str(float(request.max_ground_angle_deg)),
            "--normal-k", str(int(request.normal_k)),
            "--min-ground-height", str(float(request.min_ground_height_m)),
            "--max-ground-height", str(float(request.max_ground_height_m)),
            "--max-obstacle-height", str(float(request.max_obstacle_height_m)),
        ]
        return_code = int(self.runner(command))
        if return_code != 0:
            raise RuntimeError(f"rtabmap grid projector failed with exit code {return_code}")
        if (
            not point_pgm.is_file()
            or point_pgm.stat().st_size <= 0
            or not point_yaml.is_file()
            or point_yaml.stat().st_size <= 0
        ):
            raise RuntimeError("projector did not produce non-empty PGM/YAML outputs")

        projection_quality = "pcd_fallback"
        fallback_reason: str | None = "raycast_evidence_unavailable"
        raycast_evidence_sha256: str | None = None
        raycast_record_sha256: str | None = None
        fusion_config: dict = {
            "occupied_precedence": True,
            "endpoint_hit_requires_final_obstacle": True,
        }

        evidence_path = (
            Path(request.raycast_evidence).expanduser().resolve()
            if request.raycast_evidence is not None
            else None
        )
        evidence_record_path = (
            Path(request.raycast_record).expanduser().resolve()
            if request.raycast_record is not None
            else None
        )

        if evidence_path is not None and evidence_record_path is not None:
            try:
                evidence = load_evidence(evidence_path, evidence_record_path)
                fused = fuse_point_map_with_evidence(point_pgm, point_yaml, evidence)
                fused.pgm.write(pgm)
                _write_map_yaml(
                    nav_yaml,
                    pgm.name,
                    fused.resolution_m,
                    fused.origin_x,
                    fused.origin_y,
                )
                projection_quality = "raycast_fused"
                fallback_reason = None
                raycast_evidence_sha256 = _sha256(evidence_path)
                raycast_record_sha256 = _sha256(evidence_record_path)
                fusion_config.update(
                    {
                        "free_threshold": evidence.free_threshold,
                        "occupied_threshold": evidence.occupied_threshold,
                        "min_observation_count": evidence.min_observation_count,
                    }
                )
            except (ValueError, RuntimeError, OSError) as exc:
                fallback_reason = f"raycast_evidence_invalid: {exc}"
                _materialize_point_fallback(point_pgm, point_yaml, pgm, nav_yaml)
        elif evidence_path is not None or evidence_record_path is not None:
            fallback_reason = "raycast_evidence_incomplete"
            _materialize_point_fallback(point_pgm, point_yaml, pgm, nav_yaml)
        else:
            _materialize_point_fallback(point_pgm, point_yaml, pgm, nav_yaml)

        parsed = PgmMap.load(pgm)
        counts, ratios = _map_cell_metrics(parsed)
        parameters = {
            "normals_segmentation": True,
            "resolution_m": float(request.resolution_m),
            "max_ground_angle_deg": float(request.max_ground_angle_deg),
            "normal_k": int(request.normal_k),
            "min_ground_height_m": float(request.min_ground_height_m),
            "max_ground_height_m": float(request.max_ground_height_m),
            "max_obstacle_height_m": float(request.max_obstacle_height_m),
        }
        payload = {
            "schema_version": 2,
            "backend": self.backend_name,
            "projection_quality": projection_quality,
            "fallback_reason": fallback_reason,
            "created_at": datetime.now(timezone.utc).isoformat(),
            "source_pcd": str(source),
            "source_pcd_sha256": _sha256(source),
            "raycast_evidence": str(evidence_path) if evidence_path is not None else None,
            "raycast_evidence_sha256": raycast_evidence_sha256,
            "raycast_record": str(evidence_record_path) if evidence_record_path is not None else None,
            "raycast_record_sha256": raycast_record_sha256,
            "output_pgm": str(pgm),
            "output_pgm_sha256": _sha256(pgm),
            "output_yaml": str(nav_yaml),
            "output_yaml_sha256": _sha256(nav_yaml),
            "width": parsed.width,
            "height": parsed.height,
            "parameters": parameters,
            "fusion": fusion_config,
            "cell_counts": counts,
            "cell_ratios": ratios,
        }
        _atomic_json(record, payload)
        return ProjectionResult(
            self.backend_name,
            pgm,
            nav_yaml,
            record,
            projection_quality,
            fallback_reason,
        )


def load_projection_record(path: str | Path) -> dict:
    value = json.loads(Path(path).read_text(encoding="utf-8"))
    if not isinstance(value, dict) or value.get("schema_version") not in {1, 2}:
        raise ValueError("unsupported projection record")
    return value
