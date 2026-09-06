from pathlib import Path

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    share = Path(get_package_share_directory("agt_map_reconstruction"))
    config = LaunchConfiguration("config")
    bag = LaunchConfiguration("bag")
    play_bag = LaunchConfiguration("play_bag")
    bag_rate = LaunchConfiguration("bag_rate")
    return LaunchDescription([
        DeclareLaunchArgument("config", default_value=str(share / "config" / "reconstruction.yaml")),
        DeclareLaunchArgument("bag", default_value=""),
        DeclareLaunchArgument("play_bag", default_value="false"),
        DeclareLaunchArgument("bag_rate", default_value="5.0"),
        Node(
            package="agt_map_reconstruction",
            executable="reconstruction_node",
            name="agt_map_reconstruction",
            output="screen",
            parameters=[config],
        ),
        ExecuteProcess(
            cmd=["ros2", "bag", "play", bag, "--clock", "--rate", bag_rate],
            output="screen",
            condition=IfCondition(play_bag),
        ),
    ])
