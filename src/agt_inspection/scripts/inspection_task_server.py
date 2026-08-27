#!/usr/bin/env python3

from __future__ import annotations

import asyncio
import time
import uuid

import rclpy
from action_msgs.msg import GoalStatus
from nav_msgs.msg import Odometry
from rclpy.action import ActionClient, ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from sensor_msgs.msg import Image

from agt_interfaces.action import (
    ExecuteInspectionTask,
    ExecuteWaypointTask,
    InspectImage,
    MoveGimbal,
)
from agt_interfaces.msg import InspectionStatus
from agt_interfaces.srv import CaptureImage
from agt_inspection.evidence import EvidenceWriter
from agt_inspection.execution import (
    CaptureResult,
    ChildResult,
    InspectionErrorCode,
    InspectionExecutor,
    VisionResult,
)
from agt_inspection.multiview_evidence import InspectionEvidenceStore
from agt_inspection.multiview_execution import MultiviewInspectionExecutor
from agt_inspection.repository import InspectionRepository
from agt_inspection.ros_multiview import RosViewAggregatorRunner, RosViewContextProvider
from agt_inspection.schema import InspectionTaskError


async def _wait_future(future, poll_s: float = 0.01):
    while not future.done():
        await asyncio.sleep(poll_s)
    return future.result()


def _cancel_confirmed(status: int) -> bool:
    return int(status) == int(GoalStatus.STATUS_CANCELED)


class WaypointTaskRunner:
    def __init__(self, node: Node) -> None:
        self._client = ActionClient(
            node,
            ExecuteWaypointTask,
            "/agt/navigation/execute_waypoint_task",
            callback_group=ReentrantCallbackGroup(),
        )
        self._goal_handle = None
        self.map_id = ""
        self.map_version_id = ""
        self.session_id = ""

    def bind(self, map_id: str, map_version_id: str, session_id: str) -> None:
        self.map_id = map_id
        self.map_version_id = map_version_id
        self.session_id = session_id

    async def run(self, point) -> ChildResult:
        if not self._client.wait_for_server(timeout_sec=2.0):
            return ChildResult(False, message="waypoint task action unavailable")
        goal = ExecuteWaypointTask.Goal()
        goal.map_id = self.map_id
        goal.map_version_id = self.map_version_id
        goal.task_group_id = point.navigation.task_group_id
        goal.task_revision = point.navigation.task_revision
        goal.expected_content_sha256 = point.navigation.expected_content_sha256
        goal.loop_count = 1
        goal.client_request_id = f"{self.session_id}:{point.id}:navigation"
        self._goal_handle = await _wait_future(self._client.send_goal_async(goal))
        if self._goal_handle is None or not self._goal_handle.accepted:
            return ChildResult(False, message="waypoint task goal rejected")
        wrapped = await _wait_future(self._goal_handle.get_result_async())
        result = wrapped.result
        canceled = _cancel_confirmed(wrapped.status)
        return ChildResult(
            success=bool(result.success),
            error_code=int(result.error_code),
            message=str(result.message),
            canceled=canceled,
            cancel_confirmed=canceled,
        )

    async def cancel(self) -> bool:
        if self._goal_handle is None:
            return True
        response = await _wait_future(self._goal_handle.cancel_goal_async())
        return bool(response.goals_canceling)


