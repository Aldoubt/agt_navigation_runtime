from __future__ import annotations

from dataclasses import dataclass
from typing import Any, Mapping, Sequence

from agt_inspection.authoring_repository import InspectionAuthoringRepository
from agt_inspection.schema import canonical_hash

from .delivery_ports import TaskAuthoringPort
from .mission_authoring import (
    MissionAuthoringRepository,
    build_inspection_mission_document,
)
from .task_authoring_model import ActiveTaskSite, build_single_point_task


@dataclass(frozen=True)
class FrozenInspectionDefaults:
    count_target: str = "litchi_flower"
    linear_velocity_max_mps: float = 0.02
    angular_velocity_max_radps: float = 0.03
    stable_duration_s: float = 0.8
    stabilization_timeout_s: float = 5.0
    camera_id: str = "inspection_camera"
    vision_task_id: str = "litchi_flower_instance_seg"
    model_profile: str = "default"
    minimum_confidence: float = 0.6
    inference_timeout_s: float = 10.0
    navigation_retries: int = 1
    gimbal_retries: int = 1
    capture_retries: int = 2
    inference_retries: int = 1
    view_id: str = "view_center"
    pan_rad: float = 0.0
    tilt_rad: float = -0.1745
    gimbal_timeout_s: float = 5.0
    settle_duration_s: float = 0.5


def _required_text(value: object, label: str) -> str:
    if not isinstance(value, str) or not value.strip():
        raise ValueError(f"{label} must be a non-empty string")
    return value.strip()


def _nonnegative_revision(value: object, label: str) -> int:
    if isinstance(value, bool) or not isinstance(value, int) or value < 0:
        raise ValueError(f"{label} must be a non-negative integer")
    return value


def _binding_value(binding: Mapping[str, Any], key: str, label: str) -> Any:
    if key not in binding:
        raise ValueError(f"{label} is required")
    return binding[key]


def build_inspection_document(
    *,
    site: ActiveTaskSite,
    inspection_task_id: str,
    expected_revision: int,
    point_bindings: Sequence[Mapping[str, Any]],
    defaults: FrozenInspectionDefaults,
) -> dict[str, Any]:
    task_id = _required_text(inspection_task_id, "inspection_task_id")
    revision = _nonnegative_revision(expected_revision, "expected_revision") + 1
    if not site.site_hash.startswith("sha256:") or len(site.site_hash) != 71:
        raise ValueError("active Site manifest SHA256 is required for inspection authoring")
    if not point_bindings:
        raise ValueError("point_bindings must not be empty")

    points: list[dict[str, Any]] = []
    seen: set[str] = set()
    for index, binding in enumerate(point_bindings):
        if not isinstance(binding, Mapping):
            raise ValueError(f"point_bindings[{index}] must be an object")
        point_id = _required_text(
            _binding_value(binding, "pointId", f"point_bindings[{index}].pointId"),
            f"point_bindings[{index}].pointId",
        )
        if point_id in seen:
            raise ValueError(f"duplicate inspection point id: {point_id}")
        seen.add(point_id)
        task_group_id = _required_text(
            _binding_value(binding, "taskGroupId", f"point_bindings[{index}].taskGroupId"),
            f"point_bindings[{index}].taskGroupId",
        )
        task_revision = _nonnegative_revision(
            _binding_value(binding, "revision", f"point_bindings[{index}].revision"),
            f"point_bindings[{index}].revision",
        )
        if task_revision <= 0:
            raise ValueError(f"point_bindings[{index}].revision must be > 0")
        content_sha = _required_text(
            _binding_value(
                binding,
                "contentSha256",
                f"point_bindings[{index}].contentSha256",
            ),
            f"point_bindings[{index}].contentSha256",
        )

        points.append(
            {
                "id": point_id,
                "navigation": {
                    "task_group_id": task_group_id,
                    "task_revision": task_revision,
                    "expected_content_sha256": content_sha,
                },
                "stabilization": {
                    "linear_velocity_max_mps": defaults.linear_velocity_max_mps,
                    "angular_velocity_max_radps": defaults.angular_velocity_max_radps,
                    "stable_duration_s": defaults.stable_duration_s,
                    "timeout_s": defaults.stabilization_timeout_s,
                },
                "camera": {
                    "camera_id": defaults.camera_id,
                    "capture_count": 1,
                    "capture_interval_s": 0.0,
                },
                "vision": {
                    "task_id": defaults.vision_task_id,
                    "model_profile": defaults.model_profile,
                    "minimum_confidence": defaults.minimum_confidence,
                    "timeout_s": defaults.inference_timeout_s,
                    "execution_mode": "DEFERRED",
                },
                "retry": {
                    "navigation": defaults.navigation_retries,
                    "gimbal": defaults.gimbal_retries,
                    "capture": defaults.capture_retries,
                    "inference": defaults.inference_retries,
                },
                "aggregation": {
                    "enabled": False,
                    "aggregation_profile": "default",
                },
                "views": [
                    {
                        "id": "view_center",
                        "gimbal": {
                            "pan_rad": defaults.pan_rad,
                            "tilt_rad": defaults.tilt_rad,
                            "timeout_s": defaults.gimbal_timeout_s,
                            "settle_duration_s": defaults.settle_duration_s,
                        },
                    }
                ],
            }
        )

    document: dict[str, Any] = {
        "schema_version": 2,
        "inspection_task_id": task_id,
        "name": task_id,
        "description": "Created by AGT Operator HMI",
        "revision": revision,
        "content_sha256": "sha256:" + "0" * 64,
        "count_target": defaults.count_target,
        "map_binding": {
            "map_id": site.site_id,
            "map_version_id": site.site_revision,
            "manifest_sha256": site.site_hash,
        },
        "points": points,
    }
    document["content_sha256"] = canonical_hash(document)
    return document


