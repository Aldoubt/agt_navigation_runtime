from pathlib import Path

import pytest

from agt_field_commissioning.map_review import PgmMap
from agt_field_commissioning.raycast_free_space import RaycastConfig, RaycastEvidenceGrid
from agt_field_commissioning.raycast_fusion import fuse_point_map_with_evidence


def _write_yaml(path: Path, image: str, resolution: float, origin_x: float, origin_y: float) -> None:
    path.write_text(
        f"image: {image}\n"
        f"resolution: {resolution}\n"
        f"origin: [{origin_x}, {origin_y}, 0.0]\n"
        "negate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\nmode: trinary\n",
        encoding="utf-8",
    )


def _config() -> RaycastConfig:
    return RaycastConfig(
        resolution_m=1.0,
        free_logodds_delta=-1.0,
        hit_logodds_delta=2.0,
        free_threshold=-0.5,
        occupied_threshold=1.0,
        min_observation_count=1,
        min_ray_range_m=0.0,
        max_ray_range_m=20.0,
    )


def test_raycast_free_fills_observed_unknown_without_opening_point_obstacle(tmp_path: Path):
    point_pgm = tmp_path / "point.pgm"
    point_yaml = tmp_path / "point.yaml"
    PgmMap(3, 1, 255, bytes([205, 0, 205])).write(point_pgm)
    _write_yaml(point_yaml, point_pgm.name, 1.0, 0.0, 0.0)

    grid = RaycastEvidenceGrid(_config())
    grid.observe_ray((0.2, 0.2), (2.2, 0.2))

    result = fuse_point_map_with_evidence(point_pgm, point_yaml, grid.snapshot())

    # cell 0: observed ray passage -> free
    # cell 1: RTAB point obstacle overrides ray free
    # cell 2: ray endpoint hit alone is not enough to create final obstacle
    assert result.pgm.pixels == bytes([254, 0, 205])
    assert result.free_cells == 1
    assert result.occupied_cells == 1
    assert result.unknown_cells == 1


def test_fusion_preserves_point_ground_as_free(tmp_path: Path):
    point_pgm = tmp_path / "point.pgm"
    point_yaml = tmp_path / "point.yaml"
    PgmMap(2, 1, 255, bytes([254, 205])).write(point_pgm)
    _write_yaml(point_yaml, point_pgm.name, 1.0, 0.0, 0.0)

    grid = RaycastEvidenceGrid(_config())
    grid.observe_ray((5.2, 0.2), (6.2, 0.2))

    result = fuse_point_map_with_evidence(point_pgm, point_yaml, grid.snapshot())

    assert result.origin_x == pytest.approx(0.0)
    assert result.pgm.pixels[0] == 254


def test_fusion_builds_union_raster_for_different_xy_extents(tmp_path: Path):
    point_pgm = tmp_path / "point.pgm"
    point_yaml = tmp_path / "point.yaml"
    PgmMap(2, 1, 255, bytes([254, 0])).write(point_pgm)
    _write_yaml(point_yaml, point_pgm.name, 1.0, 1.0, 0.0)

    grid = RaycastEvidenceGrid(_config())
    grid.observe_ray((-1.8, 0.2), (0.2, 0.2))

    result = fuse_point_map_with_evidence(point_pgm, point_yaml, grid.snapshot())

    # evidence spans ix=-2..0, point map spans ix=1..2 => union ix=-2..2
    assert result.origin_x == pytest.approx(-2.0)
    assert result.origin_y == pytest.approx(0.0)
    assert result.pgm.width == 5
    assert result.pgm.height == 1
    assert result.pgm.pixels == bytes([254, 254, 205, 254, 0])


def test_fusion_rejects_resolution_mismatch(tmp_path: Path):
    point_pgm = tmp_path / "point.pgm"
    point_yaml = tmp_path / "point.yaml"
    PgmMap(1, 1, 255, bytes([205])).write(point_pgm)
    _write_yaml(point_yaml, point_pgm.name, 0.5, 0.0, 0.0)

    grid = RaycastEvidenceGrid(_config())
    grid.observe_ray((0.0, 0.0), (1.0, 0.0))

    with pytest.raises(ValueError, match="resolution"):
        fuse_point_map_with_evidence(point_pgm, point_yaml, grid.snapshot())
