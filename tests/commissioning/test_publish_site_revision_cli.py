import importlib.util
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
SCRIPT = ROOT / "src" / "agt_field_commissioning" / "scripts" / "publish_site_revision.py"


def _prepare_reviewed_run(runtime_dir: Path) -> None:
    run_root = runtime_dir / "commissioning" / "orchard" / "run_001"
    mapping = run_root / "mapping"
    review = run_root / "map_review"
    projection = run_root / "projection"
    mapping.mkdir(parents=True)
    review.mkdir(parents=True)
    projection.mkdir(parents=True)

    (mapping / "localization_map.pcd").write_text(
        "# .PCD v0.7\nFIELDS x y z\nSIZE 4 4 4\nTYPE F F F\nCOUNT 1 1 1\n"
        "WIDTH 1\nHEIGHT 1\nPOINTS 1\nDATA ascii\n0 0 0\n",
        encoding="ascii",
    )
    (mapping / "localization_map.processing.yaml").write_text(
        "schema_version: 1\nsource: commissioning\n",
        encoding="utf-8",
    )
    (review / "reviewed_map.pgm").write_bytes(
        b"P5\n3 2\n255\n" + bytes([254, 205, 0, 254, 205, 0])
    )
    (review / "reviewed_map.yaml").write_text(
        "image: reviewed_map.pgm\nresolution: 0.10\norigin: [1.0, 2.0, 0.0]\n"
        "negate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\nmode: trinary\n",
        encoding="utf-8",
    )
    (projection / "projection_record.json").write_text(
        json.dumps({"schema_version": 1, "backend": "lightweight_pcd_grid"}) + "\n",
        encoding="utf-8",
    )


def test_publish_site_revision_cli_uses_reviewed_map_and_can_activate(tmp_path, capsys):
    assert SCRIPT.is_file(), "field workflow needs a reviewed Site publish CLI"
    spec = importlib.util.spec_from_file_location("publish_site_revision", SCRIPT)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)

    runtime_dir = tmp_path / "runtime"
    sites_root = tmp_path / "sites"
    state_root = tmp_path / "state"
    _prepare_reviewed_run(runtime_dir)

    rc = module.main(
        [
            "--runtime-dir",
            str(runtime_dir),
            "--site-id",
            "orchard",
            "--run-id",
            "run_001",
            "--revision",
            "r01",
            "--sites-root",
            str(sites_root),
            "--state-root",
            str(state_root),
            "--vehicle-profile",
            str(ROOT / "profiles/platforms/bunker.yaml"),
            "--vehicle-schema",
            str(ROOT / "schemas/vehicle_profile.schema.json"),
            "--site-schema",
            str(ROOT / "schemas/site_package.schema.json"),
            "--activate",
        ]
    )
    assert rc == 0

    output = json.loads(capsys.readouterr().out)
    assert output["status"] == "SITE_READY"
    assert output["site_id"] == "orchard"
    assert output["revision"] == "r01"
    assert output["validated"] is True
    assert output["activated"] is True
    site_root = Path(output["site_root"])
    assert (site_root / "map/navigation.pgm").read_bytes().endswith(
        bytes([254, 205, 0, 254, 205, 0])
    )
    assert (site_root / "manifest.yaml").is_file()
    assert (site_root / "hashes.yaml").is_file()
    assert (state_root / "active_site.yaml").is_file()


def test_publish_cli_never_uses_raw_projection_as_explicit_authority():
    assert SCRIPT.is_file(), "field workflow needs a reviewed Site publish CLI"
    text = SCRIPT.read_text(encoding="utf-8")
    assert "ReviewedSitePublisher" in text
    assert "RtabmapGridBackend" not in text
