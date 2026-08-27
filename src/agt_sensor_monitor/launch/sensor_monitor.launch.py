from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    default = str(
        Path(get_package_share_directory("agt_sensor_monitor"))
        / "config"
        / "sensor_monitor.yaml"
    )
    return LaunchDescription(
        [
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument("params_file", default_value=default),
            DeclareLaunchArgument("gnss_enabled", default_value="false"),
            Node(
                package="agt_sensor_monitor",
                executable="agt_sensor_monitor_node",
                name="agt_sensor_monitor",
                output="screen",
                parameters=[
                    LaunchConfiguration("params_file"),
                    {
                        "use_sim_time": LaunchConfiguration("use_sim_time"),
                        "gnss.enabled": ParameterValue(
                            LaunchConfiguration("gnss_enabled"), value_type=bool
                        ),
                        "gnss.required": False,
                    },
                ],
            ),
        ]
    )
