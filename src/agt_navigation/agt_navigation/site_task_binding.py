"""Validated immutable Site identity used by the mutable Task Library.

This module keeps Task persistence independent from Site Package storage.  The
public task interfaces still use ``map_id`` / ``map_version_id`` for backward
compatibility; within P1 they identify ``site.id`` / ``site.revision``.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import re
from typing import Callable, Optional


_SAFE_COMPONENT_RE = re.compile(r"^[A-Za-z0-9._-]+$")
_SHA256_RE = re.compile(r"^[0-9a-f]{64}$")


class SiteTaskBindingError(RuntimeError):
    """Stable fail-closed error raised while resolving a task's Site binding."""

    def __init__(self, code: str, message: str) -> None:
        super().__init__(message)
        self.code = str(code)
        self.message = str(message)


def normalize_sha256(value: str) -> str:
    text = str(value or "").strip().lower()
    if text.startswith("sha256:"):
        text = text[7:]
    if _SHA256_RE.fullmatch(text) is None:
        raise SiteTaskBindingError(
            "TASK_SITE_BINDING_INVALID", "Site binding contains an invalid SHA256 digest"
        )
    return "sha256:" + text


@dataclass(frozen=True)
class ValidatedSiteBinding:
    map_id: str
    map_version_id: str
    map_hash: str
    manifest_sha256: str
    navigation_yaml_sha256: str
    navigation_image_sha256: str
    localization_pcd_sha256: str

    def __post_init__(self) -> None:
        if (
            not self.map_id
            or not self.map_version_id
            or _SAFE_COMPONENT_RE.fullmatch(self.map_id) is None
            or _SAFE_COMPONENT_RE.fullmatch(self.map_version_id) is None
        ):
            raise SiteTaskBindingError(
                "TASK_SITE_BINDING_INVALID",
                "Site task binding requires safe non-empty map_id and map_version_id",
            )
        for field_name in (
            "map_hash",
            "manifest_sha256",
            "navigation_yaml_sha256",
            "navigation_image_sha256",
            "localization_pcd_sha256",
        ):
            object.__setattr__(self, field_name, normalize_sha256(getattr(self, field_name)))

    def to_dict(self) -> dict:
        return {
            "schema_version": 1,
            "map_id": self.map_id,
            "map_version_id": self.map_version_id,
            "map_hash": self.map_hash,
            "manifest_sha256": self.manifest_sha256,
            "navigation_yaml_sha256": self.navigation_yaml_sha256,
            "navigation_image_sha256": self.navigation_image_sha256,
            "localization_pcd_sha256": self.localization_pcd_sha256,
        }

    @classmethod
    def from_dict(cls, value: object) -> "ValidatedSiteBinding":
        if not isinstance(value, dict) or value.get("schema_version") != 1:
            raise SiteTaskBindingError(
                "TASK_SITE_BINDING_INVALID", "unsupported or malformed site_binding.json"
            )
        try:
            return cls(
                map_id=str(value["map_id"]),
                map_version_id=str(value["map_version_id"]),
                map_hash=str(value["map_hash"]),
                manifest_sha256=str(value["manifest_sha256"]),
                navigation_yaml_sha256=str(value["navigation_yaml_sha256"]),
                navigation_image_sha256=str(value["navigation_image_sha256"]),
                localization_pcd_sha256=str(value["localization_pcd_sha256"]),
            )
        except KeyError as exc:
            raise SiteTaskBindingError(
                "TASK_SITE_BINDING_INVALID", f"site_binding.json is missing {exc.args[0]}"
            ) from exc


SummaryResolver = Callable[[str, str], object | None]


class FilesystemSiteBindingResolver:
    """Resolve one deployed, validated Site revision into task-binding identity.

    Imports Site Runtime lazily so pure Task Registry tests do not require a ROS
    installation or an installed Site Runtime package.  ``summary_resolver`` is a
    narrow test seam and may also be used by offline tooling.
    """

    def __init__(
        self,
        *,
        sites_root: str | Path,
        vehicle_profile: str | Path,
        vehicle_schema: str | Path,
        site_schema: str | Path,
        summary_resolver: Optional[SummaryResolver] = None,
    ) -> None:
        self.sites_root = Path(sites_root).expanduser()
        self.vehicle_profile = Path(vehicle_profile).expanduser()
        self.vehicle_schema = Path(vehicle_schema).expanduser()
        self.site_schema = Path(site_schema).expanduser()
        self._summary_resolver = summary_resolver

    def __call__(self, map_id: str, map_version_id: str) -> ValidatedSiteBinding:
        requested_id = str(map_id)
        requested_revision = str(map_version_id)
        try:
            summary = (
                self._summary_resolver(requested_id, requested_revision)
                if self._summary_resolver is not None
                else self._resolve_summary(requested_id, requested_revision)
            )
        except SiteTaskBindingError:
            raise
        except Exception as exc:
            raise SiteTaskBindingError(
                "MAP_NOT_READY", f"cannot validate deployed Site: {exc}"
            ) from exc

        if summary is None:
            raise SiteTaskBindingError(
                "MAP_NOT_READY",
                f"deployed Site revision not found: {requested_id}/{requested_revision}",
            )
        summary_id = str(getattr(summary, "map_id", ""))
        summary_revision = str(getattr(summary, "map_version_id", ""))
        if summary_id != requested_id or summary_revision != requested_revision:
            raise SiteTaskBindingError(
                "MAP_VERSION_MISMATCH",
                "validated Site identity does not match the requested task binding",
            )
        if int(getattr(summary, "state", 0)) != 3 or not bool(
            getattr(summary, "valid", False)
        ):
            errors = getattr(summary, "validation_errors", ()) or ()
            detail = "; ".join(str(item) for item in errors) or "Site is not READY and valid"
            raise SiteTaskBindingError("MAP_NOT_READY", detail)

        try:
            return ValidatedSiteBinding(
                map_id=summary_id,
                map_version_id=summary_revision,
                map_hash=str(getattr(summary, "map_hash", "")),
                manifest_sha256=str(getattr(summary, "manifest_sha256", "")),
                navigation_yaml_sha256=str(
                    getattr(summary, "navigation_yaml_sha256", "")
                ),
                navigation_image_sha256=str(
                    getattr(summary, "navigation_image_sha256", "")
                ),
                localization_pcd_sha256=str(
                    getattr(summary, "localization_pcd_sha256", "")
                ),
            )
        except SiteTaskBindingError as exc:
            raise SiteTaskBindingError(
                "MAP_NOT_READY", f"validated Site lacks complete content identity: {exc}"
            ) from exc

    def _resolve_summary(self, map_id: str, map_version_id: str):
        from agt_site_runtime.models import SiteKey
        from agt_site_runtime.registry import SiteRegistry
        from agt_site_runtime.summary_builder import build_site_summary
        from agt_site_runtime.validator import SiteValidator

        candidate = SiteRegistry(self.sites_root).resolve(SiteKey(map_id, map_version_id))
        if candidate is None:
            return None
        validation = SiteValidator(
            self.vehicle_profile, self.vehicle_schema, self.site_schema
        ).validate(candidate)
        if not validation.valid:
            detail = "; ".join(validation.blocker_messages) or "Site validation failed"
            raise SiteTaskBindingError("MAP_NOT_READY", detail)
        return build_site_summary(candidate, validation, active=False)
