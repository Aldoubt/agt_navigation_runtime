from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument("runtime_dir", default_value="runtime"),
        DeclareLaunchArgument("repository_root", default_value=""),
        Node(
            package="agt_experiment_manager",
            executable="experiment_manager_node.py",
            name="agt_experiment_manager",
            output="screen",
            parameters=[{
                "runtime_dir": LaunchConfiguration("runtime_dir"),
                "repository_root": LaunchConfiguration("repository_root"),
            }],
        ),
    ])

