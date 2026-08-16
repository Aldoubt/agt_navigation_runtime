from __future__ import annotations

from dataclasses import dataclass
import json
from pathlib import Path
from typing import Any, Mapping

import yaml
from jsonschema import Draft202012Validator


@dataclass(frozen=True)
class ValidationIssue:
    code: str
    message: str


@dataclass(frozen=True)
class ValidationReport:
    ok: bool
    checks: tuple[str, ...] = ()
    issues: tuple[ValidationIssue, ...] = ()


def load_yaml(path: Path) -> dict[str, Any]:
    with Path(path).open("r", encoding="utf-8") as stream:
        data = yaml.safe_load(stream)
    if not isinstance(data, Mapping):
        raise ValueError(f"YAML root must be a mapping: {path}")
    return dict(data)


def _load_json(path: Path) -> dict[str, Any]:
    with Path(path).open("r", encoding="utf-8") as stream:
        data = json.load(stream)
    if not isinstance(data, Mapping):
        raise ValueError(f"JSON root must be an object: {path}")
    return dict(data)


def _format_jsonschema_error(error: Any) -> str:
    location = ".".join(str(part) for part in error.absolute_path)
    if location:
        return f"{location}: {error.message}"
    return error.message


def validate_vehicle_profile(path: Path, schema_path: Path) -> ValidationReport:
    try:
        profile = load_yaml(path)
        schema = _load_json(schema_path)
        validator = Draft202012Validator(schema)
        errors = sorted(validator.iter_errors(profile), key=lambda item: list(item.absolute_path))
    except (OSError, ValueError, json.JSONDecodeError, yaml.YAMLError) as exc:
        return ValidationReport(
            ok=False,
            issues=(ValidationIssue("VEHICLE_SCHEMA", str(exc)),),
        )

    if errors:
        return ValidationReport(
            ok=False,
            issues=tuple(
                ValidationIssue("VEHICLE_SCHEMA", _format_jsonschema_error(error))
                for error in errors
            ),
        )

    return ValidationReport(ok=True, checks=("vehicle schema",))
