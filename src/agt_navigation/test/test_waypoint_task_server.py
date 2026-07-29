import importlib.util
import asyncio
import json
from pathlib import Path
import threading
import time

from action_msgs.msg import GoalStatus
from agt_interfaces.action import ExecuteWaypointTask
from agt_interfaces.msg import LocalizationStatus, MapVersionSummary
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus, KeyValue
from geometry_msgs.msg import PoseStamped
import pytest
import rclpy
from nav2_msgs.action import FollowWaypoints
from nav_msgs.msg import OccupancyGrid
from rclpy.action import ActionClient, ActionServer, CancelResponse, GoalResponse
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.parameter import Parameter
from agt_navigation.task_group import MapBinding, TaskGroup, Waypoint

SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "waypoint_task_server.py"
SPEC = importlib.util.spec_from_file_location("waypoint_task_server", SCRIPT)
SERVER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SERVER)


@pytest.fixture
def node(tmp_path):
    if not rclpy.ok():
        rclpy.init()
    value = SERVER.WaypointTaskServer(
        parameter_overrides=[
            Parameter("require_map", value=False),
            Parameter("require_localization_valid", value=False),
            Parameter("require_safety_ready", value=False),
            Parameter("require_task_readiness", value=False),
            Parameter("allow_legacy_local_task_file", value=True),
            Parameter("allow_direct_pose_goals", value=True),
            Parameter("maps_root", value=str(tmp_path)),
        ]
    )
    try:
        yield value
    finally:
        value.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


def _request(loop=False, count=1):
    request = ExecuteWaypointTask.Goal()
    request.task_file = "/tmp/task.json"
    request.loop = loop
    request.loop_count = count
    return request


def _versioned_task(root, revision=1, version_id="v1"):
    version = root / "site" / "versions" / version_id
    (version / "tasks").mkdir(parents=True, exist_ok=True)
    (version / "manifest.yaml").write_text(
        "\n".join(
            (
                "schema_version: 1",
                "map_id: site",
                f"map_version_id: {version_id}",
                "state: READY",
            )
        ),
        encoding="utf-8",
    )
    task = TaskGroup(
        task_group_id="route",
        name="Route",
        description="",
        created_at="2026-07-29T00:00:00+00:00",
        updated_at="2026-07-29T00:00:00+00:00",
        revision=revision,
        map_binding=MapBinding(
            "site",
            version_id,
            map_yaml_sha256="sha256:yaml",
            map_image_sha256="sha256:image",
            localization_pcd_sha256="sha256:pcd",
            resolution=1.0,
            width=2,
            height=2,
            origin=(10.0, 20.0, 0.0),
        ),
        points=[Waypoint("wp_0001", "A", 10.5, 20.5, 0.0)],
    )
    task.content_sha256 = task.canonical_hash()
    (version / "tasks" / "route.json").write_text(
        json.dumps(task.to_dict(), ensure_ascii=False), encoding="utf-8"
    )
    return task


def _formal_request(task, version_id="v1"):
    request = ExecuteWaypointTask.Goal()
    request.map_id = "site"
    request.map_version_id = version_id
    request.task_group_id = task.task_group_id
    request.task_revision = task.revision
    request.expected_content_sha256 = task.content_sha256
    request.client_request_id = "request_1"
    request.loop_count = 1
    return request


def _active_map(
    *,
    map_id="site",
    version_id="v1",
    yaml_hash="sha256:yaml",
    image_hash="sha256:image",
    pcd_hash="sha256:pcd",
    valid=True,
):
    message = MapVersionSummary()
    message.active = True
    message.valid = valid
    message.state = MapVersionSummary.STATE_READY
    message.map_id = map_id
    message.map_version_id = version_id
    message.navigation_yaml_sha256 = yaml_hash
    message.navigation_image_sha256 = image_hash
    message.localization_pcd_sha256 = pcd_hash
    return message


def test_rejects_concurrent_and_unbounded_loops(node):
    assert node._goal_callback(_request(loop=True, count=0)) == GoalResponse.REJECT
    assert node._goal_callback(_request()) == GoalResponse.ACCEPT
    node._active = True
    with pytest.raises(SERVER.Blocked) as exc:
        node._claim_request(_request())
    assert exc.value.problem.code == "TASK_ALREADY_ACTIVE"


