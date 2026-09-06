from dataclasses import dataclass
import numpy as np


@dataclass(frozen=True)
class TerrainParameters:
    resolution: float = 0.10
    max_slope_deg: float = 15.0
    unknown_slope_deg: float = 25.0
    obstacle_height_m: float = 0.25
    voxel_size: float = 0.05
    frame_id: str = "map"


@dataclass
class TerrainGrid:
    height: np.ndarray
    slope_deg: np.ndarray
    occupancy: np.ndarray  # -1 unknown, 0 free, 100 occupied
    origin_xy: tuple[float, float]
    resolution: float


def _voxel_downsample(points: np.ndarray, size: float) -> np.ndarray:
    keys = np.floor(points / size).astype(np.int64)
    _, unique = np.unique(keys, axis=0, return_index=True)
    # One representative per voxel is sufficient for terrain estimation.
    return points[np.sort(unique)]


def build_terrain_grid(points: np.ndarray, parameters: TerrainParameters) -> TerrainGrid:
    if parameters.resolution <= 0 or parameters.voxel_size <= 0:
        raise ValueError("resolution and voxel_size must be positive")
    if parameters.unknown_slope_deg < parameters.max_slope_deg:
        raise ValueError("unknown_slope_deg must be >= max_slope_deg")
    sampled = _voxel_downsample(np.asarray(points, dtype=float), parameters.voxel_size)
    origin = np.floor(sampled[:, :2].min(axis=0) / parameters.resolution) * parameters.resolution
    indices = np.floor((sampled[:, :2] - origin) / parameters.resolution).astype(int)
    width, height = indices.max(axis=0) + 1
    terrain = np.full((height, width), np.nan)
    highest = np.full((height, width), -np.inf)
    for (col, row), point in zip(indices, sampled):
        terrain[row, col] = point[2] if np.isnan(terrain[row, col]) else min(terrain[row, col], point[2])
        highest[row, col] = max(highest[row, col], point[2])
    known = np.isfinite(terrain)
    fill = np.nanmedian(terrain) if known.any() else 0.0
    smooth_height = np.where(known, terrain, fill)
    # np.gradient needs at least two samples along an axis. A one-cell-wide
    # map is valid (for example, a narrow corridor), so use zero slope there.
    gy = np.gradient(smooth_height, parameters.resolution, axis=0, edge_order=1) if height > 1 else np.zeros_like(smooth_height)
    gx = np.gradient(smooth_height, parameters.resolution, axis=1, edge_order=1) if width > 1 else np.zeros_like(smooth_height)
    slope = np.degrees(np.arctan(np.hypot(gx, gy)))
    occupancy = np.full((height, width), -1, dtype=np.int8)
    free = known & (slope < parameters.max_slope_deg)
    unknown = known & (slope >= parameters.max_slope_deg) & (slope <= parameters.unknown_slope_deg)
    high_obstacle = known & ((highest - terrain) > parameters.obstacle_height_m)
    occupancy[free & ~high_obstacle] = 0
    occupancy[unknown] = -1
    occupancy[(slope > parameters.unknown_slope_deg) | high_obstacle] = 100
    return TerrainGrid(terrain, slope, occupancy, (float(origin[0]), float(origin[1])), parameters.resolution)
