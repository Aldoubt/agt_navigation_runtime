#!/usr/bin/env python3

from __future__ import annotations

import os

import rclpy

from agt_operator_gateway.mission_ros_adapter import MissionCommandAdapter
from agt_operator_gateway.ros_adapter import RobotStateAdapter
from agt_operator_gateway.server import GatewayHttpServer

COMMAND_TOKEN_ENV = 'AGT_OPERATOR_COMMAND_TOKEN'


def main(args=None) -> None:
    rclpy.init(args=args)
    node = RobotStateAdapter()

    command_token = os.environ.get(COMMAND_TOKEN_ENV, '').strip()
    mission_commands = None
    write_api_enabled = False
    if node.write_api_enabled:
        if command_token:
            mission_commands = MissionCommandAdapter(
                node,
                timeout_s=node.mission_command_timeout_s,
            )
            write_api_enabled = True
        else:
            node.get_logger().error(
                f'write_api_enabled requested but {COMMAND_TOKEN_ENV} is empty; '
                'continuing in read-only mode'
            )

    server = GatewayHttpServer(
        node.store,
        host=node.host,
        port=node.port,
        stream_poll_s=node.stream_poll_s,
        offline_after_ms=node.offline_after_ms,
        allowed_origins=node.cors_allowed_origins,
        mission_commands=mission_commands,
        write_api_enabled=write_api_enabled,
        command_token=command_token,
    )
    try:
        server.start()
        mode = 'read-write' if write_api_enabled else 'read-only'
        node.get_logger().info(
            f'operator gateway listening on http://{node.host}:{node.port} ({mode})'
        )
        rclpy.spin(node)
    finally:
        server.stop()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
