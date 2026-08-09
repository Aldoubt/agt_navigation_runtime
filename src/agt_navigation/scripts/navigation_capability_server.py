#!/usr/bin/env python3

"""MAP/ROUTE internal backend selector for the public ExecuteWaypointTask Action.

The existing waypoint_task_server remains the MAP implementation. This subclass
adds an optional, hash-bound ROUTE backend without changing the Action schema.
"""

from __future__ import annotations

import importlib.util
import math
from pathlib import Path

from nav2_msgs.action import FollowPath
import rclpy
from rclpy.action import ActionClient
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.duration import Duration
from rclpy.executors import MultiThreadedExecutor
from rclpy.time import Time
from tf2_ros import Buffer, TransformListener
import yaml

from agt_navigation.route_backend import RouteBackendExecutor
from agt_navigation.route_runtime import MapOdomSnapshot, RouteRuntimeError
from agt_navigation.route_task_binding import RouteTaskResolver, sha256_file


_BASE_SCRIPT = Path(__file__).with_name("waypoint_task_server.py")
_SPEC = importlib.util.spec_from_file_location("agt_waypoint_task_server_base", _BASE_SCRIPT)
_BASE = importlib.util.module_from_spec(_SPEC)
_SPEC.loader.exec_module(_BASE)

ERROR_ROUTE_INVALID = 43
ERROR_ROUTE_FAILED = 44