class GimbalRunner:
    def __init__(self, node: Node) -> None:
        self._client = ActionClient(
            node,
            MoveGimbal,
            "/agt/gimbal/move",
            callback_group=ReentrantCallbackGroup(),
        )
        self._goal_handle = None
        self._last_feedback: tuple[float, float] | None = None
        self.session_id = ""

    async def move(self, point) -> ChildResult:
        self._last_feedback = None
        if point.gimbal is None:
            return ChildResult(False, message="gimbal pose is missing")
        if not self._client.wait_for_server(timeout_sec=2.0):
            return ChildResult(False, message="gimbal action unavailable")
        goal = MoveGimbal.Goal()
        goal.request_id = f"{self.session_id}:{point.id}:gimbal"
        goal.pan_rad = point.gimbal.pan_rad
        goal.tilt_rad = point.gimbal.tilt_rad
        goal.timeout_s = point.gimbal.timeout_s
        self._goal_handle = await _wait_future(self._client.send_goal_async(goal))
        if self._goal_handle is None or not self._goal_handle.accepted:
            return ChildResult(False, message="gimbal goal rejected")
        wrapped = await _wait_future(self._goal_handle.get_result_async())
        result = wrapped.result
        canceled = _cancel_confirmed(wrapped.status)
        if bool(result.success):
            self._last_feedback = (
                float(result.final_pan_rad),
                float(result.final_tilt_rad),
            )
        return ChildResult(
            success=bool(result.success),
            error_code=int(result.error_code),
            message=str(result.message),
            canceled=canceled,
            cancel_confirmed=canceled,
        )

    def last_feedback(self) -> tuple[float, float] | None:
        return self._last_feedback

    async def cancel(self) -> bool:
        if self._goal_handle is None:
            return True
        response = await _wait_future(self._goal_handle.cancel_goal_async())
        return bool(response.goals_canceling)


class CameraRunner:
    def __init__(self, node: Node, image_cache: dict[str, Image]) -> None:
        self._image_cache = image_cache
        self._capture_stamps = {}
        self._client = node.create_client(
            CaptureImage,
            "/agt/camera/capture",
            callback_group=ReentrantCallbackGroup(),
        )

    async def capture(self, point, capture_index: int, request_id: str) -> CaptureResult:
        del capture_index
        if not self._client.wait_for_service(timeout_sec=2.0):
            return CaptureResult(False, message="camera service unavailable")
        request = CaptureImage.Request()
        request.request_id = request_id
        request.camera_id = point.camera.camera_id
        response = await _wait_future(self._client.call_async(request))
        if response is None:
            return CaptureResult(False, message="camera service returned no response")
        if response.success:
            self._image_cache[request_id] = response.image
            self._capture_stamps[request_id] = response.image.header.stamp
        return CaptureResult(
            success=bool(response.success),
            error_code=int(response.error_code),
            message=str(response.message),
            image_bytes=bytes(response.image.data),
            image_uri=str(response.image_uri),
        )

    def capture_stamp(self, request_id: str):
        return self._capture_stamps.pop(request_id, None)


class VisionRunner:
    def __init__(self, node: Node, image_cache: dict[str, Image]) -> None:
        self._image_cache = image_cache
        self._client = ActionClient(
            node,
            InspectImage,
            "/agt/vision/inspect",
            callback_group=ReentrantCallbackGroup(),
        )
        self._goal_handle = None

    async def inspect(self, point, capture: CaptureResult, request_id: str) -> VisionResult:
        del capture
        if not self._client.wait_for_server(timeout_sec=2.0):
            return VisionResult(False, message="vision action unavailable")
        image = self._image_cache.get(request_id)
        if image is None:
            return VisionResult(False, message="captured ROS Image is unavailable")

        goal = InspectImage.Goal()
        goal.request_id = request_id
        goal.task_id = point.vision.task_id
        goal.model_profile = point.vision.model_profile
        goal.camera_id = point.camera.camera_id
        goal.image = image
        goal.metadata_json = "{}"
        self._goal_handle = await _wait_future(self._client.send_goal_async(goal))
        if self._goal_handle is None or not self._goal_handle.accepted:
            return VisionResult(False, message="vision goal rejected")
        wrapped = await _wait_future(self._goal_handle.get_result_async())
        result = wrapped.result
        canceled = _cancel_confirmed(wrapped.status)
        self._image_cache.pop(request_id, None)
        return VisionResult(
            success=bool(result.success),
            error_code=int(result.error_code),
            message=str(result.message),
            model_id=str(result.model_id),
            model_version=str(result.model_version),
            inference_time_ms=float(result.inference_time_ms),
            primary_confidence=float(result.primary_confidence),
            result_json=str(result.result_json),
            canceled=canceled,
            cancel_confirmed=canceled,
        )

    async def cancel(self) -> bool:
        if self._goal_handle is None:
            return True
        response = await _wait_future(self._goal_handle.cancel_goal_async())
        return bool(response.goals_canceling)


