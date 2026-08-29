from __future__ import annotations

import csv
import json
import os
from pathlib import Path
import tempfile
from typing import Any, Mapping

from .mission_model import Mission, MissionRuntimeStatus, MissionStep, MissionState, StepType, validate_component


def _atomic_json(path: Path, value: Mapping[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix=f".{path.name}.", suffix=".tmp", dir=path.parent)
    temporary_path = Path(temporary)
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as stream:
            json.dump(dict(value), stream, ensure_ascii=False, sort_keys=True, indent=2)
            stream.write("\n")
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


class MissionReportWriter:
    """Mission-level manifest that links child inspection evidence without re-owning it.

    Point-local deduplicated counts may be summed only as a clearly labeled
    POINT_SUM_ESTIMATE. This writer never claims whole-mission/global ID dedup.
    """

    def __init__(self, root: str | Path, *, run_id: str) -> None:
        self.root = Path(root).expanduser().resolve()
        self.run_id = validate_component(run_id, "run_id")
        self._mission: Mission | None = None
        self._run_root: Path | None = None
        self._steps: list[dict[str, Any]] = []
        self._inspections: list[dict[str, Any]] = []

    @property
    def report_uri(self) -> str:
        if self._run_root is None:
            return ""
        return str(self._run_root / "report.json")

    def start(self, mission: Mission) -> str:
        if self._run_root is not None:
            raise RuntimeError("mission report already started")
        run_root = self.root / mission.mission_id / self.run_id
        run_root.mkdir(parents=True, exist_ok=False)
        self._mission = mission
        self._run_root = run_root
        _atomic_json(
            run_root / "report.json",
            {
                "schema_version": 1,
                "run_id": self.run_id,
                "mission_id": mission.mission_id,
                "mission_version": mission.mission_version,
                "mission_content_sha256": mission.content_sha256,
                "map_id": mission.map_binding.map_id,
                "map_version_id": mission.map_binding.map_version_id,
                "map_manifest_sha256": mission.map_binding.manifest_sha256,
                "state": "RUNNING",
                "home_returned": False,
                "steps": [],
                "inspections": [],
                "inspection_summary": self._inspection_summary(),
            },
        )
        return str(run_root)

    def _require_started(self) -> tuple[Mission, Path]:
        if self._mission is None or self._run_root is None:
            raise RuntimeError("mission report has not been started")
        return self._mission, self._run_root

    @staticmethod
    def _load_inspection_summary(artifact_uri: str) -> dict[str, Any] | None:
        if not artifact_uri:
            return None
        path = Path(artifact_uri).expanduser() / "report" / "report.json"
        if not path.is_file():
            return None
        try:
            value = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, UnicodeError, json.JSONDecodeError):
            return None
        if not isinstance(value, dict):
            return None
        totals = value.get("totals")
        if not isinstance(totals, dict):
            totals = {}
        return {
            "inspection_task_id": str(value.get("inspection_task_id", "")),
            "session_id": str(value.get("session_id", "")),
            "count_target": str(value.get("count_target", "")),
            "count_mode": str(value.get("count_mode", "")),
            "raw_instance_count": totals.get("raw_instance_count"),
            "unique_instance_count": totals.get("unique_instance_count"),
            "ambiguous_instance_count": totals.get("ambiguous_instance_count"),
            "inspection_report_uri": str(path),
        }

    def record_step(
        self,
        *,
        index: int,
        step: MissionStep,
        success: bool,
        message: str,
        session_id: str = "",
        artifact_uri: str = "",
    ) -> None:
        self._require_started()
        row = {
            "index": int(index),
            "step_id": step.id,
            "step_type": step.type.name,
            "success": bool(success),
            "message": str(message),
            "session_id": str(session_id),
            "artifact_uri": str(artifact_uri),
        }
        self._steps.append(row)
        if step.type == StepType.INSPECTION_TASK:
            summary = self._load_inspection_summary(artifact_uri) or {
                "inspection_task_id": step.inspection_task_id,
                "session_id": str(session_id),
                "count_target": "",
                "count_mode": "",
                "raw_instance_count": None,
                "unique_instance_count": None,
                "ambiguous_instance_count": None,
                "inspection_report_uri": "",
            }
            summary.update(
                {
                    "step_id": step.id,
                    "success": bool(success),
                    "evidence_root_uri": str(artifact_uri),
                }
            )
            self._inspections.append(summary)

    def _inspection_summary(self) -> dict[str, Any]:
        successful = [item for item in self._inspections if item.get("success")]
        targets = sorted(
            {
                str(item.get("count_target", ""))
                for item in successful
                if item.get("count_target")
            }
        )
        if any(item.get("count_mode") == "PENDING_OFFLINE" for item in successful):
            return {
                "count_targets": targets,
                "raw_instance_count": None,
                "point_sum_estimate": None,
                "ambiguous_instance_count": None,
                "count_semantics": "PENDING_OFFLINE",
                "mission_dedup_applied": False,
            }

        raw_values = [
            item.get("raw_instance_count")
            for item in successful
            if isinstance(item.get("raw_instance_count"), int)
        ]
        point_values = [
            item.get("unique_instance_count")
            for item in successful
            if item.get("count_mode") == "POINT_DEDUP"
            and isinstance(item.get("unique_instance_count"), int)
        ]
        ambiguous_values = [
            item.get("ambiguous_instance_count")
            for item in successful
            if item.get("count_mode") == "POINT_DEDUP"
            and isinstance(item.get("ambiguous_instance_count"), int)
        ]
        all_point_dedup = bool(successful) and len(point_values) == len(successful)
        return {
            "count_targets": targets,
            "raw_instance_count": sum(raw_values) if raw_values else 0,
            "point_sum_estimate": sum(point_values) if all_point_dedup else None,
            "ambiguous_instance_count": (
                sum(ambiguous_values) if all_point_dedup else None
            ),
            "count_semantics": "POINT_SUM_ESTIMATE" if all_point_dedup else "VIEW_RAW",
            "mission_dedup_applied": False,
        }

    def finish(self, status: MissionRuntimeStatus) -> str:
        mission, run_root = self._require_started()
        home_returned = any(
            row["step_type"] == StepType.RETURN_HOME.name and row["success"]
            for row in self._steps
        )
        state_name = (
            status.state.name if isinstance(status.state, MissionState) else MissionState(int(status.state)).name
        )
        report = {
            "schema_version": 1,
            "run_id": self.run_id,
            "mission_id": mission.mission_id,
            "mission_version": mission.mission_version,
            "mission_content_sha256": mission.content_sha256,
            "map_id": mission.map_binding.map_id,
            "map_version_id": mission.map_binding.map_version_id,
            "map_manifest_sha256": mission.map_binding.manifest_sha256,
            "state": state_name,
            "success": state_name == MissionState.SUCCEEDED.name,
            "error_code": int(status.error_code),
            "message": status.message,
            "home_returned": home_returned,
            "steps": list(self._steps),
            "inspections": list(self._inspections),
            "inspection_summary": self._inspection_summary(),
        }
        _atomic_json(run_root / "report.json", report)
        _write_csv(
            run_root / "steps.csv",
            [
                "index",
                "step_id",
                "step_type",
                "success",
                "message",
                "session_id",
                "artifact_uri",
            ],
            self._steps,
        )
        _write_csv(
            run_root / "inspections.csv",
            [
                "step_id",
                "inspection_task_id",
                "session_id",
                "success",
                "count_target",
                "count_mode",
                "raw_instance_count",
                "unique_instance_count",
                "ambiguous_instance_count",
                "evidence_root_uri",
                "inspection_report_uri",
            ],
            self._inspections,
        )
        return str(run_root / "report.json")
