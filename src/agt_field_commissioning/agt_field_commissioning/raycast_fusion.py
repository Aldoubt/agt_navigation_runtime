from __future__ import annotations

from dataclasses import dataclass
import math
from pathlib import Path

import yaml

from .map_review import PgmMap
from .raycast_free_space import RaycastEvidenceSnapshot


_OCCUPIED = 0
_UNKNOWN = 205
_FREE = 254


@dataclass(frozen=True)
class FusedMapResult:
    pgm: PgmMap
    resolution_m: float
    origin_x: float
    origin_y: float
    free_cells: int
    occupied_cells: int
    unknown_cells: int

    @property
    def cell_count(self) -> int:
        return self.pgm.width * self.pgm.height

    @property
    def cell_ratios(self) -> dict[str, float]:
        total = self.cell_count
        return {
            "free": self.free_cells / total,
            "occupied": self.occupied_cells / total,
            "unknown": self.unknown_cells / total,
        }


def _aligned_index(value_m: float, resolution_m: float, label: str) -> int:
    raw = float(value_m) / float(resolution_m)
    rounded = round(raw)
    if not math.isclose(raw, rounded, abs_tol=1e-6):
        raise ValueError(f"{label} is not aligned to the map resolution")
    return int(rounded)


def _load_point_geometry(path: str | Path) -> tuple[float, float, float]:
    document = yaml.safe_load(Path(path).read_text(encoding="utf-8"))
    if not isinstance(document, dict):
        raise ValueError("point-map YAML must be a mapping")
    resolution = float(document.get("resolution", 0.0))
    origin = document.get("origin")
    if resolution <= 0.0:
        raise ValueError("point-map resolution must be positive")
    if not isinstance(origin, list) or len(origin) != 3:
        raise ValueError("point-map origin must contain x, y, yaw")
    yaw = float(origin[2])
    if not math.isclose(yaw, 0.0, abs_tol=1e-9):
        raise ValueError("rotated point maps are not supported by commissioning fusion")
    return resolution, float(origin[0]), float(origin[1])


def _point_state(
    pgm: PgmMap,
    x: int,
    y_from_bottom: int,
) -> str:
    row_from_top = pgm.height - 1 - int(y_from_bottom)
    value = pgm.pixels[row_from_top * pgm.width + int(x)]
    if value == _OCCUPIED:
        return "occupied"
    if value == _FREE:
        return "free"
    return "unknown"


def fuse_point_map_with_evidence(
    point_pgm_path: str | Path,
    point_yaml_path: str | Path,
    evidence: RaycastEvidenceSnapshot,
) -> FusedMapResult:
    point_pgm = PgmMap.load(point_pgm_path)
    point_resolution, point_origin_x, point_origin_y = _load_point_geometry(point_yaml_path)
    if not math.isclose(point_resolution, evidence.resolution_m, rel_tol=0.0, abs_tol=1e-9):
        raise ValueError(
            "raycast evidence resolution does not match RTAB point-map resolution"
        )

    resolution = point_resolution
    point_origin_ix = _aligned_index(point_origin_x, resolution, "point-map origin x")
    point_origin_iy = _aligned_index(point_origin_y, resolution, "point-map origin y")
    point_max_ix = point_origin_ix + point_pgm.width - 1
    point_max_iy = point_origin_iy + point_pgm.height - 1

    evidence_max_ix = evidence.origin_ix + evidence.width - 1
    evidence_max_iy = evidence.origin_iy + evidence.height - 1

    union_origin_ix = min(point_origin_ix, evidence.origin_ix)
    union_origin_iy = min(point_origin_iy, evidence.origin_iy)
    union_max_ix = max(point_max_ix, evidence_max_ix)
    union_max_iy = max(point_max_iy, evidence_max_iy)
    width = union_max_ix - union_origin_ix + 1
    height = union_max_iy - union_origin_iy + 1
    pixels = bytearray([_UNKNOWN] * (width * height))

    free_cells = 0
    occupied_cells = 0
    unknown_cells = 0

    for iy in range(union_origin_iy, union_max_iy + 1):
        for ix in range(union_origin_ix, union_max_ix + 1):
            point_state = "unknown"
            if (
                point_origin_ix <= ix <= point_max_ix
                and point_origin_iy <= iy <= point_max_iy
            ):
                point_state = _point_state(
                    point_pgm,
                    ix - point_origin_ix,
                    iy - point_origin_iy,
                )
            ray_state = evidence.classify_cell(ix, iy)

            if point_state == "occupied":
                value = _OCCUPIED
                occupied_cells += 1
            elif point_state == "free" or ray_state == "free":
                value = _FREE
                free_cells += 1
            else:
                # A ray endpoint/hit alone is observation evidence, not final
                # occupied authority. The finalized RTAB obstacle model must
                # support occupied output so transient foliage cannot punch
                # false barriers into the navigation map.
                value = _UNKNOWN
                unknown_cells += 1

            local_x = ix - union_origin_ix
            local_y = iy - union_origin_iy
            row_from_top = height - 1 - local_y
            pixels[row_from_top * width + local_x] = value

    return FusedMapResult(
        pgm=PgmMap(width=width, height=height, max_value=255, pixels=bytes(pixels)),
        resolution_m=resolution,
        origin_x=union_origin_ix * resolution,
        origin_y=union_origin_iy * resolution,
        free_cells=free_cells,
        occupied_cells=occupied_cells,
        unknown_cells=unknown_cells,
    )
