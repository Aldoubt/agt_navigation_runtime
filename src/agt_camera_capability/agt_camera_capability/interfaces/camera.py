from __future__ import annotations

from dataclasses import dataclass
from typing import Protocol


@dataclass(frozen=True)
class CaptureRequest:
    request_id: str
    waypoint_id: str
    target_heading: float = 0.0
    target_pitch: float = 0.0
    capture_tag: str = ""
    save_image: bool = True
    camera_id: str = "inspection_camera"
    # Strategy metadata. Existing heading/pitch fields remain the wire-compatible
    # defaults used by older callers and camera services.
    view_name: str = ""
    target_yaw: float | None = None
    target_roll: float = 0.0

    @property
    def yaw(self) -> float:
        return float(self.target_heading if self.target_yaw is None else self.target_yaw)


@dataclass(frozen=True)
class CaptureResult:
    success: bool
    image_bytes: bytes = b""
    image_uri: str = ""
    image_suffix: str = ".img"
    message: str = ""
    actual_heading: float | None = None
    actual_pitch: float | None = None
    capture_stamp: float | None = None
    error_code: int = 0


class CameraBackend(Protocol):
    def ready(self) -> tuple[bool, str]: ...
    async def capture(self, request: CaptureRequest) -> CaptureResult: ...
    async def cancel(self) -> bool: ...
