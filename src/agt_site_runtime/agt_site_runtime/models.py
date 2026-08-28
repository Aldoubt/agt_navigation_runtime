from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True, order=True)
class SiteKey:
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
