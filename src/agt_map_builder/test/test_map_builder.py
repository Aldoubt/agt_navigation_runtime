from pathlib import Path
import hashlib
import json
import sys

import numpy as np
import pytest
import yaml

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "src/agt_map_builder"))

from agt_map_builder.cloud_loader import load_pcd  # noqa: E402
from agt_map_builder.map_exporter import export_map_package  # noqa: E402
from agt_map_builder.terrain_analysis import (  # noqa: E402
    TerrainParameters,
    build_terrain_grid,
)


def write_pcd(path: Path, points: np.ndarray) -> None:
    rows = "\n".join("%.3f %.3f %.3f" % tuple(p) for p in points)
    path.write_text(
        "VERSION .7\nFIELDS x y z\nSIZE 4 4 4\nTYPE F F F\nCOUNT 1 1 1\n"
        f"WIDTH {len(points)}\nHEIGHT 1\nPOINTS {len(points)}\nDATA ascii\n{rows}\n",
        encoding="ascii",
    )


def test_pcd_reading_extracts_xyz_and_ignores_nan(tmp_path):
    pcd = tmp_path / "cloud.pcd"
    write_pcd(pcd, np.array([[0, 0, 1], [1, 0, 2], [np.nan, 0, 1]]))
    points = load_pcd(pcd)
    assert points.shape == (2, 3)
    assert np.allclose(points[1], [1, 0, 2])


def test_binary_pcd_reading(tmp_path):
    pcd = tmp_path / "cloud_binary.pcd"
    pcd.write_bytes(
        b"VERSION .7\nFIELDS x y z\nSIZE 4 4 4\nTYPE F F F\nCOUNT 1 1 1\n"
        b"WIDTH 2\nHEIGHT 1\nPOINTS 2\nDATA binary\n"
        + np.array([(1, 2, 3), (4, 5, 6)], dtype=[("x", "<f4"), ("y", "<f4"), ("z", "<f4")]).tobytes()
    )
    assert np.allclose(load_pcd(pcd), [[1, 2, 3], [4, 5, 6]])


def test_grid_has_height_slope_and_terrain_classification():
    # A 10 degree ramp: free below 15 degrees, and a steep discontinuity.
    x = np.repeat(np.arange(4, dtype=float), 4)
    y = np.tile(np.arange(4, dtype=float), 4)
    z = 0.1763 * x
    points = np.column_stack((x, y, z))
    grid = build_terrain_grid(points, TerrainParameters(resolution=1, voxel_size=0.1))
    assert grid.height.shape == (4, 4)
    assert np.nanmax(grid.slope_deg) == pytest.approx(10, abs=1)
    assert np.all(grid.occupancy == 0)


def test_steep_grid_is_occupied_and_unobserved_is_unknown():
    points = np.array([[0, 0, 0], [0, 1, 0], [1, 0, 1], [1, 1, 1]], dtype=float)
    grid = build_terrain_grid(points, TerrainParameters(resolution=1, voxel_size=0.1))
    assert np.all(grid.occupancy == 100)


def test_export_is_nav2_compatible_and_hash_covers_map_files(tmp_path):
    points = np.array([[0, 0, 0], [0, 1, 0], [1, 0, 0], [1, 1, 0]], dtype=float)
    params = TerrainParameters(resolution=1, voxel_size=0.1, frame_id="map")
    package = tmp_path / "inspection_maps" / "demo"
    export_map_package(build_terrain_grid(points, params), package, "cloud.pcd", params)
    assert (package / "map.pgm").read_bytes().startswith(b"P5\n")
    map_config = yaml.safe_load((package / "map.yaml").read_text())
    assert map_config["image"] == "map.pgm"
    assert map_config["resolution"] == 1
    manifest = json.loads((package / "manifest.json").read_text())
    expected = hashlib.sha256((package / "map.pgm").read_bytes() + (package / "map.yaml").read_bytes()).hexdigest()
    assert manifest["hash"]["sha256"] == expected
    metadata = yaml.safe_load((package / "metadata.yaml").read_text())
    assert metadata["frame_id"] == "map"
