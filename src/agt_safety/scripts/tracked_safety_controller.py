#!/usr/bin/env python3

import math
import threading
import time

from agt_interfaces.msg import LocalizationStatus
import rclpy
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus, KeyValue
from geometry_msgs.msg import Twist
from rclpy.callback_groups import MutuallyExclusiveCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from std_msgs.msg import Bool
from std_srvs.srv import SetBool, Trigger


SENSOR_SUMMARY_NAME = "agt_sensor_monitor/summary"


def clamp(value: float, lower: float, upper: float) -> float:
    return min(max(value, lower), upper)


def project_track_speeds(
    linear: float, angular: float, track_width: float, max_track_speed: float
) -> tuple[float, float]:
    left = linear - angular * track_width * 0.5
    right = linear + angular * track_width * 0.5
    peak = max(abs(left), abs(right))
    if max_track_speed > 0.0 and peak > max_track_speed:
        scale = max_track_speed / peak
        linear *= scale
        angular *= scale
    return linear, angular


def slew(current: float, target: float, rise_rate: float, fall_rate: float, dt: float) -> float:
    rate = rise_rate if abs(target) > abs(current) else fall_rate
    return current + clamp(target - current, -rate * dt, rate * dt)


def localization_status_is_valid(message: LocalizationStatus) -> bool:
    return (
        message.state == LocalizationStatus.STATE_TRACKING
        and message.pose_valid
        and message.localization_accepted
        and message.error_code == LocalizationStatus.ERROR_NONE
        and not message.status_stale
    )


def sensor_summary_is_ready(
    message: DiagnosticArray, summary_name: str = SENSOR_SUMMARY_NAME
) -> bool | None:
    """Return required sensor readiness when the configured summary is present.

    ``None`` means this DiagnosticArray did not contain sensor-monitor summary
    evidence and therefore must not refresh the safety freshness timer.
    """
    for status in message.status:
        if status.name != summary_name:
            continue
        values = {item.key: item.value.strip().lower() for item in status.values}
        declared_ready = values.get("required_streams_healthy") == "true"
        return declared_ready and status.level < DiagnosticStatus.ERROR
    return None


