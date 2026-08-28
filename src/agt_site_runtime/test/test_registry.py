from pathlib import Path

from agt_site_runtime.models import SiteKey
from agt_site_runtime.registry import SiteRegistry


def _candidate(root: Path, site_id: str, revision: str) -> None:
    path = root / site_id / revision
    path.mkdir(parents=True)
    (path / "manifest.yaml").write_text("site_schema_version: '1.0'\n", encoding="utf-8")


def test_empty_registry_returns_no_candidates(tmp_path):
    registry = SiteRegistry(tmp_path / "sites")
    assert registry.scan() == ()


def test_registry_scans_exact_two_level_site_revision_layout_in_sorted_order(tmp_path):
    root = tmp_path / "sites"
    _candidate(root, "orchard_b", "r02")
    _candidate(root, "greenhouse_a", "r03")
    _candidate(root, "greenhouse_a", "r01")

    (root / "README.txt").write_text("ignore", encoding="utf-8")
    (root / "greenhouse_a" / "not-a-version.txt").write_text("ignore", encoding="utf-8")
    nested = root / "wrong" / "too" / "deep"
    nested.mkdir(parents=True)
    (nested / "manifest.yaml").write_text("ignore", encoding="utf-8")

    registry = SiteRegistry(root)
    found = registry.scan()

    assert [item.key for item in found] == [
        SiteKey("greenhouse_a", "r01"),
        SiteKey("greenhouse_a", "r03"),
        SiteKey("orchard_b", "r02"),
    ]
    assert all(item.manifest_path == item.root / "manifest.yaml" for item in found)


def test_registry_resolves_only_exact_discovered_identity(tmp_path):
    root = tmp_path / "sites"
    _candidate(root, "greenhouse_a", "r01")
    registry = SiteRegistry(root)

    found = registry.resolve(SiteKey("greenhouse_a", "r01"))
    missing = registry.resolve(SiteKey("greenhouse_a", "r02"))

    assert found is not None
    assert found.root == root / "greenhouse_a" / "r01"
    assert missing is None
