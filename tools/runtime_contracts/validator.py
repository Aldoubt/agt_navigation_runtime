from __future__ import annotations

from dataclasses import dataclass
import hashlib
import json
from pathlib import Path
import re
from typing import Any, Mapping

import yaml
from jsonschema import Draft202012Validator


_SHA256_RE = re.compile(r"^[0-9a-f]{64}$")


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


def _schema_issues(
    document: Mapping[str, Any],
    schema: Mapping[str, Any],
    code: str,
) -> tuple[ValidationIssue, ...]:
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


def _resolve_relative_path(
    site_root: Path,
    raw: str,
) -> tuple[Path | None, ValidationIssue | None]:
    candidate = Path(raw)
    if candidate.is_absolute():
        return None, ValidationIssue(
            "ABSOLUTE_PATH",
            f"absolute Site Package path is forbidden: {raw}",
        )

    root = site_root.resolve()
    resolved = (root / candidate).resolve()
    try:
        resolved.relative_to(root)
    except ValueError:
        return None, ValidationIssue(
            "PATH_ESCAPE",
            f"path escapes Site Package root: {raw}",
        )

    return resolved, None


def _navigation_image_asset(
    site_root: Path,
    manifest: Mapping[str, Any],
) -> tuple[str | None, Path | None, ValidationIssue | None]:
    navigation_map_raw = manifest["assets"]["navigation_map"]
    navigation_map_path, issue = _resolve_relative_path(site_root, navigation_map_raw)
    if issue is not None or navigation_map_path is None:
        return None, None, issue or ValidationIssue(
            "NAVIGATION_MAP",
            "invalid navigation map path",
        )

    try:
        navigation_map = load_yaml(navigation_map_path)
    except (OSError, ValueError, yaml.YAMLError) as exc:
        return None, None, ValidationIssue("NAVIGATION_MAP", str(exc))

    image_raw = navigation_map.get("image")
    if not isinstance(image_raw, str) or not image_raw.strip():
        return None, None, ValidationIssue(
            "NAVIGATION_MAP",
            "navigation map YAML must declare a non-empty image path",
        )

    if Path(image_raw).is_absolute():
        return None, None, ValidationIssue(
            "ABSOLUTE_PATH",
            f"assets.navigation_map.image: absolute Site Package path is forbidden: {image_raw}",
        )

    image_site_raw = (Path(navigation_map_raw).parent / image_raw).as_posix()
    image_path, image_issue = _resolve_relative_path(site_root, image_site_raw)
    if image_issue is not None or image_path is None:
        return None, None, ValidationIssue(
            image_issue.code if image_issue is not None else "NAVIGATION_MAP",
            "assets.navigation_map.image: "
            + (image_issue.message if image_issue is not None else "invalid image path"),
        )

    return image_site_raw, image_path, None


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
    for name, raw in manifest["assets"].items():
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

    image_raw, image_path, image_issue = _navigation_image_asset(site_root, manifest)
    if image_issue is not None:
        return ValidationReport(
            ok=False,
            checks=tuple(checks),
            issues=(image_issue,),
        )
    assert image_raw is not None and image_path is not None
    if not image_path.is_file():
        return ValidationReport(
            ok=False,
            checks=tuple(checks),
            issues=(
                ValidationIssue(
                    "MISSING_ASSET",
                    f"assets.navigation_map.image: missing file {image_path}",
                ),
            ),
        )
    checks.append("navigation map image")

    return ValidationReport(ok=True, checks=tuple(checks))


