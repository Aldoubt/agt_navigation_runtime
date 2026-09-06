from __future__ import annotations

import importlib.util
import json
from pathlib import Path

from agt_field_commissioning.map_review import PgmMap


ROOT = Path(__file__).resolve().parents[2]
SCRIPT = ROOT / "src" / "agt_field_commissioning" / "scripts" / "compare_commissioning_maps.py"


def _load_script_module():
    spec = importlib.util.spec_from_file_location("compare_commissioning_maps", SCRIPT)
    assert spec is not None and spec.loader is not None
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def test_map_metrics_count_classes_and_free_connectivity(tmp_path: Path):
    module = _load_script_module()
    # 4x3 map, top to bottom:
    # F F ? O
    # ? F ? O
    # F ? F O
    pgm = tmp_path / "map.pgm"
    PgmMap(
        4,
        3,
        255,
        bytes(
            [
                254, 254, 205, 0,
                205, 254, 205, 0,
                254, 205, 254, 0,
            ]
        ),
    ).write(pgm)

    metrics = module.compute_map_metrics(pgm)

    assert metrics["width"] == 4
    assert metrics["height"] == 3
    assert metrics["free_cells"] == 5
    assert metrics["occupied_cells"] == 3
    assert metrics["unknown_cells"] == 4
    assert metrics["unknown_ratio"] == 4 / 12
    assert metrics["free_component_count"] == 3
    assert metrics["largest_free_component"] == 3


def test_comparison_report_contains_point_fused_and_optional_reference(tmp_path: Path):
    module = _load_script_module()
    point = tmp_path / "point.pgm"
    fused = tmp_path / "fused.pgm"
    reference = tmp_path / "reference.pgm"
    PgmMap(3, 1, 255, bytes([205, 0, 205])).write(point)
    PgmMap(3, 1, 255, bytes([254, 0, 205])).write(fused)
    PgmMap(3, 1, 255, bytes([254, 0, 254])).write(reference)

    report = module.compare_maps(point, fused, reference)

    assert set(report["maps"]) == {"point", "fused", "reference"}
    assert report["maps"]["point"]["unknown_ratio"] == 2 / 3
    assert report["maps"]["fused"]["unknown_ratio"] == 1 / 3
    assert report["delta"]["unknown_ratio_fused_minus_point"] == -1 / 3
    assert report["delta"]["largest_free_component_fused_minus_point"] == 1


def test_cli_writes_json_report(tmp_path: Path, monkeypatch):
    module = _load_script_module()
    point = tmp_path / "point.pgm"
    fused = tmp_path / "fused.pgm"
    output = tmp_path / "report.json"
    PgmMap(2, 1, 255, bytes([205, 0])).write(point)
    PgmMap(2, 1, 255, bytes([254, 0])).write(fused)

    monkeypatch.setattr(
        "sys.argv",
        [
            "compare_commissioning_maps.py",
            "--point-map", str(point),
            "--fused-map", str(fused),
            "--json-output", str(output),
        ],
    )
    assert module.main() == 0

    payload = json.loads(output.read_text(encoding="utf-8"))
    assert payload["maps"]["point"]["unknown_cells"] == 1
    assert payload["maps"]["fused"]["free_cells"] == 1
