import importlib.util
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
SCRIPT = ROOT / "src" / "agt_field_commissioning" / "scripts" / "project_navigation_map.py"


def _write_mapping_run(runtime_dir: Path) -> None:
    mapping = runtime_dir / "commissioning" / "orchard" / "run_001" / "mapping"
    mapping.mkdir(parents=True)
    (mapping / "localization_map.pcd").write_text(
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
    (mapping / "localization_map.processing.yaml").write_text(
        "schema_version: 1\nstatus: finalized\n",
        encoding="utf-8",
    )


def test_project_navigation_map_cli_materializes_editable_review(tmp_path, capsys):
    assert SCRIPT.is_file(), "field workflow needs an installed PCD -> Nav2 map CLI"
    spec = importlib.util.spec_from_file_location("project_navigation_map", SCRIPT)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)

    runtime_dir = tmp_path / "runtime"
    _write_mapping_run(runtime_dir)

    rc = module.main(
        [
            "--runtime-dir",
            str(runtime_dir),
            "--site-id",
            "orchard",
            "--run-id",
            "run_001",
            "--resolution",
            "0.10",
            "--min-vertical-span",
            "0.15",
            "--chunk-points",
            "2",
        ]
    )
    assert rc == 0

    output = json.loads(capsys.readouterr().out)
    assert output["status"] == "MAP_READY"
    assert output["backend"] == "lightweight_pcd_grid"
    assert output["source_pcd"].endswith("mapping/localization_map.pcd")
    assert output["projection_yaml"].endswith("projection/raw_map.yaml")
    assert output["projection_pgm"].endswith("projection/raw_map.pgm")
    assert output["review_yaml"].endswith("map_review/reviewed_map.yaml")
    assert output["review_pgm"].endswith("map_review/reviewed_map.pgm")
    assert Path(output["projection_yaml"]).is_file()
    assert Path(output["projection_pgm"]).is_file()
    assert Path(output["review_yaml"]).is_file()
    assert Path(output["review_pgm"]).is_file()
    assert Path(output["projection_record"]).is_file()


def test_project_navigation_map_cli_is_lightweight_only():
    assert SCRIPT.is_file(), "field workflow needs an installed PCD -> Nav2 map CLI"
    text = SCRIPT.read_text(encoding="utf-8")
    assert "LightweightPcdGridBackend" in text
    assert "RtabmapGridBackend" not in text
    assert "rtabmap_grid_projector" not in text
