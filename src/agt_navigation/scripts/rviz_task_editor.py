#!/usr/bin/env python3

"""Thin RViz task editor for field acceptance.

RViz clicks only edit an in-memory draft. SAVE/LOAD use the authoritative Task
Registry and START references the exact last-saved TaskGroup revision/hash.
This node intentionally owns no direct Nav2 motion action.
"""

from __future__ import annotations

import json
import math
import uuid

from agt_interfaces.action import ExecuteWaypointTask
from agt_interfaces.srv import GetTaskGroup, PutTaskGroup
from agt_navigation.rviz_task_draft import DraftStateError, RvizTaskDraft
from agt_navigation.task_group import MapBinding, TaskGroup, TaskGroupError
from geometry_msgs.msg import Pose, PoseArray, PoseStamped
from nav_msgs.msg import OccupancyGrid
import rclpy
from rclpy.action import ActionClient
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy
from std_msgs.msg import String
from std_srvs.srv import Trigger
from visualization_msgs.msg import Marker, MarkerArray


def _yaw_from_quaternion(q) -> float:
    norm = math.sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w)
    if not math.isfinite(norm) or norm < 1.0e-9:
        raise ValueError("RViz task point quaternion is invalid")
    return math.atan2(
        2.0 * (q.w * q.z + q.x * q.y),
        1.0 - 2.0 * (q.y * q.y + q.z * q.z),
    )


def _yaw_to_pose(x: float, y: float, yaw: float) -> Pose:
    pose = Pose()
    pose.position.x = float(x)
    pose.position.y = float(y)
    pose.orientation.z = math.sin(float(yaw) * 0.5)
    pose.orientation.w = math.cos(float(yaw) * 0.5)
    return pose


