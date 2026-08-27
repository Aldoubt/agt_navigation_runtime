from __future__ import annotations

import json
import os
from pathlib import Path
import tempfile
from typing import Any

from .execution import CaptureResult, VisionResult
from .model import InspectionPoint, InspectionTask


def _atomic_json(path: Path, value: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix=path.name + ".", dir=str(path.parent))
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as stream:
            json.dump(value, stream, indent=2, ensure_ascii=False, sort_keys=True)
            stream.write("\n")
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary, path)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)


class RuntimeEvidenceWriter:
    """Persist inspection evidence under one Runtime-owned root.

    Paths are derived only from already-validated portable ids supplied by the
    inspection schema/repository; callers do not pass arbitrary evidence paths.
    """

    def __init__(self, runtime_root: str | Path = "runtime") -> None:
        self._root = Path(runtime_root).expanduser().resolve() / "inspections"
        self._session_root: Path | None = None

    def start_session(self, task: InspectionTask, session_id: str) -> str:
        if not session_id or "/" in session_id or "\\" in session_id or session_id in {".", ".."}:
            raise ValueError("session_id must be one portable path component")
        root = self._root / task.map_binding.map_id / task.inspection_task_id / session_id
        root.mkdir(parents=True, exist_ok=False)
        self._session_root = root
        _atomic_json(
            root / "session.json",
            {
                "schema_version": 1,
                "session_id": session_id,
                "inspection_task_id": task.inspection_task_id,
                "task_revision": task.revision,
                "content_sha256": task.content_sha256,
                "map_id": task.map_binding.map_id,
                "map_version_id": task.map_binding.map_version_id,
                "map_manifest_sha256": task.map_binding.manifest_sha256,
                "state": "RUNNING",
                "success": False,
                "error_code": 0,
                "message": "",
            },
        )
        return str(root)

    def persist_capture(
        self,
        task: InspectionTask,
        point: InspectionPoint,
        capture_index: int,
        request_id: str,
        capture: CaptureResult,
        vision: VisionResult,
    ) -> None:
        root = self._require_session()
        point_root = root / point.id
        point_root.mkdir(parents=True, exist_ok=True)
        stem = f"capture_{capture_index:03d}"
        image_uri = capture.image_uri
        if capture.image_payload:
            image_path = point_root / f"{stem}.bin"
            image_path.write_bytes(capture.image_payload)
            image_uri = str(image_path)
        _atomic_json(
            point_root / f"{stem}.json",
            {
                "schema_version": 1,
                "inspection_task_id": task.inspection_task_id,
                "point_id": point.id,
                "capture_index": capture_index,
                "request_id": request_id,
                "camera_id": point.camera.camera_id,
                "vision_task_id": point.vision.task_id,
                "model_profile": point.vision.model_profile,
                "image_uri": image_uri,
                "model_id": vision.model_id,
                "model_version": vision.model_version,
                "inference_time_ms": vision.inference_time_ms,
                "primary_confidence": vision.primary_confidence,
                "result_json": vision.result_json,
            },
        )

    def finish_session(
        self,
        task: InspectionTask,
        session_id: str,
        success: bool,
        error_code: int,
        message: str,
    ) -> None:
        root = self._require_session()
        session_file = root / "session.json"
        value = json.loads(session_file.read_text(encoding="utf-8"))
        value.update(
            {
                "state": "SUCCEEDED" if success else "FAILED",
                "success": bool(success),
                "error_code": int(error_code),
                "message": str(message),
            }
        )
        _atomic_json(session_file, value)

    def _require_session(self) -> Path:
        if self._session_root is None:
            raise RuntimeError("inspection evidence session has not started")
        return self._session_root
