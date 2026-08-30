from __future__ import annotations

from dataclasses import asdict, dataclass
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
from typing import Callable

from .map_review import PgmMap


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


def _default_runner(command: list[str]) -> int:
    return subprocess.run(command, check=False).returncode


def _resolve_executable(executable: str) -> str | None:
    candidate = Path(executable).expanduser()
    if candidate.is_absolute() or "/" in executable:
        return str(candidate.resolve()) if candidate.is_file() else None
    return shutil.which(executable)


@dataclass(frozen=True)
class ProjectionRequest:
    source_pcd: Path
    output_dir: Path
    resolution_m: float = 0.05
    max_ground_angle_deg: float = 35.0
    normal_k: int = 20
    min_ground_height_m: float = -0.4
    max_ground_height_m: float = 0.5
    max_obstacle_height_m: float = 2.0

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
        if float(self.min_ground_height_m) >= float(self.max_ground_height_m):
            raise ValueError("min_ground_height_m must be less than max_ground_height_m")
        if float(self.max_obstacle_height_m) <= float(self.min_ground_height_m):
            raise ValueError("max_obstacle_height_m must exceed min_ground_height_m")


@dataclass(frozen=True)
class ProjectionResult:
    backend: str
    pgm: Path
    yaml: Path
    record: Path


class RtabmapGridBackend:
    backend_name = "rtabmap_grid"

    def __init__(
        self,
        executable: str = "rtabmap_grid_projector",
        runner: Callable[[list[str]], int] | None = None,
    ) -> None:
        self.executable = str(executable)
        self.runner = runner or _default_runner

    def project(self, request: ProjectionRequest) -> ProjectionResult:
        request.validate()
        resolved_executable = _resolve_executable(self.executable)
        if resolved_executable is None:
            raise RuntimeError(f"projector executable is not available: {self.executable}")

        source = Path(request.source_pcd).expanduser().resolve()
        output_dir = Path(request.output_dir).expanduser().resolve()
        output_dir.mkdir(parents=True, exist_ok=True)
        pgm = output_dir / "raw_map.pgm"
        yaml = output_dir / "raw_map.yaml"
        record = output_dir / "projection_record.json"

        command = [
            resolved_executable,
            "--input", str(source),
            "--output-pgm", str(pgm),
            "--output-yaml", str(yaml),
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
        if not pgm.is_file() or pgm.stat().st_size <= 0 or not yaml.is_file() or yaml.stat().st_size <= 0:
            raise RuntimeError("projector did not produce non-empty PGM/YAML outputs")

        parsed = PgmMap.load(pgm)
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
            "schema_version": 1,
            "backend": self.backend_name,
            "created_at": datetime.now(timezone.utc).isoformat(),
            "source_pcd": str(source),
            "source_pcd_sha256": _sha256(source),
            "output_pgm": str(pgm),
            "output_pgm_sha256": _sha256(pgm),
            "output_yaml": str(yaml),
            "output_yaml_sha256": _sha256(yaml),
            "width": parsed.width,
            "height": parsed.height,
            "parameters": parameters,
        }
        _atomic_json(record, payload)
        return ProjectionResult(self.backend_name, pgm, yaml, record)


def load_projection_record(path: str | Path) -> dict:
    value = json.loads(Path(path).read_text(encoding="utf-8"))
    if not isinstance(value, dict) or value.get("schema_version") != 1:
        raise ValueError("unsupported projection record")
    return value
