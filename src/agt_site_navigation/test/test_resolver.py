from __future__ import annotations

from dataclasses import replace
from pathlib import Path
import shutil
import sys

import pytest

REPO_ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(REPO_ROOT / "src/agt_site_runtime"))
sys.path.insert(0, str(REPO_ROOT / "src/agt_runtime_contracts"))

from agt_site_runtime.models import SiteCandidate, SiteKey  # noqa: E402
from agt_site_runtime.summary_builder import build_site_summary  # noqa: E402
from agt_site_runtime.validator import SiteValidator  # noqa: E402
from agt_site_navigation.resolver import (  # noqa: E402
    ActiveSiteNavigationResolver,
    SiteNavigationBindingError,
)


VEHICLE = REPO_ROOT / "profiles/platforms/mk_mini.yaml"
VEHICLE_SCHEMA = REPO_ROOT / "schemas/vehicle_profile.schema.json"
SITE_SCHEMA = REPO_ROOT / "schemas/site_package.schema.json"
FIXTURE = REPO_ROOT / "tests/contracts/fixtures/site_valid"


def _deployed(tmp_path: Path):
    root = tmp_path / "sites" / "greenhouse_test" / "r01"
    shutil.copytree(FIXTURE, root)
    candidate = SiteCandidate(
        SiteKey("greenhouse_test", "r01"), root, root / "manifest.yaml"
    )
    validation = SiteValidator(VEHICLE, VEHICLE_SCHEMA, SITE_SCHEMA).validate(candidate)
    assert validation.valid
    return root, build_site_summary(candidate, validation, active=True)


def _resolver(tmp_path: Path) -> ActiveSiteNavigationResolver:
    return ActiveSiteNavigationResolver(
        sites_root=tmp_path / "sites",
        vehicle_profile=VEHICLE,
        vehicle_schema=VEHICLE_SCHEMA,
        site_schema=SITE_SCHEMA,
    )


def test_exact_active_site_resolves_deterministic_navigation_binding(tmp_path):
    root, summary = _deployed(tmp_path)

    binding = _resolver(tmp_path).resolve(summary)

    assert binding.site_id == "greenhouse_test"
    assert binding.site_revision == "r01"
    assert binding.site_hash == summary.map_hash
    assert binding.manifest_sha256 == summary.manifest_sha256
    assert binding.navigation_yaml == (root / "map/navigation.yaml").resolve()
    assert binding.navigation_yaml_sha256 == summary.navigation_yaml_sha256
    assert binding.navigation_image == (root / "map/navigation.pgm").resolve()
    assert binding.navigation_image_sha256 == summary.navigation_image_sha256
    assert binding.localization_pcd == (root / "map/localization_map.pcd").resolve()
    assert binding.localization_pcd_sha256 == summary.localization_pcd_sha256
    assert binding.processing_record is None


def test_no_active_site_is_fail_closed(tmp_path):
    with pytest.raises(SiteNavigationBindingError) as exc:
        _resolver(tmp_path).resolve(None)
    assert exc.value.code == "NO_ACTIVE_SITE"


def test_inactive_or_invalid_summary_is_fail_closed(tmp_path):
    _root, summary = _deployed(tmp_path)

    with pytest.raises(SiteNavigationBindingError) as exc:
        _resolver(tmp_path).resolve(replace(summary, active=False))
    assert exc.value.code == "NO_ACTIVE_SITE"

    with pytest.raises(SiteNavigationBindingError) as exc:
        _resolver(tmp_path).resolve(replace(summary, valid=False))
    assert exc.value.code == "ACTIVE_SITE_NOT_READY"


def test_active_summary_identity_hash_mismatch_is_fail_closed(tmp_path):
    _root, summary = _deployed(tmp_path)
    wrong = replace(summary, map_hash="0" * 64)

    with pytest.raises(SiteNavigationBindingError) as exc:
        _resolver(tmp_path).resolve(wrong)
    assert exc.value.code == "ACTIVE_SITE_IDENTITY_MISMATCH"


def test_asset_corruption_after_activation_is_fail_closed(tmp_path):
    root, summary = _deployed(tmp_path)
    (root / "map/navigation.pgm").write_bytes(b"corrupted-after-activation")

    with pytest.raises(SiteNavigationBindingError) as exc:
        _resolver(tmp_path).resolve(summary)
    assert exc.value.code == "SITE_ASSET_INVALID"


def test_missing_deployed_revision_is_fail_closed(tmp_path):
    _root, summary = _deployed(tmp_path)
    shutil.rmtree(tmp_path / "sites" / "greenhouse_test" / "r01")

    with pytest.raises(SiteNavigationBindingError) as exc:
        _resolver(tmp_path).resolve(summary)
    assert exc.value.code == "ACTIVE_SITE_NOT_DEPLOYED"
