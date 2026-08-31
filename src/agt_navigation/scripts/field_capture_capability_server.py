#!/usr/bin/env python3

"""Sequential field inspection capability for formal waypoint tasks.

The server deliberately keeps navigation, capture and evidence as separate
outcomes:
- Nav2 / localization / safety failures stop the task immediately.
- Capture failures are recorded per waypoint and, by default, stop the task
  after the configured retry budget is exhausted.
- The overall inspection action still fails when one or more captures fail.

Task Registry, Site binding and runtime readiness validation stay owned by the
existing NavigationCapabilityServer.
"""

from __future__ import annotations

import asyncio
import copy
import importlib.util
import math
from pathlib import Path

from action_msgs.msg import GoalStatus
from agt_interfaces.srv import CaptureImage
from agt_navigation.field_capture import FieldCaptureRun, Pose2D
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import NavigateToPose
import rclpy
from rclpy.action import ActionClient
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor


_CAPABILITY_SCRIPT = Path(__file__).with_name("navigation_capability_server.py")
_SPEC = importlib.util.spec_from_file_location(
    "agt_navigation_capability_base", _CAPABILITY_SCRIPT
)
_CAP = importlib.util.module_from_spec(_SPEC)
_SPEC.loader.exec_module(_CAP)
_BASE = _CAP._BASE

ERROR_CAPTURE_UNAVAILABLE = 45
ERROR_CAPTURE_FAILED = 46
ERROR_RETURN_HOME_FAILED = 47


