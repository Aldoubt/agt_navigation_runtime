from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='camera_gimbal_manager',
            executable='camera_gimbal_manager_node',
            name='camera_gimbal_manager',
            parameters=[os.path.join(
                get_package_share_directory('camera_gimbal_manager'),
                'config', 'gimbal_manager.yaml')],
            output='screen',
        )
    ])
