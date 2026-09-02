"""FAST-LIO-SAM mapping entrypoint placeholder.

This launch file is intentionally kept as a runtime wrapper. The underlying
SLAM implementation can be replaced without changing Nav2/HMI interfaces.
"""

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        # TODO: include fast_lio_sam launch after dependency import.
        # This node is only a migration placeholder.
        Node(
            package='agt_slam_runtime',
            executable='slam_bridge_node',
            name='agt_slam_runtime_bridge',
            output='screen',
        )
    ])
