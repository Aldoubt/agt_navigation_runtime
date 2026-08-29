"""Resolve the authoritative Active Site into immutable navigation asset paths.

This module is intentionally ROS-free. It reuses the canonical Site Runtime
registry/validator/summary builder and never mutates Site assets, publishes TF,
or owns navigation lifecycle state.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

from agt_runtime_contracts.validator import load_yaml, navigation_image_asset
from agt_site_runtime.models import SiteKey
from agt_site_runtime.registry import SiteRegistry
from agt_site_runtime.summary_builder import STATE_READY, build_site_summary
from agt_site_runtime.validator import SiteValidator


class SiteNavigationBindingError(RuntimeError):
    """Stable fail-closed error raised while resolving Active Site assets."""

    def __init__(self, code: str, message: str) -> None:
        super().__init__(message)
        self.code = str(code)
        self.message = str(message)


@dataclass(frozen=True)
class ResolvedNavigationBinding:
    site_id: str
    site_revision: str
    site_hash: str
    manifest_sha256: str
    navigation_yaml: Path
    navigation_yaml_sha256: str
    navigation_image: Path
    navigation_image_sha256: str
    localization_pcd: Path
    localization_pcd_sha256: str
    processing_record: Path | None = None


class ActiveSiteNavigationResolver:
    """Re-resolve and verify the exact deployed Site selected by Site Runtime."""

    def __init__(
        self,
        *,
        sites_root: str | Path,
        vehicle_profile: str | Path,
        vehicle_schema: str | Path,
        site_schema: str | Path,
    ) -> None:
        self.sites_root = Path(sites_root).expanduser()
        self.vehicle_profile = Path(vehicle_profile).expanduser()
        self.vehicle_schema = Path(vehicle_schema).expanduser()
        self.site_schema = Path(site_schema).expanduser()

    def resolve(self, active_summary) -> ResolvedNavigationBinding:
        if active_summary is None or not bool(getattr(active_summary, "active", False)):
            raise SiteNavigationBindingError(
                "NO_ACTIVE_SITE", "no authoritative active Site is available"
            )
        if (
            int(getattr(active_summary, "state", 0)) != STATE_READY
            or not bool(getattr(active_summary, "valid", False))
        ):
            raise SiteNavigationBindingError(
                "ACTIVE_SITE_NOT_READY", "authoritative active Site is not READY and valid"
            )

        site_id = str(getattr(active_summary, "map_id", ""))
        revision = str(getattr(active_summary, "map_version_id", ""))
        if not site_id or not revision:
            raise SiteNavigationBindingError(
                "ACTIVE_SITE_NOT_READY", "active Site identity is incomplete"
            )

        candidate = SiteRegistry(self.sites_root).resolve(SiteKey(site_id, revision))
        if candidate is None:
            raise SiteNavigationBindingError(
                "ACTIVE_SITE_NOT_DEPLOYED",
                f"active Site revision is not deployed: {site_id}/{revision}",
            )

        validation = SiteValidator(
            self.vehicle_profile, self.vehicle_schema, self.site_schema
        ).validate(candidate)
        if not validation.valid:
            detail = "; ".join(validation.blocker_messages) or "Site validation failed"
            raise SiteNavigationBindingError("SITE_ASSET_INVALID", detail)

        try:
            canonical = build_site_summary(candidate, validation, active=True)
            manifest = load_yaml(candidate.manifest_path)
            _image_raw, image_path = navigation_image_asset(candidate.root, manifest)
        except Exception as exc:
            raise SiteNavigationBindingError(
                "SITE_ASSET_INVALID", f"cannot resolve validated navigation assets: {exc}"
            ) from exc

        self._require_summary_match(active_summary, canonical)

        navigation_yaml = Path(canonical.navigation_yaml).resolve()
        localization_pcd = Path(canonical.localization_pcd).resolve()
        resolved_image = Path(image_path).resolve()
        processing_record = (
            Path(canonical.processing_record).resolve()
            if canonical.processing_record
            else None
        )

        for label, path in (
            ("navigation YAML", navigation_yaml),
            ("navigation image", resolved_image),
            ("localization PCD", localization_pcd),
        ):
            if not path.is_file():
                raise SiteNavigationBindingError(
                    "SITE_ASSET_INVALID", f"resolved {label} does not exist: {path}"
                )
        if processing_record is not None and not processing_record.is_file():
            raise SiteNavigationBindingError(
                "SITE_ASSET_INVALID",
                f"resolved processing record does not exist: {processing_record}",
            )

        return ResolvedNavigationBinding(
            site_id=canonical.map_id,
            site_revision=canonical.map_version_id,
            site_hash=canonical.map_hash,
            manifest_sha256=canonical.manifest_sha256,
            navigation_yaml=navigation_yaml,
            navigation_yaml_sha256=canonical.navigation_yaml_sha256,
            navigation_image=resolved_image,
            navigation_image_sha256=canonical.navigation_image_sha256,
            localization_pcd=localization_pcd,
            localization_pcd_sha256=canonical.localization_pcd_sha256,
            processing_record=processing_record,
        )

    @staticmethod
    def _require_summary_match(active_summary, canonical) -> None:
        fields = (
            "map_id",
            "map_version_id",
            "map_hash",
            "manifest_sha256",
            "navigation_yaml_sha256",
            "navigation_image_sha256",
            "localization_pcd_sha256",
            "navigation_yaml",
            "localization_pcd",
            "processing_record",
        )
        mismatches = []
        for field_name in fields:
            expected = str(getattr(canonical, field_name, ""))
            actual = str(getattr(active_summary, field_name, ""))
            if actual != expected:
                mismatches.append(field_name)
        if mismatches:
            raise SiteNavigationBindingError(
                "ACTIVE_SITE_IDENTITY_MISMATCH",
                "active Site summary differs from canonical deployed content: "
                + ", ".join(mismatches),
            )
