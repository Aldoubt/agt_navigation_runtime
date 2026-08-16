#!/usr/bin/env python3

import math
import time

from agt_chassis_mk_mini.mk_mini_command_state import (
    CommandStateMachine,
    gear_feedback_allows_motion,
)
from agt_chassis_mk_mini.mk_mini_protocol import (
    BMS_INFO_FB_ID,
    CTRL_CMD_ID,
    CTRL_FB_ID,
    LEFT_REAR_WHEEL_FB_ID,
    RIGHT_REAR_WHEEL_FB_ID,
    Gear as ProtocolGear,
    ProtocolError,
    decode_bms_info,
    decode_ctrl_feedback,
    decode_wheel_feedback,
    encode_ctrl_command,
    next_alive_counter,
)
from agt_chassis_mk_mini.socketcan_transport import SocketCanTransport
from agt_interfaces.msg import AckermannCommand
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus, KeyValue
from geometry_msgs.msg import TwistWithCovarianceStamped
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import BatteryState
from std_msgs.msg import Bool


class MkMiniCanBackend(Node):
    def __init__(self) -> None:
        super().__init__("agt_mk_mini_can_backend")

        self._operation_mode = str(
            self.declare_parameter("operation_mode", "monitor").value
        ).lower()
        if self._operation_mode not in {"monitor", "control"}:
            raise ValueError("operation_mode must be 'monitor' or 'control'")

        self._can_interface = str(self.declare_parameter("can_interface", "can0").value)
        self._input_topic = str(
            self.declare_parameter(
                "input_topic", "/agt/chassis/backend/ackermann_command"
            ).value
        )
        self._tx_period_sec = float(self.declare_parameter("tx_period_sec", 0.01).value)
        self._rx_poll_period_sec = float(
            self.declare_parameter("rx_poll_period_sec", 0.005).value
        )
        self._reconnect_period_sec = float(
            self.declare_parameter("reconnect_period_sec", 1.0).value
        )
        self._command_timeout = float(
            self.declare_parameter("command_timeout", 0.20).value
        )
        self._feedback_timeout = float(
            self.declare_parameter("feedback_timeout", 0.20).value
        )
        self._speed_deadband = float(
            self.declare_parameter("speed_deadband", 0.01).value
        )
        self._shift_speed_threshold = float(
            self.declare_parameter("shift_speed_threshold", 0.05).value
        )
        self._gear_shift_hold_sec = float(
            self.declare_parameter("gear_shift_hold_sec", 0.05).value
        )
        self._park_hold_sec = float(
            self.declare_parameter("park_hold_sec", 0.20).value
        )
        self._wheelbase = float(self.declare_parameter("wheelbase", 0.600).value)
        self._steering_scale = float(
            self.declare_parameter("steering_scale", 1.0).value
        )
        self._steering_offset_deg = float(
            self.declare_parameter("steering_offset_deg", 0.0).value
        )
        self._vcu_steering_soft_limit_deg = float(
            self.declare_parameter("vcu_steering_soft_limit_deg", 34.0).value
        )
        self._steering_calibration_confirmed = bool(
            self.declare_parameter("steering_calibration_confirmed", False).value
        )
        self._allow_uncalibrated_control = bool(
            self.declare_parameter("allow_uncalibrated_control", False).value
        )
        self._base_frame = str(
            self.declare_parameter("base_frame", "base_footprint").value
        )

        positive = {
            "tx_period_sec": self._tx_period_sec,
            "rx_poll_period_sec": self._rx_poll_period_sec,
            "reconnect_period_sec": self._reconnect_period_sec,
            "command_timeout": self._command_timeout,
            "feedback_timeout": self._feedback_timeout,
            "wheelbase": self._wheelbase,
            "vcu_steering_soft_limit_deg": self._vcu_steering_soft_limit_deg,
        }
        for name, value in positive.items():
            if not math.isfinite(value) or value <= 0.0:
                raise ValueError(f"{name} must be finite and positive")
        if not math.isfinite(self._steering_scale) or abs(self._steering_scale) < 1e-9:
            raise ValueError("steering_scale must be finite and non-zero")
        if not math.isfinite(self._steering_offset_deg):
            raise ValueError("steering_offset_deg must be finite")

        self._state = CommandStateMachine(
            command_timeout=self._command_timeout,
            feedback_timeout=self._feedback_timeout,
            speed_deadband=self._speed_deadband,
            shift_speed_threshold=self._shift_speed_threshold,
            gear_shift_hold_sec=self._gear_shift_hold_sec,
            park_hold_sec=self._park_hold_sec,
        )
        self._transport = SocketCanTransport(self._can_interface)
        self._next_reconnect_time = 0.0
        self._alive_counter = 0
        self._last_ctrl_feedback_time = float("-inf")
        self._last_ctrl_mode = None
        self._last_ctrl_gear = None
        self._last_ctrl_counter = None
        self._last_feedback_steering_rad = 0.0
        self._last_left_wheel = None
        self._last_right_wheel = None
        self._last_requested_vcu_steering_deg = 0.0
        self._last_state_reason = "startup"

        self._rx_frames = 0
        self._tx_frames = 0
        self._protocol_errors = 0
        self._counter_gaps = 0
        self._transport_errors = 0
        self._calibration_blocks = 0
        self._gear_feedback_blocks = 0

        self._feedback_pub = self.create_publisher(
            AckermannCommand,
            "/agt/chassis/backend/ackermann_feedback",
            10,
        )
        self._connected_pub = self.create_publisher(Bool, "/agt/chassis/connected", 10)
        self._diagnostic_pub = self.create_publisher(
            DiagnosticArray, "/agt/chassis/status", 10
        )
        self._wheel_twist_pub = self.create_publisher(
            TwistWithCovarianceStamped,
            "/agt/chassis/wheel_twist",
            10,
        )
        self._battery_pub = self.create_publisher(BatteryState, "/battery", 10)
        self.create_subscription(AckermannCommand, self._input_topic, self._command_callback, 10)

        self.create_timer(self._rx_poll_period_sec, self._rx_tick)
        if self._operation_mode == "control":
            self.create_timer(self._tx_period_sec, self._tx_tick)
        self.create_timer(0.20, self._status_tick)

        self._ensure_transport(time.monotonic())
        if self._operation_mode == "control" and not self._calibration_allows_motion():
            self.get_logger().warning(
                "MK-mini control mode started with steering calibration unconfirmed; "
                "moving commands will be blocked"
            )

    def _calibration_allows_motion(self) -> bool:
        return self._steering_calibration_confirmed or self._allow_uncalibrated_control

    def _equivalent_rad_to_vcu_deg(self, angle_rad: float) -> float:
        equivalent_deg = math.degrees(angle_rad)
        requested = equivalent_deg * self._steering_scale + self._steering_offset_deg
        return min(
            max(requested, -self._vcu_steering_soft_limit_deg),
            self._vcu_steering_soft_limit_deg,
        )

    def _vcu_deg_to_equivalent_rad(self, vcu_deg: float) -> float:
        equivalent_deg = (vcu_deg - self._steering_offset_deg) / self._steering_scale
        return math.radians(equivalent_deg)

    def _command_callback(self, message: AckermannCommand) -> None:
        if not (
            math.isfinite(message.speed_mps)
            and math.isfinite(message.steering_angle_rad)
        ):
            self.get_logger().error("rejected non-finite MK-mini Ackermann command")
            return

        now = time.monotonic()
        speed = float(message.speed_mps)
        steering_deg = self._equivalent_rad_to_vcu_deg(message.steering_angle_rad)
        if abs(speed) > self._speed_deadband and not self._calibration_allows_motion():
            self._calibration_blocks += 1
            self._state.update_command(speed_mps=0.0, steering_deg=0.0, stamp=now)
            return

        self._last_requested_vcu_steering_deg = steering_deg
        self._state.update_command(
            speed_mps=speed,
            steering_deg=steering_deg,
            stamp=now,
        )

    def _ensure_transport(self, now: float) -> bool:
        if self._transport.is_open:
            return True
        if now < self._next_reconnect_time:
            return False
        self._next_reconnect_time = now + self._reconnect_period_sec
        try:
            self._transport.open()
            self.get_logger().info(f"opened SocketCAN interface {self._can_interface}")
            return True
        except OSError as exc:
            self._transport_errors += 1
            self.get_logger().error(
                f"failed to open SocketCAN interface {self._can_interface}: {exc}"
            )
            return False

    def _mark_transport_failed(self, exc: Exception) -> None:
        self._transport_errors += 1
        self.get_logger().error(f"SocketCAN transport error: {exc}")
        self._transport.close()
        self._next_reconnect_time = time.monotonic() + self._reconnect_period_sec

    @staticmethod
    def _signed_speed(gear: ProtocolGear, speed_mps: float) -> float:
        if gear == ProtocolGear.REVERSE:
            return -abs(speed_mps)
        if gear == ProtocolGear.DRIVE:
            return abs(speed_mps)
        return 0.0

    def _handle_ctrl_feedback(self, payload: bytes, now: float) -> None:
        feedback = decode_ctrl_feedback(payload)
        if self._last_ctrl_counter is not None:
            expected = next_alive_counter(self._last_ctrl_counter)
            if feedback.alive_counter != expected:
                self._counter_gaps += 1
        self._last_ctrl_counter = feedback.alive_counter
        self._last_ctrl_feedback_time = now
        self._last_ctrl_mode = feedback.mode
        self._last_ctrl_gear = feedback.gear

        signed_speed = self._signed_speed(feedback.gear, feedback.speed_mps)
        self._state.update_feedback(speed_mps=signed_speed, stamp=now)
        equivalent_rad = self._vcu_deg_to_equivalent_rad(feedback.steering_deg)
        self._last_feedback_steering_rad = equivalent_rad

        message = AckermannCommand()
        message.header.stamp = self.get_clock().now().to_msg()
        message.speed_mps = signed_speed
        message.steering_angle_rad = equivalent_rad
        self._feedback_pub.publish(message)
        self._publish_wheel_twist_if_ready(now)

    def _handle_wheel_feedback(self, payload: bytes, now: float, *, left: bool) -> None:
        feedback = decode_wheel_feedback(payload)
        observation = (feedback.speed_mps, feedback.pulse_count, now)
        if left:
            self._last_left_wheel = observation
        else:
            self._last_right_wheel = observation
        self._publish_wheel_twist_if_ready(now)

    def _handle_bms_info(self, payload: bytes) -> None:
        feedback = decode_bms_info(payload)
        message = BatteryState()
        message.header.stamp = self.get_clock().now().to_msg()
        message.voltage = feedback.voltage_v
        message.current = feedback.current_a
        message.charge = feedback.remaining_capacity_ah
        message.present = True
        self._battery_pub.publish(message)

    def _publish_wheel_twist_if_ready(self, now: float) -> None:
        if self._last_left_wheel is None or self._last_right_wheel is None:
            return
        if now - self._last_ctrl_feedback_time > self._feedback_timeout:
            return
        left_speed, _, left_stamp = self._last_left_wheel
        right_speed, _, right_stamp = self._last_right_wheel
        if (
            now - left_stamp > self._feedback_timeout
            or now - right_stamp > self._feedback_timeout
        ):
            return
        linear_speed = 0.5 * (left_speed + right_speed)
        yaw_rate = (
            linear_speed * math.tan(self._last_feedback_steering_rad) / self._wheelbase
        )
        message = TwistWithCovarianceStamped()
        message.header.stamp = self.get_clock().now().to_msg()
        message.header.frame_id = self._base_frame
        message.twist.twist.linear.x = linear_speed
        message.twist.twist.angular.z = yaw_rate
        self._wheel_twist_pub.publish(message)

    def _handle_frame(self, can_id: int, payload: bytes, now: float) -> None:
        if can_id == CTRL_FB_ID:
            self._handle_ctrl_feedback(payload, now)
        elif can_id == LEFT_REAR_WHEEL_FB_ID:
            self._handle_wheel_feedback(payload, now, left=True)
        elif can_id == RIGHT_REAR_WHEEL_FB_ID:
            self._handle_wheel_feedback(payload, now, left=False)
        elif can_id == BMS_INFO_FB_ID:
            self._handle_bms_info(payload)

    def _rx_tick(self) -> None:
        now = time.monotonic()
        if not self._ensure_transport(now):
            return
        for _ in range(128):
            try:
                frame = self._transport.recv_nonblocking()
            except (OSError, ValueError) as exc:
                if isinstance(exc, OSError):
                    self._mark_transport_failed(exc)
                    return
                self._protocol_errors += 1
                continue
            if frame is None:
                return
            self._rx_frames += 1
            try:
                self._handle_frame(frame.can_id, frame.data, time.monotonic())
            except ProtocolError:
                self._protocol_errors += 1

    def _tx_tick(self) -> None:
        if self._operation_mode != "control":
            return
        now = time.monotonic()
        if not self._ensure_transport(now):
            return

        output = self._state.step(now)
        self._last_state_reason = output.reason
        speed = output.speed_mps
        steering = output.steering_deg

        if not self._calibration_allows_motion() and speed > self._speed_deadband:
            speed = 0.0
            steering = 0.0
            self._calibration_blocks += 1
            self._last_state_reason = f"{output.reason}+calibration_block"

        if self._last_ctrl_mode is not None and self._last_ctrl_mode != 0:
            speed = 0.0
            self._last_state_reason = f"{output.reason}+vcu_not_auto"

        if speed > self._speed_deadband and not gear_feedback_allows_motion(
            output.gear, self._last_ctrl_gear
        ):
            speed = 0.0
            self._gear_feedback_blocks += 1
            self._last_state_reason = f"{output.reason}+gear_feedback_mismatch"

        steering = min(
            max(steering, -self._vcu_steering_soft_limit_deg),
            self._vcu_steering_soft_limit_deg,
        )
        payload = encode_ctrl_command(
            gear=ProtocolGear(int(output.gear)),
            speed_mps=speed,
            steering_deg=steering,
            alive_counter=self._alive_counter,
        )
        try:
            self._transport.send(CTRL_CMD_ID, payload)
        except OSError as exc:
            self._mark_transport_failed(exc)
            return
        self._tx_frames += 1
        self._alive_counter = next_alive_counter(self._alive_counter)

    def _connected(self, now: float) -> bool:
        return (
            self._transport.is_open
            and 0.0 <= now - self._last_ctrl_feedback_time <= self._feedback_timeout
        )

    def _status_tick(self) -> None:
        now = time.monotonic()
        connected = self._connected(now)
        connected_message = Bool()
        connected_message.data = connected
        self._connected_pub.publish(connected_message)

        array = DiagnosticArray()
        array.header.stamp = self.get_clock().now().to_msg()
        status = DiagnosticStatus()
        status.name = "agt_chassis_mk_mini/can_backend"
        status.hardware_id = "mk_mini"
        if not self._transport.is_open or not connected:
            status.level = DiagnosticStatus.ERROR
            status.message = "CAN/VCU feedback unavailable"
        elif self._operation_mode == "control" and not self._calibration_allows_motion():
            status.level = DiagnosticStatus.WARN
            status.message = "control motion blocked: steering calibration unconfirmed"
        elif self._last_ctrl_mode not in (None, 0):
            status.level = DiagnosticStatus.WARN
            status.message = f"VCU not in autonomous mode ({self._last_ctrl_mode})"
        else:
            status.level = DiagnosticStatus.OK
            status.message = f"MK-mini backend {self._operation_mode}"

        values = {
            "operation_mode": self._operation_mode,
            "can_interface": self._can_interface,
            "connected": str(connected).lower(),
            "vcu_mode": str(self._last_ctrl_mode),
            "vcu_gear": str(self._last_ctrl_gear),
            "state_reason": self._last_state_reason,
            "rx_frames": str(self._rx_frames),
            "tx_frames": str(self._tx_frames),
            "protocol_errors": str(self._protocol_errors),
            "counter_gaps": str(self._counter_gaps),
            "transport_errors": str(self._transport_errors),
            "calibration_blocks": str(self._calibration_blocks),
            "gear_feedback_blocks": str(self._gear_feedback_blocks),
            "steering_calibration_confirmed": str(
                self._steering_calibration_confirmed
            ).lower(),
            "allow_uncalibrated_control": str(
                self._allow_uncalibrated_control
            ).lower(),
        }
        status.values = [KeyValue(key=key, value=value) for key, value in values.items()]
        array.status = [status]
        self._diagnostic_pub.publish(array)

    def safe_shutdown(self) -> None:
        if self._operation_mode != "control" or not self._transport.is_open:
            return
        try:
            payload = encode_ctrl_command(
                gear=ProtocolGear(int(self._state.gear)),
                speed_mps=0.0,
                steering_deg=min(
                    max(
                        self._last_requested_vcu_steering_deg,
                        -self._vcu_steering_soft_limit_deg,
                    ),
                    self._vcu_steering_soft_limit_deg,
                ),
                alive_counter=self._alive_counter,
            )
            self._transport.send(CTRL_CMD_ID, payload)
        except Exception as exc:
            self.get_logger().warning(f"best-effort MK-mini stop frame failed: {exc}")

    def close_transport(self) -> None:
        self._transport.close()


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MkMiniCanBackend()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.safe_shutdown()
        node.close_transport()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
