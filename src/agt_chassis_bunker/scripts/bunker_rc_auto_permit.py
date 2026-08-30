#!/usr/bin/env python3

import time

import rclpy
from bunker_msgs.msg import BunkerRCState
from rclpy.node import Node
from std_msgs.msg import Bool


_VALID_SWITCHES = ("swa", "swb", "swc", "swd")


class BunkerRcAutoPermit(Node):
    """Convert one explicitly configured BUNKER RC switch into an AUTO permit.

    The adapter is intentionally fail-closed: an unconfigured mapping, stale RC
    input, or a switch value different from the configured enabled value yields
    ``False``. It never publishes velocity commands or changes BUNKER modes.
    """

    def __init__(self) -> None:
        super().__init__("agt_bunker_rc_auto_permit")
        self._input_topic = str(
            self.declare_parameter("input_topic", "/agt/chassis/rc_state").value
        ).strip()
        self._output_topic = str(
            self.declare_parameter("output_topic", "/agt/chassis/auto_permit").value
        ).strip()
        self._switch_name = str(
            self.declare_parameter("switch_name", "").value
        ).strip().lower()
        self._enabled_value = int(self.declare_parameter("enabled_value", -1).value)
        self._status_timeout = float(
            self.declare_parameter("status_timeout", 0.5).value
        )
        self._publish_rate = float(
            self.declare_parameter("publish_rate", 20.0).value
        )

        if self._switch_name not in _VALID_SWITCHES:
            raise ValueError(
                "switch_name must be one of swa, swb, swc, swd; inspect "
                "/agt/chassis/rc_state on the physical remote before configuring it"
            )
        if self._enabled_value < 0:
            raise ValueError(
                "enabled_value must be configured explicitly from physical RC evidence"
            )
        if self._status_timeout <= 0.0:
            raise ValueError("status_timeout must be > 0")
        if self._publish_rate <= 0.0:
            raise ValueError("publish_rate must be > 0")

        self._last_value: int | None = None
        self._last_stamp = float("-inf")
        self._publisher = self.create_publisher(Bool, self._output_topic, 10)
        self.create_subscription(
            BunkerRCState,
            self._input_topic,
            self._callback,
            10,
        )
        self.create_timer(1.0 / self._publish_rate, self._tick)

    def _callback(self, msg: BunkerRCState) -> None:
        self._last_value = int(getattr(msg, self._switch_name))
        self._last_stamp = time.monotonic()

    def _tick(self) -> None:
        now = time.monotonic()
        fresh = now - self._last_stamp <= self._status_timeout
        permit = bool(
            fresh
            and self._last_value is not None
            and self._last_value == self._enabled_value
        )
        self._publisher.publish(Bool(data=permit))


def main(args=None) -> None:
    rclpy.init(args=args)
    node = BunkerRcAutoPermit()
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
