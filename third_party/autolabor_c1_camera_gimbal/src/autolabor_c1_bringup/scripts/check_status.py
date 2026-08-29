#!/usr/bin/env python3
import sys
import time

import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import Image

from pantilt_camera_serial.msg import PantiltAngleInfo, PantiltStatus


class HealthChecker(Node):
    def __init__(self):
        super().__init__('autolabor_c1_health_checker')
        self.declare_parameter('image_topic', '/cv_camera0/image_raw')
        self.declare_parameter('angle_topic', '/pantilt_camera_serial0/pantilt_angle_info')
        self.declare_parameter('status_topic', '/pantilt_camera_serial0/pantilt_status')
        self.declare_parameter('startup_timeout', 5.0)
        self.declare_parameter('stale_timeout', 2.0)

        self.image_count = 0
        self.angle_count = 0
        self.last_image_monotonic = None
        self.last_angle_monotonic = None
        self.latest_angle = None
        self.latest_status = None

        self.create_subscription(
            Image, self.get_parameter('image_topic').value, self.image_callback, qos_profile_sensor_data)
        self.create_subscription(
            PantiltAngleInfo, self.get_parameter('angle_topic').value, self.angle_callback, qos_profile_sensor_data)
        self.create_subscription(
            PantiltStatus, self.get_parameter('status_topic').value, self.status_callback, 10)

    def image_callback(self, _msg):
        self.image_count += 1
        self.last_image_monotonic = time.monotonic()

    def angle_callback(self, msg):
        self.angle_count += 1
        self.last_angle_monotonic = time.monotonic()
        self.latest_angle = msg

    def status_callback(self, msg):
        self.latest_status = msg

    def wait_for_inputs(self):
        deadline = time.monotonic() + float(self.get_parameter('startup_timeout').value)
        while rclpy.ok() and time.monotonic() < deadline:
            rclpy.spin_once(self, timeout_sec=0.1)
            if self.image_count > 0 and self.angle_count > 0 and self.latest_status is not None:
                return True
        return False

    def evaluate(self):
        stale_timeout = float(self.get_parameter('stale_timeout').value)
        now = time.monotonic()
        failures = []

        if self.last_image_monotonic is None or now - self.last_image_monotonic > stale_timeout:
            failures.append('image stream missing or stale')
        if self.last_angle_monotonic is None or now - self.last_angle_monotonic > stale_timeout:
            failures.append('gimbal angle feedback missing or stale')
        if self.latest_status is None:
            failures.append('gimbal status missing')
        else:
            if not self.latest_status.serial_connected:
                failures.append('gimbal serial disconnected')
            if not self.latest_status.feedback_alive:
                failures.append('gimbal feedback not healthy')

        if self.latest_angle is not None:
            self.get_logger().info(
                'encoder H=%.2f R=%.2f P=%.2f; image=%d angle=%d' % (
                    self.latest_angle.encoder_heading,
                    self.latest_angle.encoder_roll,
                    self.latest_angle.encoder_pitch,
                    self.image_count,
                    self.angle_count,
                )
            )

        if failures:
            for failure in failures:
                self.get_logger().error('FAIL: %s' % failure)
            return False
        self.get_logger().info('PASS: camera stream, serial link and gimbal feedback are healthy')
        return True


def main():
    rclpy.init()
    node = HealthChecker()
    try:
        if not node.wait_for_inputs():
            node.get_logger().error('FAIL: startup timeout waiting for camera/gimbal/status')
            return 1
        return 0 if node.evaluate() else 1
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    sys.exit(main())
