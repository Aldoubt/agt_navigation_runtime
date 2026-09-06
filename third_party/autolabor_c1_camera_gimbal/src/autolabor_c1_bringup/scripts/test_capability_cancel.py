#!/usr/bin/env python3
import sys
import time

import rclpy
from action_msgs.msg import GoalStatus
from rclpy.action import ActionClient
from rclpy.node import Node

from camera_gimbal_interfaces.action import AcquireView
from camera_gimbal_interfaces.msg import CapabilityHealth
from pantilt_camera_serial.msg import PantiltStatus


class CancelProbe(Node):
    def __init__(self):
        super().__init__('camera_gimbal_cancel_probe')
        self._health = None
        self._low_status = None
        self._client = ActionClient(self, AcquireView, '/camera_gimbal/acquire_view')
        self.create_subscription(CapabilityHealth, '/camera_gimbal/health', self._on_health, 10)
        self.create_subscription(PantiltStatus, '/pantilt_camera_serial0/pantilt_status', self._on_low_status, 10)

    def _on_health(self, msg):
        self._health = msg

    def _on_low_status(self, msg):
        self._low_status = msg

    def wait_ready(self):
        deadline = time.monotonic() + 8.0
        while rclpy.ok() and time.monotonic() < deadline:
            rclpy.spin_once(self, timeout_sec=0.1)
            if self._client.server_is_ready() and self._health is not None:
                if self._health.state == CapabilityHealth.STATE_READY:
                    return True
        return False

    def run(self):
        if not self.wait_ready():
            self.get_logger().error('FAIL: capability never became READY')
            return False

        goal = AcquireView.Goal()
        goal.heading = 60.0
        goal.roll = 0.0
        goal.pitch = 0.0
        goal.tolerance = 1.5
        goal.timeout = 8.0
        goal.stable_samples = 3
        goal.settle_time = 0.1
        goal.image_timeout = 1.0
        goal.save_image = False
        goal.tag = 'cancel_probe'

        send_future = self._client.send_goal_async(goal)
        rclpy.spin_until_future_complete(self, send_future, timeout_sec=2.0)
        if not send_future.done() or send_future.result() is None or not send_future.result().accepted:
            self.get_logger().error('FAIL: cancel probe goal was not accepted')
            return False
        handle = send_future.result()
        result_future = handle.get_result_async()

        # Let the low-level fake action enter motion, then cancel the public capability.
        deadline = time.monotonic() + 1.0
        while rclpy.ok() and time.monotonic() < deadline:
            rclpy.spin_once(self, timeout_sec=0.05)
            if self._low_status is not None and self._low_status.target_active:
                break
        if self._low_status is None or not self._low_status.target_active:
            self.get_logger().error('FAIL: low-level motion never became active before cancel')
            return False

        cancel_future = handle.cancel_goal_async()
        rclpy.spin_until_future_complete(self, cancel_future, timeout_sec=2.0)
        if not cancel_future.done() or cancel_future.result() is None:
            self.get_logger().error('FAIL: public cancel request timed out')
            return False

        rclpy.spin_until_future_complete(self, result_future, timeout_sec=4.0)
        if not result_future.done() or result_future.result() is None:
            self.get_logger().error('FAIL: canceled public action produced no result')
            return False
        wrapped = result_future.result()
        result = wrapped.result
        if wrapped.status != GoalStatus.STATUS_CANCELED:
            self.get_logger().error(
                f'FAIL: public action status is not CANCELED: {wrapped.status}')
            return False
        if result.success or int(result.error_code) != AcquireView.Result.ERROR_CANCELED:
            self.get_logger().error(
                f'FAIL: expected ERROR_CANCELED={AcquireView.Result.ERROR_CANCELED} '
                f'but got success={result.success} code={int(result.error_code)}')
            return False

        # The public node waits for low-level cancellation completion before returning.
        deadline = time.monotonic() + 1.0
        while rclpy.ok() and time.monotonic() < deadline:
            rclpy.spin_once(self, timeout_sec=0.05)
            if self._low_status is not None and not self._low_status.target_active:
                self.get_logger().info('PASS: public cancel propagated and low-level target_active=false')
                return True
        self.get_logger().error('FAIL: low-level target_active remained true after public cancel result')
        return False


def main():
    rclpy.init()
    node = CancelProbe()
    try:
        return 0 if node.run() else 1
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    sys.exit(main())