class TrackedSafetyController(Node):
    def __init__(self) -> None:
        super().__init__("agt_tracked_safety_controller")
        self._nav_timeout = self.declare_parameter("navigation_timeout", 0.5).value
        self._manual_timeout = self.declare_parameter("manual_timeout", 0.35).value
        self._publish_rate = self.declare_parameter("publish_rate", 20.0).value
        self._max_forward = self.declare_parameter("max_forward_speed", 0.5).value
        self._max_reverse = self.declare_parameter("max_reverse_speed", 0.25).value
        self._max_angular = self.declare_parameter("max_angular_speed", 0.6).value
        self._max_track = self.declare_parameter("max_track_speed", 0.65).value
        self._track_width = self.declare_parameter("effective_track_width", 0.62).value
        self._linear_accel = self.declare_parameter("max_linear_acceleration", 0.35).value
        self._linear_decel = self.declare_parameter("max_linear_deceleration", 0.7).value
        self._angular_accel = self.declare_parameter("max_angular_acceleration", 0.8).value
        self._angular_decel = self.declare_parameter("max_angular_deceleration", 1.2).value
        self._motion_enabled = self.declare_parameter("startup_motion_enabled", False).value
        self._require_localization_valid = self.declare_parameter(
            "require_localization_valid", True
        ).value
        self._localization_status_timeout = self.declare_parameter(
            "localization_status_timeout", 10.0
        ).value
        self._require_sensor_input_ready = self.declare_parameter(
            "require_sensor_input_ready", False
        ).value
        self._sensor_status_timeout = self.declare_parameter(
            "sensor_status_timeout", 1.5
        ).value
        self._sensor_diagnostics_topic = self.declare_parameter(
            "sensor_diagnostics_topic", "/diagnostics"
        ).value
        self._sensor_summary_name = self.declare_parameter(
            "sensor_summary_name", SENSOR_SUMMARY_NAME
        ).value
        if self._localization_status_timeout <= 0.0:
            raise ValueError("localization_status_timeout must be positive")
        if self._sensor_status_timeout <= 0.0:
            raise ValueError("sensor_status_timeout must be positive")

        self._nav_cmd = Twist()
        self._manual_cmd = Twist()
        self._nav_stamp = float("-inf")
        self._manual_stamp = float("-inf")
        self._physical_estop = False
        self._estop_latched = False
        self._localization_valid = False
        self._localization_stamp = float("-inf")
        self._sensor_input_ready = False
        self._sensor_status_stamp = float("-inf")
        self._linear_out = 0.0
        self._angular_out = 0.0
        self._last_tick = time.monotonic()
        self._reason = "startup_disabled" if not self._motion_enabled else "input_timeout"
        self._state_lock = threading.RLock()
        runtime_group = MutuallyExclusiveCallbackGroup()
        service_group = MutuallyExclusiveCallbackGroup()

        self._publisher = self.create_publisher(Twist, "/agt/safety/cmd_vel", 10)
        self._status_publisher = self.create_publisher(
            DiagnosticArray, "/agt/safety/status", 10
        )
        self.create_subscription(
            Twist, "/agt/navigation/cmd_vel", self._navigation_callback, 10,
            callback_group=runtime_group,
        )
        self.create_subscription(
            Twist, "/agt/cmd_vel_manual", self._manual_callback, 10,
            callback_group=runtime_group,
        )
        self.create_subscription(
            Bool, "/agt/safety/emergency_stop", self._estop_callback, 10,
            callback_group=runtime_group,
        )
        self.create_subscription(
            LocalizationStatus,
            "/agt/localization/status",
            self._localization_callback,
            10,
            callback_group=runtime_group,
        )
        self.create_subscription(
            DiagnosticArray,
            self._sensor_diagnostics_topic,
            self._sensor_diagnostics_callback,
            10,
            callback_group=runtime_group,
        )
        self.create_service(
            SetBool, "/agt/safety/set_motion_enabled", self._set_motion_enabled,
            callback_group=service_group,
        )
        self.create_service(
            Trigger, "/agt/safety/reset_emergency_stop", self._reset_estop,
            callback_group=service_group,
        )
        self._timer = self.create_timer(
            1.0 / self._publish_rate, self._tick, callback_group=runtime_group
        )

    @staticmethod
    def _valid(cmd: Twist) -> bool:
        values = (
            cmd.linear.x,
            cmd.linear.y,
            cmd.linear.z,
            cmd.angular.x,
            cmd.angular.y,
            cmd.angular.z,
        )
        return all(math.isfinite(value) for value in values)

    def _navigation_callback(self, msg: Twist) -> None:
        with self._state_lock:
            if self._valid(msg):
                self._nav_cmd = msg
                self._nav_stamp = time.monotonic()
            else:
                self._nav_stamp = float("-inf")
                self.get_logger().error("rejected non-finite navigation command")

    def _manual_callback(self, msg: Twist) -> None:
        with self._state_lock:
            if self._valid(msg):
                self._manual_cmd = msg
                self._manual_stamp = time.monotonic()
            else:
                self._manual_stamp = float("-inf")
                self.get_logger().error("rejected non-finite manual command")

    def _estop_callback(self, msg: Bool) -> None:
        with self._state_lock:
            self._physical_estop = msg.data
            if msg.data:
                self._estop_latched = True
                self._motion_enabled = False

    def _localization_callback(self, msg: LocalizationStatus) -> None:
        with self._state_lock:
            self._localization_valid = localization_status_is_valid(msg)
            self._localization_stamp = time.monotonic()

    def _sensor_diagnostics_callback(self, msg: DiagnosticArray) -> None:
        ready = sensor_summary_is_ready(msg, self._sensor_summary_name)
        if ready is None:
            return
        with self._state_lock:
            self._sensor_input_ready = ready
            self._sensor_status_stamp = time.monotonic()

    def _localization_is_valid(self, now: float) -> bool:
        return self._localization_valid and (
            now - self._localization_stamp <= self._localization_status_timeout
        )

    def _sensor_input_is_ready(self, now: float) -> bool:
        if not self._require_sensor_input_ready:
            return True
        return self._sensor_input_ready and (
            now - self._sensor_status_stamp <= self._sensor_status_timeout
        )

    def _set_motion_enabled(self, request: SetBool.Request, response: SetBool.Response):
        with self._state_lock:
            if request.data and (self._physical_estop or self._estop_latched):
                response.success = False
                response.message = "clear the emergency stop before enabling motion"
                return response
            self._motion_enabled = request.data
            response.success = True
            response.message = "motion enabled" if request.data else "motion disabled"
            return response

    def _reset_estop(self, _request: Trigger.Request, response: Trigger.Response):
        with self._state_lock:
            if self._physical_estop:
                response.success = False
                response.message = "physical emergency-stop input is still active"
                return response
            self._estop_latched = False
            response.success = True
            response.message = "emergency stop latch cleared; motion remains explicitly controlled"
            return response

    def _target(self, now: float) -> tuple[float, float, str, bool]:
        if self._physical_estop or self._estop_latched:
            return 0.0, 0.0, "emergency_stop", True
        if not self._motion_enabled:
            return 0.0, 0.0, "motion_disabled", True
        if now - self._manual_stamp <= self._manual_timeout:
            cmd = self._manual_cmd
            source = "manual"
        elif now - self._nav_stamp <= self._nav_timeout:
            if self._require_localization_valid and not self._localization_is_valid(now):
                return 0.0, 0.0, "localization_invalid", True
            if not self._sensor_input_is_ready(now):
                return 0.0, 0.0, "sensor_input_unhealthy", True
            cmd = self._nav_cmd
            source = "navigation"
        else:
            return 0.0, 0.0, "input_timeout", True

        linear = clamp(cmd.linear.x, -self._max_reverse, self._max_forward)
        angular = clamp(cmd.angular.z, -self._max_angular, self._max_angular)
        linear, angular = project_track_speeds(
            linear, angular, self._track_width, self._max_track
        )
        return linear, angular, source, False

    def _tick(self) -> None:
        with self._state_lock:
            now = time.monotonic()
            dt = min(max(now - self._last_tick, 0.0), 0.2)
            self._last_tick = now
            target_linear, target_angular, self._reason, immediate_stop = self._target(now)
            if immediate_stop:
                self._linear_out = 0.0
                self._angular_out = 0.0
            else:
                self._linear_out = slew(
                    self._linear_out,
                    target_linear,
                    self._linear_accel,
                    self._linear_decel,
                    dt,
                )
                self._angular_out = slew(
                    self._angular_out,
                    target_angular,
                    self._angular_accel,
                    self._angular_decel,
                    dt,
                )

            output = Twist()
            output.linear.x = self._linear_out
            output.angular.z = self._angular_out
            self._publisher.publish(output)
            self._publish_status()

    def _publish_status(self) -> None:
        now = time.monotonic()
        status = DiagnosticStatus()
        status.name = "agt_safety/tracked_controller"
        status.hardware_id = "bunker"
        stopped = self._reason in (
            "emergency_stop",
            "motion_disabled",
            "input_timeout",
            "localization_invalid",
            "sensor_input_unhealthy",
        )
        status.level = DiagnosticStatus.WARN if stopped else DiagnosticStatus.OK
        status.message = self._reason
        localization_valid = self._localization_is_valid(now)
        sensor_input_ready = self._sensor_input_is_ready(now)
        status.values = [
            KeyValue(key="motion_enabled", value=str(self._motion_enabled).lower()),
            KeyValue(key="estop_latched", value=str(self._estop_latched).lower()),
            KeyValue(
                key="emergency_stop",
                value=str(self._physical_estop or self._estop_latched).lower(),
            ),
            KeyValue(
                key="navigation_ready",
                value=str(
                    self._motion_enabled
                    and not self._physical_estop
                    and not self._estop_latched
                    and localization_valid
                    and sensor_input_ready
                ).lower(),
            ),
            KeyValue(key="localization_valid", value=str(localization_valid).lower()),
            KeyValue(key="sensor_input_ready", value=str(sensor_input_ready).lower()),
            KeyValue(
                key="sensor_input_required",
                value=str(self._require_sensor_input_ready).lower(),
            ),
            KeyValue(key="linear_output", value=f"{self._linear_out:.4f}"),
            KeyValue(key="angular_output", value=f"{self._angular_out:.4f}"),
        ]
        array = DiagnosticArray()
        array.header.stamp = self.get_clock().now().to_msg()
        array.status = [status]
        self._status_publisher.publish(array)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = TrackedSafetyController()
    executor = MultiThreadedExecutor(num_threads=2)
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        node._timer.cancel()
        executor.shutdown()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
