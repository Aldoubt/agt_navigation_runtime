import pytest

from agt_navigation.odometry_settle_monitor import (
    OdometrySettleMonitor, SETTLED, STABILIZING, STALE, TIMEOUT, NOT_READY
)


def monitor():
    return OdometrySettleMonitor(
        linear_velocity_threshold=0.05,
        angular_velocity_threshold=0.05,
        stable_duration=2.0,
        timeout=5.0,
        odom_stale_timeout=0.5,
    )


def sample(m, now, vx=0.0, vy=0.0, wz=0.0, stamp=None):
    m.update(vx=vx, vy=vy, wz=wz, odom_stamp=now if stamp is None else stamp, now=now)


def test_no_odom_is_not_settled():
    m = monitor(); m.start(0.0)
    assert m.status(1.0).state == NOT_READY


def test_single_low_speed_sample_is_not_settled():
    m = monitor(); m.start(0.0); sample(m, 0.1)
    assert m.status(0.1).state == STABILIZING


def test_low_speed_window_needs_full_duration():
    m = monitor(); m.start(0.0); sample(m, 0.1)
    assert m.status(1.9).state != SETTLED


def test_continuous_low_speed_window_settles():
    m = monitor(); m.start(0.0); sample(m, 0.1); sample(m, 2.1)
    assert m.status(2.2).settled


def test_speed_spike_resets_stable_window():
    m = monitor(); m.start(0.0); sample(m, 0.1); sample(m, 1.0, vx=0.1); sample(m, 1.1); sample(m, 3.1)
    assert not m.status(2.9).settled
    assert m.status(3.2).settled


def test_stale_odom_is_not_settled():
    m = monitor(); m.start(0.0); sample(m, 0.1, stamp=0.1)
    assert m.status(0.7).state == STALE


def test_timeout_without_odom_is_fail_closed():
    m = monitor(); m.start(0.0)
    assert m.status(5.0).state == TIMEOUT


def test_angular_velocity_prevents_settle():
    m = monitor(); m.start(0.0); sample(m, 0.1, wz=0.1)
    assert not m.status(2.2).settled


def test_invalid_timestamp_is_fail_closed():
    m = monitor(); m.start(0.0); sample(m, 0.1, stamp=0.0)
    assert not m.status(2.2).settled


def test_timestamp_rollback_resets_stable_window():
    m = monitor(); m.start(100.0)
    sample(m, 100.1, stamp=100.1); sample(m, 100.2, stamp=100.2)
    sample(m, 100.3, stamp=99.9)
    assert not m.status(102.3).settled
