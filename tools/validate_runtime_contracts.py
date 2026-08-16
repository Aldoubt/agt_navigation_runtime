#!/usr/bin/env python3
from __future__ import annotations

import argparse
from pathlib import Path
import sys

from runtime_contracts.validator import validate_runtime_contracts


REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_VEHICLE_SCHEMA = REPO_ROOT / "schemas/vehicle_profile.schema.json"
DEFAULT_SITE_SCHEMA = REPO_ROOT / "schemas/site_package.schema.json"


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Validate AGT V3 Vehicle Profile and deployable Site Package contracts",
    )
    parser.add_argument("--vehicle", required=True, type=Path, help="Vehicle Profile YAML")
    parser.add_argument("--site", required=True, type=Path, help="Site Package root directory")
    parser.add_argument(
        "--vehicle-schema",
        type=Path,
        default=DEFAULT_VEHICLE_SCHEMA,
        help="Vehicle Profile JSON Schema",
    )
    parser.add_argument(
        "--site-schema",
        type=Path,
        default=DEFAULT_SITE_SCHEMA,
        help="Site Package JSON Schema",
    )
    return parser


def main(argv: list[str] | None = None) -> int:
    args = build_parser().parse_args(argv)

    try:
        report = validate_runtime_contracts(
            args.vehicle,
            args.site,
            args.vehicle_schema,
            args.site_schema,
        )
    except Exception as exc:  # CLI boundary: unexpected execution/configuration error
        print(f"[ERROR] {type(exc).__name__}: {exc}")
        return 1

    for check in report.checks:
        print(f"[PASS] {check}")

    if report.ok:
        print("Runtime contract validation: READY")
        return 0

    for issue in report.issues:
        print(f"[FAIL] {issue.code}: {issue.message}")
    print("Runtime contract validation: NOT READY")
    return 2


if __name__ == "__main__":
    sys.exit(main())
