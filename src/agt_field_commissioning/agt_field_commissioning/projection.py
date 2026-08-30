from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
from typing import Callable

import yaml

from .map_review import PgmMap
from .raycast_free_space import load_evidence
from .raycast_fusion import fuse_point_map_with_evidence


_PROJECTOR_PACKAGE = "agt_field_commissioning"


def _sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return f"sha256:{digest.hexdigest()}"


def _atomic_json(path: Path, payload: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_text(json.dumps(payload, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    temporary.replace(path)


def _atomic_text(path: Path, payload: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_text(payload, encoding="utf-8")
    temporary.replace(path)


def _default_runner(command: list[str]) -> int:
    return subprocess.run(command, check=False).returncode


def _resolve_executable(executable: str) -> str | None:
    candidate = Path(executable).expanduser()
    if candidate.is_absolute() or "/" in executable:
        return str(candidate.resolve()) if candidate.is_file() else None

    path_match = shutil.which(executable)
    if path_match:
        return path_match

    for raw_prefix in os.environ.get("AMENT_PREFIX_PATH", "").split(os.pathsep):
        prefix = raw_prefix.strip()
        if not prefix:
            continue
        ros_candidate = Path(prefix) / "lib" / _PROJECTOR_PACKAGE / executable
        if ros_candidate.is_file() and os.access(ros_candidate, os.X_OK):
            return str(ros_candidate.resolve())

    return None


@dataclass(frozen=True)
class ProjectionRequest:
    source_pcd: Path
    output_dir: Path
    resolution_m: float = 0.05
    max_ground_angle_deg: float = 35.0
    normal_k: int = 20
    min_ground_height_m: float = 0.0
    max_ground_height_m: float = 0.0
    max_obstacle_height_m: float = 0.0
    raycast_evidence: Path | None = None
    raycast_record: Path | None = None

    def validate(self) -> None:
        source = Path(self.source_pcd).expanduser()
        if not source.is_file() or source.stat().st_size <= 0:
            raise RuntimeError(f"source PCD is missing or empty: {source}")
        if not (0.01 <= float(self.resolution_m) <= 1.0):
            raise ValueError("resolution_m must be between 0.01 and 1.0")
        if not (0.0 < float(self.max_ground_angle_deg) < 90.0):
            raise ValueError("max_ground_angle_deg must be between 0 and 90")
        if int(self.normal_k) < 3:
            raise ValueError("normal_k must be >= 3")

        min_ground = float(self.min_ground_height_m)
        max_ground = float(self.max_ground_height_m)
        max_obstacle = float(self.max_obstacle_height_m)
        if min_ground != 0.0 and max_ground != 0.0 and min_ground >= max_ground:
            raise ValueError("min_ground_height_m must be less than max_ground_height_m when both are enabled")
        if min_ground != 0.0 and max_obstacle != 0.0 and max_obstacle <= min_ground:
            raise ValueError("max_obstacle_height_m must exceed min_ground_height_m when both are enabled")


@dataclass(frozen=True)
class ProjectionResult:
    backend: str
    pgm: Path
    yaml: Path
    record: Path
    projection_quality: str = "pcd_fallback"
    fallback_reason: str | None = None


def _write_map_yaml(
    destination: Path,
    image_name: str,
    resolution_m: float,
    origin_x: float,
    origin_y: float,
) -> None:
    payload = {
        "image": image_name,
        "resolution": float(resolution_m),
        "origin": [float(origin_x), float(origin_y), 0.0],
        "negate": 0,
        "occupied_thresh": 0.65,
        "free_thresh": 0.196,
        "mode": "trinary",
    }
    _atomic_text(destination, yaml.safe_dump(payload, sort_keys=False))


def _materialize_point_fallback(
    point_pgm: Path,
    point_yaml: Path,
    output_pgm: Path,
    output_yaml: Path,
) -> None:
    shutil.copy2(point_pgm, output_pgm)
    document = yaml.safe_load(point_yaml.read_text(encoding="utf-8"))
    if not isinstance(document, dict):
        raise RuntimeError("RTAB point-map YAML is invalid")
    document["image"] = output_pgm.name
    _atomic_text(output_yaml, yaml.safe_dump(document, sort_keys=False))


def _map_cell_metrics(pgm: PgmMap) -> tuple[dict[str, int], dict[str, float]]:
    occupied = sum(1 for value in pgm.pixels if value == 0)
    free = sum(1 for value in pgm.pixels if value == 254)
    unknown = len(pgm.pixels) - occupied - free
    counts = {"free": free, "occupied": occupied, "unknown": unknown}
    total = len(pgm.pixels)
    ratios = {key: value / total for key, value in counts.items()}
    return counts, ratios


class RtabmapGridBackend:
    backend_name = "rtabmap_grid"

    def __init__(
        self,
        executable: str = "rtabmap_grid_projector",
        runner: Callable[[list[str]], int] | None = None,
    ) -> None:
        self.executable = str(executable)
        self._runner_injected = runner is not None
        self.runner = runner or _default_runner

    def project(self, request: ProjectionRequest) -> ProjectionResult:
        request.validate()
        if self._runner_injected:
            resolved_executable = self.executable
        else:
            resolved_executable = _resolve_executable(self.executable)
            if resolved_executable is None:
                raise RuntimeError(f"projector executable is not available: {self.executable}")

        source = Path(request.source_pcd).expanduser().resolve()
        output_dir = Path(request.output_dir).expanduser().resolve()
        output_dir.mkdir(parents=True, exist_ok=True)
        point_pgm = output_dir / "rtab_point_map.pgm"
        point_yaml = output_dir / "rtab_point_map.yaml"
        pgm = output_dir / "raw_map.pgm"
        nav_yaml = output_dir / "raw_map.yaml"
        record = output_dir / "projection_record.json"

        command = [
            resolved_executable,
            "--input", str(source),
            "--output-pgm", str(point_pgm),
            "--output-yaml", str(point_yaml),
            "--cell-size", str(float(request.resolution_m)),
            "--max-ground-angle-deg", str(float(request.max_ground_angle_deg)),
            "--normal-k", str(int(request.normal_k)),
            "--min-ground-height", str(float(request.min_ground_height_m)),
            "--max-ground-height", str(float(request.max_ground_height_m)),
            "--max-obstacle-height", str(float(request.max_obstacle_height_m)),
        ]
        return_code = int(self.runner(command))
        if return_code != 0:
            raise RuntimeError(f"rtabmap grid projector failed with exit code {return_code}")
        if (
            not point_pgm.is_file()
            or point_pgm.stat().st_size <= 0
            or not point_yaml.is_file()
            or point_yaml.stat().st_size <= 0
        ):
            raise RuntimeError("projector did not produce non-empty PGM/YAML outputs")

        projection_quality = "pcd_fallback"
        fallback_reason: str | None = "raycast_evidence_unavailable"
        raycast_evidence_sha256: str | None = None
        raycast_record_sha256: str | None = None
        fusion_config: dict = {
            "occupied_precedence": True,
            "endpoint_hit_requires_final_obstacle": True,
        }

        evidence_path = (
            Path(request.raycast_evidence).expanduser().resolve()
            if request.raycast_evidence is not None
            else None
        )
        evidence_record_path = (
            Path(request.raycast_record).expanduser().resolve()
            if request.raycast_record is not None
            else None
        )

        if evidence_path is not None and evidence_record_path is not None:
            try:
                evidence = load_evidence(evidence_path, evidence_record_path)
                fused = fuse_point_map_with_evidence(point_pgm, point_yaml, evidence)
                fused.pgm.write(pgm)
                _write_map_yaml(
                    nav_yaml,
                    pgm.name,
                    fused.resolution_m,
                    fused.origin_x,
                    fused.origin_y,
                )
                projection_quality = "raycast_fused"
                fallback_reason = None
                raycast_evidence_sha256 = _sha256(evidence_path)
                raycast_record_sha256 = _sha256(evidence_record_path)
                fusion_config.update(
                    {
                        "free_threshold": evidence.free_threshold,
                        "occupied_threshold": evidence.occupied_threshold,
                        "min_observation_count": evidence.min_observation_count,
                    }
                )
            except (ValueError, RuntimeError, OSError) as exc:
                fallback_reason = f"raycast_evidence_invalid: {exc}"
                _materialize_point_fallback(point_pgm, point_yaml, pgm, nav_yaml)
        elif evidence_path is not None or evidence_record_path is not None:
            fallback_reason = "raycast_evidence_incomplete"
            _materialize_point_fallback(point_pgm, point_yaml, pgm, nav_yaml)
        else:
            _materialize_point_fallback(point_pgm, point_yaml, pgm, nav_yaml)

        parsed = PgmMap.load(pgm)
        counts, ratios = _map_cell_metrics(parsed)
        parameters = {
            "normals_segmentation": True,
            "resolution_m": float(request.resolution_m),
            "max_ground_angle_deg": float(request.max_ground_angle_deg),
            "normal_k": int(request.normal_k),
            "min_ground_height_m": float(request.min_ground_height_m),
            "max_ground_height_m": float(request.max_ground_height_m),
            "max_obstacle_height_m": float(request.max_obstacle_height_m),
        }
        payload = {
            "schema_version": 2,
            "backend": self.backend_name,
            "projection_quality": projection_quality,
            "fallback_reason": fallback_reason,
            "created_at": datetime.now(timezone.utc).isoformat(),
            "source_pcd": str(source),
            "source_pcd_sha256": _sha256(source),
            "raycast_evidence": str(evidence_path) if evidence_path is not None else None,
            "raycast_evidence_sha256": raycast_evidence_sha256,
            "raycast_record": str(evidence_record_path) if evidence_record_path is not None else None,
            "raycast_record_sha256": raycast_record_sha256,
            "output_pgm": str(pgm),
            "output_pgm_sha256": _sha256(pgm),
            "output_yaml": str(nav_yaml),
            "output_yaml_sha256": _sha256(nav_yaml),
            "width": parsed.width,
            "height": parsed.height,
            "parameters": parameters,
            "fusion": fusion_config,
            "cell_counts": counts,
            "cell_ratios": ratios,
        }
        _atomic_json(record, payload)
        return ProjectionResult(
            self.backend_name,
            pgm,
            nav_yaml,
            record,
            projection_quality,
            fallback_reason,
        )


def load_projection_record(path: str | Path) -> dict:
    value = json.loads(Path(path).read_text(encoding="utf-8"))
    if not isinstance(value, dict) or value.get("schema_version") not in {1, 2}:
        raise ValueError("unsupported projection record")
    return value
