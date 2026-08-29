#!/usr/bin/env python3
import json
import os
from pathlib import Path
import sys
import time

import cv2
from cv_bridge import CvBridge
import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import Image

from pantilt_camera_serial.action import MovePantilt
from pantilt_camera_serial.msg import PantiltAngleInfo, PantiltStatus


class GimbalAcceptance(Node):
    def __init__(self):
        super().__init__('autolabor_c1_gimbal_acceptance')
        self.declare_parameter('image_topic', '/cv_camera0/image_raw')
        self.declare_parameter('angle_topic', '/pantilt_camera_serial0/pantilt_angle_info')
        self.declare_parameter('status_topic', '/pantilt_camera_serial0/pantilt_status')
        self.declare_parameter('action_name', '/pantilt_camera_serial0/move_pantilt')
        self.declare_parameter('tolerance', 1.5)
        self.declare_parameter('motion_timeout', 8.0)
        self.declare_parameter('stable_samples', 3)
        self.declare_parameter('startup_timeout', 10.0)
        self.declare_parameter('fresh_image_timeout', 2.0)
        self.declare_parameter(
            'save_dir', str(Path.home() / 'autolabor_c1_inspection' / time.strftime('%Y%m%d_%H%M%S')))

        self.bridge = CvBridge()
        self.latest_image = None
        self.image_sequence = 0
        self.latest_angle = None
        self.latest_status = None
        self.summary = {'started_at': time.strftime('%Y-%m-%dT%H:%M:%S'), 'tests': []}

        self.create_subscription(
            Image, self.get_parameter('image_topic').value, self.image_callback, qos_profile_sensor_data)
        self.create_subscription(
            PantiltAngleInfo, self.get_parameter('angle_topic').value, self.angle_callback, qos_profile_sensor_data)
        self.create_subscription(
            PantiltStatus, self.get_parameter('status_topic').value, self.status_callback, 10)
        self.action_client = ActionClient(
            self, MovePantilt, self.get_parameter('action_name').value)

        self.save_dir = Path(os.path.expanduser(self.get_parameter('save_dir').value))
        self.save_dir.mkdir(parents=True, exist_ok=True)

    def image_callback(self, msg):
        self.latest_image = msg
        self.image_sequence += 1

    def angle_callback(self, msg):
        self.latest_angle = msg

    def status_callback(self, msg):
        self.latest_status = msg

    def wait_for_startup(self):
        timeout = float(self.get_parameter('startup_timeout').value)
        deadline = time.monotonic() + timeout
        while rclpy.ok() and time.monotonic() < deadline:
            rclpy.spin_once(self, timeout_sec=0.1)
            ready = (
                self.latest_image is not None and
                self.latest_angle is not None and
                self.latest_status is not None and
                self.latest_status.serial_connected and
                self.latest_status.feedback_alive
            )
            if ready and self.action_client.wait_for_server(timeout_sec=0.0):
                return True
        return False

    def move_and_wait(self, heading, roll=0.0, pitch=0.0):
        goal = MovePantilt.Goal()
        goal.heading = float(heading)
        goal.roll = float(roll)
        goal.pitch = float(pitch)
        goal.tolerance = float(self.get_parameter('tolerance').value)
        goal.timeout = float(self.get_parameter('motion_timeout').value)
        goal.stable_samples = int(self.get_parameter('stable_samples').value)

        send_future = self.action_client.send_goal_async(goal)
        rclpy.spin_until_future_complete(self, send_future, timeout_sec=2.0)
        if not send_future.done() or send_future.result() is None:
            return False, 'action goal request timed out', None
        goal_handle = send_future.result()
        if not goal_handle.accepted:
            return False, 'action goal rejected', None

        result_future = goal_handle.get_result_async()
        wait_timeout = goal.timeout + 2.0
        rclpy.spin_until_future_complete(self, result_future, timeout_sec=wait_timeout)
        if not result_future.done() or result_future.result() is None:
            cancel_future = goal_handle.cancel_goal_async()
            rclpy.spin_until_future_complete(self, cancel_future, timeout_sec=1.0)
            return False, 'action result timed out; cancel requested', None
        result = result_future.result().result
        return bool(result.success), result.message, result

    def wait_for_fresh_image(self, previous_sequence):
        timeout = float(self.get_parameter('fresh_image_timeout').value)
        deadline = time.monotonic() + timeout
        while rclpy.ok() and time.monotonic() < deadline:
            rclpy.spin_once(self, timeout_sec=0.05)
            if self.image_sequence > previous_sequence and self.latest_image is not None:
                return self.latest_image
        return None

    def save_image(self, image_msg, label):
        if image_msg is None:
            return None
        image = self.bridge.imgmsg_to_cv2(image_msg, desired_encoding='bgr8')
        stamp = image_msg.header.stamp
        filename = self.save_dir / f'{label}_{stamp.sec}_{stamp.nanosec:09d}.png'
        if not cv2.imwrite(str(filename), image):
            return None
        return str(filename)

    def run(self):
        if not self.wait_for_startup():
            self.get_logger().error('FAIL: camera/gimbal/action server did not become healthy')
            return False

        tests = [
            ('center', 0.0),
            ('left', -30.0),
            ('right', 30.0),
        ]
        all_ok = True

        for label, heading in tests:
            before_image = self.image_sequence
            ok, message, result = self.move_and_wait(heading)
            record = {'name': label, 'target_heading': heading, 'motion_ok': ok, 'message': message}
            if result is not None:
                record.update({
                    'result_code': int(result.result_code),
                    'final_heading': float(result.final_heading),
                    'final_roll': float(result.final_roll),
                    'final_pitch': float(result.final_pitch),
                })
            if not ok:
                self.get_logger().error('FAIL %s: %s' % (label, message))
                record['image_ok'] = False
                self.summary['tests'].append(record)
                all_ok = False
                break

            image_msg = self.wait_for_fresh_image(before_image)
            path = self.save_image(image_msg, label)
            record['image_ok'] = path is not None
            record['image'] = path
            if image_msg is not None:
                record['image_stamp'] = {
                    'sec': int(image_msg.header.stamp.sec),
                    'nanosec': int(image_msg.header.stamp.nanosec),
                }
            if self.latest_angle is not None:
                record['angle_stamp'] = {
                    'sec': int(self.latest_angle.header.stamp.sec),
                    'nanosec': int(self.latest_angle.header.stamp.nanosec),
                }
            self.summary['tests'].append(record)
            if path is None:
                self.get_logger().error('FAIL %s: no fresh image after stable arrival' % label)
                all_ok = False
                break
            self.get_logger().info('PASS %s: stable arrival + fresh image: %s' % (label, path))

        # Best-effort safe return to center; it is itself part of acceptance.
        center_ok, center_message, center_result = self.move_and_wait(0.0)
        self.summary['return_center'] = {
            'ok': center_ok,
            'message': center_message,
            'result_code': int(center_result.result_code) if center_result is not None else None,
        }
        if not center_ok:
            self.get_logger().error('FAIL return-center: %s' % center_message)
            all_ok = False

        self.summary['passed'] = all_ok
        self.summary['finished_at'] = time.strftime('%Y-%m-%dT%H:%M:%S')
        summary_path = self.save_dir / 'acceptance_summary.json'
        summary_path.write_text(json.dumps(self.summary, ensure_ascii=False, indent=2), encoding='utf-8')

        if all_ok:
            self.get_logger().info('PASS: all gimbal acceptance steps succeeded')
        else:
            self.get_logger().error('FAIL: one or more gimbal acceptance steps failed')
        self.get_logger().info('acceptance artifacts: %s' % self.save_dir)
        return all_ok


def main():
    rclpy.init()
    node = GimbalAcceptance()
    try:
        return 0 if node.run() else 1
    except KeyboardInterrupt:
        node.get_logger().error('FAIL: acceptance interrupted')
        return 1
    except Exception as exc:
        node.get_logger().exception('FAIL: acceptance exception: %s' % exc)
        return 1
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    sys.exit(main())
