from __future__ import annotations

from pathlib import Path

from .models import SiteCandidate, SiteKey


class SiteRegistry:
    """Discover only deployed ``<site>/<revision>/manifest.yaml`` candidates."""

    def __init__(self, sites_root: Path):
        self.sites_root = Path(sites_root)

    def scan(self) -> tuple[SiteCandidate, ...]:
        if not self.sites_root.is_dir():
            return ()

        root_resolved = self.sites_root.resolve()
        candidates: list[SiteCandidate] = []
        for site_dir in self.sites_root.iterdir():
            if not site_dir.is_dir():
                continue
            for revision_dir in site_dir.iterdir():
                if not revision_dir.is_dir():
                    continue
                manifest_path = revision_dir / "manifest.yaml"
                if not manifest_path.is_file():
                    continue

                # A symlinked candidate must not escape the configured deployment root.
                try:
                    revision_dir.resolve().relative_to(root_resolved)
                    manifest_path.resolve().relative_to(root_resolved)
                except ValueError:
                    continue

                candidates.append(
                    SiteCandidate(
                        key=SiteKey(site_dir.name, revision_dir.name),
                        root=revision_dir,
                        manifest_path=manifest_path,
                    )
                )

        return tuple(sorted(candidates, key=lambda item: item.key))

    def resolve(self, key: SiteKey) -> SiteCandidate | None:
        for candidate in self.scan():
            if candidate.key == key:
                return candidate
        return None
