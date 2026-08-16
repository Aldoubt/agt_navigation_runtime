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


def _schema_issues(document: Mapping[str, Any], schema: Mapping[str, Any], code: str) -> tuple[ValidationIssue, ...]:
    validator = Draft202012Validator(schema)
    errors = sorted(validator.iter_errors(document), key=lambda item: list(item.absolute_path))
    return tuple(ValidationIssue(code, _format_jsonschema_error(error)) for error in errors)


def validate_vehicle_profile(path: Path, schema_path: Path) -> ValidationReport:
    try:
        profile = load_yaml(path)
        schema = _load_json(schema_path)
        issues = _schema_issues(profile, schema, "VEHICLE_SCHEMA")
    except (OSError, ValueError, json.JSONDecodeError, yaml.YAMLError) as exc:
        return ValidationReport(
            ok=False,
            issues=(ValidationIssue("VEHICLE_SCHEMA", str(exc)),),
        )

    if issues:
        return ValidationReport(ok=False, issues=issues)

    return ValidationReport(ok=True, checks=("vehicle schema",))


def _resolve_relative_path(site_root: Path, raw: str) -> tuple[Path | None, ValidationIssue | None]:
    candidate = Path(raw)
    if candidate.is_absolute():
        return None, ValidationIssue("ABSOLUTE_PATH", f"absolute Site Package path is forbidden: {raw}")

    root = site_root.resolve()
    resolved = (root / candidate).resolve()
    try:
        resolved.relative_to(root)
    except ValueError:
        return None, ValidationIssue("PATH_ESCAPE", f"path escapes Site Package root: {raw}")

    return resolved, None


def validate_site_package(site_root: Path, schema_path: Path) -> ValidationReport:
    site_root = Path(site_root)
    checks: list[str] = []
    issues: list[ValidationIssue] = []

    try:
        manifest = load_yaml(site_root / "manifest.yaml")
        schema = _load_json(schema_path)
    except (OSError, ValueError, json.JSONDecodeError, yaml.YAMLError) as exc:
        return ValidationReport(
            ok=False,
            issues=(ValidationIssue("SITE_SCHEMA", str(exc)),),
        )

    schema_issues = _schema_issues(manifest, schema, "SITE_SCHEMA")
    if schema_issues:
        return ValidationReport(ok=False, issues=schema_issues)
    checks.append("site schema")

    declared_paths: list[tuple[str, str]] = []
    assets = manifest["assets"]
    for name, raw in assets.items():
        declared_paths.append((f"assets.{name}", raw))
    declared_paths.append(("integrity.hashes_file", manifest["integrity"]["hashes_file"]))

    resolved_paths: list[tuple[str, Path]] = []
    for label, raw in declared_paths:
        resolved, issue = _resolve_relative_path(site_root, raw)
        if issue is not None:
            issues.append(ValidationIssue(issue.code, f"{label}: {issue.message}"))
            continue
        assert resolved is not None
        resolved_paths.append((label, resolved))

    if issues:
        return ValidationReport(ok=False, checks=tuple(checks), issues=tuple(issues))
    checks.append("relative paths")

    for label, path in resolved_paths:
        if not path.is_file():
            issues.append(ValidationIssue("MISSING_ASSET", f"{label}: missing file {path}"))

    if issues:
        return ValidationReport(ok=False, checks=tuple(checks), issues=tuple(issues))
    checks.append("required assets")

    return ValidationReport(ok=True, checks=tuple(checks))