class NavigationCapabilityServer(_BASE.WaypointTaskServer):
    """Preserve MAP behavior and opt exact formal TaskGroup revisions into ROUTE."""

    def __init__(self, route_snapshot_provider=None, **kwargs):
        super().__init__(**kwargs)
        self._route_snapshot_provider_override = route_snapshot_provider
        self._route_resolver = RouteTaskResolver(self.maps_root)
        self._route_executor = None
        self._localization_correction_generation = 0

        profile_value = str(
            self.declare_parameter("execution_vehicle_profile", "").value
        ).strip()
        self.execution_vehicle_profile = (
            Path(profile_value).expanduser().resolve() if profile_value else None
        )
        self.execution_vehicle_profile_sha256 = ""
        self.execution_vehicle_route_accepted = False
        if self.execution_vehicle_profile is not None:
            if not self.execution_vehicle_profile.is_file():
                raise ValueError(
                    f"execution_vehicle_profile does not exist: {self.execution_vehicle_profile}"
                )
            self.execution_vehicle_profile_sha256 = sha256_file(
                self.execution_vehicle_profile
            )
            try:
                profile_document = yaml.safe_load(
                    self.execution_vehicle_profile.read_text(encoding="utf-8")
                ) or {}
            except (OSError, UnicodeError, yaml.YAMLError) as exc:
                raise ValueError(f"cannot read execution vehicle profile: {exc}") from exc
            platform = profile_document.get("platform") or {}
            acceptance = platform.get("route_acceptance") or {}
            self.execution_vehicle_route_accepted = bool(acceptance.get("enabled", False))

        self.route_controller_id_forward = str(
            self.declare_parameter("route_controller_id_forward", "").value
        )
        self.route_controller_id_reverse = str(
            self.declare_parameter("route_controller_id_reverse", "").value
        )
        self.route_goal_checker_id = str(
            self.declare_parameter("route_goal_checker_id", "").value
        )
        self.route_progress_checker_id = str(
            self.declare_parameter("route_progress_checker_id", "").value
        )

        route_group = ReentrantCallbackGroup()
        self._route_follow_path = ActionClient(
            self, FollowPath, "follow_path", callback_group=route_group
        )
        self._tf_buffer = None
        self._tf_listener = None
        if self._route_snapshot_provider_override is None:
            self._tf_buffer = Buffer()
            self._tf_listener = TransformListener(
                self._tf_buffer, self, spin_thread=False
            )

    def _route_binding_path(self, task) -> Path:
        return (
            self.maps_root.expanduser().resolve()
            / task.map_binding.map_id
            / "versions"
            / task.map_binding.map_version_id
            / "tasks"
            / f"{task.task_group_id}.route.yaml"
        )

    def _formal_task_has_route_binding(self, request) -> bool:
        if not self._is_formal_goal(request):
            return False
        try:
            stored = self._registry.resolve_task(
                str(request.map_id),
                str(request.map_version_id),
                str(request.task_group_id),
                int(request.task_revision),
            )
        except _BASE.TaskRegistryError:
            return False
        task = stored.task
        if task.content_sha256 != str(request.expected_content_sha256):
            return False
        return self._route_binding_path(task).exists()

    def _route_snapshot(self) -> MapOdomSnapshot:
        if self._route_snapshot_provider_override is not None:
            snapshot = self._route_snapshot_provider_override()
            if not isinstance(snapshot, MapOdomSnapshot):
                raise RouteRuntimeError(
                    "route_snapshot_invalid",
                    "route snapshot provider must return MapOdomSnapshot",
                )
            if int(snapshot.generation) <= 0:
                raise RouteRuntimeError(
                    "ROUTE_ALIGNMENT_GENERATION_UNAVAILABLE",
                    "route snapshot has no accepted correction generation",
                )
            return snapshot
        if self._tf_buffer is None:
            raise RouteRuntimeError(
                "route_tf_unavailable", "map->odom TF buffer is unavailable"
            )
        try:
            transform = self._tf_buffer.lookup_transform(
                "map",
                "odom",
                Time(),
                timeout=Duration(seconds=self.nav2_wait_timeout),
            )
        except Exception as exc:
            raise RouteRuntimeError(
                "route_tf_unavailable", f"cannot resolve map->odom: {exc}"
            ) from exc
        t = transform.transform.translation
        q = transform.transform.rotation
        yaw = math.atan2(
            2.0 * (q.w * q.z + q.x * q.y),
            1.0 - 2.0 * (q.y * q.y + q.z * q.z),
        )
        with self._lock:
            generation = self._localization_correction_generation
        if generation <= 0:
            raise RouteRuntimeError(
                "ROUTE_ALIGNMENT_GENERATION_UNAVAILABLE",
                "canonical localization has no accepted correction generation",
            )
        return MapOdomSnapshot(float(t.x), float(t.y), yaw, generation=generation)

    def _runtime_gate_problem(self):
        problem = super()._runtime_gate_problem()
        if problem is not None:
            return problem
        with self._lock:
            route_active = self._route_executor is not None and self._active
            generation = self._localization_correction_generation
        if route_active and self.require_localization_valid and generation <= 0:
            return _BASE.blocker(
                "ROUTE_ALIGNMENT_GENERATION_UNAVAILABLE",
                "canonical localization has no accepted correction generation",
            )
        return None

    def _cancel_route_backend(self, *, failed_reason: str = "") -> None:
        with self._lock:
            executor = self._route_executor
        if executor is None:
            return
        if failed_reason:
            executor.fail(failed_reason)
        else:
            executor.cancel()

    def _safety_callback(self, message):
        super()._safety_callback(message)
        with self._lock:
            route_active = self._route_executor is not None and self._active
            estop = self._estop_latched
        if route_active and self.require_safety_ready and not self._safety_is_ready():
            code = "ESTOP_LATCHED" if estop else "SAFETY_NOT_READY"
            self._fail_for_runtime_loss(code)
            self._cancel_route_backend(failed_reason=code)

    def _localization_callback(self, message):
        super()._localization_callback(message)
        with self._lock:
            self._localization_correction_generation = int(message.correction_generation)
            route_active = self._route_executor is not None and self._active
        if route_active and self.require_localization_valid:
            if not self._localization_is_ready():
                self._fail_for_runtime_loss("LOCALIZATION_NOT_READY")
                self._cancel_route_backend(failed_reason="LOCALIZATION_NOT_READY")
            elif self._localization_correction_generation <= 0:
                self._fail_for_runtime_loss("ROUTE_ALIGNMENT_GENERATION_UNAVAILABLE")
                self._cancel_route_backend(
                    failed_reason="ROUTE_ALIGNMENT_GENERATION_UNAVAILABLE"
                )

    def _task_readiness_callback(self, message):
        super()._task_readiness_callback(message)
        with self._lock:
            route_active = self._route_executor is not None and self._active
        if route_active and self.require_task_readiness and not self._task_readiness_is_ready():
            self._fail_for_runtime_loss("TASK_READINESS_NOT_READY")
            self._cancel_route_backend(failed_reason="TASK_READINESS_NOT_READY")

    def _safety_watchdog(self):
        super()._safety_watchdog()
        with self._lock:
            route_active = self._route_executor is not None and self._active
        if route_active:
            problem = self._runtime_gate_problem()
            if problem is not None:
                self._fail_for_runtime_loss(problem.code)
                self._cancel_route_backend(failed_reason=problem.code)

    def _cancel_callback(self, goal_handle):
        response = super()._cancel_callback(goal_handle)
        self._cancel_route_backend()
        return response

    async def _execute(self, goal_handle):
        if not self._formal_task_has_route_binding(goal_handle.request):
            return await super()._execute(goal_handle)
        return await self._execute_route(goal_handle)

    async def _execute_route(self, goal_handle):
        result = _BASE.ExecuteWaypointTask.Result()
        claimed_request = False
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

            try:
                self._start_session(goal_handle.request, None)
                points, task_binding, task = self._load_points_and_binding(
                    goal_handle.request
                )
            except _BASE.Blocked as exc:
                problem = exc.problem
                if self.session.status.client_request_id != str(
                    goal_handle.request.client_request_id
                ):
                    self._start_session(goal_handle.request, None)
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
                self._publish_status("REJECTED", backend="ROUTE", reason=problem.technical_message)
                self._remember_request()
                return self._finish(result, False, problem)

            current_map = self._map
            if self.require_map and current_map is None:
                return self._reject_route_goal(
                    goal_handle,
                    result,
                    _BASE.blocker("NO_ACTIVE_MAP", "global occupancy map has not been received"),
                )
            if current_map is not None:
                outside = [
                    point.name
                    for point in points
                    if not _BASE.point_inside_map(point, current_map.info)
                ]
                if outside:
                    return self._reject_route_goal(
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
                return self._reject_route_goal(goal_handle, result, binding_problem)
            gate_problem = self._runtime_gate_problem()
            if gate_problem is not None:
                return self._reject_route_goal(goal_handle, result, gate_problem)
            if self.require_localization_valid:
                with self._lock:
                    correction_generation = self._localization_correction_generation
                if correction_generation <= 0:
                    return self._reject_route_goal(
                        goal_handle,
                        result,
                        _BASE.blocker(
                            "ROUTE_ALIGNMENT_GENERATION_UNAVAILABLE",
                            "canonical localization has no accepted correction generation",
                        ),
                    )

            if not self.execution_vehicle_profile_sha256:
                return self._reject_route_goal(
                    goal_handle,
                    result,
                    _BASE.blocker(
                        "ROUTE_VEHICLE_PROFILE_MISSING",
                        "ROUTE backend requires execution_vehicle_profile",
                        error_code=ERROR_ROUTE_INVALID,
                    ),
                )
            if not self.execution_vehicle_route_accepted:
                return self._reject_route_goal(
                    goal_handle,
                    result,
                    _BASE.blocker(
                        "ROUTE_VEHICLE_NOT_ACCEPTED",
                        "execution vehicle profile has route_acceptance.enabled=false",
                        error_code=ERROR_ROUTE_INVALID,
                    ),
                )

            try:
                resolved = self._route_resolver.resolve(
                    task,
                    expected_vehicle_profile_sha256=self.execution_vehicle_profile_sha256,
                )
            except RouteRuntimeError as exc:
                return self._reject_route_goal(
                    goal_handle,
                    result,
                    _BASE.blocker(
                        exc.code, str(exc), error_code=ERROR_ROUTE_INVALID
                    ),
                )
            if resolved is None:
                return self._reject_route_goal(
                    goal_handle,
                    result,
                    _BASE.blocker(
                        "ROUTE_BINDING_MISSING",
                        "route binding disappeared after backend selection",
                        error_code=ERROR_ROUTE_INVALID,
                    ),
                )

            asset = resolved.asset
            total_segments = len(asset.segments)
            self.session.transition(
                _BASE.NavigationSessionStatus.STATE_ACCEPTED,
                total_waypoints=total_segments,
            )
            # ROUTE is running once the exact READY asset has been accepted and
            # the first odom RuntimePath is about to be handed to FollowPath.
            # Do not depend on Nav2 producing at least one feedback sample before
            # it returns a terminal result.
            self.session.transition(
                _BASE.NavigationSessionStatus.STATE_RUNNING,
                loop_index=0,
                current_waypoint=0,
                total_waypoints=total_segments,
            )

            def progress_sink(feedback, loop_index, segment_index):
                if str(feedback.status).upper() == "RUNNING":
                    try:
                        self.session.transition(
                            _BASE.NavigationSessionStatus.STATE_RUNNING,
                            loop_index=loop_index,
                            current_waypoint=segment_index,
                            total_waypoints=total_segments,
                        )
                    except ValueError:
                        pass
                    goal_handle.publish_feedback(
                        self._feedback(
                            "RUNNING", loop_index, segment_index, total_segments
                        )
                    )
                    self._publish_status(
                        "RUNNING",
                        backend="ROUTE",
                        route_id=asset.route_id,
                        route_revision=asset.revision,
                        segment_id=feedback.active_segment_id,
                        segment_index=segment_index,
                        total_segments=total_segments,
                        remaining_distance_m=feedback.remaining_distance_m,
                    )

            def completion_sink(completion, loop_index, segment_index):
                self._publish_status(
                    "SEGMENT_COMPLETE",
                    backend="ROUTE",
                    route_id=asset.route_id,
                    route_revision=asset.revision,
                    segment_id=completion.segment_id,
                    segment_index=segment_index,
                    total_segments=total_segments,
                    event_refs=list(completion.event_refs),
                    route_complete=completion.route_complete,
                )

            backend = RouteBackendExecutor(
                action_client=self._route_follow_path,
                asset=asset,
                snapshot_provider=self._route_snapshot,
                controller_id_forward=self.route_controller_id_forward,
                controller_id_reverse=self.route_controller_id_reverse,
                goal_checker_id=self.route_goal_checker_id,
                progress_checker_id=self.route_progress_checker_id,
                wait_timeout_sec=self.nav2_wait_timeout,
                progress_sink=progress_sink,
                completion_sink=completion_sink,
            )
            with self._lock:
                self._route_executor = backend
            backend_result = await backend.run(
                loop_count=int(goal_handle.request.loop_count),
                cancel_requested=lambda: bool(goal_handle.is_cancel_requested),
            )
            with self._lock:
                self._route_executor = None

            if backend_result.global_planner_requests != 0:
                backend_result = type(backend_result)(
                    False,
                    False,
                    "ROUTE backend attempted a global planner request",
                    backend_result.completions,
                    backend_result.global_planner_requests,
                )
            if backend_result.canceled or goal_handle.is_cancel_requested:
                if self.session.status.state != _BASE.NavigationSessionStatus.STATE_FAILED:
                    self.session.transition(
                        _BASE.NavigationSessionStatus.STATE_CANCELED, success=False
                    )
                goal_handle.canceled()
                self._publish_status("CANCELED", backend="ROUTE")
                self._remember_request()
                return self._finish(
                    result, False, _BASE.blocker("CANCELED", "task canceled")
                )
            if not backend_result.success:
                problem = _BASE.blocker(
                    "ROUTE_TRACKING_FAILED",
                    backend_result.failure_reason or "Route FollowPath tracking failed",
                    error_code=ERROR_ROUTE_FAILED,
                )
                if self.session.status.state != _BASE.NavigationSessionStatus.STATE_FAILED:
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
                goal_handle.abort()
                self._publish_status(
                    "FAILED", backend="ROUTE", reason=problem.technical_message
                )
                self._remember_request()
                return self._finish(result, False, problem)

            self.session.transition(
                _BASE.NavigationSessionStatus.STATE_SUCCEEDED,
                loop_index=max(0, int(goal_handle.request.loop_count) - 1),
                current_waypoint=total_segments,
                total_waypoints=total_segments,
                success=True,
            )
            goal_handle.succeed()
            self._publish_status(
                "SUCCEEDED",
                backend="ROUTE",
                route_id=asset.route_id,
                route_revision=asset.revision,
                loops=int(goal_handle.request.loop_count),
                segments=total_segments,
                global_planner_requests=backend_result.global_planner_requests,
            )
            self._remember_request()
            return self._finish(
                result,
                True,
                message=f"Route {asset.route_id} revision {asset.revision} completed",
            )
        except Exception as exc:
            self.get_logger().error(f"ROUTE waypoint task failed unexpectedly: {exc}")
            problem = _BASE.blocker(
                "ROUTE_TRACKING_FAILED", str(exc), error_code=ERROR_ROUTE_FAILED
            )
            try:
                if self.session.status.state == _BASE.NavigationSessionStatus.STATE_VALIDATING:
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
            except ValueError:
                pass
            goal_handle.abort()
            self._publish_status("FAILED", backend="ROUTE", reason=str(exc))
            self._remember_request()
            return self._finish(result, False, problem)
        finally:
            if claimed_request:
                with self._lock:
                    self._route_executor = None
                    self._child_goal_handle = None
                    self._active = False
                    self._active_request_id = ""

    def _reject_route_goal(self, goal_handle, result, problem):
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
            "REJECTED", backend="ROUTE", reason=problem.technical_message
        )
        self._remember_request()
        return self._finish(result, False, problem)


def main(args=None):
    rclpy.init(args=args)
    node = NavigationCapabilityServer()
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
