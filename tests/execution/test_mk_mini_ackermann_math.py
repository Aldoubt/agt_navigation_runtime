import importlib.util
import math
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
MODULE = ROOT / "src" / "agt_chassis_mk_mini" / "agt_chassis_mk_mini" / "ackermann_math.py"
SPEC = importlib.util.spec_from_file_location("ackermann_math", MODULE)
ACK = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(ACK)


WHEELBASE = 0.600
MIN_TURNING_RADIUS = 1.500
MAX_STEER = math.atan(WHEELBASE / MIN_TURNING_RADIUS)


def test_straight_forward_has_zero_steering():
    out = ACK.twist_to_ackermann(0.5, 0.0, WHEELBASE, MIN_TURNING_RADIUS)
    assert out.speed_mps == 0.5
    assert out.steering_angle_rad == 0.0


def test_forward_curvature_uses_bicycle_model():
    out = ACK.twist_to_ackermann(0.5, 0.2, WHEELBASE, MIN_TURNING_RADIUS)
    assert math.isclose(out.speed_mps, 0.5)
    assert math.isclose(out.steering_angle_rad, math.atan(WHEELBASE * 0.2 / 0.5))


def test_left_and_right_curvature_preserve_sign():
    left = ACK.twist_to_ackermann(0.4, 0.2, WHEELBASE, MIN_TURNING_RADIUS)
    right = ACK.twist_to_ackermann(0.4, -0.2, WHEELBASE, MIN_TURNING_RADIUS)
    assert left.steering_angle_rad > 0.0
    assert right.steering_angle_rad < 0.0
    assert math.isclose(left.steering_angle_rad, -right.steering_angle_rad)


def test_curvature_is_clamped_by_minimum_turning_radius():
    out = ACK.twist_to_ackermann(0.2, 10.0, WHEELBASE, MIN_TURNING_RADIUS)
    assert math.isclose(out.steering_angle_rad, MAX_STEER)


def test_reverse_uses_signed_longitudinal_speed():
    out = ACK.twist_to_ackermann(-0.4, 0.2, WHEELBASE, MIN_TURNING_RADIUS)
    assert out.speed_mps == -0.4
    assert out.steering_angle_rad < 0.0
    assert math.isclose(out.steering_angle_rad, math.atan(WHEELBASE * 0.2 / -0.4))


def test_zero_speed_yaw_request_fails_closed_instead_of_in_place_turning():
    out = ACK.twist_to_ackermann(0.0, 0.5, WHEELBASE, MIN_TURNING_RADIUS)
    assert out.speed_mps == 0.0
    assert out.steering_angle_rad == 0.0


def test_near_zero_speed_uses_configured_deadband():
    out = ACK.twist_to_ackermann(
        0.005, 0.5, WHEELBASE, MIN_TURNING_RADIUS, speed_deadband=0.01
    )
    assert out.speed_mps == 0.0
    assert out.steering_angle_rad == 0.0


def test_non_finite_input_fails_closed():
    out = ACK.twist_to_ackermann(float("nan"), 0.2, WHEELBASE, MIN_TURNING_RADIUS)
    assert out.speed_mps == 0.0
    assert out.steering_angle_rad == 0.0


def test_frozen_vehicle_profile_matches_adapter_reference_geometry():
    profile = (ROOT / "profiles" / "platforms" / "mk_mini.yaml").read_text(encoding="utf-8")
    assert "wheel_base: 0.600" in profile
    assert "track_width: 0.517" in profile
    assert "wheel_diameter: 0.240" in profile
    assert "ground_clearance: 0.111" in profile
    assert "min_turning_radius: 1.500" in profile
    assert "max_steering_angle_deg: 34.0" in profile
    assert "steering_angle_semantics: vcu_target_steering_soft_limit" in profile
