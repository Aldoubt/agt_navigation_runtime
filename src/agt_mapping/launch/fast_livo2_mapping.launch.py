from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    OpaqueFunction,
    SetLaunchConfiguration,
)
from launch.conditions import IfCondition, UnlessCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def validate_pcd_output(context):
    save_pcd = LaunchConfiguration("save_pcd").perform(context).strip().lower()
    if save_pcd not in {"true", "1", "yes", "on"}:
        return []
    output_dir = Path(LaunchConfiguration("pcd_output_dir").perform(context)).expanduser()
    if output_dir.exists() and not output_dir.is_dir():
        raise RuntimeError(f"PCD output path is not a directory: {output_dir}")
    existing = (
        sorted(path.name for path in output_dir.iterdir())
        if output_dir.is_dir()
        else []
    )
    if existing:
        raise RuntimeError(
            f"refusing to overwrite existing PCD output directory: {output_dir} "
            f"({', '.join(existing[:8])}); choose a new output directory"
        )
    return []


def generate_launch_description():
    mapping_share = Path(get_package_share_directory("agt_mapping"))
    sensor_share = Path(get_package_share_directory("agt_sensor_adapters"))
    return LaunchDescription([
        DeclareLaunchArgument("params_file", default_value=str(mapping_share / "config" / "mid360_lio_only.yaml")),
        DeclareLaunchArgument(
            "camera_params_file",
            default_value=str(mapping_share / "config" / "camera_disabled_placeholder.yaml"),
        ),
        DeclareLaunchArgument("use_sim_time", default_value="false"),
        DeclareLaunchArgument(
            "adapter_params_file",
            default_value=str(mapping_share / "config" / "fast_livo2_adapter.yaml"),
        ),
        DeclareLaunchArgument("save_pcd", default_value="false"),
        DeclareLaunchArgument("pcd_save_interval", default_value="-1"),
        DeclareLaunchArgument("pcd_output_dir", default_value="runtime/maps/fast_livo2"),
        DeclareLaunchArgument(
            "platform_profile",
            default_value=str(mapping_share.parents[3] / "profiles" / "platforms" / "bunker.yaml"),
        ),
        DeclareLaunchArgument("start_lidar_self_filter", default_value="true"),
        DeclareLaunchArgument("lidar_self_filter_geometry_source", default_value="urdf"),
        DeclareLaunchArgument(
            "lidar_self_filter_params_file",
            default_value=str(sensor_share / "config" / "livox_self_filter.yaml"),
        ),
        DeclareLaunchArgument(
            "fast_livo_input_topic",
            default_value="/agt/sensors/lidar/custom_filtered",
        ),
        OpaqueFunction(function=validate_pcd_output),
        SetLaunchConfiguration(
            "fast_livo_input_topic",
            "/agt/sensors/lidar/custom",
            condition=UnlessCondition(LaunchConfiguration("start_lidar_self_filter")),
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(str(sensor_share / "launch" / "lidar_self_filter.launch.py")),
            launch_arguments={
                "filter_params_file": LaunchConfiguration("lidar_self_filter_params_file"),
                "platform_profile": LaunchConfiguration("platform_profile"),
                "geometry_source": LaunchConfiguration("lidar_self_filter_geometry_source"),
                "use_sim_time": LaunchConfiguration("use_sim_time"),
            }.items(),
            condition=IfCondition(LaunchConfiguration("start_lidar_self_filter")),
        ),
        Node(
            package="fast_livo", executable="fastlivo_mapping", name="fast_livo2_backend",
            output="screen",
            sigterm_timeout="30",
            sigkill_timeout="10",
            parameters=[
                LaunchConfiguration("params_file"),
                LaunchConfiguration("camera_params_file"), {
                "use_sim_time": LaunchConfiguration("use_sim_time"),
                "common.publish_tf": False,
                "common.lid_topic": LaunchConfiguration("fast_livo_input_topic"),
                "pcd_save.pcd_save_en": ParameterValue(
                    LaunchConfiguration("save_pcd"), value_type=bool
                ),
                "pcd_save.interval": ParameterValue(
                    LaunchConfiguration("pcd_save_interval"), value_type=int
                ),
                "pcd_save.output_directory": LaunchConfiguration("pcd_output_dir"),
            }],
            remappings=[
                ("/cloud_registered", "/agt/mapping/backend/registered_points"),
            ],
        ),
        Node(
            package="agt_mapping", executable="fast_livo2_adapter.py",
            name="agt_mapping_fast_livo2_adapter", output="screen",
            sigterm_timeout="10",
            sigkill_timeout="5",
            parameters=[LaunchConfiguration("adapter_params_file"), {
                "use_sim_time": LaunchConfiguration("use_sim_time")
            }],
        ),
    ])
