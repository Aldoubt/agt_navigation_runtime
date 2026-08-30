from __future__ import annotations

import json
import math
from threading import Event, Lock
from typing import Any, Mapping
from uuid import uuid4

from agt_interfaces.srv import PutTaskGroup
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import ComputePathToPose
from rclpy.action import ActionClient
from rclpy.node import Node

from .task_authoring_model import ActiveTaskSite, build_task_document


class TaskAuthoringRosAdapter:
    """Site-bound task authoring facade over the existing planner and Task Registry."""

    def __init__(
        self,
        node: Node,
        *,
        active_site: ActiveTaskSite,
        timeout_s: float = 5.0,
        planner_timeout_s: float = 5.0,
    ) -> None:
        if timeout_s <= 0.0 or planner_timeout_s <= 0.0:
            raise ValueError("task authoring timeouts must be > 0")
        self._node = node
        self._active_site = active_site
        self._timeout_s = float(timeout_s)
        self._planner_timeout_s = float(planner_timeout_s)
        self._lock = Lock()
        self._planner = ActionClient(
            node,
            ComputePathToPose,
            '/compute_path_to_pose',
        )
        self._put = node.create_client(
            PutTaskGroup,
            '/agt/navigation/tasks/put',
        )

    def _wait_future(self, future: Any, timeout_s: float | None = None) -> Any:
        event = Event()
        future.add_done_callback(lambda _future: event.set())
        if not event.wait(self._timeout_s if timeout_s is None else timeout_s):
            raise TimeoutError("ROS task-authoring future timed out")
        if future.cancelled():
            raise RuntimeError("ROS task-authoring future was canceled")
        exception = future.exception()
        if exception is not None:
            raise RuntimeError(f"ROS task-authoring future failed: {exception}")
        return future.result()

    @staticmethod
    def _pose(x: float, y: float, yaw: float) -> PoseStamped:
        pose = PoseStamped()
        pose.header.frame_id = "map"
        pose.pose.position.x = float(x)
        pose.pose.position.y = float(y)
        half = float(yaw) * 0.5
        pose.pose.orientation.z = math.sin(half)
        pose.pose.orientation.w = math.cos(half)
        return pose

    def context(self) -> Mapping[str, Any]:
        return self._active_site.context()

    def map_image(self) -> bytes:
        try:
            return self._active_site.image_path.read_bytes()
        except OSError as exc:
            raise RuntimeError(f"cannot read active Site map image: {exc}") from exc

    def preview(self, payload: Mapping[str, Any]) -> Mapping[str, Any]:
        self._active_site.validate_payload_identity(payload)
        waypoints = payload.get("waypoints")
        if not isinstance(waypoints, list) or len(waypoints) < 2:
            raise ValueError("planner preview requires at least two waypoints")

        with self._lock:
            if not self._planner.wait_for_server(timeout_sec=self._timeout_s):
                raise RuntimeError("Nav2 ComputePathToPose action server is unavailable")

            start_raw = waypoints[0]
            assert isinstance(start_raw, Mapping)
            start = self._pose(
                float(start_raw["x"]),
                float(start_raw["y"]),
                float(start_raw["yaw"]),
            )
            merged: list[dict[str, float]] = []
            segments: list[dict[str, Any]] = []
            targets: list[tuple[int, Mapping[str, Any], Mapping[str, Any]]] = []
            for index in range(1, len(waypoints)):
                previous_raw = waypoints[index - 1]
                target_raw = waypoints[index]
                assert isinstance(previous_raw, Mapping)
                assert isinstance(target_raw, Mapping)
                targets.append((index, previous_raw, target_raw))
            if bool(payload.get("loop", False)):
                last_raw = waypoints[-1]
                first_raw = waypoints[0]
                assert isinstance(last_raw, Mapping)
                assert isinstance(first_raw, Mapping)
                targets.append((len(waypoints), last_raw, first_raw))

            for _index, previous_raw, target_raw in targets:
                goal_pose = self._pose(
                    float(target_raw["x"]),
                    float(target_raw["y"]),
                    float(target_raw["yaw"]),
                )
                goal = ComputePathToPose.Goal()
                goal.start = start
                goal.goal = goal_pose
                goal.use_start = True
                goal.planner_id = ""
                segment = {
                    "fromId": str(previous_raw["id"]),
                    "toId": str(target_raw["id"]),
                    "ok": False,
                }
                try:
                    goal_handle = self._wait_future(
                        self._planner.send_goal_async(goal),
                        self._planner_timeout_s,
                    )
                    if goal_handle is None or not bool(goal_handle.accepted):
                        segment["reason"] = "planner goal rejected"
                        segments.append(segment)
                        return {"ok": False, "segments": segments, "path": merged}
                    wrapped = self._wait_future(
                        goal_handle.get_result_async(),
                        self._planner_timeout_s,
                    )
                    result = None if wrapped is None else wrapped.result
                    poses = [] if result is None else list(result.path.poses)
                    if not poses:
                        segment["reason"] = "planner returned an empty path"
                        segments.append(segment)
                        return {"ok": False, "segments": segments, "path": merged}
                except TimeoutError as exc:
                    segment["reason"] = str(exc)
                    segments.append(segment)
                    return {"ok": False, "segments": segments, "path": merged}
                except RuntimeError as exc:
                    segment["reason"] = str(exc)
                    segments.append(segment)
                    return {"ok": False, "segments": segments, "path": merged}

                points = [
                    {
                        "x": float(item.pose.position.x),
                        "y": float(item.pose.position.y),
                    }
                    for item in poses
                ]
                if merged and points and merged[-1] == points[0]:
                    points = points[1:]
                merged.extend(points)
                segment["ok"] = True
                segments.append(segment)
                start = poses[-1]

            return {"ok": True, "segments": segments, "path": merged}

    def save(self, task_id: str, payload: Mapping[str, Any]) -> Mapping[str, Any]:
        if str(payload.get("taskId", "")).strip() != task_id:
            raise ValueError("route task id does not match task payload")
        task = build_task_document(self._active_site, payload)
        expected_revision = int(payload.get("expectedRevision", 0))
        request = PutTaskGroup.Request()
        request.map_id = self._active_site.site_id
        request.map_version_id = self._active_site.site_revision
        request.task_group_id = task.task_group_id
        request.expected_revision = expected_revision
        request.client_request_id = f"hmi-{uuid4().hex}"
        request.task_json = json.dumps(
            task.to_dict(),
            ensure_ascii=False,
            indent=2,
            allow_nan=False,
        ) + "\n"

        with self._lock:
            if not self._put.wait_for_service(timeout_sec=self._timeout_s):
                raise RuntimeError("Runtime Task Registry service is unavailable")
            try:
                response = self._wait_future(self._put.call_async(request))
            except TimeoutError as exc:
                raise RuntimeError(str(exc)) from exc
            if response is None:
                raise RuntimeError("Runtime Task Registry returned no response")
            if not bool(response.success):
                detail = str(response.operator_message or response.technical_message or response.blocker_code)
                raise ValueError(detail or "Runtime Task Registry rejected task")
            return {
                "taskId": str(response.task_group_id),
                "state": "SAVED",
                "revision": int(response.revision),
                "contentSha256": str(response.content_sha256),
                "duplicateRequest": bool(response.duplicate_request),
            }
