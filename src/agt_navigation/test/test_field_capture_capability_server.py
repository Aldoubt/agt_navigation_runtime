import importlib.util
import json
from pathlib import Path
import threading
import time

from action_msgs.msg import GoalStatus
from agt_interfaces.action import ExecuteWaypointTask
from agt_interfaces.msg import MapVersionSummary
from agt_navigation.task_group import MapBinding, TaskGroup, Waypoint
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import NavigateToPose
from nav_msgs.msg import OccupancyGrid
import rclpy
from rclpy.action import ActionClient, ActionServer
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.parameter import Parameter


SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "field_capture_capability_server.py"
SPEC = importlib.util.spec_from_file_location("field_capture_capability_server", SCRIPT)
SERVER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SERVER)


def _digest(char):
    return "sha256:" + char * 64


def _wait(future, timeout=5.0):
    deadline = time.monotonic() + timeout
    while not future.done() and time.monotonic() < deadline:
        time.sleep(0.01)
    assert future.done()
    return future.result()


def _pose(x, y, yaw=0.0):
    import math

    pose = PoseStamped()
    pose.header.frame_id = "map"
    pose.pose.position.x = float(x)
    pose.pose.position.y = float(y)
    pose.pose.orientation.z = math.sin(float(yaw) / 2.0)
    pose.pose.orientation.w = math.cos(float(yaw) / 2.0)
    return pose


def _prepare_task(root: Path):
    task_root = root / "tasks" / "orchard" / "map_v1"
    task_root.mkdir(parents=True, exist_ok=True)
    task = TaskGroup(
        task_group_id="inspection",
        name="Inspection",
        description="",
        created_at="2026-08-31T00:00:00+00:00",
        updated_at="2026-08-31T00:00:00+00:00",
        revision=1,
        map_binding=MapBinding(
            "orchard",
            "map_v1",
            map_yaml_sha256=_digest("1"),
            map_image_sha256=_digest("2"),
            localization_pcd_sha256=_digest("3"),
            resolution=1.0,
            width=10,
            height=10,
            origin=(0.0, 0.0, 0.0),
        ),
        points=[Waypoint("tree_01", "Tree 01", 4.0, 5.0, 0.25)],
    )
    task.content_sha256 = task.canonical_hash()
    (task_root / "inspection.json").write_text(
        json.dumps(task.to_dict(), ensure_ascii=False), encoding="utf-8"
    )
    (task_root / "site_binding.json").write_text(
        json.dumps(
            {
                "schema_version": 1,
                "map_id": "orchard",
                "map_version_id": "map_v1",
                "map_hash": _digest("a"),
                "manifest_sha256": _digest("b"),
                "navigation_yaml_sha256": _digest("1"),
                "navigation_image_sha256": _digest("2"),
                "localization_pcd_sha256": _digest("3"),
            }
        ),
        encoding="utf-8",
    )
    return task


def _set_map(server):
    grid = OccupancyGrid()
    grid.header.frame_id = "map"
    grid.info.resolution = 1.0
    grid.info.width = 10
    grid.info.height = 10
    grid.info.origin.orientation.w = 1.0
    server._map_callback(grid)

    active = MapVersionSummary()
    active.active = True
    active.valid = True
    active.state = MapVersionSummary.STATE_READY
    active.map_id = "orchard"
    active.map_version_id = "map_v1"
    active.map_hash = _digest("a")
    active.manifest_sha256 = _digest("b")
    active.navigation_yaml_sha256 = _digest("1")
    active.navigation_image_sha256 = _digest("2")
    active.localization_pcd_sha256 = _digest("3")
    server._active_map_callback(active)


def _request(task):
    goal = ExecuteWaypointTask.Goal()
    goal.map_id = "orchard"
    goal.map_version_id = "map_v1"
    goal.task_group_id = "inspection"
    goal.task_revision = 1
    goal.expected_content_sha256 = task.content_sha256
    goal.loop_count = 1
    goal.client_request_id = "field-capture-test-001"
    return goal


def test_field_capture_executes_point_capture_then_returns_home(tmp_path):
    task = _prepare_task(tmp_path)
    poses = iter([_pose(1.0, 2.0, 0.0), _pose(4.1, 5.1, 0.3)])
    if not rclpy.ok():
        rclpy.init()

    server = SERVER.FieldCaptureCapabilityServer(
        field_pose_provider=lambda: next(poses),
        parameter_overrides=[
            Parameter("require_safety_ready", value=False),
            Parameter("require_localization_valid", value=False),
            Parameter("require_task_readiness", value=False),
            Parameter("maps_root", value=str(tmp_path)),
            Parameter("tasks_root", value=str(tmp_path / "tasks")),
            Parameter("runtime_dir", value=str(tmp_path / "runtime")),
            Parameter("field_capture_root", value=str(tmp_path / "inspection_runs")),
            Parameter("field_capture_backend", value="placeholder"),
        ],
    )
    _set_map(server)

    nav_node = Node("mock_field_navigate_to_pose")
    received = []

    def execute_nav(goal_handle):
        received.append(goal_handle.request.pose)
        goal_handle.succeed()
        return NavigateToPose.Result()

    nav_server = ActionServer(nav_node, NavigateToPose, "navigate_to_pose", execute_nav)
    client_node = Node("field_capture_action_client")
    client = ActionClient(
        client_node,
        ExecuteWaypointTask,
        "/agt/navigation/execute_waypoint_task",
    )
    executor = MultiThreadedExecutor(num_threads=7)
    for node in (server, nav_node, client_node):
        executor.add_node(node)
    thread = threading.Thread(target=executor.spin, daemon=True)
    thread.start()
    try:
        assert client.wait_for_server(timeout_sec=2.0)
        handle = _wait(client.send_goal_async(_request(task)))
        assert handle.accepted
        wrapped = _wait(handle.get_result_async())

        assert wrapped.status == GoalStatus.STATUS_SUCCEEDED
        assert wrapped.result.success
        assert len(received) == 2
        assert (received[0].pose.position.x, received[0].pose.position.y) == (4.0, 5.0)
        assert (received[1].pose.position.x, received[1].pose.position.y) == (1.0, 2.0)
        assert "return_home=SUCCESS" in wrapped.result.message
        assert "images saved to:" in wrapped.result.message

        run_dirs = list((tmp_path / "inspection_runs").iterdir())
        assert len(run_dirs) == 1
        run_dir = run_dirs[0]
        point_dirs = list(run_dir.glob("P01_*"))
        assert len(point_dirs) == 1
        assert (point_dirs[0] / "image.pgm").is_file()
        point_result = json.loads(
            (point_dirs[0] / "result.json").read_text(encoding="utf-8")
        )
        assert point_result["capture_pose"] == {"x": 4.1, "y": 5.1, "yaw": 0.3}
        summary = json.loads((run_dir / "summary.json").read_text(encoding="utf-8"))
        assert summary["success"] is True
        assert summary["return_home_success"] is True
        assert summary["completed_waypoints"] == 1
    finally:
        executor.shutdown(timeout_sec=2.0)
        thread.join(timeout=2.0)
        nav_server.destroy()
        for node in (client_node, nav_node, server):
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
