from importlib import import_module
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[2]


def test_installable_runtime_contract_library_is_canonical():
    canonical = import_module("agt_runtime_contracts.validator")
    compatibility = import_module("tools.runtime_contracts.validator")

    assert compatibility.ValidationIssue is canonical.ValidationIssue
    assert compatibility.ValidationReport is canonical.ValidationReport
    assert compatibility.validate_site_package is canonical.validate_site_package
    assert compatibility.validate_vehicle_profile is canonical.validate_vehicle_profile
    assert compatibility.validate_runtime_contracts is canonical.validate_runtime_contracts


def test_installable_library_preserves_existing_fixture_behavior():
    canonical = import_module("agt_runtime_contracts.validator")
    valid = canonical.validate_runtime_contracts(
        REPO_ROOT / "profiles/platforms/mk_mini.yaml",
        REPO_ROOT / "tests/contracts/fixtures/site_valid",
        REPO_ROOT / "schemas/vehicle_profile.schema.json",
        REPO_ROOT / "schemas/site_package.schema.json",
    )
    invalid = canonical.validate_runtime_contracts(
        REPO_ROOT / "profiles/platforms/mk_mini.yaml",
        REPO_ROOT / "tests/contracts/fixtures/site_hash_mismatch",
        REPO_ROOT / "schemas/vehicle_profile.schema.json",
        REPO_ROOT / "schemas/site_package.schema.json",
    )

    assert valid.ok
    assert "SHA256 integrity" in valid.checks
    assert not invalid.ok
    assert any(issue.code == "HASH_MISMATCH" for issue in invalid.issues)


def test_canonical_library_exposes_safe_asset_helpers():
    canonical = import_module("agt_runtime_contracts.validator")
    for name in (
        "resolve_relative_path",
        "navigation_image_asset",
        "load_hashes",
        "sha256_file",
    ):
        assert callable(getattr(canonical, name))
