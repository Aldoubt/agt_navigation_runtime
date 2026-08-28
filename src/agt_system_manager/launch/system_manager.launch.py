from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    share = Path(get_package_share_directory("agt_system_manager"))
    default_config = share / "config" / "system_manager.yaml"

    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "system_manager_config", default_value=str(default_config)
            ),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            Node(
                package="agt_system_manager",
                executable="system_manager_node.py",
                name="agt_system_manager",
                output="screen",
                parameters=[
                    LaunchConfiguration("system_manager_config"),
                    {
                        "use_sim_time": ParameterValue(
                            LaunchConfiguration("use_sim_time"), value_type=bool
                        )
                    },
                ],
            ),
        ]
    )
