"""Pure MK-mini CAN protocol codec.

This module deliberately contains no ROS or socket imports. Logical CAN IDs stay
as 29-bit manufacturer IDs; Linux CAN_EFF_FLAG belongs to the SocketCAN boundary.
"""

from dataclasses import dataclass
from enum import IntEnum
import math
from typing import Iterable


CTRL_CMD_ID = 0x18C4D2D0
CTRL_FB_ID = 0x18C4D2EF
LEFT_REAR_WHEEL_FB_ID = 0x18C4D7EF
RIGHT_REAR_WHEEL_FB_ID = 0x18C4D8EF
ODOMETER_FB_ID = 0x18C4DEEF
BMS_INFO_FB_ID = 0x18C4E1EF
BMS_FLAG_FB_ID = 0x18C4E2EF
VEHICLE_DIAG_FB_ID = 0x18C4EAEF

FRAME_SIZE = 8
VELOCITY_RESOLUTION_MPS = 0.001
STEERING_RESOLUTION_DEG = 0.01


class ProtocolError(ValueError):
    """Raised when an MK-mini frame violates the protocol contract."""


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
class CtrlFeedback:
    gear: Gear
    speed_mps: float
    steering_deg: float
    mode: int
    alive_counter: int


@dataclass(frozen=True)
class WheelFeedback:
    speed_mps: float
    pulse_count: int
    alive_counter: int


@dataclass(frozen=True)
class BmsInfo:
    voltage_v: float
    current_a: float
    remaining_capacity_ah: float
    alive_counter: int


@dataclass(frozen=True)
class OdometerFeedback:
    distance_m: float


def compute_bcc(values: Iterable[int]) -> int:
    checksum = 0
    for value in values:
        checksum ^= int(value) & 0xFF
    return checksum


def next_alive_counter(current: int) -> int:
    if not 0 <= int(current) <= 15:
        raise ProtocolError("AliveCounter must be in range 0..15")
    return (int(current) + 1) & 0x0F


def _require_finite(name: str, value: float) -> float:
    value = float(value)
    if not math.isfinite(value):
        raise ProtocolError(f"{name} must be finite")
    return value


def _require_payload(payload: bytes, *, verify_bcc: bool = True) -> bytes:
    data = bytes(payload)
    if len(data) != FRAME_SIZE:
        raise ProtocolError(f"expected {FRAME_SIZE}-byte frame, got {len(data)}")
    if verify_bcc and compute_bcc(data[:7]) != data[7]:
        raise ProtocolError("BCC checksum mismatch")
    return data


def _decode_gear(raw: int) -> Gear:
    try:
        return Gear(raw & 0x0F)
    except ValueError as exc:
        raise ProtocolError(f"unsupported gear value {raw & 0x0F}") from exc


def encode_ctrl_command(
    *,
    gear: Gear,
    speed_mps: float,
    steering_deg: float,
    alive_counter: int,
) -> bytes:
    """Encode the manufacturer ctrl_cmd 8-byte payload.

    The speed field is unsigned. Reverse motion is represented by Gear.REVERSE.
    """

    try:
        gear_value = int(Gear(gear))
    except ValueError as exc:
        raise ProtocolError(f"unsupported gear value {gear}") from exc

    speed = _require_finite("speed_mps", speed_mps)
    steering = _require_finite("steering_deg", steering_deg)
    if speed < 0.0:
        raise ProtocolError("speed_mps must be non-negative at the CAN protocol layer")
    if not 0 <= int(alive_counter) <= 15:
        raise ProtocolError("AliveCounter must be in range 0..15")

    raw_speed = int(round(speed / VELOCITY_RESOLUTION_MPS))
    if not 0 <= raw_speed <= 0xFFFF:
        raise ProtocolError("speed_mps exceeds 16-bit protocol field")

    raw_steering = int(round(steering / STEERING_RESOLUTION_DEG))
    if not -0x8000 <= raw_steering <= 0x7FFF:
        raise ProtocolError("steering_deg exceeds signed 16-bit protocol field")
    steering_bits = raw_steering & 0xFFFF

    data = bytearray(FRAME_SIZE)
    data[0] = gear_value & 0x0F
    data[0] |= (raw_speed & 0x000F) << 4
    data[1] = (raw_speed >> 4) & 0xFF
    data[2] = (raw_speed >> 12) & 0x0F

    data[2] |= (steering_bits & 0x000F) << 4
    data[3] = (steering_bits >> 4) & 0xFF
    data[4] = (steering_bits >> 12) & 0x0F

    data[6] = (int(alive_counter) & 0x0F) << 4
    data[7] = compute_bcc(data[:7])
    return bytes(data)


def decode_ctrl_feedback(payload: bytes) -> CtrlFeedback:
    data = _require_payload(payload)
    gear = _decode_gear(data[0])
    raw_speed = (
        ((data[0] >> 4) & 0x0F)
        | (data[1] << 4)
        | ((data[2] & 0x0F) << 12)
    )
    steering_bits = (
        ((data[2] >> 4) & 0x0F)
        | (data[3] << 4)
        | ((data[4] & 0x0F) << 12)
    )
    raw_steering = (
        steering_bits - 0x10000 if steering_bits & 0x8000 else steering_bits
    )
    return CtrlFeedback(
        gear=gear,
        speed_mps=raw_speed * VELOCITY_RESOLUTION_MPS,
        steering_deg=raw_steering * STEERING_RESOLUTION_DEG,
        mode=(data[5] >> 4) & 0x03,
        alive_counter=(data[6] >> 4) & 0x0F,
    )


def decode_wheel_feedback(payload: bytes) -> WheelFeedback:
    data = _require_payload(payload)
    raw_speed = int.from_bytes(data[0:2], byteorder="little", signed=True)
    pulse_count = int.from_bytes(data[2:6], byteorder="little", signed=True)
    return WheelFeedback(
        speed_mps=raw_speed * VELOCITY_RESOLUTION_MPS,
        pulse_count=pulse_count,
        alive_counter=(data[6] >> 4) & 0x0F,
    )


def decode_bms_info(payload: bytes) -> BmsInfo:
    data = _require_payload(payload)
    raw_voltage = int.from_bytes(data[0:2], byteorder="little", signed=False)
    raw_current = int.from_bytes(data[2:4], byteorder="little", signed=True)
    raw_capacity = int.from_bytes(data[4:6], byteorder="little", signed=False)
    return BmsInfo(
        voltage_v=raw_voltage * 0.01,
        current_a=raw_current * 0.01,
        remaining_capacity_ah=raw_capacity * 0.01,
        alive_counter=(data[6] >> 4) & 0x0F,
    )


def decode_odometer_feedback(payload: bytes) -> OdometerFeedback:
    data = _require_payload(payload, verify_bcc=False)
    raw_distance = int.from_bytes(data[0:4], byteorder="little", signed=True)
    return OdometerFeedback(distance_m=raw_distance * 0.001)
