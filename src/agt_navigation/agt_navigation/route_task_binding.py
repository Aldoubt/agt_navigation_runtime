"""Resolve an exact TaskGroup revision to an immutable READY Route Asset.

The public ExecuteWaypointTask Action remains unchanged. A formal task may opt
into ROUTE execution by placing one audited binding beside the task JSON:

  tasks/<task_group_id>.route.yaml

No binding means the existing MAP backend remains authoritative.
"""

from __future__ import annotations

from dataclasses import dataclass
import hashlib
from pathlib import Path
from typing import Any

import yaml

from .route_runtime import RouteAsset, RouteRuntimeError, load_route_asset
from .task_group import SAFE_COMPONENT_RE, TaskGroup


@dataclass(frozen=True)
class ResolvedRouteTask:
    binding_path: Path
    route_manifest_path: Path
    asset: RouteAsset


def sha256_file(path: str | Path) -> str:
    digest = hashlib.sha256()
    with Path(path).open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return "sha256:" + digest.hexdigest()


class RouteTaskResolver:
    """Fail-closed resolver for optional TaskGroup -> Route execution bindings."""

    def __init__(self, maps_root: str | Path):
        self.root = Path(maps_root).expanduser().resolve()

    def resolve(
        self,
        task: TaskGroup,
        *,
        expected_vehicle_profile_sha256: str,
    ) -> ResolvedRouteTask | None:
        """Return a READY route binding, or None when this task stays in MAP mode."""
        version_root = self._version_root(
            task.map_binding.map_id, task.map_binding.map_version_id
        )
        binding_path = version_root / "tasks" / f"{task.task_group_id}.route.yaml"
        if not binding_path.exists():
            return None
        if binding_path.is_symlink() or not binding_path.is_file():
            raise RouteRuntimeError(
                "route_binding_invalid", "task route binding must be a regular file"
            )

        binding = self._load_mapping(binding_path, "route binding")
        if int(binding.get("schema_version", 0)) != 1:
            raise RouteRuntimeError(
                "route_binding_schema_invalid", "unsupported route binding schema_version"
            )
        if str(binding.get("status", "")).upper() != "READY":
            raise RouteRuntimeError(
                "route_binding_not_ready", "task route binding must be READY"
            )
        if str(binding.get("backend", "")).upper() != "ROUTE":
            raise RouteRuntimeError(
                "route_binding_backend_invalid", "task route binding backend must be ROUTE"
            )

        task_binding = binding.get("task_binding") or {}
        self._require_exact(
            task_binding,
            {
                "task_group_id": task.task_group_id,
                "task_revision": int(task.revision),
                "task_content_sha256": task.content_sha256,
            },
            code="route_task_binding_mismatch",
        )

        map_manifest = self._load_mapping(version_root / "manifest.yaml", "map manifest")
        if str(map_manifest.get("state", "")).upper() != "READY":
            raise RouteRuntimeError(
                "route_map_not_ready", "ROUTE execution requires a READY map version"
            )
        map_content_sha256 = str(map_manifest.get("map_content_sha256", ""))
        if not map_content_sha256:
            raise RouteRuntimeError(
                "route_map_content_missing",
                "ROUTE execution requires map_content_sha256 in the active map manifest",
            )
        if not expected_vehicle_profile_sha256:
            raise RouteRuntimeError(
                "route_vehicle_profile_missing",
                "ROUTE execution requires the selected vehicle profile hash",
            )

        route_binding = binding.get("route_binding") or {}
        route_id = self._safe_component(route_binding.get("route_id"), "route_id")
        try:
            revision = int(route_binding.get("revision", 0))
        except (TypeError, ValueError) as exc:
            raise RouteRuntimeError(
                "route_binding_revision_invalid", "route revision must be positive"
            ) from exc
        if revision <= 0:
            raise RouteRuntimeError(
                "route_binding_revision_invalid", "route revision must be positive"
            )
        route_dir = version_root / "routes" / route_id / str(revision)
        route_manifest_path = route_dir / "route.yaml"
        expected_manifest_hash = str(route_binding.get("route_manifest_sha256", ""))
        if not expected_manifest_hash or not route_manifest_path.is_file():
            raise RouteRuntimeError(
                "route_binding_asset_missing", "bound Route manifest is missing"
            )
        actual_manifest_hash = sha256_file(route_manifest_path)
        if actual_manifest_hash != expected_manifest_hash:
            raise RouteRuntimeError(
                "route_binding_manifest_hash_mismatch",
                "bound Route manifest differs from the execution binding",
            )

        asset = load_route_asset(
            route_dir,
            expected_map_content_sha256=map_content_sha256,
            expected_vehicle_profile_sha256=expected_vehicle_profile_sha256,
        )
        if asset.route_id != route_id or asset.revision != revision:
            raise RouteRuntimeError(
                "route_binding_identity_mismatch", "resolved Route identity is inconsistent"
            )
        if asset.map_id != task.map_binding.map_id or asset.map_version_id != task.map_binding.map_version_id:
            raise RouteRuntimeError(
                "route_binding_map_mismatch", "Route Asset and TaskGroup bind different map versions"
            )
        return ResolvedRouteTask(binding_path, route_manifest_path, asset)

    def _version_root(self, map_id: str, map_version_id: str) -> Path:
        safe_map = self._safe_component(map_id, "map_id")
        safe_version = self._safe_component(map_version_id, "map_version_id")
        candidate = (self.root / safe_map / "versions" / safe_version).resolve(
            strict=False
        )
        try:
            candidate.relative_to(self.root)
        except ValueError as exc:
            raise RouteRuntimeError(
                "route_binding_path_escape", "map version path escapes maps_root"
            ) from exc
        return candidate

    @staticmethod
    def _safe_component(value: Any, field_name: str) -> str:
        text = str(value or "")
        if not text or not SAFE_COMPONENT_RE.fullmatch(text):
            raise RouteRuntimeError(
                "route_binding_identity_invalid", f"{field_name} contains unsafe characters"
            )
        return text

    @staticmethod
    def _load_mapping(path: Path, label: str) -> dict:
        if path.is_symlink():
            raise RouteRuntimeError(
                "route_binding_invalid", f"{label} must not be a symlink"
            )
        try:
            value = yaml.safe_load(path.read_text(encoding="utf-8")) or {}
        except (OSError, UnicodeError, yaml.YAMLError) as exc:
            raise RouteRuntimeError(
                "route_binding_invalid", f"cannot read {label}: {exc}"
            ) from exc
        if not isinstance(value, dict):
            raise RouteRuntimeError(
                "route_binding_invalid", f"{label} must contain a mapping"
            )
        return value

    @staticmethod
    def _require_exact(actual: dict, expected: dict, *, code: str) -> None:
        for key, expected_value in expected.items():
            if actual.get(key) != expected_value:
                raise RouteRuntimeError(
                    code, f"route binding {key} does not match the resolved TaskGroup"
                )
