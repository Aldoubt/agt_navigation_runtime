import re
from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, OpaqueFunction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


_SHA256_PATTERN = re.compile(r"sha256:[0-9a-f]{64}")


def _validate_frozen_assets(context):
    map_id = LaunchConfiguration("map_id").perform(context).strip()
    if not map_id:
        raise RuntimeError("map_id must not be empty")

    for name in (
        "global_map_pcd",
        "global_map_processing_record",
        "navigation_map",
    ):
        path = Path(LaunchConfiguration(name).perform(context)).expanduser()
        if not path.is_file():
            raise RuntimeError(f"{name} must be a file: {path}")

    map_hash = LaunchConfiguration("map_hash").perform(context).strip()
    if _SHA256_PATTERN.fullmatch(map_hash) is None:
        raise RuntimeError("map_hash must match sha256:<64 lowercase hex>")

    if LaunchConfiguration("start_gnss").perform(context).strip().lower() in {
        "true",
        "1",
        "yes",
        "on",
    }:
        input_topic = LaunchConfiguration("gnss_input_topic").perform(context).strip()
        if not input_topic.startswith("/"):
            raise RuntimeError("start_gnss requires an absolute gnss_input_topic")
        if input_topic == "/agt/sensors/gnss/fix":
            raise RuntimeError("gnss_input_topic must not equal canonical GNSS output")

    return []


def generate_launch_description():
    bringup_share = Path(get_package_share_directory("agt_bringup"))
    navigation_share = Path(get_package_share_directory("agt_navigation"))

    return LaunchDescription(
        [
            DeclareLaunchArgument("platform", default_value="bunker"),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument("global_map_pcd"),
            DeclareLaunchArgument("global_map_processing_record"),
            DeclareLaunchArgument("navigation_map"),
            DeclareLaunchArgument("map_id"),
            DeclareLaunchArgument("map_hash"),
            DeclareLaunchArgument("localization_backend", default_value="ndt"),
            DeclareLaunchArgument("localization_status_timeout", default_value="10.0"),
            DeclareLaunchArgument("start_gnss", default_value="false"),
            DeclareLaunchArgument("gnss_input_topic", default_value=""),
            DeclareLaunchArgument("start_chassis", default_value="false"),
            DeclareLaunchArgument("chassis_operation_mode", default_value="control"),
            DeclareLaunchArgument("can_interface", default_value="can0"),
            DeclareLaunchArgument("start_rviz", default_value="true"),
            OpaqueFunction(function=_validate_frozen_assets),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(bringup_share / "launch" / "system.launch.py")
                ),
                launch_arguments={
                    "platform": LaunchConfiguration("platform"),
                    "use_sim_time": LaunchConfiguration("use_sim_time"),
                    "start_sensor": "true",
                    "start_sensor_monitor": "true",
                    "start_gnss": LaunchConfiguration("start_gnss"),
                    "gnss_input_topic": LaunchConfiguration("gnss_input_topic"),
                    "start_odometry": "true",
                    "mapping_save_pcd": "false",
                    "start_perception": "true",
                    "start_localization": "true",
                    "start_navigation": "true",
                    "enable_rviz_goal_bridge": "true",
                    "start_chassis": LaunchConfiguration("start_chassis"),
                    "chassis_operation_mode": LaunchConfiguration("chassis_operation_mode"),
                    "can_interface": LaunchConfiguration("can_interface"),
                    "global_map_pcd": LaunchConfiguration("global_map_pcd"),
                    "global_map_processing_record": LaunchConfiguration("global_map_processing_record"),
                    "navigation_map": LaunchConfiguration("navigation_map"),
                    "map_id": LaunchConfiguration("map_id"),
                    "map_hash": LaunchConfiguration("map_hash"),
                    "localization_backend": LaunchConfiguration("localization_backend"),
                    "localization_status_timeout": LaunchConfiguration(
                        "localization_status_timeout"
                    ),
                }.items(),
            ),
            Node(
                package="rviz2",
                executable="rviz2",
                name="agt_field_navigation_rviz",
                output="screen",
                arguments=[
                    "-d",
                    str(navigation_share / "config" / "field_navigation.rviz"),
                ],
                condition=IfCondition(LaunchConfiguration("start_rviz")),
            ),
        ]
    )
