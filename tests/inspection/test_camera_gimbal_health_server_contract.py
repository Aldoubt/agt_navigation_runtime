from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
SERVER = ROOT / "src/agt_inspection/scripts/inspection_task_server.py"
CMAKE = ROOT / "src/agt_inspection/CMakeLists.txt"


def test_camera_gimbal_backend_subscribes_health_and_rejects_unready_goals():
    source = SERVER.read_text(encoding="utf-8")
    assert "camera_gimbal_interfaces.msg import CapabilityHealth" in source
    assert "CameraGimbalHealthGate" in source
    assert 'declare_parameter("camera_gimbal_health_freshness_s", 1.5)' in source
    assert '"/camera_gimbal/health"' in source
    assert "self._camera_gimbal_health.update(" in source
    assert "self._camera_gimbal_health.ready(time.monotonic())" in source
    assert "return GoalResponse.REJECT" in source


def test_health_policy_runs_in_humble_package_tests():
    source = CMAKE.read_text(encoding="utf-8")
    assert "test_camera_gimbal_health" in source