def test_rejected_concurrent_execute_does_not_clear_active_session(node):
    class GoalHandle:
        def __init__(self, request):
            self.request = request
            self.aborted = False

        def abort(self):
            self.aborted = True

        def succeed(self):
            pass

    node._active = True
    node._active_request_id = "running_request"
    handle = GoalHandle(_request())
    result = asyncio.run(node._execute(handle))

    assert handle.aborted
    assert not result.success
    assert result.blocker_code == "TASK_ALREADY_ACTIVE"
    assert node._active
    assert node._active_request_id == "running_request"


def test_legacy_task_file_is_disabled_by_default():
    if not rclpy.ok():
        rclpy.init()
    value = SERVER.WaypointTaskServer(
        parameter_overrides=[
            Parameter("require_map", value=False),
            Parameter("require_localization_valid", value=False),
            Parameter("require_safety_ready", value=False),
            Parameter("require_task_readiness", value=False),
        ]
    )
    try:
        assert value._goal_callback(_request()) == GoalResponse.REJECT
    finally:
        value.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


def test_safety_readiness_requires_enabled_and_clear_estop(node):
    message = DiagnosticArray()
    status = DiagnosticStatus()
    status.name = "agt_safety/tracked_controller"
    status.values = [
        KeyValue(key="motion_enabled", value="true"),
        KeyValue(key="estop_latched", value="false"),
    ]
    message.status = [status]
    node._safety_callback(message)
    assert node._safety_is_ready()

    status.values[1].value = "true"
    node._safety_callback(message)
    assert not node._safety_is_ready()


def test_localization_readiness_requires_accepted_tracking():
    message = LocalizationStatus()
    assert not SERVER.WaypointTaskServer.localization_status_is_ready(message)

    message.state = LocalizationStatus.STATE_TRACKING
    message.pose_valid = True
    message.localization_accepted = True
    message.error_code = LocalizationStatus.ERROR_NONE
    assert SERVER.WaypointTaskServer.localization_status_is_ready(message)

    message.status_stale = True
    assert not SERVER.WaypointTaskServer.localization_status_is_ready(message)


def test_portable_pose_input_requires_map_frame(node):
    request = _request()
    request.task_file = ""
    pose = PoseStamped()
    pose.header.frame_id = "map"
    pose.pose.position.x = 1.0
    pose.pose.orientation.w = 1.0
    request.poses = [pose]
    points = node._load_points(request)
    assert points[0].x == 1.0

    request.poses[0].header.frame_id = "odom"
    with pytest.raises(SERVER.Blocked) as exc:
        node._load_points(request)
    assert exc.value.problem.code == "TASK_SCHEMA_INVALID"


def test_formal_task_id_loads_from_robot_registry(node, tmp_path):
    task = _versioned_task(tmp_path)
    request = _formal_request(task)
    points, binding, loaded = node._load_points_and_binding(request)
    assert [point.name for point in points] == ["A"]
    assert loaded.task_group_id == "route"
    assert binding.map_id == "site"

    request.task_revision = 99
    with pytest.raises(SERVER.Blocked) as exc:
        node._load_points_and_binding(request)
    assert exc.value.problem.code == "TASK_REVISION_CONFLICT"


def test_formal_task_rejects_content_hash_mismatch(node, tmp_path):
    task = _versioned_task(tmp_path)
    request = _formal_request(task)
    request.expected_content_sha256 = "sha256:" + "0" * 64
    with pytest.raises(SERVER.Blocked) as exc:
        node._load_points_and_binding(request)
    assert exc.value.problem.code == "TASK_CONTENT_HASH_MISMATCH"


