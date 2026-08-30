from __future__ import annotations

import json
from pathlib import Path

import pytest

from agt_field_commissioning.raycast_free_space import (
    RaycastConfig,
    RaycastEvidenceGrid,
    grid_ray_cells,
    load_evidence,
    save_evidence,
)


def test_grid_ray_traverses_integer_cells_in_order():
    assert grid_ray_cells((0, 0), (3, 0)) == [(0, 0), (1, 0), (2, 0), (3, 0)]
    assert grid_ray_cells((0, 0), (3, 3)) == [(0, 0), (1, 1), (2, 2), (3, 3)]
    assert grid_ray_cells((3, 1), (0, 1)) == [(3, 1), (2, 1), (1, 1), (0, 1)]


def test_observe_ray_marks_passage_free_endpoint_hit_and_unseen_unknown():
    config = RaycastConfig(
        resolution_m=1.0,
        free_logodds_delta=-1.0,
        hit_logodds_delta=2.0,
        free_threshold=-0.5,
        occupied_threshold=1.0,
        min_observation_count=1,
    )
    grid = RaycastEvidenceGrid(config)

    assert grid.observe_ray((0.2, 0.2), (3.2, 0.2)) is True

    assert grid.classify_world((0.2, 0.2)) == "free"
    assert grid.classify_world((1.2, 0.2)) == "free"
    assert grid.classify_world((2.2, 0.2)) == "free"
    assert grid.classify_world((3.2, 0.2)) == "occupied"
    assert grid.classify_world((9.2, 9.2)) == "unknown"


def test_log_odds_are_clamped_and_minimum_observation_count_is_respected():
    config = RaycastConfig(
        resolution_m=1.0,
        free_logodds_delta=-2.0,
        hit_logodds_delta=3.0,
        min_logodds=-4.0,
        max_logodds=4.0,
        free_threshold=-1.0,
        occupied_threshold=1.0,
        min_observation_count=2,
    )
    grid = RaycastEvidenceGrid(config)

    grid.observe_ray((0.2, 0.2), (2.2, 0.2))
    assert grid.classify_world((1.2, 0.2)) == "unknown"
    assert grid.classify_world((2.2, 0.2)) == "unknown"

    for _ in range(5):
        grid.observe_ray((0.2, 0.2), (2.2, 0.2))

    free = grid.cell_evidence(1, 0)
    hit = grid.cell_evidence(2, 0)
    assert free.log_odds == pytest.approx(-4.0)
    assert hit.log_odds == pytest.approx(4.0)
    assert free.observation_count == 6
    assert hit.observation_count == 6
    assert grid.classify_world((1.2, 0.2)) == "free"
    assert grid.classify_world((2.2, 0.2)) == "occupied"


def test_observe_ray_rejects_nonfinite_and_out_of_range_endpoints():
    config = RaycastConfig(
        resolution_m=1.0,
        min_ray_range_m=1.0,
        max_ray_range_m=5.0,
        min_observation_count=1,
    )
    grid = RaycastEvidenceGrid(config)

    assert grid.observe_ray((0.0, 0.0), (0.5, 0.0)) is False
    assert grid.observe_ray((0.0, 0.0), (6.0, 0.0)) is False
    assert grid.observe_ray((0.0, 0.0), (float("nan"), 0.0)) is False
    assert grid.stats.accepted_rays == 0
    assert grid.stats.rejected_range == 2
    assert grid.stats.rejected_nonfinite == 1


def test_evidence_round_trip_preserves_geometry_values_record_and_checksum(tmp_path: Path):
    config = RaycastConfig(
        frame_id="camera_init",
        resolution_m=1.0,
        free_logodds_delta=-1.0,
        hit_logodds_delta=2.0,
        free_threshold=-0.5,
        occupied_threshold=1.0,
        min_observation_count=1,
    )
    grid = RaycastEvidenceGrid(config)
    grid.observe_ray((-1.2, 0.2), (2.2, 0.2))
    grid.observe_ray((-1.2, 1.2), (2.2, 1.2))

    artifact = save_evidence(
        grid,
        tmp_path / "free_space_evidence.bin",
        tmp_path / "raycast_record.json",
    )
    loaded = load_evidence(artifact.binary, artifact.record)
    record = json.loads(artifact.record.read_text(encoding="utf-8"))

    assert loaded.frame_id == "camera_init"
    assert loaded.resolution_m == pytest.approx(1.0)
    assert loaded.origin_ix == -2
    assert loaded.origin_iy == 0
    assert loaded.width == 5
    assert loaded.height == 2
    assert loaded.classify_cell(-1, 0) == "free"
    assert loaded.classify_cell(2, 0) == "occupied"
    assert record["schema_version"] == 1
    assert record["binary_sha256"].startswith("sha256:")
    assert record["stats"]["accepted_rays"] == 2


def test_load_evidence_rejects_corrupt_binary_checksum(tmp_path: Path):
    grid = RaycastEvidenceGrid(
        RaycastConfig(
            resolution_m=1.0,
            free_threshold=-0.5,
            occupied_threshold=0.5,
            min_observation_count=1,
        )
    )
    grid.observe_ray((0.0, 0.0), (2.0, 0.0))
    artifact = save_evidence(
        grid,
        tmp_path / "free_space_evidence.bin",
        tmp_path / "raycast_record.json",
    )
    artifact.binary.write_bytes(artifact.binary.read_bytes() + b"corrupt")

    with pytest.raises(ValueError, match="checksum"):
        load_evidence(artifact.binary, artifact.record)


def test_load_evidence_rejects_unsupported_magic(tmp_path: Path):
    binary = tmp_path / "free_space_evidence.bin"
    record = tmp_path / "raycast_record.json"
    binary.write_bytes(b"BADMAGIC")
    record.write_text(
        json.dumps(
            {
                "schema_version": 1,
                "binary_sha256": "sha256:deadbeef",
            }
        ),
        encoding="utf-8",
    )

    with pytest.raises(ValueError):
        load_evidence(binary, record)
