"""Fail-closed, ROS-independent odometry settle gate."""

from __future__ import annotations

from dataclasses import dataclass
import math


NOT_READY = "NOT_READY"
STABILIZING = "STABILIZING"
SETTLED = "SETTLED"
STALE = "STALE"
INVALID = "INVALID"
TIMEOUT = "TIMEOUT"


@dataclass(frozen=True)
class SettleStatus:
    state: str
    stable_duration: float = 0.0
    reason: str = ""

    @property
    def settled(self) -> bool:
        return self.state == SETTLED


class OdometrySettleMonitor:
    """Track a continuous low-speed window using monotonic caller time.

    ``odom_stamp`` and ``now`` must use the same clock domain.  The caller owns
    conversion from ROS time and can therefore unit-test this class without ROS.
    """

    def __init__(
        self,
        *,
        linear_velocity_threshold: float,
        angular_velocity_threshold: float,
        stable_duration: float,
        timeout: float,
        odom_stale_timeout: float,
    ) -> None:
        values = (linear_velocity_threshold, angular_velocity_threshold,
                  stable_duration, timeout, odom_stale_timeout)
        if any(not math.isfinite(float(value)) for value in values):
            raise ValueError("settle parameters must be finite")
        if linear_velocity_threshold < 0 or angular_velocity_threshold < 0:
            raise ValueError("velocity thresholds must be non-negative")
        if stable_duration < 0 or timeout <= 0 or odom_stale_timeout <= 0:
            raise ValueError("stable duration must be >= 0 and timeouts positive")
        self.linear_velocity_threshold = float(linear_velocity_threshold)
        self.angular_velocity_threshold = float(angular_velocity_threshold)
        self.stable_duration = float(stable_duration)
        self.timeout = float(timeout)
        self.odom_stale_timeout = float(odom_stale_timeout)
        self._started_at: float | None = None
        self._latest_stamp: float | None = None
        self._latest_received_at: float | None = None
        self._stable_since: float | None = None
        self._state = NOT_READY
        self._reason = "odometry has not been received"

    def start(self, now: float) -> None:
        self._started_at = float(now)
        self._latest_stamp = None
        self._latest_received_at = None
        self._stable_since = None
        self._state = NOT_READY
        self._reason = "odometry has not been received"

    def update(self, *, vx: float, vy: float, wz: float, odom_stamp: float, now: float) -> None:
        now = float(now)
        stamp = float(odom_stamp)
        if not all(math.isfinite(value) for value in (vx, vy, wz, stamp, now)) or stamp <= 0:
            self._stable_since = None
            self._state, self._reason = INVALID, "odometry timestamp or velocity is invalid"
            return
        if self._latest_stamp is not None:
            jump = stamp - self._latest_stamp
            if jump < 0 or jump > max(self.odom_stale_timeout * 4.0, 1.0):
                self._stable_since = None
                self._state, self._reason = INVALID, "odometry timestamp jumped"
        self._latest_stamp = stamp
        self._latest_received_at = now
        low_speed = (
            abs(float(vx)) < self.linear_velocity_threshold
            and abs(float(vy)) < self.linear_velocity_threshold
            and abs(float(wz)) < self.angular_velocity_threshold
        )
        if not low_speed:
            self._stable_since = None
            self._state, self._reason = STABILIZING, "velocity exceeds settle threshold"
        elif self._state == INVALID and self._reason == "odometry timestamp jumped":
            self._stable_since = now
            self._state, self._reason = STABILIZING, "timestamp recovered; stabilizing"
        elif self._stable_since is None:
            self._stable_since = now
            self._state, self._reason = STABILIZING, "stable window started"

    def status(self, now: float) -> SettleStatus:
        now = float(now)
        if self._started_at is None:
            return SettleStatus(NOT_READY, reason="settle monitor has not started")
        if self._latest_stamp is None or self._latest_received_at is None:
            if now - self._started_at >= self.timeout:
                return SettleStatus(TIMEOUT, reason="no odometry received before settle timeout")
            return SettleStatus(NOT_READY, reason=self._reason)
        if now - self._latest_stamp > self.odom_stale_timeout:
            return SettleStatus(STALE, reason="odometry is stale")
        if self._state == INVALID:
            return SettleStatus(INVALID, reason=self._reason)
        stable_since = self._stable_since
        duration = max(0.0, now - stable_since) if stable_since is not None else 0.0
        if self._stable_since is not None and duration >= self.stable_duration:
            return SettleStatus(SETTLED, duration, "odometry stable window satisfied")
        if now - self._started_at >= self.timeout:
            return SettleStatus(TIMEOUT, duration, "stable window did not complete before timeout")
        return SettleStatus(STABILIZING, duration, self._reason)
