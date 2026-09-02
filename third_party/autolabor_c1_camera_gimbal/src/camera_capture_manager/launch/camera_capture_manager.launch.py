from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='camera_capture_manager',
            executable='camera_capture_manager',
            name='camera_capture_manager',
            output='screen',
        ),
    ])
