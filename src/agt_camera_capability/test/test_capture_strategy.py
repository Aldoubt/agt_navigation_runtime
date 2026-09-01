import math

import pytest

from agt_camera_capability.strategy import CaptureStrategy, FixedOverviewCaptureStrategy


class Waypoint:
    theta = 0.0


def test_fixed_overview_generates_one_view():
    view = FixedOverviewCaptureStrategy(pitch=math.radians(45)).generate_views(Waypoint())[0]
    assert view.name == "overview"
    assert view.yaw == 0.0
    assert view.pitch == pytest.approx(math.radians(45))
    assert view.roll == 0.0


def test_fixed_overview_uses_waypoint_heading_without_hardcoded_yaw():
    waypoint = type("Waypoint", (), {"theta": -0.75})()
    assert FixedOverviewCaptureStrategy().generate_views(waypoint)[0].yaw == -0.75


def test_fixed_overview_rejects_invalid_waypoint():
    with pytest.raises(ValueError):
        FixedOverviewCaptureStrategy().generate_views(object())
    bad = type("Waypoint", (), {"theta": float("nan")})()
    with pytest.raises(ValueError):
        FixedOverviewCaptureStrategy().generate_views(bad)


def test_capture_strategy_is_abstract():
    with pytest.raises(TypeError):
        CaptureStrategy()
