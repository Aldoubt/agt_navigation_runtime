from pathlib import Path
import json
import shutil

import yaml

from agt_field_commissioning.projection import ProjectionResult
from agt_field_commissioning.service import CommissioningService
from agt_runtime_contracts.validator import validate_runtime_contracts


class FakeProjectionBackend:
    backend_name = "fake_grid"

    def project(self, request):
        output = Path(request.output_dir)
        output.mkdir(parents=True, exist_ok=True)
        pgm = output / "raw_map.pgm"
        nav_yaml = output / "raw_map.yaml"
        record = output / "projection_record.json"
        pgm.write_bytes(b"P5\n3 2\n255\n" + bytes([0, 205, 254, 254, 205, 0]))
        nav_yaml.write_text(
            "image: raw_map.pgm\nresolution: 0.10\norigin: [1.0, 2.0, 0.0]\n"
            "negate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\nmode: trinary\n",
            encoding="utf-8",
        )
        record.write_text(json.dumps({"schema_version": 1, "backend": self.backend_name}) + "\n")
        return ProjectionResult(self.backend_name, pgm, nav_yaml, record)


def _prepare_run(runtime: Path, site_id: str, run_id: str) -> Path:
    mapping = runtime / "commissioning" / site_id / run_id / "mapping"
    mapping.mkdir(parents=True)
    (mapping / "localization_map.pcd").write_text(
        "# .PCD v0.7\nFIELDS x y z\nSIZE 4 4 4\nTYPE F F F\nCOUNT 1 1 1\n"
        "WIDTH 1\nHEIGHT 1\nPOINTS 1\nDATA ascii\n0 0 0\n",
        encoding="ascii",
    )
    (mapping / "localization_map.processing.yaml").write_text(
        "schema_version: 1\nsource: commissioning\n",
        encoding="utf-8",
    )
    evidence = mapping.parent / "evidence"
    evidence.mkdir()
    (evidence / "mapping_metadata.json").write_text(
        json.dumps({"status": "FINALIZED"}) + "\n", encoding="utf-8"
    )
    return mapping.parent


def _service(tmp_path: Path) -> CommissioningService:
    repo = Path(__file__).resolve().parents[2]
    return CommissioningService(
        runtime_dir=tmp_path / "runtime",
        sites_root=tmp_path / "sites",
        state_root=tmp_path / "state",
        vehicle_profile=repo / "profiles/platforms/bunker.yaml",
        vehicle_schema=repo / "schemas/vehicle_profile.schema.json",
        site_schema=repo / "schemas/site_package.schema.json",
        projection_backend=FakeProjectionBackend(),
    )


def test_project_edit_save_and_activate_site_revision(tmp_path: Path) -> None:
    service = _service(tmp_path)
    _prepare_run(tmp_path / "runtime", "slope", "run01")

    assert service.status("slope", "run01")["state"] == "PCD_READY"
    service.project("slope", "run01")
    assert service.status("slope", "run01")["state"] == "MAP_READY"

    descriptor = service.map_descriptor("slope", "run01")
    assert descriptor["width"] == 3
    assert descriptor["height"] == 2
    assert descriptor["resolution"] == 0.10
    assert descriptor["origin"] == [1.0, 2.0, 0.0]
    assert descriptor["revision"] == 0

    service.apply_map_edit("slope", "run01", "erase_to_free", [0])
    assert service.map_descriptor("slope", "run01")["revision"] == 1
    assert service.current_map_bytes("slope", "run01")[-6:] == bytes([254, 205, 254, 254, 205, 0])
    assert service.undo_map_edit("slope", "run01") is True
    assert service.redo_map_edit("slope", "run01") is True

    saved = service.save_review("slope", "run01", "r01")
    site_root = Path(saved["site_root"])
    assert site_root == tmp_path / "sites" / "slope" / "r01"
    assert saved["validated"] is True
    assert (site_root / "map/navigation.pgm").is_file()
    assert (site_root / "map/navigation.yaml").is_file()
    assert (site_root / "map/localization_map.pcd").is_file()
    assert (site_root / "manifest.yaml").is_file()
    assert (site_root / "hashes.yaml").is_file()

    repo = Path(__file__).resolve().parents[2]
    report = validate_runtime_contracts(
        repo / "profiles/platforms/bunker.yaml",
        site_root,
        repo / "schemas/vehicle_profile.schema.json",
        repo / "schemas/site_package.schema.json",
    )
    assert report.ok, report.issues

    active = service.activate_revision("slope", "r01")
    assert active == {"site_id": "slope", "revision": "r01"}
    active_doc = yaml.safe_load((tmp_path / "state/active_site.yaml").read_text(encoding="utf-8"))
    assert active_doc["site_id"] == "slope"
    assert active_doc["revision"] == "r01"


def test_save_review_is_fail_closed_and_never_overwrites_revision(tmp_path: Path) -> None:
    service = _service(tmp_path)
    _prepare_run(tmp_path / "runtime", "slope", "run01")
    service.project("slope", "run01")
    service.save_review("slope", "run01", "r01")

    try:
        service.save_review("slope", "run01", "r01")
    except RuntimeError as exc:
        assert "already exists" in str(exc)
    else:
        raise AssertionError("existing immutable Site revision must not be overwritten")


def test_service_rejects_unsafe_identity(tmp_path: Path) -> None:
    service = _service(tmp_path)
    for value in ("../escape", "a/b", "", "."):
        try:
            service.status(value, "run01")
        except ValueError:
            pass
        else:
            raise AssertionError(f"unsafe identity was accepted: {value!r}")
