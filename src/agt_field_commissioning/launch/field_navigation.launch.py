from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, OpaqueFunction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

from agt_field_commissioning.frozen_site import resolve_active_frozen_site


_TRUE_VALUES = {"1", "true", "yes", "on"}


def _enabled(context, name: str) -> bool:
    return LaunchConfiguration(name).perform(context).strip().lower() in _TRUE_VALUES


def _include(path: Path, arguments: dict[str, str] | None = None, *, condition=None):
    return IncludeLaunchDescription(
        PythonLaunchDescriptionSource(str(path)),
        launch_arguments=(arguments or {}).items(),
        condition=condition,
    )


def _compose(context):
    commissioning_share = Path(get_package_share_directory("agt_field_commissioning"))
    contract_share = Path(get_package_share_directory("agt_runtime_contracts"))
    hardware_share = Path(get_package_share_directory("agt_hardware_bringup"))
    odometry_share = Path(get_package_share_directory("agt_odometry"))
    localization_share = Path(get_package_share_directory("agt_localization"))
    site_navigation_share = Path(get_package_share_directory("agt_site_navigation"))
    navigation_share = Path(get_package_share_directory("agt_navigation"))
    safety_share = Path(get_package_share_directory("agt_safety"))
    system_manager_share = Path(get_package_share_directory("agt_system_manager"))

    sites_root = LaunchConfiguration("sites_root").perform(context)
    state_root = LaunchConfiguration("state_root").perform(context)
    site_vehicle_profile = LaunchConfiguration("site_vehicle_profile").perform(context)
    site_id = LaunchConfiguration("site_id").perform(context)
    site_revision = LaunchConfiguration("site_revision").perform(context)
    use_sim_time = LaunchConfiguration("use_sim_time").perform(context)

    assets = resolve_active_frozen_site(
        sites_root=sites_root,
        state_root=state_root,
        site_id=site_id,
        site_revision=site_revision,
        vehicle_profile=site_vehicle_profile,
        vehicle_schema=contract_share / "schemas" / "vehicle_profile.schema.json",
        site_schema=contract_share / "schemas" / "site_package.schema.json",
    )

    actions = []

    if _enabled(context, "start_site_runtime"):
        actions.append(
            Node(
                package="agt_site_runtime",
                executable="site_runtime_node.py",
                name="agt_site_runtime",
                output="screen",
                parameters=[
                    {
                        "sites_root": sites_root,
                        "state_root": state_root,
                        "vehicle_profile": site_vehicle_profile,
                    }
                ],
            )
        )

    actions.extend(
        [
            _include(
                site_navigation_share / "launch" / "site_navigation_binding.launch.py",
                {
                    "sites_root": sites_root,
                    "site_vehicle_profile": site_vehicle_profile,
                },
            ),
            _include(
                site_navigation_share / "launch" / "navigation_runtime_status.launch.py"
            ),
        ]
    )

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
                    "sensor_profile": "navigation",
                    "start_safety": "false",
                    "start_auto_permit": LaunchConfiguration("start_auto_permit").perform(context),
                    "auto_permit_switch": LaunchConfiguration("auto_permit_switch").perform(context),
                    "auto_permit_enabled_value": LaunchConfiguration("auto_permit_enabled_value").perform(context),
                    "auto_permit_status_timeout": LaunchConfiguration("auto_permit_status_timeout").perform(context),
                    "start_camera": "false",
                    "start_gimbal": "false",
                    "start_inspection": LaunchConfiguration("start_inspection").perform(context),
                    "inspection_camera_device_path": LaunchConfiguration("inspection_camera_device_path").perform(context),
                    "inspection_camera_gimbal_port": LaunchConfiguration("inspection_camera_gimbal_port").perform(context),
                    "inspection_camera_width": LaunchConfiguration("inspection_camera_width").perform(context),
                    "inspection_camera_height": LaunchConfiguration("inspection_camera_height").perform(context),
                    "inspection_camera_fps": LaunchConfiguration("inspection_camera_fps").perform(context),
                    "inspection_capture_output_root": LaunchConfiguration("inspection_capture_output_root").perform(context),
                    "inspection_runtime_maps_root": LaunchConfiguration("inspection_runtime_maps_root").perform(context),
                    "inspection_evidence_root": LaunchConfiguration("inspection_evidence_root").perform(context),
                    "inspection_camera_calibration_id": LaunchConfiguration("inspection_camera_calibration_id").perform(context),
                    "inspection_camera_calibration_sha256": LaunchConfiguration("inspection_camera_calibration_sha256").perform(context),
                },
            )
        )

    actions.extend(
        [
            _include(
                odometry_share / "launch" / "fast_livo2_odometry.launch.py",
                {"use_sim_time": use_sim_time},
            ),
            _include(
                localization_share / "launch" / "relocalization.launch.py",
                {
                    "use_sim_time": use_sim_time,
                    "global_map_pcd": str(assets.localization_pcd),
                    "global_map_processing_record": (
                        str(assets.processing_record) if assets.processing_record else ""
                    ),
                    "map_id": assets.site_id,
                    "map_hash": assets.localization_pcd_sha256,
                    "backend": LaunchConfiguration("localization_backend").perform(context),
                },
            ),
            _include(
                safety_share / "launch" / "safety.launch.py",
                {
                    "use_sim_time": use_sim_time,
                    "require_auto_permit": "true",
                    "auto_permit_timeout": LaunchConfiguration("auto_permit_status_timeout").perform(context),
                },
            ),
            _include(
                navigation_share / "launch" / "navigation.launch.py",
                {
                    "params_file": LaunchConfiguration("nav2_params_file").perform(context),
                    "map": str(assets.navigation_yaml),
                    "runtime_dir": LaunchConfiguration("runtime_dir").perform(context),
                    "tasks_root": LaunchConfiguration("tasks_root").perform(context),
                    "sites_root": sites_root,
                    "site_vehicle_profile": site_vehicle_profile,
                    "map_id": assets.site_id,
                    "map_version_id": assets.site_revision,
                    "current_map_yaml_sha256": assets.navigation_yaml_sha256,
                    "current_map_image_sha256": assets.navigation_image_sha256,
                    "current_localization_pcd_sha256": assets.localization_pcd_sha256,
                    "execution_vehicle_profile": site_vehicle_profile,
                    "use_sim_time": use_sim_time,
                    "autostart": "true",
                    "enable_rviz_goal_bridge": LaunchConfiguration("enable_rviz_goal_bridge").perform(context),
                },
            ),
            _include(
                system_manager_share / "launch" / "system_manager.launch.py",
                {"use_sim_time": use_sim_time},
            ),
        ]
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
                        "commissioning_enabled": False,
                        "task_authoring_enabled": True,
                        "task_authoring_site_id": assets.site_id,
                        "task_authoring_site_revision": assets.site_revision,
                        "task_authoring_navigation_yaml": str(assets.navigation_yaml),
                        "task_authoring_localization_pcd": str(assets.localization_pcd),
                        "run_control_enabled": True,
                        "run_lidar_component_id": LaunchConfiguration("run_lidar_component_id").perform(context),
                        "run_camera_gimbal_component_id": LaunchConfiguration("run_camera_gimbal_component_id").perform(context),
                        "run_auto_permit_topic": "/agt/chassis/auto_permit",
                        "run_auto_permit_freshness_s": float(LaunchConfiguration("run_auto_permit_freshness_s").perform(context)),
                    }
                ],
            )
        )

    actions.append(
        Node(
            package="rviz2",
            executable="rviz2",
            name="agt_field_commissioning_rviz",
            output="screen",
            arguments=[
                "-d",
                str(commissioning_share / "rviz" / "field_commissioning.rviz"),
            ],
            condition=IfCondition(LaunchConfiguration("start_rviz")),
        )
    )
    return actions


