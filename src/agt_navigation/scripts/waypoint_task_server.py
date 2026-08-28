#!/usr/bin/env python3

from __future__ import annotations

from collections import OrderedDict
import copy
import json
import math
from pathlib import Path
import threading
import time

from action_msgs.msg import GoalStatus
from agt_interfaces.action import ExecuteWaypointTask
from agt_interfaces.msg import (
    LocalizationStatus,
    MapVersionSummary,
    NavigationSessionStatus,
    TaskReadiness,
)
from agt_interfaces.srv import GetNavigationSession
from agt_navigation.navigation_errors import Blocker, blocker
from agt_navigation.qt_task_chain import (
    TaskChainError,
    Waypoint,
    load_qt_task_chain,
    point_inside_map,
)
from agt_navigation.session_manager import NavigationSessionManager, SessionSpec
from agt_navigation.task_group import MapBinding, TaskGroupError, load_task_group
from agt_navigation.task_registry import TaskRegistry, TaskRegistryError
from diagnostic_msgs.msg import DiagnosticArray
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import FollowWaypoints
from nav_msgs.msg import OccupancyGrid
import rclpy
from rclpy.action import ActionClient, ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy
from std_msgs.msg import String


ERROR_NONE = 0
ERROR_INVALID_REQUEST = 10
ERROR_TASK_INVALID = 20
ERROR_MAP_UNAVAILABLE = 30
ERROR_POINT_OUTSIDE_MAP = 31
ERROR_MAP_MISMATCH = 32
ERROR_SAFETY_NOT_READY = 35
ERROR_LOCALIZATION_NOT_READY = 36
ERROR_TASK_READINESS_NOT_READY = 37
ERROR_NAV2_UNAVAILABLE = 40
ERROR_NAV2_REJECTED = 41
ERROR_NAV2_FAILED = 42
ERROR_CANCELED = 50

_ERROR_BY_BLOCKER = {
    "INVALID_REQUEST": ERROR_INVALID_REQUEST,
    "LEGACY_TASK_FILE_DISABLED": ERROR_INVALID_REQUEST,
    "TASK_NOT_FOUND": ERROR_TASK_INVALID,
    "TASK_REVISION_CONFLICT": ERROR_TASK_INVALID,
    "TASK_CONTENT_HASH_MISMATCH": ERROR_TASK_INVALID,
    "TASK_SCHEMA_INVALID": ERROR_TASK_INVALID,
    "TASK_MAP_BINDING_MISMATCH": ERROR_MAP_MISMATCH,
    "TASK_NOT_SYNCED": ERROR_TASK_INVALID,
    "NO_ACTIVE_MAP": ERROR_MAP_UNAVAILABLE,
    "MAP_NOT_READY": ERROR_MAP_UNAVAILABLE,
    "MAP_VERSION_MISMATCH": ERROR_MAP_MISMATCH,
    "MAP_GEOMETRY_MISMATCH": ERROR_MAP_MISMATCH,
    "MAP_YAML_HASH_MISMATCH": ERROR_MAP_MISMATCH,
    "MAP_IMAGE_HASH_MISMATCH": ERROR_MAP_MISMATCH,
    "LOCALIZATION_PCD_HASH_MISSING": ERROR_MAP_MISMATCH,
    "LOCALIZATION_PCD_HASH_MISMATCH": ERROR_MAP_MISMATCH,
    "LOCALIZATION_NOT_READY": ERROR_LOCALIZATION_NOT_READY,
    "LOCALIZATION_STATUS_STALE": ERROR_LOCALIZATION_NOT_READY,
    "TASK_READINESS_NOT_READY": ERROR_TASK_READINESS_NOT_READY,
    "SAFETY_NOT_READY": ERROR_SAFETY_NOT_READY,
    "ESTOP_LATCHED": ERROR_SAFETY_NOT_READY,
    "NAV2_UNAVAILABLE": ERROR_NAV2_UNAVAILABLE,
    "NAV2_REJECTED": ERROR_NAV2_REJECTED,
    "NAV2_FAILED": ERROR_NAV2_FAILED,
    "CANCELED": ERROR_CANCELED,
    "TASK_ALREADY_ACTIVE": ERROR_INVALID_REQUEST,
    "DUPLICATE_REQUEST": ERROR_NONE,
}


class DuplicateRequest(RuntimeError):
    pass


class Blocked(RuntimeError):
    def __init__(self, problem: Blocker) -> None:
        super().__init__(problem.technical_message)
        self.problem = problem


def fail(code: str, technical: str = "", *, error_code: int = 0) -> Blocked:
    return Blocked(blocker(code, technical, error_code=error_code))


