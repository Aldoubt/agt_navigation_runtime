from __future__ import annotations

import asyncio
import json
import math
from pathlib import Path
import time
from typing import Any, Mapping

from action_msgs.msg import GoalStatus
from rclpy.action import ActionClient
from rclpy.callback_groups import ReentrantCallbackGroup

from agt_interfaces.action import AggregateInspectionViews
from agt_interfaces.msg import InspectionViewObservation, LocalizationStatus

from .multiview_execution import AggregationResult


async def _wait_future(future, poll_s: float = 0.01):
    while not future.done():
        await asyncio.sleep(poll_s)
    exception = future.exception()
    if exception is not None:
        raise exception
    return future.result()


def _yaw_from_quaternion(quaternion) -> float:
    siny_cosp = 2.0 * (
        float(quaternion.w) * float(quaternion.z)
        + float(quaternion.x) * float(quaternion.y)
    )
    cosy_cosp = 1.0 - 2.0 * (
        float(quaternion.y) * float(quaternion.y)
        + float(quaternion.z) * float(quaternion.z)
    )
    return math.atan2(siny_cosp, cosy_cosp)


class RosViewContextProvider:
    """Capture-time map pose + gimbal/camera calibration context for evidence."""

    def __init__(
        self,
        node,
        *,
        camera_runner,
        gimbal_runner,
        camera_calibration_id: str,
        camera_calibration_sha256: str,
        localization_timeout_s: float = 2.0,
    ) -> None:
        self._node = node
        self._camera_runner = camera_runner
        self._gimbal_runner = gimbal_runner
        self._camera_calibration_id = str(camera_calibration_id)
        self._camera_calibration_sha256 = str(camera_calibration_sha256)
        self._localization_timeout_s = max(float(localization_timeout_s), 0.1)
        self._localization = None
        self._localization_seen = float("-inf")
        self._subscription = node.create_subscription(
            LocalizationStatus,
            "/agt/localization/status",
            self._localization_callback,
            10,
            callback_group=ReentrantCallbackGroup(),
        )

    def _localization_callback(self, message: LocalizationStatus) -> None:
        self._localization = message
        self._localization_seen = time.monotonic()

    def _accepted_localization(self):
        message = self._localization
        fresh = time.monotonic() - self._localization_seen <= self._localization_timeout_s
        if not (
            fresh
            and message is not None
            and message.state == LocalizationStatus.STATE_TRACKING
            and message.pose_valid
            and message.localization_accepted
            and message.error_code == LocalizationStatus.ERROR_NONE
            and not message.status_stale
        ):
            raise ValueError("capture-time accepted localization pose is unavailable or stale")
        return message

    def snapshot(self, task, point, view, request_id: str) -> Mapping[str, Any]:
        localization = self._accepted_localization()
        pose_message = localization.global_pose
        pose = pose_message.pose.pose
        covariance = list(pose_message.pose.covariance)
        stamp = self._camera_runner.capture_stamp(request_id)
        if stamp is None:
            stamp = self._node.get_clock().now().to_msg()

        gimbal = self._gimbal_runner.last_feedback()
        if gimbal is None:
            gimbal_pan = view.gimbal.pan_rad
            gimbal_tilt = view.gimbal.tilt_rad
            gimbal_feedback_valid = False
        else:
            gimbal_pan, gimbal_tilt = gimbal
            gimbal_feedback_valid = True

        warnings = []
        if not self._camera_calibration_id or not self._camera_calibration_sha256:
            warnings.append("CAMERA_CALIBRATION_IDENTITY_MISSING")

        return {
            "capture_stamp": f"{int(stamp.sec)}.{int(stamp.nanosec):09d}",
            "robot_pose_map": {
                "frame_id": pose_message.header.frame_id or "map",
                "x": float(pose.position.x),
                "y": float(pose.position.y),
                "z": float(pose.position.z),
                "yaw": _yaw_from_quaternion(pose.orientation),
                "covariance": covariance,
            },
            "gimbal": {
                "pan_rad": float(gimbal_pan),
                "tilt_rad": float(gimbal_tilt),
                "feedback_valid": gimbal_feedback_valid,
            },
            "camera": {
                "camera_id": point.camera.camera_id,
                "calibration_id": self._camera_calibration_id,
                "calibration_sha256": self._camera_calibration_sha256,
            },
            "camera_pose_valid": False,
            "camera_pose_map": {},
            "warnings": warnings,
        }


