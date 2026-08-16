#!/usr/bin/env python3

import math
import time

from agt_chassis_mk_mini.mk_mini_protocol import (
    BMS_INFO_FB_ID,
    CTRL_CMD_ID,
    CTRL_FB_ID,
    LEFT_REAR_WHEEL_FB_ID,
    RIGHT_REAR_WHEEL_FB_ID,
    Gear,
)
from agt_chassis_mk_mini.socketcan_transport import SocketCanTransport
from agt_chassis_mk_mini_sim.vcu_model import VcuFaultConfig, VcuModel
from agt_chassis_mk_mini_sim.vcu_protocol import (
    CtrlCommand,
    SimProtocolError,
    decode_ctrl_command,
    encode_bms_info,
    encode_ctrl_feedback,
    encode_wheel_feedback,
)
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus, KeyValue
import rclpy
from rclpy.node import Node


class MkMiniVcuSimulator(Node):
    def __init__(self) -> None:
        super().__init__("agt_mk_mini_vcu_sim")

        self._can_interface = str(self.declare_parameter("can_interface", "vcan0").value)
        self._rx_poll_period_sec = float(
            self.declare_parameter("rx_poll_period_sec", 0.002).value
        )
        self._feedback_period_sec = float(
            self.declare_parameter("feedback_period_sec", 0.01).value
        )
        self._bms_period_sec = float(
            self.declare_parameter("bms_period_sec", 0.10).value
        )
        self._reconnect_period_sec = float(
            self.declare_parameter("reconnect_period_sec", 0.50).value
        )
        self._drop_feedback = bool(
            self.declare_parameter("drop_feedback", False).value
        )
        self._corrupt_bcc = bool(
            self.declare_parameter("corrupt_bcc", False).value
        )

        max_accel = float(self.declare_parameter("max_accel_mps2", 1.0).value)
        max_decel = float(self.declare_parameter("max_decel_mps2", 2.0).value)
        stationary_threshold = float(
            self.declare_parameter("stationary_threshold_mps", 0.01).value
        )
        wheel_diameter = float(
            self.declare_parameter("wheel_diameter_m", 0.24).value
        )
        encoder_pulses = int(
            self.declare_parameter("encoder_pulses_per_rev", 4096).value
        )
        battery_voltage = float(
            self.declare_parameter("battery_voltage_v", 48.0).value
        )
        remaining_capacity = float(
            self.declare_parameter("remaining_capacity_ah", 20.0).value
        )
        mode = int(self.declare_parameter("vcu_mode", 0).value)

        for name, value in {
            "rx_poll_period_sec": self._rx_poll_period_sec,
            "feedback_period_sec": self._feedback_period_sec,
            "bms_period_sec": self._bms_period_sec,
            "reconnect_period_sec": self._reconnect_period_sec,
        }.items():
            if not math.isfinite(value) or value <= 0.0:
                raise ValueError(f"{name} must be finite and positive")

        self._model = VcuModel(
            max_accel_mps2=max_accel,
            max_decel_mps2=max_decel,
            stationary_threshold_mps=stationary_threshold,
            wheel_diameter_m=wheel_diameter,
            encoder_pulses_per_rev=encoder_pulses,
            battery_voltage_v=battery_voltage,
            remaining_capacity_ah=remaining_capacity,
            mode=mode,
            faults=VcuFaultConfig(
                drop_feedback=self._drop_feedback,
                corrupt_bcc=self._corrupt_bcc,
            ),
        )
        self._transport = SocketCanTransport(self._can_interface)
        self._next_reconnect_time = 0.0
        self._last_command = CtrlCommand(
            gear=Gear.PARK,
            speed_mps=0.0,
            steering_deg=0.0,
            alive_counter=0,
        )
        self._last_command_counter = None
        self._ctrl_feedback_counter = 0
        self._left_feedback_counter = 0
        self._right_feedback_counter = 0
        self._bms_feedback_counter = 0
        self._last_state = None

        self.command_frames = 0
        self.checksum_failures = 0
        self.counter_gaps = 0
        self.feedback_frames = 0
        self.transport_errors = 0

        self._status_pub = self.create_publisher(
            DiagnosticArray, "/agt/sim/mk_mini/status", 10
        )
        self.create_timer(self._rx_poll_period_sec, self._rx_tick)
        self.create_timer(self._feedback_period_sec, self._feedback_tick)
        self.create_timer(self._bms_period_sec, self._bms_tick)
        self.create_timer(0.20, self._status_tick)
        self._ensure_transport(time.monotonic())

    @staticmethod
    def _next_counter(counter: int) -> int:
        return (int(counter) + 1) & 0x0F

    def _ensure_transport(self, now: float) -> bool:
        if self._transport.is_open:
            return True
        if now < self._next_reconnect_time:
            return False
        self._next_reconnect_time = now + self._reconnect_period_sec
        try:
            self._transport.open()
            self.get_logger().info(
                f"opened simulated MK-mini SocketCAN interface {self._can_interface}"
            )
            return True
        except OSError as exc:
            self.transport_errors += 1
            self.get_logger().error(
                f"failed to open simulator SocketCAN interface {self._can_interface}: {exc}"
            )
            return False

    def _mark_transport_failed(self, exc: Exception) -> None:
        self.transport_errors += 1
        self.get_logger().error(f"simulator SocketCAN transport error: {exc}")
        self._transport.close()
        self._next_reconnect_time = time.monotonic() + self._reconnect_period_sec

    def _handle_command(self, payload: bytes) -> None:
        try:
            command = decode_ctrl_command(payload)
        except SimProtocolError:
            self.checksum_failures += 1
            return

        if self._last_command_counter is not None:
            expected = self._next_counter(self._last_command_counter)
            if command.alive_counter != expected:
                self.counter_gaps += 1
        self._last_command_counter = command.alive_counter
        self._last_command = command
        self.command_frames += 1

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
                self.checksum_failures += 1
                continue
            if frame is None:
                return
            if frame.can_id == CTRL_CMD_ID:
                self._handle_command(frame.data)

    def _maybe_corrupt(self, payload: bytes) -> bytes:
        if not self._corrupt_bcc:
            return payload
        data = bytearray(payload)
        data[7] ^= 0x01
        return bytes(data)

    def _send_frame(self, can_id: int, payload: bytes) -> None:
        if self._drop_feedback:
            return
        if not self._ensure_transport(time.monotonic()):
            return
        try:
            self._transport.send(can_id, self._maybe_corrupt(payload))
        except OSError as exc:
            self._mark_transport_failed(exc)
            return
        self.feedback_frames += 1

    def _feedback_tick(self) -> None:
        state = self._model.step(self._last_command, self._feedback_period_sec)
        self._last_state = state

        ctrl = encode_ctrl_feedback(
            gear=state.gear,
            speed_mps=abs(state.speed_mps),
            steering_deg=state.steering_deg,
            mode=state.mode,
            alive_counter=self._ctrl_feedback_counter,
        )
        left = encode_wheel_feedback(
            speed_mps=state.left_wheel_speed_mps,
            pulse_count=state.left_pulse_count,
            alive_counter=self._left_feedback_counter,
        )
        right = encode_wheel_feedback(
            speed_mps=state.right_wheel_speed_mps,
            pulse_count=state.right_pulse_count,
            alive_counter=self._right_feedback_counter,
        )

        self._send_frame(CTRL_FB_ID, ctrl)
        self._send_frame(LEFT_REAR_WHEEL_FB_ID, left)
        self._send_frame(RIGHT_REAR_WHEEL_FB_ID, right)

        self._ctrl_feedback_counter = self._next_counter(self._ctrl_feedback_counter)
        self._left_feedback_counter = self._next_counter(self._left_feedback_counter)
        self._right_feedback_counter = self._next_counter(self._right_feedback_counter)

    def _bms_tick(self) -> None:
        state = self._last_state
        if state is None:
            return
        payload = encode_bms_info(
            voltage_v=state.battery_voltage_v,
            current_a=state.battery_current_a,
            remaining_capacity_ah=state.remaining_capacity_ah,
            alive_counter=self._bms_feedback_counter,
        )
        self._send_frame(BMS_INFO_FB_ID, payload)
        self._bms_feedback_counter = self._next_counter(self._bms_feedback_counter)

    def _status_tick(self) -> None:
        array = DiagnosticArray()
        array.header.stamp = self.get_clock().now().to_msg()
        status = DiagnosticStatus()
        status.name = "agt_chassis_mk_mini_sim/vcu"
        status.hardware_id = "mk_mini_virtual_vcu"
        if not self._transport.is_open:
            status.level = DiagnosticStatus.ERROR
            status.message = "vcan transport unavailable"
        elif self._drop_feedback:
            status.level = DiagnosticStatus.WARN
            status.message = "feedback drop fault enabled"
        elif self._corrupt_bcc:
            status.level = DiagnosticStatus.WARN
            status.message = "feedback BCC corruption fault enabled"
        else:
            status.level = DiagnosticStatus.OK
            status.message = "virtual VCU active"

        values = {
            "can_interface": self._can_interface,
            "command_frames": self.command_frames,
            "checksum_failures": self.checksum_failures,
            "counter_gaps": self.counter_gaps,
            "feedback_frames": self.feedback_frames,
            "transport_errors": self.transport_errors,
            "drop_feedback": self._drop_feedback,
            "corrupt_bcc": self._corrupt_bcc,
        }
        status.values = [KeyValue(key=str(k), value=str(v)) for k, v in values.items()]
        array.status = [status]
        self._status_pub.publish(array)

    def destroy_node(self):
        self._transport.close()
        return super().destroy_node()


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MkMiniVcuSimulator()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
