from __future__ import annotations

import hashlib
import json
import math
from pathlib import Path
from typing import Any, Mapping

import yaml

from .mission_model import (
    MapBinding,
    Mission,
    MissionError,
    MissionStep,
    SCHEMA_VERSION,
    StepType,
    validate_component,
    validate_sha256,
    validate_task_path,
)


MISSION_KEYS = {
    "schema_version",
    "mission_id",
    "mission_version",
    "content_sha256",
    "map_binding",
    "steps",
}
MAP_BINDING_KEYS = {"map_id", "map_version_id", "manifest_sha256"}
STEP_KEYS = {
    StepType.WAYPOINT_TASK: {"id", "type", "task_file"},
    StepType.WAIT_DURATION: {"id", "type", "duration_s"},
    StepType.WAIT_EVENT: {
        "id",
        "type",
        "event_type",
        "event_source",
        "correlation_id",
        "timeout_s",
    },
    StepType.INSPECTION_TASK: {
        "id",
        "type",
        "inspection_task_id",
        "inspection_task_revision",
        "expected_content_sha256",
    },
}
REQUIRED_STEP_KEYS = {
    StepType.WAYPOINT_TASK: {"id", "type", "task_file"},
    StepType.WAIT_DURATION: {"id", "type", "duration_s"},
    StepType.WAIT_EVENT: {"id", "type", "event_type", "timeout_s"},
    StepType.INSPECTION_TASK: {
        "id",
        "type",
        "inspection_task_id",
        "inspection_task_revision",
        "expected_content_sha256",
    },
}


def _exact_keys(
    value: Mapping[str, Any],
    allowed: set[str],
    required: set[str],
    label: str,
) -> None:
    unknown = set(value) - allowed
    missing = required - set(value)
    if unknown or missing:
        raise MissionError(
            f"{label} keys are invalid; missing={sorted(missing)}, "
            f"unknown={sorted(unknown)}"
        )


def _positive_finite(value: object, name: str, maximum: float) -> float:
    if isinstance(value, bool) or not isinstance(value, (int, float)):
        raise MissionError(f"{name} must be numeric")
    result = float(value)
    if not math.isfinite(result) or result <= 0.0 or result > maximum:
        raise MissionError(f"{name} must be finite and in (0, {maximum}]")
    return result


def _positive_revision(value: object, name: str) -> int:
    if isinstance(value, bool) or not isinstance(value, int) or value <= 0:
        raise MissionError(f"{name} must be a positive integer")
    return value


def canonical_hash(document: Mapping[str, Any]) -> str:
    payload = dict(document)
    payload.pop("content_sha256", None)
    encoded = json.dumps(
        payload,
        ensure_ascii=False,
        sort_keys=True,
        separators=(",", ":"),
    ).encode("utf-8")
    return "sha256:" + hashlib.sha256(encoded).hexdigest()


