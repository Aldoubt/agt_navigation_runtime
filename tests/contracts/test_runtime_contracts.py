from importlib import import_module
from pathlib import Path

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
