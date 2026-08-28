#!/usr/bin/env python3

from __future__ import annotations

import argparse
import hashlib
import json
import os
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Mapping

import yaml


CHUNK_SIZE = 1024 * 1024


def _require_identity(value: str, name: str) -> str:
    normalized = str(value).strip()
    if not normalized:
        raise ValueError(f"{name} must not be empty")
    return normalized


def _require_file(path: str | Path, name: str) -> Path:
    resolved = Path(path).expanduser().resolve()
    if not resolved.is_file():
        raise FileNotFoundError(f"{name} must be a file: {resolved}")
    return resolved


def _sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        while True:
            chunk = stream.read(CHUNK_SIZE)
            if not chunk:
                break
            digest.update(chunk)
    return f"sha256:{digest.hexdigest()}"


def _navigation_image_path(navigation_yaml: Path) -> Path:
    try:
        document = yaml.safe_load(navigation_yaml.read_text(encoding="utf-8"))
    except (OSError, UnicodeError, yaml.YAMLError) as error:
        raise ValueError(f"failed to read navigation YAML: {navigation_yaml}") from error

    if not isinstance(document, Mapping):
        raise ValueError("navigation YAML must contain a mapping")

    image_value = document.get("image")
    if not isinstance(image_value, str) or not image_value.strip():
        raise ValueError("navigation YAML image must be a non-empty path")

    image = Path(image_value.strip()).expanduser()
    if not image.is_absolute():
        image = navigation_yaml.parent / image
    image = image.resolve()
    if not image.is_file():
        raise FileNotFoundError(f"navigation image must be a file: {image}")
    return image


def _generated_at_utc() -> str:
    return datetime.now(timezone.utc).isoformat(timespec="seconds").replace("+00:00", "Z")


def _atomic_write_json(path: Path, payload: Mapping[str, Any]) -> None:
    if path.exists():
        raise FileExistsError(f"manifest already exists: {path}")

    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_suffix(path.suffix + ".tmp")

    if temporary.exists():
        raise FileExistsError(f"temporary manifest already exists: {temporary}")

    try:
        temporary.write_text(
            json.dumps(payload, indent=2, ensure_ascii=False, sort_keys=True) + "\n",
            encoding="utf-8",
        )
        os.replace(temporary, path)
    finally:
        if temporary.exists():
            temporary.unlink()


def freeze_assets(
    *,
    pcd_path: str | Path,
    navigation_yaml_path: str | Path,
    map_id: str,
    run_id: str,
    manifest_path: str | Path,
) -> dict[str, Any]:
    normalized_map_id = _require_identity(map_id, "map_id")
    normalized_run_id = _require_identity(run_id, "run_id")
    pcd = _require_file(pcd_path, "pcd_path")
    navigation_yaml = _require_file(navigation_yaml_path, "navigation_yaml_path")
    navigation_image = _navigation_image_path(navigation_yaml)
    manifest = Path(manifest_path).expanduser().resolve()

    if manifest.exists():
        raise FileExistsError(f"manifest already exists: {manifest}")

    payload: dict[str, Any] = {
        "schema_version": 1,
        "map_id": normalized_map_id,
        "run_id": normalized_run_id,
        "mapping_source": "FAST_LIVO2_LIO_ONLY",
        "pcd_path": str(pcd),
        "pcd_sha256": _sha256(pcd),
        "navigation_yaml_path": str(navigation_yaml),
        "navigation_yaml_sha256": _sha256(navigation_yaml),
        "navigation_image_path": str(navigation_image),
        "navigation_image_sha256": _sha256(navigation_image),
        "calibration_status": "UNVERIFIED",
        "generated_at_utc": _generated_at_utc(),
    }

    _atomic_write_json(manifest, payload)
    return payload


def main() -> int:
    parser = argparse.ArgumentParser(
        description=(
            "Freeze FAST-LIVO2 commissioning map identity into an atomic "
            "map_manifest.json without overwriting an existing manifest."
        )
    )
    parser.add_argument("--pcd", required=True, help="Commissioning global PCD")
    parser.add_argument(
        "--navigation-yaml",
        required=True,
        help="Nav2 map YAML whose image reference must resolve",
    )
    parser.add_argument("--map-id", required=True)
    parser.add_argument("--run-id", required=True)
    parser.add_argument("--manifest", required=True, help="Output map_manifest.json")
    args = parser.parse_args()

    try:
        payload = freeze_assets(
            pcd_path=args.pcd,
            navigation_yaml_path=args.navigation_yaml,
            map_id=args.map_id,
            run_id=args.run_id,
            manifest_path=args.manifest,
        )
    except (FileExistsError, FileNotFoundError, ValueError, OSError) as error:
        parser.error(str(error))

    print(json.dumps(payload, indent=2, ensure_ascii=False, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
