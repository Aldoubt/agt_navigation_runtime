from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('move_delay', default_value='0.35'),
        DeclareLaunchArgument('publish_images', default_value='true'),
        DeclareLaunchArgument('serial_connected', default_value='true'),
        DeclareLaunchArgument('drop_images_on_motion', default_value='false'),
        DeclareLaunchArgument('fail_motion', default_value='false'),
        DeclareLaunchArgument('capture_output_root', default_value='~/autolabor_c1_capture'),
        Node(
            package='autolabor_c1_bringup',
            executable='fake_gimbal_camera.py',
            namespace='pantilt_camera_serial0',
            name='fake_hardware',
            output='screen',
            parameters=[{
                'move_delay': ParameterValue(LaunchConfiguration('move_delay'), value_type=float),
                'publish_images': ParameterValue(LaunchConfiguration('publish_images'), value_type=bool),
                'serial_connected': ParameterValue(LaunchConfiguration('serial_connected'), value_type=bool),
                'drop_images_on_motion': ParameterValue(LaunchConfiguration('drop_images_on_motion'), value_type=bool),
                'fail_motion': ParameterValue(LaunchConfiguration('fail_motion'), value_type=bool),
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
                'default_motion_timeout': 8.0,
                'default_stable_samples': 3,
                'default_settle_time': 0.10,
                'default_image_timeout': 1.0,
            }],
        ),
    ])
