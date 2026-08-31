from __future__ import annotations

from dataclasses import asdict, dataclass
import json
from pathlib import Path
import re
import shutil
from typing import Any
from urllib.parse import unquote, urlparse


@dataclass(frozen=True)
class Pose2D:
    x: float
    y: float
    yaw: float

    def to_dict(self) -> dict[str, float]:
        return {key: float(value) for key, value in asdict(self).items()}


def _safe_component(value: str) -> str:
    text = re.sub(r"[^A-Za-z0-9._-]+", "_", str(value).strip())
    text = text.strip("._-")
    return text[:80] or "waypoint"


def _atomic_json(path: Path, document: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_suffix(path.suffix + ".tmp")
    temp.write_text(
        json.dumps(document, ensure_ascii=False, indent=2) + "\n",
        encoding="utf-8",
    )
    temp.replace(path)


class FieldCaptureRun:
    """Filesystem evidence for a single waypoint-capture mission.

    This class intentionally has no ROS or camera dependency. The mission executor
    owns motion and capture; this class only makes the resulting evidence durable
    and easy to inspect on the robot after a field run.
    """

    def __init__(
        self,
        root: Path | str,
        *,
        session_id: str,
        map_id: str,
        map_version_id: str,
        task_group_id: str,
    ) -> None:
        self.root = Path(root).expanduser()
        self.session_id = _safe_component(session_id)
        self.map_id = str(map_id)
        self.map_version_id = str(map_version_id)
        self.task_group_id = str(task_group_id)
        self.run_dir = self.root / self.session_id
        self.run_dir.mkdir(parents=True, exist_ok=False)

    def start(self, home_pose: Pose2D) -> Path:
        path = self.run_dir / "mission.json"
        _atomic_json(
            path,
            {
                "schema_version": 1,
                "session_id": self.session_id,
                "map_id": self.map_id,
                "map_version_id": self.map_version_id,
                "task_group_id": self.task_group_id,
                "home_pose": home_pose.to_dict(),
            },
        )
        return path

    def point_dir(self, index: int, waypoint_id: str) -> Path:
        if int(index) <= 0:
            raise ValueError("waypoint index must be positive")
        path = self.run_dir / f"P{int(index):02d}_{_safe_component(waypoint_id)}"
        path.mkdir(parents=True, exist_ok=True)
        return path

    @staticmethod
    def write_placeholder_image(point_dir: Path) -> Path:
        """Write a valid tiny grayscale PGM for hardware-free commissioning tests."""
        path = Path(point_dir) / "image.pgm"
        path.write_bytes(b"P5\n1 1\n255\n\x80")
        return path

    @staticmethod
    def copy_local_image_uri(point_dir: Path, image_uri: str) -> Path:
        """Copy a camera-produced local file into the mission evidence directory."""
        parsed = urlparse(str(image_uri))
        if parsed.scheme not in ("", "file"):
            raise ValueError(f"only local image_uri values are supported, got {parsed.scheme!r}")
        source = Path(unquote(parsed.path if parsed.scheme else str(image_uri))).expanduser()
        if not source.is_file():
            raise ValueError(f"camera image_uri does not exist: {source}")
        suffix = source.suffix if source.suffix else ".img"
        destination = Path(point_dir) / f"image{suffix.lower()}"
        shutil.copy2(source, destination)
        return destination

    @staticmethod
    def write_sensor_image(
        point_dir: Path,
        *,
        width: int,
        height: int,
        step: int,
        encoding: str,
        data: bytes | bytearray | memoryview,
    ) -> Path:
        """Persist common sensor_msgs/Image payloads without cv_bridge/OpenCV.

        rgb8/bgr8 are written as portable PPM and mono8 as PGM. Row padding is
        removed using ``step`` so the artifact is a normal image file that can be
        inspected with standard image viewers.
        """
        width = int(width)
        height = int(height)
        step = int(step)
        encoding = str(encoding).lower()
        if width <= 0 or height <= 0:
            raise ValueError("captured image width and height must be positive")
        channels = 1 if encoding == "mono8" else 3 if encoding in ("rgb8", "bgr8") else 0
        if channels == 0:
            raise ValueError(f"unsupported capture encoding: {encoding}")
        row_bytes = width * channels
        if step < row_bytes:
            raise ValueError("captured image step is smaller than the packed row size")
        payload = bytes(data)
        if len(payload) < step * height:
            raise ValueError("captured image payload is shorter than height*step")

        packed = bytearray()
        for row in range(height):
            begin = row * step
            row_data = payload[begin : begin + row_bytes]
            if encoding == "bgr8":
                for offset in range(0, len(row_data), 3):
                    packed.extend((row_data[offset + 2], row_data[offset + 1], row_data[offset]))
            else:
                packed.extend(row_data)

        point_dir = Path(point_dir)
        if channels == 1:
            path = point_dir / "image.pgm"
            header = f"P5\n{width} {height}\n255\n".encode("ascii")
        else:
            path = point_dir / "image.ppm"
            header = f"P6\n{width} {height}\n255\n".encode("ascii")
        path.write_bytes(header + bytes(packed))
        return path

    def record_waypoint(
        self,
        *,
        index: int,
        waypoint_id: str,
        target: Pose2D,
        capture: Pose2D | None,
        image_path: Path | str | None,
        navigation_success: bool | None = None,
        capture_success: bool | None = None,
        navigation_message: str = "",
        capture_retry_count: int = 0,
        capture_message: str = "",
        status: str | None = None,
    ) -> Path:
        """Persist one waypoint result with navigation and capture kept independent.

        ``status`` is accepted temporarily for the existing ROS execution server;
        it is normalized immediately into the v2 split outcome and is never
        written to disk. New callers should pass the two explicit success flags.
        """
        if status is not None:
            legacy_success = str(status).upper() == "SUCCESS"
            if navigation_success is None:
                navigation_success = legacy_success
            if capture_success is None:
                capture_success = legacy_success
        if navigation_success is None or capture_success is None:
            raise ValueError(
                "navigation_success and capture_success are required for waypoint evidence"
            )

        retry_count = int(capture_retry_count)
        if retry_count < 0:
            raise ValueError("capture_retry_count must be >= 0")
        if capture_success and image_path is None:
            raise ValueError("successful capture requires image_path")

        point_dir = self.point_dir(index, waypoint_id)
        image_value: str | None = None
        if image_path is not None:
            image = Path(image_path)
            try:
                image_value = str(image.resolve().relative_to(self.run_dir.resolve()))
            except ValueError:
                image_value = str(image)

        waypoint_path = point_dir / "waypoint.json"
        _atomic_json(
            waypoint_path,
            {
                "schema_version": 1,
                "waypoint_id": str(waypoint_id),
                "index": int(index),
                "target_pose": target.to_dict(),
            },
        )
        result_path = point_dir / "result.json"
        _atomic_json(
            result_path,
            {
                "schema_version": 2,
                "waypoint_id": str(waypoint_id),
                "index": int(index),
                "target_pose": target.to_dict(),
                "capture_pose": capture.to_dict() if capture is not None else None,
                "image": image_value,
                "navigation": {
                    "success": bool(navigation_success),
                    "message": str(navigation_message),
                },
                "capture": {
                    "success": bool(capture_success),
                    "retry_count": retry_count,
                    "message": str(capture_message),
                },
            },
        )
        return result_path

    def finish(
        self,
        *,
        success: bool,
        return_home_success: bool,
        completed_waypoints: int,
        total_waypoints: int,
        message: str = "",
    ) -> Path:
        summary_path = self.run_dir / "summary.json"
        _atomic_json(
            summary_path,
            {
                "schema_version": 1,
                "success": bool(success),
                "return_home_success": bool(return_home_success),
                "completed_waypoints": int(completed_waypoints),
                "total_waypoints": int(total_waypoints),
                "images_dir": str(self.run_dir),
                "message": str(message),
            },
        )
        return summary_path
