from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    navigation_share = Path(get_package_share_directory("agt_navigation"))
    runtime_root = LaunchConfiguration("runtime_root")
    maps_root = PathJoinSubstitution([runtime_root, "maps"])
    vehicle_profile = LaunchConfiguration("vehicle_profile")
    distance_m = LaunchConfiguration("distance_m")

    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "runtime_root", default_value="/tmp/agt_route_system_smoke"
            ),
            DeclareLaunchArgument(
                "vehicle_profile",
                default_value=str(
                    navigation_share / "config" / "route_smoke_vehicle.yaml"
                ),
            ),
            DeclareLaunchArgument("distance_m", default_value="2.0"),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(navigation_share / "launch" / "route_controller_smoke.launch.py")
                )
            ),
            Node(
                package="agt_navigation",
                executable="route_system_smoke_fixture.py",
                name="agt_route_system_smoke_fixture",
                output="screen",
                parameters=[
                    {
                        "maps_root": maps_root,
                        "vehicle_profile": vehicle_profile,
                        "distance_m": ParameterValue(distance_m, value_type=float),
                    }
                ],
            ),
            Node(
                package="agt_navigation",
                executable="navigation_capability_server.py",
                name="agt_route_system_navigation_capability",
                output="screen",
                parameters=[
                    {
                        "runtime_dir": runtime_root,
                        "maps_root": maps_root,
                        "require_map": True,
                        "require_map_content_hashes": True,
                        "require_safety_ready": True,
                        "require_localization_valid": True,
                        "require_task_readiness": False,
                        "execution_vehicle_profile": vehicle_profile,
                        "route_controller_id_forward": "FollowPath",
                        "route_controller_id_reverse": "FollowPath",
                        "route_goal_checker_id": "general_goal_checker",
                        "nav2_wait_timeout": 5.0,
                    }
                ],
            ),
        ]
    )
