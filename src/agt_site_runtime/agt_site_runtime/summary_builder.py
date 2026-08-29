from __future__ import annotations

import hashlib
from pathlib import Path
from typing import Mapping

from agt_runtime_contracts.validator import (
    load_hashes,
    load_yaml,
    navigation_image_asset,
    resolve_relative_path,
    sha256_file,
)

from .models import SiteCandidate, SiteSummary, SiteValidation


STATE_UNKNOWN = 0
STATE_READY = 3
STATE_INVALID = 4


def _content_hash(manifest_sha256: str, hashes: Mapping[str, str], effective_paths: set[str]) -> str:
    lines = "".join(f"{path}:{hashes[path]}\n" for path in sorted(effective_paths))
    payload = f"{manifest_sha256}\n{lines}".encode("utf-8")
    return hashlib.sha256(payload).hexdigest()


def build_site_summary(
    candidate: SiteCandidate,
    validation: SiteValidation,
    *,
    active: bool,
) -> SiteSummary:
    if validation.candidate != candidate:
        raise ValueError("validation result does not belong to the requested Site candidate")

    if not validation.valid:
        return SiteSummary(
            map_id=candidate.key.site_id,
            map_version_id=candidate.key.revision,
            state=STATE_INVALID,
            active=False,
            valid=False,
            validation_errors=tuple(validation.blocker_messages),
        )

    manifest = load_yaml(candidate.manifest_path)
    assets = manifest["assets"]
    hashes = load_hashes(candidate.root, manifest)
    image_raw, _image_path = navigation_image_asset(candidate.root, manifest)

    navigation_raw = str(assets["navigation_map"])
    localization_raw = str(assets["localization_map"])
    effective_paths = {str(path) for path in assets.values()}
    effective_paths.add(image_raw)

    missing_hashes = sorted(path for path in effective_paths if path not in hashes)
    if missing_hashes:
        raise ValueError(
            "validated Site Package is missing effective asset digests: "
            + ", ".join(missing_hashes)
        )

    manifest_sha = sha256_file(candidate.manifest_path)
    processing_record = ""
    processing_raw = assets.get("processing_record")
    if isinstance(processing_raw, str) and processing_raw:
        processing_record = str(resolve_relative_path(candidate.root, processing_raw))

    return SiteSummary(
        map_id=str(manifest["site"]["id"]),
        map_version_id=str(manifest["site"]["revision"]),
        state=STATE_READY,
        active=bool(active),
        valid=True,
        map_hash=_content_hash(manifest_sha, hashes, effective_paths),
        manifest_sha256=manifest_sha,
        navigation_yaml_sha256=hashes[navigation_raw],
        navigation_image_sha256=hashes[image_raw],
        localization_pcd_sha256=hashes[localization_raw],
        navigation_yaml=str(resolve_relative_path(candidate.root, navigation_raw)),
        localization_pcd=str(resolve_relative_path(candidate.root, localization_raw)),
        processing_record=processing_record,
        tasks_directory="",
    )
