from __future__ import annotations

import math
from typing import Any

from .capture_strategy import CaptureStrategy, CaptureView


class FixedOverviewCaptureStrategy(CaptureStrategy):
    """Generate one overview view aligned to the waypoint heading."""

    def __init__(self, *, pitch: float = math.radians(45.0), roll: float = 0.0) -> None:
        self.pitch = float(pitch)
        self.roll = float(roll)

    def generate_views(self, waypoint: Any) -> list[CaptureView]:
        try:
            yaw = float(waypoint.theta)
        except AttributeError as exc:
            raise ValueError("fixed overview strategy requires waypoint.theta") from exc
        if not all(math.isfinite(v) for v in (yaw, self.pitch, self.roll)):
            raise ValueError("capture view angles must be finite")
        return [CaptureView(yaw=yaw, pitch=self.pitch, roll=self.roll, name="overview")]
