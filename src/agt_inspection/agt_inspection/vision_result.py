from __future__ import annotations

from dataclasses import dataclass
import json
import re
from typing import Any, Mapping


_SHA256_RE = re.compile(r"^sha256:[0-9a-f]{64}$")


class Level1VisionResultError(ValueError):
    """Raised when a Level-1 vision result violates the frozen contract."""


@dataclass(frozen=True)
class Level1VisionResult:
    schema_version: int
    count_target: str
    model_id: str
    model_version: str
    weights_sha256: str
    raw_count: int
    instances: tuple[Mapping[str, Any], ...]
    quality: Mapping[str, Any]
    warnings: tuple[Any, ...]
    payload: Mapping[str, Any]


def _require_nonempty_string(value: Any, name: str) -> str:
    if not isinstance(value, str) or not value:
        raise Level1VisionResultError(f"{name} must be a non-empty string")
    return value


def _require_canonical_sha256(value: Any, name: str = "weights_sha256") -> str:
    if not isinstance(value, str) or _SHA256_RE.fullmatch(value) is None:
        raise Level1VisionResultError(
            f"{name} must be canonical sha256:<64 lowercase hex>"
        )
    return value


def parse_level1_result(
    result_json: str,
    *,
    model_id: str,
    model_version: str,
    weights_sha256: str,
) -> Level1VisionResult:
    """Parse and validate one canonical Level-1 inference result.

    The typed Action result is authoritative for model identity. The JSON payload
    must repeat the same identity so persisted evidence is independently auditable.
    A successful zero-target observation is represented by raw_count == 0 with an
    empty instances array; it is not treated as an inference failure here.
    """

    typed_model_id = _require_nonempty_string(model_id, "model_id")
    typed_model_version = _require_nonempty_string(model_version, "model_version")
    typed_weights_sha256 = _require_canonical_sha256(weights_sha256)

    if not isinstance(result_json, str):
        raise Level1VisionResultError("result_json must be valid JSON text")
    try:
        payload = json.loads(result_json)
    except (TypeError, json.JSONDecodeError) as exc:
        raise Level1VisionResultError(f"result_json must contain valid JSON: {exc}") from exc

    if not isinstance(payload, dict):
        raise Level1VisionResultError("result_json must contain a JSON object")

    schema_version = payload.get("schema_version")
    if isinstance(schema_version, bool) or schema_version != 1:
        raise Level1VisionResultError("schema_version must be 1")

    count_target = _require_nonempty_string(payload.get("count_target"), "count_target")

    model = payload.get("model")
    if not isinstance(model, dict):
        raise Level1VisionResultError("model must be a JSON object")

    expected_identity = {
        "model_id": typed_model_id,
        "model_version": typed_model_version,
        "weights_sha256": typed_weights_sha256,
    }
    for field, expected in expected_identity.items():
        actual = model.get(field)
        if actual != expected:
            raise Level1VisionResultError(
                f"{field} in result_json does not match typed Action result"
            )

    raw_count = payload.get("raw_count")
    if isinstance(raw_count, bool) or not isinstance(raw_count, int) or raw_count < 0:
        raise Level1VisionResultError("raw_count must be a non-negative integer")

    instances = payload.get("instances")
    if not isinstance(instances, list):
        raise Level1VisionResultError("instances must be a JSON array")
    normalized_instances: list[Mapping[str, Any]] = []
    for index, instance in enumerate(instances):
        if not isinstance(instance, dict):
            raise Level1VisionResultError(
                f"instances[{index}] must be a JSON object"
            )
        normalized_instances.append(dict(instance))

    quality = payload.get("quality")
    if not isinstance(quality, dict):
        raise Level1VisionResultError("quality must be a JSON object")

    warnings = payload.get("warnings")
    if not isinstance(warnings, list):
        raise Level1VisionResultError("warnings must be a JSON array")

    return Level1VisionResult(
        schema_version=1,
        count_target=count_target,
        model_id=typed_model_id,
        model_version=typed_model_version,
        weights_sha256=typed_weights_sha256,
        raw_count=raw_count,
        instances=tuple(normalized_instances),
        quality=dict(quality),
        warnings=tuple(warnings),
        payload=dict(payload),
    )
