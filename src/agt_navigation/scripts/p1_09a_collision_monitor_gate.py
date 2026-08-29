#!/usr/bin/env python3

from __future__ import annotations

import json
import math
import sys
import time
from dataclasses import dataclass, field
from typing import Optional

from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from rclpy.node import Node
from rclpy.qos import QoSProfile
from sensor_msgs.msg import PointCloud2

import rclpy


RAW_TOPIC = "/agt/navigation/cmd_vel_raw"
FILTERED_TOPIC = "/agt/navigation/cmd_vel"
SAFETY_TOPIC = "/agt/safety/cmd_vel"
ODOM_TOPIC = "/agt/odometry/odometry"
OBSTACLE_TOPIC = "/agt/perception/obstacle_cloud"


@dataclass(frozen=True)
class GateThresholds:
    publish_hz: float = 15.0
    drive_duration_s: float = 2.5
    settle_after_start_s: float = 0.5
    raw_min_linear_x: float = 0.15
    raw_max_angular_z: float = 0.02
    filtered_max_linear_x: float = 0.02
    filtered_max_angular_z: float = 0.02
    safety_max_linear_x: float = 0.02
    safety_max_angular_z: float = 0.02
    odom_max_displacement_m: float = 0.05
    obstacle_min_points: int = 1
    cleanup_zero_bursts: int = 6
    cleanup_zero_period_s: float = 0.05
    command_linear_x: float = 0.20
    command_angular_z: float = 0.0
    obstacle_timeout_s: float = 10.0
    odom_timeout_s: float = 10.0


@dataclass
class TwistWindowStats:
    count: int = 0
    max_linear_x: float = 0.0
    max_angular_z: float = 0.0

    def observe(self, message: Twist) -> None:
        self.count += 1
        self.max_linear_x = max(self.max_linear_x, abs(float(message.linear.x)))
        self.max_angular_z = max(self.max_angular_z, abs(float(message.angular.z)))


@dataclass
class GateMetrics:
    obstacle_messages: int = 0
    obstacle_points: int = 0
    raw: TwistWindowStats = field(default_factory=TwistWindowStats)
    filtered_after_settle: TwistWindowStats = field(default_factory=TwistWindowStats)
    safety_after_settle: TwistWindowStats = field(default_factory=TwistWindowStats)
    odom_messages: int = 0
    odom_displacement_m: float = 0.0
    initial_odom_x: Optional[float] = None
    initial_odom_y: Optional[float] = None


@dataclass(frozen=True)
class GateOutcome:
    obstacle_present: bool
    raw_command: bool
    collision_stop: bool
    safety_stop: bool
    odom_stop: bool

    @property
    def passed(self) -> bool:
        return all(
            (
                self.obstacle_present,
                self.raw_command,
                self.collision_stop,
                self.safety_stop,
                self.odom_stop,
            )
        )


def _point_cloud_points(message: PointCloud2) -> int:
    if message.width <= 0 or message.height <= 0 or message.point_step <= 0:
        return 0
    available = len(message.data) // int(message.point_step)
    return min(int(message.width) * int(message.height), available)


def evaluate_gate(metrics: GateMetrics, thresholds: GateThresholds) -> GateOutcome:
    obstacle_present = (
        metrics.obstacle_messages > 0 and metrics.obstacle_points >= thresholds.obstacle_min_points
    )
    raw_command = (
        metrics.raw.count > 0
        and metrics.raw.max_linear_x >= thresholds.raw_min_linear_x
        and metrics.raw.max_angular_z <= thresholds.raw_max_angular_z
    )
    collision_stop = (
        metrics.filtered_after_settle.count > 0
        and metrics.filtered_after_settle.max_linear_x <= thresholds.filtered_max_linear_x
        and metrics.filtered_after_settle.max_angular_z <= thresholds.filtered_max_angular_z
    )
    safety_stop = (
        metrics.safety_after_settle.count > 0
        and metrics.safety_after_settle.max_linear_x <= thresholds.safety_max_linear_x
        and metrics.safety_after_settle.max_angular_z <= thresholds.safety_max_angular_z
    )
    odom_stop = (
        metrics.odom_messages > 1
        and metrics.odom_displacement_m <= thresholds.odom_max_displacement_m
    )
    return GateOutcome(
        obstacle_present=obstacle_present,
        raw_command=raw_command,
        collision_stop=collision_stop,
        safety_stop=safety_stop,
        odom_stop=odom_stop,
    )


