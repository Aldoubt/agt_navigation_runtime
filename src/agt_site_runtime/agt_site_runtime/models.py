from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True, order=True)
class SiteKey:
    site_id: str
    revision: str


@dataclass(frozen=True)
class ActiveSelection:
    site_id: str
    revision: str


@dataclass(frozen=True)
class SiteCandidate:
    key: SiteKey
    root: Path
    manifest_path: Path


@dataclass(frozen=True)
class SiteValidation:
    candidate: SiteCandidate
    valid: bool
    blocker_codes: tuple[str, ...] = ()
    blocker_messages: tuple[str, ...] = ()
    checks: tuple[str, ...] = ()


@dataclass(frozen=True)
class SiteSummary:
    map_id: str
    map_version_id: str
    parent_map_version_id: str = ""
    state: int = 0
    active: bool = False
    pinned: bool = False
    deleted: bool = False
    valid: bool = False
    map_hash: str = ""
    manifest_sha256: str = ""
    navigation_yaml_sha256: str = ""
    navigation_image_sha256: str = ""
    localization_pcd_sha256: str = ""
    navigation_yaml: str = ""
    localization_pcd: str = ""
    processing_record: str = ""
    tasks_directory: str = ""
    storage_bytes: int = 0
    created_at: str = ""
    validation_errors: tuple[str, ...] = ()
    validation_warnings: tuple[str, ...] = ()
