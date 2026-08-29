from __future__ import annotations

import hashlib
import json
import math
import re
from typing import Any, Mapping

from .model import (
    AggregationPolicy,
    CameraPolicy,
    GimbalPose,
    InspectionPoint,
    InspectionTask,
    InspectionView,
    MapBinding,
    NavigationBinding,
    RetryPolicy,
    StabilizationPolicy,
    VisionPolicy,
)


LEGACY_SCHEMA_VERSION = 1
SCHEMA_VERSION = 2
SUPPORTED_SCHEMA_VERSIONS = {LEGACY_SCHEMA_VERSION, SCHEMA_VERSION}
SAFE_COMPONENT_RE = re.compile(r"^[A-Za-z0-9][A-Za-z0-9._-]{0,127}$")
SHA256_RE = re.compile(r"^sha256:[0-9a-f]{64}$")

TASK_KEYS_V1 = {
    "schema_version",
    "inspection_task_id",
    "name",
    "description",
    "revision",
    "content_sha256",
    "map_binding",
    "points",
}
TASK_KEYS_V2 = TASK_KEYS_V1 | {"count_target"}
MAP_KEYS = {"map_id", "map_version_id", "manifest_sha256"}
POINT_KEYS_V1 = {
    "id",
    "navigation",
    "stabilization",
    "gimbal",
    "camera",
    "vision",
    "retry",
}
POINT_KEYS_V2 = {
    "id",
    "navigation",
    "stabilization",
    "camera",
    "vision",
    "retry",
    "views",
    "aggregation",
}
VIEW_KEYS = {"id", "gimbal"}
AGGREGATION_KEYS = {"enabled", "aggregation_profile"}
NAV_KEYS = {"task_group_id", "task_revision", "expected_content_sha256"}
STABILIZATION_KEYS = {
    "linear_velocity_max_mps",
    "angular_velocity_max_radps",
    "stable_duration_s",
    "timeout_s",
}
GIMBAL_KEYS = {"pan_rad", "tilt_rad", "timeout_s", "settle_duration_s"}
CAMERA_KEYS = {"camera_id", "capture_count", "capture_interval_s"}
VISION_KEYS = {"task_id", "model_profile", "minimum_confidence", "timeout_s"}
RETRY_KEYS = {"navigation", "gimbal", "capture", "inference"}


class InspectionTaskError(ValueError):
    pass


def _mapping(value: object, name: str) -> Mapping[str, Any]:
    if not isinstance(value, Mapping):
        raise InspectionTaskError(f"{name} must be an object")
    return value


def _exact_keys(value: Mapping[str, Any], expected: set[str], name: str) -> None:
    unknown = set(value) - expected
    missing = expected - set(value)
    if unknown or missing:
        raise InspectionTaskError(
            f"{name} keys are invalid; missing={sorted(missing)}, unknown={sorted(unknown)}"
        )


def _component(value: object, name: str) -> str:
    if not isinstance(value, str) or not SAFE_COMPONENT_RE.fullmatch(value):
        raise InspectionTaskError(f"{name} must be a portable identifier")
    return value


def _text(value: object, name: str, *, allow_empty: bool = False) -> str:
    if not isinstance(value, str) or (not allow_empty and not value.strip()):
        raise InspectionTaskError(
            f"{name} must be a string" + ("" if allow_empty else " and not empty")
        )
    return value


def _sha256(value: object, name: str) -> str:
    if not isinstance(value, str) or not SHA256_RE.fullmatch(value):
        raise InspectionTaskError(f"{name} must be sha256:<64 lowercase hex>")
    return value


def _finite(value: object, name: str) -> float:
    if isinstance(value, bool) or not isinstance(value, (int, float)):
        raise InspectionTaskError(f"{name} must be numeric")
    result = float(value)
    if not math.isfinite(result):
        raise InspectionTaskError(f"{name} must be finite")
    return result


