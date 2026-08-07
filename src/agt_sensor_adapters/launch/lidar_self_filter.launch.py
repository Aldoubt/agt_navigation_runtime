from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    package_share = Path(get_package_share_directory("agt_sensor_adapters"))
    default_profile = package_share.parents[3] / "profiles" / "platforms" / "bunker.yaml"
    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "filter_params_file",
                default_value=str(package_share / "config" / "livox_self_filter.yaml"),
            ),
            DeclareLaunchArgument("input_topic", default_value="/agt/sensors/lidar/custom"),
            DeclareLaunchArgument(
                "output_topic", default_value="/agt/sensors/lidar/custom_filtered"
            ),
            DeclareLaunchArgument("platform_profile", default_value=str(default_profile)),
            DeclareLaunchArgument("geometry_source", default_value="urdf"),
            DeclareLaunchArgument("urdf_reference_frame", default_value="base_link"),
            DeclareLaunchArgument("robot_description_topic", default_value="/robot_description"),
            DeclareLaunchArgument("enabled", default_value="true"),
            DeclareLaunchArgument("transform_timeout_sec", default_value="0.10"),
            DeclareLaunchArgument("zero_point_epsilon", default_value="0.000001"),
            DeclareLaunchArgument("fail_open_on_tf_error", default_value="false"),
            DeclareLaunchArgument("publish_removed_points", default_value="false"),
            DeclareLaunchArgument(
                "removed_points_topic",
                default_value="/agt/sensors/lidar/self_filter/removed_points",
            ),
            DeclareLaunchArgument("publish_filter_geometry", default_value="true"),
            DeclareLaunchArgument(
                "filter_geometry_topic", default_value="/agt/sensors/lidar/self_filter/geometry"
            ),
            DeclareLaunchArgument("diagnostics_topic", default_value="/diagnostics"),
            DeclareLaunchArgument("queue_depth", default_value="200000"),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            Node(
                package="agt_sensor_adapters",
                executable="livox_custom_self_filter",
                name="agt_livox_self_filter",
                output="screen",
                parameters=[
                    LaunchConfiguration("filter_params_file"),
                    {
                        "input_topic": LaunchConfiguration("input_topic"),
                        "output_topic": LaunchConfiguration("output_topic"),
                        "platform_profile": LaunchConfiguration("platform_profile"),
                        "geometry_source": LaunchConfiguration("geometry_source"),
                        "urdf_reference_frame": LaunchConfiguration("urdf_reference_frame"),
                        "robot_description_topic": LaunchConfiguration("robot_description_topic"),
                        "enabled": ParameterValue(
                            LaunchConfiguration("enabled"), value_type=bool
                        ),
                        "transform_timeout_sec": ParameterValue(
                            LaunchConfiguration("transform_timeout_sec"), value_type=float
                        ),
                        "zero_point_epsilon": ParameterValue(
                            LaunchConfiguration("zero_point_epsilon"), value_type=float
                        ),
                        "fail_open_on_tf_error": ParameterValue(
                            LaunchConfiguration("fail_open_on_tf_error"), value_type=bool
                        ),
                        "publish_removed_points": ParameterValue(
                            LaunchConfiguration("publish_removed_points"), value_type=bool
                        ),
                        "removed_points_topic": LaunchConfiguration("removed_points_topic"),
                        "publish_filter_geometry": ParameterValue(
                            LaunchConfiguration("publish_filter_geometry"), value_type=bool
                        ),
                        "filter_geometry_topic": LaunchConfiguration("filter_geometry_topic"),
                        "diagnostics_topic": LaunchConfiguration("diagnostics_topic"),
                        "queue_depth": ParameterValue(
                            LaunchConfiguration("queue_depth"), value_type=int
                        ),
                        "use_sim_time": ParameterValue(
                            LaunchConfiguration("use_sim_time"), value_type=bool
                        ),
                    },
                ],
            ),
        ]
    )
