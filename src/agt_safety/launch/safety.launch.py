from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    default_config = Path(get_package_share_directory("agt_safety")) / "config" / "safety.yaml"
    return LaunchDescription(
        [
            DeclareLaunchArgument("safety_config", default_value=str(default_config)),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument("require_auto_permit", default_value="false"),
            DeclareLaunchArgument("auto_permit_timeout", default_value="0.5"),
            Node(
                package="agt_safety",
                executable="safety_controller.py",
                name="agt_safety_controller",
                output="screen",
                parameters=[
                    LaunchConfiguration("safety_config"),
                    {
                        "use_sim_time": ParameterValue(
                            LaunchConfiguration("use_sim_time"), value_type=bool
                        ),
                        "require_auto_permit": ParameterValue(
                            LaunchConfiguration("require_auto_permit"), value_type=bool
                        ),
                        "auto_permit_timeout": ParameterValue(
                            LaunchConfiguration("auto_permit_timeout"), value_type=float
                        ),
                    },
                ],
            ),
        ]
    )