class CollisionMonitorGate(Node):
    def __init__(self) -> None:
        super().__init__("agt_p1_09a_collision_monitor_gate")
        self.thresholds = GateThresholds(
            publish_hz=float(self.declare_parameter("publish_hz", GateThresholds.publish_hz).value),
            drive_duration_s=float(
                self.declare_parameter("drive_duration_s", GateThresholds.drive_duration_s).value
            ),
            settle_after_start_s=float(
                self.declare_parameter(
                    "settle_after_start_s", GateThresholds.settle_after_start_s
                ).value
            ),
            raw_min_linear_x=float(
                self.declare_parameter("raw_min_linear_x", GateThresholds.raw_min_linear_x).value
            ),
            filtered_max_linear_x=float(
                self.declare_parameter(
                    "filtered_max_linear_x", GateThresholds.filtered_max_linear_x
                ).value
            ),
            filtered_max_angular_z=float(
                self.declare_parameter(
                    "filtered_max_angular_z", GateThresholds.filtered_max_angular_z
                ).value
            ),
            safety_max_linear_x=float(
                self.declare_parameter("safety_max_linear_x", GateThresholds.safety_max_linear_x).value
            ),
            safety_max_angular_z=float(
                self.declare_parameter("safety_max_angular_z", GateThresholds.safety_max_angular_z).value
            ),
            odom_max_displacement_m=float(
                self.declare_parameter(
                    "odom_max_displacement_m", GateThresholds.odom_max_displacement_m
                ).value
            ),
            obstacle_min_points=int(
                self.declare_parameter("obstacle_min_points", GateThresholds.obstacle_min_points).value
            ),
            cleanup_zero_bursts=int(
                self.declare_parameter("cleanup_zero_bursts", GateThresholds.cleanup_zero_bursts).value
            ),
            cleanup_zero_period_s=float(
                self.declare_parameter(
                    "cleanup_zero_period_s", GateThresholds.cleanup_zero_period_s
                ).value
            ),
            command_linear_x=float(
                self.declare_parameter("command_linear_x", GateThresholds.command_linear_x).value
            ),
            command_angular_z=float(
                self.declare_parameter("command_angular_z", GateThresholds.command_angular_z).value
            ),
            obstacle_timeout_s=float(
                self.declare_parameter("obstacle_timeout_s", GateThresholds.obstacle_timeout_s).value
            ),
            odom_timeout_s=float(
                self.declare_parameter("odom_timeout_s", GateThresholds.odom_timeout_s).value
            ),
        )
        if self.thresholds.publish_hz <= 0.0:
            raise ValueError("publish_hz must be positive")
        if self.thresholds.drive_duration_s <= 0.0:
            raise ValueError("drive_duration_s must be positive")
        if self.thresholds.settle_after_start_s < 0.0:
            raise ValueError("settle_after_start_s must be non-negative")
        if self.thresholds.cleanup_zero_bursts <= 0:
            raise ValueError("cleanup_zero_bursts must be positive")
        if self.thresholds.cleanup_zero_period_s < 0.0:
            raise ValueError("cleanup_zero_period_s must be non-negative")
        if self.thresholds.obstacle_timeout_s <= 0.0 or self.thresholds.odom_timeout_s <= 0.0:
            raise ValueError("timeouts must be positive")

        self._metrics = GateMetrics()
        self._run_started_at: Optional[float] = None
        self._drive_start_at: Optional[float] = None
        self._drive_end_at: Optional[float] = None
        self._settle_start_at: Optional[float] = None
        self._twist = Twist()
        self._twist.linear.x = self.thresholds.command_linear_x
        self._twist.angular.z = self.thresholds.command_angular_z
        self._zero_twist = Twist()
        self._raw_pub = self.create_publisher(Twist, RAW_TOPIC, 10)
        self._qos = QoSProfile(depth=10)
        self.create_subscription(Twist, RAW_TOPIC, self._on_raw, self._qos)
        self.create_subscription(Twist, FILTERED_TOPIC, self._on_filtered, self._qos)
        self.create_subscription(Twist, SAFETY_TOPIC, self._on_safety, self._qos)
        self.create_subscription(Odometry, ODOM_TOPIC, self._on_odom, self._qos)
        self.create_subscription(PointCloud2, OBSTACLE_TOPIC, self._on_obstacle, self._qos)

    def _now(self) -> float:
        return time.monotonic()

    def _active(self) -> bool:
        return self._run_started_at is not None

    def _in_settle_window(self, stamp: float) -> bool:
        if self._settle_start_at is None or self._drive_end_at is None:
            return False
        return self._settle_start_at <= stamp < self._drive_end_at

    def _on_raw(self, message: Twist) -> None:
        now = self._now()
        if self._drive_start_at is None or now < self._drive_start_at:
            return
        if now < (self._drive_end_at or now):
            self._metrics.raw.observe(message)

    def _on_filtered(self, message: Twist) -> None:
        now = self._now()
        if self._in_settle_window(now):
            self._metrics.filtered_after_settle.observe(message)

    def _on_safety(self, message: Twist) -> None:
        now = self._now()
        if self._in_settle_window(now):
            self._metrics.safety_after_settle.observe(message)

    def _on_odom(self, message: Odometry) -> None:
        self._metrics.odom_messages += 1
        pose = message.pose.pose.position
        x = float(pose.x)
        y = float(pose.y)
        if self._metrics.initial_odom_x is None or self._metrics.initial_odom_y is None:
            self._metrics.initial_odom_x = x
            self._metrics.initial_odom_y = y
            return
        self._metrics.odom_displacement_m = max(
            self._metrics.odom_displacement_m,
            math.hypot(x - self._metrics.initial_odom_x, y - self._metrics.initial_odom_y),
        )

    def _on_obstacle(self, message: PointCloud2) -> None:
        self._metrics.obstacle_messages += 1
        self._metrics.obstacle_points = max(self._metrics.obstacle_points, _point_cloud_points(message))

    def _wait_until(self, predicate, timeout_s: float) -> bool:
        deadline = self._now() + timeout_s
        while rclpy.ok() and self._now() < deadline:
            rclpy.spin_once(self, timeout_sec=0.05)
            if predicate():
                return True
        return bool(predicate())

    def _publish_twist(self, message: Twist) -> None:
        self._raw_pub.publish(message)

    def _send_zero_cleanup(self) -> None:
        for _ in range(self.thresholds.cleanup_zero_bursts):
            self._publish_twist(self._zero_twist)
            rclpy.spin_once(self, timeout_sec=0.01)
            if self.thresholds.cleanup_zero_period_s > 0.0:
                time.sleep(self.thresholds.cleanup_zero_period_s)

    def run(self) -> dict:
        if not self._wait_until(
            lambda: self._metrics.obstacle_points >= self.thresholds.obstacle_min_points,
            self.thresholds.obstacle_timeout_s,
        ):
            raise RuntimeError("timed out waiting for synthetic obstacle_cloud")
        if not self._wait_until(lambda: self._metrics.odom_messages > 0, self.thresholds.odom_timeout_s):
            raise RuntimeError("timed out waiting for /agt/odometry/odometry")

        self._metrics = GateMetrics(
            obstacle_messages=self._metrics.obstacle_messages,
            obstacle_points=self._metrics.obstacle_points,
            initial_odom_x=self._metrics.initial_odom_x,
            initial_odom_y=self._metrics.initial_odom_y,
            odom_messages=1,
        )
        if self._metrics.initial_odom_x is None or self._metrics.initial_odom_y is None:
            raise RuntimeError("failed to capture initial odometry reference")

        self._run_started_at = self._now()
        self._drive_start_at = self._run_started_at
        self._drive_end_at = self._drive_start_at + self.thresholds.drive_duration_s
        self._settle_start_at = self._drive_start_at + self.thresholds.settle_after_start_s
        measurement_end = self._drive_end_at + self.thresholds.settle_after_start_s
        publish_period = 1.0 / self.thresholds.publish_hz
        next_publish_at = self._drive_start_at

        while rclpy.ok() and self._now() < measurement_end:
            now = self._now()
            if now >= next_publish_at:
                self._publish_twist(self._twist if now < self._drive_end_at else self._zero_twist)
                next_publish_at = now + publish_period
            rclpy.spin_once(self, timeout_sec=0.02)

        outcome = evaluate_gate(self._metrics, self.thresholds)
        return {
            "passed": outcome.passed,
            "outcome": outcome,
            "metrics": self._metrics,
            "thresholds": self.thresholds,
        }


