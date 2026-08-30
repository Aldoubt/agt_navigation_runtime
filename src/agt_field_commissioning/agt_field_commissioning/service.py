from __future__ import annotations

from dataclasses import dataclass
import json
import os
from pathlib import Path
import re
import shutil
import tempfile
from typing import Any

import yaml

from agt_runtime_contracts.validator import load_yaml, sha256_file, validate_runtime_contracts
from agt_site_runtime.activation_store import ActivationStore
from agt_site_runtime.models import ActiveSelection

from .map_review import MapEdit, MapReviewDraft, PgmMap
from .projection import ProjectionRequest, RtabmapGridBackend


_IDENTITY_RE = re.compile(r"^[A-Za-z0-9][A-Za-z0-9_.-]*$")


def _identity(value: str, label: str) -> str:
    text = str(value).strip()
    if not _IDENTITY_RE.fullmatch(text):
        raise ValueError(f"unsafe {label}: {value!r}")
    return text


def _atomic_yaml(path: Path, document: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".tmp")
    with temporary.open("w", encoding="utf-8") as stream:
        yaml.safe_dump(document, stream, sort_keys=False)
        stream.flush()
        os.fsync(stream.fileno())
    os.replace(temporary, path)


def _atomic_text(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".tmp")
    with temporary.open("w", encoding="utf-8") as stream:
        stream.write(text)
        stream.flush()
        os.fsync(stream.fileno())
    os.replace(temporary, path)


@dataclass(frozen=True)
class CommissioningPaths:
    root: Path
    mapping: Path
    projection: Path
    review: Path
    evidence: Path


