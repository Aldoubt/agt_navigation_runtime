import sys
from pathlib import Path

import pytest


ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "src" / "agt_chassis_mk_mini"))
sys.path.insert(0, str(ROOT / "src" / "agt_chassis_mk_mini_sim"))

from agt_chassis_mk_mini.mk_mini_protocol import (  # noqa: E402
    Gear,
    decode_bms_info,
    decode_ctrl_feedback,
    decode_wheel_feedback,
    encode_ctrl_command,
)
from agt_chassis_mk_mini_sim.vcu_protocol import (  # noqa: E402
    SimProtocolError,
    decode_ctrl_command,
    encode_bms_info,
    encode_ctrl_feedback,
    encode_wheel_feedback,
)


def test_command_decoder_matches_real_backend_golden_command_bytes():
    payload = encode_ctrl_command(
        gear=Gear.D,
        speed_mps=1.0,
        steering_deg=-12.34,
        alive_counter=7,
    )
    decoded = decode_ctrl_command(payload)
    assert decoded.gear == Gear.D
    assert decoded.speed_mps == pytest.approx(1.0)
    assert decoded.steering_deg == pytest.approx(-12.34)
    assert decoded.alive_counter == 7


def test_ctrl_feedback_is_independently_packable_and_real_decoder_accepts_it():
    payload = encode_ctrl_feedback(
        gear=Gear.R,
        speed_mps=0.321,
        steering_deg=8.75,
        mode=0,
        alive_counter=9,
    )
    decoded = decode_ctrl_feedback(payload)
    assert decoded.gear == Gear.R
    assert decoded.speed_mps == pytest.approx(0.321)
    assert decoded.steering_deg == pytest.approx(8.75)
    assert decoded.mode == 0
    assert decoded.alive_counter == 9


def test_wheel_feedback_is_independently_packable_and_real_decoder_accepts_it():
    payload = encode_wheel_feedback(
        speed_mps=-0.456,
        pulse_count=-123456,
        alive_counter=4,
    )
    decoded = decode_wheel_feedback(payload)
    assert decoded.speed_mps == pytest.approx(-0.456)
    assert decoded.pulse_count == -123456
    assert decoded.alive_counter == 4


def test_bms_feedback_is_independently_packable_and_real_decoder_accepts_it():
    payload = encode_bms_info(
        voltage_v=47.52,
        current_a=-3.25,
        remaining_capacity_ah=18.75,
        alive_counter=2,
    )
    decoded = decode_bms_info(payload)
    assert decoded.voltage_v == pytest.approx(47.52)
    assert decoded.current_a == pytest.approx(-3.25)
    assert decoded.remaining_capacity_ah == pytest.approx(18.75)
    assert decoded.alive_counter == 2


def test_command_decoder_rejects_bad_bcc():
    payload = bytearray(
        encode_ctrl_command(
            gear=Gear.D,
            speed_mps=0.1,
            steering_deg=0.0,
            alive_counter=1,
        )
    )
    payload[7] ^= 0x01
    with pytest.raises(SimProtocolError, match="BCC"):
        decode_ctrl_command(bytes(payload))
