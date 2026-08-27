#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Any, Mapping

import yaml


REQUIRED_TOPICS = (
    "/tf",
    "/tf_static",
    "/agt/sensors/lidar/custom",
    "/agt/sensors/imu/data",
    "/agt/chassis/odometry",
    "/agt/chassis/status",
    "/agt/mapping/odometry",
    "/agt/mapping/registered_points",
    "/agt/navigation/cmd_vel",
    "/diagnostics",
)
GNSS_TOPIC = "/agt/sensors/gnss/fix"


def _duration_nanoseconds(information: Mapping[str, Any]) -> int:
    duration = information.get("duration", {})
    if isinstance(duration, Mapping):
        return int(duration.get("nanoseconds", 0) or 0)
    try:
        return int(duration or 0)
    except (TypeError, ValueError):
        return 0


def _topic_counts(information: Mapping[str, Any]) -> dict[str, int]:
    records = information.get("topics_with_message_count", [])
    if not isinstance(records, list):
        raise ValueError("topics_with_message_count must be a list")

    counts: dict[str, int] = {}
    for record in records:
        if not isinstance(record, Mapping):
            continue
        metadata = record.get("topic_metadata", {})
        if not isinstance(metadata, Mapping):
            continue
        name = str(metadata.get("name", "")).strip()
        if not name:
            continue
        try:
            count = int(record.get("message_count", 0) or 0)
        except (TypeError, ValueError) as error:
            raise ValueError(f"invalid message_count for {name}") from error
        counts[name] = counts.get(name, 0) + count
    return counts


def validate_metadata(metadata: dict, require_gnss: bool = False) -> dict:
    if not isinstance(metadata, Mapping):
        raise ValueError("metadata must be a mapping")
    information = metadata.get("rosbag2_bagfile_information")
    if not isinstance(information, Mapping):
        raise ValueError("metadata is missing rosbag2_bagfile_information")

    counts = _topic_counts(information)
    required = list(REQUIRED_TOPICS)
    if require_gnss:
        required.append(GNSS_TOPIC)

    missing_topics = sorted(topic for topic in required if topic not in counts)
    empty_topics = sorted(
        topic for topic in required if topic in counts and counts.get(topic, 0) <= 0
    )
    gnss_present = counts.get(GNSS_TOPIC, 0) > 0

    return {
        "accepted": not missing_topics and not empty_topics,
        "missing_topics": missing_topics,
        "empty_topics": empty_topics,
        "message_counts": dict(sorted(counts.items())),
        "duration_nanoseconds": _duration_nanoseconds(information),
        "gnss_present": gnss_present,
    }


def validate_bag_directory(
    bag_directory: str | Path, require_gnss: bool = False
) -> dict:
    bag = Path(bag_directory).expanduser().resolve()
    metadata_path = bag / "metadata.yaml"
    try:
        if not bag.is_dir():
            raise ValueError(f"bag directory does not exist: {bag}")
        if not metadata_path.is_file():
            raise ValueError(f"metadata.yaml is missing: {metadata_path}")
        metadata = yaml.safe_load(metadata_path.read_text(encoding="utf-8"))
        result = validate_metadata(metadata, require_gnss=require_gnss)
        result["bag_directory"] = str(bag)
        result["metadata_path"] = str(metadata_path)
        return result
    except (OSError, UnicodeError, yaml.YAMLError, ValueError, TypeError) as error:
        return {
            "accepted": False,
            "missing_topics": [],
            "empty_topics": [],
            "message_counts": {},
            "duration_nanoseconds": 0,
            "gnss_present": False,
            "bag_directory": str(bag),
            "metadata_path": str(metadata_path),
            "error": str(error),
        }


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Validate the structural topic contract of a completed AGT calibration rosbag2 bundle."
    )
    parser.add_argument("bag_directory", help="Path containing rosbag2 metadata.yaml")
    parser.add_argument(
        "--require-gnss",
        action="store_true",
        help="Reject the bag unless canonical GNSS contains at least one message.",
    )
    args = parser.parse_args()

    result = validate_bag_directory(
        args.bag_directory, require_gnss=bool(args.require_gnss)
    )
    print(json.dumps(result, indent=2, ensure_ascii=False, sort_keys=True))
    return 0 if result["accepted"] else 2


if __name__ == "__main__":
    raise SystemExit(main())
