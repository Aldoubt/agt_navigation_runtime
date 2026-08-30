from pathlib import Path

import os
import pytest

from agt_field_commissioning.raycast_free_space import (
    RaycastConfig,
    RaycastEvidenceGrid,
    save_evidence,
)
from agt_field_commissioning.projection import (
    ProjectionRequest,
    RtabmapGridBackend,
    _resolve_executable,
    load_projection_record,
)


def _write_source_pcd(path: Path) -> None:
    path.write_text("# .PCD v0.7\nDATA ascii\n0 0 0\n", encoding="ascii")


def _runner_writing_outputs(calls: list[list[str]], pixels: bytes = bytes([254, 0])):
    def runner(command: list[str]) -> int:
        calls.append(command)
        pgm = Path(command[command.index("--output-pgm") + 1])
        yaml = Path(command[command.index("--output-yaml") + 1])
        pgm.parent.mkdir(parents=True, exist_ok=True)
        pgm.write_bytes(f"P5\n{len(pixels)} 1\n255\n".encode("ascii") + pixels)
        yaml.write_text(
            f"image: {pgm.name}\nresolution: 0.05\norigin: [0.0, 0.0, 0.0]\n"
            "negate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\nmode: trinary\n",
            encoding="utf-8",
        )
        return 0

    return runner


def test_projection_builds_global_lio_safe_rtabmap_grid_command_and_fallback_record(tmp_path: Path) -> None:
    source = tmp_path / "map.pcd"
    _write_source_pcd(source)
    output = tmp_path / "projection"
    calls: list[list[str]] = []

    backend = RtabmapGridBackend(
        executable="/opt/agt/bin/rtabmap_grid_projector",
        runner=_runner_writing_outputs(calls),
    )
    result = backend.project(
        ProjectionRequest(
            source_pcd=source,
            output_dir=output,
            resolution_m=0.05,
            max_ground_angle_deg=35.0,
            normal_k=20,
        )
    )

    assert result.backend == "rtabmap_grid"
    assert result.projection_quality == "pcd_fallback"
    assert result.fallback_reason == "raycast_evidence_unavailable"
    assert result.pgm.is_file()
    assert result.yaml.is_file()
    assert result.record.is_file()
    command = calls[0]
    assert command[0] == "/opt/agt/bin/rtabmap_grid_projector"
    assert command[command.index("--input") + 1] == str(source.resolve())
    assert command[command.index("--max-ground-angle-deg") + 1] == "35.0"
    assert command[command.index("--normal-k") + 1] == "20"
    assert command[command.index("--min-ground-height") + 1] == "0.0"
    assert command[command.index("--max-ground-height") + 1] == "0.0"
    assert command[command.index("--max-obstacle-height") + 1] == "0.0"

    record = load_projection_record(result.record)
    assert record["schema_version"] == 2
    assert record["backend"] == "rtabmap_grid"
    assert record["projection_quality"] == "pcd_fallback"
    assert record["fallback_reason"] == "raycast_evidence_unavailable"
    assert record["source_pcd_sha256"].startswith("sha256:")
    assert record["output_pgm_sha256"].startswith("sha256:")
    assert record["output_yaml_sha256"].startswith("sha256:")
    assert record["parameters"]["normals_segmentation"] is True
    assert record["parameters"]["max_ground_angle_deg"] == 35.0
    assert record["parameters"]["min_ground_height_m"] == 0.0
    assert record["parameters"]["max_ground_height_m"] == 0.0
    assert record["parameters"]["max_obstacle_height_m"] == 0.0
    assert record["cell_counts"] == {"free": 1, "occupied": 1, "unknown": 0}
    assert record["cell_ratios"]["free"] == pytest.approx(0.5)
    assert record["fusion"]["occupied_precedence"] is True
    assert record["fusion"]["endpoint_hit_requires_final_obstacle"] is True


def test_projection_uses_valid_run_scoped_raycast_evidence(tmp_path: Path) -> None:
    source = tmp_path / "map.pcd"
    _write_source_pcd(source)
    calls: list[list[str]] = []

    config = RaycastConfig(
        resolution_m=0.05,
        free_logodds_delta=-1.0,
        hit_logodds_delta=2.0,
        free_threshold=-0.5,
        occupied_threshold=1.0,
        min_observation_count=1,
        min_ray_range_m=0.0,
        max_ray_range_m=10.0,
    )
    grid = RaycastEvidenceGrid(config)
    grid.observe_ray((0.01, 0.01), (0.11, 0.01))
    artifact = save_evidence(
        grid,
        tmp_path / "observation/free_space_evidence.bin",
        tmp_path / "observation/raycast_record.json",
    )

    backend = RtabmapGridBackend(
        executable="/opt/agt/bin/rtabmap_grid_projector",
        runner=_runner_writing_outputs(calls, pixels=bytes([205, 0, 205])),
    )
    result = backend.project(
        ProjectionRequest(
            source_pcd=source,
            output_dir=tmp_path / "projection",
            resolution_m=0.05,
            raycast_evidence=artifact.binary,
            raycast_record=artifact.record,
        )
    )

    assert result.projection_quality == "raycast_fused"
    assert result.fallback_reason is None
    record = load_projection_record(result.record)
    assert record["projection_quality"] == "raycast_fused"
    assert record["fallback_reason"] is None
    assert record["raycast_evidence_sha256"].startswith("sha256:")
    assert record["cell_counts"]["free"] >= 1
    assert record["cell_counts"]["occupied"] == 1


