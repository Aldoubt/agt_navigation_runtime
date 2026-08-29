"""Planner-only P1 headland smoke test: map + planner + artifact runner."""

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, RegisterEventHandler, Shutdown
from launch.event_handlers import OnProcessExit
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    nav_share = Path(get_package_share_directory("agt_navigation"))
    default_planner_config = str(
        nav_share / "config" / "headland_planner_smoke_nav2.yaml"
    )

    runner = Node(
        package="agt_navigation",
        executable="headland_planner_smoke.py",
        name="agt_headland_planner_smoke",
        output="screen",
        arguments=[
            "--planner-pairs",
            LaunchConfiguration("planner_pairs"),
            "--gap-diagnostics",
            LaunchConfiguration("gap_diagnostics"),
            "--request-derivation",
            LaunchConfiguration("request_derivation"),
            "--map-yaml",
            LaunchConfiguration("map"),
            "--output",
            LaunchConfiguration("output"),
            "--planner-id",
            LaunchConfiguration("planner_id"),
            "--planner-action",
            LaunchConfiguration("planner_action"),
            "--planner-contract",
            LaunchConfiguration("planner_contract"),
            "--result-mode",
            LaunchConfiguration("result_mode"),
            "--server-timeout",
            LaunchConfiguration("server_timeout_s"),
            "--request-timeout",
            LaunchConfiguration("request_timeout_s"),
        ],
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument("map"),
            DeclareLaunchArgument("planner_pairs"),
            DeclareLaunchArgument("gap_diagnostics"),
            DeclareLaunchArgument("request_derivation", default_value=""),
            DeclareLaunchArgument("output"),
            DeclareLaunchArgument(
                "planner_params", default_value=default_planner_config
            ),
            DeclareLaunchArgument(
                "planner_contract", default_value="baseline_source_map"
            ),
            DeclareLaunchArgument(
                "result_mode", default_value="expectation_match"
            ),
            DeclareLaunchArgument("planner_id", default_value="GridBased"),
            DeclareLaunchArgument(
                "planner_action", default_value="/compute_path_to_pose"
            ),
            DeclareLaunchArgument("server_timeout_s", default_value="30.0"),
            DeclareLaunchArgument("request_timeout_s", default_value="30.0"),
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
                package="nav2_planner",
                executable="planner_server",
                name="planner_server",
                output="screen",
                parameters=[LaunchConfiguration("planner_params")],
            ),
            Node(
                package="nav2_lifecycle_manager",
                executable="lifecycle_manager",
                name="lifecycle_manager_headland_smoke",
                output="screen",
                parameters=[
                    {
                        "autostart": True,
                        "node_names": ["map_server", "planner_server"],
                        "use_sim_time": False,
                    }
                ],
            ),
            runner,
            RegisterEventHandler(
                OnProcessExit(
                    target_action=runner,
                    on_exit=[Shutdown(reason="headland planner smoke finished")],
                )
            ),
        ]
    )
