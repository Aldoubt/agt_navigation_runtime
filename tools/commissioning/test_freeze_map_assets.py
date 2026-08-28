from __future__ import annotations

import hashlib
import importlib.util
import json
from pathlib import Path

import pytest
import yaml


SCRIPT = Path(__file__).with_name("freeze_map_assets.py")


def _load_freezer():
    assert SCRIPT.is_file(), "freeze_map_assets.py must exist"
    spec = importlib.util.spec_from_file_location("freeze_map_assets", SCRIPT)
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)
    return module


def _sha256(path: Path) -> str:
    return "sha256:" + hashlib.sha256(path.read_bytes()).hexdigest()


def _fixture(tmp_path: Path):
    pcd = tmp_path / "global_map.pcd"
    image = tmp_path / "map.pgm"
    nav_yaml = tmp_path / "map.yaml"
    manifest = tmp_path / "metadata" / "map_manifest.json"

    pcd.write_bytes(b"VERSION .7\nDATA binary\nfixture-pcd\n")
    image.write_bytes(b"P5\n2 2\n255\n\x00\xff\xff\x00")
    nav_yaml.write_text(
        yaml.safe_dump(
            {
                "image": image.name,
                "resolution": 0.05,
                "origin": [0.0, 0.0, 0.0],
                "negate": 0,
                "occupied_thresh": 0.65,
                "free_thresh": 0.25,
            },
            sort_keys=False,
        ),
        encoding="utf-8",
    )
    return pcd, nav_yaml, image, manifest


def test_manifest_hashes_pcd_yaml_and_image(tmp_path):
    freezer = _load_freezer()
    pcd, nav_yaml, image, manifest_path = _fixture(tmp_path)

    manifest = freezer.freeze_assets(
        pcd_path=pcd,
        navigation_yaml_path=nav_yaml,
        map_id="greenhouse_01",
        run_id="mapping_001",
        manifest_path=manifest_path,
    )

    assert manifest["schema_version"] == 1
    assert manifest["map_id"] == "greenhouse_01"
    assert manifest["run_id"] == "mapping_001"
    assert manifest["mapping_source"] == "FAST_LIVO2_LIO_ONLY"
    assert manifest["pcd_path"] == str(pcd.resolve())
    assert manifest["navigation_yaml_path"] == str(nav_yaml.resolve())
    assert manifest["navigation_image_path"] == str(image.resolve())
    assert manifest["pcd_sha256"] == _sha256(pcd)
    assert manifest["navigation_yaml_sha256"] == _sha256(nav_yaml)
    assert manifest["navigation_image_sha256"] == _sha256(image)
    assert manifest["calibration_status"] == "UNVERIFIED"
    assert manifest["generated_at_utc"].endswith("Z")

    assert json.loads(manifest_path.read_text(encoding="utf-8")) == manifest
    assert not manifest_path.with_suffix(manifest_path.suffix + ".tmp").exists()


def test_existing_manifest_is_not_overwritten(tmp_path):
    freezer = _load_freezer()
    pcd, nav_yaml, _image, manifest_path = _fixture(tmp_path)
    manifest_path.parent.mkdir(parents=True, exist_ok=True)
    manifest_path.write_text('{"sentinel": true}\n', encoding="utf-8")
    before = manifest_path.read_bytes()

    with pytest.raises(FileExistsError):
        freezer.freeze_assets(
            pcd_path=pcd,
            navigation_yaml_path=nav_yaml,
            map_id="greenhouse_01",
            run_id="mapping_001",
            manifest_path=manifest_path,
        )

    assert manifest_path.read_bytes() == before


@pytest.mark.parametrize(
    ("map_id", "run_id"),
    (("", "mapping_001"), ("greenhouse_01", "")),
)
def test_empty_map_or_run_identity_is_rejected(tmp_path, map_id, run_id):
    freezer = _load_freezer()
    pcd, nav_yaml, _image, manifest_path = _fixture(tmp_path)

    with pytest.raises(ValueError):
        freezer.freeze_assets(
            pcd_path=pcd,
            navigation_yaml_path=nav_yaml,
            map_id=map_id,
            run_id=run_id,
            manifest_path=manifest_path,
        )


def test_missing_input_file_is_rejected(tmp_path):
    freezer = _load_freezer()
    _pcd, nav_yaml, _image, manifest_path = _fixture(tmp_path)

    with pytest.raises(FileNotFoundError):
        freezer.freeze_assets(
            pcd_path=tmp_path / "missing.pcd",
            navigation_yaml_path=nav_yaml,
            map_id="greenhouse_01",
            run_id="mapping_001",
            manifest_path=manifest_path,
        )


def test_unresolved_navigation_image_is_rejected(tmp_path):
    freezer = _load_freezer()
    pcd, nav_yaml, image, manifest_path = _fixture(tmp_path)
    image.unlink()

    with pytest.raises(FileNotFoundError):
        freezer.freeze_assets(
            pcd_path=pcd,
            navigation_yaml_path=nav_yaml,
            map_id="greenhouse_01",
            run_id="mapping_001",
            manifest_path=manifest_path,
        )