def test_new_task_group_loads_enabled_points_and_checks_active_map(node, tmp_path):
    task = tmp_path / "task_group.json"
    task.write_text(
        json.dumps(
            {
                "schema_version": 1,
                "task_group_id": "inspection_v01",
                "name": "Inspection",
                "description": "",
                "created_at": "2026-07-25T00:00:00+00:00",
                "updated_at": "2026-07-25T00:00:00+00:00",
                "frame_id": "map",
                "map_binding": {
                    "map_id": "site",
                    "map_version_id": "map_v1",
                    "map_yaml_path": "navigation/map.yaml",
                    "map_yaml_sha256": "sha256:yaml",
                    "map_image_sha256": "sha256:image",
                    "localization_pcd_sha256": "sha256:pcd",
                    "resolution": 1.0,
                    "width": 2,
                    "height": 2,
                    "origin": [10.0, 20.0, 0.0],
                },
                "execution": {"loop": False, "loop_count": 1},
                "points": [
                    {"id": "wp_1", "name": "A", "x": 10.5, "y": 20.5, "yaw": 0.0, "enabled": True, "note": ""},
                    {"id": "wp_2", "name": "B", "x": 11.5, "y": 20.5, "yaw": 0.0, "enabled": False, "note": ""},
                ],
            }
        ),
        encoding="utf-8",
    )
    request = _request()
    request.task_file = str(task)
    points, binding, loaded_task = node._load_points_and_binding(request)
    assert [point.name for point in points] == ["A"]
    assert loaded_task.task_group_id == "inspection_v01"

    current = OccupancyGrid()
    current.header.frame_id = "map"
    current.info.resolution = 1.0
    current.info.width = 2
    current.info.height = 2
    current.info.origin.position.x = 10.0
    current.info.origin.position.y = 20.0
    current.info.origin.orientation.w = 1.0
    node._active_map_callback(_active_map(version_id="map_v2"))
    assert node._validate_task_binding(binding, current).code == "MAP_VERSION_MISMATCH"

    node._active_map_callback(_active_map(version_id="map_v1", yaml_hash="sha256:other"))
    assert node._validate_task_binding(binding, current).code == "MAP_YAML_HASH_MISMATCH"

    node._active_map_callback(_active_map(version_id="map_v1"))
    assert node._validate_task_binding(binding, current) is None

    inactive = _active_map(version_id="map_v1", valid=False)
    inactive.active = False
    node._active_map_callback(inactive)
    assert node._validate_task_binding(binding, current).code == "NO_ACTIVE_MAP"


def test_versioned_task_file_rejects_unsupported_schema(node, tmp_path):
    task = tmp_path / "future.json"
    task.write_text(
        json.dumps({"schema_version": 2, "points": []}), encoding="utf-8"
    )
    request = _request()
    request.task_file = str(task)
    with pytest.raises(SERVER.Blocked) as exc:
        node._load_points_and_binding(request)
    assert exc.value.problem.code == "TASK_SCHEMA_INVALID"


def _wait(future, timeout=3.0):
    deadline = time.monotonic() + timeout
    while not future.done() and time.monotonic() < deadline:
        time.sleep(0.01)
    assert future.done()
    return future.result()


@pytest.mark.parametrize("missed, expected_success", [([], True), ([1], False)])
def test_project_action_uses_follow_waypoints_result(
    tmp_path, missed, expected_success
):
    if not rclpy.ok():
        rclpy.init()
    task_server = SERVER.WaypointTaskServer(
        parameter_overrides=[
                Parameter("require_map", value=False),
                Parameter("require_safety_ready", value=False),
                Parameter("require_localization_valid", value=False),
                Parameter("require_task_readiness", value=False),
                Parameter("allow_legacy_local_task_file", value=True),
                Parameter("maps_root", value=str(tmp_path)),
        ]
    )
    mock_node = Node("mock_follow_waypoints")

    def execute(goal_handle):
        feedback = FollowWaypoints.Feedback()
        feedback.current_waypoint = 1
        goal_handle.publish_feedback(feedback)
        goal_handle.succeed()
        result = FollowWaypoints.Result()
        result.missed_waypoints = missed
        return result

    child_server = ActionServer(mock_node, FollowWaypoints, "follow_waypoints", execute)
    client_node = Node("waypoint_task_test_client")
    client = ActionClient(
        client_node,
        ExecuteWaypointTask,
        "/agt/navigation/execute_waypoint_task",
    )
    executor = MultiThreadedExecutor(num_threads=4)
    for value in (task_server, mock_node, client_node):
        executor.add_node(value)
    thread = threading.Thread(target=executor.spin, daemon=True)
    thread.start()
    feedback_messages = []
    try:
        task_path = tmp_path / "task.json"
        task_path.write_text(
            json.dumps(
                {
                    "points": [
                        {"name": "a", "x": 0.0, "y": 0.0, "theta": 0.0},
                        {"name": "b", "x": 1.0, "y": 0.0, "theta": 0.0},
                    ]
                }
            ),
            encoding="utf-8",
        )
        assert client.wait_for_server(timeout_sec=2.0)
        request = ExecuteWaypointTask.Goal()
        request.task_file = str(task_path)
        request.loop_count = 1
        handle = _wait(
            client.send_goal_async(
                request,
                feedback_callback=lambda message: feedback_messages.append(
                    message.feedback
                ),
            )
        )
        assert handle.accepted
        wrapped = _wait(handle.get_result_async())
        assert wrapped.result.success is expected_success
        expected_code = SERVER.ERROR_NONE if expected_success else SERVER.ERROR_NAV2_FAILED
        assert wrapped.result.error_code == expected_code
        assert any(
            feedback.state == "RUNNING"
            and feedback.current_waypoint == 1
            and feedback.total_waypoints == 2
            for feedback in feedback_messages
        )
    finally:
        executor.shutdown(timeout_sec=2.0)
        thread.join(timeout=2.0)
        child_server.destroy()
        for value in (client_node, mock_node, task_server):
            value.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


