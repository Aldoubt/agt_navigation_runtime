from __future__ import annotations

import csv
import json
import os
from pathlib import Path
import tempfile
from typing import Any, Mapping

from .schema import SAFE_COMPONENT_RE, SHA256_RE


class MultiviewEvidenceError(ValueError):
    pass


def _component(value: object, name: str) -> str:
    if not isinstance(value, str) or not SAFE_COMPONENT_RE.fullmatch(value):
        raise MultiviewEvidenceError(f"{name} must be a portable identifier")
    return value


def _sha256(value: object, name: str) -> str:
    if not isinstance(value, str) or not SHA256_RE.fullmatch(value):
        raise MultiviewEvidenceError(f"{name} must be sha256:<64 lowercase hex>")
    return value


def _mapping(value: object, name: str) -> Mapping[str, Any]:
    if not isinstance(value, Mapping):
        raise MultiviewEvidenceError(f"{name} must be an object")
    return value


def _atomic_json(path: Path, value: Mapping[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix=f".{path.name}.", suffix=".tmp", dir=path.parent)
    temporary_path = Path(temporary)
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as stream:
            json.dump(value, stream, ensure_ascii=False, sort_keys=True, indent=2)
            stream.write("\n")
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary_path, path)
    finally:
        if temporary_path.exists():
            temporary_path.unlink()


def _atomic_bytes(path: Path, payload: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix=f".{path.name}.", suffix=".tmp", dir=path.parent)
    temporary_path = Path(temporary)
    try:
        with os.fdopen(fd, "wb") as stream:
            stream.write(payload)
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary_path, path)
    finally:
        if temporary_path.exists():
            temporary_path.unlink()


def _write_csv(path: Path, fieldnames: list[str], rows: list[Mapping[str, Any]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix=f".{path.name}.", suffix=".tmp", dir=path.parent)
    temporary_path = Path(temporary)
    try:
        with os.fdopen(fd, "w", encoding="utf-8", newline="") as stream:
            writer = csv.DictWriter(stream, fieldnames=fieldnames)
            writer.writeheader()
            for row in rows:
                writer.writerow({name: row.get(name, "") for name in fieldnames})
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary_path, path)
    finally:
        if temporary_path.exists():
            temporary_path.unlink()


