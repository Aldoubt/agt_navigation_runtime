from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    share = Path(get_package_share_directory("agt_chassis_mk_mini"))
    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "adapter_config", default_value=str(share / "config" / "mk_mini.yaml")
            ),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            Node(
                package="agt_chassis_mk_mini",
                executable="mk_mini_adapter.py",
                name="agt_mk_mini_adapter",
                output="screen",
                parameters=[
                    LaunchConfiguration("adapter_config"),
                    {
                        "use_sim_time": ParameterValue(
                            LaunchConfiguration("use_sim_time"), value_type=bool
                        )
                    },
                ],
            ),
        ]
    )
