from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    package_share = Path(get_package_share_directory("agt_localization"))
    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "params_file",
                default_value=str(package_share / "config" / "relocalization.yaml"),
            ),
            DeclareLaunchArgument(
                "correction_params_file",
                default_value=str(package_share / "config" / "global_correction.yaml"),
            ),
            DeclareLaunchArgument("global_map_pcd", default_value=""),
            DeclareLaunchArgument("global_map_processing_record", default_value=""),
            DeclareLaunchArgument("configured_candidates_yaml", default_value=""),
            DeclareLaunchArgument("last_valid_pose_path", default_value=""),
            DeclareLaunchArgument(
                "external_coarse_pose_topic", default_value="/agt/localization/coarse_pose"
            ),
            DeclareLaunchArgument("manual_initialpose_enabled", default_value="true"),
            DeclareLaunchArgument("map_id", default_value=""),
            DeclareLaunchArgument("map_hash", default_value=""),
            DeclareLaunchArgument("backend", default_value="ndt"),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            Node(
                package="agt_localization",
                executable="relocalization_node",
                name="agt_relocalization",
                output="screen",
                parameters=[
                    LaunchConfiguration("params_file"),
                    {
                        "global_map_pcd": LaunchConfiguration("global_map_pcd"),
                        "global_map_processing_record": LaunchConfiguration(
                            "global_map_processing_record"
                        ),
                        "configured_candidates_yaml": LaunchConfiguration(
                            "configured_candidates_yaml"
                        ),
                        "last_valid_pose_path": LaunchConfiguration("last_valid_pose_path"),
                        "external_coarse_pose_topic": LaunchConfiguration(
                            "external_coarse_pose_topic"
                        ),
                        "manual_initialpose_enabled": ParameterValue(
                            LaunchConfiguration("manual_initialpose_enabled"), value_type=bool
                        ),
                        "map_id": LaunchConfiguration("map_id"),
                        "map_hash": LaunchConfiguration("map_hash"),
                        "backend": LaunchConfiguration("backend"),
                        # V25-10 invariant: relocalization produces evidence only.
                        "publish_tf": False,
                        "use_sim_time": ParameterValue(
                            LaunchConfiguration("use_sim_time"), value_type=bool
                        ),
                    },
                ],
            ),
            Node(
                package="agt_localization",
                executable="global_correction_manager",
                name="agt_global_correction_manager",
                output="screen",
                parameters=[
                    LaunchConfiguration("correction_params_file"),
                    {
                        "map_id": LaunchConfiguration("map_id"),
                        "map_hash": LaunchConfiguration("map_hash"),
                        "use_sim_time": ParameterValue(
                            LaunchConfiguration("use_sim_time"), value_type=bool
                        ),
                    },
                ],
            ),
        ]
    )