def generate_launch_description():
    sensor_share = Path(get_package_share_directory("agt_sensor_adapters"))
    navigation_share = Path(get_package_share_directory("agt_navigation"))
    default_mid360_config = sensor_share / "config" / "mid360_network.json"
    default_nav2_params = navigation_share / "config" / "nav2_bunker.yaml"

    return LaunchDescription(
        [
            DeclareLaunchArgument("site_id"),
            DeclareLaunchArgument("site_revision"),
            DeclareLaunchArgument("sites_root", default_value="/opt/agt/sites"),
            DeclareLaunchArgument(
                "state_root", default_value="~/.local/state/agt_navigation_runtime"
            ),
            DeclareLaunchArgument(
                "site_vehicle_profile", default_value="/opt/agt/profiles/bunker.yaml"
            ),
            DeclareLaunchArgument("runtime_dir", default_value="runtime"),
            DeclareLaunchArgument("tasks_root", default_value=""),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument("start_site_runtime", default_value="true"),
            DeclareLaunchArgument("start_hardware", default_value="true"),
            DeclareLaunchArgument("operation_mode", default_value="control", choices=["monitor", "control"]),
            DeclareLaunchArgument("can_interface", default_value="can0"),
            DeclareLaunchArgument("expected_can_bitrate", default_value="0"),
            DeclareLaunchArgument("run_can_preflight", default_value="true"),
            DeclareLaunchArgument("start_auto_permit", default_value="false"),
            DeclareLaunchArgument("auto_permit_switch", default_value=""),
            DeclareLaunchArgument("auto_permit_enabled_value", default_value="-1"),
            DeclareLaunchArgument("auto_permit_status_timeout", default_value="0.5"),
            DeclareLaunchArgument("run_auto_permit_freshness_s", default_value="0.75"),
            DeclareLaunchArgument("start_inspection", default_value="true"),
            DeclareLaunchArgument("inspection_camera_device_path", default_value="/dev/video0"),
            DeclareLaunchArgument("inspection_camera_gimbal_port", default_value="/dev/ttyUSB0"),
            DeclareLaunchArgument("inspection_camera_width", default_value="1920"),
            DeclareLaunchArgument("inspection_camera_height", default_value="1080"),
            DeclareLaunchArgument("inspection_camera_fps", default_value="30.0"),
            DeclareLaunchArgument("inspection_capture_output_root", default_value="runtime/camera_gimbal_capture"),
            DeclareLaunchArgument("inspection_runtime_maps_root", default_value="runtime/maps"),
            DeclareLaunchArgument("inspection_evidence_root", default_value="runtime/inspections"),
            DeclareLaunchArgument("inspection_camera_calibration_id", default_value=""),
            DeclareLaunchArgument("inspection_camera_calibration_sha256", default_value=""),
            DeclareLaunchArgument("start_operator_gateway", default_value="true"),
            DeclareLaunchArgument("gateway_write_api_enabled", default_value="true"),
            DeclareLaunchArgument("gateway_host", default_value="0.0.0.0"),
            DeclareLaunchArgument("gateway_port", default_value="8765"),
            DeclareLaunchArgument("run_lidar_component_id", default_value="lidar"),
            DeclareLaunchArgument("run_camera_gimbal_component_id", default_value="camera_gimbal"),
            DeclareLaunchArgument(
                "mid360_user_config_path", default_value=str(default_mid360_config)
            ),
            DeclareLaunchArgument("localization_backend", default_value="ndt"),
            DeclareLaunchArgument(
                "nav2_params_file", default_value=str(default_nav2_params)
            ),
            DeclareLaunchArgument("enable_rviz_goal_bridge", default_value="false"),
            DeclareLaunchArgument("start_rviz", default_value="true"),
            OpaqueFunction(function=_compose),
        ]
    )
