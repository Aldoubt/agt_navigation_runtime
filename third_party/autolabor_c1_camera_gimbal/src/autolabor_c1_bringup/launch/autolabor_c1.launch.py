from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    rviz_config = str(
        Path(get_package_share_directory('pantilt_camera_serial'))
        / 'rviz' / 'singleCamera.rviz'
    )

    return LaunchDescription([
        DeclareLaunchArgument('device_path', default_value='/dev/video0'),
        DeclareLaunchArgument('image_width', default_value='1920'),
        DeclareLaunchArgument('image_height', default_value='1080'),
        DeclareLaunchArgument('fps', default_value='30.0'),
        DeclareLaunchArgument('port_name', default_value='/dev/ttyUSB0'),
        DeclareLaunchArgument('baud_rate', default_value='115200'),
        DeclareLaunchArgument('query_rate', default_value='10.0'),
        DeclareLaunchArgument('gui', default_value='true'),
        DeclareLaunchArgument('capture_output_root', default_value='~/autolabor_c1_capture'),

        Node(
            package='opencv_camera_node',
            executable='opencv_camera_node',
            namespace='cv_camera0',
            name='camera',
            output='screen',
            parameters=[{
                'device_path': LaunchConfiguration('device_path'),
                'image_width': LaunchConfiguration('image_width'),
                'image_height': LaunchConfiguration('image_height'),
                'rate': LaunchConfiguration('fps'),
                'frame_id': 'camera_link',
                'camera_name': 'autolabor_c1_camera',
            }],
        ),

        Node(
            package='pantilt_camera_serial',
            executable='pantilt_camera_serial_node',
            namespace='pantilt_camera_serial0',
            name='driver',
            output='screen',
            parameters=[{
                'port_name': LaunchConfiguration('port_name'),
                'baud_rate': LaunchConfiguration('baud_rate'),
                'query_rate': LaunchConfiguration('query_rate'),
                'feedback_timeout': 1.0,
                'write_timeout': 0.5,
                'default_tolerance': 1.5,
                'max_tolerance': 10.0,
                'default_stable_samples': 3,
                'frame_id': 'gimbal_link',
            }],
        ),

        Node(
            package='camera_gimbal_capability',
            executable='camera_gimbal_capability',
            namespace='camera_gimbal',
            name='capability',
            output='screen',
            parameters=[{
                'image_topic': '/cv_camera0/image_raw',
                'gimbal_status_topic': '/pantilt_camera_serial0/pantilt_status',
                'move_action': '/pantilt_camera_serial0/move_pantilt',
                'acquire_action': 'acquire_view',
                'health_topic': 'health',
                'output_root': LaunchConfiguration('capture_output_root'),
                'default_tolerance': 1.5,
                'max_tolerance': 10.0,
                'default_motion_timeout': 8.0,
                'default_stable_samples': 3,
                'default_settle_time': 0.25,
                'default_image_timeout': 2.0,
            }],
        ),

        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            output='screen',
            arguments=['-d', rviz_config],
            condition=IfCondition(LaunchConfiguration('gui')),
        ),
    ])
