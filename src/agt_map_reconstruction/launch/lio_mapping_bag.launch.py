from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    map_share = Path(get_package_share_directory('agt_map_reconstruction'))
    odom_share = Path(get_package_share_directory('agt_odometry'))
    bag = LaunchConfiguration('bag')
    config = LaunchConfiguration('config')
    rate = LaunchConfiguration('bag_rate')
    return LaunchDescription([
        DeclareLaunchArgument('bag'),
        DeclareLaunchArgument('config', default_value=str(map_share / 'config' / 'reconstruction_lio_bag.yaml')),
        DeclareLaunchArgument('bag_rate', default_value='5.0'),
        DeclareLaunchArgument('start_rviz', default_value='true'),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(str(odom_share / 'launch' / 'fast_livo2_odometry.launch.py')),
            launch_arguments={
                'use_sim_time': 'true',
                'start_lidar_self_filter': 'false',
                'fast_livo_input_topic': '/agt/sensors/lidar/custom',
            }.items(),
        ),
        Node(
            package='agt_map_reconstruction', executable='reconstruction_node',
            name='agt_map_reconstruction', output='screen',
            parameters=[config, {'use_sim_time': True}],
        ),
        ExecuteProcess(
            cmd=['ros2', 'bag', 'play', bag, '--clock', '--rate', rate,
                 '--topics', '/agt/sensors/lidar/custom', '/agt/sensors/imu/data'],
            output='screen',
        ),
        ExecuteProcess(
            cmd=['rviz2', '-d', str(map_share / 'rviz' / 'reconstruction.rviz')],
            output='screen', condition=IfCondition(LaunchConfiguration('start_rviz')),
        ),
    ])