class RvizTaskEditor(Node):
    """RViz draft -> Task Registry -> formal ExecuteWaypointTask adapter."""

    def __init__(self) -> None:
        super().__init__("agt_rviz_task_editor")
        self.map_id = str(self.declare_parameter("map_id", "").value).strip()
        self.map_version_id = str(
            self.declare_parameter("map_version_id", "").value
        ).strip()
        self.map_yaml_sha256 = str(
            self.declare_parameter("map_yaml_sha256", "").value
        ).strip()
        self.map_image_sha256 = str(
            self.declare_parameter("map_image_sha256", "").value
        ).strip()
        self.localization_pcd_sha256 = str(
            self.declare_parameter("localization_pcd_sha256", "").value
        ).strip()
        self.task_group_id = str(
            self.declare_parameter("task_group_id", "field_inspection").value
        ).strip()
        self.task_name = str(
            self.declare_parameter("task_name", "RViz Field Inspection").value
        ).strip()
        self.task_description = str(
            self.declare_parameter(
                "task_description", "RViz field acceptance inspection task"
            ).value
        )
        self.service_timeout_s = float(
            self.declare_parameter("service_timeout_s", 2.0).value
        )
        if not self.map_id or not self.map_version_id or not self.task_group_id:
            raise ValueError("map_id, map_version_id and task_group_id are required")
        if self.service_timeout_s <= 0.0:
            raise ValueError("service_timeout_s must be positive")

        self._draft = RvizTaskDraft()
        self._map: OccupancyGrid | None = None
        self._saved_revision = 0
        self._active_goal = None
        group = ReentrantCallbackGroup()

        transient_qos = QoSProfile(depth=1)
        transient_qos.reliability = ReliabilityPolicy.RELIABLE
        transient_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL

        self._marker_pub = self.create_publisher(
            MarkerArray, "/agt/navigation/task_markers", transient_qos
        )
        self._preview_pub = self.create_publisher(
            PoseArray, "/agt/navigation/waypoint_preview_request", 10
        )
        self._status_pub = self.create_publisher(
            String, "/agt/rviz/task/status", transient_qos
        )
        self.create_subscription(
            PoseStamped,
            "/agt/rviz/task_point",
            self._point_callback,
            10,
            callback_group=group,
        )
        self.create_subscription(
            OccupancyGrid,
            "/map",
            self._map_callback,
            transient_qos,
            callback_group=group,
        )

        self._get_task = self.create_client(
            GetTaskGroup, "/agt/navigation/tasks/get", callback_group=group
        )
        self._put_task = self.create_client(
            PutTaskGroup, "/agt/navigation/tasks/put", callback_group=group
        )
        self._execute_task = ActionClient(
            self,
            ExecuteWaypointTask,
            "/agt/navigation/execute_waypoint_task",
            callback_group=group,
        )

        self.create_service(
            Trigger, "/agt/rviz/task/undo", self._undo, callback_group=group
        )
        self.create_service(
            Trigger, "/agt/rviz/task/clear", self._clear, callback_group=group
        )
        self.create_service(
            Trigger, "/agt/rviz/task/preview", self._preview, callback_group=group
        )
        self.create_service(
            Trigger, "/agt/rviz/task/save", self._save, callback_group=group
        )
        self.create_service(
            Trigger, "/agt/rviz/task/load", self._load, callback_group=group
        )
        self.create_service(
            Trigger, "/agt/rviz/task/start", self._start, callback_group=group
        )

        self._publish_markers()
        self._status("READY", "click RViz Nav Goal to add task points")

    def _status(self, state: str, message: str = "", **extra) -> None:
        output = String()
        output.data = json.dumps(
            {"state": state, "message": message, **extra},
            ensure_ascii=False,
        )
        self._status_pub.publish(output)

    def _map_callback(self, message: OccupancyGrid) -> None:
        if message.header.frame_id not in ("", "map"):
            self._status("MAP_REJECTED", f"map frame is {message.header.frame_id!r}")
            return
        self._map = message

    def _point_callback(self, message: PoseStamped) -> None:
        if message.header.frame_id not in ("", "map"):
            self._status("POINT_REJECTED", "task points must use map frame")
            return
        try:
            yaw = _yaw_from_quaternion(message.pose.orientation)
            point = self._draft.add(
                message.pose.position.x,
                message.pose.position.y,
                yaw,
            )
        except (TypeError, ValueError) as exc:
            self._status("POINT_REJECTED", str(exc))
            return
        self._publish_markers()
        self._status(
            "DRAFT_DIRTY",
            f"added {point.id}",
            point_count=len(self._draft.points),
        )

    def _undo(self, _request, response):
        changed = self._draft.undo()
        self._publish_markers()
        response.success = changed
        response.message = "last point removed" if changed else "draft is empty"
        self._status("DRAFT_DIRTY" if changed else "DRAFT_EMPTY", response.message)
        return response

    def _clear(self, _request, response):
        self._draft.clear()
        self._publish_markers()
        response.success = True
        response.message = "draft cleared"
        self._status("DRAFT_DIRTY", response.message, point_count=0)
        return response

    def _preview(self, _request, response):
        if len(self._draft.points) < 2:
            response.success = False
            response.message = "preview requires at least two points"
            return response
        preview = PoseArray()
        preview.header.frame_id = "map"
        preview.header.stamp = self.get_clock().now().to_msg()
        preview.poses = [
            _yaw_to_pose(point.x, point.y, point.yaw)
            for point in self._draft.points
        ]
        self._preview_pub.publish(preview)
        response.success = True
        response.message = f"preview requested for {len(preview.poses)} points"
        self._status("PREVIEW_REQUESTED", response.message)
        return response

    def _map_binding(self) -> MapBinding:
        if self._map is None:
            raise DraftStateError("global map has not been received")
        info = self._map.info
        if info.resolution <= 0.0 or info.width <= 0 or info.height <= 0:
            raise DraftStateError("global map geometry is invalid")
        origin_yaw = _yaw_from_quaternion(info.origin.orientation)
        return MapBinding(
            map_id=self.map_id,
            map_version_id=self.map_version_id,
            map_yaml_path="",
            map_yaml_sha256=self.map_yaml_sha256,
            map_image_sha256=self.map_image_sha256,
            localization_pcd_sha256=self.localization_pcd_sha256,
            resolution=float(info.resolution),
            width=int(info.width),
            height=int(info.height),
            origin=(
                float(info.origin.position.x),
                float(info.origin.position.y),
                float(origin_yaw),
            ),
        )

    async def _save(self, _request, response):
        if not self._put_task.wait_for_service(timeout_sec=self.service_timeout_s):
            response.success = False
            response.message = "Task Registry put service is unavailable"
            return response
        try:
            task = self._draft.build_task(
                map_binding=self._map_binding(),
                task_group_id=self.task_group_id,
                name=self.task_name,
                description=self.task_description,
                revision=self._saved_revision + 1,
            )
        except (DraftStateError, TaskGroupError, ValueError) as exc:
            response.success = False
            response.message = str(exc)
            return response

        request = PutTaskGroup.Request()
        request.map_id = self.map_id
        request.map_version_id = self.map_version_id
        request.task_group_id = self.task_group_id
        request.expected_revision = int(self._saved_revision)
        request.client_request_id = f"rviz-save-{uuid.uuid4()}"
        request.task_json = json.dumps(
            task.to_dict(), ensure_ascii=False, separators=(",", ":")
        )
        try:
            result = await self._put_task.call_async(request)
        except Exception as exc:  # pragma: no cover - ROS transport boundary
            response.success = False
            response.message = f"Task Registry put failed: {exc}"
            return response
        if not result.success:
            response.success = False
            response.message = result.technical_message or result.operator_message
            self._status(
                "SAVE_FAILED", response.message, blocker_code=result.blocker_code
            )
            return response
        try:
            authoritative = TaskGroup.from_dict(json.loads(result.task_json))
            self._draft.mark_saved(authoritative)
        except (json.JSONDecodeError, TaskGroupError, DraftStateError) as exc:
            response.success = False
            response.message = f"Task Registry returned invalid task JSON: {exc}"
            return response
        self._saved_revision = int(result.revision)
        self._publish_markers()
        response.success = True
        response.message = (
            f"saved {result.task_group_id} revision {result.revision}"
        )
        self._status(
            "SAVED",
            response.message,
            revision=int(result.revision),
            content_sha256=result.content_sha256,
        )
        return response

    async def _load(self, _request, response):
        if not self._get_task.wait_for_service(timeout_sec=self.service_timeout_s):
            response.success = False
            response.message = "Task Registry get service is unavailable"
            return response
        request = GetTaskGroup.Request()
        request.map_id = self.map_id
        request.map_version_id = self.map_version_id
        request.task_group_id = self.task_group_id
        request.task_revision = 0
        try:
            result = await self._get_task.call_async(request)
        except Exception as exc:  # pragma: no cover - ROS transport boundary
            response.success = False
            response.message = f"Task Registry get failed: {exc}"
            return response
        if not result.success:
            response.success = False
            response.message = result.technical_message or result.operator_message
            self._status(
                "LOAD_FAILED", response.message, blocker_code=result.blocker_code
            )
            return response
        try:
            task = TaskGroup.from_dict(json.loads(result.task_json))
            self._draft.load_task(task)
        except (json.JSONDecodeError, TaskGroupError, DraftStateError) as exc:
            response.success = False
            response.message = f"stored task is invalid: {exc}"
            return response
        self._saved_revision = int(result.revision)
        self._publish_markers()
        response.success = True
        response.message = (
            f"loaded {result.task_group_id} revision {result.revision}; START remains manual"
        )
        self._status(
            "LOADED",
            response.message,
            revision=int(result.revision),
            point_count=len(self._draft.points),
        )
        return response

    async def _start(self, _request, response):
        try:
            saved = self._draft.execution_ref()
        except DraftStateError as exc:
            response.success = False
            response.message = str(exc)
            return response
        if self._active_goal is not None:
            response.success = False
            response.message = "an RViz-started task is already active"
            return response
        if not self._execute_task.wait_for_server(timeout_sec=self.service_timeout_s):
            response.success = False
            response.message = "formal ExecuteWaypointTask server is unavailable"
            return response
        goal = ExecuteWaypointTask.Goal()
        goal.map_id = self.map_id
        goal.map_version_id = self.map_version_id
        goal.task_group_id = saved.task_group_id
        goal.task_revision = int(saved.revision)
        goal.expected_content_sha256 = saved.content_sha256
        goal.loop_count = 1
        goal.client_request_id = f"rviz-start-{uuid.uuid4()}"
        try:
            handle = await self._execute_task.send_goal_async(goal)
        except Exception as exc:  # pragma: no cover - ROS transport boundary
            response.success = False
            response.message = f"formal task start failed: {exc}"
            return response
        if not handle.accepted:
            response.success = False
            response.message = "formal Runtime rejected the saved task"
            self._status("START_REJECTED", response.message)
            return response
        self._active_goal = handle
        result_future = handle.get_result_async()
        result_future.add_done_callback(self._task_result)
        response.success = True
        response.message = (
            f"START accepted for {saved.task_group_id} revision {saved.revision}"
        )
        self._status(
            "START_ACCEPTED",
            response.message,
            revision=int(saved.revision),
            content_sha256=saved.content_sha256,
        )
        return response

    def _task_result(self, future) -> None:
        self._active_goal = None
        try:
            wrapped = future.result()
            result = wrapped.result
            self._status(
                "FINISHED" if result.success else "FAILED",
                result.message,
                blocker_code=result.blocker_code,
                session_id=result.session_id,
            )
        except Exception as exc:  # pragma: no cover - ROS transport boundary
            self._status("FAILED", f"formal task result error: {exc}")

    def _publish_markers(self) -> None:
        output = MarkerArray()
        clear = Marker()
        clear.action = Marker.DELETEALL
        output.markers.append(clear)
        stamp = self.get_clock().now().to_msg()
        for index, point in enumerate(self._draft.points):
            arrow = Marker()
            arrow.header.frame_id = "map"
            arrow.header.stamp = stamp
            arrow.ns = "agt_rviz_task_arrows"
            arrow.id = index * 2
            arrow.type = Marker.ARROW
            arrow.action = Marker.ADD
            arrow.pose = _yaw_to_pose(point.x, point.y, point.yaw)
            arrow.pose.position.z = 0.08
            arrow.scale.x = 0.55
            arrow.scale.y = 0.12
            arrow.scale.z = 0.12
            arrow.color.a = 0.95
            arrow.color.r = 0.15
            arrow.color.g = 0.55 if self._draft.dirty else 0.85
            arrow.color.b = 1.0 if self._draft.dirty else 0.2
            output.markers.append(arrow)

            label = Marker()
            label.header.frame_id = "map"
            label.header.stamp = stamp
            label.ns = "agt_rviz_task_labels"
            label.id = index * 2 + 1
            label.type = Marker.TEXT_VIEW_FACING
            label.action = Marker.ADD
            label.pose.position.x = float(point.x)
            label.pose.position.y = float(point.y)
            label.pose.position.z = 0.45
            label.pose.orientation.w = 1.0
            label.scale.z = 0.28
            label.color.a = 1.0
            label.color.r = 1.0
            label.color.g = 1.0
            label.color.b = 1.0
            label.text = point.id
            output.markers.append(label)
        self._marker_pub.publish(output)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = RvizTaskEditor()
    executor = MultiThreadedExecutor(num_threads=4)
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
