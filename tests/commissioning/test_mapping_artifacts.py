import hashlib
import json
from pathlib import Path

import pytest

from agt_field_commissioning.mapping_artifacts import (
    finalize_mapping_run,
    prepare_mapping_run,
)
from agt_field_commissioning.raycast_free_space import (
    RaycastConfig,
    RaycastEvidenceGrid,
    save_evidence,
)


def _write_ready_mapping(mapping_dir: Path) -> None:
    mapping_dir.mkdir(parents=True, exist_ok=True)
    (mapping_dir / "localization_map.pcd").write_bytes(b"pcd-data\n")
    (mapping_dir / "localization_map.processing.yaml").write_text(
        "schema_version: 1\nstate: ready\nmap_file: localization_map.pcd\n",
        encoding="utf-8",
    )


def _write_raycast_observation(observation_dir: Path):
    grid = RaycastEvidenceGrid(
        RaycastConfig(
            resolution_m=0.1,
            free_logodds_delta=-1.0,
            hit_logodds_delta=2.0,
            free_threshold=-0.5,
            occupied_threshold=1.0,
            min_observation_count=1,
            min_ray_range_m=0.0,
            max_ray_range_m=10.0,
        )
    )
    grid.observe_ray((0.0, 0.0), (1.0, 0.0))
    return save_evidence(
        grid,
        observation_dir / "free_space_evidence.bin",
        observation_dir / "raycast_record.json",
    )


def test_prepare_mapping_run_uses_deterministic_unique_path(tmp_path):
    paths = prepare_mapping_run(tmp_path, "greenhouse_01", "20260829T150000")

    assert paths.run_root == tmp_path / "commissioning" / "greenhouse_01" / "20260829T150000"
    assert paths.mapping_dir == paths.run_root / "mapping"
    assert paths.observation_dir == paths.run_root / "observation"
    assert paths.evidence_dir == paths.run_root / "evidence"
    assert paths.mapping_dir.is_dir()
    assert paths.observation_dir.is_dir()
    assert paths.evidence_dir.is_dir()


@pytest.mark.parametrize("value", ["", "../escape", "a/b", ".", "..", " space", "x" * 65])
def test_prepare_mapping_run_rejects_unsafe_identity_tokens(tmp_path, value):
    with pytest.raises(ValueError):
        prepare_mapping_run(tmp_path, value, "run_01")

    with pytest.raises(ValueError):
        prepare_mapping_run(tmp_path, "site_01", value)


def test_prepare_mapping_run_refuses_populated_mapping_directory(tmp_path):
    mapping_dir = tmp_path / "commissioning" / "site_01" / "run_01" / "mapping"
    mapping_dir.mkdir(parents=True)
    (mapping_dir / "old.pcd").write_bytes(b"old")

    with pytest.raises(RuntimeError, match="refusing to reuse populated"):
        prepare_mapping_run(tmp_path, "site_01", "run_01")


def test_finalize_mapping_run_requires_shutdown_artifacts(tmp_path):
    paths = prepare_mapping_run(tmp_path, "site_01", "run_01")

    with pytest.raises(RuntimeError, match="localization_map.pcd"):
        finalize_mapping_run(tmp_path, "site_01", "run_01")

    paths.localization_map.write_bytes(b"")
    paths.processing_record.write_text("state: ready\n", encoding="utf-8")
    with pytest.raises(RuntimeError, match="empty"):
        finalize_mapping_run(tmp_path, "site_01", "run_01")


def test_finalize_mapping_run_rejects_leftover_tmp_files(tmp_path):
    paths = prepare_mapping_run(tmp_path, "site_01", "run_01")
    _write_ready_mapping(paths.mapping_dir)
    (paths.mapping_dir / "localization_map.pcd.tmp").write_bytes(b"partial")

    with pytest.raises(RuntimeError, match="temporary"):
        finalize_mapping_run(tmp_path, "site_01", "run_01")


def test_finalize_mapping_run_writes_hash_evidence_atomically(tmp_path):
    paths = prepare_mapping_run(tmp_path, "site_01", "run_01")
    _write_ready_mapping(paths.mapping_dir)

    evidence = finalize_mapping_run(tmp_path, "site_01", "run_01")

    expected_pcd_sha = hashlib.sha256(paths.localization_map.read_bytes()).hexdigest()
    expected_record_sha = hashlib.sha256(paths.processing_record.read_bytes()).hexdigest()
    assert evidence["state"] == "READY"
    assert evidence["site_id"] == "site_01"
    assert evidence["run_id"] == "run_01"
    assert evidence["artifacts"]["localization_map.pcd"]["sha256"] == expected_pcd_sha
    assert evidence["artifacts"]["localization_map.processing.yaml"]["sha256"] == expected_record_sha
    assert "observation" not in evidence

    metadata_path = paths.evidence_dir / "mapping_metadata.json"
    assert json.loads(metadata_path.read_text(encoding="utf-8")) == evidence
    assert not (paths.evidence_dir / "mapping_metadata.json.tmp").exists()


def test_finalize_mapping_run_records_valid_optional_raycast_observation(tmp_path):
    paths = prepare_mapping_run(tmp_path, "site_01", "run_01")
    _write_ready_mapping(paths.mapping_dir)
    artifact = _write_raycast_observation(paths.observation_dir)

    evidence = finalize_mapping_run(tmp_path, "site_01", "run_01")

    observation = evidence["observation"]
    assert observation["state"] == "READY"
    assert observation["projection_quality_candidate"] == "raycast_fused"
    assert observation["free_space_evidence.bin"]["sha256"] == hashlib.sha256(
        artifact.binary.read_bytes()
    ).hexdigest()
    assert observation["raycast_record.json"]["sha256"] == hashlib.sha256(
        artifact.record.read_bytes()
    ).hexdigest()
    assert observation["frame_id"] == "camera_init"
    assert observation["resolution_m"] == pytest.approx(0.1)
    assert observation["stats"]["accepted_rays"] == 1


def test_finalize_mapping_run_marks_corrupt_optional_raycast_observation_without_rejecting_pcd(tmp_path):
    paths = prepare_mapping_run(tmp_path, "site_01", "run_01")
    _write_ready_mapping(paths.mapping_dir)
    artifact = _write_raycast_observation(paths.observation_dir)
    artifact.binary.write_bytes(artifact.binary.read_bytes() + b"corrupt")

    evidence = finalize_mapping_run(tmp_path, "site_01", "run_01")

    assert evidence["state"] == "READY"
    assert evidence["observation"]["state"] == "INVALID"
    assert evidence["observation"]["projection_quality_candidate"] == "pcd_fallback"
    assert "checksum" in evidence["observation"]["reason"]
