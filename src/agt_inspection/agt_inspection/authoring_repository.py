from __future__ import annotations

import json
import os
from pathlib import Path
from typing import Any, Mapping

from .model import InspectionTask
from .repository import InspectionRepository
from .schema import InspectionTaskError, parse_inspection_task


class InspectionAuthoringRepository(InspectionRepository):
    """Validated, revision-guarded writer for inspection assets.

    Execution continues to depend on the read-only ``InspectionRepository`` API.
    This subclass is used only by the field authoring path and publishes a new
    document with one atomic ``os.replace`` after full schema validation.
    """

    def put_document(
        self,
        document: Mapping[str, Any],
        *,
        expected_revision: int,
    ) -> InspectionTask:
        if isinstance(expected_revision, bool) or not isinstance(expected_revision, int) or expected_revision < 0:
            raise InspectionTaskError("expected_revision must be a non-negative integer")
        if not isinstance(document, Mapping):
            raise InspectionTaskError("inspection document must be an object")

        candidate = parse_inspection_task(dict(document))
        if candidate.map_binding.map_id != self.map_id or candidate.map_binding.map_version_id != self.map_version_id:
            raise InspectionTaskError("inspection task map binding does not match authoring repository")
        target = self.path_for(candidate.inspection_task_id)
        if target.is_symlink():
            raise InspectionTaskError("inspection task path must not be a symlink")

        current: InspectionTask | None = None
        if target.exists():
            current = self.load(candidate.inspection_task_id)
            # Lost-response retry: an already committed byte-equivalent revision is success.
            if (
                current.revision == candidate.revision
                and current.content_sha256 == candidate.content_sha256
            ):
                return current
            if current.revision != expected_revision:
                raise InspectionTaskError(
                    f"inspection task revision conflict: expected {expected_revision}, got {current.revision}"
                )
        elif expected_revision != 0:
            raise InspectionTaskError(
                f"inspection task revision conflict: expected {expected_revision}, task does not exist"
            )

        if candidate.revision != expected_revision + 1:
            raise InspectionTaskError(
                "inspection task revision must equal expected_revision + 1"
            )

        payload = (
            json.dumps(dict(document), ensure_ascii=False, indent=2, allow_nan=False)
            + "\n"
        ).encode("utf-8")
        self.directory.mkdir(parents=True, exist_ok=True)
        temporary = target.with_name(f".{target.name}.tmp")
        try:
            with open(temporary, "wb") as stream:
                stream.write(payload)
                stream.flush()
                os.fsync(stream.fileno())
            os.replace(temporary, target)
            try:
                directory_fd = os.open(str(self.directory), os.O_RDONLY)
            except OSError:
                directory_fd = -1
            if directory_fd >= 0:
                try:
                    os.fsync(directory_fd)
                finally:
                    os.close(directory_fd)
        except Exception as exc:
            temporary.unlink(missing_ok=True)
            raise InspectionTaskError(f"cannot persist inspection task: {exc}") from exc

        return self.load(
            candidate.inspection_task_id,
            expected_revision=candidate.revision,
            expected_content_sha256=candidate.content_sha256,
        )