class InspectionAuthoringAdapter:
    """Publish point TaskGroups, inspection asset, HOME TaskGroup and Mission."""

    def __init__(
        self,
        *,
        active_site: ActiveTaskSite,
        task_authoring: TaskAuthoringPort,
        repository: InspectionAuthoringRepository,
        mission_repository: MissionAuthoringRepository,
        defaults: FrozenInspectionDefaults | None = None,
    ) -> None:
        self._active_site = active_site
        self._task_authoring = task_authoring
        self._repository = repository
        self._mission_repository = mission_repository
        self._defaults = defaults or FrozenInspectionDefaults()

    def _save_navigation_task(
        self,
        *,
        inspection_task_id: str,
        point: Mapping[str, Any],
        expected_revision: int,
    ) -> dict[str, Any]:
        task = build_single_point_task(
            self._active_site,
            inspection_task_id=inspection_task_id,
            point=point,
            expected_revision=expected_revision,
        )
        waypoint = task.points[0]
        task_payload = dict(
            taskId=task.task_group_id,
            siteId=self._active_site.site_id,
            siteRevision=self._active_site.site_revision,
            expectedRevision=expected_revision,
            loop=False,
            loopCount=1,
            waypoints=[
                dict(
                    id=waypoint.id,
                    x=waypoint.x,
                    y=waypoint.y,
                    yaw=waypoint.yaw,
                    dwellS=0.0,
                )
            ],
        )
        saved = self._task_authoring.save(task.task_group_id, task_payload)
        return {
            "pointId": waypoint.id,
            "taskGroupId": _required_text(saved.get("taskId"), "saved taskId"),
            "revision": int(saved.get("revision", 0)),
            "contentSha256": _required_text(
                saved.get("contentSha256"), "saved contentSha256"
            ),
        }

    def save(self, inspection_task_id: str, payload: Mapping[str, Any]) -> Mapping[str, Any]:
        if not isinstance(payload, Mapping):
            raise ValueError("inspection request must be an object")
        route_id = _required_text(inspection_task_id, "inspection_task_id")
        payload_id = _required_text(payload.get("inspectionTaskId"), "inspectionTaskId")
        if route_id != payload_id:
            raise ValueError("route inspection_task_id must match inspectionTaskId")
        self._active_site.validate_payload_identity(payload)
        expected_revision = _nonnegative_revision(
            payload.get("expectedRevision", 0), "expectedRevision"
        )
        raw_points = payload.get("points")
        if not isinstance(raw_points, list) or not raw_points:
            raise ValueError("points must be a non-empty array")
        raw_home = payload.get("home")
        if not isinstance(raw_home, Mapping):
            raise ValueError("home must be an explicit map pose")
        home_expected_revision = _nonnegative_revision(
            payload.get("expectedHomeTaskRevision", 0),
            "expectedHomeTaskRevision",
        )

        bindings: list[Mapping[str, Any]] = []
        for index, point in enumerate(raw_points):
            if not isinstance(point, Mapping):
                raise ValueError(f"points[{index}] must be an object")
            task_expected_revision = _nonnegative_revision(
                point.get("expectedTaskRevision", 0),
                f"points[{index}].expectedTaskRevision",
            )
            bindings.append(
                self._save_navigation_task(
                    inspection_task_id=route_id,
                    point=point,
                    expected_revision=task_expected_revision,
                )
            )

        document = build_inspection_document(
            site=self._active_site,
            inspection_task_id=route_id,
            expected_revision=expected_revision,
            point_bindings=bindings,
            defaults=self._defaults,
        )
        stored = self._repository.put_document(
            document,
            expected_revision=expected_revision,
        )

        home_point = {
            "id": "home",
            "x": raw_home.get("x"),
            "y": raw_home.get("y"),
            "yaw": raw_home.get("yaw"),
        }
        try:
            float(home_point["x"])
            float(home_point["y"])
            float(home_point["yaw"])
        except (TypeError, ValueError) as exc:
            raise ValueError("home must contain numeric x, y and yaw") from exc
        home_binding = self._save_navigation_task(
            inspection_task_id=route_id,
            point=home_point,
            expected_revision=home_expected_revision,
        )

        mission_document = build_inspection_mission_document(
            site=self._active_site,
            inspection_task_id=stored.inspection_task_id,
            inspection_revision=stored.revision,
            inspection_content_sha256=stored.content_sha256,
            home_binding=home_binding,
        )
        mission = self._mission_repository.put_document(mission_document)
        return {
            "inspectionTaskId": stored.inspection_task_id,
            "state": "SAVED",
            "revision": stored.revision,
            "contentSha256": stored.content_sha256,
            "pointBindings": [dict(item) for item in bindings],
            "homeBinding": dict(home_binding),
            "mission": {
                "missionId": mission.mission_id,
                "missionVersion": mission.mission_version,
                "contentSha256": mission.content_sha256,
            },
        }
