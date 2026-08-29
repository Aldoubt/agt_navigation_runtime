from __future__ import annotations

import json
from pathlib import Path

from .model import InspectionTask
from .schema import InspectionTaskError, SAFE_COMPONENT_RE, parse_inspection_task


def _safe_component(value: str, name: str) -> str:
    if not isinstance(value, str) or not SAFE_COMPONENT_RE.fullmatch(value):
        raise InspectionTaskError(f"{name} must be a portable identifier")
    return value


class InspectionRepository:
    """Read versioned inspection assets below one immutable map version."""

    def __init__(self, runtime_maps_root: str | Path, map_id: str, map_version_id: str):
        self.root = Path(runtime_maps_root).expanduser().resolve()
        self.map_id = _safe_component(map_id, "map_id")
        self.map_version_id = _safe_component(map_version_id, "map_version_id")
        self.directory = (
            self.root
            / self.map_id
            / "versions"
            / self.map_version_id
            / "inspections"
        )

    def path_for(self, inspection_task_id: str) -> Path:
        component = _safe_component(inspection_task_id, "inspection_task_id")
        return self.directory / f"{component}.json"

    def load(
        self,
        inspection_task_id: str,
        *,
        expected_revision: int = 0,
        expected_content_sha256: str = "",
    ) -> InspectionTask:
        path = self.path_for(inspection_task_id)
        try:
            document = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, UnicodeError, json.JSONDecodeError) as exc:
            raise InspectionTaskError(f"cannot read inspection task JSON: {exc}") from exc

        task = parse_inspection_task(document)
        if task.inspection_task_id != inspection_task_id:
            raise InspectionTaskError("inspection task id does not match repository path")
        if (
            task.map_binding.map_id != self.map_id
            or task.map_binding.map_version_id != self.map_version_id
        ):
            raise InspectionTaskError("inspection task map binding does not match repository map version")
        if expected_revision and task.revision != expected_revision:
            raise InspectionTaskError(
                f"inspection task revision mismatch: expected {expected_revision}, got {task.revision}"
            )
        if expected_content_sha256 and task.content_sha256 != expected_content_sha256:
            raise InspectionTaskError("inspection task content hash mismatch")
        return task
