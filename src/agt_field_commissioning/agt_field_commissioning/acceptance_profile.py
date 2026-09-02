"""Strict, motion-free field acceptance profile loader.

The profile only selects an immutable Site revision, a map-bound relocalization
candidate document, and a saved Task Registry id.  It deliberately has no
motion/start field; execution remains an explicit operator action in RViz.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import re

import yaml


_SAFE_COMPONENT = re.compile(r"^[A-Za-z0-9._-]+$")
_SHA256 = re.compile(r"^(?:sha256:)?[0-9a-fA-F]{64}$")
_ALLOWED_FIELDS = {
    "schema_version",
    "site_id",
    "site_revision",
    "initial_pose_candidates_yaml",
    "task_group_id",
    "auto_load_task",
}
_REQUIRED_FIELDS = {
    "schema_version",
    "site_id",
    "site_revision",
    "initial_pose_candidates_yaml",
    "task_group_id",
    "auto_load_task",
}


class AcceptanceProfileError(ValueError):
    pass


@dataclass(frozen=True)
class AcceptanceProfile:
    site_id: str
    site_revision: str
    initial_pose_candidates_yaml: Path
    task_group_id: str
    auto_load_task: bool


def _safe_component(value: object, field_name: str) -> str:
    if not isinstance(value, str) or not value.strip():
        raise AcceptanceProfileError(f"{field_name} must be a non-empty string")
    text = value.strip()
    if _SAFE_COMPONENT.fullmatch(text) is None:
        raise AcceptanceProfileError(f"{field_name} contains unsafe characters")
    return text


def _load_yaml(path: Path, label: str) -> dict:
    try:
        document = yaml.safe_load(path.read_text(encoding="utf-8"))
    except (OSError, UnicodeError, yaml.YAMLError) as exc:
        raise AcceptanceProfileError(f"cannot read {label}: {exc}") from exc
    if not isinstance(document, dict):
        raise AcceptanceProfileError(f"{label} must contain a YAML object")
    return document


def _validate_candidate_document(path: Path, site_id: str) -> None:
    candidate = _load_yaml(path, "initial pose candidates YAML")
    if candidate.get("schema_version") != 1:
        raise AcceptanceProfileError("initial pose candidates YAML must use schema_version 1")
    if candidate.get("map_id") != site_id:
        raise AcceptanceProfileError(
            "initial pose candidates map_id must match acceptance profile site_id"
        )
    map_hash = candidate.get("map_hash")
    if not isinstance(map_hash, str) or _SHA256.fullmatch(map_hash.strip()) is None:
        raise AcceptanceProfileError("initial pose candidates map_hash must be a SHA256 digest")
    seeds = candidate.get("candidates")
    if not isinstance(seeds, list) or not seeds:
        raise AcceptanceProfileError("initial pose candidates must contain at least one seed")


def load_acceptance_profile(path: str | Path) -> AcceptanceProfile:
    profile_path = Path(path).expanduser().resolve()
    if not profile_path.is_file():
        raise AcceptanceProfileError(f"acceptance profile does not exist: {profile_path}")
    document = _load_yaml(profile_path, "acceptance profile")

    unexpected = sorted(set(document) - _ALLOWED_FIELDS)
    if unexpected:
        raise AcceptanceProfileError(
            f"acceptance profile contains unsupported field: {unexpected[0]}"
        )
    missing = sorted(_REQUIRED_FIELDS - set(document))
    if missing:
        raise AcceptanceProfileError(
            f"acceptance profile is missing required field: {missing[0]}"
        )
    if document.get("schema_version") != 1:
        raise AcceptanceProfileError("unsupported acceptance profile schema_version")

    site_id = _safe_component(document.get("site_id"), "site_id")
    site_revision = _safe_component(document.get("site_revision"), "site_revision")
    task_group_id = _safe_component(document.get("task_group_id"), "task_group_id")
    auto_load_task = document.get("auto_load_task")
    if not isinstance(auto_load_task, bool):
        raise AcceptanceProfileError("auto_load_task must be boolean")

    candidate_value = document.get("initial_pose_candidates_yaml")
    if not isinstance(candidate_value, str) or not candidate_value.strip():
        raise AcceptanceProfileError(
            "initial_pose_candidates_yaml must be a non-empty path"
        )
    candidate_path = Path(candidate_value).expanduser()
    if not candidate_path.is_absolute():
        candidate_path = profile_path.parent / candidate_path
    candidate_path = candidate_path.resolve()
    if not candidate_path.is_file():
        raise AcceptanceProfileError(
            f"initial pose candidates YAML does not exist: {candidate_path}"
        )
    _validate_candidate_document(candidate_path, site_id)

    return AcceptanceProfile(
        site_id=site_id,
        site_revision=site_revision,
        initial_pose_candidates_yaml=candidate_path,
        task_group_id=task_group_id,
        auto_load_task=auto_load_task,
    )
