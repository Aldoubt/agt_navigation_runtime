"""Independent MK-mini VCU-side protocol packing for software HIL."""

from dataclasses import dataclass

from agt_chassis_mk_mini.mk_mini_protocol import (
    BMS_INFO_FB_ID,
    CTRL_CMD_ID,
    CTRL_FB_ID,
    LEFT_REAR_WHEEL_FB_ID,
    RIGHT_REAR_WHEEL_FB_ID,
    Gear,
)

FRAME_SIZE = 8
VELOCITY_RESOLUTION_MPS = 0.001
STEERING_RESOLUTION_DEG = 0.01


class SimProtocolError(ValueError):
    pass


@dataclass(frozen=True)
class CtrlCommand:
    gear: Gear
    speed_mps: float
    steering_deg: float
    alive_counter: int


def compute_bcc(data: bytes) -> int:
    checksum = 0
    for value in bytes(data):
        checksum ^= value
    return checksum


def _require_payload(payload: bytes) -> bytes:
    data = bytes(payload)
    if len(data) != FRAME_SIZE:
        raise SimProtocolError(f"expected {FRAME_SIZE} bytes, got {len(data)}")
    if compute_bcc(data[:7]) != data[7]:
        raise SimProtocolError("BCC checksum mismatch")
    return data


def _pack_bcc(data: bytearray) -> bytes:
    data[7] = compute_bcc(data[:7])
    return bytes(data)


def decode_ctrl_command(payload: bytes) -> CtrlCommand:
    data = _require_payload(payload)
    try:
        gear = Gear(data[0] & 0x0F)
    except ValueError as exc:
        raise SimProtocolError(f"unsupported gear value {data[0] & 0x0F}") from exc

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
    raw_steering = steering_bits - 0x10000 if steering_bits & 0x8000 else steering_bits
    return CtrlCommand(
        gear=gear,
        speed_mps=raw_speed * VELOCITY_RESOLUTION_MPS,
        steering_deg=raw_steering * STEERING_RESOLUTION_DEG,
        alive_counter=(data[6] >> 4) & 0x0F,
    )


def encode_ctrl_feedback(
    *,
    gear: Gear,
    speed_mps: float,
    steering_deg: float,
    mode: int,
    alive_counter: int,
) -> bytes:
    raw_speed = int(round(abs(float(speed_mps)) / VELOCITY_RESOLUTION_MPS))
    if not 0 <= raw_speed <= 0xFFFF:
        raise SimProtocolError("speed outside 16-bit field")
    raw_steering = int(round(float(steering_deg) / STEERING_RESOLUTION_DEG))
    if not -0x8000 <= raw_steering <= 0x7FFF:
        raise SimProtocolError("steering outside signed 16-bit field")
    if not 0 <= int(mode) <= 3:
        raise SimProtocolError("mode outside 2-bit field")
    if not 0 <= int(alive_counter) <= 15:
        raise SimProtocolError("alive counter outside 0..15")

    steering_bits = raw_steering & 0xFFFF
    data = bytearray(FRAME_SIZE)
    data[0] = int(Gear(gear)) & 0x0F
    data[0] |= (raw_speed & 0x0F) << 4
    data[1] = (raw_speed >> 4) & 0xFF
    data[2] = (raw_speed >> 12) & 0x0F
    data[2] |= (steering_bits & 0x0F) << 4
    data[3] = (steering_bits >> 4) & 0xFF
    data[4] = (steering_bits >> 12) & 0x0F
    data[5] = (int(mode) & 0x03) << 4
    data[6] = (int(alive_counter) & 0x0F) << 4
    return _pack_bcc(data)


def encode_wheel_feedback(
    *, speed_mps: float, pulse_count: int, alive_counter: int
) -> bytes:
    raw_speed = int(round(float(speed_mps) / VELOCITY_RESOLUTION_MPS))
    if not -0x8000 <= raw_speed <= 0x7FFF:
        raise SimProtocolError("wheel speed outside signed 16-bit field")
    if not -0x80000000 <= int(pulse_count) <= 0x7FFFFFFF:
        raise SimProtocolError("pulse count outside signed 32-bit field")
    if not 0 <= int(alive_counter) <= 15:
        raise SimProtocolError("alive counter outside 0..15")

    data = bytearray(FRAME_SIZE)
    data[0:2] = int(raw_speed).to_bytes(2, "little", signed=True)
    data[2:6] = int(pulse_count).to_bytes(4, "little", signed=True)
    data[6] = (int(alive_counter) & 0x0F) << 4
    return _pack_bcc(data)


def encode_bms_info(
    *, voltage_v: float, current_a: float, remaining_capacity_ah: float, alive_counter: int
) -> bytes:
    raw_voltage = int(round(float(voltage_v) / 0.01))
    raw_current = int(round(float(current_a) / 0.01))
    raw_capacity = int(round(float(remaining_capacity_ah) / 0.01))
    if not 0 <= raw_voltage <= 0xFFFF:
        raise SimProtocolError("voltage outside uint16 field")
    if not -0x8000 <= raw_current <= 0x7FFF:
        raise SimProtocolError("current outside int16 field")
    if not 0 <= raw_capacity <= 0xFFFF:
        raise SimProtocolError("capacity outside uint16 field")
    if not 0 <= int(alive_counter) <= 15:
        raise SimProtocolError("alive counter outside 0..15")

    data = bytearray(FRAME_SIZE)
    data[0:2] = raw_voltage.to_bytes(2, "little", signed=False)
    data[2:4] = raw_current.to_bytes(2, "little", signed=True)
    data[4:6] = raw_capacity.to_bytes(2, "little", signed=False)
    data[6] = (int(alive_counter) & 0x0F) << 4
    return _pack_bcc(data)