def test_projection_falls_back_when_raycast_evidence_is_corrupt(tmp_path: Path) -> None:
    source = tmp_path / "map.pcd"
    _write_source_pcd(source)
    calls: list[list[str]] = []

    grid = RaycastEvidenceGrid(
        RaycastConfig(
            resolution_m=0.05,
            free_threshold=-0.5,
            occupied_threshold=0.5,
            min_observation_count=1,
            min_ray_range_m=0.0,
            max_ray_range_m=10.0,
        )
    )
    grid.observe_ray((0.0, 0.0), (0.1, 0.0))
    artifact = save_evidence(
        grid,
        tmp_path / "observation/free_space_evidence.bin",
        tmp_path / "observation/raycast_record.json",
    )
    artifact.binary.write_bytes(artifact.binary.read_bytes() + b"corrupt")

    backend = RtabmapGridBackend(
        executable="/opt/agt/bin/rtabmap_grid_projector",
        runner=_runner_writing_outputs(calls),
    )
    result = backend.project(
        ProjectionRequest(
            source_pcd=source,
            output_dir=tmp_path / "projection",
            raycast_evidence=artifact.binary,
            raycast_record=artifact.record,
        )
    )

    assert result.projection_quality == "pcd_fallback"
    assert "checksum" in (result.fallback_reason or "")
    record = load_projection_record(result.record)
    assert record["projection_quality"] == "pcd_fallback"
    assert "checksum" in (record["fallback_reason"] or "")


def test_projection_accepts_explicitly_disabled_absolute_height_gates(tmp_path: Path) -> None:
    source = tmp_path / "map.pcd"
    _write_source_pcd(source)
    calls: list[list[str]] = []
    backend = RtabmapGridBackend(executable="/opt/agt/bin/rtabmap_grid_projector", runner=_runner_writing_outputs(calls))

    backend.project(
        ProjectionRequest(
            source_pcd=source,
            output_dir=tmp_path / "projection",
            min_ground_height_m=0.0,
            max_ground_height_m=0.0,
            max_obstacle_height_m=0.0,
        )
    )

    assert calls


def test_projector_passes_max_ground_angle_to_rtabmap_in_degrees() -> None:
    root = Path(__file__).resolve().parents[2]
    source = (root / "src/agt_field_commissioning/src/rtabmap_grid_projector.cpp").read_text(encoding="utf-8")
    assert 'parameters["Grid/MaxGroundAngle"] = std::to_string(options.max_ground_angle_deg);' in source
    assert "options.max_ground_angle_deg * M_PI / 180.0" not in source


def test_projector_uses_finalized_global_lio_segmentation_policy() -> None:
    root = Path(__file__).resolve().parents[2]
    source = (root / "src/agt_field_commissioning/src/rtabmap_grid_projector.cpp").read_text(encoding="utf-8")

    assert 'parameters["Grid/PreVoxelFiltering"] = "false";' in source
    assert 'parameters["Grid/MinClusterSize"] = "1";' in source
    assert 'parameters["Grid/ClusterRadius"] = "0.15";' in source
    assert 'parameters["Grid/FlatObstacleDetected"] = "false";' in source


def test_projection_resolves_projector_from_ros_ament_prefix(tmp_path: Path, monkeypatch) -> None:
    prefix = tmp_path / "install" / "agt_field_commissioning"
    executable = prefix / "lib" / "agt_field_commissioning" / "rtabmap_grid_projector"
    executable.parent.mkdir(parents=True)
    executable.write_text("#!/bin/sh\nexit 0\n", encoding="utf-8")
    executable.chmod(0o755)

    monkeypatch.setenv("PATH", "")
    monkeypatch.setenv("AMENT_PREFIX_PATH", str(prefix))

    assert _resolve_executable("rtabmap_grid_projector") == str(executable.resolve())


def test_projection_fails_closed_when_backend_or_output_is_missing(tmp_path: Path) -> None:
    source = tmp_path / "map.pcd"
    _write_source_pcd(source)
    request = ProjectionRequest(source_pcd=source, output_dir=tmp_path / "out")

    backend = RtabmapGridBackend(executable="/missing/rtabmap_grid_projector")
    with pytest.raises(RuntimeError, match="projector executable"):
        backend.project(request)

    backend = RtabmapGridBackend(executable="/bin/true", runner=lambda command: 0)
    with pytest.raises(RuntimeError, match="did not produce"):
        backend.project(request)


def test_projection_rejects_invalid_slope_parameters_before_runner(tmp_path: Path) -> None:
    source = tmp_path / "map.pcd"
    _write_source_pcd(source)
    called = False

    def runner(command: list[str]) -> int:
        nonlocal called
        called = True
        return 0

    backend = RtabmapGridBackend(executable="/bin/true", runner=runner)
    with pytest.raises(ValueError, match="max_ground_angle_deg"):
        backend.project(
            ProjectionRequest(
                source_pcd=source,
                output_dir=tmp_path / "out",
                max_ground_angle_deg=95.0,
            )
        )
    assert called is False
