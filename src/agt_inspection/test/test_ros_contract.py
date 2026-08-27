from pathlib import Path


PACKAGE = Path(__file__).resolve().parents[1]


def test_inspection_ros_endpoints_and_adapter_boundaries_are_frozen():
    scripts = PACKAGE / "scripts"
    expected = {
        "inspection_task_server.py": "/agt/inspection/execute_task",
        "mock_gimbal_server.py": "/agt/gimbal/move",
        "mock_camera_server.py": "/agt/camera/capture",
        "mock_vision_server.py": "/agt/vision/inspect",
    }
    for filename, endpoint in expected.items():
        path = scripts / filename
        assert path.is_file(), filename
        source = path.read_text(encoding="utf-8")
        assert endpoint in source
        assert "nav2_msgs" not in source

    inspection = (scripts / "inspection_task_server.py").read_text(encoding="utf-8")
    assert "ExecuteWaypointTask" in inspection
    assert "/agt/navigation/execute_waypoint_task" in inspection
    assert "/agt/chassis/odometry" in inspection
    assert "InspectionRepository" in inspection
    assert "expected_content_sha256" in inspection
    assert "task_revision" in inspection
    assert "loop_count = 1" in inspection
    assert "task_file" not in inspection


def test_mocks_use_declared_action_service_types_and_deterministic_vision_result():
    gimbal = (PACKAGE / "scripts" / "mock_gimbal_server.py").read_text(encoding="utf-8")
    camera = (PACKAGE / "scripts" / "mock_camera_server.py").read_text(encoding="utf-8")
    vision = (PACKAGE / "scripts" / "mock_vision_server.py").read_text(encoding="utf-8")

    assert "ActionServer" in gimbal and "MoveGimbal" in gimbal
    assert "create_service" in camera and "CaptureImage" in camera
    assert "ActionServer" in vision and "InspectImage" in vision
    assert "rgb8" in camera
    assert "16" in camera
    assert 'model_id = "mock-vision"' in vision
    assert 'model_version = "1"' in vision
    assert "0.93" in vision
    assert "test_target" in vision


def test_package_installs_ros_scripts_and_declares_runtime_dependencies():
    cmake = (PACKAGE / "CMakeLists.txt").read_text(encoding="utf-8")
    manifest = (PACKAGE / "package.xml").read_text(encoding="utf-8")
    for filename in (
        "inspection_task_server.py",
        "mock_gimbal_server.py",
        "mock_camera_server.py",
        "mock_vision_server.py",
    ):
        assert filename in cmake
    for dependency in (
        "agt_interfaces",
        "nav_msgs",
        "rclpy",
        "sensor_msgs",
    ):
        assert f"<{ 'depend' }>{dependency}</depend>" in manifest
