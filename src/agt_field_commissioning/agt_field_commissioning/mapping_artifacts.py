from __future__ import annotations

from dataclasses import dataclass
import hashlib
import json
from pathlib import Path
import re


_IDENTITY_RE = re.compile(r"^[A-Za-z0-9][A-Za-z0-9._-]{0,63}$")


@dataclass(frozen=True)
class CommissioningRunPaths:
    runtime_dir: Path
    site_id: str
    run_id: str
    run_root: Path
    mapping_dir: Path
    observation_dir: Path
    evidence_dir: Path
    localization_map: Path
    processing_record: Path


def _validate_identity_token(value: str, field_name: str) -> str:
    value = str(value)
    if value != value.strip():
        raise ValueError(f"invalid {field_name}: surrounding whitespace is not allowed")
    if value in {"", ".", ".."} or _IDENTITY_RE.fullmatch(value) is None:
        raise ValueError(f"invalid {field_name}: {value!r}")
    return value


def _paths(runtime_dir: str | Path, site_id: str, run_id: str) -> CommissioningRunPaths:
    runtime = Path(runtime_dir).expanduser()
    site = _validate_identity_token(site_id, "site_id")
    run = _validate_identity_token(run_id, "run_id")
    run_root = runtime / "commissioning" / site / run
    mapping_dir = run_root / "mapping"
    observation_dir = run_root / "observation"
    evidence_dir = run_root / "evidence"
    return CommissioningRunPaths(
        runtime_dir=runtime,
        site_id=site,
        run_id=run,
        run_root=run_root,
        mapping_dir=mapping_dir,
        observation_dir=observation_dir,
        evidence_dir=evidence_dir,
        localization_map=mapping_dir / "localization_map.pcd",
        processing_record=mapping_dir / "localization_map.processing.yaml",
    )


def prepare_mapping_run(
    runtime_dir: str | Path,
    site_id: str,
    run_id: str,
) -> CommissioningRunPaths:
    paths = _paths(runtime_dir, site_id, run_id)

    if paths.mapping_dir.exists() and not paths.mapping_dir.is_dir():
        raise RuntimeError(f"commissioning mapping output path is not a directory: {paths.mapping_dir}")

    existing = sorted(path.name for path in paths.mapping_dir.iterdir()) if paths.mapping_dir.is_dir() else []
    if existing:
        preview = ", ".join(existing[:8])
        raise RuntimeError(
            "refusing to reuse populated commissioning mapping directory: "
            f"{paths.mapping_dir} ({preview})"
        )

    paths.mapping_dir.mkdir(parents=True, exist_ok=True)
    paths.observation_dir.mkdir(parents=True, exist_ok=True)
    paths.evidence_dir.mkdir(parents=True, exist_ok=True)
    return paths


def _sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def _require_nonempty_file(path: Path) -> None:
    if not path.is_file():
        raise RuntimeError(f"required mapping artifact is missing: {path.name}")
    if path.stat().st_size <= 0:
        raise RuntimeError(f"required mapping artifact is empty: {path.name}")


def finalize_mapping_run(
    runtime_dir: str | Path,
    site_id: str,
    run_id: str,
) -> dict:
    paths = _paths(runtime_dir, site_id, run_id)

    if not paths.mapping_dir.is_dir():
        raise RuntimeError(f"commissioning mapping directory is missing: {paths.mapping_dir}")

    temporary_files = sorted(path.name for path in paths.mapping_dir.glob("*.tmp"))
    if temporary_files:
        raise RuntimeError(
            "temporary FAST-LIVO2 mapping artifacts remain; normal shutdown/save is incomplete: "
            + ", ".join(temporary_files)
        )

    _require_nonempty_file(paths.localization_map)
    _require_nonempty_file(paths.processing_record)
    paths.evidence_dir.mkdir(parents=True, exist_ok=True)

    evidence = {
        "schema_version": 1,
        "state": "READY",
        "site_id": paths.site_id,
        "run_id": paths.run_id,
        "mapping_directory": str(paths.mapping_dir),
        "artifacts": {
            paths.localization_map.name: {
                "size_bytes": paths.localization_map.stat().st_size,
                "sha256": _sha256(paths.localization_map),
            },
            paths.processing_record.name: {
                "size_bytes": paths.processing_record.stat().st_size,
                "sha256": _sha256(paths.processing_record),
            },
        },
    }

    metadata_path = paths.evidence_dir / "mapping_metadata.json"
    temporary_metadata_path = metadata_path.with_name(metadata_path.name + ".tmp")
    temporary_metadata_path.write_text(
        json.dumps(evidence, indent=2, sort_keys=True) + "\n",
        encoding="utf-8",
    )
    temporary_metadata_path.replace(metadata_path)
    return evidence
