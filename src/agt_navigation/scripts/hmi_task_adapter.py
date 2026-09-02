#!/usr/bin/env python3
"""Bridge the vendored Qt HMI task-chain messages to the formal Runtime API.

The HMI remains an editor. This node owns the translation to the map-bound
Task Registry and ExecuteWaypointTask action; it never publishes cmd_vel or
calls the camera directly.
"""

from __future__ import annotations

import json
import uuid
from datetime import datetime, timezone

from agt_interfaces.action import ExecuteWaypointTask
from agt_interfaces.msg import MapVersionSummary
from agt_interfaces.srv import PutTaskGroup
from agt_navigation.task_group import MapBinding, TaskGroup, Waypoint
import rclpy
from rclpy.action import ActionClient
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from nav_msgs.msg import OccupancyGrid
from std_msgs.msg import String


class HmiTaskAdapter(Node):
    def __init__(self) -> None:
        super().__init__("agt_hmi_task_adapter")
        self._active: MapVersionSummary | None = None
        self._map: OccupancyGrid | None = None
        self._goal_handle = None
        self._busy = False
        group = ReentrantCallbackGroup()
        self._put = self.create_client(PutTaskGroup, "/agt/navigation/tasks/put", callback_group=group)
        self._execute = ActionClient(self, ExecuteWaypointTask, "/agt/navigation/execute_waypoint_task", callback_group=group)
        self._status = self.create_publisher(String, "/agt/hmi/task_status", 10)
        self.create_subscription(MapVersionSummary, "/agt/maps/active", self._active_callback, 10, callback_group=group)
        self.create_subscription(OccupancyGrid, "/map", self._map_callback, 10, callback_group=group)
        self.create_subscription(String, "/agt/hmi/task_chain", self._task_callback, 10, callback_group=group)
        self.create_subscription(String, "/agt/hmi/task_cancel", self._cancel_callback, 10, callback_group=group)

    def _publish(self, state: str, message: str = "", **extra) -> None:
        value = {"state": state, "message": message, **extra}
        msg = String()
        msg.data = json.dumps(value, ensure_ascii=False)
        self._status.publish(msg)

    def _active_callback(self, message: MapVersionSummary) -> None:
        self._active = message if message.active and message.valid else None

    def _map_callback(self, message: OccupancyGrid) -> None:
        self._map = message

    def _cancel_callback(self, _message: String) -> None:
        if self._goal_handle is not None:
            self._goal_handle.cancel_goal_async()
            self._publish("CANCEL_REQUESTED")
        elif self._busy:
            self._publish("CANCEL_REQUESTED", "任务尚在注册，取消将在注册完成后生效")

    def _task_callback(self, message: String) -> None:
        if self._busy or self._goal_handle is not None:
            self._publish("REJECTED", "已有任务正在执行")
            return
        try:
            document = json.loads(message.data)
            points = document["points"]
            if not isinstance(points, list) or not points:
                raise ValueError("任务至少需要一个点位")
            self._start(document)
        except Exception as exc:
            self._publish("REJECTED", str(exc))

    def _start(self, document: dict) -> None:
        active = self._active
        current_map = self._map
        if active is None or current_map is None:
            self._publish("REJECTED", "没有有效 Active Site")
            return
        loop_count = int(document.get("loop_count", 1))
        if loop_count != 1:
            self._publish("REJECTED", "拍照巡检当前只支持单轮任务，请将 Repeat 设置为 1")
            return
        now = datetime.now(timezone.utc).isoformat(timespec="seconds")
        points = []
        for index, raw in enumerate(document["points"], start=1):
            points.append(Waypoint(
                id=f"P{index:02d}", name=str(raw["name"]),
                x=float(raw["x"]), y=float(raw["y"]), yaw=float(raw["theta"]),
            ))
        binding = MapBinding(
            map_id=active.map_id, map_version_id=active.map_version_id,
            map_yaml_sha256=active.navigation_yaml_sha256,
            map_image_sha256=active.navigation_image_sha256,
            localization_pcd_sha256=active.localization_pcd_sha256,
            resolution=float(current_map.info.resolution),
            width=int(current_map.info.width), height=int(current_map.info.height),
            origin=(float(current_map.info.origin.position.x),
                    float(current_map.info.origin.position.y), 0.0),
        )
        if loop_count <= 0:
            raise ValueError("loop_count must be positive")
        task_group_id = str(document.get("task_group_id", "")).strip()
        if not task_group_id:
            task_group_id = f"hmi_task_{uuid.uuid4().hex}"
        task = TaskGroup(
            task_group_id=task_group_id,
            name="Qt5 HMI Task",
            description="Task submitted by agt_robot_hmi",
            created_at=now, updated_at=now, revision=1,
            map_binding=binding, points=points,
            loop=loop_count > 1, loop_count=loop_count,
        )
        task.content_sha256 = task.canonical_hash()
        if not self._put.wait_for_service(timeout_sec=2.0):
            self._publish("REJECTED", "Task Registry 服务不可用")
            return
        request = PutTaskGroup.Request()
        request.map_id = active.map_id
        request.map_version_id = active.map_version_id
        request.task_group_id = task.task_group_id
        request.expected_revision = 0
        request.client_request_id = f"hmi-put-{uuid.uuid4()}"
        request.task_json = json.dumps(task.to_dict(), ensure_ascii=False, separators=(",", ":"))
        self._busy = True
        future = self._put.call_async(request)
        future.add_done_callback(self._put_done)
        self._publish("REGISTERING", point_count=len(points))

    def _put_done(self, future) -> None:
        try:
            result = future.result()
        except Exception as exc:
            self._busy = False
            self._publish("FAILED", f"Task Registry 调用失败: {exc}")
            return
        if not result.success:
            self._busy = False
            self._publish("REJECTED", result.operator_message or result.technical_message, blocker_code=result.blocker_code)
            return
        goal = ExecuteWaypointTask.Goal()
        goal.map_id = result.map_id
        goal.map_version_id = result.map_version_id
        goal.task_group_id = result.task_group_id
        goal.task_revision = result.revision
        goal.expected_content_sha256 = result.content_sha256
        goal.loop_count = int(json.loads(result.task_json).get("execution", {}).get("loop_count", 1))
        goal.client_request_id = f"hmi-start-{uuid.uuid4()}"
        if not self._execute.wait_for_server(timeout_sec=2.0):
            self._busy = False
            self._publish("FAILED", "ExecuteWaypointTask 服务不可用")
            return
        future = self._execute.send_goal_async(goal, feedback_callback=self._feedback)
        future.add_done_callback(self._goal_response)

    def _goal_response(self, future) -> None:
        try:
            handle = future.result()
        except Exception as exc:
            self._busy = False
            self._publish("FAILED", str(exc))
            return
        if not handle.accepted:
            self._busy = False
            self._publish("REJECTED", "正式导航任务被拒绝")
            return
        self._goal_handle = handle
        self._publish("ACCEPTED")
        result_future = handle.get_result_async()
        result_future.add_done_callback(self._result)

    def _feedback(self, feedback) -> None:
        value = feedback.feedback
        self._publish(value.state, loop_index=value.loop_index, current_waypoint=value.current_waypoint, total_waypoints=value.total_waypoints)

    def _result(self, future) -> None:
        self._goal_handle = None
        self._busy = False
        try:
            result = future.result().result
            self._publish("FINISHED" if result.success else "FAILED", result.message, error_code=result.error_code)
        except Exception as exc:
            self._publish("FAILED", str(exc))


def main(args=None) -> None:
    rclpy.init(args=args)
    node = HmiTaskAdapter()
    executor = MultiThreadedExecutor(num_threads=3)
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        executor.shutdown()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