class FieldCaptureCapabilityServer(_CAP.NavigationCapabilityServer):
    """Execute waypoint -> capture sequentially, then return to HOME."""

    def __init__(self, field_pose_provider=None, **kwargs):
        self._field_pose_provider_override = field_pose_provider
        self._latest_global_pose = None
        super().__init__(**kwargs)

        self.field_capture_enabled = bool(
            self.declare_parameter("field_capture_enabled", True).value
        )
        root_value = str(self.declare_parameter("field_capture_root", "").value).strip()
        self.field_capture_root = (
            Path(root_value).expanduser()
            if root_value
            else self.runtime_dir / "inspection_runs"
        )
        self.field_capture_backend = str(
            self.declare_parameter("field_capture_backend", "placeholder").value
        ).strip().lower()
        self.field_capture_service = str(
            self.declare_parameter(
                "field_capture_service", "/agt/camera/capture"
            ).value
        ).strip()
        self.field_capture_camera_id = str(
            self.declare_parameter(
                "field_capture_camera_id", "inspection_camera"
            ).value
        ).strip()
        self.field_capture_retry_count = int(
            self.declare_parameter("field_capture_retry_count", 1).value
        )
        self.field_capture_continue_on_failure = bool(
            self.declare_parameter(
                "field_capture_continue_on_failure", False
            ).value
        )
        self.field_capture_settle_sec = float(
            self.declare_parameter("field_capture_settle_sec", 0.0).value
        )
        self.field_capture_service_timeout = float(
            self.declare_parameter("field_capture_service_timeout", 2.0).value
        )

        if self.field_capture_backend not in ("placeholder", "service"):
            raise ValueError(
                "field_capture_backend must be 'placeholder' or 'service'"
            )
        if self.field_capture_retry_count < 0:
            raise ValueError("field_capture_retry_count must be >= 0")
        if self.field_capture_settle_sec < 0.0:
            raise ValueError("field_capture_settle_sec must be >= 0")
        if self.field_capture_service_timeout <= 0.0:
            raise ValueError("field_capture_service_timeout must be positive")
        if self.field_capture_backend == "service" and not self.field_capture_camera_id:
            raise ValueError("field_capture_camera_id is required for service capture")

        field_group = ReentrantCallbackGroup()
        self._field_nav2 = ActionClient(
            self, NavigateToPose, "navigate_to_pose", callback_group=field_group
        )
        self._field_capture_client = self.create_client(
            CaptureImage,
            self.field_capture_service,
            callback_group=field_group,
        )

    def _localization_callback(self, message):
        super()._localization_callback(message)
        with self._lock:
            self._latest_global_pose = copy.deepcopy(message.global_pose)

    def _current_pose_stamped(self) -> PoseStamped:
        if self._field_pose_provider_override is not None:
            value = self._field_pose_provider_override()
            if not isinstance(value, PoseStamped):
                raise RuntimeError(
                    "field_pose_provider must return geometry_msgs/PoseStamped"
                )
            pose = copy.deepcopy(value)
        else:
            with self._lock:
                global_pose = copy.deepcopy(self._latest_global_pose)
            if global_pose is None:
                raise RuntimeError("accepted localization pose is not available")
            pose = PoseStamped()
            pose.header = global_pose.header
            pose.pose = global_pose.pose.pose

        if pose.header.frame_id != "map":
            raise RuntimeError(
                f"field capture pose frame must be map, got {pose.header.frame_id!r}"
            )
        q = pose.pose.orientation
        norm = math.sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w)
        if norm < 1.0e-9:
            raise RuntimeError("field capture pose quaternion is invalid")
        return pose

    @staticmethod
    def _pose2d(pose: PoseStamped) -> Pose2D:
        q = pose.pose.orientation
        yaw = math.atan2(
            2.0 * (q.w * q.z + q.x * q.y),
            1.0 - 2.0 * (q.y * q.y + q.z * q.z),
        )
        return Pose2D(
            float(pose.pose.position.x),
            float(pose.pose.position.y),
            float(yaw),
        )

    @staticmethod
    def _point_pose2d(point) -> Pose2D:
        return Pose2D(float(point.x), float(point.y), float(point.theta))

    def _capture_service_ready(self) -> bool:
        if self.field_capture_backend == "placeholder":
            return True
        return self._field_capture_client.wait_for_service(
            timeout_sec=self.field_capture_service_timeout
        )

    async def _capture(
        self, run: FieldCaptureRun, index: int, waypoint_id: str
    ):
        point_dir = run.point_dir(index, waypoint_id)
        if self.field_capture_backend == "placeholder":
            return (
                run.write_placeholder_image(point_dir),
                "placeholder capture; replace field_capture_backend with service when camera is connected",
            )

        request = CaptureImage.Request()
        request.request_id = f"{run.session_id}-P{index:02d}"
        request.camera_id = self.field_capture_camera_id
        response = await self._field_capture_client.call_async(request)
        if not response.success:
            raise RuntimeError(
                response.message
                or f"CaptureImage failed with error_code={response.error_code}"
            )
        if response.image_uri:
            path = run.copy_local_image_uri(point_dir, response.image_uri)
        else:
            image = response.image
            path = run.write_sensor_image(
                point_dir,
                width=image.width,
                height=image.height,
                step=image.step,
                encoding=image.encoding,
                data=image.data,
            )
        return path, str(response.message)

    async def _navigate(self, pose: PoseStamped):
        goal = NavigateToPose.Goal()
        goal.pose = copy.deepcopy(pose)
        goal.pose.header.stamp = self.get_clock().now().to_msg()
        child = await self._field_nav2.send_goal_async(goal)
        if not child.accepted:
            return False, "Nav2 rejected NavigateToPose goal"
        with self._lock:
            self._child_goal_handle = child
        wrapped = await child.get_result_async()
        with self._lock:
            self._child_goal_handle = None
        if wrapped.status != GoalStatus.STATUS_SUCCEEDED:
            return False, f"NavigateToPose failed with status {wrapped.status}"
        return True, ""

    def _reject_field_goal(self, goal_handle, result, problem, run=None):
        self.session.transition(
            _BASE.NavigationSessionStatus.STATE_REJECTED,
            problem=_BASE.Blocker(
                problem.code,
                problem.operator_message,
                problem.technical_message,
                self._error_code(problem),
            ),
            success=False,
        )
        goal_handle.abort()
        self._publish_status(
            "REJECTED", backend="FIELD_CAPTURE", reason=problem.technical_message
        )
        if run is not None:
            run.finish(
                success=False,
                return_home_success=False,
                completed_waypoints=0,
                total_waypoints=0,
                message=problem.technical_message,
            )
        self._remember_request()
        return self._finish(result, False, problem)

    def _fail_field_goal(
        self,
        goal_handle,
        result,
        problem,
        *,
        run,
        completed_waypoints,
        total_waypoints,
        return_home_success=False,
        message=None,
    ):
        if self.session.status.state not in (
            _BASE.NavigationSessionStatus.STATE_FAILED,
            _BASE.NavigationSessionStatus.STATE_CANCELED,
        ):
            self.session.transition(
                _BASE.NavigationSessionStatus.STATE_FAILED,
                problem=_BASE.Blocker(
                    problem.code,
                    problem.operator_message,
                    problem.technical_message,
                    self._error_code(problem),
                ),
                success=False,
            )
        run.finish(
            success=False,
            return_home_success=return_home_success,
            completed_waypoints=completed_waypoints,
            total_waypoints=total_waypoints,
            message=message or problem.technical_message,
        )
        goal_handle.abort()
        self._publish_status(
            "FAILED",
            backend="FIELD_CAPTURE",
            reason=problem.technical_message,
            images_dir=str(run.run_dir),
        )
        self._remember_request()
        return self._finish(
            result,
            False,
            problem,
            message=(
                message
                or f"{problem.technical_message}; images saved to: {run.run_dir}"
            ),
        )

    def _record_navigation_failure(self, run, index, point, message):
        run.record_waypoint(
            index=index,
            waypoint_id=point.name,
            target=self._point_pose2d(point),
            capture=None,
            image_path=None,
            navigation_success=False,
            navigation_message=message,
            capture_success=False,
            capture_retry_count=0,
            capture_message="not attempted because navigation failed",
        )

    def _capture_pose_after_failure(self):
        try:
            return self._pose2d(self._current_pose_stamped())
        except RuntimeError as exc:
            self.get_logger().warning(
                f"cannot attach capture pose to failed capture evidence: {exc}"
            )
            return None

    async def _execute(self, goal_handle):
        if not self.field_capture_enabled or not self._is_formal_goal(
            goal_handle.request
        ):
            return await super()._execute(goal_handle)
        return await self._execute_field_capture(goal_handle)

    async def _execute_field_capture(self, goal_handle):
        result = _BASE.ExecuteWaypointTask.Result()
        claimed_request = False
        run = None
        completed = 0
        total = 0
        capture_failures: list[str] = []
        try:
            try:
                self._claim_request(goal_handle.request)
                claimed_request = True
            except _BASE.DuplicateRequest:
                goal_handle.succeed()
                duplicate = _BASE.blocker(
                    "DUPLICATE_REQUEST", "client_request_id was already handled"
                )
                return self._finish(
                    result,
                    self.session.status.success,
                    duplicate,
                    duplicate=True,
                )
            except _BASE.Blocked as exc:
                goal_handle.abort()
                return self._finish(result, False, exc.problem)

            self._start_session(goal_handle.request, None)
            if int(goal_handle.request.loop_count) != 1:
                return self._reject_field_goal(
                    goal_handle,
                    result,
                    _BASE.blocker(
                        "INVALID_REQUEST",
                        "FIELD_CAPTURE executes one finite inspection pass; loop_count must be 1",
                    ),
                )

            try:
                points, task_binding, _task = self._load_points_and_binding(
                    goal_handle.request
                )
            except _BASE.Blocked as exc:
                return self._reject_field_goal(goal_handle, result, exc.problem)
            total = len(points)

            current_map = self._map
            if self.require_map and current_map is None:
                return self._reject_field_goal(
                    goal_handle,
                    result,
                    _BASE.blocker(
                        "NO_ACTIVE_MAP", "global occupancy map has not been received"
                    ),
                )
            if current_map is not None:
                outside = [
                    point.name
                    for point in points
                    if not _BASE.point_inside_map(point, current_map.info)
                ]
                if outside:
                    return self._reject_field_goal(
                        goal_handle,
                        result,
                        _BASE.blocker(
                            "MAP_GEOMETRY_MISMATCH",
                            "waypoints outside current map: " + ", ".join(outside),
                            error_code=_BASE.ERROR_POINT_OUTSIDE_MAP,
                        ),
                    )

            binding_problem = self._validate_task_binding(task_binding, current_map)
            if binding_problem is not None:
                return self._reject_field_goal(
                    goal_handle, result, binding_problem
                )
            gate_problem = self._runtime_gate_problem()
            if gate_problem is not None:
                return self._reject_field_goal(goal_handle, result, gate_problem)
            if not self._field_nav2.wait_for_server(
                timeout_sec=self.nav2_wait_timeout
            ):
                return self._reject_field_goal(
                    goal_handle,
                    result,
                    _BASE.blocker(
                        "NAV2_UNAVAILABLE",
                        "Nav2 NavigateToPose action is unavailable",
                        error_code=_BASE.ERROR_NAV2_UNAVAILABLE,
                    ),
                )
            if not self._capture_service_ready():
                return self._reject_field_goal(
                    goal_handle,
                    result,
                    _BASE.blocker(
                        "CAPTURE_UNAVAILABLE",
                        f"capture service {self.field_capture_service} is unavailable; no motion started",
                        error_code=ERROR_CAPTURE_UNAVAILABLE,
                    ),
                )

            try:
                home_pose = self._current_pose_stamped()
            except RuntimeError as exc:
                return self._reject_field_goal(
                    goal_handle,
                    result,
                    _BASE.blocker(
                        "LOCALIZATION_NOT_READY",
                        str(exc),
                        error_code=_BASE.ERROR_LOCALIZATION_NOT_READY,
                    ),
                )
            home = self._pose2d(home_pose)

            run = FieldCaptureRun(
                self.field_capture_root,
                session_id=self.session.status.session_id,
                map_id=str(goal_handle.request.map_id),
                map_version_id=str(goal_handle.request.map_version_id),
                task_group_id=str(goal_handle.request.task_group_id),
            )
            run.start(home)
            self.session.transition(
                _BASE.NavigationSessionStatus.STATE_ACCEPTED,
                total_waypoints=total,
            )
            self._publish_status(
                "ACCEPTED",
                backend="FIELD_CAPTURE",
                total_waypoints=total,
                images_dir=str(run.run_dir),
            )

            for index, point in enumerate(points, start=1):
                if goal_handle.is_cancel_requested:
                    self.session.transition(
                        _BASE.NavigationSessionStatus.STATE_CANCELED, success=False
                    )
                    run.finish(
                        success=False,
                        return_home_success=False,
                        completed_waypoints=completed,
                        total_waypoints=total,
                        message="task canceled",
                    )
                    goal_handle.canceled()
                    self._remember_request()
                    return self._finish(
                        result,
                        False,
                        _BASE.blocker("CANCELED", "task canceled"),
                        message=f"task canceled; images saved to: {run.run_dir}",
                    )

                gate_problem = self._runtime_gate_problem()
                if gate_problem is not None:
                    return self._fail_field_goal(
                        goal_handle,
                        result,
                        gate_problem,
                        run=run,
                        completed_waypoints=completed,
                        total_waypoints=total,
                    )

                current_index = index - 1
                self.session.transition(
                    _BASE.NavigationSessionStatus.STATE_RUNNING,
                    loop_index=0,
                    current_waypoint=current_index,
                    total_waypoints=total,
                )
                goal_handle.publish_feedback(
                    self._feedback("NAVIGATING", 0, current_index, total)
                )
                self._publish_status(
                    "NAVIGATING",
                    backend="FIELD_CAPTURE",
                    waypoint_id=point.name,
                    waypoint_index=index,
                    total_waypoints=total,
                )
                target_pose = self._pose(point, self.get_clock().now().to_msg())
                nav_success, nav_message = await self._navigate(target_pose)

                if goal_handle.is_cancel_requested:
                    self.session.transition(
                        _BASE.NavigationSessionStatus.STATE_CANCELED, success=False
                    )
                    run.finish(
                        success=False,
                        return_home_success=False,
                        completed_waypoints=completed,
                        total_waypoints=total,
                        message="task canceled",
                    )
                    goal_handle.canceled()
                    self._remember_request()
                    return self._finish(
                        result,
                        False,
                        _BASE.blocker("CANCELED", "task canceled"),
                        message=f"task canceled; images saved to: {run.run_dir}",
                    )

                if not nav_success:
                    self._record_navigation_failure(
                        run, index, point, nav_message
                    )
                    return self._fail_field_goal(
                        goal_handle,
                        result,
                        _BASE.blocker(
                            "NAV2_FAILED",
                            nav_message,
                            error_code=_BASE.ERROR_NAV2_FAILED,
                        ),
                        run=run,
                        completed_waypoints=completed,
                        total_waypoints=total,
                    )

                gate_problem = self._runtime_gate_problem()
                if gate_problem is not None:
                    return self._fail_field_goal(
                        goal_handle,
                        result,
                        gate_problem,
                        run=run,
                        completed_waypoints=completed,
                        total_waypoints=total,
                    )

                self._publish_status(
                    "ARRIVED",
                    backend="FIELD_CAPTURE",
                    waypoint_id=point.name,
                    waypoint_index=index,
                )
                if self.field_capture_settle_sec > 0.0:
                    await asyncio.sleep(self.field_capture_settle_sec)
                self._publish_status(
                    "CAPTURING",
                    backend="FIELD_CAPTURE",
                    waypoint_id=point.name,
                    waypoint_index=index,
                )

                image_path = None
                capture_message = ""
                capture_error = ""
                retries_used = 0
                for attempt in range(self.field_capture_retry_count + 1):
                    retries_used = attempt
                    try:
                        image_path, capture_message = await self._capture(
                            run, index, point.name
                        )
                        capture_error = ""
                        break
                    except Exception as exc:
                        capture_error = str(exc)
                        self.get_logger().warning(
                            f"capture {point.name} attempt {attempt + 1} failed: {exc}"
                        )

                if image_path is None:
                    capture_pose = self._capture_pose_after_failure()
                    run.record_waypoint(
                        index=index,
                        waypoint_id=point.name,
                        target=self._point_pose2d(point),
                        capture=capture_pose,
                        image_path=None,
                        navigation_success=True,
                        navigation_message="arrived",
                        capture_success=False,
                        capture_retry_count=retries_used,
                        capture_message=capture_error,
                    )
                    completed = index
                    capture_failures.append(point.name)
                    self._publish_status(
                        "WAYPOINT_CAPTURE_FAILED",
                        backend="FIELD_CAPTURE",
                        waypoint_id=point.name,
                        waypoint_index=index,
                        capture_error=capture_error,
                    )
                    if self.field_capture_continue_on_failure:
                        continue
                    return self._fail_field_goal(
                        goal_handle,
                        result,
                        _BASE.blocker(
                            "CAPTURE_FAILED",
                            f"capture failed at {point.name}: {capture_error}",
                            error_code=ERROR_CAPTURE_FAILED,
                        ),
                        run=run,
                        completed_waypoints=completed,
                        total_waypoints=total,
                    )

                try:
                    capture_pose = self._current_pose_stamped()
                except RuntimeError as exc:
                    return self._fail_field_goal(
                        goal_handle,
                        result,
                        _BASE.blocker(
                            "LOCALIZATION_NOT_READY",
                            str(exc),
                            error_code=_BASE.ERROR_LOCALIZATION_NOT_READY,
                        ),
                        run=run,
                        completed_waypoints=completed,
                        total_waypoints=total,
                    )
                run.record_waypoint(
                    index=index,
                    waypoint_id=point.name,
                    target=self._point_pose2d(point),
                    capture=self._pose2d(capture_pose),
                    image_path=image_path,
                    navigation_success=True,
                    navigation_message="arrived",
                    capture_success=True,
                    capture_retry_count=retries_used,
                    capture_message=capture_message,
                )
                completed = index
                self._publish_status(
                    "WAYPOINT_SUCCESS",
                    backend="FIELD_CAPTURE",
                    waypoint_id=point.name,
                    waypoint_index=index,
                    image=str(image_path),
                )

            gate_problem = self._runtime_gate_problem()
            if gate_problem is not None:
                return self._fail_field_goal(
                    goal_handle,
                    result,
                    gate_problem,
                    run=run,
                    completed_waypoints=completed,
                    total_waypoints=total,
                )

            self._publish_status(
                "RETURNING_HOME",
                backend="FIELD_CAPTURE",
                completed_waypoints=completed,
                total_waypoints=total,
            )
            nav_success, nav_message = await self._navigate(home_pose)
            if not nav_success:
                return self._fail_field_goal(
                    goal_handle,
                    result,
                    _BASE.blocker(
                        "RETURN_HOME_FAILED",
                        nav_message,
                        error_code=ERROR_RETURN_HOME_FAILED,
                    ),
                    run=run,
                    completed_waypoints=completed,
                    total_waypoints=total,
                    return_home_success=False,
                )

            if capture_failures:
                capture_summary = (
                    f"field capture route completed; capture_failures={len(capture_failures)}; "
                    f"failed_waypoints={','.join(capture_failures)}; return_home=SUCCESS; "
                    f"images saved to: {run.run_dir}"
                )
                problem = _BASE.blocker(
                    "CAPTURE_FAILED",
                    f"{len(capture_failures)} waypoint capture(s) failed",
                    error_code=ERROR_CAPTURE_FAILED,
                )
                return self._fail_field_goal(
                    goal_handle,
                    result,
                    problem,
                    run=run,
                    completed_waypoints=completed,
                    total_waypoints=total,
                    return_home_success=True,
                    message=capture_summary,
                )

            run.finish(
                success=True,
                return_home_success=True,
                completed_waypoints=completed,
                total_waypoints=total,
                message="field capture mission completed",
            )
            self.session.transition(
                _BASE.NavigationSessionStatus.STATE_SUCCEEDED,
                loop_index=0,
                current_waypoint=total,
                total_waypoints=total,
                success=True,
            )
            goal_handle.succeed()
            self._publish_status(
                "SUCCEEDED",
                backend="FIELD_CAPTURE",
                waypoints=total,
                return_home=True,
                images_dir=str(run.run_dir),
            )
            self._remember_request()
            return self._finish(
                result,
                True,
                message=(
                    f"field capture mission completed; waypoints={total}/{total}; "
                    f"return_home=SUCCESS; images saved to: {run.run_dir}"
                ),
            )
        except Exception as exc:
            self.get_logger().error(
                f"FIELD_CAPTURE task failed unexpectedly: {exc}"
            )
            problem = _BASE.blocker(
                "NAV2_FAILED", str(exc), error_code=_BASE.ERROR_NAV2_FAILED
            )
            try:
                if run is not None:
                    run.finish(
                        success=False,
                        return_home_success=False,
                        completed_waypoints=completed,
                        total_waypoints=total,
                        message=str(exc),
                    )
                if (
                    self.session.status.state
                    == _BASE.NavigationSessionStatus.STATE_VALIDATING
                ):
                    self.session.transition(
                        _BASE.NavigationSessionStatus.STATE_REJECTED,
                        problem=_BASE.Blocker(
                            problem.code,
                            problem.operator_message,
                            problem.technical_message,
                            self._error_code(problem),
                        ),
                        success=False,
                    )
                elif self.session.status.state not in (
                    _BASE.NavigationSessionStatus.STATE_FAILED,
                    _BASE.NavigationSessionStatus.STATE_CANCELED,
                ):
                    self.session.transition(
                        _BASE.NavigationSessionStatus.STATE_FAILED,
                        problem=_BASE.Blocker(
                            problem.code,
                            problem.operator_message,
                            problem.technical_message,
                            self._error_code(problem),
                        ),
                        success=False,
                    )
            except (OSError, ValueError):
                pass
            goal_handle.abort()
            self._publish_status(
                "FAILED",
                backend="FIELD_CAPTURE",
                reason=str(exc),
                images_dir=str(run.run_dir) if run is not None else "",
            )
            self._remember_request()
            return self._finish(
                result,
                False,
                problem,
                message=(
                    f"{exc}; images saved to: {run.run_dir}"
                    if run is not None
                    else str(exc)
                ),
            )
        finally:
            if claimed_request:
                with self._lock:
                    self._child_goal_handle = None
                    self._route_executor = None
                    self._active = False
                    self._active_request_id = ""


def main(args=None):
    rclpy.init(args=args)
    node = FieldCaptureCapabilityServer()
    executor = MultiThreadedExecutor(num_threads=5)
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
