from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription(
        [
            DeclareLaunchArgument("sites_root", default_value="/opt/agt/sites"),
            DeclareLaunchArgument(
                "site_vehicle_profile", default_value="/opt/agt/profiles/bunker.yaml"
            ),
            Node(
                package="agt_site_navigation",
                executable="site_navigation_binding_node.py",
                name="agt_site_navigation_binding",
                output="screen",
                parameters=[
                    {
                        "sites_root": LaunchConfiguration("sites_root"),
                        "site_vehicle_profile": LaunchConfiguration(
                            "site_vehicle_profile"
                        ),
                    }
                ],
            ),
        ]
    )
