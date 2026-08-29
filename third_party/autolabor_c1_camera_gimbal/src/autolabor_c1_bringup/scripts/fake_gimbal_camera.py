#!/usr/bin/env python3
import math
import threading
import time

import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import Image

from pantilt_camera_serial.action import MovePantilt
from pantilt_camera_serial.msg import PantiltAngleInfo, PantiltStatus


class FakeGimbalCamera(Node):
    """Deterministic no-hardware fixture for capability integration tests."""

    def __init__(self):
        super().__init__('fake_gimbal_camera')
        self.declare_parameter('move_delay', 0.35)
        self.declare_parameter('image_rate', 20.0)
        self.declare_parameter('status_rate', 10.0)
        self.declare_parameter('fail_motion', False)
        self.declare_parameter('publish_images', True)
        self.declare_parameter('serial_connected', True)
        self.declare_parameter('drop_images_on_motion', False)

        self._group = ReentrantCallbackGroup()
        self._lock = threading.Lock()
        self._angles = [0.0, 0.0, 0.0]
        self._target = [0.0, 0.0, 0.0]
        self._active = False
        self._reached = True
        self._rx_count = 0
        self._image_drop_latched = False

        self._status_pub = self.create_publisher(PantiltStatus, 'pantilt_status', 10)
        self._angle_pub = self.create_publisher(PantiltAngleInfo, 'pantilt_angle_info', qos_profile_sensor_data)
        self._image_pub = self.create_publisher(Image, '/cv_camera0/image_raw', qos_profile_sensor_data)
        self._action_server = ActionServer(
            self,
            MovePantilt,
            'move_pantilt',
            execute_callback=self._execute_move,
            goal_callback=self._goal_callback,
            cancel_callback=lambda _gh: CancelResponse.ACCEPT,
            callback_group=self._group,
        )
        status_rate = max(1.0, float(self.get_parameter('status_rate').value))
        image_rate = max(1.0, float(self.get_parameter('image_rate').value))
        self.create_timer(1.0 / status_rate, self._publish_status, callback_group=self._group)
        self.create_timer(1.0 / image_rate, self._publish_image, callback_group=self._group)

    @staticmethod
    def _goal_callback(goal):
        finite = all(math.isfinite(v) for v in (goal.heading, goal.roll, goal.pitch))
        inside = -160.0 <= goal.heading <= 160.0 and -40.0 <= goal.roll <= 40.0 and -90.0 <= goal.pitch <= 90.0
        return GoalResponse.ACCEPT if finite and inside else GoalResponse.REJECT

    def _execute_move(self, goal_handle):
        goal = goal_handle.request
        result = MovePantilt.Result()
        move_delay = max(0.05, float(self.get_parameter('move_delay').value))
        steps = max(3, int(goal.stable_samples) if goal.stable_samples else 3)
        with self._lock:
            start = list(self._angles)
            self._target = [float(goal.heading), float(goal.roll), float(goal.pitch)]
            self._active = True
            self._reached = False

        for index in range(steps + 2):
            if goal_handle.is_cancel_requested:
                with self._lock:
                    self._active = False
                    self._reached = False
                result.success = False
                result.result_code = MovePantilt.Result.RESULT_CANCELED
                result.message = 'fake motion canceled'
                goal_handle.canceled()
                return result
            ratio = min(1.0, (index + 1) / float(steps + 1))
            with self._lock:
                self._angles = [
                    start[i] + (self._target[i] - start[i]) * ratio for i in range(3)
                ]
                current = list(self._angles)
            feedback = MovePantilt.Feedback()
            feedback.current_heading, feedback.current_roll, feedback.current_pitch = current
            feedback.max_error = max(abs(current[i] - self._target[i]) for i in range(3))
            if ratio >= 0.85:
                feedback.state = MovePantilt.Feedback.STATE_STABILIZING
                feedback.stable_count = max(1, index - steps + 2)
            else:
                feedback.state = MovePantilt.Feedback.STATE_MOVING
                feedback.stable_count = 0
            goal_handle.publish_feedback(feedback)
            time.sleep(move_delay / float(steps + 2))

        if bool(self.get_parameter('fail_motion').value):
            with self._lock:
                self._active = False
                self._reached = False
            result.success = False
            result.result_code = MovePantilt.Result.RESULT_MOTION_TIMEOUT
            result.message = 'fake injected motion failure'
            result.final_heading, result.final_roll, result.final_pitch = current
            goal_handle.abort()
            return result

        with self._lock:
            self._angles = list(self._target)
            current = list(self._angles)
            self._active = False
            self._reached = True
        result.success = True
        result.result_code = MovePantilt.Result.RESULT_OK
        result.message = 'fake target reached and stable'
        result.final_heading, result.final_roll, result.final_pitch = current
        goal_handle.succeed()
        return result

    def _publish_status(self):
        now = self.get_clock().now().to_msg()
        with self._lock:
            angles = list(self._angles)
            target = list(self._target)
            active = self._active
            reached = self._reached
            self._rx_count += 1
            rx_count = self._rx_count
        status = PantiltStatus()
        status.header.stamp = now
        status.header.frame_id = 'fake_gimbal_link'
        status.state = PantiltStatus.STATE_MOVING if active else (
            PantiltStatus.STATE_REACHED if reached else PantiltStatus.STATE_IDLE)
        connected = bool(self.get_parameter('serial_connected').value)
        status.serial_connected = connected
        status.feedback_alive = connected
        status.target_active = active
        status.target_reached = reached
        status.target_heading, status.target_roll, status.target_pitch = target
        status.max_error = max(abs(angles[i] - target[i]) for i in range(3))
        status.stable_count = 3 if reached else 0
        status.rx_frame_count = rx_count
        status.crc_error_count = 0
        status.protocol_error_count = 0
        status.last_error = ''
        self._status_pub.publish(status)

        angle = PantiltAngleInfo()
        angle.header.stamp = now
        angle.header.frame_id = 'fake_gimbal_link'
        angle.heading, angle.roll, angle.pitch = angles
        angle.encoder_heading, angle.encoder_roll, angle.encoder_pitch = angles
        self._angle_pub.publish(angle)

    def _publish_image(self):
        if not bool(self.get_parameter('publish_images').value):
            return
        if bool(self.get_parameter('drop_images_on_motion').value):
            with self._lock:
                if self._active:
                    self._image_drop_latched = True
                if self._image_drop_latched:
                    return
        msg = Image()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = 'fake_camera_link'
        msg.height = 48
        msg.width = 64
        msg.encoding = 'rgb8'
        msg.is_bigendian = 0
        msg.step = msg.width * 3
        msg.data = bytes([32, 64, 96]) * (msg.width * msg.height)
        self._image_pub.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = FakeGimbalCamera()
    executor = MultiThreadedExecutor(num_threads=4)
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
