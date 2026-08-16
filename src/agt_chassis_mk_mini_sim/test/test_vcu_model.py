import math
import sys
from pathlib import Path

import pytest


ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "src" / "agt_chassis_mk_mini"))
sys.path.insert(0, str(ROOT / "src" / "agt_chassis_mk_mini_sim"))

from agt_chassis_mk_mini.mk_mini_protocol import Gear  # noqa: E402
from agt_chassis_mk_mini_sim.vcu_protocol import CtrlCommand  # noqa: E402
from agt_chassis_mk_mini_sim.vcu_model import (  # noqa: E402
    VcuFaultConfig,
    VcuModel,
)


def cmd(gear, speed, steering=0.0, counter=0):
    return CtrlCommand(gear=gear, speed_mps=speed, steering_deg=steering, alive_counter=counter)


def test_forward_speed_is_acceleration_limited():
    model = VcuModel(max_accel_mps2=1.0, max_decel_mps2=2.0)
    state = model.step(cmd(Gear.D, 1.0), 0.1)
    assert state.gear == Gear.D
    assert state.speed_mps == pytest.approx(0.1)
    state = model.step(cmd(Gear.D, 1.0), 0.1)
    assert state.speed_mps == pytest.approx(0.2)


def test_reverse_request_does_not_flip_gear_while_vehicle_is_moving():
    model = VcuModel(max_accel_mps2=2.0, max_decel_mps2=1.0)
    for _ in range(5):
        state = model.step(cmd(Gear.D, 1.0), 0.1)
    assert state.speed_mps > 0.0
    state = model.step(cmd(Gear.R, 0.5), 0.1)
    assert state.gear == Gear.D
    assert state.speed_mps >= 0.0
    assert state.speed_mps < 1.0


def test_reverse_is_confirmed_only_after_stationary_then_speed_becomes_negative():
    model = VcuModel(
        max_accel_mps2=2.0,
        max_decel_mps2=2.0,
        stationary_threshold_mps=0.01,
    )
    for _ in range(5):
        model.step(cmd(Gear.D, 0.5), 0.1)
    for _ in range(20):
        state = model.step(cmd(Gear.R, 0.5), 0.1)
        if state.gear == Gear.R:
            break
    assert state.gear == Gear.R
    assert abs(state.speed_mps) <= 0.01
    state = model.step(cmd(Gear.R, 0.5), 0.1)
    assert state.speed_mps < 0.0


def test_encoder_pulses_accumulate_from_wheel_distance():
    model = VcuModel(
        max_accel_mps2=100.0,
        max_decel_mps2=100.0,
        wheel_diameter_m=0.24,
        encoder_pulses_per_rev=4096,
    )
    state = model.step(cmd(Gear.D, 0.24 * math.pi), 1.0)
    assert state.left_pulse_count == pytest.approx(4096, abs=1)
    assert state.right_pulse_count == pytest.approx(4096, abs=1)


def test_fault_configuration_is_explicit_and_safe_by_default():
    faults = VcuFaultConfig()
    assert faults.drop_feedback is False
    assert faults.corrupt_bcc is False
    configured = VcuFaultConfig(drop_feedback=True, corrupt_bcc=True)
    assert configured.drop_feedback is True
    assert configured.corrupt_bcc is True
