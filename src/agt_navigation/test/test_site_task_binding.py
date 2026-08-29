from pathlib import Path
import sys
from types import SimpleNamespace

import pytest

PACKAGE_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PACKAGE_ROOT))

from agt_navigation.site_task_binding import (  # noqa: E402
    FilesystemSiteBindingResolver,
    SiteTaskBindingError,
    ValidatedSiteBinding,
    binding_from_map_version_summary,
)


def _digest(char: str, *, prefix: bool = True) -> str:
    value = char * 64
    return f"sha256:{value}" if prefix else value


def _summary(**overrides):
    values = {
        "map_id": "orchard_a",
        "map_version_id": "r01",
        "state": 3,
        "active": False,
        "valid": True,
        "map_hash": _digest("a", prefix=False),
        "manifest_sha256": _digest("b", prefix=False),
        "navigation_yaml_sha256": _digest("c", prefix=False),
        "navigation_image_sha256": _digest("d", prefix=False),
        "localization_pcd_sha256": _digest("e", prefix=False),
        "validation_errors": (),
    }
    values.update(overrides)
    return SimpleNamespace(**values)


def test_validated_site_binding_normalizes_all_hashes():
    binding = ValidatedSiteBinding(
        map_id="orchard_a",
        map_version_id="r01",
        map_hash=_digest("a", prefix=False),
        manifest_sha256=_digest("b"),
        navigation_yaml_sha256=_digest("c", prefix=False),
        navigation_image_sha256=_digest("d"),
        localization_pcd_sha256=_digest("e", prefix=False),
    )

    assert binding.map_hash == _digest("a")
    assert binding.manifest_sha256 == _digest("b")
    assert binding.navigation_yaml_sha256 == _digest("c")
    assert binding.navigation_image_sha256 == _digest("d")
    assert binding.localization_pcd_sha256 == _digest("e")
    assert binding.to_dict()["schema_version"] == 1


def test_validated_site_binding_rejects_missing_identity_and_bad_hash():
    with pytest.raises(SiteTaskBindingError) as exc:
        ValidatedSiteBinding(
            map_id="",
            map_version_id="r01",
            map_hash=_digest("a"),
            manifest_sha256=_digest("b"),
            navigation_yaml_sha256=_digest("c"),
            navigation_image_sha256=_digest("d"),
            localization_pcd_sha256=_digest("e"),
        )
    assert exc.value.code == "TASK_SITE_BINDING_INVALID"

    with pytest.raises(SiteTaskBindingError) as exc:
        ValidatedSiteBinding(
            map_id="orchard_a",
            map_version_id="r01",
            map_hash="not-a-digest",
            manifest_sha256=_digest("b"),
            navigation_yaml_sha256=_digest("c"),
            navigation_image_sha256=_digest("d"),
            localization_pcd_sha256=_digest("e"),
        )
    assert exc.value.code == "TASK_SITE_BINDING_INVALID"


def test_binding_from_active_map_summary_requires_ready_valid_active_exact_identity():
    binding = binding_from_map_version_summary(
        _summary(active=True),
        requested_map_id="orchard_a",
        requested_map_version_id="r01",
        require_active=True,
    )
    assert binding.map_hash == _digest("a")

    for bad_summary, code in (
        (None, "MAP_NOT_READY"),
        (_summary(active=False), "MAP_NOT_READY"),
        (_summary(active=True, valid=False), "MAP_NOT_READY"),
        (_summary(active=True, state=0), "MAP_NOT_READY"),
        (_summary(active=True, map_version_id="r02"), "MAP_VERSION_MISMATCH"),
    ):
        with pytest.raises(SiteTaskBindingError) as exc:
            binding_from_map_version_summary(
                bad_summary,
                requested_map_id="orchard_a",
                requested_map_version_id="r01",
                require_active=True,
            )
        assert exc.value.code == code


def test_active_summary_content_hash_change_changes_binding_identity():
    first = binding_from_map_version_summary(
        _summary(active=True),
        requested_map_id="orchard_a",
        requested_map_version_id="r01",
        require_active=True,
    )
    second = binding_from_map_version_summary(
        _summary(active=True, map_hash=_digest("f", prefix=False)),
        requested_map_id="orchard_a",
        requested_map_version_id="r01",
        require_active=True,
    )
    assert first != second


def test_filesystem_resolver_returns_exact_validated_binding_from_summary_adapter():
    resolver = FilesystemSiteBindingResolver(
        sites_root="/unused/sites",
        vehicle_profile="/unused/profile.yaml",
        vehicle_schema="/unused/vehicle.schema.json",
        site_schema="/unused/site.schema.json",
        summary_resolver=lambda _map_id, _version: _summary(),
    )

    binding = resolver("orchard_a", "r01")

    assert binding.map_id == "orchard_a"
    assert binding.map_version_id == "r01"
    assert binding.map_hash == _digest("a")
    assert binding.manifest_sha256 == _digest("b")


def test_filesystem_resolver_fails_closed_for_missing_invalid_or_wrong_site():
    missing = FilesystemSiteBindingResolver(
        sites_root="/unused/sites",
        vehicle_profile="/unused/profile.yaml",
        vehicle_schema="/unused/vehicle.schema.json",
        site_schema="/unused/site.schema.json",
        summary_resolver=lambda _map_id, _version: None,
    )
    with pytest.raises(SiteTaskBindingError) as exc:
        missing("orchard_a", "r01")
    assert exc.value.code == "MAP_NOT_READY"

    invalid = FilesystemSiteBindingResolver(
        sites_root="/unused/sites",
        vehicle_profile="/unused/profile.yaml",
        vehicle_schema="/unused/vehicle.schema.json",
        site_schema="/unused/site.schema.json",
        summary_resolver=lambda _map_id, _version: _summary(valid=False),
    )
    with pytest.raises(SiteTaskBindingError) as exc:
        invalid("orchard_a", "r01")
    assert exc.value.code == "MAP_NOT_READY"

    wrong = FilesystemSiteBindingResolver(
        sites_root="/unused/sites",
        vehicle_profile="/unused/profile.yaml",
        vehicle_schema="/unused/vehicle.schema.json",
        site_schema="/unused/site.schema.json",
        summary_resolver=lambda _map_id, _version: _summary(map_version_id="r02"),
    )
    with pytest.raises(SiteTaskBindingError) as exc:
        wrong("orchard_a", "r01")
    assert exc.value.code == "MAP_VERSION_MISMATCH"
