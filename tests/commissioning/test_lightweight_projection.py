from pathlib import Path
import struct

from agt_field_commissioning.map_review import PgmMap
from agt_field_commissioning.projection import (
    LightweightPcdGridBackend,
    ProjectionRequest,
    load_projection_record,
)
from agt_field_commissioning.service import CommissioningService


def _write_ascii_pcd(path: Path) -> None:
    path.write_text(
        "# .PCD v0.7\n"
        "VERSION 0.7\n"
        "FIELDS x y z intensity\n"
        "SIZE 4 4 4 4\n"
        "TYPE F F F F\n"
        "COUNT 1 1 1 1\n"
        "WIDTH 5\n"
        "HEIGHT 1\n"
        "POINTS 5\n"
        "DATA ascii\n"
        "0.00 0.00 0.00 1\n"
        "0.02 0.01 0.45 1\n"
        "0.20 0.00 0.00 1\n"
        "0.21 0.01 0.02 1\n"
        "0.40 0.00 0.00 1\n",
        encoding="ascii",
    )


def _write_binary_fast_livo_style_pcd(path: Path) -> None:
    points = [
        (0.00, 0.00, 0.00, 1.0, 0.0, 0.0, 1.0, 0.0),
        (0.02, 0.01, 0.45, 1.0, 0.0, 0.0, 1.0, 0.0),
        (0.20, 0.00, 0.00, 1.0, 0.0, 0.0, 1.0, 0.0),
        (0.21, 0.01, 0.02, 1.0, 0.0, 0.0, 1.0, 0.0),
        (0.40, 0.00, 0.00, 1.0, 0.0, 0.0, 1.0, 0.0),
    ]
    header = (
        "# .PCD v0.7\n"
        "VERSION 0.7\n"
        "FIELDS x y z intensity normal_x normal_y normal_z curvature\n"
        "SIZE 4 4 4 4 4 4 4 4\n"
        "TYPE F F F F F F F F\n"
        "COUNT 1 1 1 1 1 1 1 1\n"
        f"WIDTH {len(points)}\n"
        "HEIGHT 1\n"
        f"POINTS {len(points)}\n"
        "DATA binary\n"
    ).encode("ascii")
    payload = b"".join(struct.pack("<8f", *point) for point in points)
    path.write_bytes(header + payload)


def _assert_projection_has_obstacle_and_free_space(source: Path, output_dir: Path) -> None:
    result = LightweightPcdGridBackend(
        min_vertical_span_m=0.15,
        chunk_points=2,
    ).project(
        ProjectionRequest(
            source_pcd=source,
            output_dir=output_dir,
            resolution_m=0.10,
        )
    )

    assert result.backend == "lightweight_pcd_grid"
    assert result.projection_quality == "pcd_height_grid"
    assert result.fallback_reason is None
    assert result.pgm.is_file()
    assert result.yaml.is_file()
    parsed = PgmMap.load(result.pgm)
    assert 0 in parsed.pixels
    assert 254 in parsed.pixels

    record = load_projection_record(result.record)
    assert record["backend"] == "lightweight_pcd_grid"
    assert record["parameters"]["min_vertical_span_m"] == 0.15
    assert record["cell_counts"]["occupied"] >= 1
    assert record["cell_counts"]["free"] >= 1


def test_lightweight_projection_builds_nav2_map_without_rtabmap(tmp_path: Path) -> None:
    source = tmp_path / "localization_map.pcd"
    _write_ascii_pcd(source)
    _assert_projection_has_obstacle_and_free_space(source, tmp_path / "projection")


def test_lightweight_projection_streams_binary_fast_livo_style_pcd(tmp_path: Path) -> None:
    source = tmp_path / "localization_map_binary.pcd"
    _write_binary_fast_livo_style_pcd(source)
    _assert_projection_has_obstacle_and_free_space(source, tmp_path / "binary_projection")


def test_commissioning_service_defaults_to_lightweight_projection(tmp_path: Path) -> None:
    service = CommissioningService(
        runtime_dir=tmp_path / "runtime",
        sites_root=tmp_path / "sites",
        state_root=tmp_path / "state",
        vehicle_profile=tmp_path / "vehicle.yaml",
        vehicle_schema=tmp_path / "vehicle.schema.json",
        site_schema=tmp_path / "site.schema.json",
    )

    assert service.projection_backend.backend_name == "lightweight_pcd_grid"
