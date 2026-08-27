from __future__ import annotations

from dataclasses import asdict
import json
import os
from pathlib import Path
import tempfile
from typing import Any, Mapping

from .model import InspectionPoint, InspectionTask
from .schema import InspectionTaskError, SAFE_COMPONENT_RE


def _safe_component(value: str, name: str) -> str:
    if not isinstance(value, str) or not SAFE_COMPONENT_RE.fullmatch(value):
        raise InspectionTaskError(f"{name} must be a portable identifier")
    return value


def _atomic_json(path: Path, value: Mapping[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(
        prefix=f".{path.name}.", suffix=".tmp", dir=path.parent
    )
    temporary_path = Path(temporary)
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as stream:
            json.dump(value, stream, indent=2, ensure_ascii=False, sort_keys=True)
            stream.write("\n")
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary_path, path)
    finally:
        if temporary_path.exists():
            temporary_path.unlink()


class EvidenceWriter:
    """Persist inspection evidence below one caller-owned inspection root.

    ``root`` is normally ``runtime/inspections``. Session and point paths are
    derived only from schema-validated portable ids. The executor owns the
    active session; model/camera responses never choose filesystem paths.
    """

    def __init__(self, root: str | Path = "runtime/inspections") -> None:
        self.root = Path(root).expanduser().resolve()
        self._active_session_id: str | None = None

    def _session_path(self, task: InspectionTask, session_id: str) -> Path:
        task_id = _safe_component(task.inspection_task_id, "inspection_task_id")
        session = _safe_component(session_id, "session_id")
        return self.root / task_id / session

    def start_session(self, task: InspectionTask, session_id: str) -> str:
        session_root = self._session_path(task, session_id)
        session_root.mkdir(parents=True, exist_ok=False)
        self._active_session_id = session_id
        _atomic_json(
            session_root / "session.json",
            {
                "schema_version": 1,
                "session_id": session_id,
                "inspection_task_id": task.inspection_task_id,
                "task_revision": task.revision,
                "content_sha256": task.content_sha256,
                "map_binding": asdict(task.map_binding),
                "state": "RUNNING",
                "success": False,
                "canceled": False,
                "error_code": 0,
                "message": "inspection session running",
            },
        )
        return str(session_root)

    def persist_capture(
        self,
        task: InspectionTask,
        point: InspectionPoint,
        capture_index: int,
        request_id: str,
        capture,
        vision,
    ) -> str:
        if self._active_session_id is None:
            raise RuntimeError("inspection evidence session has not started")
        if capture_index < 0:
            raise ValueError("capture_index must be non-negative")

        point_id = _safe_component(point.id, "point_id")
        point_root = (
            self._session_path(task, self._active_session_id) / point_id
        )
        point_root.mkdir(parents=True, exist_ok=True)

        # Executor indexes captures from zero; evidence names are human-facing 1-based.
        ordinal = capture_index + 1
        stem = f"capture_{ordinal:04d}"

        image_path = ""
        image_bytes = bytes(getattr(capture, "image_bytes", b"") or b"")
        if image_bytes:
            target = point_root / f"{stem}.bin"
            target.write_bytes(image_bytes)
            image_path = str(target)

        result_path = point_root / f"{stem}.result.json"
        _atomic_json(
            result_path,
            {
                "schema_version": 1,
                "inspection_task_id": task.inspection_task_id,
                "task_revision": task.revision,
                "map_id": task.map_binding.map_id,
                "map_version_id": task.map_binding.map_version_id,
                "point_id": point.id,
                "capture_index": ordinal,
                "request_id": request_id,
                "camera_id": point.camera.camera_id,
                "vision_task_id": point.vision.task_id,
                "model_profile": point.vision.model_profile,
                "capture_image_uri": str(
                    getattr(capture, "image_uri", "") or ""
                ),
                "capture_image_path": image_path,
                "model_id": str(getattr(vision, "model_id", "") or ""),
                "model_version": str(
                    getattr(vision, "model_version", "") or ""
                ),
                "inference_time_ms": float(
                    getattr(vision, "inference_time_ms", 0.0) or 0.0
                ),
                "primary_confidence": float(
                    getattr(vision, "primary_confidence", 0.0) or 0.0
                ),
                "result_json": str(
                    getattr(vision, "result_json", "") or ""
                ),
                "message": str(getattr(vision, "message", "") or ""),
            },
        )
        return str(result_path)

    def finish_session(
        self,
        task: InspectionTask,
        session_id: str,
        success: bool,
        error_code: int,
        message: str,
        canceled: bool = False,
    ) -> None:
        session_file = self._session_path(task, session_id) / "session.json"
        try:
            value = json.loads(session_file.read_text(encoding="utf-8"))
        except (OSError, UnicodeError, json.JSONDecodeError):
            value = {
                "schema_version": 1,
                "session_id": session_id,
                "inspection_task_id": task.inspection_task_id,
                "task_revision": task.revision,
                "content_sha256": task.content_sha256,
                "map_binding": asdict(task.map_binding),
            }
        value.update(
            {
                "state": (
                    "CANCELED"
                    if canceled
                    else ("SUCCEEDED" if success else "FAILED")
                ),
                "success": bool(success),
                "canceled": bool(canceled),
                "error_code": int(error_code),
                "message": str(message),
            }
        )
        _atomic_json(session_file, value)
        if self._active_session_id == session_id:
            self._active_session_id = None


RuntimeEvidenceWriter = EvidenceWriter
