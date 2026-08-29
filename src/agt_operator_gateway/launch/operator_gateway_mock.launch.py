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
            executable='mock_robot_state_publisher.py',
            name='agt_operator_gateway_mock_robot_state',
            output='screen',
            parameters=[{
                'publish_rate_hz': 5.0,
                'map_id': 'mock_map',
                'map_version_id': 'v1',
                'mission_id': 'mock_inspection',
                'x': 2.0,
                'y': 1.0,
                'yaw': 0.35,
            }],
        ),
        Node(
            package='agt_operator_gateway',
            executable='operator_gateway_node.py',
            name='agt_operator_gateway',
            output='screen',
            parameters=[str(config)],
        ),
    ])
