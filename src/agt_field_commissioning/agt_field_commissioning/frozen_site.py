from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

from agt_site_runtime.activation_store import ActivationStore
from agt_site_runtime.models import SiteKey
from agt_site_runtime.registry import SiteRegistry
from agt_site_runtime.summary_builder import STATE_READY, build_site_summary
from agt_site_runtime.validator import SiteValidator


@dataclass(frozen=True)
class FrozenSiteAssets:
    site_id: str
    site_revision: str
    site_hash: str
    navigation_yaml: Path
    navigation_yaml_sha256: str
    navigation_image_sha256: str
    localization_pcd: Path
    localization_pcd_sha256: str
    processing_record: Path | None


def resolve_active_frozen_site(
    *,
    sites_root: str | Path,
    state_root: str | Path,
    site_id: str,
    site_revision: str,
    vehicle_profile: str | Path,
    vehicle_schema: str | Path,
    site_schema: str | Path,
) -> FrozenSiteAssets:
    requested = SiteKey(str(site_id), str(site_revision))
    active = ActivationStore(Path(state_root).expanduser()).load()
    if active is None:
        raise RuntimeError("no persisted active Site selection; activate the Site before Phase C")
    if active.site_id != requested.site_id or active.revision != requested.revision:
        raise RuntimeError(
            "active Site mismatch: "
            f"requested {requested.site_id}/{requested.revision}, "
            f"active is {active.site_id}/{active.revision}"
        )

    candidate = SiteRegistry(Path(sites_root).expanduser()).resolve(requested)
    if candidate is None:
        raise RuntimeError(
            f"active Site is not deployed: {requested.site_id}/{requested.revision}"
        )

    validation = SiteValidator(
        Path(vehicle_profile).expanduser(),
        Path(vehicle_schema).expanduser(),
        Path(site_schema).expanduser(),
    ).validate(candidate)
    if not validation.valid:
        details = "; ".join(validation.blocker_messages) or "unknown validation failure"
        raise RuntimeError(f"active Site validation failed: {details}")

    summary = build_site_summary(candidate, validation, active=True)
    if summary.state != STATE_READY or not summary.valid or not summary.active:
        raise RuntimeError("active Site did not resolve to a READY immutable Site summary")

    navigation_yaml = Path(summary.navigation_yaml).resolve()
    localization_pcd = Path(summary.localization_pcd).resolve()
    processing_record = Path(summary.processing_record).resolve() if summary.processing_record else None

    if not navigation_yaml.is_file():
        raise RuntimeError(f"validated navigation YAML is missing: {navigation_yaml}")
    if not localization_pcd.is_file():
        raise RuntimeError(f"validated localization PCD is missing: {localization_pcd}")
    if processing_record is not None and not processing_record.is_file():
        raise RuntimeError(f"validated processing record is missing: {processing_record}")

    return FrozenSiteAssets(
        site_id=summary.map_id,
        site_revision=summary.map_version_id,
        site_hash=summary.map_hash,
        navigation_yaml=navigation_yaml,
        navigation_yaml_sha256=summary.navigation_yaml_sha256,
        navigation_image_sha256=summary.navigation_image_sha256,
        localization_pcd=localization_pcd,
        localization_pcd_sha256=summary.localization_pcd_sha256,
        processing_record=processing_record,
    )
