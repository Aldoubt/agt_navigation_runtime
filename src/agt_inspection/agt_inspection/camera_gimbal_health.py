from __future__ import annotations

from dataclasses import dataclass
import math


@dataclass
class CameraGimbalHealthGate:
    """Pure freshness/readiness policy for the camera-gimbal capability."""

    freshness_s: float = 1.5
    _state: int | None = None
    _camera_alive: bool = False
    _gimbal_serial_connected: bool = False
    _gimbal_feedback_alive: bool = False
    _move_action_ready: bool = False
    _busy: bool = False
    _seen_monotonic: float | None = None

    READY_STATE = 1

    def __post_init__(self) -> None:
        self.freshness_s = max(float(self.freshness_s), 0.01)

    def update(
        self,
        *,
        state: int,
        camera_alive: bool,
        gimbal_serial_connected: bool,
        gimbal_feedback_alive: bool,
        move_action_ready: bool,
        busy: bool,
        seen_monotonic: float,
    ) -> None:
        seen = float(seen_monotonic)
        if not math.isfinite(seen):
            raise ValueError("seen_monotonic must be finite")
        self._state = int(state)
        self._camera_alive = bool(camera_alive)
        self._gimbal_serial_connected = bool(gimbal_serial_connected)
        self._gimbal_feedback_alive = bool(gimbal_feedback_alive)
        self._move_action_ready = bool(move_action_ready)
        self._busy = bool(busy)
        self._seen_monotonic = seen

    def reason(self, now: float) -> str:
        current = float(now)
        if not math.isfinite(current):
            return "INVALID_NOW"
        if self._seen_monotonic is None:
            return "NO_HEALTH_SAMPLE"
        age = current - self._seen_monotonic
        if age < 0.0 or age > self.freshness_s:
            return "HEALTH_STALE"
        if self._state != self.READY_STATE:
            return "STATE_NOT_READY"
        if self._busy:
            return "BUSY"
        if not self._camera_alive:
            return "CAMERA_NOT_ALIVE"
        if not self._gimbal_serial_connected:
            return "GIMBAL_SERIAL_DISCONNECTED"
        if not self._gimbal_feedback_alive:
            return "GIMBAL_FEEDBACK_NOT_ALIVE"
        if not self._move_action_ready:
            return "MOVE_ACTION_NOT_READY"
        return "READY"

    def ready(self, now: float) -> bool:
        return self.reason(now) == "READY"
