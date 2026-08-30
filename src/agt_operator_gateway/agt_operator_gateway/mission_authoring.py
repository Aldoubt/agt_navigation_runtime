from __future__ import annotations

import os
from pathlib import Path
from typing import Any, Mapping

import yaml

from agt_mission_manager.mission_model import Mission, validate_component
from agt_mission_manager.mission_schema import canonical_hash, parse_mission

from .task_authoring_model import ActiveTaskSite


def _required_text(value: object, label: str) -> str:
    if not isinstance(value, str) or not value.strip():
        raise ValueError(f"{label} must be a non-empty string")
    return value.strip()


def _positive_revision(value: object, label: str) -> int:
    if isinstance(value, bool) or not isinstance(value, int) or value <= 0:
        raise ValueError(f"{label} must be a positive integer")
    return value


def build_inspection_mission_document(
    *,
    site: ActiveTaskSite,
    inspection_task_id: str,
    inspection_revision: int,
    inspection_content_sha256: str,
    home_binding: Mapping[str, Any],
) -> dict[str, Any]:
    task_id = _required_text(inspection_task_id, "inspection_task_id")
    revision = _positive_revision(inspection_revision, "inspection_revision")
    inspection_hash = _required_text(
        inspection_content_sha256,
        "inspection_content_sha256",
    )
    home_task_id = _required_text(home_binding.get("taskGroupId"), "home taskGroupId")
    home_revision = _positive_revision(home_binding.get("revision"), "home revision")
    home_hash = _required_text(home_binding.get("contentSha256"), "home contentSha256")
    if not site.site_hash.startswith("sha256:") or len(site.site_hash) != 71:
        raise ValueError("active Site manifest SHA256 is required for mission authoring")

    mission_id = f"{task_id}-mission"
    mission_version = f"r{revision:04d}"
    document: dict[str, Any] = {
        "schema_version": 1,
        "mission_id": mission_id,
        "mission_version": mission_version,
        "content_sha256": "sha256:" + "0" * 64,
        "map_binding": {
            "map_id": site.site_id,
            "map_version_id": site.site_revision,
            "manifest_sha256": site.site_hash,
        },
        "steps": [
            {
                "id": "inspect",
                "type": "INSPECTION_TASK",
                "inspection_task_id": task_id,
                "inspection_task_revision": revision,
                "expected_content_sha256": inspection_hash,
            },
            {
                "id": "return_home",
                "type": "RETURN_HOME",
                "task_group_id": home_task_id,
                "task_group_revision": home_revision,
                "expected_content_sha256": home_hash,
            },
        ],
    }
    document["content_sha256"] = canonical_hash(document)
    parse_mission(document)
    return document


class MissionAuthoringRepository:
    """Immutable, atomically published Mission writer used by field authoring.

    Mission Manager remains the sole execution owner. This writer only creates
    validated versioned assets under the existing runtime/missions layout.
    A mission version is immutable: an exact retry is accepted, while different
    content at the same path is rejected.
    """

    def __init__(self, root: str | Path) -> None:
        self.root = Path(root).expanduser().resolve()

    def path_for(self, mission_id: str, mission_version: str) -> Path:
        safe_id = validate_component(mission_id, "mission_id")
        safe_version = validate_component(mission_version, "mission_version")
        return self.root / safe_id / safe_version / "mission.yaml"

    def put_document(self, document: Mapping[str, Any]) -> Mission:
        if not isinstance(document, Mapping):
            raise ValueError("mission document must be an object")
        candidate = parse_mission(dict(document))
        target = self.path_for(candidate.mission_id, candidate.mission_version)
        if target.is_symlink():
            raise ValueError("mission path must not be a symlink")
        if target.exists():
            try:
                existing_raw = yaml.safe_load(target.read_text(encoding="utf-8"))
            except Exception as exc:
                raise ValueError(f"cannot read existing mission: {exc}") from exc
            existing = parse_mission(existing_raw)
            if existing.content_sha256 == candidate.content_sha256:
                return existing
            raise ValueError(
                "mission version already exists with different content; create a new inspection revision"
            )

        payload = yaml.safe_dump(
            dict(document),
            allow_unicode=True,
            sort_keys=False,
        ).encode("utf-8")
        target.parent.mkdir(parents=True, exist_ok=True)
        temporary = target.with_name(".mission.yaml.tmp")
        try:
            with open(temporary, "wb") as stream:
                stream.write(payload)
                stream.flush()
                os.fsync(stream.fileno())
            os.replace(temporary, target)
            directory_fd = os.open(str(target.parent), os.O_RDONLY)
            try:
                os.fsync(directory_fd)
            finally:
                os.close(directory_fd)
        except Exception as exc:
            temporary.unlink(missing_ok=True)
            raise ValueError(f"cannot persist mission: {exc}") from exc
        return parse_mission(yaml.safe_load(target.read_text(encoding="utf-8")))
