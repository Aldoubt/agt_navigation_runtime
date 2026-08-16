#!/usr/bin/env python3

import argparse
import time

from agt_chassis_mk_mini.mk_mini_protocol import (
    CTRL_CMD_ID,
    CTRL_FB_ID,
    Gear,
    ProtocolError,
    decode_ctrl_feedback,
)
from agt_chassis_mk_mini.socketcan_transport import SocketCanTransport
from agt_chassis_mk_mini_sim.vcu_protocol import SimProtocolError, decode_ctrl_command
from agt_interfaces.msg import AckermannCommand
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus
from geometry_msgs.msg import Twist, TwistWithCovarianceStamped
import rclpy
from rclpy.node import Node
from std_msgs.msg import Bool


SCENARIOS = (
    "monitor_only",
    "forward",
    "reverse_interlock",
    "command_timeout",
    "feedback_fault",
)


class AcceptanceFailure(RuntimeError):
    pass


class HilObserver(Node):
    def __init__(self, can_interface: str) -> None:
        super().__init__("agt_mk_mini_vcan_hil_acceptance")
        self._cmd_pub = self.create_publisher(Twist, "/agt/chassis/cmd_vel", 10)
        self.create_subscription(Bool, "/agt/chassis/connected", self._on_connected, 10)
        self.create_subscription(
            DiagnosticArray, "/agt/chassis/status", self._on_status, 10
        )
        self.create_subscription(
            AckermannCommand,
            "/agt/chassis/backend/ackermann_feedback",
            self._on_ackermann_feedback,
            10,
        )
        self.create_subscription(
            TwistWithCovarianceStamped,
            "/agt/chassis/wheel_twist",
            self._on_wheel_twist,
            10,
        )

        self.connected = None
        self.backend_status = None
        self.feedback_speed = None
        self.wheel_speed = None
        self.ctrl_commands = []
        self.ctrl_feedback = []
        self.invalid_bus_frames = 0

        self._bus = SocketCanTransport(can_interface)
        self._bus.open()

    def destroy_node(self):
        self._bus.close()
        return super().destroy_node()

    def _on_connected(self, msg: Bool) -> None:
        self.connected = bool(msg.data)

    def _on_status(self, msg: DiagnosticArray) -> None:
        for status in msg.status:
            if status.hardware_id == "mk_mini" or status.name.endswith("can_backend"):
                self.backend_status = status

    def _on_ackermann_feedback(self, msg: AckermannCommand) -> None:
        self.feedback_speed = float(msg.speed_mps)

    def _on_wheel_twist(self, msg: TwistWithCovarianceStamped) -> None:
        self.wheel_speed = float(msg.twist.twist.linear.x)

    def _drain_bus(self) -> None:
        for _ in range(512):
            try:
                frame = self._bus.recv_nonblocking()
            except (OSError, ValueError):
                self.invalid_bus_frames += 1
                return
            if frame is None:
                return
            now = time.monotonic()
            try:
                if frame.can_id == CTRL_CMD_ID:
                    self.ctrl_commands.append((now, decode_ctrl_command(frame.data)))
                elif frame.can_id == CTRL_FB_ID:
                    self.ctrl_feedback.append((now, decode_ctrl_feedback(frame.data)))
            except (SimProtocolError, ProtocolError):
                self.invalid_bus_frames += 1

    def spin_once(self, timeout_sec: float = 0.01) -> None:
        rclpy.spin_once(self, timeout_sec=timeout_sec)
        self._drain_bus()

    def wait_until(self, predicate, timeout: float, description: str, publisher=None) -> None:
        deadline = time.monotonic() + timeout
        next_publish = 0.0
        while time.monotonic() < deadline:
            now = time.monotonic()
            if publisher is not None and now >= next_publish:
                publisher()
                next_publish = now + 0.05
            self.spin_once()
            if predicate():
                return
        raise AcceptanceFailure(f"timeout waiting for {description}")

    def spin_for(self, duration: float, publisher=None) -> None:
        deadline = time.monotonic() + duration
        next_publish = 0.0
        while time.monotonic() < deadline:
            now = time.monotonic()
            if publisher is not None and now >= next_publish:
                publisher()
                next_publish = now + 0.05
            self.spin_once()

    def publish_twist(self, linear_x: float, angular_z: float = 0.0) -> None:
        msg = Twist()
        msg.linear.x = float(linear_x)
        msg.angular.z = float(angular_z)
        self._cmd_pub.publish(msg)


def _assert(condition: bool, message: str) -> None:
    if not condition:
        raise AcceptanceFailure(message)


def _wait_connected(node: HilObserver, timeout: float) -> None:
    node.wait_until(lambda: node.connected is True, timeout, "/agt/chassis/connected=true")


def scenario_monitor_only(node: HilObserver, timeout: float) -> None:
    _wait_connected(node, timeout)
    node.ctrl_commands.clear()
    node.spin_for(0.50)
    _assert(
        len(node.ctrl_commands) == 0,
        f"monitor mode transmitted {len(node.ctrl_commands)} ctrl_cmd frames",
    )


