"""Deterministic minimal MK-mini VCU state model for virtual-CAN HIL."""

from dataclasses import dataclass
import math

from agt_chassis_mk_mini.mk_mini_protocol import Gear
from .vcu_protocol import CtrlCommand


@dataclass(frozen=True)
class VcuFaultConfig:
    drop_feedback: bool = False
    corrupt_bcc: bool = False


@dataclass(frozen=True)
class VcuState:
    gear: Gear
    speed_mps: float
    steering_deg: float
    left_wheel_speed_mps: float
    right_wheel_speed_mps: float
    left_pulse_count: int
    right_pulse_count: int
    battery_voltage_v: float
    battery_current_a: float
    remaining_capacity_ah: float
    mode: int


class VcuModel:
    def __init__(
        self,
        *,
        max_accel_mps2: float = 1.0,
        max_decel_mps2: float = 2.0,
        stationary_threshold_mps: float = 0.01,
        wheel_diameter_m: float = 0.24,
        encoder_pulses_per_rev: int = 4096,
        battery_voltage_v: float = 48.0,
        remaining_capacity_ah: float = 20.0,
        mode: int = 0,
        faults: VcuFaultConfig | None = None,
    ) -> None:
        positive = {
            "max_accel_mps2": max_accel_mps2,
            "max_decel_mps2": max_decel_mps2,
            "wheel_diameter_m": wheel_diameter_m,
        }
        for name, value in positive.items():
            if not math.isfinite(float(value)) or float(value) <= 0.0:
                raise ValueError(f"{name} must be finite and positive")
        if not math.isfinite(float(stationary_threshold_mps)) or stationary_threshold_mps < 0.0:
            raise ValueError("stationary_threshold_mps must be finite and non-negative")
        if int(encoder_pulses_per_rev) <= 0:
            raise ValueError("encoder_pulses_per_rev must be positive")
        if not 0 <= int(mode) <= 3:
            raise ValueError("mode must fit the protocol field")

        self.max_accel_mps2 = float(max_accel_mps2)
        self.max_decel_mps2 = float(max_decel_mps2)
        self.stationary_threshold_mps = float(stationary_threshold_mps)
        self.wheel_diameter_m = float(wheel_diameter_m)
        self.encoder_pulses_per_rev = int(encoder_pulses_per_rev)
        self.battery_voltage_v = float(battery_voltage_v)
        self.remaining_capacity_ah = float(remaining_capacity_ah)
        self.mode = int(mode)
        self.faults = faults if faults is not None else VcuFaultConfig()

        self._gear = Gear.PARK
        self._speed_mps = 0.0
        self._steering_deg = 0.0
        self._left_pulses = 0.0
        self._right_pulses = 0.0

    @staticmethod
    def _approach(current: float, target: float, max_delta: float) -> float:
        if target > current:
            return min(target, current + max_delta)
        if target < current:
            return max(target, current - max_delta)
        return current

    def _signed_target(self, command: CtrlCommand) -> float:
        if self._gear == Gear.DRIVE and command.gear == Gear.DRIVE:
            return abs(command.speed_mps)
        if self._gear == Gear.REVERSE and command.gear == Gear.REVERSE:
            return -abs(command.speed_mps)
        return 0.0

    def step(self, command: CtrlCommand, dt: float) -> VcuState:
        dt = float(dt)
        if not math.isfinite(dt) or dt <= 0.0:
            raise ValueError("dt must be finite and positive")

        previous_gear = self._gear
        requested_gear = Gear(command.gear)
        moving = abs(self._speed_mps) > self.stationary_threshold_mps
        direction_change = (
            previous_gear in (Gear.DRIVE, Gear.REVERSE)
            and requested_gear in (Gear.DRIVE, Gear.REVERSE)
            and requested_gear != previous_gear
        )

        shifted_direction = False
        if requested_gear != self._gear and not moving:
            self._gear = requested_gear
            shifted_direction = direction_change

        target_speed = 0.0 if shifted_direction else self._signed_target(command)
        if requested_gear != self._gear:
            target_speed = 0.0

        same_direction_accel = (
            self._speed_mps == 0.0
            or target_speed == 0.0
            or math.copysign(1.0, self._speed_mps) == math.copysign(1.0, target_speed)
        )
        increasing_magnitude = abs(target_speed) > abs(self._speed_mps) and same_direction_accel
        limit = self.max_accel_mps2 if increasing_magnitude else self.max_decel_mps2
        self._speed_mps = self._approach(self._speed_mps, target_speed, limit * dt)
        if abs(self._speed_mps) < 1e-12:
            self._speed_mps = 0.0

        self._steering_deg = float(command.steering_deg)
        circumference = math.pi * self.wheel_diameter_m
        pulse_delta = (
            self._speed_mps * dt / circumference * self.encoder_pulses_per_rev
        )
        self._left_pulses += pulse_delta
        self._right_pulses += pulse_delta

        current_a = -abs(self._speed_mps) * 8.0
        return VcuState(
            gear=self._gear,
            speed_mps=self._speed_mps,
            steering_deg=self._steering_deg,
            left_wheel_speed_mps=self._speed_mps,
            right_wheel_speed_mps=self._speed_mps,
            left_pulse_count=int(round(self._left_pulses)),
            right_pulse_count=int(round(self._right_pulses)),
            battery_voltage_v=self.battery_voltage_v,
            battery_current_a=current_a,
            remaining_capacity_ah=self.remaining_capacity_ah,
            mode=self.mode,
        )
