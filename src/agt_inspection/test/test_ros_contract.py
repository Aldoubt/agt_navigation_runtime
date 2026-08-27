from pathlib import Path


PACKAGE = Path(__file__).resolve().parents[1]


def _read(relative: str) -> str:
    return (PACKAGE / relative).read_text(encoding="utf-8")


def _production_python() -> str:
    roots = (PACKAGE / "agt_inspection", PACKAGE / "scripts")
    return "\n".join(
        path.read_text(encoding="utf-8")
        for root in roots
        for path in root.rglob("*.py")
    )


def _has_runtime_dependency(manifest: str, dependency: str) -> bool:
    return (
        f"<depend>{dependency}</depend>" in manifest
        or f"<exec_depend>{dependency}</exec_depend>" in manifest
    )


def test_inspection_ros_nodes_use_only_project_navigation_boundary():
    server = _read("scripts/inspection_task_server.py")
    production_python = _production_python()

    assert "ExecuteWaypointTask" in server
    assert '"/agt/navigation/execute_waypoint_task"' in server
    assert "/agt/chassis/odometry" in server
    assert "InspectionRepository" in server
    assert "nav2_msgs" not in production_python
    assert "NavigateToPose" not in production_python
    assert "FollowWaypoints" not in production_python

    for token in (
        "goal.map_id = self.map_id",
        "goal.map_version_id = self.map_version_id",
        "goal.task_group_id = point.navigation.task_group_id",
        "goal.task_revision = point.navigation.task_revision",
        "goal.expected_content_sha256 = point.navigation.expected_content_sha256",
        "goal.loop_count = 1",
        'goal.task_file = ""',
        "goal.poses = []",
        "goal.loop = False",
    ):
        assert token in server


def test_mock_leaf_servers_freeze_endpoint_names_and_types():
    gimbal = _read("scripts/mock_gimbal_server.py")
    camera = _read("scripts/mock_camera_server.py")
    vision = _read("scripts/mock_vision_server.py")
    task_server = _read("scripts/inspection_task_server.py")

    assert "ActionServer" in gimbal and "MoveGimbal" in gimbal
    assert '"/agt/gimbal/move"' in gimbal
    assert "create_service" in camera and "CaptureImage" in camera
    assert '"/agt/camera/capture"' in camera
    assert "ActionServer" in vision and "InspectImage" in vision
    assert '"/agt/vision/inspect"' in vision
    assert "ActionServer" in task_server and "ExecuteInspectionTask" in task_server
    assert '"/agt/inspection/execute_task"' in task_server


def test_mocks_are_deterministic_contract_fixtures():
    camera = _read("scripts/mock_camera_server.py")
    vision = _read("scripts/mock_vision_server.py")

    assert "16" in camera
    assert 'image.encoding = "rgb8"' in camera
    assert 'result.model_id = "mock-vision"' in vision
    assert 'result.model_version = "1"' in vision
    assert "0.93" in vision
    assert "test_target" in vision


def test_package_installs_ros_scripts_launch_and_runtime_dependencies():
    cmake = _read("CMakeLists.txt")
    manifest = _read("package.xml")
    for filename in (
        "inspection_task_server.py",
        "mock_gimbal_server.py",
        "mock_camera_server.py",
        "mock_vision_server.py",
    ):
        assert filename in cmake
    assert "install(DIRECTORY launch" in cmake
    for dependency in (
        "action_msgs",
        "agt_interfaces",
        "nav_msgs",
        "rclpy",
        "sensor_msgs",
    ):
        assert _has_runtime_dependency(manifest, dependency)
