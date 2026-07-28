from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument("runtime_dir", default_value="runtime"),
        Node(
            package="agt_mission_manager",
            executable="mission_manager_node.py",
            name="agt_mission_manager",
            output="screen",
            parameters=[{"runtime_dir": LaunchConfiguration("runtime_dir")}],
        ),
    ])