class RosViewAggregatorRunner:
    def __init__(self, node, *, server_wait_timeout_s: float = 2.0) -> None:
        self._node = node
        self._client = ActionClient(
            node,
            AggregateInspectionViews,
            "/agt/vision/aggregate_views",
            callback_group=ReentrantCallbackGroup(),
        )
        self._server_wait_timeout_s = max(float(server_wait_timeout_s), 0.1)
        self._goal_handle = None
        self.session_id = ""

    @staticmethod
    def _stamp_from_text(value: object):
        sec = 0
        nanosec = 0
        try:
            text = str(value)
            whole, fraction = text.split(".", 1)
            sec = int(whole)
            nanosec = int((fraction + "000000000")[:9])
        except (ValueError, TypeError):
            pass
        return sec, nanosec

    @staticmethod
    def _observation_message(task, point, value: Mapping[str, Any]) -> InspectionViewObservation:
        message = InspectionViewObservation()
        message.view_id = str(value.get("view_id", ""))
        message.capture_id = str(value.get("capture_id", ""))
        sec, nanosec = RosViewAggregatorRunner._stamp_from_text(value.get("capture_stamp", ""))
        message.capture_stamp.sec = sec
        message.capture_stamp.nanosec = nanosec
        message.map_id = task.map_binding.map_id
        message.map_version_id = task.map_binding.map_version_id
        message.point_id = point.id

        camera = dict(value.get("camera", {}))
        message.camera_id = str(camera.get("camera_id", point.camera.camera_id))
        message.camera_calibration_id = str(camera.get("calibration_id", ""))
        message.camera_calibration_sha256 = str(camera.get("calibration_sha256", ""))

        pose = dict(value.get("robot_pose_map", {}))
        message.robot_pose_map.header.frame_id = str(pose.get("frame_id", "map"))
        message.robot_pose_map.header.stamp = message.capture_stamp
        message.robot_pose_map.pose.pose.position.x = float(pose.get("x", 0.0))
        message.robot_pose_map.pose.pose.position.y = float(pose.get("y", 0.0))
        message.robot_pose_map.pose.pose.position.z = float(pose.get("z", 0.0))
        yaw = float(pose.get("yaw", 0.0))
        message.robot_pose_map.pose.pose.orientation.z = math.sin(yaw / 2.0)
        message.robot_pose_map.pose.pose.orientation.w = math.cos(yaw / 2.0)
        covariance = pose.get("covariance", [])
        if isinstance(covariance, list) and len(covariance) == 36:
            message.robot_pose_map.pose.covariance = [float(item) for item in covariance]

        message.camera_pose_valid = bool(value.get("camera_pose_valid", False))
        if message.camera_pose_valid:
            camera_pose = dict(value.get("camera_pose_map", {}))
            message.camera_pose_map.header.frame_id = str(camera_pose.get("frame_id", "map"))
            message.camera_pose_map.header.stamp = message.capture_stamp
            message.camera_pose_map.pose.position.x = float(camera_pose.get("x", 0.0))
            message.camera_pose_map.pose.position.y = float(camera_pose.get("y", 0.0))
            message.camera_pose_map.pose.position.z = float(camera_pose.get("z", 0.0))
            camera_yaw = float(camera_pose.get("yaw", 0.0))
            message.camera_pose_map.pose.orientation.z = math.sin(camera_yaw / 2.0)
            message.camera_pose_map.pose.orientation.w = math.cos(camera_yaw / 2.0)

        gimbal = dict(value.get("gimbal", {}))
        message.gimbal_pan_rad = float(gimbal.get("pan_rad", 0.0))
        message.gimbal_tilt_rad = float(gimbal.get("tilt_rad", 0.0))
        message.gimbal_feedback_valid = bool(gimbal.get("feedback_valid", False))

        vision = dict(value.get("vision", {}))
        message.raw_instance_count = int(vision.get("raw_count", 0))
        message.model_id = str(vision.get("model_id", ""))
        message.model_version = str(vision.get("model_version", ""))
        message.inference_time_ms = float(vision.get("inference_time_ms", 0.0))

        evidence = dict(value.get("evidence", {}))
        message.image_uri = str(evidence.get("image", ""))
        message.overlay_uri = str(evidence.get("overlay", ""))
        message.mask_uri = str(evidence.get("mask", ""))
        message.single_view_result_uri = str(value.get("single_view_result_uri", ""))
        if not message.image_uri and message.single_view_result_uri:
            message.image_uri = str(Path(message.single_view_result_uri).with_name("original.bin"))
        message.single_view_result_json = json.dumps(
            vision.get("result_json", {}), ensure_ascii=False, separators=(",", ":")
        )
        return message

    async def aggregate(self, task, point, observations) -> AggregationResult:
        if self._goal_handle is not None:
            return AggregationResult(False, error_code=1, message="aggregation goal already active")
        if not self._client.wait_for_server(timeout_sec=self._server_wait_timeout_s):
            return AggregationResult(False, error_code=1, message="view aggregator action unavailable")
        if point.aggregation is None:
            return AggregationResult(False, error_code=1, message="aggregation policy is missing")

        goal = AggregateInspectionViews.Goal()
        goal.request_id = f"{self.session_id}:{point.id}:aggregate"
        goal.session_id = self.session_id
        goal.point_id = point.id
        goal.map_id = task.map_binding.map_id
        goal.map_version_id = task.map_binding.map_version_id
        goal.count_target = task.count_target
        goal.aggregation_profile = point.aggregation.aggregation_profile
        goal.views = [self._observation_message(task, point, item) for item in observations]

        handle = await _wait_future(self._client.send_goal_async(goal))
        if handle is None or not handle.accepted:
            return AggregationResult(False, error_code=1, message="view aggregator goal rejected")
        self._goal_handle = handle
        try:
            wrapped = await _wait_future(handle.get_result_async())
            result = wrapped.result
            canceled = int(wrapped.status) == int(GoalStatus.STATUS_CANCELED)
            return AggregationResult(
                success=bool(result.success),
                error_code=int(result.error_code),
                message=str(result.message),
                aggregator_id=str(result.aggregator_id),
                aggregator_version=str(result.aggregator_version),
                raw_instance_count=int(result.raw_instance_count),
                unique_instance_count=int(result.unique_instance_count),
                ambiguous_instance_count=int(result.ambiguous_instance_count),
                association_confidence=float(result.association_confidence),
                result_json=str(result.result_json),
                canceled=canceled,
                cancel_confirmed=canceled,
            )
        finally:
            self._goal_handle = None

    async def cancel(self) -> bool:
        handle = self._goal_handle
        if handle is None:
            return True
        response = await _wait_future(handle.cancel_goal_async())
        return bool(response.goals_canceling)
