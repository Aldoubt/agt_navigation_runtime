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
    / "mk_mini_command_state.py"
)


def load_state():
    spec = importlib.util.spec_from_file_location("mk_mini_command_state", MODULE_PATH)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def machine(module):
    return module.CommandStateMachine(
        command_timeout=0.20,
        feedback_timeout=0.20,
        speed_deadband=0.01,
        shift_speed_threshold=0.05,
        gear_shift_hold_sec=0.05,
        park_hold_sec=0.20,
    )


def establish_drive(module, m):
    m.update_feedback(speed_mps=0.0, stamp=0.00)
    m.update_command(speed_mps=0.5, steering_deg=5.0, stamp=0.00)
    first = m.step(0.00)
    assert first.speed_mps == 0.0
    assert first.gear == module.Gear.PARK
    m.update_feedback(speed_mps=0.0, stamp=0.06)
    second = m.step(0.06)
    assert second.gear == module.Gear.DRIVE
    assert second.speed_mps == 0.0
    third = m.step(0.07)
    assert third.gear == module.Gear.DRIVE
    assert third.speed_mps == pytest.approx(0.5)


def test_positive_speed_requires_fresh_stationary_feedback_before_drive_engages():
    s = load_state()
    m = machine(s)
    m.update_command(speed_mps=0.5, steering_deg=0.0, stamp=0.0)
    no_feedback = m.step(0.0)
    assert no_feedback.gear == s.Gear.PARK
    assert no_feedback.speed_mps == 0.0

    m.update_feedback(speed_mps=0.0, stamp=0.0)
    waiting = m.step(0.0)
    assert waiting.gear == s.Gear.PARK
    assert waiting.speed_mps == 0.0

    m.update_feedback(speed_mps=0.0, stamp=0.06)
    shifted = m.step(0.06)
    assert shifted.gear == s.Gear.DRIVE
    assert shifted.speed_mps == 0.0
    moving = m.step(0.07)
    assert moving.speed_mps == pytest.approx(0.5)


def test_negative_speed_selects_reverse_with_unsigned_can_speed_magnitude():
    s = load_state()
    m = machine(s)
    m.update_feedback(speed_mps=0.0, stamp=0.0)
    m.update_command(speed_mps=-0.4, steering_deg=-3.0, stamp=0.0)
    m.step(0.0)
    m.update_feedback(speed_mps=0.0, stamp=0.06)
    shifted = m.step(0.06)
    assert shifted.gear == s.Gear.REVERSE
    moving = m.step(0.07)
    assert moving.gear == s.Gear.REVERSE
    assert moving.speed_mps == pytest.approx(0.4)
    assert moving.steering_deg == pytest.approx(-3.0)


def test_fresh_zero_command_retains_current_motion_gear():
    s = load_state()
    m = machine(s)
    establish_drive(s, m)
    m.update_feedback(speed_mps=0.0, stamp=0.08)
    m.update_command(speed_mps=0.0, steering_deg=0.0, stamp=0.08)
    out = m.step(0.08)
    assert out.gear == s.Gear.DRIVE
    assert out.speed_mps == 0.0


def test_drive_to_reverse_is_blocked_until_fresh_feedback_proves_standstill():
    s = load_state()
    m = machine(s)
    establish_drive(s, m)

    m.update_feedback(speed_mps=0.3, stamp=0.08)
    m.update_command(speed_mps=-0.4, steering_deg=-6.0, stamp=0.08)
    blocked = m.step(0.08)
    assert blocked.gear == s.Gear.DRIVE
    assert blocked.speed_mps == 0.0

    m.update_feedback(speed_mps=0.0, stamp=0.10)
    waiting = m.step(0.10)
    assert waiting.gear == s.Gear.DRIVE
    m.update_feedback(speed_mps=0.0, stamp=0.16)
    shifted = m.step(0.16)
    assert shifted.gear == s.Gear.REVERSE
    assert shifted.speed_mps == 0.0
    moving = m.step(0.17)
    assert moving.speed_mps == pytest.approx(0.4)


def test_feedback_timeout_forces_zero_speed_without_blind_gear_change():
    s = load_state()
    m = machine(s)
    establish_drive(s, m)
    m.update_command(speed_mps=0.5, steering_deg=4.0, stamp=0.18)
    out = m.step(0.31)  # latest feedback was 0.06: stale
    assert out.gear == s.Gear.DRIVE
    assert out.speed_mps == 0.0
    assert out.steering_deg == pytest.approx(4.0)
    assert "feedback_stale" in out.reason


def test_command_timeout_holds_steering_while_decelerating_then_parks_when_stopped():
    s = load_state()
    m = machine(s)
    establish_drive(s, m)

    m.update_feedback(speed_mps=0.25, stamp=0.28)
    stale_moving = m.step(0.28)  # command stamp 0.00 is stale
    assert stale_moving.gear == s.Gear.DRIVE
    assert stale_moving.speed_mps == 0.0
    assert stale_moving.steering_deg == pytest.approx(5.0)

    m.update_feedback(speed_mps=0.0, stamp=0.30)
    waiting = m.step(0.30)
    assert waiting.gear == s.Gear.DRIVE
    m.update_feedback(speed_mps=0.0, stamp=0.51)
    parked = m.step(0.51)
    assert parked.gear == s.Gear.PARK
    assert parked.speed_mps == 0.0
    assert parked.steering_deg == 0.0
