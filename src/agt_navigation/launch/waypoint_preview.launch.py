"""Offline waypoint preview: map + planner + Qt, with no motion stack."""

import json
from pathlib import Path

import yaml
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, OpaqueFunction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def _planner_nodes(context):
    nav_share = Path(get_package_share_directory("agt_navigation"))
    profile_path = Path(LaunchConfiguration("platform_profile").perform(context))
    profile = yaml.safe_load(profile_path.read_text(encoding="utf-8"))
    footprint = profile["platform"]["geometry"]["navigation_footprint"]
    footprint_text = str([[float(x), float(y)] for x, y in footprint])
    params = [
        str(nav_share / "config" / "waypoint_preview_nav2.yaml"),
        {"footprint": footprint_text, "use_sim_time": False},
    ]
    return [
        Node(
            package="nav2_planner",
            executable="planner_server",
            name="planner_server",
            output="screen",
            parameters=params,
        ),
        Node(
            package="agt_navigation",
            executable="waypoint_preview_planner.py",
            name="agt_waypoint_preview_planner",
            output="screen",
            parameters=[{"footprint_json": json.dumps(footprint)}],
        ),
        Node(
            package="nav2_lifecycle_manager",
            executable="lifecycle_manager",
            name="lifecycle_manager_waypoint_preview_planner",
            output="screen",
            parameters=[
                {
                    "autostart": True,
                    "node_names": ["planner_server"],
                    "use_sim_time": False,
                }
            ],
        ),
    ]


def generate_launch_description():
    nav_share = Path(get_package_share_directory("agt_navigation"))
    ui_share = Path(get_package_share_directory("agt_ui_bridge"))
    root = nav_share.parents[3]
    return LaunchDescription(
        [
            DeclareLaunchArgument("map"),
            DeclareLaunchArgument(
                "platform_profile",
                default_value=str(root / "profiles" / "platforms" / "bunker.yaml"),
            ),
            DeclareLaunchArgument("start_gui", default_value="true"),
            DeclareLaunchArgument("start_rviz", default_value="true"),
            Node(
                package="nav2_map_server",
                executable="map_server",
                name="map_server",
                output="screen",
                parameters=[
                    {
                        "yaml_filename": LaunchConfiguration("map"),
                        "use_sim_time": False,
                    }
                ],
                remappings=[("map", "/agt/map/global_occupancy")],
            ),
            Node(
                package="nav2_lifecycle_manager",
                executable="lifecycle_manager",
                name="lifecycle_manager_waypoint_preview_map",
                output="screen",
                parameters=[
                    {
                        "autostart": True,
                        "node_names": ["map_server"],
                        "use_sim_time": False,
                    }
                ],
            ),
            OpaqueFunction(function=_planner_nodes),
            Node(
                package="agt_navigation",
                executable="start_waypoint_preview_rviz.sh",
                name="agt_waypoint_preview_rviz",
                output="screen",
                arguments=[
                    "-d",
                    str(nav_share / "config" / "waypoint_preview.rviz"),
                ],
                condition=IfCondition(LaunchConfiguration("start_rviz")),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(ui_share / "launch" / "ros_qt5_gui.launch.py")
                ),
                launch_arguments={
                    "profile": "offline",
                    "map": LaunchConfiguration("map"),
                    "start_map_io_bridge": "false",
                }.items(),
                condition=IfCondition(LaunchConfiguration("start_gui")),
            ),
        ]
    )
