import importlib.util
from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parents[2]
MODULE_PATH = (
    ROOT
    / "src"
    / "agt_chassis_mk_mini"
    / "agt_chassis_mk_mini"
    / "mk_mini_command_state.py"
)


def load_state():
    spec = importlib.util.spec_from_file_location("mk_mini_command_state_interlock", MODULE_PATH)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def test_nonzero_motion_requires_matching_vcu_gear_feedback():
    s = load_state()
    assert s.gear_feedback_allows_motion(s.Gear.DRIVE, s.Gear.DRIVE)
    assert s.gear_feedback_allows_motion(s.Gear.REVERSE, s.Gear.REVERSE)
    assert not s.gear_feedback_allows_motion(s.Gear.DRIVE, s.Gear.PARK)
    assert not s.gear_feedback_allows_motion(s.Gear.REVERSE, s.Gear.DRIVE)
    assert not s.gear_feedback_allows_motion(s.Gear.DRIVE, None)


def test_ros_backend_uses_gear_feedback_interlock_before_transmitting_speed():
    backend = (
        ROOT / "src" / "agt_chassis_mk_mini" / "scripts" / "mk_mini_can_backend.py"
    ).read_text(encoding="utf-8")
    assert "gear_feedback_allows_motion" in backend
    assert "gear_feedback_mismatch" in backend