def _positive(value: object, name: str, *, maximum: float = 86400.0) -> float:
    result = _finite(value, name)
    if result <= 0.0 or result > maximum:
        raise InspectionTaskError(f"{name} must be in (0, {maximum}]")
    return result


def _nonnegative(value: object, name: str, *, maximum: float = 86400.0) -> float:
    result = _finite(value, name)
    if result < 0.0 or result > maximum:
        raise InspectionTaskError(f"{name} must be in [0, {maximum}]")
    return result


def _positive_int(value: object, name: str, *, maximum: int) -> int:
    if isinstance(value, bool) or not isinstance(value, int) or value <= 0 or value > maximum:
        raise InspectionTaskError(f"{name} must be an integer in 1..{maximum}")
    return value


def _retry(value: object, name: str) -> int:
    if isinstance(value, bool) or not isinstance(value, int) or value < 0 or value > 10:
        raise InspectionTaskError(f"{name} must be an integer in 0..10")
    return value


def canonical_hash(document: Mapping[str, Any]) -> str:
    payload = dict(document)
    payload.pop("content_sha256", None)
    encoded = json.dumps(
        payload,
        ensure_ascii=False,
        sort_keys=True,
        separators=(",", ":"),
        allow_nan=False,
    ).encode("utf-8")
    return "sha256:" + hashlib.sha256(encoded).hexdigest()


def _parse_navigation(raw: Mapping[str, Any], index: int) -> NavigationBinding:
    navigation_raw = _mapping(raw["navigation"], f"point {index}.navigation")
    _exact_keys(navigation_raw, NAV_KEYS, f"point {index}.navigation")
    return NavigationBinding(
        task_group_id=_component(
            navigation_raw["task_group_id"], f"point {index}.navigation.task_group_id"
        ),
        task_revision=_positive_int(
            navigation_raw["task_revision"],
            f"point {index}.navigation.task_revision",
            maximum=2**32 - 1,
        ),
        expected_content_sha256=_sha256(
            navigation_raw["expected_content_sha256"],
            f"point {index}.navigation.expected_content_sha256",
        ),
    )


def _parse_stabilization(raw: Mapping[str, Any], index: int) -> StabilizationPolicy:
    stabilization_raw = _mapping(raw["stabilization"], f"point {index}.stabilization")
    _exact_keys(stabilization_raw, STABILIZATION_KEYS, f"point {index}.stabilization")
    return StabilizationPolicy(
        linear_velocity_max_mps=_positive(
            stabilization_raw["linear_velocity_max_mps"],
            f"point {index}.stabilization.linear_velocity_max_mps",
            maximum=10.0,
        ),
        angular_velocity_max_radps=_positive(
            stabilization_raw["angular_velocity_max_radps"],
            f"point {index}.stabilization.angular_velocity_max_radps",
            maximum=20.0,
        ),
        stable_duration_s=_positive(
            stabilization_raw["stable_duration_s"],
            f"point {index}.stabilization.stable_duration_s",
            maximum=60.0,
        ),
        timeout_s=_positive(
            stabilization_raw["timeout_s"],
            f"point {index}.stabilization.timeout_s",
            maximum=300.0,
        ),
    )


def _parse_gimbal(value: object, name: str) -> GimbalPose:
    raw = _mapping(value, name)
    _exact_keys(raw, GIMBAL_KEYS, name)
    return GimbalPose(
        pan_rad=_finite(raw["pan_rad"], f"{name}.pan_rad"),
        tilt_rad=_finite(raw["tilt_rad"], f"{name}.tilt_rad"),
        timeout_s=_positive(raw["timeout_s"], f"{name}.timeout_s", maximum=300.0),
        settle_duration_s=_nonnegative(
            raw["settle_duration_s"], f"{name}.settle_duration_s", maximum=60.0
        ),
    )