class ChassisStationaryProvider:
    def __init__(self, node: Node) -> None:
        self._stamp = float("-inf")
        self._linear = 0.0
        self._angular = 0.0
        self._subscription = node.create_subscription(
            Odometry,
            "/agt/chassis/odometry",
            self._callback,
            20,
            callback_group=ReentrantCallbackGroup(),
        )

    def _callback(self, message: Odometry) -> None:
        self._stamp = time.monotonic()
        self._linear = float(message.twist.twist.linear.x)
        self._angular = float(message.twist.twist.angular.z)

    def sample(self) -> tuple[float, float, float]:
        return self._stamp, self._linear, self._angular


class InspectionTaskServer(Node):
    def __init__(self) -> None:
        super().__init__("agt_inspection_task_server")
        self._maps_root = str(
            self.declare_parameter("runtime_maps_root", "runtime/maps").value
        )
        self._evidence_root = str(
            self.declare_parameter("evidence_root", "runtime/inspections").value
        )
        camera_calibration_id = str(
            self.declare_parameter("camera_calibration_id", "").value
        )
        camera_calibration_sha256 = str(
            self.declare_parameter("camera_calibration_sha256", "").value
        )
        localization_timeout_s = float(
            self.declare_parameter("capture_localization_timeout_s", 2.0).value
        )

        image_cache: dict[str, Image] = {}
        self._navigation = WaypointTaskRunner(self)
        self._gimbal = GimbalRunner(self)
        self._camera = CameraRunner(self, image_cache)
        self._vision = VisionRunner(self, image_cache)
        self._stationary = ChassisStationaryProvider(self)
        self._view_aggregator = RosViewAggregatorRunner(self)
        self._view_context = RosViewContextProvider(
            self,
            camera_runner=self._camera,
            gimbal_runner=self._gimbal,
            camera_calibration_id=camera_calibration_id,
            camera_calibration_sha256=camera_calibration_sha256,
            localization_timeout_s=localization_timeout_s,
        )
        self._active_executor = None
        self._active_goal = None
        self._active_task = None
        self._active_session_id = ""
        self._server = ActionServer(
            self,
            ExecuteInspectionTask,
            "/agt/inspection/execute_task",
            execute_callback=self._execute,
            goal_callback=self._goal,
            cancel_callback=self._cancel,
            callback_group=ReentrantCallbackGroup(),
        )

    def _goal(self, request: ExecuteInspectionTask.Goal) -> GoalResponse:
        required = (
            request.map_id,
            request.map_version_id,
            request.inspection_task_id,
            request.expected_content_sha256,
            request.client_request_id,
        )
        if (
            self._active_executor is not None
            or not all(required)
            or request.task_revision == 0
        ):
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def _cancel(self, _goal_handle) -> CancelResponse:
        if self._active_executor is not None:
            self._active_executor.request_cancel()
        return CancelResponse.ACCEPT

    def _publish_stage(self, stage: str, point_id: str) -> None:
        goal_handle = self._active_goal
        task = self._active_task
        if goal_handle is None or task is None:
            return
        feedback = ExecuteInspectionTask.Feedback()
        feedback.state = "RUNNING"
        feedback.current_point = next(
            (
                index
                for index, point in enumerate(task.points, start=1)
                if point.id == point_id
            ),
            0,
        )
        feedback.total_points = len(task.points)
        feedback.point_id = point_id
        feedback.stage = stage
        feedback.status = self._status(
            InspectionStatus.STATE_RUNNING,
            point_id=point_id,
            stage=stage,
            current_point=feedback.current_point,
        )
        goal_handle.publish_feedback(feedback)

    def _status(
        self,
        state: int,
        *,
        error_code: int = 0,
        message: str = "",
        point_id: str = "",
        stage: str = "",
        current_point: int = 0,
    ) -> InspectionStatus:
        status = InspectionStatus()
        status.header.stamp = self.get_clock().now().to_msg()
        status.state = state
        status.session_id = self._active_session_id
        if self._active_task is not None:
            task = self._active_task
            status.inspection_task_id = task.inspection_task_id
            status.task_revision = task.revision
            status.content_sha256 = task.content_sha256
            status.map_id = task.map_binding.map_id
            status.map_version_id = task.map_binding.map_version_id
            status.total_points = len(task.points)
        status.current_point = current_point
        status.point_id = point_id
        status.stage = stage
        status.error_code = int(error_code)
        status.message = message
        return status

    def _execute(self, goal_handle):
        return asyncio.run(self._execute_async(goal_handle))

    async def _execute_async(self, goal_handle):
        request = goal_handle.request
        result = ExecuteInspectionTask.Result()
        self._active_goal = goal_handle
        self._active_session_id = uuid.uuid4().hex
        try:
            repository = InspectionRepository(
                self._maps_root, request.map_id, request.map_version_id
            )
            task = repository.load(
                request.inspection_task_id,
                expected_revision=request.task_revision,
                expected_content_sha256=request.expected_content_sha256,
            )
            self._active_task = task
            self._navigation.bind(
                request.map_id, request.map_version_id, self._active_session_id
            )
            self._gimbal.session_id = self._active_session_id
            self._view_aggregator.session_id = self._active_session_id

            if task.schema_version == 2:
                self._active_executor = MultiviewInspectionExecutor(
                    navigation=self._navigation,
                    gimbal=self._gimbal,
                    camera=self._camera,
                    vision=self._vision,
                    stationary=self._stationary,
                    evidence_store=InspectionEvidenceStore(self._evidence_root),
                    aggregator=self._view_aggregator,
                    context_provider=self._view_context,
                    monotonic=time.monotonic,
                    stage_callback=self._publish_stage,
                )
            else:
                self._active_executor = InspectionExecutor(
                    navigation=self._navigation,
                    gimbal=self._gimbal,
                    camera=self._camera,
                    vision=self._vision,
                    stationary=self._stationary,
                    evidence=EvidenceWriter(self._evidence_root),
                    monotonic=time.monotonic,
                    stage_callback=self._publish_stage,
                )

            execution = await self._active_executor.execute(
                task, session_id=self._active_session_id
            )
            result.success = execution.success
            result.error_code = execution.error_code
            result.session_id = self._active_session_id
            result.evidence_root_uri = execution.evidence_root_uri
            result.message = execution.message
            final_state = (
                InspectionStatus.STATE_CANCELED
                if execution.canceled
                else (
                    InspectionStatus.STATE_SUCCEEDED
                    if execution.success
                    else InspectionStatus.STATE_FAILED
                )
            )
            result.final_status = self._status(
                final_state,
                error_code=execution.error_code,
                message=execution.message,
                current_point=len(task.points) if execution.success else 0,
            )
            if execution.canceled:
                goal_handle.canceled()
            elif execution.success:
                goal_handle.succeed()
            else:
                goal_handle.abort()
            return result
        except InspectionTaskError as exc:
            goal_handle.abort()
            code = (
                InspectionErrorCode.MAP_MISMATCH
                if "map binding" in str(exc)
                else InspectionErrorCode.INVALID_TASK
            )
            result.success = False
            result.error_code = int(code)
            result.session_id = self._active_session_id
            result.message = str(exc)
            result.final_status = self._status(
                InspectionStatus.STATE_FAILED,
                error_code=int(code),
                message=str(exc),
            )
            return result
        except Exception as exc:
            goal_handle.abort()
            result.success = False
            result.error_code = int(InspectionErrorCode.INTERNAL)
            result.session_id = self._active_session_id
            result.message = str(exc)
            result.final_status = self._status(
                InspectionStatus.STATE_FAILED,
                error_code=int(InspectionErrorCode.INTERNAL),
                message=str(exc),
            )
            return result
        finally:
            self._active_executor = None
            self._active_goal = None
            self._active_task = None
            self._active_session_id = ""


def main(args=None) -> None:
    rclpy.init(args=args)
    node = InspectionTaskServer()
    executor = MultiThreadedExecutor(num_threads=6)
    executor.add_node(node)
    try:
        executor.spin()
    finally:
        executor.shutdown()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
