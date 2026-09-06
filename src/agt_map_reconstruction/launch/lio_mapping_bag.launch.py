from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.conditions import IfCondition
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
        Node(
            package='fast_lio', executable='fastlio_mapping',
            name='fast_lio_bag_mapper', output='screen',
            parameters=[
                str(odom_share / 'config' / 'fast_lio_mid360_mapping.yaml'),
                {'use_sim_time': True},
            ],
            remappings=[
                ('/cloud_registered', '/agt/odometry/backend/registered_points'),
                ('/Odometry', '/aft_mapped_to_init'),
            ],
        ),
        Node(
            package='agt_odometry', executable='fast_livo2_adapter.py',
            name='agt_odometry_fast_lio_adapter', output='screen',
            parameters=[
                str(odom_share / 'config' / 'fast_livo2_adapter.yaml'),
                {'use_sim_time': True},
            ],
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
