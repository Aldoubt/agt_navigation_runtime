from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    config = (
        Path(get_package_share_directory('agt_operator_gateway'))
        / 'config'
        / 'operator_gateway.yaml'
    )
    return LaunchDescription([
        Node(
            package='agt_operator_gateway',
            executable='operator_gateway_node.py',
            name='agt_operator_gateway',
            output='screen',
            parameters=[str(config)],
        )
    ])
