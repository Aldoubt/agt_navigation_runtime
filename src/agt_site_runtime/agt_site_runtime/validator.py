from __future__ import annotations

from collections import OrderedDict
from pathlib import Path
from typing import Iterable

from agt_runtime_contracts.validator import (
    ValidationIssue,
    load_yaml,
    validate_runtime_contracts,
)

from .models import SiteCandidate, SiteValidation


_BLOCKER_BY_CONTRACT_CODE = {
    "SITE_SCHEMA": "SITE_SCHEMA_INVALID",
    "ABSOLUTE_PATH": "SITE_PATH_UNSAFE",
    "PATH_ESCAPE": "SITE_PATH_UNSAFE",
    "MISSING_ASSET": "SITE_ASSET_MISSING",
    "HASH_MISSING": "SITE_HASH_MISSING",
    "HASH_FORMAT": "SITE_HASH_MISSING",
    "HASHES_FILE": "SITE_HASH_MISSING",
    "HASH_MISMATCH": "SITE_HASH_MISMATCH",
    "INCOMPATIBLE_VEHICLE": "SITE_VEHICLE_INCOMPATIBLE",
    "NAVIGATION_MAP": "SITE_NAVIGATION_MAP_INVALID",
}


class SiteValidator:
    """Validate one candidate already discovered below the deployed sites root."""

    def __init__(
        self,
        vehicle_profile: Path,
        vehicle_schema: Path,
        site_schema: Path,
    ):
        self.vehicle_profile = Path(vehicle_profile)
        self.vehicle_schema = Path(vehicle_schema)
        self.site_schema = Path(site_schema)

    def validate(self, candidate: SiteCandidate) -> SiteValidation:
        identity_result = self._validate_identity(candidate)
        if identity_result is not None:
            return identity_result

        report = validate_runtime_contracts(
            self.vehicle_profile,
            candidate.root,
            self.vehicle_schema,
            self.site_schema,
        )
        if report.ok:
            return SiteValidation(
                candidate=candidate,
                valid=True,
                checks=tuple(report.checks),
            )

        codes, messages = self._stable_blockers(report.issues)
        return SiteValidation(
            candidate=candidate,
            valid=False,
            blocker_codes=codes,
            blocker_messages=messages,
            checks=tuple(report.checks),
        )

    @staticmethod
    def _validate_identity(candidate: SiteCandidate) -> SiteValidation | None:
        try:
            manifest = load_yaml(candidate.manifest_path)
        except (OSError, ValueError) as exc:
            return SiteValidation(
                candidate=candidate,
                valid=False,
                blocker_codes=("SITE_SCHEMA_INVALID",),
                blocker_messages=(str(exc),),
            )

        site = manifest.get("site")
        if not isinstance(site, dict):
            # Let the canonical schema validator report the malformed shape.
            return None
        manifest_id = site.get("id")
        manifest_revision = site.get("revision")
        if not isinstance(manifest_id, str) or not isinstance(manifest_revision, str):
            return None
        if (
            manifest_id != candidate.key.site_id
            or manifest_revision != candidate.key.revision
        ):
            return SiteValidation(
                candidate=candidate,
                valid=False,
                blocker_codes=("SITE_IDENTITY_MISMATCH",),
                blocker_messages=(
                    "deployed directory identity does not match manifest.site: "
                    f"directory={candidate.key.site_id}/{candidate.key.revision}, "
                    f"manifest={manifest_id}/{manifest_revision}",
                ),
            )
        return None

    @staticmethod
    def _stable_blockers(
        issues: Iterable[ValidationIssue],
    ) -> tuple[tuple[str, ...], tuple[str, ...]]:
        grouped: OrderedDict[str, list[str]] = OrderedDict()
        for issue in issues:
            code = _BLOCKER_BY_CONTRACT_CODE.get(issue.code, "SITE_VALIDATION_FAILED")
            grouped.setdefault(code, []).append(issue.message)

        if not grouped:
            return ("SITE_VALIDATION_FAILED",), ("Site Package validation failed",)

        return (
            tuple(grouped.keys()),
            tuple("; ".join(messages) for messages in grouped.values()),
        )
