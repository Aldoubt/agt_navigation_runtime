#!/usr/bin/env python3
import json
from pathlib import Path
import sys
import time

import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node

from camera_gimbal_interfaces.action import AcquireView
from camera_gimbal_interfaces.msg import CapabilityHealth


def stamp_ns(stamp):
    return int(stamp.sec) * 1_000_000_000 + int(stamp.nanosec)


class CapabilityAcceptance(Node):
    def __init__(self):
        super().__init__('camera_gimbal_capability_acceptance')
        self.declare_parameter('action_name', '/camera_gimbal/acquire_view')
        self.declare_parameter('health_topic', '/camera_gimbal/health')
        self.declare_parameter('startup_timeout', 10.0)
        self.declare_parameter('goal_timeout', 12.0)
        self.declare_parameter('tolerance', 1.5)
        self.declare_parameter('settle_time', 0.25)
        self.declare_parameter('image_timeout', 2.0)
        self.declare_parameter('output_dir', '')
        self.declare_parameter('save_image', True)

        self._client = ActionClient(self, AcquireView, self.get_parameter('action_name').value)
        self._latest_health = None
        self.create_subscription(
            CapabilityHealth,
            self.get_parameter('health_topic').value,
            self._health_callback,
            10,
        )
        requested = str(self.get_parameter('output_dir').value).strip()
        if requested:
            self.output_dir = Path(requested).expanduser()
        else:
            self.output_dir = Path.home() / 'autolabor_c1_acceptance' / time.strftime('%Y%m%d_%H%M%S')
        self.output_dir.mkdir(parents=True, exist_ok=True)
        self.summary = {
            'schema_version': 1,
            'kind': 'camera_gimbal_capability_acceptance',
            'started_at': time.strftime('%Y-%m-%dT%H:%M:%S'),
            'tests': [],
            'passed': False,
        }

    def _health_callback(self, msg):
        self._latest_health = msg

    def wait_ready(self):
        deadline = time.monotonic() + float(self.get_parameter('startup_timeout').value)
        while rclpy.ok() and time.monotonic() < deadline:
            rclpy.spin_once(self, timeout_sec=0.1)
            if self._client.server_is_ready() and self._latest_health is not None:
                if self._latest_health.state == CapabilityHealth.STATE_READY:
                    return True
        return False

    def send_goal(self, *, heading, roll=0.0, pitch=0.0, tag, expect_success=True):
        goal = AcquireView.Goal()
        goal.heading = float(heading)
        goal.roll = float(roll)
        goal.pitch = float(pitch)
        goal.tolerance = float(self.get_parameter('tolerance').value)
        goal.timeout = 8.0
        goal.stable_samples = 3
        goal.settle_time = float(self.get_parameter('settle_time').value)
        goal.image_timeout = float(self.get_parameter('image_timeout').value)
        goal.save_image = bool(self.get_parameter('save_image').value) and expect_success
        goal.tag = tag

        send_future = self._client.send_goal_async(goal)
        rclpy.spin_until_future_complete(self, send_future, timeout_sec=3.0)
        if not send_future.done() or send_future.result() is None:
            return {'name': tag, 'pass': False, 'reason': 'goal request timeout'}
        handle = send_future.result()
        if not handle.accepted:
            return {'name': tag, 'pass': False, 'reason': 'transport-level goal rejection'}
        result_future = handle.get_result_async()
        rclpy.spin_until_future_complete(
            self,
            result_future,
            timeout_sec=float(self.get_parameter('goal_timeout').value),
        )
        if not result_future.done() or result_future.result() is None:
            handle.cancel_goal_async()
            return {'name': tag, 'pass': False, 'reason': 'result timeout'}

        result = result_future.result().result
        record = {
            'name': tag,
            'target': {'heading': heading, 'roll': roll, 'pitch': pitch},
            'success': bool(result.success),
            'error_code': int(result.error_code),
            'message': result.message,
            'actual': {
                'heading': float(result.actual_heading),
                'roll': float(result.actual_roll),
                'pitch': float(result.actual_pitch),
            },
            'reached_stamp_ns': stamp_ns(result.reached_stamp),
            'image_stamp_ns': stamp_ns(result.image_stamp),
            'image_path': result.image_path,
        }

        if expect_success:
            tolerance = float(self.get_parameter('tolerance').value)
            max_error = max(
                abs(float(result.actual_heading) - heading),
                abs(float(result.actual_roll) - roll),
                abs(float(result.actual_pitch) - pitch),
            )
            image_exists = bool(result.image_path) and Path(result.image_path).is_file()
            fresh = record['image_stamp_ns'] > record['reached_stamp_ns'] > 0
            record['max_error'] = max_error
            record['image_exists'] = image_exists
            record['fresh_after_reached'] = fresh
            record['pass'] = (
                bool(result.success)
                and int(result.error_code) == AcquireView.Result.ERROR_OK
                and max_error <= tolerance + 1e-6
                and fresh
                and (image_exists if goal.save_image else True)
            )
        else:
            record['pass'] = (
                not bool(result.success)
                and int(result.error_code) == AcquireView.Result.ERROR_INVALID_GOAL
            )
        return record

    def run(self):
        if not self.wait_ready():
            self.summary['failure'] = 'capability did not become READY before startup timeout'
            return self._finish(False)

        invalid = self.send_goal(heading=999.0, tag='invalid_goal', expect_success=False)
        self.summary['tests'].append(invalid)
        if not invalid['pass']:
            return self._finish(False)

        for name, heading in [('center', 0.0), ('left', -30.0), ('right', 30.0), ('return_center', 0.0)]:
            record = self.send_goal(heading=heading, tag=name, expect_success=True)
            self.summary['tests'].append(record)
            if not record['pass']:
                return self._finish(False)

        return self._finish(True)

    def _finish(self, passed):
        self.summary['passed'] = bool(passed)
        self.summary['finished_at'] = time.strftime('%Y-%m-%dT%H:%M:%S')
        path = self.output_dir / 'capability_summary.json'
        path.write_text(json.dumps(self.summary, ensure_ascii=False, indent=2), encoding='utf-8')
        if passed:
            self.get_logger().info('PASS: capability acceptance passed: %s' % path)
        else:
            self.get_logger().error('FAIL: capability acceptance failed: %s' % path)
        return passed


def main():
    rclpy.init()
    node = CapabilityAcceptance()
    try:
        return 0 if node.run() else 1
    except KeyboardInterrupt:
        node.get_logger().error('FAIL: interrupted')
        return 1
    except Exception as exc:
        node.get_logger().exception('FAIL: exception: %s' % exc)
        return 1
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    sys.exit(main())