def scenario_forward(node: HilObserver, timeout: float) -> None:
    _wait_connected(node, timeout)
    node.ctrl_commands.clear()
    drive = lambda: node.publish_twist(0.40, 0.10)
    node.wait_until(
        lambda: node.feedback_speed is not None and node.feedback_speed > 0.10,
        timeout,
        "positive Ackermann feedback",
        publisher=drive,
    )
    node.wait_until(
        lambda: node.wheel_speed is not None and node.wheel_speed > 0.10,
        timeout,
        "positive wheel twist",
        publisher=drive,
    )
    commands = [command for _, command in node.ctrl_commands]
    zero_d = next((i for i, c in enumerate(commands) if c.gear == Gear.D and c.speed_mps == 0.0), None)
    nonzero_d = next((i for i, c in enumerate(commands) if c.gear == Gear.D and c.speed_mps > 0.0), None)
    _assert(zero_d is not None, "no zero-speed D request observed")
    _assert(nonzero_d is not None, "no nonzero D request observed")
    _assert(zero_d < nonzero_d, "nonzero D speed preceded D feedback interlock")


def scenario_reverse_interlock(node: HilObserver, timeout: float) -> None:
    _wait_connected(node, timeout)
    forward = lambda: node.publish_twist(0.35, 0.0)
    node.wait_until(
        lambda: node.feedback_speed is not None and node.feedback_speed > 0.10,
        timeout,
        "forward motion before reverse test",
        publisher=forward,
    )

    node.ctrl_commands.clear()
    reverse = lambda: node.publish_twist(-0.30, 0.0)
    node.wait_until(
        lambda: node.feedback_speed is not None and node.feedback_speed < -0.10,
        timeout,
        "negative feedback after reverse interlock",
        publisher=reverse,
    )
    commands = [command for _, command in node.ctrl_commands]
    d_zero = next((i for i, c in enumerate(commands) if c.gear == Gear.D and c.speed_mps == 0.0), None)
    r_zero = next((i for i, c in enumerate(commands) if c.gear == Gear.R and c.speed_mps == 0.0), None)
    r_move = next((i for i, c in enumerate(commands) if c.gear == Gear.R and c.speed_mps > 0.0), None)
    _assert(d_zero is not None, "reverse request did not first command zero in D")
    _assert(r_zero is not None, "no zero-speed R shift request observed")
    _assert(r_move is not None, "no moving R command observed")
    _assert(d_zero < r_zero < r_move, "D-to-R interlock ordering violated")


def scenario_command_timeout(node: HilObserver, timeout: float) -> None:
    _wait_connected(node, timeout)
    drive = lambda: node.publish_twist(0.30, 0.0)
    node.wait_until(
        lambda: node.feedback_speed is not None and node.feedback_speed > 0.10,
        timeout,
        "forward motion before timeout test",
        publisher=drive,
    )

    node.ctrl_commands.clear()
    node.ctrl_feedback.clear()
    node.wait_until(
        lambda: any(command.gear == Gear.P for _, command in node.ctrl_commands),
        timeout,
        "timeout-driven PARK command",
    )
    _assert(
        len(node.ctrl_commands) >= 10,
        "backend did not maintain CAN heartbeat while upstream Twist was stale",
    )
    node.wait_until(
        lambda: any(feedback.gear == Gear.P for _, feedback in node.ctrl_feedback),
        timeout,
        "simulated VCU PARK feedback",
    )
    _assert(
        node.feedback_speed is None or abs(node.feedback_speed) <= 0.05,
        "vehicle was not stationary when PARK completed",
    )


def scenario_feedback_fault(node: HilObserver, timeout: float) -> None:
    node.wait_until(
        lambda: (
            node.connected is False
            and node.backend_status is not None
            and node.backend_status.level == DiagnosticStatus.ERROR
        ),
        timeout,
        "backend disconnected/error diagnostic under feedback fault",
    )


def parse_args(argv=None):
    parser = argparse.ArgumentParser(description="MK-mini vcan software-HIL acceptance")
    parser.add_argument("--scenario", required=True, choices=SCENARIOS)
    parser.add_argument("--can-interface", default="vcan0")
    parser.add_argument("--timeout", type=float, default=8.0)
    return parser.parse_known_args(argv)[0]


def main(argv=None) -> int:
    args = parse_args(argv)
    if args.timeout <= 0.0:
        raise SystemExit("--timeout must be positive")

    # The acceptance runner owns its CLI. Do not forward --scenario/--timeout
    # into rclpy, otherwise ROS argument parsing can reject these tool options.
    rclpy.init(args=[])
    node = HilObserver(args.can_interface)
    try:
        scenarios = {
            "monitor_only": scenario_monitor_only,
            "forward": scenario_forward,
            "reverse_interlock": scenario_reverse_interlock,
            "command_timeout": scenario_command_timeout,
            "feedback_fault": scenario_feedback_fault,
        }
        scenarios[args.scenario](node, args.timeout)
        print(f"[PASS] {args.scenario}")
        return 0
    except AcceptanceFailure as exc:
        print(f"[FAIL] {args.scenario}: {exc}")
        return 2
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    raise SystemExit(main())
