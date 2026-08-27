from __future__ import annotations

import hashlib
import json
import math
import re
from typing import Any, Mapping

from .model import (
    CameraPolicy,
    GimbalPose,
    InspectionPoint,
    InspectionTask,
    MapBinding,
    NavigationBinding,
    RetryPolicy,
    StabilizationPolicy,
    VisionPolicy,
)


SCHEMA_VERSION = 1
SAFE_COMPONENT_RE = re.compile(r"^[A-Za-z0-9][A-Za-z0-9._-]{0,127}$")
SHA256_RE = re.compile(r"^sha256:[0-9a-f]{64}$")

TASK_KEYS = {
    "schema_version",
    "inspection_task_id",
    "name",
    "description",
    "revision",
    "content_sha256",
    "map_binding",
    "points",
}
MAP_KEYS = {"map_id", "map_version_id", "manifest_sha256"}
POINT_KEYS = {
    "id",
    "navigation",
    "stabilization",
    "gimbal",
    "camera",
    "vision",
    "retry",
}
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
        raise InspectionTaskError(f"{name} must be a string" + ("" if allow_empty else " and not empty"))
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


def _parse_point(value: object, index: int) -> InspectionPoint:
    raw = _mapping(value, f"point {index}")
    _exact_keys(raw, POINT_KEYS, f"point {index}")

    navigation_raw = _mapping(raw["navigation"], f"point {index}.navigation")
    _exact_keys(navigation_raw, NAV_KEYS, f"point {index}.navigation")
    navigation = NavigationBinding(
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

    stabilization_raw = _mapping(raw["stabilization"], f"point {index}.stabilization")
    _exact_keys(stabilization_raw, STABILIZATION_KEYS, f"point {index}.stabilization")
    linear_max = _positive(
        stabilization_raw["linear_velocity_max_mps"],
        f"point {index}.stabilization.linear_velocity_max_mps",
        maximum=10.0,
    )
    angular_max = _positive(
        stabilization_raw["angular_velocity_max_radps"],
        f"point {index}.stabilization.angular_velocity_max_radps",
        maximum=20.0,
    )
    stabilization = StabilizationPolicy(
        linear_velocity_max_mps=linear_max,
        angular_velocity_max_radps=angular_max,
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

    gimbal_raw = _mapping(raw["gimbal"], f"point {index}.gimbal")
    _exact_keys(gimbal_raw, GIMBAL_KEYS, f"point {index}.gimbal")
    gimbal = GimbalPose(
        pan_rad=_finite(gimbal_raw["pan_rad"], f"point {index}.gimbal.pan_rad"),
        tilt_rad=_finite(gimbal_raw["tilt_rad"], f"point {index}.gimbal.tilt_rad"),
        timeout_s=_positive(
            gimbal_raw["timeout_s"], f"point {index}.gimbal.timeout_s", maximum=300.0
        ),
        settle_duration_s=_nonnegative(
            gimbal_raw["settle_duration_s"],
            f"point {index}.gimbal.settle_duration_s",
            maximum=60.0,
        ),
    )

    camera_raw = _mapping(raw["camera"], f"point {index}.camera")
    _exact_keys(camera_raw, CAMERA_KEYS, f"point {index}.camera")
    camera = CameraPolicy(
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

    vision_raw = _mapping(raw["vision"], f"point {index}.vision")
    _exact_keys(vision_raw, VISION_KEYS, f"point {index}.vision")
    confidence = _finite(
        vision_raw["minimum_confidence"], f"point {index}.vision.minimum_confidence"
    )
    if confidence < 0.0 or confidence > 1.0:
        raise InspectionTaskError(
            f"point {index}.vision.minimum_confidence must be in [0, 1]"
        )
    vision = VisionPolicy(
        task_id=_component(vision_raw["task_id"], f"point {index}.vision.task_id"),
        model_profile=_component(
            vision_raw["model_profile"], f"point {index}.vision.model_profile"
        ),
        minimum_confidence=confidence,
        timeout_s=_positive(
            vision_raw["timeout_s"], f"point {index}.vision.timeout_s", maximum=3600.0
        ),
    )

    retry_raw = _mapping(raw["retry"], f"point {index}.retry")
    _exact_keys(retry_raw, RETRY_KEYS, f"point {index}.retry")
    retry = RetryPolicy(
        navigation=_retry(retry_raw["navigation"], "retry.navigation"),
        gimbal=_retry(retry_raw["gimbal"], "retry.gimbal"),
        capture=_retry(retry_raw["capture"], "retry.capture"),
        inference=_retry(retry_raw["inference"], "retry.inference"),
    )

    return InspectionPoint(
        id=_component(raw["id"], f"point {index}.id"),
        navigation=navigation,
        stabilization=stabilization,
        gimbal=gimbal,
        camera=camera,
        vision=vision,
        retry=retry,
    )


def parse_inspection_task(value: object, *, maximum_points: int = 100) -> InspectionTask:
    raw = _mapping(value, "inspection task")
    _exact_keys(raw, TASK_KEYS, "inspection task")
    if raw["schema_version"] != SCHEMA_VERSION:
        raise InspectionTaskError(f"unsupported schema_version: {raw['schema_version']}")

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
    points = tuple(_parse_point(item, index) for index, item in enumerate(points_raw))
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
    )
