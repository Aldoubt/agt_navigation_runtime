import importlib.util
from pathlib import Path
import sys

import pytest


ROOT = Path(__file__).resolve().parents[2]
MODULE_PATH = (
    ROOT
    / "src"
    / "agt_chassis_mk_mini"
    / "agt_chassis_mk_mini"
    / "mk_mini_protocol.py"
)


def load_protocol():
    spec = importlib.util.spec_from_file_location("mk_mini_protocol", MODULE_PATH)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def test_manual_vector_d_gear_zero_speed_counter_1():
    p = load_protocol()
    payload = p.encode_ctrl_command(
        gear=p.Gear.D,
        speed_mps=0.0,
        steering_deg=0.0,
        alive_counter=1,
    )
    assert payload == bytes.fromhex("04 00 00 00 00 00 10 14")


def test_manual_vector_d_gear_one_meter_per_second_counter_0():
    p = load_protocol()
    payload = p.encode_ctrl_command(
        gear=p.Gear.D,
        speed_mps=1.0,
        steering_deg=0.0,
        alive_counter=0,
    )
    assert payload == bytes.fromhex("84 3E 00 00 00 00 00 BA")


def test_manual_vector_negative_25_degree_steering():
    p = load_protocol()
    payload = p.encode_ctrl_command(
        gear=p.Gear.DISABLE,
        speed_mps=0.0,
        steering_deg=-25.0,
        alive_counter=0,
    )
    assert payload == bytes.fromhex("00 00 C0 63 0F 00 00 AC")


def test_ctrl_feedback_decodes_signed_fields_mode_counter_and_checksum():
    p = load_protocol()
    payload = bytes.fromhex("84 3E C0 63 0F 00 A0 1A")
    # Replace checksum with the codec-computed value to focus this test on decode.
    payload = payload[:7] + bytes([p.compute_bcc(payload[:7])])
    fb = p.decode_ctrl_feedback(payload)
    assert fb.gear == p.Gear.D
    assert fb.speed_mps == pytest.approx(1.0)
    assert fb.steering_deg == pytest.approx(-25.0)
    assert fb.mode == 0
    assert fb.alive_counter == 10


def test_invalid_bcc_is_rejected():
    p = load_protocol()
    payload = bytes.fromhex("84 3E 00 00 00 00 00 00")
    with pytest.raises(p.ProtocolError, match="BCC"):
        p.decode_ctrl_feedback(payload)


def test_wheel_feedback_decodes_signed_velocity_and_pulse_count():
    p = load_protocol()
    payload = bytes.fromhex("0C FE C7 CF FF FF A0 5A")
    fb = p.decode_wheel_feedback(payload)
    assert fb.speed_mps == pytest.approx(-0.5)
    assert fb.pulse_count == -12345
    assert fb.alive_counter == 10


def test_bms_feedback_decodes_voltage_current_capacity():
    p = load_protocol()
    data = bytearray(8)
    data[0:2] = (5123).to_bytes(2, "little", signed=False)  # 51.23 V
    data[2:4] = (-456).to_bytes(2, "little", signed=True)  # -4.56 A
    data[4:6] = (987).to_bytes(2, "little", signed=False)  # 9.87 Ah
    data[6] = 0x70
    data[7] = p.compute_bcc(data[:7])
    fb = p.decode_bms_info(bytes(data))
    assert fb.voltage_v == pytest.approx(51.23)
    assert fb.current_a == pytest.approx(-4.56)
    assert fb.remaining_capacity_ah == pytest.approx(9.87)
    assert fb.alive_counter == 7


def test_alive_counter_wraps_0_through_15():
    p = load_protocol()
    assert p.next_alive_counter(0) == 1
    assert p.next_alive_counter(14) == 15
    assert p.next_alive_counter(15) == 0
