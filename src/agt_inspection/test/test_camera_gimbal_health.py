from agt_inspection.camera_gimbal_health import CameraGimbalHealthGate


def test_health_gate_requires_fresh_ready_sample():
    gate = CameraGimbalHealthGate(freshness_s=1.0)
    assert gate.ready(now=10.0) is False

    gate.update(
        state=1,
        camera_alive=True,
        gimbal_serial_connected=True,
        gimbal_feedback_alive=True,
        move_action_ready=True,
        busy=False,
        seen_monotonic=10.0,
    )
    assert gate.ready(now=10.5) is True
    assert gate.ready(now=11.01) is False


def test_health_gate_rejects_busy_degraded_or_partial_hardware():
    gate = CameraGimbalHealthGate(freshness_s=2.0)
    common = dict(
        camera_alive=True,
        gimbal_serial_connected=True,
        gimbal_feedback_alive=True,
        move_action_ready=True,
        busy=False,
        seen_monotonic=5.0,
    )

    gate.update(state=2, **common)
    assert gate.ready(now=5.1) is False

    gate.update(state=3, **common)
    assert gate.ready(now=5.1) is False

    gate.update(state=1, **{**common, "camera_alive": False})
    assert gate.ready(now=5.1) is False

    gate.update(state=1, **{**common, "gimbal_feedback_alive": False})
    assert gate.ready(now=5.1) is False

    gate.update(state=1, **{**common, "busy": True})
    assert gate.ready(now=5.1) is False


def test_health_gate_exposes_diagnostic_reason_without_changing_control_semantics():
    gate = CameraGimbalHealthGate(freshness_s=1.0)
    assert gate.reason(now=1.0) == "NO_HEALTH_SAMPLE"

    gate.update(
        state=4,
        camera_alive=True,
        gimbal_serial_connected=True,
        gimbal_feedback_alive=True,
        move_action_ready=True,
        busy=False,
        seen_monotonic=1.0,
    )
    assert gate.reason(now=1.1) == "STATE_NOT_READY"
