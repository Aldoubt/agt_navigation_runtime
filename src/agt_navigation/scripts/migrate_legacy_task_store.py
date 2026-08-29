#!/usr/bin/env python3

"""Operator-invoked migration from legacy map-local tasks to runtime/tasks.

The command is dry-run by default. Pass --apply only after the preflight report
is accepted. Runtime nodes never call this script automatically.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys

from ament_index_python.packages import get_package_share_directory

from agt_navigation.legacy_task_migration import (
    LegacyTaskMigrationError,
    migrate_legacy_task_store,
)
from agt_navigation.site_task_binding import FilesystemSiteBindingResolver


def _parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description=(
            "Explicitly migrate legacy maps/<site>/versions/<revision>/tasks into "
            "the mutable runtime/tasks Task Library. Dry-run is the default."
        )
    )
    parser.add_argument("--map-id", required=True)
    parser.add_argument("--map-version-id", required=True)
    parser.add_argument("--legacy-maps-root", default="runtime/maps")
    parser.add_argument("--tasks-root", default="runtime/tasks")
    parser.add_argument("--sites-root", default="/opt/agt/sites")
    parser.add_argument(
        "--site-vehicle-profile", default="/opt/agt/profiles/bunker.yaml"
    )
    parser.add_argument("--site-schema", default="")
    parser.add_argument("--vehicle-schema", default="")
    parser.add_argument(
        "--apply",
        action="store_true",
        help="write the validated migration; without this flag only preflight is run",
    )
    return parser


def _report_dict(report) -> dict:
    return {
        "map_id": report.map_id,
        "map_version_id": report.map_version_id,
        "source_directory": str(report.source_directory),
        "destination_directory": str(report.destination_directory),
        "dry_run": report.dry_run,
        "migrated_task_ids": list(report.migrated_task_ids),
        "skipped_task_ids": list(report.skipped_task_ids),
        "migrated_route_binding_ids": list(report.migrated_route_binding_ids),
        "skipped_route_binding_ids": list(report.skipped_route_binding_ids),
    }


def main(argv=None) -> int:
    args = _parser().parse_args(argv)
    schema_root = Path(get_package_share_directory("agt_runtime_contracts")) / "schemas"
    site_schema = Path(args.site_schema) if args.site_schema else schema_root / "site_package.schema.json"
    vehicle_schema = (
        Path(args.vehicle_schema)
        if args.vehicle_schema
        else schema_root / "vehicle_profile.schema.json"
    )
    resolver = FilesystemSiteBindingResolver(
        sites_root=args.sites_root,
        vehicle_profile=args.site_vehicle_profile,
        vehicle_schema=vehicle_schema,
        site_schema=site_schema,
    )
    try:
        report = migrate_legacy_task_store(
            legacy_maps_root=args.legacy_maps_root,
            tasks_root=args.tasks_root,
            map_id=args.map_id,
            map_version_id=args.map_version_id,
            site_binding_resolver=resolver,
            dry_run=not args.apply,
        )
    except LegacyTaskMigrationError as exc:
        print(
            json.dumps(
                {"success": False, "code": exc.code, "message": exc.message},
                ensure_ascii=False,
            ),
            file=sys.stderr,
        )
        return 2

    print(json.dumps({"success": True, **_report_dict(report)}, ensure_ascii=False, indent=2))
    if report.dry_run:
        print("Dry-run only. Re-run with --apply to write the migration.", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
