from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    localization = Path(get_package_share_directory("agt_localization"))
    odometry = Path(get_package_share_directory("agt_odometry"))
    return LaunchDescription([
        DeclareLaunchArgument("global_map_pcd"),
        DeclareLaunchArgument("processing_record"),
        DeclareLaunchArgument("candidates"),
        DeclareLaunchArgument("map_id"),
        DeclareLaunchArgument("map_hash"),
        DeclareLaunchArgument("backend", default_value="ndt"),
        DeclareLaunchArgument("enable_recovery_trigger", default_value="false"),
        DeclareLaunchArgument("adapter_params_file", default_value=str(odometry / "config" / "fast_livo2_adapter_handheld.yaml")),
        DeclareLaunchArgument("params_file", default_value=str(odometry / "config" / "mid360_lio_only.yaml")),
        DeclareLaunchArgument("use_sim_time", default_value="true"),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(str(odometry / "launch" / "fast_livo2_odometry.launch.py")),
            launch_arguments={
                "params_file": LaunchConfiguration("params_file"),
                "adapter_params_file": LaunchConfiguration("adapter_params_file"),
                "use_sim_time": LaunchConfiguration("use_sim_time"),
                "start_lidar_self_filter": "false",
            }.items(),
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(str(localization / "launch" / "relocalization.launch.py")),
            launch_arguments={
                "params_file": str(localization / "config" / "relocalization_handheld_validation.yaml"),
                "correction_params_file": str(localization / "config" / "global_correction_handheld_validation.yaml"),
                "global_map_pcd": LaunchConfiguration("global_map_pcd"),
                "global_map_processing_record": LaunchConfiguration("processing_record"),
                "configured_candidates_yaml": LaunchConfiguration("candidates"),
                "map_id": LaunchConfiguration("map_id"),
                "map_hash": LaunchConfiguration("map_hash"),
                "backend": LaunchConfiguration("backend"),
                "use_sim_time": LaunchConfiguration("use_sim_time"),
                "manual_initialpose_enabled": "false",
                "enable_recovery_trigger": LaunchConfiguration("enable_recovery_trigger"),
            }.items(),
        ),
        Node(
            package="agt_localization", executable="reference_map_publisher.py",
            name="agt_localization_reference_map_publisher", output="screen",
            parameters=[{"pcd": LaunchConfiguration("global_map_pcd"), "use_sim_time": LaunchConfiguration("use_sim_time")}],
        ),
    ])
