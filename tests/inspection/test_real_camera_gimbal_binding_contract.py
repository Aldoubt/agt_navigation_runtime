from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
SERVER = ROOT / "src/agt_inspection/scripts/inspection_task_server.py"
CONTEXT = ROOT / "src/agt_inspection/agt_inspection/ros_multiview.py"
ROS_BACKEND = ROOT / "src/agt_inspection/agt_inspection/ros_camera_gimbal.py"


def test_inspection_server_exposes_explicit_camera_gimbal_backend():
    source = SERVER.read_text(encoding="utf-8")
    assert 'declare_parameter("view_backend", "legacy")' in source
    assert '"camera_gimbal"' in source
    assert "RosCameraGimbalAcquireRunner" in source
    assert "view_acquirer=self._view_acquirer" in source


def test_real_backend_uses_atomic_acquire_view_action():
    source = ROS_BACKEND.read_text(encoding="utf-8")
    assert "camera_gimbal_interfaces.action import AcquireView" in source
    assert '"/camera_gimbal/acquire_view"' in source
    assert "make_acquire_view_goal" in source
    assert "normalize_acquire_view_result" in source
    assert "actual_pan_rad" in source
    assert "actual_roll_rad" in source
    assert "actual_tilt_rad" in source
    assert "image_stamp" in source
    assert "reached_stamp" in source


def test_capture_context_fails_closed_without_real_stamp_or_gimbal_feedback():
    source = CONTEXT.read_text(encoding="utf-8")
    assert 'raise ValueError("capture timestamp is unavailable")' in source
    assert 'raise ValueError("actual gimbal feedback is unavailable")' in source
    assert "view.gimbal.pan_rad" not in source
    assert "view.gimbal.tilt_rad" not in source


def test_camera_gimbal_backend_rejects_new_goals_until_health_is_fresh_ready():
    source = SERVER.read_text(encoding="utf-8")
    assert "camera_gimbal_interfaces.msg import CapabilityHealth" in source
    assert "CameraGimbalHealthGate" in source
    assert '"/camera_gimbal/health"' in source
    assert "self._camera_gimbal_health.ready(time.monotonic())" in source
    assert "GoalResponse.REJECT" in source