def _parse_camera(raw: Mapping[str, Any], index: int) -> CameraPolicy:
    camera_raw = _mapping(raw["camera"], f"point {index}.camera")
    _exact_keys(camera_raw, CAMERA_KEYS, f"point {index}.camera")
    return CameraPolicy(
        camera_id=_component(camera_raw["camera_id"], f"point {index}.camera.camera_id"),
        capture_count=_positive_int(
            camera_raw["capture_count"], f"point {index}.camera.capture_count", maximum=20
        ),
        capture_interval_s=_nonnegative(
            camera_raw["capture_interval_s"],
            f"point {index}.camera.capture_interval_s",
            maximum=60.0,
        ),
    )


def _parse_vision(raw: Mapping[str, Any], index: int) -> VisionPolicy:
    vision_raw = _mapping(raw["vision"], f"point {index}.vision")
    _exact_keys(vision_raw, VISION_KEYS, f"point {index}.vision")
    confidence = _finite(
        vision_raw["minimum_confidence"], f"point {index}.vision.minimum_confidence"
    )
    if confidence < 0.0 or confidence > 1.0:
        raise InspectionTaskError(
            f"point {index}.vision.minimum_confidence must be in [0, 1]"
        )
    return VisionPolicy(
        task_id=_component(vision_raw["task_id"], f"point {index}.vision.task_id"),
        model_profile=_component(
            vision_raw["model_profile"], f"point {index}.vision.model_profile"
        ),
        minimum_confidence=confidence,
        timeout_s=_positive(
            vision_raw["timeout_s"], f"point {index}.vision.timeout_s", maximum=3600.0
        ),
    )


def _parse_retry(raw: Mapping[str, Any], index: int) -> RetryPolicy:
    retry_raw = _mapping(raw["retry"], f"point {index}.retry")
    _exact_keys(retry_raw, RETRY_KEYS, f"point {index}.retry")
    return RetryPolicy(
        navigation=_retry(retry_raw["navigation"], "retry.navigation"),
        gimbal=_retry(retry_raw["gimbal"], "retry.gimbal"),
        capture=_retry(retry_raw["capture"], "retry.capture"),
        inference=_retry(retry_raw["inference"], "retry.inference"),
    )


def _parse_point_v1(value: object, index: int) -> InspectionPoint:
    raw = _mapping(value, f"point {index}")
    _exact_keys(raw, POINT_KEYS_V1, f"point {index}")
    return InspectionPoint(
        id=_component(raw["id"], f"point {index}.id"),
        navigation=_parse_navigation(raw, index),
        stabilization=_parse_stabilization(raw, index),
        gimbal=_parse_gimbal(raw["gimbal"], f"point {index}.gimbal"),
        camera=_parse_camera(raw, index),
        vision=_parse_vision(raw, index),
        retry=_parse_retry(raw, index),
    )


