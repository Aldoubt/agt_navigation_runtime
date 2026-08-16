import math

from agt_chassis_mk_mini.ackermann_math import twist_to_ackermann


def test_bicycle_conversion_and_radius_clamp():
    wheelbase = 0.600
    minimum_radius = 1.500

    nominal = twist_to_ackermann(0.5, 0.2, wheelbase, minimum_radius)
    assert math.isclose(
        nominal.steering_angle_rad,
        math.atan(wheelbase * 0.2 / 0.5),
    )

    clamped = twist_to_ackermann(0.2, 10.0, wheelbase, minimum_radius)
    assert math.isclose(
        clamped.steering_angle_rad,
        math.atan(wheelbase / minimum_radius),
    )


def test_reverse_and_zero_speed_behavior():
    reverse = twist_to_ackermann(-0.4, 0.2, 0.600, 1.500)
    assert reverse.speed_mps == -0.4
    assert reverse.steering_angle_rad < 0.0

    stopped = twist_to_ackermann(0.0, 0.5, 0.600, 1.500)
    assert stopped.speed_mps == 0.0
    assert stopped.steering_angle_rad == 0.0


def test_non_finite_input_fails_closed():
    invalid = twist_to_ackermann(float("nan"), 0.2, 0.600, 1.500)
    assert invalid.speed_mps == 0.0
    assert invalid.steering_angle_rad == 0.0
