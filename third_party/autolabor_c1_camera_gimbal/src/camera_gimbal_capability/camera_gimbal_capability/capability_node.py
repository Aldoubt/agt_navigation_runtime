#!/usr/bin/env python3
import math
from pathlib import Path
import threading
import time
from typing import Optional

import cv2
from cv_bridge import CvBridge
import rclpy
from rclpy.action import ActionClient, ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import Image

from camera_gimbal_interfaces.action import AcquireView
from camera_gimbal_interfaces.msg import CapabilityHealth
from pantilt_camera_serial.action import MovePantilt
from pantilt_camera_serial.msg import PantiltStatus

from .policy import (
    is_strictly_fresh,
    resolve_positive_or_default,
    sanitize_tag,
    stamp_to_ns,
    validate_acquire_goal,
)


class CameraGimbalCapability(Node):
    """Atomic capability: verified gimbal arrival -> optional settle -> fresh camera frame."""

    def __init__(self):
        super().__init__('camera_gimbal_capability')
        self.declare_parameter('image_topic', '/cv_camera0/image_raw')
        self.declare_parameter('gimbal_status_topic', '/pantilt_camera_serial0/pantilt_status')
        self.declare_parameter('move_action', '/pantilt_camera_serial0/move_pantilt')
        self.declare_parameter('acquire_action', 'acquire_view')
        self.declare_parameter('health_topic', 'health')
        self.declare_parameter('output_root', '~/autolabor_c1_capture')
        self.declare_parameter('camera_stale_timeout', 1.0)
        self.declare_parameter('gimbal_status_stale_timeout', 1.5)
        self.declare_parameter('move_server_timeout', 2.0)
        self.declare_parameter('default_tolerance', 1.5)
        self.declare_parameter('max_tolerance', 10.0)
        self.declare_parameter('default_motion_timeout', 8.0)
        self.declare_parameter('default_stable_samples', 3)
        self.declare_parameter('default_settle_time', 0.25)
        self.declare_parameter('default_image_timeout', 2.0)
        self.declare_parameter('health_rate', 2.0)

        self._group = ReentrantCallbackGroup()
        self._bridge = CvBridge()
        self._image_condition = threading.Condition()
        self._latest_image: Optional[Image] = None
        self._image_sequence = 0
        self._last_image_monotonic: Optional[float] = None
        self._status_lock = threading.Lock()
        self._latest_status: Optional[PantiltStatus] = None
        self._last_status_monotonic: Optional[float] = None
        self._busy_lock = threading.Lock()
        self._busy = False
        self._last_error = ''

        self._move_client = ActionClient(
            self,
            MovePantilt,
            self.get_parameter('move_action').value,
            callback_group=self._group,
        )
        self._server = ActionServer(
            self,
            AcquireView,
            self.get_parameter('acquire_action').value,
            execute_callback=self._execute_acquire,
            goal_callback=self._goal_callback,
            cancel_callback=self._cancel_callback,
            callback_group=self._group,
        )
        self._health_pub = self.create_publisher(
            CapabilityHealth,
            self.get_parameter('health_topic').value,
            10,
        )
        self.create_subscription(
            Image,
            self.get_parameter('image_topic').value,
            self._image_callback,
            qos_profile_sensor_data,
            callback_group=self._group,
        )
        self.create_subscription(
            PantiltStatus,
            self.get_parameter('gimbal_status_topic').value,
            self._status_callback,
            10,
            callback_group=self._group,
        )
        rate = max(0.2, float(self.get_parameter('health_rate').value))
        self.create_timer(1.0 / rate, self._publish_health, callback_group=self._group)

    @staticmethod
    def _goal_callback(_goal_request):
        # Accept so invalid/busy/unavailable requests receive a structured result code instead
        # of only a generic action rejection at transport level.
        return GoalResponse.ACCEPT

    @staticmethod
    def _cancel_callback(_goal_handle):
        return CancelResponse.ACCEPT

    def _image_callback(self, msg: Image):
        with self._image_condition:
            self._latest_image = msg
            self._image_sequence += 1
            self._last_image_monotonic = time.monotonic()
            self._image_condition.notify_all()

    def _status_callback(self, msg: PantiltStatus):
        with self._status_lock:
            self._latest_status = msg
            self._last_status_monotonic = time.monotonic()

    def _resolve_goal(self, goal):
        tolerance = resolve_positive_or_default(
            goal.tolerance, float(self.get_parameter('default_tolerance').value))
        timeout = resolve_positive_or_default(
            goal.timeout, float(self.get_parameter('default_motion_timeout').value))
        stable_samples = goal.stable_samples if goal.stable_samples > 0 else int(
            self.get_parameter('default_stable_samples').value)
        settle_time = resolve_positive_or_default(
            goal.settle_time, float(self.get_parameter('default_settle_time').value))
        image_timeout = resolve_positive_or_default(
            goal.image_timeout, float(self.get_parameter('default_image_timeout').value))
        return tolerance, timeout, stable_samples, settle_time, image_timeout

    def _component_snapshot(self):
        now = time.monotonic()
        camera_stale = float(self.get_parameter('camera_stale_timeout').value)
        status_stale = float(self.get_parameter('gimbal_status_stale_timeout').value)
        with self._image_condition:
            image_age = math.inf if self._last_image_monotonic is None else now - self._last_image_monotonic
        with self._status_lock:
            status = self._latest_status
            status_age = math.inf if self._last_status_monotonic is None else now - self._last_status_monotonic
        camera_alive = image_age <= camera_stale
        status_fresh = status is not None and status_age <= status_stale
        serial_connected = bool(status_fresh and status.serial_connected)
        feedback_alive = bool(status_fresh and status.feedback_alive)
        move_ready = self._move_client.server_is_ready()
        return camera_alive, image_age, serial_connected, feedback_alive, move_ready, status is not None

    def _publish_health(self):
        msg = CapabilityHealth()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = 'camera_gimbal_capability'
        camera_alive, image_age, serial_connected, feedback_alive, move_ready, have_status = (
            self._component_snapshot()
        )
        msg.camera_alive = camera_alive
        msg.gimbal_serial_connected = serial_connected
        msg.gimbal_feedback_alive = feedback_alive
        msg.move_action_ready = move_ready
        with self._busy_lock:
            msg.busy = self._busy
        msg.camera_age = float(image_age) if math.isfinite(image_age) else -1.0
        msg.last_error = self._last_error
        fully_ready = camera_alive and serial_connected and feedback_alive and move_ready
        if msg.busy:
            msg.state = CapabilityHealth.STATE_BUSY
        elif fully_ready:
            msg.state = CapabilityHealth.STATE_READY
        elif not have_status and not camera_alive:
            msg.state = CapabilityHealth.STATE_NOT_READY
        elif have_status and not serial_connected:
            msg.state = CapabilityHealth.STATE_ERROR
        else:
            msg.state = CapabilityHealth.STATE_DEGRADED
        self._health_pub.publish(msg)

    def _publish_feedback(self, goal_handle, state, stage, move_feedback=None):
        feedback = AcquireView.Feedback()
        feedback.state = state
        feedback.stage = stage
        if move_feedback is not None:
            feedback.current_heading = float(move_feedback.current_heading)
            feedback.current_roll = float(move_feedback.current_roll)
            feedback.current_pitch = float(move_feedback.current_pitch)
            feedback.max_error = float(move_feedback.max_error)
            feedback.stable_count = int(move_feedback.stable_count)
        goal_handle.publish_feedback(feedback)

    def _result(self, code, message, tag):
        result = AcquireView.Result()
        result.success = code == AcquireView.Result.ERROR_OK
        result.error_code = code
        result.message = message
        result.tag = tag
        return result

    def _abort(self, goal_handle, result):
        self._last_error = result.message
        goal_handle.abort()
        return result

    def _cancel(self, goal_handle, result):
        self._last_error = result.message
        goal_handle.canceled()
        return result

    def _wait_future(self, future, goal_handle, timeout_s):
        deadline = time.monotonic() + timeout_s
        while rclpy.ok() and not future.done():
            if goal_handle.is_cancel_requested:
                return 'canceled'
            if time.monotonic() >= deadline:
                return 'timeout'
            time.sleep(0.02)
        return 'done' if future.done() else 'shutdown'

    def _wait_future_ignore_cancel(self, future, timeout_s):
        """Wait for a goal-handshake future even if the public goal was canceled.

        Once a low-level goal request has been sent, returning before its goal handle is known can
        orphan a later-accepted motion. The caller must obtain the handle first, then cancel it.
        """
        deadline = time.monotonic() + timeout_s
        while rclpy.ok() and not future.done():
            if time.monotonic() >= deadline:
                return 'timeout'
            time.sleep(0.02)
        return 'done' if future.done() else 'shutdown'

    def _cancel_move_and_wait(self, move_handle, move_result_future, timeout_s=1.5):
        """Request low-level cancel and briefly wait for its execute loop to apply hold-current."""
        try:
            cancel_future = move_handle.cancel_goal_async()
            deadline = time.monotonic() + timeout_s
            while rclpy.ok() and not cancel_future.done() and time.monotonic() < deadline:
                time.sleep(0.02)
            while rclpy.ok() and not move_result_future.done() and time.monotonic() < deadline:
                time.sleep(0.02)
            return bool(move_result_future.done())
        except Exception as exc:
            self.get_logger().warning(f'low-level cancel wait failed: {exc}')
            return False

    def _wait_settle(self, goal_handle, seconds):
        deadline = time.monotonic() + seconds
        while rclpy.ok() and time.monotonic() < deadline:
            if goal_handle.is_cancel_requested:
                return False
            time.sleep(min(0.02, max(0.001, deadline - time.monotonic())))
        return rclpy.ok()

    def _wait_for_fresh_image(self, goal_handle, threshold_ns, sequence_before, timeout_s):
        deadline = time.monotonic() + timeout_s
        with self._image_condition:
            while rclpy.ok() and time.monotonic() < deadline:
                if goal_handle.is_cancel_requested:
                    return None, 'canceled'
                if self._latest_image is not None and self._image_sequence > sequence_before:
                    stamp = self._latest_image.header.stamp
                    if is_strictly_fresh(stamp.sec, stamp.nanosec, threshold_ns):
                        return self._latest_image, 'ok'
                self._image_condition.wait(timeout=min(0.05, max(0.001, deadline - time.monotonic())))
        return None, 'timeout'

    def _save_image(self, image_msg, tag):
        stamp = image_msg.header.stamp
        root = Path(self.get_parameter('output_root').value).expanduser()
        run_dir = root / time.strftime('%Y%m%d')
        run_dir.mkdir(parents=True, exist_ok=True)
        filename = f'{sanitize_tag(tag)}_{stamp.sec}_{stamp.nanosec:09d}.png'
        path = run_dir / filename
        image = self._bridge.imgmsg_to_cv2(image_msg, desired_encoding='bgr8')
        if not cv2.imwrite(str(path), image):
            raise RuntimeError(f'cv2.imwrite returned false for {path}')
        return str(path)

    def _execute_acquire(self, goal_handle):
        goal = goal_handle.request
        tag = sanitize_tag(goal.tag)
        with self._busy_lock:
            if self._busy:
                return self._abort(
                    goal_handle,
                    self._result(AcquireView.Result.ERROR_BUSY, 'camera-gimbal capability is busy', tag),
                )
            self._busy = True

        try:
            tolerance, timeout, stable_samples, settle_time, image_timeout = self._resolve_goal(goal)
            errors = validate_acquire_goal(
                heading=goal.heading,
                roll=goal.roll,
                pitch=goal.pitch,
                tolerance=tolerance,
                timeout=timeout,
                settle_time=settle_time,
                image_timeout=image_timeout,
                max_tolerance=float(self.get_parameter('max_tolerance').value),
            )
            if errors:
                return self._abort(
                    goal_handle,
                    self._result(AcquireView.Result.ERROR_INVALID_GOAL, '; '.join(errors), tag),
                )

            camera_alive, _, serial_connected, feedback_alive, move_ready, _ = self._component_snapshot()
            if not serial_connected or not feedback_alive or not move_ready:
                return self._abort(
                    goal_handle,
                    self._result(
                        AcquireView.Result.ERROR_GIMBAL_UNAVAILABLE,
                        'gimbal serial/feedback/action is not ready',
                        tag,
                    ),
                )
            if not camera_alive:
                return self._abort(
                    goal_handle,
                    self._result(AcquireView.Result.ERROR_CAMERA_UNAVAILABLE, 'camera stream is stale', tag),
                )

            if goal_handle.is_cancel_requested:
                return self._cancel(
                    goal_handle,
                    self._result(AcquireView.Result.ERROR_CANCELED, 'request canceled before motion', tag),
                )

            move_goal = MovePantilt.Goal()
            move_goal.heading = float(goal.heading)
            move_goal.roll = float(goal.roll)
            move_goal.pitch = float(goal.pitch)
            move_goal.tolerance = float(tolerance)
            move_goal.timeout = float(timeout)
            move_goal.stable_samples = int(stable_samples)

            self._publish_feedback(goal_handle, AcquireView.Feedback.STATE_WAITING_GIMBAL, 'waiting_gimbal')

            def move_feedback_callback(feedback_msg):
                low = feedback_msg.feedback
                state = AcquireView.Feedback.STATE_MOVING
                stage = 'moving'
                if low.state == MovePantilt.Feedback.STATE_STABILIZING:
                    stage = 'stabilizing'
                self._publish_feedback(goal_handle, state, stage, low)

            send_future = self._move_client.send_goal_async(
                move_goal,
                feedback_callback=move_feedback_callback,
            )
            wait_state = self._wait_future_ignore_cancel(send_future, float(
                self.get_parameter('move_server_timeout').value))
            if wait_state != 'done' or send_future.result() is None:
                if goal_handle.is_cancel_requested:
                    return self._cancel(
                        goal_handle,
                        self._result(
                            AcquireView.Result.ERROR_CANCELED,
                            'request canceled while gimbal goal handshake did not complete',
                            tag,
                        ),
                    )
                return self._abort(
                    goal_handle,
                    self._result(AcquireView.Result.ERROR_GIMBAL_UNAVAILABLE, 'MovePantilt goal request timed out', tag),
                )
            move_handle = send_future.result()
            if not move_handle.accepted:
                if goal_handle.is_cancel_requested:
                    return self._cancel(
                        goal_handle,
                        self._result(AcquireView.Result.ERROR_CANCELED, 'request canceled after gimbal goal handshake', tag),
                    )
                return self._abort(
                    goal_handle,
                    self._result(AcquireView.Result.ERROR_GIMBAL_REJECTED, 'MovePantilt goal rejected', tag),
                )

            move_result_future = move_handle.get_result_async()
            if goal_handle.is_cancel_requested:
                self._cancel_move_and_wait(move_handle, move_result_future)
                return self._cancel(
                    goal_handle,
                    self._result(AcquireView.Result.ERROR_CANCELED, 'request canceled after gimbal goal handshake', tag),
                )
            wait_state = self._wait_future(move_result_future, goal_handle, timeout + 2.0)
            if wait_state == 'canceled':
                self._cancel_move_and_wait(move_handle, move_result_future)
                return self._cancel(
                    goal_handle,
                    self._result(AcquireView.Result.ERROR_CANCELED, 'request canceled during gimbal motion', tag),
                )
            if wait_state != 'done' or move_result_future.result() is None:
                self._cancel_move_and_wait(move_handle, move_result_future)
                return self._abort(
                    goal_handle,
                    self._result(AcquireView.Result.ERROR_GIMBAL_FAILED, 'MovePantilt result timed out', tag),
                )
            low_result = move_result_future.result().result
            if not low_result.success:
                if low_result.result_code == MovePantilt.Result.RESULT_CANCELED:
                    return self._cancel(
                        goal_handle,
                        self._result(AcquireView.Result.ERROR_CANCELED, low_result.message, tag),
                    )
                return self._abort(
                    goal_handle,
                    self._result(
                        AcquireView.Result.ERROR_GIMBAL_FAILED,
                        f'MovePantilt failed ({int(low_result.result_code)}): {low_result.message}',
                        tag,
                    ),
                )

            result = self._result(AcquireView.Result.ERROR_OK, 'view acquired', tag)
            result.actual_heading = float(low_result.final_heading)
            result.actual_roll = float(low_result.final_roll)
            result.actual_pitch = float(low_result.final_pitch)
            result.reached_stamp = self.get_clock().now().to_msg()

            self._publish_feedback(goal_handle, AcquireView.Feedback.STATE_SETTLING, 'settling')
            if settle_time > 0.0 and not self._wait_settle(goal_handle, settle_time):
                return self._cancel(
                    goal_handle,
                    self._result(AcquireView.Result.ERROR_CANCELED, 'request canceled during settle time', tag),
                )

            threshold_now = self.get_clock().now()
            threshold_ns = threshold_now.nanoseconds
            with self._image_condition:
                sequence_before = self._image_sequence
            self._publish_feedback(goal_handle, AcquireView.Feedback.STATE_WAITING_IMAGE, 'waiting_fresh_image')
            image_msg, image_state = self._wait_for_fresh_image(
                goal_handle,
                threshold_ns,
                sequence_before,
                image_timeout,
            )
            if image_state == 'canceled':
                return self._cancel(
                    goal_handle,
                    self._result(AcquireView.Result.ERROR_CANCELED, 'request canceled waiting for image', tag),
                )
            if image_msg is None:
                return self._abort(
                    goal_handle,
                    self._result(
                        AcquireView.Result.ERROR_IMAGE_TIMEOUT,
                        'no strictly fresh camera frame arrived after stable settle',
                        tag,
                    ),
                )

            result.image_stamp = image_msg.header.stamp
            if goal_handle.is_cancel_requested:
                result.success = False
                result.error_code = AcquireView.Result.ERROR_CANCELED
                result.message = 'request canceled after image capture'
                return self._cancel(goal_handle, result)

            reached_ns = stamp_to_ns(result.reached_stamp.sec, result.reached_stamp.nanosec)
            image_ns = stamp_to_ns(result.image_stamp.sec, result.image_stamp.nanosec)
            if image_ns <= reached_ns:
                return self._abort(
                    goal_handle,
                    self._result(
                        AcquireView.Result.ERROR_IMAGE_TIMEOUT,
                        'camera frame timestamp is not newer than reached timestamp',
                        tag,
                    ),
                )

            if goal.save_image:
                self._publish_feedback(goal_handle, AcquireView.Feedback.STATE_SAVING, 'saving')
                try:
                    result.image_path = self._save_image(image_msg, tag)
                except Exception as exc:  # cv_bridge / filesystem / encoder failure
                    return self._abort(
                        goal_handle,
                        self._result(
                            AcquireView.Result.ERROR_IMAGE_SAVE_FAILED,
                            f'image save failed: {exc}',
                            tag,
                        ),
                    )
                if goal_handle.is_cancel_requested:
                    result.success = False
                    result.error_code = AcquireView.Result.ERROR_CANCELED
                    result.message = 'request canceled after image save'
                    return self._cancel(goal_handle, result)

            if goal_handle.is_cancel_requested:
                result.success = False
                result.error_code = AcquireView.Result.ERROR_CANCELED
                result.message = 'request canceled after image capture'
                return self._cancel(goal_handle, result)

            self._last_error = ''
            goal_handle.succeed()
            return result
        except Exception as exc:
            self.get_logger().exception(f'AcquireView internal error: {exc}')
            return self._abort(
                goal_handle,
                self._result(AcquireView.Result.ERROR_INTERNAL, f'internal error: {exc}', tag),
            )
        finally:
            with self._busy_lock:
                self._busy = False


def main(args=None):
    rclpy.init(args=args)
    node = CameraGimbalCapability()
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
