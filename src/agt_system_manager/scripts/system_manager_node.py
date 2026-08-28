#!/usr/bin/env python3

from __future__ import annotations

import copy
import time
import threading

from agt_interfaces.msg import (
    BagSessionSummary,
    ComponentHealth,
    LocalizationStatus,
    MapVersionSummary,
    MissionStatus,
    RobotState,
    SystemHealth,
    TaskReadiness,
)
from agt_interfaces.srv import EvaluateTaskReadiness, GetRobotState, GetSystemHealth
from agt_system_manager.readiness import (
    ComponentEvidence,
    Evidence,
    evaluate_navigation_readiness,
    overall_health_state,
)
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus
import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy
from std_msgs.msg import Bool


class SystemManager(Node):
    """Own the authoritative read-only runtime health/readiness/robot-state model."""

    def __init__(self) -> None:
        super().__init__("agt_system_manager")

        self._publish_rate_hz = float(
            self.declare_parameter("publish_rate_hz", 5.0).value
        )
        self._active_mode = str(
            self.declare_parameter("active_mode", "NAVIGATION").value
        ).strip().upper()
        self._active_profile = str(
            self.declare_parameter("active_profile", "").value
        ).strip()
        self._sensor_timeout_s = float(
            self.declare_parameter("sensor_status_timeout_s", 1.5).value
        )
        self._localization_timeout_s = float(
            self.declare_parameter("localization_status_timeout_s", 10.0).value
        )
        self._safety_timeout_s = float(
            self.declare_parameter("safety_status_timeout_s", 1.0).value
        )
        self._chassis_timeout_s = float(
            self.declare_parameter("chassis_status_timeout_s", 1.0).value
        )
        self._sensor_summary_name = str(
            self.declare_parameter(
                "sensor_summary_name", "agt_sensor_monitor/summary"
            ).value
        )
        self._safety_status_name = str(
            self.declare_parameter(
                "safety_status_name", "agt_safety/controller"
            ).value
        )

        if min(
            self._publish_rate_hz,
            self._sensor_timeout_s,
            self._localization_timeout_s,
            self._safety_timeout_s,
            self._chassis_timeout_s,
        ) <= 0.0:
            raise ValueError("publish rate and all runtime freshness timeouts must be positive")

        self._lock = threading.RLock()
        self._revision = 0

        self._sensor_summary = None
        self._sensor_seen = float("-inf")
        self._sensor_count = 0
        self._active_map = None
        self._active_map_seen = float("-inf")
        self._localization = None
        self._localization_seen = float("-inf")
        self._mission = None
        self._mission_seen = float("-inf")
        self._safety_status = None
        self._safety_seen = float("-inf")
        self._chassis_status = None
        self._chassis_status_seen = float("-inf")
        self._chassis_status_count = 0
        self._chassis_connected = False
        self._chassis_connected_seen = float("-inf")
        self._bag_status = None
        self._bag_seen = float("-inf")

        self._current_health = SystemHealth()
        self._current_readiness = TaskReadiness()
        self._current_robot_state = RobotState()

        latched = QoSProfile(depth=1)
        latched.reliability = ReliabilityPolicy.RELIABLE
        latched.durability = DurabilityPolicy.TRANSIENT_LOCAL

        self._health_pub = self.create_publisher(
            SystemHealth, "/agt/system/health", latched
        )
        self._readiness_pub = self.create_publisher(
            TaskReadiness, "/agt/system/task_readiness", latched
        )
        self._robot_state_pub = self.create_publisher(
            RobotState, "/agt/system/robot_state", latched
        )

        self.create_subscription(
            DiagnosticArray, "/diagnostics", self._diagnostics_callback, 20
        )
        self.create_subscription(
            MapVersionSummary,
            "/agt/maps/active",
            self._active_map_callback,
            latched,
        )
        self.create_subscription(
            LocalizationStatus,
            "/agt/localization/status",
            self._localization_callback,
            20,
        )
        self.create_subscription(
            MissionStatus,
            "/agt/missions/status",
            self._mission_callback,
            latched,
        )
        self.create_subscription(
            DiagnosticArray,
            "/agt/safety/status",
            self._safety_callback,
            20,
        )
        self.create_subscription(
            DiagnosticArray,
            "/agt/chassis/status",
            self._chassis_status_callback,
            20,
        )
        self.create_subscription(
            Bool,
            "/agt/chassis/connected",
            self._chassis_connected_callback,
            20,
        )
        self.create_subscription(
            BagSessionSummary,
            "/agt/data/bags/status",
            self._bag_callback,
            latched,
        )

        self.create_service(
            GetSystemHealth,
            "/agt/system/health/get",
            self._get_system_health,
        )
        self.create_service(
            EvaluateTaskReadiness,
            "/agt/system/task_readiness/evaluate",
            self._evaluate_task_readiness,
        )
        self.create_service(
            GetRobotState,
            "/agt/system/robot_state/get",
            self._get_robot_state,
        )

        self._refresh_models(publish=True)
        self.create_timer(1.0 / self._publish_rate_hz, self._timer_callback)

    @staticmethod
    def _values(status: DiagnosticStatus) -> dict[str, str]:
        return {item.key: item.value.strip().lower() for item in status.values}

    @staticmethod
    def _age(now: float, stamp: float) -> float:
        if stamp == float("-inf"):
            return 0.0
        return max(0.0, now - stamp)

    @staticmethod
    def _is_fresh(now: float, stamp: float, timeout: float) -> bool:
        return stamp != float("-inf") and now - stamp <= timeout

    @staticmethod
    def _localization_state_name(status: LocalizationStatus | None) -> str:
        if status is None:
            return "UNKNOWN"
        names = {
            LocalizationStatus.STATE_UNINITIALIZED: "UNINITIALIZED",
            LocalizationStatus.STATE_SEARCHING: "SEARCHING",
            LocalizationStatus.STATE_VERIFYING: "VERIFYING",
            LocalizationStatus.STATE_TRACKING: "TRACKING",
            LocalizationStatus.STATE_DEGRADED: "DEGRADED",
            LocalizationStatus.STATE_RECOVERING: "RECOVERING",
            LocalizationStatus.STATE_LOST: "LOST",
            LocalizationStatus.STATE_ERROR: "ERROR",
        }
        return names.get(int(status.state), "UNKNOWN")

    @staticmethod
    def _system_mode(active_mode: str) -> int:
        return {
            "IDLE": RobotState.MODE_IDLE,
            "SENSOR_ONLY": RobotState.MODE_SENSOR_ONLY,
            "MAPPING": RobotState.MODE_MAPPING,
            "LOCALIZATION_DEBUG": RobotState.MODE_LOCALIZATION_DEBUG,
            "NAVIGATION": RobotState.MODE_NAVIGATION,
            "ERROR": RobotState.MODE_ERROR,
        }.get(active_mode, RobotState.MODE_UNKNOWN)

    def _diagnostics_callback(self, message: DiagnosticArray) -> None:
        for status in message.status:
            if status.name != self._sensor_summary_name:
                continue
            with self._lock:
                self._sensor_summary = copy.deepcopy(status)
                self._sensor_seen = time.monotonic()
                self._sensor_count += 1
            return

    def _active_map_callback(self, message: MapVersionSummary) -> None:
        with self._lock:
            self._active_map = copy.deepcopy(message)
            self._active_map_seen = time.monotonic()

    def _localization_callback(self, message: LocalizationStatus) -> None:
        with self._lock:
            self._localization = copy.deepcopy(message)
            self._localization_seen = time.monotonic()

    def _mission_callback(self, message: MissionStatus) -> None:
        with self._lock:
            self._mission = copy.deepcopy(message)
            self._mission_seen = time.monotonic()

    def _safety_callback(self, message: DiagnosticArray) -> None:
        for status in message.status:
            if status.name != "agt_safety/controller":
                continue
            with self._lock:
                self._safety_status = copy.deepcopy(status)
                self._safety_seen = time.monotonic()
            return

    def _chassis_status_callback(self, message: DiagnosticArray) -> None:
        for status in message.status:
            if not status.name.startswith("agt_chassis/"):
                continue
            with self._lock:
                self._chassis_status = copy.deepcopy(status)
                self._chassis_status_seen = time.monotonic()
                self._chassis_status_count += 1
            return

    def _chassis_connected_callback(self, message: Bool) -> None:
        with self._lock:
            self._chassis_connected = bool(message.data)
            self._chassis_connected_seen = time.monotonic()

    def _bag_callback(self, message: BagSessionSummary) -> None:
        with self._lock:
            self._bag_status = copy.deepcopy(message)
            self._bag_seen = time.monotonic()

    def _sensor_component(self, now: float, header) -> tuple[ComponentHealth, bool]:
        fresh = self._is_fresh(now, self._sensor_seen, self._sensor_timeout_s)
        component = ComponentHealth()
        component.header = copy.deepcopy(header)
        component.component_id = "sensor_input"
        component.display_name = "Required sensor input"
        component.required = True
        component.present = fresh
        component.message_age_sec = self._age(now, self._sensor_seen)
        component.message_count = self._sensor_count

        if not fresh or self._sensor_summary is None:
            component.state = ComponentHealth.STATE_ERROR
            component.errors = ["required sensor health evidence is missing or stale"]
            component.detail = "sensor status unknown"
            return component, False

        status = self._sensor_summary
        values = self._values(status)
        required_healthy = values.get("required_streams_healthy") == "true"
        if not required_healthy or status.level >= DiagnosticStatus.ERROR:
            component.state = ComponentHealth.STATE_ERROR
            component.errors = [status.message or "required sensor streams are unhealthy"]
        elif status.level == DiagnosticStatus.WARN:
            component.state = ComponentHealth.STATE_WARN
            component.warnings = [status.message or "sensor input warning"]
        else:
            component.state = ComponentHealth.STATE_OK
        component.detail = status.message
        return component, True

    def _chassis_component(self, now: float, header) -> ComponentHealth:
        fresh = self._is_fresh(
            now, self._chassis_status_seen, self._chassis_timeout_s
        )
        component = ComponentHealth()
        component.header = copy.deepcopy(header)
        component.component_id = "chassis_status"
        component.display_name = "Chassis diagnostics"
        component.required = False
        component.present = fresh
        component.message_age_sec = self._age(now, self._chassis_status_seen)
        component.message_count = self._chassis_status_count

        if not fresh or self._chassis_status is None:
            component.state = ComponentHealth.STATE_UNKNOWN
            component.detail = "chassis diagnostic status unknown"
            return component

        status = self._chassis_status
        if status.level >= DiagnosticStatus.ERROR:
            component.state = ComponentHealth.STATE_ERROR
            component.errors = [status.message or "chassis diagnostic error"]
        elif status.level == DiagnosticStatus.WARN:
            component.state = ComponentHealth.STATE_WARN
            component.warnings = [status.message or "chassis diagnostic warning"]
        else:
            component.state = ComponentHealth.STATE_OK
        component.detail = status.message
        return component

    def _build_health(self, now: float, header) -> tuple[SystemHealth, bool]:
        sensor, sensor_known = self._sensor_component(now, header)
        chassis = self._chassis_component(now, header)
        components = (sensor, chassis)
        evidence = tuple(
            ComponentEvidence(
                component_id=item.component_id,
                required=bool(item.required),
                known=bool(item.present),
                state=int(item.state),
            )
            for item in components
        )

        health = SystemHealth()
        health.header = copy.deepcopy(header)
        health.revision = self._revision
        health.components = list(components)
        health.overall_state = overall_health_state(evidence)

        if not sensor_known:
            health.blocker_codes = ["SENSOR_INPUT_UNKNOWN"]
            health.blocker_messages = ["required sensor health evidence is missing or stale"]
        elif sensor.state == ComponentHealth.STATE_ERROR:
            health.blocker_codes = ["SENSOR_INPUT_UNHEALTHY"]
            health.blocker_messages = [sensor.detail or "required sensor streams are unhealthy"]

        if chassis.state in (ComponentHealth.STATE_WARN, ComponentHealth.STATE_ERROR):
            health.warning_codes = ["CHASSIS_DIAGNOSTIC_WARNING"]
            health.warning_messages = [chassis.detail or "chassis diagnostic warning"]

        return health, sensor_known

    def _build_readiness(
        self, now: float, header, health: SystemHealth, health_known: bool
    ) -> tuple[TaskReadiness, object]:
        map_known = self._active_map is not None
        map_ready = bool(
            map_known
            and self._active_map.active
            and self._active_map.valid
            and self._active_map.state == MapVersionSummary.STATE_READY
        )
        map_id = self._active_map.map_id if map_known else ""
        map_version_id = self._active_map.map_version_id if map_known else ""

        localization_known = self._is_fresh(
            now, self._localization_seen, self._localization_timeout_s
        ) and self._localization is not None
        localization_tracking = bool(
            localization_known
            and self._localization.state == LocalizationStatus.STATE_TRACKING
            and self._localization.pose_valid
            and self._localization.localization_accepted
            and self._localization.error_code == LocalizationStatus.ERROR_NONE
            and not self._localization.status_stale
        )
        localization_map_id = self._localization.map_id if localization_known else ""

        safety_known = self._is_fresh(
            now, self._safety_seen, self._safety_timeout_s
        ) and self._safety_status is not None
        safety_values = self._values(self._safety_status) if safety_known else {}
        motion_enabled = safety_values.get("motion_enabled") == "true"
        estop_latched = safety_values.get("estop_latched") == "true"

        chassis_known = self._is_fresh(
            now, self._chassis_connected_seen, self._chassis_timeout_s
        )
        chassis_connected = bool(chassis_known and self._chassis_connected)

        result = evaluate_navigation_readiness(
            Evidence(
                health_known=health_known,
                health_ok=health.overall_state
                in (SystemHealth.STATE_OK, SystemHealth.STATE_WARN),
                map_known=map_known,
                map_ready=map_ready,
                map_id=map_id,
                map_version_id=map_version_id,
                localization_known=localization_known,
                localization_tracking=localization_tracking,
                localization_map_id=localization_map_id,
                safety_known=safety_known,
                motion_enabled=motion_enabled,
                estop_latched=estop_latched,
                chassis_known=chassis_known,
                chassis_connected=chassis_connected,
            )
        )

        readiness = TaskReadiness()
        readiness.header = copy.deepcopy(header)
        readiness.ready = result.ready
        readiness.active_mode = self._active_mode
        readiness.map_id = result.map_id
        readiness.map_version_id = result.map_version_id
        readiness.localization_state = self._localization_state_name(
            self._localization if localization_known else None
        )
        readiness.health_revision = health.revision
        readiness.blocker_codes = list(result.blocker_codes)
        readiness.blocker_messages = list(result.blocker_messages)
        if health.overall_state == SystemHealth.STATE_WARN:
            readiness.warning_codes = ["SYSTEM_HEALTH_WARN"]
            readiness.warning_messages = ["runtime health contains non-blocking warnings"]
        return readiness, result

    def _build_robot_state(
        self,
        now: float,
        header,
        health: SystemHealth,
        readiness: TaskReadiness,
        readiness_result,
    ) -> RobotState:
        state = RobotState()
        state.header = copy.deepcopy(header)
        state.revision = self._revision
        state.system_mode = self._system_mode(self._active_mode)
        state.active_profile = self._active_profile
        state.managed_process_count = 0
        state.running_process_count = 0

        state.system_health_known = True
        state.system_health_freshness_s = 0.0
        state.system_health = copy.deepcopy(health)
        state.task_readiness_known = True
        state.task_readiness_freshness_s = 0.0
        state.task_readiness = copy.deepcopy(readiness)

        if self._active_map is not None:
            state.active_map_known = True
            state.active_map_freshness_s = self._age(now, self._active_map_seen)
            state.active_map = copy.deepcopy(self._active_map)

        localization_fresh = self._is_fresh(
            now, self._localization_seen, self._localization_timeout_s
        ) and self._localization is not None
        if localization_fresh:
            state.localization_status_known = True
            state.localization_freshness_s = self._age(now, self._localization_seen)
            state.localization = copy.deepcopy(self._localization)

        if self._mission is not None:
            state.mission_status_known = True
            state.mission_freshness_s = self._age(now, self._mission_seen)
            state.mission = copy.deepcopy(self._mission)

        state.nav2_state = RobotState.NAV2_UNKNOWN
        state.nav2_freshness_s = 0.0

        safety_fresh = self._is_fresh(now, self._safety_seen, self._safety_timeout_s)
        if safety_fresh and self._safety_status is not None:
            values = self._values(self._safety_status)
            state.safety_status_known = True
            state.safety_motion_enabled = values.get("motion_enabled") == "true"
            state.emergency_stop = values.get("emergency_stop") == "true"
            state.estop_latched = values.get("estop_latched") == "true"
            state.navigation_ready = values.get("navigation_ready") == "true"
            state.safety_freshness_s = self._age(now, self._safety_seen)

        chassis_fresh = self._is_fresh(
            now, self._chassis_connected_seen, self._chassis_timeout_s
        )
        if chassis_fresh:
            state.chassis_status_known = True
            state.chassis_connected = self._chassis_connected
            state.chassis_control_mode = RobotState.CHASSIS_MODE_UNKNOWN
            state.chassis_status_freshness_s = self._age(
                now, self._chassis_connected_seen
            )
            state.chassis_odometry_freshness_s = 0.0

        if self._bag_status is not None:
            state.bag_status_known = True
            state.bag_freshness_s = self._age(now, self._bag_seen)
            state.bag_session = copy.deepcopy(self._bag_status)

        state.error_code = 0
        state.blocker_codes = list(readiness_result.blocker_codes)
        state.blocker_messages = list(readiness_result.blocker_messages)
        state.message = "READY" if readiness_result.ready else "BLOCKED"
        return state

    def _refresh_models(self, *, publish: bool) -> None:
        with self._lock:
            now = time.monotonic()
            self._revision += 1
            header = self._current_robot_state.header
            header.stamp = self.get_clock().now().to_msg()
            header.frame_id = ""

            health, health_known = self._build_health(now, header)
            readiness, readiness_result = self._build_readiness(
                now, header, health, health_known
            )
            robot_state = self._build_robot_state(
                now, header, health, readiness, readiness_result
            )
            self._current_health = health
            self._current_readiness = readiness
            self._current_robot_state = robot_state

            if publish:
                self._health_pub.publish(copy.deepcopy(health))
                self._readiness_pub.publish(copy.deepcopy(readiness))
                self._robot_state_pub.publish(copy.deepcopy(robot_state))

    def _timer_callback(self) -> None:
        self._refresh_models(publish=True)

    def _get_system_health(self, request, response):
        self._refresh_models(publish=False)
        with self._lock:
            health = copy.deepcopy(self._current_health)
        if not request.include_optional:
            health.components = [item for item in health.components if item.required]
        response.health = health
        return response

    def _evaluate_task_readiness(self, request, response):
        self._refresh_models(publish=False)
        with self._lock:
            readiness = copy.deepcopy(self._current_readiness)

        if request.gate_profile != EvaluateTaskReadiness.Request.PROFILE_TASK_EXECUTION:
            readiness.ready = False
            readiness.blocker_codes.append("UNSUPPORTED_GATE_PROFILE")
            readiness.blocker_messages.append(
                "P0 system manager implements only PROFILE_TASK_EXECUTION"
            )
        if request.validate_task:
            readiness.ready = False
            readiness.blocker_codes.append("TASK_VALIDATION_NOT_AVAILABLE")
            readiness.blocker_messages.append(
                "task asset validation remains owned by the navigation/task registry"
            )
        response.readiness = readiness
        return response

    def _get_robot_state(self, request, response):
        self._refresh_models(publish=False)
        with self._lock:
            state = copy.deepcopy(self._current_robot_state)
        if not request.include_details:
            state.system_health.components = []
        response.success = True
        response.error_code = 0
        response.state = state
        response.message = state.message
        return response


def main(args=None) -> None:
    rclpy.init(args=args)
    node = SystemManager()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
