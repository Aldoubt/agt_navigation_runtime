import importlib.util
import json
from pathlib import Path
import threading
import time

from agt_interfaces.action import ExecuteWaypointTask
from agt_interfaces.msg import LocalizationStatus
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus, KeyValue
from geometry_msgs.msg import PoseStamped
import pytest
import rclpy
from nav2_msgs.action import FollowWaypoints
from rclpy.action import ActionClient, ActionServer, GoalResponse
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.parameter import Parameter

SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "waypoint_task_server.py"
SPEC = importlib.util.spec_from_file_location("waypoint_task_server", SCRIPT)
SERVER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SERVER)


@pytest.fixture
def node():
    if not rclpy.ok():
        rclpy.init()
    value = SERVER.WaypointTaskServer(
        parameter_overrides=[
            Parameter("require_localization_valid", value=False),
            Parameter("require_safety_ready", value=False),
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


def test_rejects_concurrent_and_unbounded_loops(node):
    assert node._goal_callback(_request(loop=True, count=0)) == GoalResponse.REJECT
    assert node._goal_callback(_request()) == GoalResponse.ACCEPT
    assert node._goal_callback(_request()) == GoalResponse.REJECT


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
    with pytest.raises(SERVER.TaskChainError, match="frame_id must be map"):
        node._load_points(request)


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
        handle = _wait(client.send_goal_async(request))
        assert handle.accepted
        wrapped = _wait(handle.get_result_async())
        assert wrapped.result.success is expected_success
        expected_code = SERVER.ERROR_NONE if expected_success else SERVER.ERROR_NAV2_FAILED
        assert wrapped.result.error_code == expected_code
    finally:
        executor.shutdown(timeout_sec=2.0)
        thread.join(timeout=2.0)
        child_server.destroy()
        for value in (client_node, mock_node, task_server):
            value.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
