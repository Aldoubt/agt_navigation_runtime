import importlib.util
import json
from pathlib import Path
import threading
import time

from action_msgs.msg import GoalStatus
from agt_interfaces.action import ExecuteWaypointTask
from agt_interfaces.msg import MapVersionSummary
from agt_navigation.route_runtime import MapOdomSnapshot
from agt_navigation.route_task_binding import sha256_file
from agt_navigation.task_group import MapBinding, TaskGroup, Waypoint
from nav2_msgs.action import FollowPath, FollowWaypoints
from nav_msgs.msg import OccupancyGrid
import pytest
import rclpy
from rclpy.action import ActionClient, ActionServer
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.parameter import Parameter
import yaml

SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "navigation_capability_server.py"
SPEC = importlib.util.spec_from_file_location("navigation_capability_server", SCRIPT)
SERVER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SERVER)


def _wait(future, timeout=4.0):
    deadline = time.monotonic() + timeout
    while not future.done() and time.monotonic() < deadline:
        time.sleep(0.01)
    assert future.done()
    return future.result()


def _prepare_assets(root: Path):
    version = root / "site" / "versions" / "map_v1"
    (version / "tasks").mkdir(parents=True)
    route_dir = version / "routes" / "route_main" / "1"
    route_dir.mkdir(parents=True)

    map_content = "sha256:" + "a" * 64
    (version / "manifest.yaml").write_text(
        yaml.safe_dump(
            {
                "schema_version": 1,
                "map_id": "site",
                "map_version_id": "map_v1",
                "state": "READY",
                "map_content_sha256": map_content,
            },
            sort_keys=False,
        ),
        encoding="utf-8",
    )

    profile = root / "mk_mini_test.yaml"
    profile.write_text(
        yaml.safe_dump(
            {
                "platform": {
                    "name": "mk_mini_test",
                    "kinematics": "ackermann",
                    "route_acceptance": {"enabled": True},
                }
            },
            sort_keys=False,
        ),
        encoding="utf-8",
    )
    profile_hash = sha256_file(profile)

    task = TaskGroup(
        task_group_id="inspection",
        name="Inspection",
        description="",
        created_at="2026-08-08T00:00:00+00:00",
        updated_at="2026-08-08T00:00:00+00:00",
        revision=1,
        map_binding=MapBinding(
            "site",
            "map_v1",
            map_yaml_sha256="sha256:yaml",
            map_image_sha256="sha256:image",
            localization_pcd_sha256="sha256:pcd",
            resolution=1.0,
            width=2,
            height=2,
            origin=(10.0, 20.0, 0.0),
        ),
        points=[Waypoint("wp_1", "A", 10.5, 20.5, 0.0)],
    )
    task.content_sha256 = task.canonical_hash()
    (version / "tasks" / "inspection.json").write_text(
        json.dumps(task.to_dict(), ensure_ascii=False), encoding="utf-8"
    )

    route_csv = route_dir / "route.csv"
    route_csv.write_text(
        "seq,segment_id,x,y,yaw,direction,v_ref,curvature,clearance,semantic_ref,event_ref\n"
        "0,s000,10.5,20.5,0.0,F,0.2,0.0,1.0,row_0,\n"
        "1,s000,11.0,20.5,0.0,F,0.2,0.0,1.0,row_0,stop_a\n"
        "2,s001,11.0,20.5,3.141592654,R,0.15,0.0,1.0,headland,\n"
        "3,s001,10.5,20.5,3.141592654,R,0.15,0.0,1.0,headland,stop_b\n",
        encoding="utf-8",
    )
    route_yaml = route_dir / "route.yaml"
    route_yaml.write_text(
        yaml.safe_dump(
            {
                "schema_version": 1,
                "route_id": "route_main",
                "revision": 1,
                "frame_id": "map",
                "map_binding": {
                    "map_id": "site",
                    "map_version_id": "map_v1",
                    "map_content_sha256": map_content,
                },
                "vehicle_binding": {
                    "platform_id": "mk_mini_test",
                    "platform_profile_sha256": profile_hash,
                },
                "route_csv_sha256": sha256_file(route_csv),
                "status": "READY",
            },
            sort_keys=False,
        ),
        encoding="utf-8",
    )
    (version / "tasks" / "inspection.route.yaml").write_text(
        yaml.safe_dump(
            {
                "schema_version": 1,
                "status": "READY",
                "backend": "ROUTE",
                "task_binding": {
                    "task_group_id": "inspection",
                    "task_revision": 1,
                    "task_content_sha256": task.content_sha256,
                },
                "route_binding": {
                    "route_id": "route_main",
                    "revision": 1,
                    "route_manifest_sha256": sha256_file(route_yaml),
                },
            },
            sort_keys=False,
        ),
        encoding="utf-8",
    )
    return task, profile, version


def _set_active_map(server):
    current = OccupancyGrid()
    current.header.frame_id = "map"
    current.info.resolution = 1.0
    current.info.width = 2
    current.info.height = 2
    current.info.origin.position.x = 10.0
    current.info.origin.position.y = 20.0
    current.info.origin.orientation.w = 1.0
    server._map_callback(current)

    active = MapVersionSummary()
    active.active = True
    active.valid = True
    active.state = MapVersionSummary.STATE_READY
    active.map_id = "site"
    active.map_version_id = "map_v1"
    active.navigation_yaml_sha256 = "sha256:yaml"
    active.navigation_image_sha256 = "sha256:image"
    active.localization_pcd_sha256 = "sha256:pcd"
    server._active_map_callback(active)


