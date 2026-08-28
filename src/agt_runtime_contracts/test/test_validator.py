from pathlib import Path

from agt_runtime_contracts.validator import validate_runtime_contracts


REPO_ROOT = Path(__file__).resolve().parents[3]


def test_canonical_validator_accepts_reference_site_fixture():
    report = validate_runtime_contracts(
        REPO_ROOT / "profiles/platforms/mk_mini.yaml",
        REPO_ROOT / "tests/contracts/fixtures/site_valid",
        REPO_ROOT / "schemas/vehicle_profile.schema.json",
        REPO_ROOT / "schemas/site_package.schema.json",
    )
    assert report.ok, report.issues
    assert "SHA256 integrity" in report.checks


def test_canonical_validator_rejects_hash_mismatch():
    report = validate_runtime_contracts(
        REPO_ROOT / "profiles/platforms/mk_mini.yaml",
        REPO_ROOT / "tests/contracts/fixtures/site_hash_mismatch",
        REPO_ROOT / "schemas/vehicle_profile.schema.json",
        REPO_ROOT / "schemas/site_package.schema.json",
    )
    assert not report.ok
    assert any(issue.code == "HASH_MISMATCH" for issue in report.issues)