def _sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def _validate_integrity(
    site_root: Path,
    manifest: Mapping[str, Any],
) -> tuple[ValidationIssue, ...]:
    issues: list[ValidationIssue] = []
    hashes_raw = manifest["integrity"]["hashes_file"]
    hashes_path, path_issue = _resolve_relative_path(site_root, hashes_raw)
    if path_issue is not None or hashes_path is None:
        return (path_issue or ValidationIssue("HASHES_FILE", "invalid hashes file path"),)

    try:
        hashes_doc = load_yaml(hashes_path)
    except (OSError, ValueError, yaml.YAMLError) as exc:
        return (ValidationIssue("HASHES_FILE", str(exc)),)

    hashes = hashes_doc.get("hashes")
    if not isinstance(hashes, Mapping):
        return (ValidationIssue("HASHES_FILE", "hashes.yaml must contain a 'hashes' mapping"),)

    effective_assets = list(manifest["assets"].values())
    image_raw, _, image_issue = _navigation_image_asset(site_root, manifest)
    if image_issue is not None or image_raw is None:
        return (image_issue or ValidationIssue("NAVIGATION_MAP", "invalid map image"),)
    effective_assets.append(image_raw)

    for raw in effective_assets:
        expected = hashes.get(raw)
        if expected is None:
            issues.append(ValidationIssue("HASH_MISSING", f"missing SHA256 entry for {raw}"))
            continue
        if not isinstance(expected, str) or _SHA256_RE.fullmatch(expected) is None:
            issues.append(ValidationIssue("HASH_FORMAT", f"invalid SHA256 digest for {raw}"))
            continue

        asset_path, asset_issue = _resolve_relative_path(site_root, raw)
        if asset_issue is not None or asset_path is None:
            issues.append(
                asset_issue or ValidationIssue("HASH_MISMATCH", f"invalid asset path {raw}")
            )
            continue
        actual = _sha256(asset_path)
        if actual != expected:
            issues.append(
                ValidationIssue(
                    "HASH_MISMATCH",
                    f"SHA256 mismatch for {raw}: expected {expected}, got {actual}",
                )
            )

    return tuple(issues)


def _validate_ackermann_geometry(
    profile: Mapping[str, Any],
) -> tuple[ValidationIssue, ...]:
    platform = profile["platform"]
    if platform.get("kinematics") != "ackermann":
        return ()

    geometry = platform.get("geometry")
    if not isinstance(geometry, Mapping):
        return (ValidationIssue("ACKERMANN_GEOMETRY", "platform.geometry must be a mapping"),)

    wheelbase = geometry.get("wheel_base", geometry.get("wheelbase"))
    min_turning_radius = geometry.get("min_turning_radius")
    footprint = geometry.get("footprint")

    missing: list[str] = []
    if not isinstance(wheelbase, (int, float)) or wheelbase <= 0:
        missing.append("wheel_base/wheelbase")
    if not isinstance(min_turning_radius, (int, float)) or min_turning_radius <= 0:
        missing.append("min_turning_radius")
    if not isinstance(footprint, list) or len(footprint) < 3:
        missing.append("footprint")

    if missing:
        return (
            ValidationIssue(
                "ACKERMANN_GEOMETRY",
                "invalid or missing Ackermann geometry: " + ", ".join(missing),
            ),
        )
    return ()


def validate_runtime_contracts(
    vehicle_path: Path,
    site_root: Path,
    vehicle_schema_path: Path,
    site_schema_path: Path,
) -> ValidationReport:
    checks: list[str] = []
    issues: list[ValidationIssue] = []

    vehicle_report = validate_vehicle_profile(vehicle_path, vehicle_schema_path)
    checks.extend(vehicle_report.checks)
    issues.extend(vehicle_report.issues)

    site_report = validate_site_package(site_root, site_schema_path)
    checks.extend(site_report.checks)
    issues.extend(site_report.issues)

    if issues:
        return ValidationReport(ok=False, checks=tuple(checks), issues=tuple(issues))

    try:
        profile = load_yaml(vehicle_path)
        manifest = load_yaml(Path(site_root) / "manifest.yaml")
    except (OSError, ValueError, yaml.YAMLError) as exc:
        return ValidationReport(
            ok=False,
            checks=tuple(checks),
            issues=(ValidationIssue("CONTRACT_LOAD", str(exc)),),
        )

    integrity_issues = _validate_integrity(Path(site_root), manifest)
    if integrity_issues:
        return ValidationReport(ok=False, checks=tuple(checks), issues=integrity_issues)
    checks.append("SHA256 integrity")

    vehicle_name = profile["platform"]["name"]
    compatible = manifest["compatibility"]["vehicle_profiles"]
    if vehicle_name not in compatible:
        return ValidationReport(
            ok=False,
            checks=tuple(checks),
            issues=(
                ValidationIssue(
                    "INCOMPATIBLE_VEHICLE",
                    f"vehicle '{vehicle_name}' is not listed in Site Package compatibility",
                ),
            ),
        )
    checks.append("vehicle compatibility")

    ackermann_issues = _validate_ackermann_geometry(profile)
    if ackermann_issues:
        return ValidationReport(ok=False, checks=tuple(checks), issues=ackermann_issues)
    checks.append("Ackermann geometry")

    return ValidationReport(ok=True, checks=tuple(checks))
