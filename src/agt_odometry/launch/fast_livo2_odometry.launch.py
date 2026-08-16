from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    SetLaunchConfiguration,
)
from launch.conditions import IfCondition, UnlessCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    odometry_share = Path(get_package_share_directory("agt_odometry"))
    sensor_share = Path(get_package_share_directory("agt_sensor_adapters"))
    return LaunchDescription([
        DeclareLaunchArgument(
            "params_file",
            default_value=str(odometry_share / "config" / "mid360_lio_only.yaml"),
        ),
        DeclareLaunchArgument(
            "camera_params_file",
            default_value=str(
                odometry_share / "config" / "camera_disabled_placeholder.yaml"
            ),
        ),
        DeclareLaunchArgument("use_sim_time", default_value="false"),
        DeclareLaunchArgument(
            "adapter_params_file",
            default_value=str(
                odometry_share / "config" / "fast_livo2_adapter.yaml"
            ),
        ),
        DeclareLaunchArgument(
            "platform_profile",
            default_value=str(
                odometry_share.parents[3] / "profiles" / "platforms" / "bunker.yaml"
            ),
        ),
        DeclareLaunchArgument("start_lidar_self_filter", default_value="true"),
        DeclareLaunchArgument(
            "lidar_self_filter_geometry_source", default_value="urdf"
        ),
        DeclareLaunchArgument(
            "lidar_self_filter_params_file",
            default_value=str(sensor_share / "config" / "livox_self_filter.yaml"),
        ),
        DeclareLaunchArgument(
            "fast_livo_input_topic",
            default_value="/agt/sensors/lidar/custom_filtered",
        ),
        SetLaunchConfiguration(
            "fast_livo_input_topic",
            "/agt/sensors/lidar/custom",
            condition=UnlessCondition(
                LaunchConfiguration("start_lidar_self_filter")
            ),
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                str(sensor_share / "launch" / "lidar_self_filter.launch.py")
            ),
            launch_arguments={
                "filter_params_file": LaunchConfiguration(
                    "lidar_self_filter_params_file"
                ),
                "platform_profile": LaunchConfiguration("platform_profile"),
                "geometry_source": LaunchConfiguration(
                    "lidar_self_filter_geometry_source"
                ),
                "use_sim_time": LaunchConfiguration("use_sim_time"),
            }.items(),
            condition=IfCondition(LaunchConfiguration("start_lidar_self_filter")),
        ),
        Node(
            package="fast_livo",
            executable="fastlivo_mapping",
            name="fast_livo2_backend",
            output="screen",
            sigterm_timeout="30",
            sigkill_timeout="10",
            parameters=[
                LaunchConfiguration("params_file"),
                LaunchConfiguration("camera_params_file"),
                {
                    "use_sim_time": LaunchConfiguration("use_sim_time"),
                    "common.publish_tf": False,
                    "common.lid_topic": LaunchConfiguration(
                        "fast_livo_input_topic"
                    ),
                    "pcd_save.pcd_save_en": False,
                    "pcd_save.interval": -1,
                },
            ],
            remappings=[
                (
                    "/cloud_registered",
                    "/agt/odometry/backend/registered_points",
                ),
            ],
        ),
        Node(
            package="agt_odometry",
            executable="fast_livo2_adapter.py",
            name="agt_odometry_fast_livo2_adapter",
            output="screen",
            sigterm_timeout="10",
            sigkill_timeout="5",
            parameters=[
                LaunchConfiguration("adapter_params_file"),
                {"use_sim_time": LaunchConfiguration("use_sim_time")},
            ],
        ),
    ])