def _parse_point_v2(value: object, index: int, *, maximum_views: int) -> InspectionPoint:
    raw = _mapping(value, f"point {index}")
    _exact_keys(raw, POINT_KEYS_V2, f"point {index}")

    camera = _parse_camera(raw, index)
    if camera.capture_count != 1:
        raise InspectionTaskError(
            f"point {index}.camera.capture_count must be 1 in schema_version 2; use views[] for distinct viewpoints"
        )

    views_raw = raw["views"]
    if not isinstance(views_raw, list) or not views_raw or len(views_raw) > maximum_views:
        raise InspectionTaskError(f"point {index}.views must contain 1..{maximum_views} entries")
    views: list[InspectionView] = []
    seen_views: set[str] = set()
    for view_index, value in enumerate(views_raw):
        view_raw = _mapping(value, f"point {index}.views[{view_index}]")
        _exact_keys(view_raw, VIEW_KEYS, f"point {index}.views[{view_index}]")
        view_id = _component(view_raw["id"], f"point {index}.views[{view_index}].id")
        if view_id in seen_views:
            raise InspectionTaskError(f"duplicate view id in point {index}: {view_id}")
        seen_views.add(view_id)
        views.append(
            InspectionView(
                id=view_id,
                gimbal=_parse_gimbal(
                    view_raw["gimbal"], f"point {index}.views[{view_index}].gimbal"
                ),
            )
        )

    aggregation_raw = _mapping(raw["aggregation"], f"point {index}.aggregation")
    _exact_keys(aggregation_raw, AGGREGATION_KEYS, f"point {index}.aggregation")
    enabled = aggregation_raw["enabled"]
    if not isinstance(enabled, bool):
        raise InspectionTaskError(f"point {index}.aggregation.enabled must be boolean")
    aggregation = AggregationPolicy(
        enabled=enabled,
        aggregation_profile=_component(
            aggregation_raw["aggregation_profile"],
            f"point {index}.aggregation.aggregation_profile",
        ),
    )

    return InspectionPoint(
        id=_component(raw["id"], f"point {index}.id"),
        navigation=_parse_navigation(raw, index),
        stabilization=_parse_stabilization(raw, index),
        gimbal=None,
        camera=camera,
        vision=_parse_vision(raw, index),
        retry=_parse_retry(raw, index),
        views=tuple(views),
        aggregation=aggregation,
    )


def parse_inspection_task(
    value: object, *, maximum_points: int = 100, maximum_views_per_point: int = 20
) -> InspectionTask:
    raw = _mapping(value, "inspection task")
    schema_version = raw.get("schema_version")
    if schema_version not in SUPPORTED_SCHEMA_VERSIONS:
        raise InspectionTaskError(f"unsupported schema_version: {schema_version}")
    _exact_keys(
        raw,
        TASK_KEYS_V1 if schema_version == LEGACY_SCHEMA_VERSION else TASK_KEYS_V2,
        "inspection task",
    )

    content_hash = _sha256(raw["content_sha256"], "content_sha256")
    try:
        expected_hash = canonical_hash(raw)
    except (TypeError, ValueError) as exc:
        raise InspectionTaskError(f"inspection task contains non-JSON data: {exc}") from exc
    if content_hash != expected_hash:
        raise InspectionTaskError("content_sha256 does not match canonical inspection task content")

    map_raw = _mapping(raw["map_binding"], "map_binding")
    _exact_keys(map_raw, MAP_KEYS, "map_binding")
    binding = MapBinding(
        map_id=_component(map_raw["map_id"], "map_binding.map_id"),
        map_version_id=_component(map_raw["map_version_id"], "map_binding.map_version_id"),
        manifest_sha256=_sha256(map_raw["manifest_sha256"], "map_binding.manifest_sha256"),
    )

    points_raw = raw["points"]
    if not isinstance(points_raw, list) or not points_raw or len(points_raw) > maximum_points:
        raise InspectionTaskError(f"points must contain 1..{maximum_points} entries")
    if schema_version == LEGACY_SCHEMA_VERSION:
        points = tuple(_parse_point_v1(item, index) for index, item in enumerate(points_raw))
        count_target = ""
    else:
        count_target = _component(raw["count_target"], "count_target")
        points = tuple(
            _parse_point_v2(item, index, maximum_views=maximum_views_per_point)
            for index, item in enumerate(points_raw)
        )

    seen: set[str] = set()
    for point in points:
        if point.id in seen:
            raise InspectionTaskError(f"duplicate point id: {point.id}")
        seen.add(point.id)

    return InspectionTask(
        inspection_task_id=_component(raw["inspection_task_id"], "inspection_task_id"),
        name=_text(raw["name"], "name"),
        description=_text(raw["description"], "description", allow_empty=True),
        revision=_positive_int(raw["revision"], "revision", maximum=2**32 - 1),
        content_sha256=content_hash,
        map_binding=binding,
        points=points,
        count_target=count_target,
        schema_version=int(schema_version),
    )
