#!/usr/bin/env python3

import time

from agt_interfaces.msg import LocalizationStatus
from nav2_msgs.srv import ManageLifecycleNodes
import rclpy
from rclpy.node import Node


def localization_status_is_ready(message: LocalizationStatus) -> bool:
    return (
        message.state == LocalizationStatus.STATE_TRACKING
        and message.pose_valid
        and message.localization_accepted
        and message.error_code == LocalizationStatus.ERROR_NONE
        and not message.status_stale
    )


class LocalizationNavigationGate(Node):
    def __init__(self) -> None:
        super().__init__("agt_localization_navigation_gate")
        self._manager_service = self.declare_parameter(
            "manager_service", "/lifecycle_manager_navigation/manage_nodes"
        ).value
        self._status_timeout = float(
            self.declare_parameter("localization_status_timeout", 10.0).value
        )
        self._retry_period = float(
            self.declare_parameter("lifecycle_retry_period", 1.0).value
        )
        self._invalid_grace_period = float(
            self.declare_parameter("localization_invalid_grace_period", 1.0).value
        )
        self._pause_on_invalid = bool(
            self.declare_parameter("pause_on_invalid", True).value
        )
        if (
            self._status_timeout <= 0.0
            or self._retry_period <= 0.0
            or self._invalid_grace_period <= 0.0
        ):
            raise ValueError("localization gate timeouts must be positive")

        self._status_valid = False
        self._status_stamp = float("-inf")
        self._invalid_since = None
        self._nav_started = False
        self._nav_paused = False
        self._recovery_reset_required = False
        self._desired_command = None
        self._pending_command = None
        self._in_flight = False
        self._client = self.create_client(ManageLifecycleNodes, self._manager_service)
        self.create_subscription(
            LocalizationStatus,
            "/agt/localization/status",
            self._localization_callback,
            10,
        )
        self.create_timer(self._retry_period, self._tick)

    @property
    def navigation_started(self) -> bool:
        return self._nav_started

    def _localization_callback(self, message: LocalizationStatus) -> None:
        self._status_valid = localization_status_is_ready(message)
        self._status_stamp = time.monotonic()
        if self._status_valid:
            self._invalid_since = None
            self._desired_command = ManageLifecycleNodes.Request.STARTUP
        elif self._pause_on_invalid:
            self._invalid_since = self._invalid_since or self._status_stamp
            self._desired_command = ManageLifecycleNodes.Request.PAUSE

    def _status_is_fresh(self) -> bool:
        return self._status_valid and (
            time.monotonic() - self._status_stamp <= self._status_timeout
        )

    def _tick(self) -> None:
        status_fresh = self._status_is_fresh()
        if status_fresh:
            self._desired_command = ManageLifecycleNodes.Request.STARTUP
            self._invalid_since = None
        elif self._pause_on_invalid:
            self._invalid_since = self._invalid_since or time.monotonic()
            if time.monotonic() - self._invalid_since < self._invalid_grace_period:
                return
            self._desired_command = ManageLifecycleNodes.Request.PAUSE

        if self._in_flight or not self._client.service_is_ready():
            return
        if self._desired_command is None:
            return
        command = self._desired_command
        if command == ManageLifecycleNodes.Request.STARTUP:
            if self._nav_started:
                return
            if self._recovery_reset_required:
                command = ManageLifecycleNodes.Request.RESET
            elif self._nav_paused:
                command = ManageLifecycleNodes.Request.RESUME
        elif command == ManageLifecycleNodes.Request.PAUSE and not self._nav_started:
            return
        self._send(command)

    def _send(self, command: int) -> None:
        request = ManageLifecycleNodes.Request()
        request.command = command
        self._pending_command = command
        self._in_flight = True
        future = self._client.call_async(request)
        future.add_done_callback(self._command_done)

    def _command_done(self, future) -> None:
        self._in_flight = False
        command = self._pending_command
        self._pending_command = None
        try:
            response = future.result()
            success = bool(response.success)
        except Exception as error:
            self.get_logger().error("Nav2 lifecycle command failed: %s", error)
            if command in (
                ManageLifecycleNodes.Request.STARTUP,
                ManageLifecycleNodes.Request.RESUME,
            ):
                self._nav_started = False
                self._nav_paused = False
                self._recovery_reset_required = True
            elif command == ManageLifecycleNodes.Request.RESET:
                self._recovery_reset_required = False
            return
        if not success:
            self.get_logger().error(
                "Nav2 lifecycle command %s was rejected", command
            )
            if command in (
                ManageLifecycleNodes.Request.STARTUP,
                ManageLifecycleNodes.Request.RESUME,
            ):
                self._nav_started = False
                self._nav_paused = False
                self._recovery_reset_required = True
            elif command == ManageLifecycleNodes.Request.RESET:
                self._recovery_reset_required = False
            return
        if command == ManageLifecycleNodes.Request.STARTUP:
            self._nav_started = True
            self._nav_paused = False
            self._recovery_reset_required = False
            self.get_logger().info(
                "Nav2 lifecycle manager started after accepted localization"
            )
        elif command == ManageLifecycleNodes.Request.PAUSE:
            self._nav_started = False
            self._nav_paused = True
            self.get_logger().warn(
                "Nav2 lifecycle manager paused because localization is not ready"
            )
        elif command == ManageLifecycleNodes.Request.RESUME:
            self._nav_started = True
            self._nav_paused = False
            self._recovery_reset_required = False
            self.get_logger().info(
                "Nav2 lifecycle manager resumed after localization recovered"
            )
        elif command == ManageLifecycleNodes.Request.RESET:
            self._nav_started = False
            self._nav_paused = False
            self._recovery_reset_required = False
            self.get_logger().warn(
                "Nav2 lifecycle manager reset after a rejected startup"
            )


def main(args=None) -> None:
    rclpy.init(args=args)
    node = LocalizationNavigationGate()
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
