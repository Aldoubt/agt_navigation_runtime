from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    return LaunchDescription(
        [
            DeclareLaunchArgument("localization_timeout_s", default_value="2.0"),
            DeclareLaunchArgument("lifecycle_timeout_s", default_value="3.0"),
            DeclareLaunchArgument("lifecycle_poll_period_s", default_value="0.5"),
            Node(
                package="agt_site_navigation",
                executable="navigation_runtime_status_node.py",
                name="agt_navigation_runtime_status",
                output="screen",
                parameters=[
                    {
                        "localization_timeout_s": ParameterValue(
                            LaunchConfiguration("localization_timeout_s"), value_type=float
                        ),
                        "lifecycle_timeout_s": ParameterValue(
                            LaunchConfiguration("lifecycle_timeout_s"), value_type=float
                        ),
                        "lifecycle_poll_period_s": ParameterValue(
                            LaunchConfiguration("lifecycle_poll_period_s"), value_type=float
                        ),
                    }
                ],
            ),
        ]
    )
