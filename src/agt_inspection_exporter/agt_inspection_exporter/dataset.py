from __future__ import annotations

import csv
import json
import math
import re
import shutil
from decimal import Decimal
from pathlib import Path
from typing import Any

IMAGE_RE = re.compile(r"^image_(?P<timestamp>[0-9]+(?:\.[0-9]+)?)\.(?:jpg|jpeg|png|pgm|ppm)$", re.I)


def _json(path: Path) -> dict[str, Any]:
    return json.loads(path.read_text(encoding="utf-8"))


def _stamp(value: Any) -> float:
    return float(value)


def export_run(run_dir: str | Path, dataset_dir: str | Path) -> Path:
    """Export the frozen metadata files into agt_vision_runtime's flat dataset."""
    run = Path(run_dir).expanduser()
    output = Path(dataset_dir).expanduser()
    metadata_dir = run / "metadata"
    records = []
    for metadata_path in sorted(metadata_dir.glob("P*.json")):
        item = _json(metadata_path)
        image = item["image"]
        source = run / image["path"]
        if not source.is_file():
            raise FileNotFoundError(f"metadata image does not exist: {source}")
        timestamp = _stamp(image["timestamp"])
        name = f"image_{_format_timestamp(timestamp)}.jpg"
        destination = output / "images" / name
        destination.parent.mkdir(parents=True, exist_ok=True)
        if source.suffix.lower() in (".jpg", ".jpeg"):
            shutil.copy2(source, destination)
        else:
            try:
                from PIL import Image
                with Image.open(source) as rendered:
                    rendered.convert("RGB").save(destination, format="JPEG")
            except (ImportError, OSError) as exc:
                raise ValueError(f"cannot convert {source} to JPEG: {exc}") from exc
        records.append((name, item))

    if not records:
        raise ValueError(f"no metadata/P*.json captures found in {run}")
    output.mkdir(parents=True, exist_ok=True)
    with (output / "pose.csv").open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=["timestamp", "x", "y", "z", "qx", "qy", "qz", "qw", "frame"])
        writer.writeheader()
        for _, item in records:
            pose = item["robot_pose"]
            writer.writerow({key: pose[key] for key in writer.fieldnames})
    with (output / "gimbal.csv").open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=["timestamp", "yaw", "pitch", "roll"])
        writer.writeheader()
        for _, item in records:
            gimbal = item["gimbal"]
            writer.writerow({key: gimbal[key] for key in writer.fieldnames})
    return output


def _read_csv(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as stream:
        rows = list(csv.DictReader(stream))
    if not rows or "timestamp" not in rows[0]:
        raise ValueError(f"{path} must contain a timestamp column and at least one row")
    return rows


def validate_dataset(dataset_dir: str | Path, tolerance_ms: float = 50.0) -> dict[str, Any]:
    dataset = Path(dataset_dir).expanduser()
    tolerance = float(tolerance_ms) / 1000.0
    errors: list[str] = []
    try:
        pose_rows = _read_csv(dataset / "pose.csv")
    except (OSError, ValueError) as exc:
        pose_rows = []
        errors.append(str(exc))
    try:
        gimbal_rows = _read_csv(dataset / "gimbal.csv")
    except (OSError, ValueError) as exc:
        gimbal_rows = []
        errors.append(str(exc))
    pose = [_stamp(row["timestamp"]) for row in pose_rows]
    gimbal = [_stamp(row["timestamp"]) for row in gimbal_rows]
    image_times = []
    image_dir = dataset / "images"
    image_paths = sorted(image_dir.iterdir()) if image_dir.is_dir() else []
    if not image_dir.is_dir():
        errors.append(f"images directory does not exist: {image_dir}")
    for path in image_paths:
        match = IMAGE_RE.match(path.name)
        if match:
            image_times.append(_stamp(match.group("timestamp")))
        elif path.is_file():
            errors.append(f"image filename has no timestamp: {path.name}")

    def deltas(log: list[float]) -> list[float]:
        return [min((abs(value - item) for item in log), default=math.inf) for value in image_times]

    pose_delta = deltas(pose)
    gimbal_delta = deltas(gimbal)
    matched_pose = sum(value <= tolerance for value in pose_delta)
    matched_gimbal = sum(value <= tolerance for value in gimbal_delta)
    finite_pose = [value for value in pose_delta if math.isfinite(value)]
    finite_gimbal = [value for value in gimbal_delta if math.isfinite(value)]
    report = {
        "images": len(image_times), "matched_pose": matched_pose,
        "matched_gimbal": matched_gimbal,
        "mean_pose_delta_ms": _mean_ms(finite_pose), "max_pose_delta_ms": _max_ms(finite_pose),
        "mean_gimbal_delta_ms": _mean_ms(finite_gimbal), "max_gimbal_delta_ms": _max_ms(finite_gimbal),
        "tolerance_ms": float(tolerance_ms), "valid": not errors and matched_pose == len(image_times) and matched_gimbal == len(image_times),
        "errors": errors,
    }
    (dataset / "dataset_validation_report.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    return report


def _mean_ms(values: list[float]) -> float | None:
    return round(sum(values) / len(values) * 1000.0, 3) if values else None


def _max_ms(values: list[float]) -> float | None:
    return round(max(values) * 1000.0, 3) if values else None


def _format_timestamp(timestamp: float) -> str:
    rendered = format(Decimal(str(float(timestamp))), "f")
    return rendered.rstrip("0").rstrip(".") if "." in rendered else rendered
