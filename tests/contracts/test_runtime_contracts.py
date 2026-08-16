from importlib import import_module
from pathlib import Path
import subprocess
import sys

import pytest
import yaml


REPO_ROOT = Path(__file__).resolve().parents[2]


def load_yaml(path: Path):
    with path.open("r", encoding="utf-8") as stream:
        return yaml.safe_load(stream)


def load_validator_module():
    try:
        return import_module("tools.runtime_contracts.validator")
    except ModuleNotFoundError as exc:
        pytest.fail(f"runtime contract validator is missing: {exc}")


def runtime_report(site_fixture: str):
    validator = load_validator_module()
    return validator.validate_runtime_contracts(
        REPO_ROOT / "profiles/platforms/mk_mini.yaml",
        REPO_ROOT / f"tests/contracts/fixtures/{site_fixture}",
        REPO_ROOT / "schemas/vehicle_profile.schema.json",
        REPO_ROOT / "schemas/site_package.schema.json",
    )


def run_cli(site_fixture: str):
    return subprocess.run(
        [
            sys.executable,
            str(REPO_ROOT / "tools/validate_runtime_contracts.py"),
            "--vehicle",
            str(REPO_ROOT / "profiles/platforms/mk_mini.yaml"),
            "--site",
            str(REPO_ROOT / f"tests/contracts/fixtures/{site_fixture}"),
        ],
        cwd=REPO_ROOT,
        text=True,
        capture_output=True,
        check=False,
    )


def test_real_mk_mini_profile_declares_v1_schema():
    profile = load_yaml(REPO_ROOT / "profiles/platforms/mk_mini.yaml")
    assert profile["schema_version"] == "1.0"


def test_real_mk_mini_profile_passes_vehicle_schema():
    validator = load_validator_module()
    report = validator.validate_vehicle_profile(
        REPO_ROOT / "profiles/platforms/mk_mini.yaml",
        REPO_ROOT / "schemas/vehicle_profile.schema.json",
    )
    assert report.ok, report.issues
    assert "vehicle schema" in report.checks


def test_site_relative_paths_pass():
    validator = load_validator_module()
    report = validator.validate_site_package(
        REPO_ROOT / "tests/contracts/fixtures/site_valid",
        REPO_ROOT / "schemas/site_package.schema.json",
    )
    assert report.ok, report.issues
    assert "site schema" in report.checks
    assert "relative paths" in report.checks
    assert "required assets" in report.checks


def test_site_absolute_asset_path_fails_closed():
    validator = load_validator_module()
    report = validator.validate_site_package(
        REPO_ROOT / "tests/contracts/fixtures/site_absolute_path",
        REPO_ROOT / "schemas/site_package.schema.json",
    )
    assert not report.ok
    assert any(issue.code == "ABSOLUTE_PATH" for issue in report.issues)


def test_site_path_escape_fails_closed():
    validator = load_validator_module()
    report = validator.validate_site_package(
        REPO_ROOT / "tests/contracts/fixtures/site_path_escape",
        REPO_ROOT / "schemas/site_package.schema.json",
    )
    assert not report.ok
    assert any(issue.code == "PATH_ESCAPE" for issue in report.issues)


def test_unsupported_site_schema_fails_closed():
    validator = load_validator_module()
    report = validator.validate_site_package(
        REPO_ROOT / "tests/contracts/fixtures/site_unsupported_schema",
        REPO_ROOT / "schemas/site_package.schema.json",
    )
    assert not report.ok
    assert any(issue.code == "SITE_SCHEMA" for issue in report.issues)


def test_valid_runtime_contracts_are_ready():
    report = runtime_report("site_valid")
    assert report.ok, report.issues
    assert "SHA256 integrity" in report.checks
    assert "vehicle compatibility" in report.checks
    assert "Ackermann geometry" in report.checks


def test_hash_mismatch_fails_closed():
    report = runtime_report("site_hash_mismatch")
    assert not report.ok
    assert any(issue.code == "HASH_MISMATCH" for issue in report.issues)


def test_incompatible_vehicle_fails_closed():
    report = runtime_report("site_incompatible_vehicle")
    assert not report.ok
    assert any(issue.code == "INCOMPATIBLE_VEHICLE" for issue in report.issues)


def test_cli_returns_zero_for_ready_contract():
    result = run_cli("site_valid")
    assert result.returncode == 0, result.stderr + result.stdout
    assert "Runtime contract validation: READY" in result.stdout
    assert "[PASS] SHA256 integrity" in result.stdout


def test_cli_returns_two_for_contract_failure():
    result = run_cli("site_hash_mismatch")
    assert result.returncode == 2, result.stderr + result.stdout
    assert "Runtime contract validation: NOT READY" in result.stdout
    assert "HASH_MISMATCH" in result.stdout