class InspectionEvidenceStore:
    """Canonical v1 evidence layout for single-view + point-local multi-view results.

    This store intentionally does not own image encoding or the visual model. The
    camera/vision adapter supplies bytes/URIs and normalized metadata; the store
    owns safe paths, evidence identity, aggregation records and report exports.
    """

    SESSION_KEYS = {
        "schema_version",
        "session_id",
        "inspection_task_id",
        "task_revision",
        "task_content_sha256",
        "map_id",
        "map_version_id",
        "map_manifest_sha256",
        "count_target",
    }

    def __init__(self, root: str | Path = "runtime/inspections") -> None:
        self.root = Path(root).expanduser().resolve()
        self._session: dict[str, Any] | None = None
        self._session_root: Path | None = None

    def start_session(self, session: Mapping[str, Any]) -> Path:
        value = dict(_mapping(session, "session"))
        unknown = set(value) - self.SESSION_KEYS
        missing = self.SESSION_KEYS - set(value)
        if unknown or missing:
            raise MultiviewEvidenceError(
                f"session keys are invalid; missing={sorted(missing)}, unknown={sorted(unknown)}"
            )
        if value["schema_version"] != 1:
            raise MultiviewEvidenceError("unsupported session schema_version")
        value["session_id"] = _component(value["session_id"], "session_id")
        value["inspection_task_id"] = _component(
            value["inspection_task_id"], "inspection_task_id"
        )
        value["map_id"] = _component(value["map_id"], "map_id")
        value["map_version_id"] = _component(value["map_version_id"], "map_version_id")
        value["count_target"] = _component(value["count_target"], "count_target")
        if isinstance(value["task_revision"], bool) or not isinstance(value["task_revision"], int) or value["task_revision"] <= 0:
            raise MultiviewEvidenceError("task_revision must be a positive integer")
        value["task_content_sha256"] = _sha256(
            value["task_content_sha256"], "task_content_sha256"
        )
        value["map_manifest_sha256"] = _sha256(
            value["map_manifest_sha256"], "map_manifest_sha256"
        )

        session_root = self.root / value["inspection_task_id"] / value["session_id"]
        session_root.mkdir(parents=True, exist_ok=False)
        (session_root / "points").mkdir()
        (session_root / "report").mkdir()
        value.update(
            {
                "state": "RUNNING",
                "count_levels": ["VIEW_RAW", "POINT_DEDUP"],
            }
        )
        _atomic_json(session_root / "session.json", value)
        self._session = value
        self._session_root = session_root
        return session_root

    def write_view(
        self,
        point_id: str,
        view_id: str,
        observation: Mapping[str, Any],
        *,
        image_bytes: bytes = b"",
        overlay_bytes: bytes = b"",
        mask_bytes: bytes = b"",
        image_suffix: str = ".bin",
        overlay_suffix: str = ".bin",
        mask_suffix: str = ".bin",
    ) -> str:
        session, session_root = self._require_session()
        point = _component(point_id, "point_id")
        view = _component(view_id, "view_id")
        value = dict(_mapping(observation, "observation"))
        if value.get("schema_version") != 1:
            raise MultiviewEvidenceError("unsupported view schema_version")
        if value.get("view_id") != view:
            raise MultiviewEvidenceError("observation view_id does not match storage path")

        vision = _mapping(value.get("vision"), "observation.vision")
        raw_count = vision.get("raw_count")
        if isinstance(raw_count, bool) or not isinstance(raw_count, int) or raw_count < 0:
            raise MultiviewEvidenceError("observation.vision.raw_count must be non-negative integer")

        view_root = session_root / "points" / point / view
        view_root.mkdir(parents=True, exist_ok=False)
        evidence = dict(_mapping(value.get("evidence", {}), "observation.evidence"))

        if image_bytes:
            image_name = "original" + self._suffix(image_suffix, "image_suffix")
            _atomic_bytes(view_root / image_name, bytes(image_bytes))
            evidence["image"] = image_name
        if overlay_bytes:
            overlay_name = "overlay" + self._suffix(overlay_suffix, "overlay_suffix")
            _atomic_bytes(view_root / overlay_name, bytes(overlay_bytes))
            evidence["overlay"] = overlay_name
        if mask_bytes:
            mask_name = "mask" + self._suffix(mask_suffix, "mask_suffix")
            _atomic_bytes(view_root / mask_name, bytes(mask_bytes))
            evidence["mask"] = mask_name

        value["session_id"] = session["session_id"]
        value["inspection_task_id"] = session["inspection_task_id"]
        value["map_id"] = session["map_id"]
        value["map_version_id"] = session["map_version_id"]
        value["point_id"] = point
        value["evidence"] = evidence
        result_path = view_root / "result.json"
        _atomic_json(result_path, value)
        return str(result_path)

    def write_aggregation(
        self,
        point_id: str,
        aggregation: Mapping[str, Any],
        *,
        association_overlay_bytes: bytes = b"",
        overlay_suffix: str = ".bin",
    ) -> str:
        session, session_root = self._require_session()
        point = _component(point_id, "point_id")
        value = dict(_mapping(aggregation, "aggregation"))
        if value.get("schema_version") != 1:
            raise MultiviewEvidenceError("unsupported aggregation schema_version")
        if value.get("aggregation_scope") != "POINT_LOCAL":
            raise MultiviewEvidenceError("aggregation_scope must be POINT_LOCAL in schema v1")
        for name in (
            "raw_instance_count",
            "unique_instance_count",
            "ambiguous_instance_count",
        ):
            number = value.get(name)
            if isinstance(number, bool) or not isinstance(number, int) or number < 0:
                raise MultiviewEvidenceError(f"aggregation.{name} must be non-negative integer")
        confidence = value.get("association_confidence")
        if isinstance(confidence, bool) or not isinstance(confidence, (int, float)) or not 0.0 <= float(confidence) <= 1.0:
            raise MultiviewEvidenceError("aggregation.association_confidence must be in [0, 1]")

        aggregation_root = session_root / "points" / point / "aggregation"
        aggregation_root.mkdir(parents=True, exist_ok=True)
        value["session_id"] = session["session_id"]
        value["inspection_task_id"] = session["inspection_task_id"]
        value["map_id"] = session["map_id"]
        value["map_version_id"] = session["map_version_id"]
        value["point_id"] = point
        if association_overlay_bytes:
            name = "association_overlay" + self._suffix(overlay_suffix, "overlay_suffix")
            _atomic_bytes(aggregation_root / name, bytes(association_overlay_bytes))
            value["association_overlay"] = name
        result_path = aggregation_root / "result.json"
        _atomic_json(result_path, value)
        return str(result_path)

    def build_report(self) -> str:
        session, session_root = self._require_session()
        point_rows: list[dict[str, Any]] = []
        view_rows: list[dict[str, Any]] = []
        instance_rows: list[dict[str, Any]] = []
        point_documents: list[dict[str, Any]] = []

        points_root = session_root / "points"
        point_dirs = sorted(path for path in points_root.iterdir() if path.is_dir())
        aggregated_points = 0
        total_raw = 0
        total_unique = 0
        total_ambiguous = 0

        for point_root in point_dirs:
            point_id = point_root.name
            views: list[dict[str, Any]] = []
            for view_root in sorted(path for path in point_root.iterdir() if path.is_dir() and path.name != "aggregation"):
                result_path = view_root / "result.json"
                if not result_path.is_file():
                    continue
                value = json.loads(result_path.read_text(encoding="utf-8"))
                views.append(value)
                pose = _mapping(value.get("robot_pose_map", {}), "robot_pose_map")
                gimbal = _mapping(value.get("gimbal", {}), "gimbal")
                vision = _mapping(value.get("vision", {}), "vision")
                view_rows.append(
                    {
                        "point_id": point_id,
                        "view_id": value.get("view_id", view_root.name),
                        "capture_stamp": value.get("capture_stamp", ""),
                        "robot_x": pose.get("x", ""),
                        "robot_y": pose.get("y", ""),
                        "robot_yaw": pose.get("yaw", ""),
                        "pan_rad": gimbal.get("pan_rad", ""),
                        "tilt_rad": gimbal.get("tilt_rad", ""),
                        "raw_count": vision.get("raw_count", 0),
                        "model_id": vision.get("model_id", ""),
                        "model_version": vision.get("model_version", ""),
                        "inference_time_ms": vision.get("inference_time_ms", ""),
                    }
                )

            raw_from_views = sum(int(_mapping(item.get("vision", {}), "vision").get("raw_count", 0)) for item in views)
            aggregation_path = point_root / "aggregation" / "result.json"
            aggregation = None
            if aggregation_path.is_file():
                aggregation = json.loads(aggregation_path.read_text(encoding="utf-8"))
                aggregated_points += 1
                raw_count = int(aggregation["raw_instance_count"])
                unique_count: int | str = int(aggregation["unique_instance_count"])
                ambiguous_count: int | str = int(aggregation["ambiguous_instance_count"])
                total_unique += int(unique_count)
                total_ambiguous += int(ambiguous_count)
                for global_instance in aggregation.get("global_instances", []):
                    global_id = str(global_instance.get("global_instance_id", ""))
                    for member in global_instance.get("members", []):
                        instance_rows.append(
                            {
                                "point_id": point_id,
                                "global_instance_id": global_id,
                                "status": global_instance.get("status", ""),
                                "association_confidence": global_instance.get("association_confidence", ""),
                                "view_id": member.get("view_id", ""),
                                "local_instance_id": member.get("local_instance_id", ""),
                            }
                        )
            else:
                raw_count = raw_from_views
                unique_count = ""
                ambiguous_count = ""

            total_raw += int(raw_count)
            point_rows.append(
                {
                    "point_id": point_id,
                    "views": len(views),
                    "raw_count": raw_count,
                    "unique_count": unique_count,
                    "ambiguous_count": ambiguous_count,
                }
            )
            point_documents.append(
                {
                    "point_id": point_id,
                    "view_count": len(views),
                    "raw_instance_count": raw_count,
                    "unique_instance_count": unique_count if unique_count != "" else None,
                    "ambiguous_instance_count": ambiguous_count if ambiguous_count != "" else None,
                    "aggregation": aggregation,
                }
            )

        if not point_dirs or aggregated_points == 0:
            count_mode = "VIEW_RAW"
            unique_total: int | None = None
            ambiguous_total: int | None = None
        elif aggregated_points == len(point_dirs):
            count_mode = "POINT_DEDUP"
            unique_total = total_unique
            ambiguous_total = total_ambiguous
        else:
            count_mode = "MIXED"
            unique_total = None
            ambiguous_total = None

        report = {
            "schema_version": 1,
            "session_id": session["session_id"],
            "inspection_task_id": session["inspection_task_id"],
            "task_revision": session["task_revision"],
            "map_id": session["map_id"],
            "map_version_id": session["map_version_id"],
            "count_target": session["count_target"],
            "count_mode": count_mode,
            "points": point_documents,
            "totals": {
                "raw_instance_count": total_raw,
                "unique_instance_count": unique_total,
                "ambiguous_instance_count": ambiguous_total,
            },
        }

        report_root = session_root / "report"
        report_path = report_root / "report.json"
        _atomic_json(report_path, report)
        _write_csv(
            report_root / "points.csv",
            ["point_id", "views", "raw_count", "unique_count", "ambiguous_count"],
            point_rows,
        )
        _write_csv(
            report_root / "views.csv",
            [
                "point_id",
                "view_id",
                "capture_stamp",
                "robot_x",
                "robot_y",
                "robot_yaw",
                "pan_rad",
                "tilt_rad",
                "raw_count",
                "model_id",
                "model_version",
                "inference_time_ms",
            ],
            view_rows,
        )
        _write_csv(
            report_root / "instances.csv",
            [
                "point_id",
                "global_instance_id",
                "status",
                "association_confidence",
                "view_id",
                "local_instance_id",
            ],
            instance_rows,
        )
        return str(report_path)

    @staticmethod
    def _suffix(value: str, name: str) -> str:
        if not isinstance(value, str) or not value.startswith(".") or "/" in value or "\\" in value or len(value) > 12:
            raise MultiviewEvidenceError(f"{name} must be a short file suffix")
        return value

    def _require_session(self) -> tuple[dict[str, Any], Path]:
        if self._session is None or self._session_root is None:
            raise RuntimeError("inspection evidence session has not started")
        return self._session, self._session_root
