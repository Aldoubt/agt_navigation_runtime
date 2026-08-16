import math
from typing import NamedTuple


class AckermannSetpoint(NamedTuple):
    speed_mps: float
    steering_angle_rad: float


def twist_to_ackermann(
    linear_velocity: float,
    yaw_rate: float,
    wheelbase: float,
    min_turning_radius: float,
    *,
    speed_deadband: float = 0.01,
) -> AckermannSetpoint:
    """Convert planar Twist semantics into an equivalent bicycle setpoint.

    `min_turning_radius` is the vehicle-level kinematic constraint. It is
    intentionally independent from any VCU steering field semantics.
    """
    if wheelbase <= 0.0:
        raise ValueError("wheelbase must be positive")
    if min_turning_radius <= 0.0:
        raise ValueError("min_turning_radius must be positive")
    if speed_deadband < 0.0:
        raise ValueError("speed_deadband must be non-negative")
    if not math.isfinite(linear_velocity) or not math.isfinite(yaw_rate):
        return AckermannSetpoint(0.0, 0.0)
    if abs(linear_velocity) < speed_deadband:
        return AckermannSetpoint(0.0, 0.0)

    curvature = yaw_rate / linear_velocity
    max_curvature = 1.0 / min_turning_radius
    curvature = min(max(curvature, -max_curvature), max_curvature)
    steering = math.atan(wheelbase * curvature)
    return AckermannSetpoint(float(linear_velocity), float(steering))
