from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    default_config = (
        Path(get_package_share_directory('agt_operator_gateway'))
        / 'config'
        / 'operator_gateway.yaml'
    )
    config_file = LaunchConfiguration('config_file')
    return LaunchDescription([
        DeclareLaunchArgument(
            'config_file',
            default_value=str(default_config),
            description='Operator gateway ROS parameter file',
        ),
        Node(
            package='agt_operator_gateway',
            executable='operator_gateway_node.py',
            name='agt_operator_gateway',
            output='screen',
            parameters=[config_file],
        )
    ])