class CommissioningService:
    """Filesystem-backed field commissioning owner.

    This service creates mutable run-scoped artifacts and immutable validated Site
    revisions. It never starts Nav2, publishes TF, or mutates an already deployed
    Site revision.
    """

    def __init__(
        self,
        *,
        runtime_dir: str | Path,
        sites_root: str | Path,
        state_root: str | Path,
        vehicle_profile: str | Path,
        vehicle_schema: str | Path,
        site_schema: str | Path,
        projection_backend: Any | None = None,
    ) -> None:
        self.runtime_dir = Path(runtime_dir).expanduser().resolve()
        self.sites_root = Path(sites_root).expanduser().resolve()
        self.state_root = Path(state_root).expanduser().resolve()
        self.vehicle_profile = Path(vehicle_profile).expanduser().resolve()
        self.vehicle_schema = Path(vehicle_schema).expanduser().resolve()
        self.site_schema = Path(site_schema).expanduser().resolve()
        self.projection_backend = projection_backend or RtabmapGridBackend()
        self._drafts: dict[tuple[str, str], MapReviewDraft] = {}

    def _paths(self, site_id: str, run_id: str) -> CommissioningPaths:
        site = _identity(site_id, "site_id")
        run = _identity(run_id, "run_id")
        root = self.runtime_dir / "commissioning" / site / run
        return CommissioningPaths(
            root=root,
            mapping=root / "mapping",
            projection=root / "projection",
            review=root / "map_review",
            evidence=root / "evidence",
        )

    def status(self, site_id: str, run_id: str) -> dict[str, Any]:
        paths = self._paths(site_id, run_id)
        pcd = paths.mapping / "localization_map.pcd"
        processing = paths.mapping / "localization_map.processing.yaml"
        projection = paths.projection / "projection_record.json"
        if projection.is_file() and (paths.projection / "raw_map.pgm").is_file():
            state = "MAP_READY"
        elif pcd.is_file() and pcd.stat().st_size > 0 and processing.is_file():
            state = "PCD_READY"
        elif paths.root.exists():
            state = "MAPPING_PENDING"
        else:
            state = "NOT_STARTED"
        return {
            "site_id": _identity(site_id, "site_id"),
            "run_id": _identity(run_id, "run_id"),
            "state": state,
            "projection_backend": getattr(self.projection_backend, "backend_name", "unknown"),
        }

    def project(self, site_id: str, run_id: str, **overrides: Any) -> dict[str, Any]:
        paths = self._paths(site_id, run_id)
        pcd = paths.mapping / "localization_map.pcd"
        if not pcd.is_file() or pcd.stat().st_size <= 0:
            raise RuntimeError("finalized localization_map.pcd is required before projection")
        request = ProjectionRequest(
            source_pcd=pcd,
            output_dir=paths.projection,
            resolution_m=float(overrides.get("resolution_m", 0.05)),
            max_ground_angle_deg=float(overrides.get("max_ground_angle_deg", 35.0)),
            normal_k=int(overrides.get("normal_k", 20)),
            min_ground_height_m=float(overrides.get("min_ground_height_m", -0.4)),
            max_ground_height_m=float(overrides.get("max_ground_height_m", 0.5)),
            max_obstacle_height_m=float(overrides.get("max_obstacle_height_m", 2.0)),
        )
        result = self.projection_backend.project(request)
        key = (_identity(site_id, "site_id"), _identity(run_id, "run_id"))
        self._drafts[key] = MapReviewDraft.create(result.pgm, result.yaml, paths.review)
        self._drafts[key].materialize()
        return self.map_descriptor(site_id, run_id)

    def _draft(self, site_id: str, run_id: str) -> MapReviewDraft:
        site = _identity(site_id, "site_id")
        run = _identity(run_id, "run_id")
        key = (site, run)
        draft = self._drafts.get(key)
        if draft is not None:
            return draft
        paths = self._paths(site, run)
        raw_pgm = paths.projection / "raw_map.pgm"
        raw_yaml = paths.projection / "raw_map.yaml"
        if not raw_pgm.is_file() or not raw_yaml.is_file():
            raise RuntimeError("projected map is not ready")
        draft = MapReviewDraft.create(raw_pgm, raw_yaml, paths.review)
        self._drafts[key] = draft
        return draft

    def map_descriptor(self, site_id: str, run_id: str) -> dict[str, Any]:
        draft = self._draft(site_id, run_id)
        raw_yaml = load_yaml(draft.raw_yaml)
        resolution = float(raw_yaml.get("resolution", 0.0))
        origin = raw_yaml.get("origin")
        if not isinstance(origin, list) or len(origin) != 3:
            raise RuntimeError("navigation map origin must contain x, y, yaw")
        return {
            "site_id": _identity(site_id, "site_id"),
            "run_id": _identity(run_id, "run_id"),
            "revision": draft.revision,
            "width": draft.map.width,
            "height": draft.map.height,
            "resolution": resolution,
            "origin": [float(origin[0]), float(origin[1]), float(origin[2])],
        }

    def current_map_bytes(self, site_id: str, run_id: str) -> bytes:
        return self._draft(site_id, run_id).map.to_p5()

    def apply_map_edit(
        self,
        site_id: str,
        run_id: str,
        kind: str,
        cells: list[int] | tuple[int, ...],
    ) -> dict[str, Any]:
        draft = self._draft(site_id, run_id)
        draft.apply(MapEdit(kind=kind, cells=tuple(cells)))
        draft.materialize()
        return self.map_descriptor(site_id, run_id)

    def undo_map_edit(self, site_id: str, run_id: str) -> bool:
        draft = self._draft(site_id, run_id)
        changed = draft.undo()
        if changed:
            draft.materialize()
        return changed

    def redo_map_edit(self, site_id: str, run_id: str) -> bool:
        draft = self._draft(site_id, run_id)
        changed = draft.redo()
        if changed:
            draft.materialize()
        return changed

    def reset_map_edit(self, site_id: str, run_id: str) -> dict[str, Any]:
        draft = self._draft(site_id, run_id)
        draft.reset()
        draft.materialize()
        return self.map_descriptor(site_id, run_id)

    def save_review(self, site_id: str, run_id: str, revision: str) -> dict[str, Any]:
        site = _identity(site_id, "site_id")
        run = _identity(run_id, "run_id")
        rev = _identity(revision, "revision")
        paths = self._paths(site, run)
        draft = self._draft(site, run)
        reviewed = draft.materialize()

        destination = self.sites_root / site / rev
        if destination.exists():
            raise RuntimeError(f"immutable Site revision already exists: {site}/{rev}")
        destination.parent.mkdir(parents=True, exist_ok=True)
        temporary = Path(tempfile.mkdtemp(prefix=f".{rev}.", dir=destination.parent))
        try:
            map_dir = temporary / "map"
            semantic_dir = temporary / "semantic"
            routes_dir = temporary / "routes"
            commissioning_dir = temporary / "commissioning"
            for directory in (map_dir, semantic_dir, routes_dir, commissioning_dir):
                directory.mkdir(parents=True, exist_ok=True)

            shutil.copy2(reviewed.pgm, map_dir / "navigation.pgm")
            nav_doc = load_yaml(reviewed.yaml)
            nav_doc["image"] = "navigation.pgm"
            _atomic_yaml(map_dir / "navigation.yaml", nav_doc)

            localization_pcd = paths.mapping / "localization_map.pcd"
            localization_record = paths.mapping / "localization_map.processing.yaml"
            if not localization_pcd.is_file() or not localization_record.is_file():
                raise RuntimeError("finalized localization assets are missing")
            shutil.copy2(localization_pcd, map_dir / localization_pcd.name)
            shutil.copy2(localization_record, map_dir / localization_record.name)

            _atomic_yaml(semantic_dir / "semantic_map.yaml", {"schema_version": 1, "features": []})
            _atomic_yaml(routes_dir / "route_graph.yaml", {"schema_version": 1, "nodes": [], "edges": []})
            if (paths.projection / "projection_record.json").is_file():
                shutil.copy2(paths.projection / "projection_record.json", commissioning_dir / "projection_record.json")
            else:
                _atomic_text(commissioning_dir / "projection_record.json", json.dumps({"schema_version": 1, "backend": "unknown"}) + "\n")
            shutil.copy2(reviewed.edit_log, commissioning_dir / "map_edits.json")

            manifest = {
                "site_schema_version": "1.0",
                "site": {"id": site, "revision": rev, "source_run_id": run},
                "frames": {"global": "map"},
                "assets": {
                    "navigation_map": "map/navigation.yaml",
                    "localization_map": "map/localization_map.pcd",
                    "localization_processing_record": "map/localization_map.processing.yaml",
                    "semantic_map": "semantic/semantic_map.yaml",
                    "route_graph": "routes/route_graph.yaml",
                    "projection_record": "commissioning/projection_record.json",
                    "map_edit_record": "commissioning/map_edits.json",
                },
                "compatibility": {"vehicle_profiles": [self._vehicle_name()]},
                "integrity": {"hashes_file": "hashes.yaml"},
            }
            _atomic_yaml(temporary / "manifest.yaml", manifest)

            effective_assets = list(manifest["assets"].values()) + ["map/navigation.pgm"]
            hashes = {raw: sha256_file(temporary / raw) for raw in effective_assets}
            _atomic_yaml(temporary / "hashes.yaml", {"hashes": hashes})

            report = validate_runtime_contracts(
                self.vehicle_profile,
                temporary,
                self.vehicle_schema,
                self.site_schema,
            )
            if not report.ok:
                reasons = "; ".join(f"{issue.code}: {issue.message}" for issue in report.issues)
                raise RuntimeError(f"candidate Site validation failed: {reasons}")
            os.replace(temporary, destination)
            return {
                "site_id": site,
                "revision": rev,
                "site_root": str(destination),
                "validated": True,
                "checks": list(report.checks),
            }
        except Exception:
            shutil.rmtree(temporary, ignore_errors=True)
            raise

    def _vehicle_name(self) -> str:
        profile = load_yaml(self.vehicle_profile)
        platform = profile.get("platform")
        if not isinstance(platform, dict) or not isinstance(platform.get("name"), str):
            raise RuntimeError("vehicle profile is missing platform.name")
        return platform["name"]

    def activate_revision(self, site_id: str, revision: str) -> dict[str, str]:
        site = _identity(site_id, "site_id")
        rev = _identity(revision, "revision")
        site_root = self.sites_root / site / rev
        if not site_root.is_dir():
            raise RuntimeError(f"Site revision is not deployed: {site}/{rev}")
        report = validate_runtime_contracts(
            self.vehicle_profile,
            site_root,
            self.vehicle_schema,
            self.site_schema,
        )
        if not report.ok:
            reasons = "; ".join(f"{issue.code}: {issue.message}" for issue in report.issues)
            raise RuntimeError(f"Site revision is not valid: {reasons}")
        ActivationStore(self.state_root).save(ActiveSelection(site_id=site, revision=rev))
        return {"site_id": site, "revision": rev}
