"""Pure fail-safe command state machine for the MK-mini VCU backend."""

from dataclasses import dataclass
from enum import IntEnum
import math


class Gear(IntEnum):
    DISABLE = 0
    PARK = 1
    P = 1
    REVERSE = 2
    R = 2
    NEUTRAL = 3
    N = 3
    DRIVE = 4
    D = 4


@dataclass(frozen=True)
class CommandOutput:
    gear: Gear
    speed_mps: float
    steering_deg: float
    reason: str


class CommandStateMachine:
    """Convert signed motion intent into conservative VCU gear/speed commands.

    Direction changes and startup motion require fresh feedback proving standstill.
    A stale command first requests zero speed in the existing motion gear; PARK is
    selected only after fresh feedback has proved standstill for park_hold_sec.
    """

    def __init__(
        self,
        *,
        command_timeout: float,
        feedback_timeout: float,
        speed_deadband: float,
        shift_speed_threshold: float,
        gear_shift_hold_sec: float,
        park_hold_sec: float,
    ) -> None:
        values = {
            "command_timeout": command_timeout,
            "feedback_timeout": feedback_timeout,
            "speed_deadband": speed_deadband,
            "shift_speed_threshold": shift_speed_threshold,
            "gear_shift_hold_sec": gear_shift_hold_sec,
            "park_hold_sec": park_hold_sec,
        }
        for name, value in values.items():
            if not math.isfinite(float(value)) or float(value) < 0.0:
                raise ValueError(f"{name} must be finite and non-negative")
        if command_timeout <= 0.0 or feedback_timeout <= 0.0:
            raise ValueError("timeouts must be positive")

        self.command_timeout = float(command_timeout)
        self.feedback_timeout = float(feedback_timeout)
        self.speed_deadband = float(speed_deadband)
        self.shift_speed_threshold = float(shift_speed_threshold)
        self.gear_shift_hold_sec = float(gear_shift_hold_sec)
        self.park_hold_sec = float(park_hold_sec)

        self._gear = Gear.PARK
        self._command_speed = 0.0
        self._command_steering = 0.0
        self._command_stamp = float("-inf")
        self._feedback_speed = 0.0
        self._feedback_stamp = float("-inf")
        self._shift_target = None
        self._shift_stationary_since = None
        self._park_stationary_since = None

    @property
    def gear(self) -> Gear:
        return self._gear

    def update_command(self, *, speed_mps: float, steering_deg: float, stamp: float) -> None:
        speed = float(speed_mps)
        steering = float(steering_deg)
        timestamp = float(stamp)
        if not all(math.isfinite(v) for v in (speed, steering, timestamp)):
            raise ValueError("command values must be finite")
        self._command_speed = speed
        self._command_steering = steering
        self._command_stamp = timestamp

    def update_feedback(self, *, speed_mps: float, stamp: float) -> None:
        speed = float(speed_mps)
        timestamp = float(stamp)
        if not all(math.isfinite(v) for v in (speed, timestamp)):
            raise ValueError("feedback values must be finite")
        self._feedback_speed = speed
        self._feedback_stamp = timestamp

    def _command_fresh(self, now: float) -> bool:
        age = now - self._command_stamp
        return 0.0 <= age <= self.command_timeout

    def _feedback_fresh(self, now: float) -> bool:
        age = now - self._feedback_stamp
        return 0.0 <= age <= self.feedback_timeout

    def _stationary(self) -> bool:
        return abs(self._feedback_speed) <= self.shift_speed_threshold

    def _motion_gear_for_command(self) -> Gear | None:
        if self._command_speed > self.speed_deadband:
            return Gear.DRIVE
        if self._command_speed < -self.speed_deadband:
            return Gear.REVERSE
        return None

    def _zero_output(self, steering: float, reason: str) -> CommandOutput:
        return CommandOutput(
            gear=self._gear,
            speed_mps=0.0,
            steering_deg=float(steering),
            reason=reason,
        )

    def _step_stale_command(self, now: float, feedback_fresh: bool) -> CommandOutput:
        self._shift_target = None
        self._shift_stationary_since = None
        held_steering = (
            self._command_steering
            if self._gear in (Gear.DRIVE, Gear.REVERSE)
            else 0.0
        )

        if not feedback_fresh:
            self._park_stationary_since = None
            return self._zero_output(held_steering, "command_stale+feedback_stale")

        if not self._stationary():
            self._park_stationary_since = None
            return self._zero_output(held_steering, "command_stale+decelerating")

        if self._park_stationary_since is None:
            self._park_stationary_since = now
        if now - self._park_stationary_since >= self.park_hold_sec:
            self._gear = Gear.PARK
            self._park_stationary_since = None
            return self._zero_output(0.0, "command_stale+parked")
        return self._zero_output(held_steering, "command_stale+park_wait")

    def _step_shift(self, desired_gear: Gear, now: float) -> CommandOutput:
        if self._shift_target != desired_gear:
            self._shift_target = desired_gear
            self._shift_stationary_since = now
        elif self._shift_stationary_since is None:
            self._shift_stationary_since = now

        if now - self._shift_stationary_since >= self.gear_shift_hold_sec:
            self._gear = desired_gear
            self._shift_target = None
            self._shift_stationary_since = None
            return self._zero_output(self._command_steering, "gear_shifted")
        return self._zero_output(self._command_steering, "gear_shift_wait")

    def step(self, now: float) -> CommandOutput:
        now = float(now)
        if not math.isfinite(now):
            raise ValueError("now must be finite")

        command_fresh = self._command_fresh(now)
        feedback_fresh = self._feedback_fresh(now)

        if not command_fresh:
            return self._step_stale_command(now, feedback_fresh)

        # A fresh command cancels a timeout-driven park sequence.
        self._park_stationary_since = None
        desired_gear = self._motion_gear_for_command()

        if desired_gear is None:
            self._shift_target = None
            self._shift_stationary_since = None
            return self._zero_output(self._command_steering, "fresh_zero")

        if not feedback_fresh:
            self._shift_target = None
            self._shift_stationary_since = None
            return self._zero_output(self._command_steering, "feedback_stale")

        if desired_gear != self._gear:
            if not self._stationary():
                self._shift_target = None
                self._shift_stationary_since = None
                return self._zero_output(self._command_steering, "direction_change_wait_stop")
            return self._step_shift(desired_gear, now)

        self._shift_target = None
        self._shift_stationary_since = None
        return CommandOutput(
            gear=self._gear,
            speed_mps=abs(self._command_speed),
            steering_deg=self._command_steering,
            reason="command_active",
        )
