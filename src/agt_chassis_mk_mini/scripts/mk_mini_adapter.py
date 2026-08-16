#!/usr/bin/env python3

import math
import time

from agt_chassis_mk_mini.ackermann_math import twist_to_ackermann
from agt_interfaces.msg import AckermannCommand
from geometry_msgs.msg import Twist
import rclpy
from rclpy.node import Node


class MkMiniAdapter(Node):
    def __init__(self) -> None:
        super().__init__("agt_mk_mini_adapter")
        input_topic = self.declare_parameter(
            "input_topic", "/agt/chassis/cmd_vel"
        ).value
        output_topic = self.declare_parameter(
            "output_topic", "/agt/chassis/backend/ackermann_command"
        ).value
        self._wheelbase = float(self.declare_parameter("wheelbase", 0.600).value)
        self._min_turning_radius = float(
            self.declare_parameter("min_turning_radius", 1.500).value
        )
        self._speed_deadband = float(
            self.declare_parameter("speed_deadband", 0.01).value
        )
        self._command_timeout = float(
            self.declare_parameter("command_timeout", 0.20).value
        )
        self._publish_rate = float(self.declare_parameter("publish_rate", 30.0).value)
        self._max_forward_speed = float(
            self.declare_parameter("max_forward_speed", 1.0).value
        )
        self._max_reverse_speed = float(
            self.declare_parameter("max_reverse_speed", 0.5).value
        )
        if self._wheelbase <= 0.0:
            raise ValueError("wheelbase must be positive")
        if self._min_turning_radius <= 0.0:
            raise ValueError("min_turning_radius must be positive")
        if self._command_timeout <= 0.0 or self._publish_rate <= 0.0:
            raise ValueError("command timeout and publish rate must be positive")

        self._last_command = Twist()
        self._last_stamp = float("-inf")
        self._publisher = self.create_publisher(AckermannCommand, output_topic, 10)
        self.create_subscription(Twist, input_topic, self._callback, 10)
        self.create_timer(1.0 / self._publish_rate, self._tick)

    @staticmethod
    def _is_finite(message: Twist) -> bool:
        return math.isfinite(message.linear.x) and math.isfinite(message.angular.z)

    def _callback(self, message: Twist) -> None:
        if not self._is_finite(message):
            self._last_stamp = float("-inf")
            self.get_logger().error("rejected non-finite chassis command")
            return
        self._last_command = message
        self._last_stamp = time.monotonic()

    def _tick(self) -> None:
        output = AckermannCommand()
        output.header.stamp = self.get_clock().now().to_msg()
        if time.monotonic() - self._last_stamp <= self._command_timeout:
            speed = min(
                max(self._last_command.linear.x, -self._max_reverse_speed),
                self._max_forward_speed,
            )
            setpoint = twist_to_ackermann(
                speed,
                self._last_command.angular.z,
                self._wheelbase,
                self._min_turning_radius,
                speed_deadband=self._speed_deadband,
            )
            output.speed_mps = setpoint.speed_mps
            output.steering_angle_rad = setpoint.steering_angle_rad
        self._publisher.publish(output)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MkMiniAdapter()
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