def _formal_request(task, request_id):
    request = ExecuteWaypointTask.Goal()
    request.map_id = "site"
    request.map_version_id = "map_v1"
    request.task_group_id = "inspection"
    request.task_revision = 1
    request.expected_content_sha256 = task.content_sha256
    request.loop_count = 1
    request.client_request_id = request_id
    return request


def test_execute_waypoint_task_selects_route_follow_path_without_follow_waypoints(tmp_path):
    task, profile, _version = _prepare_assets(tmp_path)
    if not rclpy.ok():
        rclpy.init()

    snapshots = iter(
        [
            MapOdomSnapshot(10.0, 20.0, 0.0, generation=1),
            MapOdomSnapshot(10.1, 20.0, 0.0, generation=2),
        ]
    )
    task_server = SERVER.NavigationCapabilityServer(
        route_snapshot_provider=lambda: next(snapshots),
        parameter_overrides=[
            Parameter("require_map", value=False),
            Parameter("require_safety_ready", value=False),
            Parameter("require_localization_valid", value=False),
            Parameter("require_task_readiness", value=False),
            Parameter("maps_root", value=str(tmp_path)),
            Parameter("execution_vehicle_profile", value=str(profile)),
            Parameter("route_controller_id_forward", value="RouteForward"),
            Parameter("route_controller_id_reverse", value="RouteReverse"),
        ],
    )
    _set_active_map(task_server)

    mock_node = Node("mock_follow_path_route_backend")
    received = []

    def execute_follow_path(goal_handle):
        received.append(goal_handle.request)
        goal_handle.succeed()
        result = FollowPath.Result()
        if hasattr(result, "error_code"):
            result.error_code = 0
        if hasattr(result, "error_msg"):
            result.error_msg = ""
        return result

    follow_path_server = ActionServer(
        mock_node, FollowPath, "follow_path", execute_follow_path
    )
    client_node = Node("route_capability_test_client")
    client = ActionClient(
        client_node,
        ExecuteWaypointTask,
        "/agt/navigation/execute_waypoint_task",
    )
    executor = MultiThreadedExecutor(num_threads=6)
    for value in (task_server, mock_node, client_node):
        executor.add_node(value)
    thread = threading.Thread(target=executor.spin, daemon=True)
    thread.start()
    try:
        assert client.wait_for_server(timeout_sec=2.0)
        handle = _wait(client.send_goal_async(_formal_request(task, "route_request_1")))
        assert handle.accepted
        wrapped = _wait(handle.get_result_async())

        assert wrapped.status == GoalStatus.STATUS_SUCCEEDED
        assert wrapped.result.success
        assert wrapped.result.error_code == 0
        assert len(received) == 2
        assert [goal.controller_id for goal in received] == [
            "RouteForward",
            "RouteReverse",
        ]
        assert all(goal.path.header.frame_id == "odom" for goal in received)
        # No FollowWaypoints server is created in this test. Success therefore
        # proves the formal public Action selected ROUTE -> FollowPath directly.
    finally:
        executor.shutdown(timeout_sec=2.0)
        thread.join(timeout=2.0)
        follow_path_server.destroy()
        for value in (client_node, mock_node, task_server):
            value.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


def test_task_without_route_binding_preserves_map_follow_waypoints_backend(tmp_path):
    task, _profile, version = _prepare_assets(tmp_path)
    (version / "tasks" / "inspection.route.yaml").unlink()
    if not rclpy.ok():
        rclpy.init()

    task_server = SERVER.NavigationCapabilityServer(
        parameter_overrides=[
            Parameter("require_map", value=False),
            Parameter("require_safety_ready", value=False),
            Parameter("require_localization_valid", value=False),
            Parameter("require_task_readiness", value=False),
            Parameter("maps_root", value=str(tmp_path)),
        ],
    )
    _set_active_map(task_server)
    mock_node = Node("mock_follow_waypoints_map_backend")
    received = []

    def execute_follow_waypoints(goal_handle):
        received.append(goal_handle.request)
        goal_handle.succeed()
        result = FollowWaypoints.Result()
        result.missed_waypoints = []
        return result

    follow_waypoints_server = ActionServer(
        mock_node, FollowWaypoints, "follow_waypoints", execute_follow_waypoints
    )
    client_node = Node("map_capability_test_client")
    client = ActionClient(
        client_node,
        ExecuteWaypointTask,
        "/agt/navigation/execute_waypoint_task",
    )
    executor = MultiThreadedExecutor(num_threads=6)
    for value in (task_server, mock_node, client_node):
        executor.add_node(value)
    thread = threading.Thread(target=executor.spin, daemon=True)
    thread.start()
    try:
        assert client.wait_for_server(timeout_sec=2.0)
        handle = _wait(client.send_goal_async(_formal_request(task, "map_request_1")))
        assert handle.accepted
        wrapped = _wait(handle.get_result_async())

        assert wrapped.status == GoalStatus.STATUS_SUCCEEDED
        assert wrapped.result.success
        assert len(received) == 1
        assert len(received[0].poses) == 1
        assert received[0].poses[0].header.frame_id == "map"
        # No FollowPath server exists. Success proves a task with no execution
        # binding still follows the legacy MAP / FollowWaypoints path.
    finally:
        executor.shutdown(timeout_sec=2.0)
        thread.join(timeout=2.0)
        follow_waypoints_server.destroy()
        for value in (client_node, mock_node, task_server):
            value.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