def test_parent_cancel_reaches_active_follow_waypoints_child(tmp_path):
    if not rclpy.ok():
        rclpy.init()
    task_server = SERVER.WaypointTaskServer(
        parameter_overrides=[
            Parameter("require_map", value=False),
            Parameter("require_safety_ready", value=False),
            Parameter("require_localization_valid", value=False),
            Parameter("require_task_readiness", value=False),
            Parameter("allow_legacy_local_task_file", value=True),
            Parameter("maps_root", value=str(tmp_path)),
        ]
    )
    mock_node = Node("mock_cancel_follow_waypoints")
    child_started = threading.Event()
    child_canceled = threading.Event()

    def execute(goal_handle):
        child_started.set()
        deadline = time.monotonic() + 2.0
        while time.monotonic() < deadline:
            if goal_handle.is_cancel_requested:
                child_canceled.set()
                goal_handle.canceled()
                return FollowWaypoints.Result()
            time.sleep(0.005)
        goal_handle.abort()
        return FollowWaypoints.Result()

    child_server = ActionServer(
        mock_node,
        FollowWaypoints,
        "follow_waypoints",
        execute,
        cancel_callback=lambda _goal: CancelResponse.ACCEPT,
    )
    client_node = Node("waypoint_cancel_test_client")
    client = ActionClient(
        client_node,
        ExecuteWaypointTask,
        "/agt/navigation/execute_waypoint_task",
    )
    executor = MultiThreadedExecutor(num_threads=4)
    for value in (task_server, mock_node, client_node):
        executor.add_node(value)
    thread = threading.Thread(target=executor.spin, daemon=True)
    thread.start()
    try:
        task_path = tmp_path / "cancel_task.json"
        task_path.write_text(
            json.dumps(
                {
                    "points": [
                        {"name": "a", "x": 0.0, "y": 0.0, "theta": 0.0},
                        {"name": "b", "x": 1.0, "y": 0.0, "theta": 0.0},
                    ]
                }
            ),
            encoding="utf-8",
        )
        assert client.wait_for_server(timeout_sec=2.0)
        request = ExecuteWaypointTask.Goal()
        request.task_file = str(task_path)
        request.loop_count = 1
        handle = _wait(client.send_goal_async(request))
        assert handle.accepted
        assert child_started.wait(timeout=2.0)
        cancel_response = _wait(handle.cancel_goal_async())
        assert cancel_response.goals_canceling
        wrapped = _wait(handle.get_result_async())
        assert wrapped.status == GoalStatus.STATUS_CANCELED
        assert not wrapped.result.success
        assert wrapped.result.error_code == SERVER.ERROR_CANCELED
        assert child_canceled.wait(timeout=2.0)
    finally:
        executor.shutdown(timeout_sec=2.0)
        thread.join(timeout=2.0)
        child_server.destroy()
        for value in (client_node, mock_node, task_server):
            value.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
