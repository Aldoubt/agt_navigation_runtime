from __future__ import annotations

import hashlib
from pathlib import Path

import yaml

from agt_site_runtime.models import SiteCandidate, SiteKey
from agt_site_runtime.summary_builder import (
    STATE_INVALID,
    STATE_READY,
    build_site_summary,
)
from agt_site_runtime.validator import SiteValidator


REPO_ROOT = Path(__file__).resolve().parents[3]
VEHICLE = REPO_ROOT / "profiles/platforms/mk_mini.yaml"
VEHICLE_SCHEMA = REPO_ROOT / "schemas/vehicle_profile.schema.json"
SITE_SCHEMA = REPO_ROOT / "schemas/site_package.schema.json"
FIXTURES = REPO_ROOT / "tests/contracts/fixtures"


def _candidate(fixture: str) -> SiteCandidate:
    root = FIXTURES / fixture
    manifest = yaml.safe_load((root / "manifest.yaml").read_text(encoding="utf-8"))
    return SiteCandidate(
        SiteKey(str(manifest["site"]["id"]), str(manifest["site"]["revision"])),
        root,
        root / "manifest.yaml",
    )


def _validator() -> SiteValidator:
    return SiteValidator(VEHICLE, VEHICLE_SCHEMA, SITE_SCHEMA)


def _sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def _expected_map_hash(root: Path) -> str:
    manifest_sha = _sha256(root / "manifest.yaml")
    hashes_doc = yaml.safe_load((root / "hashes.yaml").read_text(encoding="utf-8"))
    hashes = hashes_doc["hashes"]
    lines = "".join(f"{path}:{hashes[path]}\n" for path in sorted(hashes))
    payload = f"{manifest_sha}\n{lines}".encode("utf-8")
    return hashlib.sha256(payload).hexdigest()


def test_ready_summary_has_canonical_identity_hashes_and_safe_absolute_paths():
    candidate = _candidate("site_valid")
    validation = _validator().validate(candidate)
    assert validation.valid

    summary = build_site_summary(candidate, validation, active=False)

    assert summary.map_id == "greenhouse_test"
    assert summary.map_version_id == "r01"
    assert summary.state == STATE_READY
    assert summary.valid
    assert not summary.active
    assert summary.manifest_sha256 == _sha256(candidate.root / "manifest.yaml")
    assert summary.navigation_yaml_sha256 == "a137959630b040f2f9ce6203004dcf075da0b455b8ebf576eebbc2074206d10e"
    assert summary.navigation_image_sha256 == "ec85c5f801d54fee6a18fc66c5af096ea26f959e3ace0c7a515e49877266826a"
    assert summary.localization_pcd_sha256 == "86203b2845fa2b8615cbf6ae287867a6090bd29f551ee93d33cb7408e93dc532"
    assert summary.map_hash == _expected_map_hash(candidate.root)
    assert Path(summary.navigation_yaml) == (candidate.root / "map/navigation.yaml").resolve()
    assert Path(summary.localization_pcd) == (candidate.root / "map/localization_map.pcd").resolve()
    assert summary.processing_record == ""
    assert summary.tasks_directory == ""
    assert summary.validation_errors == ()


def test_active_flag_does_not_change_content_identity():
    candidate = _candidate("site_valid")
    validation = _validator().validate(candidate)
    inactive = build_site_summary(candidate, validation, active=False)
    active = build_site_summary(candidate, validation, active=True)

    assert active.active
    assert active.state == STATE_READY
    assert active.map_hash == inactive.map_hash
    assert active.manifest_sha256 == inactive.manifest_sha256


def test_invalid_summary_exposes_validation_failure_without_unsafe_runtime_paths():
    candidate = _candidate("site_hash_mismatch")
    validation = _validator().validate(candidate)
    assert not validation.valid

    summary = build_site_summary(candidate, validation, active=True)

    assert summary.state == STATE_INVALID
    assert not summary.valid
    assert not summary.active
    assert summary.map_hash == ""
    assert summary.navigation_yaml == ""
    assert summary.localization_pcd == ""
    assert summary.tasks_directory == ""
    assert summary.validation_errors == validation.blocker_messages
