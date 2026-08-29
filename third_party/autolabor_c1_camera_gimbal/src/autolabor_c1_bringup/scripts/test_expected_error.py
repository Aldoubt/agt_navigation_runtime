#!/usr/bin/env python3
import sys
import time

import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node

from camera_gimbal_interfaces.action import AcquireView
from camera_gimbal_interfaces.msg import CapabilityHealth


class ExpectedErrorProbe(Node):
    def __init__(self):
        super().__init__('camera_gimbal_expected_error_probe')
        self.declare_parameter('action_name', '/camera_gimbal/acquire_view')
        self.declare_parameter('health_topic', '/camera_gimbal/health')
        self.declare_parameter('expected_error', 300)
        self.declare_parameter('startup_timeout', 8.0)
        self.declare_parameter('heading', 10.0)
        self._health = None
        self._client = ActionClient(self, AcquireView, self.get_parameter('action_name').value)
        self.create_subscription(
            CapabilityHealth,
            self.get_parameter('health_topic').value,
            self._on_health,
            10,
        )

    def _on_health(self, msg):
        self._health = msg

    def _environment_ready_for_case(self):
        expected = int(self.get_parameter('expected_error').value)
        if self._health is None or not self._client.server_is_ready():
            return False
        if expected == AcquireView.Result.ERROR_CAMERA_UNAVAILABLE:
            return (
                self._health.gimbal_serial_connected
                and self._health.gimbal_feedback_alive
                and self._health.move_action_ready
                and not self._health.camera_alive
            )
        if expected == AcquireView.Result.ERROR_GIMBAL_UNAVAILABLE:
            return (
                self._health.move_action_ready
                and not self._health.gimbal_serial_connected
            )
        if expected in (
            AcquireView.Result.ERROR_GIMBAL_FAILED,
            AcquireView.Result.ERROR_IMAGE_TIMEOUT,
        ):
            return self._health.state == CapabilityHealth.STATE_READY
        return True

    def run(self):
        deadline = time.monotonic() + float(self.get_parameter('startup_timeout').value)
        while rclpy.ok() and time.monotonic() < deadline:
            rclpy.spin_once(self, timeout_sec=0.1)
            if self._environment_ready_for_case():
                break
        else:
            self.get_logger().error('FAIL: environment never reached the expected precondition')
            return False

        goal = AcquireView.Goal()
        goal.heading = float(self.get_parameter('heading').value)
        goal.roll = 0.0
        goal.pitch = 0.0
        goal.tolerance = 1.5
        goal.timeout = 2.0
        goal.stable_samples = 3
        goal.settle_time = 0.1
        goal.image_timeout = 0.5
        goal.save_image = False
        goal.tag = 'expected_error_probe'

        send_future = self._client.send_goal_async(goal)
        rclpy.spin_until_future_complete(self, send_future, timeout_sec=2.0)
        if not send_future.done() or send_future.result() is None or not send_future.result().accepted:
            self.get_logger().error('FAIL: AcquireView goal was not accepted for structured error reporting')
            return False
        result_future = send_future.result().get_result_async()
        rclpy.spin_until_future_complete(self, result_future, timeout_sec=5.0)
        if not result_future.done() or result_future.result() is None:
            self.get_logger().error('FAIL: no AcquireView result')
            return False
        result = result_future.result().result
        expected = int(self.get_parameter('expected_error').value)
        ok = (not result.success) and int(result.error_code) == expected
        if ok:
            self.get_logger().info(
                'PASS: received expected error_code=%d message=%s', expected, result.message)
        else:
            self.get_logger().error(
                'FAIL: expected error=%d but got success=%s error=%d message=%s',
                expected, result.success, int(result.error_code), result.message)
        return ok


def main():
    rclpy.init()
    node = ExpectedErrorProbe()
    try:
        return 0 if node.run() else 1
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    sys.exit(main())
