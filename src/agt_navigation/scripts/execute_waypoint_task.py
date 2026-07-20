#!/usr/bin/env python3

import argparse
from pathlib import Path
import sys

from agt_interfaces.action import ExecuteWaypointTask
import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node


class TaskClient(Node):
    def __init__(self):
        super().__init__("agt_execute_waypoint_task")
        self.client = ActionClient(
            self, ExecuteWaypointTask, "/agt/navigation/execute_waypoint_task"
        )

    def feedback(self, message):
        value = message.feedback
        self.get_logger().info(
            f"{value.state}: loop={value.loop_index + 1}, "
            f"waypoint={value.current_waypoint + 1}/{value.total_waypoints}"
        )


def parse_args(argv):
    parser = argparse.ArgumentParser(
        description="Execute a task-chain JSON saved by ros_qt5_gui_app"
    )
    parser.add_argument("task_file")
    parser.add_argument(
        "--loop-count",
        type=int,
        default=1,
        help="finite execution count; default 1",
    )
    return parser.parse_args(argv)


def main(args=None):
    cli_args = parse_args(args if args is not None else sys.argv[1:])
    if cli_args.loop_count <= 0:
        raise SystemExit("--loop-count must be positive")
    task_path = Path(cli_args.task_file).expanduser().resolve()

    rclpy.init()
    node = TaskClient()
    try:
        if not node.client.wait_for_server(timeout_sec=5.0):
            node.get_logger().error("ExecuteWaypointTask server is unavailable")
            return 2
        goal = ExecuteWaypointTask.Goal()
        goal.task_file = str(task_path)
        goal.loop = cli_args.loop_count > 1
        goal.loop_count = cli_args.loop_count
        send_future = node.client.send_goal_async(goal, feedback_callback=node.feedback)
        rclpy.spin_until_future_complete(node, send_future)
        handle = send_future.result()
        if handle is None or not handle.accepted:
            node.get_logger().error("Waypoint task was rejected")
            return 3
        result_future = handle.get_result_async()
        rclpy.spin_until_future_complete(node, result_future)
        wrapped = result_future.result()
        result = wrapped.result
        if not result.success:
            node.get_logger().error(
                f"Task failed: error_code={result.error_code}, {result.message}"
            )
            return 4
        node.get_logger().info(result.message)
        return 0
    except KeyboardInterrupt:
        node.get_logger().warning("Canceling waypoint task")
        if "handle" in locals() and handle is not None:
            cancel_future = handle.cancel_goal_async()
            rclpy.spin_until_future_complete(node, cancel_future, timeout_sec=2.0)
        return 130
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    raise SystemExit(main())
