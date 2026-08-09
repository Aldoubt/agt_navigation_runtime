import importlib.util
from pathlib import Path
import threading
import time

from action_msgs.msg import GoalStatus
from agt_interfaces.action import ExecuteWaypointTask
from agt_interfaces.msg import LocalizationStatus
from geometry_msgs.msg import TransformStamped
from nav2_msgs.action import FollowPath
import pytest
import rclpy
from rclpy.action import ActionClient, ActionServer
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.parameter import Parameter


HELPERS_PATH = Path(__file__).with_name("test_navigation_capability_server.py")
HELPERS_SPEC = importlib.util.spec_from_file_location(
    "v25_10_route_generation_helpers", HELPERS_PATH
)
HELPERS = importlib.util.module_from_spec(HELPERS_SPEC)
HELPERS_SPEC.loader.exec_module(HELPERS)
SERVER = HELPERS.SERVER


def _wait(future, timeout=5.0):
    deadline = time.monotonic() + timeout
    while not future.done() and time.monotonic() < deadline:
        time.sleep(0.01)
    assert future.done()
    return future.result()


def _wait_until(predicate, timeout=2.0):
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        if predicate():
            return
        time.sleep(0.01)
    assert predicate()


def _localization(generation: int) -> LocalizationStatus:
    message = LocalizationStatus()
    message.state = LocalizationStatus.STATE_TRACKING
    message.pose_valid = True
    message.localization_accepted = True
    message.error_code = LocalizationStatus.ERROR_NONE
    message.status_stale = False
    message.map_id = "site"
    message.map_hash = "sha256:pcd"
    message.correction_generation = int(generation)
    return message


class MutableMapOdomBuffer:
    """Minimal TF buffer double used by NavigationCapabilityServer._route_snapshot."""

    def __init__(self, state):
        self.state = state

    def lookup_transform(self, target_frame, source_frame, *_args, **_kwargs):
        assert target_frame == "map"
        assert source_frame == "odom"
        transform = TransformStamped()
        transform.header.frame_id = "map"
        transform.child_frame_id = "odom"
        transform.transform.translation.x = float(self.state["x"])
        transform.transform.translation.y = float(self.state["y"])
        transform.transform.rotation.w = 1.0
        return transform


def test_localization_generation_reprojects_only_next_route_segment(tmp_path):
    """Exercise LocalizationStatus -> Capability -> RouteBackend -> FollowPath.

    The first RuntimePath is frozen at correction generation 7. While that child
    FollowPath goal is active, canonical localization and map->odom advance to
    generation 8. The active path must not jump or be resent. Only after s000
    succeeds may s001 be projected from the new transform and generation.
    """

    task, profile, _version = HELPERS._prepare_assets(tmp_path)
    if not rclpy.ok():
        rclpy.init()

    tf_state = {"x": 10.0, "y": 20.0}
    task_server = SERVER.NavigationCapabilityServer(
        parameter_overrides=[
            Parameter("require_map", value=False),
            Parameter("require_safety_ready", value=False),
            Parameter("require_localization_valid", value=True),
            Parameter("require_task_readiness", value=False),
            Parameter("maps_root", value=str(tmp_path)),
            Parameter("execution_vehicle_profile", value=str(profile)),
            Parameter("route_controller_id_forward", value="RouteForward"),
            Parameter("route_controller_id_reverse", value="RouteReverse"),
            Parameter("localization_status_timeout", value=5.0),
            Parameter("nav2_wait_timeout", value=2.0),
        ],
    )
    HELPERS._set_active_map(task_server)
    task_server._tf_buffer = MutableMapOdomBuffer(tf_state)
    task_server._localization_callback(_localization(7))

    mock_node = Node("mock_follow_path_v25_10_generation")
    received = []
    first_started = threading.Event()
    second_started = threading.Event()
    release_first = threading.Event()
    release_second = threading.Event()

    def execute_follow_path(goal_handle):
        index = len(received)
        received.append(goal_handle.request)
        if index == 0:
            first_started.set()
            assert release_first.wait(timeout=3.0)
        elif index == 1:
            second_started.set()
            assert release_second.wait(timeout=3.0)
        goal_handle.succeed()
        result = FollowPath.Result()
        if hasattr(result, "error_code"):
            result.error_code = 0
        if hasattr(result, "error_msg"):
            result.error_msg = ""
        return result

    child_server = ActionServer(
        mock_node, FollowPath, "follow_path", execute_follow_path
    )
    client_node = Node("v25_10_generation_client")
    client = ActionClient(
        client_node,
        ExecuteWaypointTask,
        "/agt/navigation/execute_waypoint_task",
    )
    executor = MultiThreadedExecutor(num_threads=6)
    for node in (task_server, mock_node, client_node):
        executor.add_node(node)
    thread = threading.Thread(target=executor.spin, daemon=True)
    thread.start()

    try:
        assert client.wait_for_server(timeout_sec=2.0)
        handle = _wait(
            client.send_goal_async(
                HELPERS._formal_request(task, "v25_10_generation_boundary")
            )
        )
        assert handle.accepted
        assert first_started.wait(timeout=2.0)

        def first_core_ready():
            backend = task_server._route_executor
            return backend is not None and backend._core is not None and backend._core.active_path is not None

        _wait_until(first_core_ready)
        first_core = task_server._route_executor._core
        first_path = first_core.active_path
        first_points = tuple((point.x, point.y) for point in first_path.points)
        assert first_path.segment_id == "s000"
        assert first_path.alignment_generation == 7
        assert first_points[0][0] == pytest.approx(0.5)
        assert len(received) == 1

        # A new accepted correction arrives while s000 is still being tracked.
        tf_state["x"] = 20.0
        task_server._localization_callback(_localization(8))

        # The active RuntimePath is immutable until the segment boundary.
        assert task_server._route_executor._core.active_path is first_path
        assert tuple((point.x, point.y) for point in first_path.points) == first_points
        assert first_path.alignment_generation == 7
        assert len(received) == 1

        release_first.set()
        assert second_started.wait(timeout=2.0)

        def second_core_ready():
            backend = task_server._route_executor
            return (
                backend is not None
                and backend._core is not None
                and backend._core.active_path is not None
                and backend._core.active_path.segment_id == "s001"
            )

        _wait_until(second_core_ready)
        second_path = task_server._route_executor._core.active_path
        assert second_path.alignment_generation == 8
        assert second_path.points[0].x == pytest.approx(-9.0)
        assert second_path.points[0].y == pytest.approx(0.5)
        assert len(received) == 2
        assert received[0].path.header.frame_id == "odom"
        assert received[1].path.header.frame_id == "odom"

        release_second.set()
        wrapped = _wait(handle.get_result_async())
        assert wrapped.status == GoalStatus.STATUS_SUCCEEDED
        assert wrapped.result.success
    finally:
        release_first.set()
        release_second.set()
        executor.shutdown(timeout_sec=2.0)
        thread.join(timeout=2.0)
        child_server.destroy()
        for node in (client_node, mock_node, task_server):
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
