from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('port_name', default_value='/dev/ttyUSB0'),
        DeclareLaunchArgument('baud_rate', default_value='115200'),
        DeclareLaunchArgument('query_rate', default_value='10.0'),
        Node(
            package='pantilt_camera_serial',
            executable='pantilt_camera_serial_node',
            namespace='pantilt_camera_serial0',
            name='driver',
            output='screen',
            parameters=[{
                'port_name': LaunchConfiguration('port_name'),
                'baud_rate': ParameterValue(LaunchConfiguration('baud_rate'), value_type=int),
                'query_rate': ParameterValue(LaunchConfiguration('query_rate'), value_type=float),
            }],
        ),
    ])