class WaypointTaskServer(Node):
    def __init__(self, **kwargs):
        super().__init__("agt_waypoint_task_server", **kwargs)
        self.maximum_points = int(self.declare_parameter("maximum_points", 200).value)
        self.maximum_loops = int(self.declare_parameter("maximum_loops", 10).value)
        self.require_map = bool(self.declare_parameter("require_map", True).value)
        self.require_safety_ready = bool(
            self.declare_parameter("require_safety_ready", True).value
        )
        self.require_localization_valid = bool(
            self.declare_parameter("require_localization_valid", True).value
        )
        self.require_task_readiness = bool(
            self.declare_parameter("require_task_readiness", True).value
        )
        self.localization_status_timeout = float(
            self.declare_parameter("localization_status_timeout", 10.0).value
        )
        self.task_readiness_timeout = float(
            self.declare_parameter("task_readiness_timeout", 2.0).value
        )
        self.safety_status_timeout = float(
            self.declare_parameter("safety_status_timeout", 1.0).value
        )
        self.nav2_wait_timeout = float(
            self.declare_parameter("nav2_wait_timeout", 2.0).value
        )
        self.runtime_dir = Path(
            str(self.declare_parameter("runtime_dir", "runtime").value)
        ).expanduser()
        maps_root_value = str(self.declare_parameter("maps_root", "").value).strip()
        self.maps_root = (
            Path(maps_root_value).expanduser()
            if maps_root_value
            else self.runtime_dir / "maps"
        )
        self.allow_legacy_local_task_file = bool(
            self.declare_parameter("allow_legacy_local_task_file", False).value
        )
        self.allow_direct_pose_goals = bool(
            self.declare_parameter("allow_direct_pose_goals", False).value
        )
        self.recent_request_limit = int(
            self.declare_parameter("recent_request_limit", 256).value
        )
        self.current_map_id = str(self.declare_parameter("current_map_id", "").value)
        self.current_map_version_id = str(
            self.declare_parameter("current_map_version_id", "").value
        )
        self.current_map_yaml_sha256 = str(
            self.declare_parameter("current_map_yaml_sha256", "").value
        )
        self.current_map_image_sha256 = str(
            self.declare_parameter("current_map_image_sha256", "").value
        )
        self.current_localization_pcd_sha256 = str(
            self.declare_parameter("current_localization_pcd_sha256", "").value
        )
        self.require_map_content_hashes = bool(
            self.declare_parameter("require_map_content_hashes", True).value
        )
        if (
            self.maximum_points <= 0
            or self.maximum_loops <= 0
            or self.safety_status_timeout <= 0.0
            or self.localization_status_timeout <= 0.0
            or self.task_readiness_timeout <= 0.0
            or self.nav2_wait_timeout <= 0.0
            or self.recent_request_limit <= 0
        ):
            raise ValueError(
                "task limits, request limits, and readiness timeouts must be positive"
            )

        group = ReentrantCallbackGroup()
        self._map = None
        self._active_map = None
        self._active = False
        self._active_request_id = ""
        self._child_goal_handle = None
        self._safety_ready = False
        self._estop_latched = False
        self._safety_stamp = float("-inf")
        self._localization_ready = False
        self._localization_stamp = float("-inf")
        self._localization_map_hash = ""
        self._localization_map_id = ""
        self._task_readiness = False
        self._task_readiness_stamp = float("-inf")
        self._readiness_map_id = ""
        self._readiness_map_version_id = ""
        self._lock = threading.RLock()
        self._recent_requests: OrderedDict[str, NavigationSessionStatus] = OrderedDict()

        self._registry = TaskRegistry(
            self.maps_root,
            maximum_task_bytes=int(
                self.declare_parameter("maximum_task_bytes", 1024 * 1024).value
            ),
            backup_count=int(self.declare_parameter("backup_count", 5).value),
            recent_request_limit=self.recent_request_limit,
        )
        self.session = NavigationSessionManager(self)
        self.session.publish()
        self.create_service(
            GetNavigationSession,
            "/agt/navigation/session/get",
            self.session.fill_get_response,
            callback_group=group,
        )

        map_qos = QoSProfile(depth=1)
        map_qos.reliability = ReliabilityPolicy.RELIABLE
        map_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self.create_subscription(
            OccupancyGrid,
            "/agt/map/global_occupancy",
            self._map_callback,
            map_qos,
            callback_group=group,
        )
        self.create_subscription(
            MapVersionSummary,
            "/agt/maps/active",
            self._active_map_callback,
            map_qos,
            callback_group=group,
        )
        self.create_subscription(
            DiagnosticArray,
            "/agt/safety/status",
            self._safety_callback,
            10,
            callback_group=group,
        )
        self.create_subscription(
            LocalizationStatus,
            "/agt/localization/status",
            self._localization_callback,
            10,
            callback_group=group,
        )
        self.create_subscription(
            TaskReadiness,
            "/agt/system/task_readiness",
            self._task_readiness_callback,
            10,
            callback_group=group,
        )
        self._status = self.create_publisher(String, "/agt/navigation/task_status", 10)
        self._nav2 = ActionClient(
            self, FollowWaypoints, "follow_waypoints", callback_group=group
        )
        self._server = ActionServer(
            self,
            ExecuteWaypointTask,
            "/agt/navigation/execute_waypoint_task",
            execute_callback=self._execute,
            goal_callback=self._goal_callback,
            cancel_callback=self._cancel_callback,
            callback_group=group,
        )
        self.create_timer(0.2, self._safety_watchdog, callback_group=group)

    def _map_callback(self, message):
        self._map = message

    def _active_map_callback(self, message):
        with self._lock:
            self._active_map = copy.deepcopy(message)

    def _active_map_summary(self):
        with self._lock:
            return copy.deepcopy(self._active_map)

    def _safety_callback(self, message):
        ready = False
        estop = False
        for status in message.status:
            if status.name != "agt_safety/controller":
                continue
            values = {item.key: item.value.lower() for item in status.values}
            estop = values.get("estop_latched") == "true"
            ready = values.get("motion_enabled") == "true" and not estop
            break
        with self._lock:
            self._safety_ready = ready
            self._estop_latched = estop
            self._safety_stamp = time.monotonic()
            child = (
                self._child_goal_handle
                if self.require_safety_ready and self._active and not ready
                else None
            )
        if child is not None:
            self._fail_for_runtime_loss("ESTOP_LATCHED" if estop else "SAFETY_NOT_READY")
            child.cancel_goal_async()

    def _safety_is_ready(self):
        with self._lock:
            return self._safety_ready and (
                time.monotonic() - self._safety_stamp <= self.safety_status_timeout
            )

    @staticmethod
    def localization_status_is_ready(message):
        return (
            message.state == LocalizationStatus.STATE_TRACKING
            and message.pose_valid
            and message.localization_accepted
            and message.error_code == LocalizationStatus.ERROR_NONE
            and not message.status_stale
        )

    def _localization_callback(self, message):
        ready = self.localization_status_is_ready(message)
        with self._lock:
            self._localization_ready = ready
            self._localization_stamp = time.monotonic()
            self._localization_map_hash = str(message.map_hash)
            self._localization_map_id = str(message.map_id)
            child = (
                self._child_goal_handle
                if self.require_localization_valid and self._active and not ready
                else None
            )
        if child is not None:
            self._fail_for_runtime_loss("LOCALIZATION_NOT_READY")
            child.cancel_goal_async()

    def _localization_is_ready(self):
        with self._lock:
            return self._localization_ready and (
                time.monotonic() - self._localization_stamp
                <= self.localization_status_timeout
            )

    def _task_readiness_callback(self, message):
        with self._lock:
            self._task_readiness = bool(message.ready)
            self._task_readiness_stamp = time.monotonic()
            self._readiness_map_id = str(message.map_id)
            self._readiness_map_version_id = str(message.map_version_id)
            child = (
                self._child_goal_handle
                if self.require_task_readiness and self._active and not self._task_readiness
                else None
            )
        if child is not None:
            self._fail_for_runtime_loss("TASK_READINESS_NOT_READY")
            child.cancel_goal_async()

    def _task_readiness_is_ready(self):
        with self._lock:
            return self._task_readiness and (
                time.monotonic() - self._task_readiness_stamp
                <= self.task_readiness_timeout
            )

    def _safety_watchdog(self):
        with self._lock:
            if not self._active:
                return
            now = time.monotonic()
            code = ""
            if self.require_safety_ready and now - self._safety_stamp > self.safety_status_timeout:
                self._safety_ready = False
                code = "SAFETY_NOT_READY"
            elif self.require_localization_valid and now - self._localization_stamp > self.localization_status_timeout:
                self._localization_ready = False
                code = "LOCALIZATION_STATUS_STALE"
            elif self.require_task_readiness and not self._task_readiness_is_ready():
                code = "TASK_READINESS_NOT_READY"
            child = self._child_goal_handle if code else None
        if child is not None:
            self._fail_for_runtime_loss(code)
            child.cancel_goal_async()

    def _fail_for_runtime_loss(self, code: str) -> None:
        try:
            if self.session.status.state in (
                NavigationSessionStatus.STATE_ACCEPTED,
                NavigationSessionStatus.STATE_RUNNING,
            ):
                self.session.transition(
                    NavigationSessionStatus.STATE_FAILED,
                    problem=blocker(code, f"runtime gate lost: {code}", error_code=_ERROR_BY_BLOCKER.get(code, ERROR_NAV2_FAILED)),
                    success=False,
                )
        except ValueError:
            pass

    def _publish_status(self, state, **values):
        message = String()
        message.data = json.dumps({"state": state, **values}, ensure_ascii=False)
        self._status.publish(message)

    def _is_formal_goal(self, request) -> bool:
        return bool(request.map_id or request.map_version_id or request.task_group_id or request.task_revision)

    def _goal_callback(self, request):
        try:
            self._validate_goal_shape(request)
        except Blocked as exc:
            problem = exc.problem
            self.get_logger().warning(f"Rejecting waypoint task: {problem.technical_message}")
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def _validate_goal_shape(self, request) -> None:
        inputs = int(self._is_formal_goal(request)) + int(bool(request.task_file)) + int(bool(request.poses))
        if inputs != 1:
            raise fail("INVALID_REQUEST", "supply exactly one formal task ID, task_file, or poses input")
        if self._is_formal_goal(request):
            missing = [
                name
                for name in ("map_id", "map_version_id", "task_group_id", "task_revision", "expected_content_sha256", "client_request_id")
                if not getattr(request, name)
            ]
            if missing:
                raise fail("INVALID_REQUEST", "formal waypoint task is missing " + ", ".join(missing))
            try:
                TaskRegistry.safe_component(str(request.map_id), "map_id")
                TaskRegistry.safe_component(str(request.map_version_id), "map_version_id")
                TaskRegistry.safe_component(str(request.task_group_id), "task_group_id")
            except TaskRegistryError as exc:
                raise Blocked(exc.problem) from exc
            if not TaskRegistry.valid_client_request_id(str(request.client_request_id)):
                raise fail("INVALID_REQUEST", "client_request_id contains unsafe characters")
            if int(request.task_revision) <= 0:
                raise fail("TASK_REVISION_CONFLICT", "task_revision must be positive")
        elif request.task_file and not self.allow_legacy_local_task_file:
            raise fail("LEGACY_TASK_FILE_DISABLED", "legacy task_file execution is disabled")
        elif request.poses and not self.allow_direct_pose_goals:
            raise fail("INVALID_REQUEST", "direct pose goals are disabled")
        if request.loop_count <= 0 or request.loop_count > self.maximum_loops:
            raise fail("INVALID_REQUEST", f"loop_count must be in 1..{self.maximum_loops}")

    def _cancel_callback(self, _goal_handle):
        try:
            self.session.transition(NavigationSessionStatus.STATE_CANCELING)
        except ValueError:
            pass
        with self._lock:
            child = self._child_goal_handle
        if child is not None:
            child.cancel_goal_async()
        return CancelResponse.ACCEPT

    @staticmethod
    def _pose(point, stamp):
        pose = PoseStamped()
        pose.header.frame_id = "map"
        pose.header.stamp = stamp
        pose.pose.position.x = point.x
        pose.pose.position.y = point.y
        pose.pose.orientation.z = math.sin(point.theta / 2.0)
        pose.pose.orientation.w = math.cos(point.theta / 2.0)
        return pose

    def _load_points(self, request):
        points, _binding, _task = self._load_points_and_binding(request)
        return points

    def _load_points_and_binding(self, request):
        if self._is_formal_goal(request):
            try:
                stored = self._registry.resolve_task(
                    str(request.map_id),
                    str(request.map_version_id),
                    str(request.task_group_id),
                    int(request.task_revision),
                )
            except TaskRegistryError as exc:
                raise Blocked(exc.problem) from exc
            task = stored.task
            if task.content_sha256 != str(request.expected_content_sha256):
                raise fail(
                    "TASK_CONTENT_HASH_MISMATCH",
                    "expected_content_sha256 does not match stored task content",
                    error_code=ERROR_TASK_INVALID,
                )
            return self._points_from_task(task), task.map_binding, task
        if request.task_file:
            task_path = self._legacy_task_path(str(request.task_file))
            try:
                document = json.loads(task_path.read_text(encoding="utf-8"))
            except (OSError, UnicodeError, json.JSONDecodeError) as exc:
                raise fail("TASK_SCHEMA_INVALID", f"cannot read task JSON: {exc}") from exc
            if isinstance(document, dict) and "schema_version" in document:
                try:
                    task = load_task_group(
                        task_path,
                        maximum_points=self.maximum_points,
                        maximum_loops=self.maximum_loops,
                    )
                except TaskGroupError as exc:
                    raise fail("TASK_SCHEMA_INVALID", str(exc)) from exc
                return self._points_from_task(task), task.map_binding, task
            return load_qt_task_chain(task_path, maximum_points=self.maximum_points), None, None
        if not request.poses:
            raise fail("INVALID_REQUEST", "task ID, task_file, or poses is required")
        return self._points_from_poses(request.poses), None, None

    @staticmethod
    def _points_from_task(task):
        return [
            Waypoint(name=point.name, x=point.x, y=point.y, theta=point.yaw)
            for point in task.enabled_points
        ]

    def _legacy_task_path(self, value: str) -> Path:
        root = self.maps_root.expanduser().resolve()
        path = Path(value).expanduser()
        if not path.is_absolute():
            raise fail("INVALID_REQUEST", "task_file must be an absolute path")
        try:
            resolved = path.resolve(strict=True)
            resolved.relative_to(root)
        except FileNotFoundError as exc:
            raise fail("TASK_NOT_FOUND", "legacy task_file does not exist") from exc
        except ValueError as exc:
            raise fail("INVALID_REQUEST", "legacy task_file must stay below runtime/maps") from exc
        if resolved.is_symlink() or not resolved.is_file():
            raise fail("TASK_NOT_FOUND", "legacy task_file is not a regular file")
        return resolved

    def _points_from_poses(self, poses):
        if len(poses) > self.maximum_points:
            raise fail(
                "TASK_SCHEMA_INVALID",
                f"task contains {len(poses)} waypoints; limit is {self.maximum_points}",
            )
        points = []
        for index, pose in enumerate(poses):
            if pose.header.frame_id != "map":
                raise fail("TASK_SCHEMA_INVALID", f"pose {index} frame_id must be map")
            q = pose.pose.orientation
            values = (pose.pose.position.x, pose.pose.position.y, q.x, q.y, q.z, q.w)
            if not all(math.isfinite(value) for value in values):
                raise fail("TASK_SCHEMA_INVALID", f"pose {index} contains a non-finite value")
            norm = math.sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w)
            if norm < 1.0e-9 or abs(norm - 1.0) > 1.0e-3:
                raise fail("TASK_SCHEMA_INVALID", f"pose {index} orientation must be normalized")
            yaw = math.atan2(
                2.0 * (q.w * q.z + q.x * q.y),
                1.0 - 2.0 * (q.y * q.y + q.z * q.z),
            )
            points.append(
                Waypoint(
                    name=f"waypoint_{index:03d}",
                    x=pose.pose.position.x,
                    y=pose.pose.position.y,
                    theta=yaw,
                )
            )
        return points

    def _current_binding(self, current_map) -> MapBinding:
        active = self._active_map_summary()
        q = current_map.info.origin.orientation
        current_yaw = math.atan2(
            2.0 * (q.w * q.z + q.x * q.y),
            1.0 - 2.0 * (q.y * q.y + q.z * q.z),
        )
        with self._lock:
            localization_map_hash = self._localization_map_hash
        map_id = ""
        map_version_id = ""
        yaml_hash = ""
        image_hash = ""
        pcd_hash = localization_map_hash
        if (
            active
            and active.active
            and active.state == MapVersionSummary.STATE_READY
            and active.valid
        ):
            map_id = active.map_id
            map_version_id = active.map_version_id
            yaml_hash = active.navigation_yaml_sha256
            image_hash = active.navigation_image_sha256
            pcd_hash = active.localization_pcd_sha256 or pcd_hash
        return MapBinding(
            map_id=map_id,
            map_version_id=map_version_id,
            map_yaml_sha256=yaml_hash,
            map_image_sha256=image_hash,
            localization_pcd_sha256=pcd_hash,
            resolution=float(current_map.info.resolution),
            width=int(current_map.info.width),
            height=int(current_map.info.height),
            origin=(
                float(current_map.info.origin.position.x),
                float(current_map.info.origin.position.y),
                current_yaw,
            ),
        )

    def _validate_task_binding(self, binding, current_map):
        if binding is None:
            return None
        if current_map is None:
            return blocker("NO_ACTIVE_MAP", "map binding cannot be checked before the current map arrives")
        if getattr(current_map.header, "frame_id", "map") != "map":
            return blocker("MAP_GEOMETRY_MISMATCH", "current OccupancyGrid frame_id must be map")
        current = self._current_binding(current_map)
        if not current.map_id or not current.map_version_id:
            return blocker("NO_ACTIVE_MAP", "a valid READY /agt/maps/active identity is required for task execution")
        if binding.map_id != current.map_id or binding.map_version_id != current.map_version_id:
            return blocker(
                "MAP_VERSION_MISMATCH",
                f"task binding {binding.map_id}/{binding.map_version_id} does not match active {current.map_id}/{current.map_version_id}",
            )
        with self._lock:
            localization_map_id = self._localization_map_id
            localization_map_hash = self._localization_map_hash
        if (
            self.require_map_content_hashes
            and localization_map_id
            and localization_map_id != current.map_id
        ):
            return blocker(
                "LOCALIZATION_PCD_HASH_MISMATCH",
                f"localization map_id {localization_map_id} does not match active {current.map_id}",
            )
        geometry_matches = (
            math.isclose(binding.resolution, current.resolution, abs_tol=1.0e-9)
            and binding.width == current.width
            and binding.height == current.height
            and all(
                math.isclose(expected, actual, abs_tol=1.0e-9)
                for expected, actual in zip(binding.origin, current.origin)
            )
        )
        if not geometry_matches:
            return blocker("MAP_GEOMETRY_MISMATCH", "task map geometry does not match the current OccupancyGrid")
        for field_name, code in (
            ("map_yaml_sha256", "MAP_YAML_HASH_MISMATCH"),
            ("map_image_sha256", "MAP_IMAGE_HASH_MISMATCH"),
            ("localization_pcd_sha256", "LOCALIZATION_PCD_HASH_MISMATCH"),
        ):
            expected = getattr(binding, field_name)
            actual = getattr(current, field_name)
            if self.require_map_content_hashes and not actual:
                missing = (
                    "LOCALIZATION_PCD_HASH_MISSING"
                    if field_name == "localization_pcd_sha256"
                    else "MAP_NOT_READY"
                )
                return blocker(missing, f"active {field_name} is not configured")
            if expected and actual and expected != actual:
                return blocker(code, f"task binding {field_name} does not match the active map")
        if (
            self.require_map_content_hashes
            and binding.localization_pcd_sha256
            and localization_map_hash
            and binding.localization_pcd_sha256 != localization_map_hash
        ):
            return blocker(
                "LOCALIZATION_PCD_HASH_MISMATCH",
                "LocalizationStatus map_hash does not match the task binding localization PCD",
            )
        return None

    def _runtime_gate_problem(self):
        if self.require_safety_ready and not self._safety_is_ready():
            with self._lock:
                estop = self._estop_latched
            return blocker("ESTOP_LATCHED" if estop else "SAFETY_NOT_READY", "agt_safety is stale, motion-disabled, or emergency-stopped")
        if self.require_localization_valid and not self._localization_is_ready():
            with self._lock:
                stale = time.monotonic() - self._localization_stamp > self.localization_status_timeout
            return blocker("LOCALIZATION_STATUS_STALE" if stale else "LOCALIZATION_NOT_READY", "localization is stale, lost, or not accepted")
        if self.require_task_readiness and not self._task_readiness_is_ready():
            return blocker("TASK_READINESS_NOT_READY", "TaskReadiness is stale or blocked")
        return None

    def _claim_request(self, request) -> None:
        request_id = str(request.client_request_id)
        with self._lock:
            if request_id and request_id in self._recent_requests:
                self.session.status = copy.deepcopy(self._recent_requests[request_id])
                self.session.publish()
                raise DuplicateRequest(request_id)
            if request_id and request_id == self.session.status.client_request_id:
                self.session.publish()
                raise DuplicateRequest(request_id)
            if request_id and request_id == self._active_request_id:
                self.session.publish()
                raise DuplicateRequest(request_id)
            if self._active:
                raise fail(
                    "TASK_ALREADY_ACTIVE",
                    f"active session_id={self.session.status.session_id}",
                )
            self._active = True
            self._active_request_id = request_id

    def _remember_request(self) -> None:
        request_id = str(self.session.status.client_request_id)
        if not request_id:
            return
        with self._lock:
            self._recent_requests[request_id] = copy.deepcopy(self.session.status)
            self._recent_requests.move_to_end(request_id)
            while len(self._recent_requests) > self.recent_request_limit:
                self._recent_requests.popitem(last=False)

    def _start_session(self, request, task=None) -> None:
        spec = SessionSpec(
            client_request_id=str(request.client_request_id),
            map_id=str(request.map_id or getattr(getattr(task, "map_binding", None), "map_id", "")),
            map_version_id=str(request.map_version_id or getattr(getattr(task, "map_binding", None), "map_version_id", "")),
            task_group_id=str(request.task_group_id or getattr(task, "task_group_id", "")),
            task_revision=int(request.task_revision or getattr(task, "revision", 0)),
            task_content_sha256=str(request.expected_content_sha256 or getattr(task, "content_sha256", "")),
        )
        self.session.start(spec)

    @staticmethod
    def _error_code(problem: Blocker) -> int:
        return int(problem.error_code or _ERROR_BY_BLOCKER.get(problem.code, ERROR_INVALID_REQUEST))

    def _finish(self, result, success, problem=None, *, message="", missed=None, duplicate=False):
        result.success = bool(success)
        result.error_code = self._error_code(problem) if problem is not None else ERROR_NONE
        result.message = message or (problem.technical_message if problem is not None else "waypoint task completed")
        result.session_id = self.session.status.session_id
        result.blocker_code = problem.code if problem is not None else ""
        result.operator_message = problem.operator_message if problem is not None else ""
        result.technical_message = problem.technical_message if problem is not None else ""
        result.duplicate_request = bool(duplicate)
        result.missed_waypoints = list(missed or [])
        result.final_status = self.session.status
        return result

    def _feedback(self, state: str, loop_index: int, current_waypoint: int, total_waypoints: int):
        feedback = ExecuteWaypointTask.Feedback()
        feedback.state = state
        feedback.loop_index = int(loop_index)
        feedback.current_waypoint = int(current_waypoint)
        feedback.total_waypoints = int(total_waypoints)
        feedback.status = self.session.status
        return feedback

    async def _execute(self, goal_handle):
        result = ExecuteWaypointTask.Result()
        claimed_request = False
        try:
            try:
                self._claim_request(goal_handle.request)
                claimed_request = True
            except DuplicateRequest:
                goal_handle.succeed()
                duplicate = blocker("DUPLICATE_REQUEST", "client_request_id was already handled")
                return self._finish(result, self.session.status.success, duplicate, duplicate=True)
            except Blocked as exc:
                problem = exc.problem
                goal_handle.abort()
                return self._finish(result, False, problem)

            try:
                if self._is_formal_goal(goal_handle.request):
                    self._start_session(goal_handle.request, None)
                points, task_binding, task = self._load_points_and_binding(goal_handle.request)
                if not self._is_formal_goal(goal_handle.request):
                    self._start_session(goal_handle.request, task)
            except Blocked as exc:
                problem = exc.problem
                if self.session.status.client_request_id != str(goal_handle.request.client_request_id):
                    self._start_session(goal_handle.request, None)
                self.session.transition(
                    NavigationSessionStatus.STATE_REJECTED,
                    problem=Blocker(problem.code, problem.operator_message, problem.technical_message, self._error_code(problem)),
                    success=False,
                )
                goal_handle.abort()
                self._publish_status("REJECTED", reason=problem.technical_message)
                self._remember_request()
                return self._finish(result, False, problem)

            current_map = self._map
            if self.require_map and current_map is None:
                problem = blocker("NO_ACTIVE_MAP", "global occupancy map has not been received")
                self.session.transition(
                    NavigationSessionStatus.STATE_REJECTED,
                    problem=Blocker(problem.code, problem.operator_message, problem.technical_message, self._error_code(problem)),
                    success=False,
                )
                goal_handle.abort()
                self._publish_status("REJECTED", reason=problem.technical_message)
                self._remember_request()
                return self._finish(result, False, problem)
            if current_map is not None:
                outside = [point.name for point in points if not point_inside_map(point, current_map.info)]
                if outside:
                    problem = blocker("MAP_GEOMETRY_MISMATCH", "waypoints outside current map: " + ", ".join(outside))
                    self.session.transition(
                        NavigationSessionStatus.STATE_REJECTED,
                        problem=Blocker(problem.code, problem.operator_message, problem.technical_message, ERROR_POINT_OUTSIDE_MAP),
                        success=False,
                    )
                    goal_handle.abort()
                    self._publish_status("REJECTED", reason=problem.technical_message)
                    self._remember_request()
                    return self._finish(result, False, problem)
            binding_problem = self._validate_task_binding(task_binding, current_map)
            if binding_problem:
                problem = binding_problem
                self.session.transition(
                    NavigationSessionStatus.STATE_REJECTED,
                    problem=Blocker(problem.code, problem.operator_message, problem.technical_message, self._error_code(problem)),
                    success=False,
                )
                goal_handle.abort()
                self._publish_status("REJECTED", reason=problem.technical_message)
                self._remember_request()
                return self._finish(result, False, problem)

            gate_problem = self._runtime_gate_problem()
            if gate_problem:
                problem = gate_problem
                self.session.transition(
                    NavigationSessionStatus.STATE_REJECTED,
                    problem=Blocker(problem.code, problem.operator_message, problem.technical_message, self._error_code(problem)),
                    success=False,
                )
                goal_handle.abort()
                self._publish_status("REJECTED", reason=problem.technical_message)
                self._remember_request()
                return self._finish(result, False, problem)

            if not self._nav2.wait_for_server(timeout_sec=self.nav2_wait_timeout):
                problem = blocker("NAV2_UNAVAILABLE", "Nav2 FollowWaypoints action is unavailable")
                self.session.transition(
                    NavigationSessionStatus.STATE_FAILED,
                    problem=Blocker(problem.code, problem.operator_message, problem.technical_message, self._error_code(problem)),
                    success=False,
                )
                goal_handle.abort()
                self._publish_status("FAILED", reason=problem.technical_message)
                self._remember_request()
                return self._finish(result, False, problem)

            self.session.transition(
                NavigationSessionStatus.STATE_ACCEPTED,
                total_waypoints=len(points),
            )
            loop_count = int(goal_handle.request.loop_count)
            all_missed = []
            for loop_index in range(loop_count):
                if goal_handle.is_cancel_requested:
                    self.session.transition(NavigationSessionStatus.STATE_CANCELED, success=False)
                    goal_handle.canceled()
                    self._remember_request()
                    return self._finish(result, False, blocker("CANCELED", "task canceled"))

                nav_goal = FollowWaypoints.Goal()
                stamp = self.get_clock().now().to_msg()
                nav_goal.poses = [self._pose(point, stamp) for point in points]

                def feedback_callback(message, current_loop=loop_index):
                    current_waypoint = message.feedback.current_waypoint
                    try:
                        self.session.transition(
                            NavigationSessionStatus.STATE_RUNNING,
                            loop_index=current_loop,
                            current_waypoint=current_waypoint,
                            total_waypoints=len(points),
                        )
                    except ValueError:
                        pass
                    goal_handle.publish_feedback(
                        self._feedback("RUNNING", current_loop, current_waypoint, len(points))
                    )
                    self._publish_status(
                        "RUNNING",
                        session_id=self.session.status.session_id,
                        loop_index=current_loop,
                        current_waypoint=current_waypoint,
                        total_waypoints=len(points),
                    )

                child_handle = await self._nav2.send_goal_async(
                    nav_goal, feedback_callback=feedback_callback
                )
                if not child_handle.accepted:
                    problem = blocker("NAV2_REJECTED", "Nav2 rejected the waypoint chain")
                    self.session.transition(
                        NavigationSessionStatus.STATE_FAILED,
                        problem=Blocker(problem.code, problem.operator_message, problem.technical_message, self._error_code(problem)),
                        success=False,
                    )
                    goal_handle.abort()
                    self._publish_status("FAILED", reason=problem.technical_message)
                    self._remember_request()
                    return self._finish(result, False, problem)

                try:
                    self.session.transition(
                        NavigationSessionStatus.STATE_RUNNING,
                        loop_index=loop_index,
                        current_waypoint=0,
                        total_waypoints=len(points),
                    )
                except ValueError:
                    pass
                with self._lock:
                    self._child_goal_handle = child_handle
                if goal_handle.is_cancel_requested:
                    cancel_response = await child_handle.cancel_goal_async()
                    if not cancel_response.goals_canceling:
                        problem = blocker("NAV2_FAILED", "Nav2 did not accept task cancellation")
                        self.session.transition(
                            NavigationSessionStatus.STATE_FAILED,
                            problem=Blocker(problem.code, problem.operator_message, problem.technical_message, self._error_code(problem)),
                            success=False,
                        )
                        goal_handle.abort()
                        self._remember_request()
                        return self._finish(result, False, problem)
                    self.session.transition(NavigationSessionStatus.STATE_CANCELED, success=False)
                    goal_handle.canceled()
                    self._remember_request()
                    return self._finish(result, False, blocker("CANCELED", "task canceled"))

                wrapped = await child_handle.get_result_async()
                with self._lock:
                    self._child_goal_handle = None
                if goal_handle.is_cancel_requested:
                    self.session.transition(NavigationSessionStatus.STATE_CANCELED, success=False)
                    goal_handle.canceled()
                    self._publish_status("CANCELED", loop_index=loop_index)
                    self._remember_request()
                    return self._finish(result, False, blocker("CANCELED", "task canceled"))

                gate_problem = self._runtime_gate_problem()
                if gate_problem:
                    problem = gate_problem
                    if self.session.status.state not in (
                        NavigationSessionStatus.STATE_FAILED,
                        NavigationSessionStatus.STATE_CANCELED,
                    ):
                        self.session.transition(
                            NavigationSessionStatus.STATE_FAILED,
                            problem=Blocker(problem.code, problem.operator_message, problem.technical_message, self._error_code(problem)),
                            success=False,
                        )
                    goal_handle.abort()
                    self._publish_status("FAILED", reason=problem.technical_message)
                    self._remember_request()
                    return self._finish(result, False, problem)

                missed = list(wrapped.result.missed_waypoints)
                all_missed.extend(missed)
                if wrapped.status != GoalStatus.STATUS_SUCCEEDED or missed:
                    message = f"Nav2 waypoint execution failed with status {wrapped.status}; missed={missed}"
                    problem = blocker("NAV2_FAILED", message)
                    self.session.transition(
                        NavigationSessionStatus.STATE_FAILED,
                        missed_waypoints=all_missed,
                        problem=Blocker(problem.code, problem.operator_message, problem.technical_message, self._error_code(problem)),
                        success=False,
                    )
                    goal_handle.abort()
                    self._publish_status("FAILED", reason=problem.technical_message)
                    self._remember_request()
                    return self._finish(result, False, problem, missed=all_missed)

            self.session.transition(
                NavigationSessionStatus.STATE_SUCCEEDED,
                loop_index=max(0, loop_count - 1),
                current_waypoint=len(points),
                total_waypoints=len(points),
                success=True,
            )
            goal_handle.succeed()
            self._publish_status(
                "SUCCEEDED",
                session_id=self.session.status.session_id,
                loops=loop_count,
                waypoints=len(points),
            )
            self._remember_request()
            return self._finish(result, True, missed=all_missed)
        except Exception as exc:
            self.get_logger().error(f"Waypoint task failed unexpectedly: {exc}")
            problem = blocker("NAV2_FAILED", str(exc))
            try:
                if self.session.status.state == NavigationSessionStatus.STATE_VALIDATING:
                    self.session.transition(
                        NavigationSessionStatus.STATE_REJECTED,
                        problem=Blocker(problem.code, problem.operator_message, problem.technical_message, self._error_code(problem)),
                        success=False,
                    )
                elif self.session.status.state not in (
                    NavigationSessionStatus.STATE_FAILED,
                    NavigationSessionStatus.STATE_CANCELED,
                ):
                    self.session.transition(
                        NavigationSessionStatus.STATE_FAILED,
                        problem=Blocker(problem.code, problem.operator_message, problem.technical_message, self._error_code(problem)),
                        success=False,
                    )
            except ValueError:
                pass
            goal_handle.abort()
            self._publish_status("FAILED", reason=str(exc))
            self._remember_request()
            return self._finish(result, False, problem)
        finally:
            if claimed_request:
                with self._lock:
                    self._child_goal_handle = None
                    self._active = False
                    self._active_request_id = ""


def main(args=None):
    rclpy.init(args=args)
    node = WaypointTaskServer()
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
