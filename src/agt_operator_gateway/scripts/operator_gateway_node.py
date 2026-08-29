#!/usr/bin/env python3

from __future__ import annotations

import rclpy

from agt_operator_gateway.ros_adapter import RobotStateAdapter
from agt_operator_gateway.server import GatewayHttpServer


def main(args=None) -> None:
    rclpy.init(args=args)
    node = RobotStateAdapter()
    server = GatewayHttpServer(
        node.store,
        host=node.host,
        port=node.port,
        stream_poll_s=node.stream_poll_s,
        offline_after_ms=node.offline_after_ms,
    )
    try:
        server.start()
        node.get_logger().info(
            f'operator gateway listening on http://{node.host}:{node.port}'
        )
        rclpy.spin(node)
    finally:
        server.stop()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
