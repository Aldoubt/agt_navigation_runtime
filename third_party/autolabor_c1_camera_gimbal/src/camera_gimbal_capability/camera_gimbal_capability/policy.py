import math
import re
from typing import List


def stamp_to_ns(sec: int, nanosec: int) -> int:
    return int(sec) * 1_000_000_000 + int(nanosec)


def is_strictly_fresh(sec: int, nanosec: int, threshold_ns: int) -> bool:
    return stamp_to_ns(sec, nanosec) > int(threshold_ns)


def sanitize_tag(tag: str) -> str:
    raw = (tag or '').strip()
    value = ''.join(ch if ch.isalnum() or ch in '._-' else '_' for ch in raw)
    value = re.sub(r'_+', '_', value).strip('._-')
    return (value or 'capture')[:64]


def validate_acquire_goal(
    *,
    heading: float,
    roll: float,
    pitch: float,
    tolerance: float,
    timeout: float,
    settle_time: float,
    image_timeout: float,
    max_tolerance: float,
) -> List[str]:
    errors: List[str] = []
    finite_angles = all(math.isfinite(v) for v in (heading, roll, pitch))
    if not finite_angles:
        errors.append('angles must be finite')
    elif not (-160.0 <= heading <= 160.0 and -40.0 <= roll <= 40.0 and -90.0 <= pitch <= 90.0):
        errors.append('angles exceed mechanical limits H[-160,160] R[-40,40] P[-90,90]')
    if not math.isfinite(tolerance) or tolerance <= 0.0 or tolerance > max_tolerance:
        errors.append(f'tolerance must be within (0, {max_tolerance}]')
    if not math.isfinite(timeout) or timeout <= 0.0:
        errors.append('timeout must be > 0')
    if not math.isfinite(settle_time) or settle_time < 0.0:
        errors.append('settle_time must be >= 0')
    if not math.isfinite(image_timeout) or image_timeout <= 0.0:
        errors.append('image_timeout must be > 0')
    return errors


def resolve_positive_or_default(value: float, default: float) -> float:
    """Use configured default only for the explicit sentinel 0; preserve invalid negatives/NaN for validation."""
    return float(default) if value == 0.0 else float(value)
