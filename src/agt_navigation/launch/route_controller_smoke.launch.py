from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    navigation_share = Path(get_package_share_directory("agt_navigation"))
    safety_share = Path(get_package_share_directory("agt_safety"))
    params_file = LaunchConfiguration("params_file")

    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "params_file",
                default_value=str(navigation_share / "config" / "nav2_bunker.yaml"),
            ),
            DeclareLaunchArgument("synthetic_obstacle_enabled", default_value="false"),
            DeclareLaunchArgument("initial_x", default_value="0.0"),
            DeclareLaunchArgument("initial_y", default_value="0.0"),
            DeclareLaunchArgument("initial_yaw", default_value="0.0"),
            Node(
                package="agt_navigation",
                executable="differential_drive_simulator.py",
                name="agt_route_controller_simulator",
                output="screen",
                parameters=[
                    {
                        "initial_x": ParameterValue(
                            LaunchConfiguration("initial_x"), value_type=float
                        ),
                        "initial_y": ParameterValue(
                            LaunchConfiguration("initial_y"), value_type=float
                        ),
                        "initial_yaw": ParameterValue(
                            LaunchConfiguration("initial_yaw"), value_type=float
                        ),
                        "synthetic_obstacle_enabled": ParameterValue(
                            LaunchConfiguration("synthetic_obstacle_enabled"),
                            value_type=bool,
                        ),
                    }
                ],
            ),
            Node(
                package="agt_safety",
                executable="tracked_safety_controller.py",
                name="agt_route_controller_safety",
                output="screen",
                parameters=[
                    str(safety_share / "config" / "bunker_safety.yaml"),
                    {
                        "startup_motion_enabled": True,
                        # This gate isolates controller plumbing. Localization
                        # validity is exercised separately by capability tests.
                        "require_localization_valid": False,
                    },
                ],
            ),
            Node(
                package="nav2_controller",
                executable="controller_server",
                name="controller_server",
                output="screen",
                parameters=[params_file],
                remappings=[("cmd_vel", "/agt/navigation/cmd_vel_raw")],
            ),
            Node(
                package="nav2_collision_monitor",
                executable="collision_monitor",
                name="collision_monitor",
                output="screen",
                parameters=[params_file],
            ),
            Node(
                package="nav2_lifecycle_manager",
                executable="lifecycle_manager",
                name="lifecycle_manager_route_controller_smoke",
                output="screen",
                parameters=[
                    {"autostart": True},
                    {"node_names": ["controller_server", "collision_monitor"]},
                    {"bond_timeout": 4.0},
                ],
            ),
        ]
    )
