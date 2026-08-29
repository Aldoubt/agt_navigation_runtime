import importlib.util
from pathlib import Path
import sys


SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "p1_09a_collision_monitor_gate.py"
SPEC = importlib.util.spec_from_file_location("p1_09a_collision_monitor_gate", SCRIPT)
GATE = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = GATE
SPEC.loader.exec_module(GATE)


def _metrics(
    *,
    obstacle_points=1,
    raw_max_linear=0.2,
    filtered_max_linear=0.0,
    safety_max_linear=0.0,
    odom_displacement=0.0,
    raw_count=8,
    filtered_count=5,
    safety_count=5,
    odom_count=12,
):
    metrics = GATE.GateMetrics()
    metrics.obstacle_messages = 1 if obstacle_points > 0 else 0
    metrics.obstacle_points = obstacle_points
    metrics.raw.count = raw_count
    metrics.raw.max_linear_x = raw_max_linear
    metrics.raw.max_angular_z = 0.0
    metrics.filtered_after_settle.count = filtered_count
    metrics.filtered_after_settle.max_linear_x = filtered_max_linear
    metrics.filtered_after_settle.max_angular_z = 0.0
    metrics.safety_after_settle.count = safety_count
    metrics.safety_after_settle.max_linear_x = safety_max_linear
    metrics.safety_after_settle.max_angular_z = 0.0
    metrics.odom_messages = odom_count
    metrics.odom_displacement_m = odom_displacement
    return metrics


def test_gate_passes_on_obstacle_raw_command_and_stop():
    outcome = GATE.evaluate_gate(_metrics(), GATE.GateThresholds())
    assert outcome.passed
    assert outcome.obstacle_present
    assert outcome.raw_command
    assert outcome.collision_stop
    assert outcome.safety_stop
    assert outcome.odom_stop


def test_gate_fails_when_filtered_velocity_is_not_stopped():
    outcome = GATE.evaluate_gate(
        _metrics(filtered_max_linear=0.11),
        GATE.GateThresholds(),
    )
    assert not outcome.passed
    assert not outcome.collision_stop
    assert outcome.raw_command
    assert outcome.obstacle_present


def test_gate_fails_when_obstacle_cloud_is_empty():
    outcome = GATE.evaluate_gate(
        _metrics(obstacle_points=0),
        GATE.GateThresholds(),
    )
    assert not outcome.passed
    assert not outcome.obstacle_present


def test_gate_fails_when_raw_command_stays_zero():
    outcome = GATE.evaluate_gate(
        _metrics(raw_max_linear=0.0),
        GATE.GateThresholds(),
    )
    assert not outcome.passed
    assert not outcome.raw_command
