from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    share = Path(get_package_share_directory("agt_navigation"))
    params = LaunchConfiguration("params_file")
    use_sim_time = ParameterValue(LaunchConfiguration("use_sim_time"), value_type=bool)
    common = [params, {"use_sim_time": use_sim_time}]
    managed_nodes = [
        "map_server",
        "planner_server",
        "smoother_server",
        "controller_server",
        "behavior_server",
        "bt_navigator",
        "waypoint_follower",
        "collision_monitor",
    ]

    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "params_file", default_value=str(share / "config" / "nav2_bunker.yaml")
            ),
            DeclareLaunchArgument("map", default_value=str(share / "maps" / "offline_test.yaml")),
            DeclareLaunchArgument("runtime_dir", default_value="runtime"),
            DeclareLaunchArgument("maps_root", default_value=""),
            DeclareLaunchArgument("map_id", default_value=""),
            DeclareLaunchArgument("map_version_id", default_value=""),
            DeclareLaunchArgument("current_map_yaml_sha256", default_value=""),
            DeclareLaunchArgument("current_map_image_sha256", default_value=""),
            DeclareLaunchArgument("current_localization_pcd_sha256", default_value=""),
            DeclareLaunchArgument("execution_vehicle_profile", default_value=""),
            DeclareLaunchArgument("route_controller_id_forward", default_value="FollowPath"),
            DeclareLaunchArgument("route_controller_id_reverse", default_value="FollowPath"),
            DeclareLaunchArgument("route_goal_checker_id", default_value="general_goal_checker"),
            DeclareLaunchArgument("route_progress_checker_id", default_value="progress_checker"),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument("autostart", default_value="false"),
            DeclareLaunchArgument("enable_localization_gate", default_value="true"),
            DeclareLaunchArgument("localization_status_timeout", default_value="10.0"),
            DeclareLaunchArgument(
                "use_keepout_filter",
                default_value="false",
                description=(
                    "Start the Keepout Costmap Filter Info Server. When enabled, "
                    "/agt/map/keepout_mask must be published by the semantic map server."
                ),
            ),
            Node(
                package="nav2_map_server",
                executable="map_server",
                name="map_server",
                output="screen",
                parameters=[params, {"yaml_filename": LaunchConfiguration("map"), "use_sim_time": use_sim_time}],
            ),
            Node(
                package="nav2_map_server",
                executable="costmap_filter_info_server",
                name="costmap_filter_info_server",
                output="screen",
                parameters=common,
                condition=IfCondition(LaunchConfiguration("use_keepout_filter")),
            ),
            Node(package="nav2_planner", executable="planner_server", name="planner_server", output="screen", parameters=common),
            Node(package="nav2_smoother", executable="smoother_server", name="smoother_server", output="screen", parameters=common),
            Node(
                package="nav2_controller",
                executable="controller_server",
                name="controller_server",
                output="screen",
                parameters=common,
                remappings=[("cmd_vel", "/agt/navigation/cmd_vel_raw")],
            ),
            Node(
                package="nav2_behaviors",
                executable="behavior_server",
                name="behavior_server",
                output="screen",
                parameters=common,
                remappings=[("cmd_vel", "/agt/navigation/cmd_vel_raw")],
            ),
            Node(
                package="nav2_bt_navigator",
                executable="bt_navigator",
                name="bt_navigator",
                output="screen",
                parameters=[
                    params,
                    {
                        "use_sim_time": use_sim_time,
                        "default_nav_to_pose_bt_xml": str(
                            share / "behavior_trees" / "navigate_to_pose.xml"
                        ),
                    },
                ],
            ),
            Node(package="nav2_waypoint_follower", executable="waypoint_follower", name="waypoint_follower", output="screen", parameters=common),
            Node(package="nav2_collision_monitor", executable="collision_monitor", name="collision_monitor", output="screen", parameters=common),
            Node(
                package="agt_navigation",
                executable="goal_pose_bridge.py",
                name="agt_goal_pose_bridge",
                output="screen",
                parameters=[{"use_sim_time": use_sim_time}],
            ),
            Node(
                package="agt_navigation",
                executable="navigation_capability_server.py",
                name="agt_waypoint_task_server",
                output="screen",
                parameters=[
                    {
                        "use_sim_time": use_sim_time,
                        "require_localization_valid": True,
                        "require_task_readiness": True,
                        "runtime_dir": LaunchConfiguration("runtime_dir"),
                        "maps_root": LaunchConfiguration("maps_root"),
                        "allow_legacy_local_task_file": False,
                        "allow_direct_pose_goals": False,
                        "localization_status_timeout": ParameterValue(
                            LaunchConfiguration("localization_status_timeout"), value_type=float
                        ),
                        "current_map_id": LaunchConfiguration("map_id"),
                        "current_map_version_id": LaunchConfiguration("map_version_id"),
                        "current_map_yaml_sha256": LaunchConfiguration("current_map_yaml_sha256"),
                        "current_map_image_sha256": LaunchConfiguration("current_map_image_sha256"),
                        "current_localization_pcd_sha256": LaunchConfiguration("current_localization_pcd_sha256"),
                        "execution_vehicle_profile": LaunchConfiguration("execution_vehicle_profile"),
                        "route_controller_id_forward": LaunchConfiguration("route_controller_id_forward"),
                        "route_controller_id_reverse": LaunchConfiguration("route_controller_id_reverse"),
                        "route_goal_checker_id": LaunchConfiguration("route_goal_checker_id"),
                        "route_progress_checker_id": LaunchConfiguration("route_progress_checker_id"),
                    }
                ],
            ),
            Node(
                package="agt_navigation",
                executable="task_registry_node.py",
                name="agt_task_registry",
                output="screen",
                parameters=[
                    {
                        "use_sim_time": use_sim_time,
                        "runtime_dir": LaunchConfiguration("runtime_dir"),
                        "maps_root": LaunchConfiguration("maps_root"),
                    }
                ],
            ),
            Node(
                package="agt_navigation",
                executable="waypoint_preview_planner.py",
                name="agt_waypoint_preview_planner",
                output="screen",
                parameters=[{"use_sim_time": use_sim_time}],
            ),
            Node(
                package="nav2_lifecycle_manager",
                executable="lifecycle_manager",
                name="lifecycle_manager_navigation",
                output="screen",
                parameters=[
                    {"use_sim_time": use_sim_time},
                    {"autostart": ParameterValue(LaunchConfiguration("autostart"), value_type=bool)},
                    {"node_names": managed_nodes},
                    {"bond_timeout": 4.0},
                ],
            ),
            Node(
                package="nav2_lifecycle_manager",
                executable="lifecycle_manager_keepout_filter",
                name="lifecycle_manager_keepout_filter",
                output="screen",
                parameters=[
                    {"use_sim_time": use_sim_time},
                    {"autostart": True},
                    {"node_names": ["costmap_filter_info_server"]},
                    {"bond_timeout": 4.0},
                ],
                condition=IfCondition(LaunchConfiguration("use_keepout_filter")),
            ),
            Node(
                package="agt_bringup",
                executable="localization_navigation_gate.py",
                name="agt_localization_navigation_gate",
                output="screen",
                parameters=[{
                    "localization_status_timeout": ParameterValue(
                        LaunchConfiguration("localization_status_timeout"), value_type=float
                    )
                }],
                condition=IfCondition(LaunchConfiguration("enable_localization_gate")),
            ),
        ]
    )
