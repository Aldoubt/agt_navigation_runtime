#!/usr/bin/env python3

"""Publish the current reviewed commissioning map as an immutable Site revision."""

from __future__ import annotations

import argparse
import json
from pathlib import Path

from agt_field_commissioning.reviewed_site import ReviewedSitePublisher


def _parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Validate and publish map_review/reviewed_map.* as an immutable Site revision"
    )
    parser.add_argument("--runtime-dir", required=True)
    parser.add_argument("--site-id", required=True)
    parser.add_argument("--run-id", required=True)
    parser.add_argument("--revision", required=True)
    parser.add_argument("--sites-root", default="/opt/agt/sites")
    parser.add_argument(
        "--state-root", default="~/.local/state/agt_navigation_runtime"
    )
    parser.add_argument("--vehicle-profile", required=True)
    parser.add_argument("--vehicle-schema", default="")
    parser.add_argument("--site-schema", default="")
    parser.add_argument(
        "--activate",
        action="store_true",
        help="explicitly persist this newly validated revision as the active Site",
    )
    return parser


def _schema_path(value: str, filename: str) -> Path:
    text = str(value).strip()
    if text:
        path = Path(text).expanduser().resolve()
    else:
        try:
            from ament_index_python.packages import get_package_share_directory
        except ImportError as exc:  # pragma: no cover - installed ROS boundary
            raise RuntimeError(
                f"--{filename.replace('_', '-')} is required outside a sourced ROS workspace"
            ) from exc
        share = Path(get_package_share_directory("agt_runtime_contracts"))
        path = share / "schemas" / filename
    if not path.is_file():
        raise RuntimeError(f"contract schema does not exist: {path}")
    return path


def publish(args: argparse.Namespace) -> dict[str, object]:
    vehicle_schema = _schema_path(args.vehicle_schema, "vehicle_profile.schema.json")
    site_schema = _schema_path(args.site_schema, "site_package.schema.json")
    publisher = ReviewedSitePublisher(
        runtime_dir=Path(args.runtime_dir),
        sites_root=Path(args.sites_root),
        state_root=Path(args.state_root),
        vehicle_profile=Path(args.vehicle_profile),
        vehicle_schema=vehicle_schema,
        site_schema=site_schema,
    )
    saved = publisher.save_review(args.site_id, args.run_id, args.revision)
    activated = False
    if args.activate:
        publisher.activate_revision(args.site_id, args.revision)
        activated = True
    return {
        "status": "SITE_READY",
        "site_id": saved["site_id"],
        "revision": saved["revision"],
        "site_root": saved["site_root"],
        "validated": bool(saved["validated"]),
        "activated": activated,
        "checks": list(saved.get("checks", [])),
    }


def main(argv=None) -> int:
    args = _parser().parse_args(argv)
    print(json.dumps(publish(args), ensure_ascii=False, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
