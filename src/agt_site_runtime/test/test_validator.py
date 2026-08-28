from pathlib import Path
import shutil

import yaml

from agt_site_runtime.models import SiteCandidate, SiteKey
from agt_site_runtime.validator import SiteValidator


REPO_ROOT = Path(__file__).resolve().parents[3]
VEHICLE = REPO_ROOT / "profiles/platforms/mk_mini.yaml"
VEHICLE_SCHEMA = REPO_ROOT / "schemas/vehicle_profile.schema.json"
SITE_SCHEMA = REPO_ROOT / "schemas/site_package.schema.json"
FIXTURES = REPO_ROOT / "tests/contracts/fixtures"


def _copy_candidate(
    tmp_path: Path,
    fixture: str,
    site_id: str | None = None,
    revision: str | None = None,
) -> SiteCandidate:
    source = FIXTURES / fixture
    manifest = yaml.safe_load((source / "manifest.yaml").read_text(encoding="utf-8"))
    manifest_site = manifest.get("site", {}) if isinstance(manifest, dict) else {}
    deployed_site_id = site_id if site_id is not None else str(manifest_site.get("id", "missing-site"))
    deployed_revision = revision if revision is not None else str(manifest_site.get("revision", "missing-revision"))

    root = tmp_path / "sites" / deployed_site_id / deployed_revision
    shutil.copytree(source, root)
    return SiteCandidate(
        SiteKey(deployed_site_id, deployed_revision),
        root,
        root / "manifest.yaml",
    )


def _validator() -> SiteValidator:
    return SiteValidator(VEHICLE, VEHICLE_SCHEMA, SITE_SCHEMA)


def test_valid_deployed_candidate_passes_full_runtime_contract(tmp_path):
    result = _validator().validate(_copy_candidate(tmp_path, "site_valid"))
    assert result.valid
    assert result.blocker_codes == ()
    assert "SHA256 integrity" in result.checks


def test_directory_site_identity_mismatch_fails_before_ready(tmp_path):
    candidate = _copy_candidate(tmp_path, "site_valid", site_id="wrong_site")
    result = _validator().validate(candidate)
    assert not result.valid
    assert result.blocker_codes == ("SITE_IDENTITY_MISMATCH",)


def test_directory_revision_identity_mismatch_fails_before_ready(tmp_path):
    candidate = _copy_candidate(tmp_path, "site_valid", revision="r99")
    result = _validator().validate(candidate)
    assert not result.valid
    assert result.blocker_codes == ("SITE_IDENTITY_MISMATCH",)


def test_manifest_identity_is_read_from_content_not_directory_name_only(tmp_path):
    candidate = _copy_candidate(tmp_path, "site_valid")
    manifest = yaml.safe_load(candidate.manifest_path.read_text(encoding="utf-8"))
    manifest["site"]["id"] = "orchard_other"
    candidate.manifest_path.write_text(yaml.safe_dump(manifest, sort_keys=False), encoding="utf-8")

    result = _validator().validate(candidate)
    assert not result.valid
    assert result.blocker_codes == ("SITE_IDENTITY_MISMATCH",)


def test_low_level_contract_failures_map_to_stable_site_runtime_blockers(tmp_path):
    cases = {
        "site_unsupported_schema": "SITE_SCHEMA_INVALID",
        "site_absolute_path": "SITE_PATH_UNSAFE",
        "site_path_escape": "SITE_PATH_UNSAFE",
        "site_hash_mismatch": "SITE_HASH_MISMATCH",
        "site_incompatible_vehicle": "SITE_VEHICLE_INCOMPATIBLE",
    }

    validator = _validator()
    for fixture, blocker in cases.items():
        candidate = _copy_candidate(tmp_path / fixture, fixture)
        result = validator.validate(candidate)
        assert not result.valid, fixture
        assert blocker in result.blocker_codes, (fixture, result.blocker_codes, result.blocker_messages)