def parse_mission(
    value: object,
    *,
    maximum_duration_s: float = 86400.0,
    maximum_event_timeout_s: float = 86400.0,
    maximum_steps: int = 100,
) -> Mission:
    if not isinstance(value, dict):
        raise MissionError("mission YAML must contain an object")
    _exact_keys(value, MISSION_KEYS, MISSION_KEYS, "mission")
    if value.get("schema_version") != SCHEMA_VERSION:
        raise MissionError(f"unsupported schema_version: {value.get('schema_version')}")

    mission_id = validate_component(value.get("mission_id"), "mission_id")
    mission_version = validate_component(
        value.get("mission_version"), "mission_version"
    )
    content_hash = validate_sha256(
        value.get("content_sha256"), "content_sha256"
    )
    expected_hash = canonical_hash(value)
    if content_hash != expected_hash:
        raise MissionError("content_sha256 does not match canonical mission content")

    raw_binding = value.get("map_binding")
    if not isinstance(raw_binding, dict):
        raise MissionError("map_binding must be an object")
    _exact_keys(
        raw_binding,
        MAP_BINDING_KEYS,
        MAP_BINDING_KEYS,
        "map_binding",
    )
    binding = MapBinding(
        map_id=validate_component(
            raw_binding.get("map_id"), "map_binding.map_id"
        ),
        map_version_id=validate_component(
            raw_binding.get("map_version_id"), "map_binding.map_version_id"
        ),
        manifest_sha256=validate_sha256(
            raw_binding.get("manifest_sha256"),
            "map_binding.manifest_sha256",
        ),
    )

    raw_steps = value.get("steps")
    if (
        not isinstance(raw_steps, list)
        or not raw_steps
        or len(raw_steps) > maximum_steps
    ):
        raise MissionError(f"steps must contain 1..{maximum_steps} entries")

    seen: set[str] = set()
    steps: list[MissionStep] = []
    type_map = {
        item.name: item for item in StepType if item != StepType.UNKNOWN
    }
    for index, raw in enumerate(raw_steps):
        if not isinstance(raw, dict):
            raise MissionError(f"step {index} must be an object")
        raw_type = raw.get("type")
        if not isinstance(raw_type, str) or raw_type not in type_map:
            raise MissionError(
                f"step {index} has unsupported type: {raw_type}"
            )
        step_type = type_map[raw_type]
        _exact_keys(
            raw,
            STEP_KEYS[step_type],
            REQUIRED_STEP_KEYS[step_type],
            f"step {index}",
        )
        step_id = validate_component(raw.get("id"), f"step {index}.id")
        if step_id in seen:
            raise MissionError(f"duplicate step id: {step_id}")
        seen.add(step_id)

        if step_type == StepType.WAYPOINT_TASK:
            step = MissionStep(
                step_id,
                step_type,
                task_file=validate_task_path(raw.get("task_file")),
            )
        elif step_type == StepType.WAIT_DURATION:
            step = MissionStep(
                step_id,
                step_type,
                duration_s=_positive_finite(
                    raw.get("duration_s"),
                    "duration_s",
                    maximum_duration_s,
                ),
            )
        elif step_type == StepType.WAIT_EVENT:
            event_type = validate_component(
                raw.get("event_type"), "event_type"
            )
            event_source = raw.get("event_source", "")
            correlation_id = raw.get("correlation_id", "")
            if not isinstance(event_source, str) or (
                event_source
                and not validate_component(event_source, "event_source")
            ):
                raise MissionError(
                    "event_source must be empty or a portable identifier"
                )
            if not isinstance(correlation_id, str) or (
                correlation_id
                and not validate_component(
                    correlation_id, "correlation_id"
                )
            ):
                raise MissionError(
                    "correlation_id must be empty or a portable identifier"
                )
            step = MissionStep(
                step_id,
                step_type,
                event_type=event_type,
                event_source=event_source,
                correlation_id=correlation_id,
                timeout_s=_positive_finite(
                    raw.get("timeout_s"),
                    "timeout_s",
                    maximum_event_timeout_s,
                ),
            )
        else:
            step = MissionStep(
                step_id,
                step_type,
                inspection_task_id=validate_component(
                    raw.get("inspection_task_id"),
                    "inspection_task_id",
                ),
                inspection_task_revision=_positive_revision(
                    raw.get("inspection_task_revision"),
                    "inspection_task_revision",
                ),
                expected_content_sha256=validate_sha256(
                    raw.get("expected_content_sha256"),
                    "expected_content_sha256",
                ),
            )
        steps.append(step)

    return Mission(
        mission_id=mission_id,
        mission_version=mission_version,
        content_sha256=content_hash,
        map_binding=binding,
        steps=tuple(steps),
    )


def load_mission(path: str | Path, **limits: Any) -> Mission:
    try:
        with open(path, "r", encoding="utf-8") as stream:
            document = yaml.safe_load(stream)
    except (OSError, UnicodeError, yaml.YAMLError) as exc:
        raise MissionError(f"cannot read mission YAML: {exc}") from exc
    return parse_mission(document, **limits)
