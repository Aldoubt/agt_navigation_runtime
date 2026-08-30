from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, OpaqueFunction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

from agt_field_commissioning.mapping_artifacts import prepare_mapping_run


_TRUE_VALUES = {"1", "true", "yes", "on"}


def _enabled(context, name: str) -> bool:
    return LaunchConfiguration(name).perform(context).strip().lower() in _TRUE_VALUES


def _include(path: Path, arguments: dict[str, str] | None = None):
    return IncludeLaunchDescription(
        PythonLaunchDescriptionSource(str(path)),
        launch_arguments=(arguments or {}).items(),
    )


def _compose(context):
    commissioning_share = Path(get_package_share_directory("agt_field_commissioning"))
    hardware_share = Path(get_package_share_directory("agt_hardware_bringup"))
    odometry_share = Path(get_package_share_directory("agt_odometry"))
    sensor_share = Path(get_package_share_directory("agt_sensor_adapters"))

    runtime_dir = LaunchConfiguration("runtime_dir").perform(context)
    site_id = LaunchConfiguration("site_id").perform(context)
    run_id = LaunchConfiguration("run_id").perform(context)
    paths = prepare_mapping_run(runtime_dir, site_id, run_id)
    mapping_output_dir = str(paths.mapping_dir)
    use_sim_time = LaunchConfiguration("use_sim_time").perform(context)

    actions = []
    if _enabled(context, "start_hardware"):
        actions.append(
            _include(
                hardware_share / "launch" / "bunker_mid360.launch.py",
                {
                    "use_sim_time": use_sim_time,
                    "operation_mode": LaunchConfiguration("operation_mode").perform(context),
                    "can_interface": LaunchConfiguration("can_interface").perform(context),
                    "expected_can_bitrate": LaunchConfiguration("expected_can_bitrate").perform(context),
                    "run_can_preflight": LaunchConfiguration("run_can_preflight").perform(context),
                    "mid360_user_config_path": LaunchConfiguration("mid360_user_config_path").perform(context),
                    "sensor_profile": LaunchConfiguration("sensor_profile").perform(context),
                    "start_camera": "false",
                    "start_gimbal": "false",
                },
            )
        )

    fast_livo_input_topic = "/agt/sensors/lidar/custom"
    if _enabled(context, "start_lidar_self_filter"):
        fast_livo_input_topic = "/agt/sensors/lidar/custom_filtered"
        actions.append(
            _include(
                sensor_share / "launch" / "lidar_self_filter.launch.py",
                {
                    "filter_params_file": LaunchConfiguration("lidar_self_filter_params_file").perform(context),
                    "platform_profile": LaunchConfiguration("platform_profile").perform(context),
                    "geometry_source": LaunchConfiguration("lidar_self_filter_geometry_source").perform(context),
                    "use_sim_time": use_sim_time,
                },
            )
        )

    actions.append(
        Node(
            package="fast_livo",
            executable="fastlivo_mapping",
            name="fast_livo2_commissioning_mapper",
            output="screen",
            sigterm_timeout="30",
            sigkill_timeout="10",
            parameters=[
                LaunchConfiguration("params_file"),
                LaunchConfiguration("camera_params_file"),
                {
                    "use_sim_time": LaunchConfiguration("use_sim_time"),
                    "common.publish_tf": False,
                    "common.lid_topic": fast_livo_input_topic,
                    "pcd_save.pcd_save_en": True,
                    "pcd_save.interval": -1,
                    "pcd_save.incremental_voxel_en": True,
                    "pcd_save.output_directory": mapping_output_dir,
                },
            ],
            remappings=[
                (
                    "/cloud_registered",
                    "/agt/commissioning/mapping/registered_points",
                ),
            ],
        )
    )

    if _enabled(context, "start_rviz"):
        actions.append(
            Node(
                package="rviz2",
                executable="rviz2",
                name="agt_field_mapping_rviz",
                output="screen",
                arguments=[
                    "-d",
                    str(commissioning_share / "rviz" / "field_mapping.rviz"),
                ],
                parameters=[{"use_sim_time": _enabled(context, "use_sim_time")}],
            )
        )

    if _enabled(context, "start_operator_gateway"):
        actions.append(
            Node(
                package="agt_operator_gateway",
                executable="operator_delivery_gateway_node.py",
                name="agt_operator_delivery_gateway",
                output="screen",
                parameters=[
                    {
                        "use_sim_time": _enabled(context, "use_sim_time"),
                        "host": LaunchConfiguration("gateway_host").perform(context),
                        "port": int(LaunchConfiguration("gateway_port").perform(context)),
                        "write_api_enabled": _enabled(context, "gateway_write_api_enabled"),
                        "commissioning_enabled": True,
                        "commissioning_site_id": site_id,
                        "commissioning_run_id": run_id,
                        "commissioning_runtime_dir": runtime_dir,
                        "commissioning_vehicle_profile": LaunchConfiguration("platform_profile").perform(context),
                    }
                ],
            )
        )
    return actions


def generate_launch_description():
    odometry_share = Path(get_package_share_directory("agt_odometry"))
    sensor_share = Path(get_package_share_directory("agt_sensor_adapters"))
    default_mid360_config = sensor_share / "config" / "mid360_network.json"

    return LaunchDescription(
        [
            DeclareLaunchArgument("runtime_dir", default_value="runtime"),
            DeclareLaunchArgument("site_id"),
            DeclareLaunchArgument("run_id"),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument("start_hardware", default_value="true"),
            DeclareLaunchArgument("operation_mode", default_value="monitor", choices=["monitor", "control"]),
            DeclareLaunchArgument("can_interface", default_value="can0"),
            DeclareLaunchArgument("expected_can_bitrate", default_value="0"),
            DeclareLaunchArgument("run_can_preflight", default_value="true"),
            DeclareLaunchArgument("sensor_profile", default_value="hardware_check"),
            DeclareLaunchArgument("start_operator_gateway", default_value="true"),
            DeclareLaunchArgument("gateway_write_api_enabled", default_value="true"),
            DeclareLaunchArgument("gateway_host", default_value="127.0.0.1"),
            DeclareLaunchArgument("gateway_port", default_value="8765"),
            DeclareLaunchArgument("start_rviz", default_value="false"),
            DeclareLaunchArgument(
                "mid360_user_config_path",
                default_value=str(default_mid360_config),
            ),
            DeclareLaunchArgument(
                "params_file",
                default_value=str(odometry_share / "config" / "mid360_lio_only.yaml"),
            ),
            DeclareLaunchArgument(
                "camera_params_file",
                default_value=str(odometry_share / "config" / "camera_disabled_placeholder.yaml"),
            ),
            DeclareLaunchArgument("start_lidar_self_filter", default_value="true"),
            DeclareLaunchArgument(
                "lidar_self_filter_geometry_source",
                default_value="urdf",
            ),
            DeclareLaunchArgument(
                "lidar_self_filter_params_file",
                default_value=str(sensor_share / "config" / "livox_self_filter.yaml"),
            ),
            DeclareLaunchArgument(
                "platform_profile",
                default_value=str(odometry_share.parents[3] / "profiles" / "platforms" / "bunker.yaml"),
            ),
            OpaqueFunction(function=_compose),
        ]
    )