def _format_report(report: dict) -> str:
    metrics: GateMetrics = report["metrics"]
    outcome: GateOutcome = report["outcome"]
    threshold: GateThresholds = report["thresholds"]
    lines = [
        f"GATE_E_OBSTACLE_PRESENT={'PASS' if outcome.obstacle_present else 'FAIL'}",
        f"GATE_E_RAW_COMMAND={'PASS' if outcome.raw_command else 'FAIL'}",
        f"GATE_E_COLLISION_STOP={'PASS' if outcome.collision_stop else 'FAIL'}",
        f"GATE_E_SAFETY_STOP={'PASS' if outcome.safety_stop else 'FAIL'}",
        f"GATE_E_ODOM_STOP={'PASS' if outcome.odom_stop else 'FAIL'}",
        f"GATE_E={'PASS' if outcome.passed else 'FAIL'}",
        f"obstacle_points={metrics.obstacle_points}",
        f"raw_max_linear={metrics.raw.max_linear_x:.3f}",
        f"raw_max_angular={metrics.raw.max_angular_z:.3f}",
        f"filtered_max_linear_after_settle={metrics.filtered_after_settle.max_linear_x:.3f}",
        f"filtered_max_angular_after_settle={metrics.filtered_after_settle.max_angular_z:.3f}",
        f"safety_max_linear_after_settle={metrics.safety_after_settle.max_linear_x:.3f}",
        f"safety_max_angular_after_settle={metrics.safety_after_settle.max_angular_z:.3f}",
        f"odom_displacement={metrics.odom_displacement_m:.3f}",
        f"threshold_raw_min_linear_x={threshold.raw_min_linear_x:.3f}",
        f"threshold_raw_max_angular_z={threshold.raw_max_angular_z:.3f}",
        f"threshold_stop_max_linear_x={threshold.filtered_max_linear_x:.3f}",
        f"threshold_stop_max_angular_z={threshold.filtered_max_angular_z:.3f}",
        f"threshold_odom_max_displacement_m={threshold.odom_max_displacement_m:.3f}",
    ]
    return "\n".join(lines)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = CollisionMonitorGate()
    exit_code = 1
    report = None
    try:
        report = node.run()
        print(_format_report(report))
        print(
            json.dumps(
                {
                    "gate": "E",
                    "passed": bool(report["passed"]),
                    "obstacle_points": report["metrics"].obstacle_points,
                    "raw_max_linear": report["metrics"].raw.max_linear_x,
                    "raw_max_angular": report["metrics"].raw.max_angular_z,
                    "filtered_max_linear_after_settle": report["metrics"].filtered_after_settle.max_linear_x,
                    "filtered_max_angular_after_settle": report["metrics"].filtered_after_settle.max_angular_z,
                    "safety_max_linear_after_settle": report["metrics"].safety_after_settle.max_linear_x,
                    "safety_max_angular_after_settle": report["metrics"].safety_after_settle.max_angular_z,
                    "odom_displacement_m": report["metrics"].odom_displacement_m,
                },
                sort_keys=True,
                separators=(",", ":"),
            )
        )
        exit_code = 0 if report["passed"] else 2
    except Exception as exc:
        print(
            json.dumps(
                {"gate": "E", "passed": False, "error": str(exc)},
                sort_keys=True,
                separators=(",", ":"),
            ),
            file=sys.stderr,
        )
        exit_code = 1
    finally:
        try:
            node._send_zero_cleanup()
        except Exception:
            pass
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
    raise SystemExit(exit_code)


if __name__ == "__main__":
    main()
