from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, OpaqueFunction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

from agt_hardware_bringup.socketcan_preflight import run_preflight


def _as_bool(value: str) -> bool:
    return value.strip().lower() in {"1", "true", "yes", "on"}


def _include(path: Path, arguments: dict[str, str] | None = None):
    return IncludeLaunchDescription(
        PythonLaunchDescriptionSource(str(path)),
        launch_arguments=(arguments or {}).items(),
    )


def _compose(context):
    bringup_share = Path(get_package_share_directory("agt_hardware_bringup"))
    chassis_share = Path(get_package_share_directory("agt_chassis_bunker"))
    inspection_share = Path(get_package_share_directory("agt_inspection"))
    sensor_adapter_share = Path(get_package_share_directory("agt_sensor_adapters"))
    sensor_monitor_share = Path(get_package_share_directory("agt_sensor_monitor"))

    use_sim_time = LaunchConfiguration("use_sim_time").perform(context)
    operation_mode = LaunchConfiguration("operation_mode").perform(context)
    can_interface = LaunchConfiguration("can_interface").perform(context)
    expected_can_bitrate = int(LaunchConfiguration("expected_can_bitrate").perform(context))

    if _as_bool(LaunchConfiguration("run_can_preflight").perform(context)):
        report = run_preflight(can_interface, expected_can_bitrate)
        if not report["ready"]:
            blockers = ", ".join(report.get("blockers", [])) or "unknown"
            raise RuntimeError(f"SocketCAN preflight failed for {can_interface}: {blockers}")

    sensor_profile = LaunchConfiguration("sensor_profile").perform(context)
    profile_file = bringup_share / "config" / f"sensor_monitor.{sensor_profile}.yaml"
    if not profile_file.is_file():
        raise RuntimeError(f"sensor monitor profile does not exist: {profile_file}")

    actions = [
        _include(
            chassis_share / "launch" / "bunker.launch.py",
            {
                "use_sim_time": use_sim_time,
                "operation_mode": operation_mode,
                "can_interface": can_interface,
                "start_safety": LaunchConfiguration("start_safety").perform(context),
                "start_auto_permit": LaunchConfiguration("start_auto_permit").perform(context),
                "auto_permit_switch": LaunchConfiguration("auto_permit_switch").perform(context),
                "auto_permit_enabled_value": LaunchConfiguration("auto_permit_enabled_value").perform(context),
                "auto_permit_status_timeout": LaunchConfiguration("auto_permit_status_timeout").perform(context),
            },
        ),
        _include(
            sensor_adapter_share / "launch" / "mid360.launch.py",
            {
                "use_sim_time": use_sim_time,
                "user_config_path": LaunchConfiguration("mid360_user_config_path").perform(context),
            },
        ),
        _include(
            sensor_monitor_share / "launch" / "sensor_monitor.launch.py",
            {
                "use_sim_time": use_sim_time,
                "params_file": str(profile_file),
            },
        ),
    ]

    start_inspection = _as_bool(LaunchConfiguration("start_inspection").perform(context))
    start_camera = _as_bool(LaunchConfiguration("start_camera").perform(context))
    start_gimbal = _as_bool(LaunchConfiguration("start_gimbal").perform(context))
    if start_inspection and (start_camera or start_gimbal):
        raise RuntimeError(
            "start_inspection cannot be combined with start_camera/start_gimbal"
        )

    for enabled_arg, path_arg, label in (
        ("start_camera", "camera_launch_file", "camera"),
        ("start_gimbal", "gimbal_launch_file", "gimbal"),
    ):
        if not _as_bool(LaunchConfiguration(enabled_arg).perform(context)):
            continue
        launch_path_value = LaunchConfiguration(path_arg).perform(context).strip()
        if not launch_path_value:
            raise RuntimeError(f"{label} enabled but {path_arg} is empty")
        launch_path = Path(launch_path_value).expanduser()
        if not launch_path.is_file():
            raise RuntimeError(f"{label} launch file does not exist: {launch_path}")
        actions.append(_include(launch_path, {"use_sim_time": use_sim_time}))

    if start_inspection:
        actions.append(
            _include(
                inspection_share / "launch" / "camera_gimbal_inspection.launch.py",
                {
                    "camera_device_path": LaunchConfiguration(
                        "inspection_camera_device_path"
                    ).perform(context),
                    "camera_gimbal_port": LaunchConfiguration(
                        "inspection_camera_gimbal_port"
                    ).perform(context),
                    "camera_width": LaunchConfiguration(
                        "inspection_camera_width"
                    ).perform(context),
                    "camera_height": LaunchConfiguration(
                        "inspection_camera_height"
                    ).perform(context),
                    "camera_fps": LaunchConfiguration("inspection_camera_fps").perform(
                        context
                    ),
                    "capture_output_root": LaunchConfiguration(
                        "inspection_capture_output_root"
                    ).perform(context),
                    "runtime_maps_root": LaunchConfiguration(
                        "inspection_runtime_maps_root"
                    ).perform(context),
                    "evidence_root": LaunchConfiguration(
                        "inspection_evidence_root"
                    ).perform(context),
                    "camera_calibration_id": LaunchConfiguration(
                        "inspection_camera_calibration_id"
                    ).perform(context),
                    "camera_calibration_sha256": LaunchConfiguration(
                        "inspection_camera_calibration_sha256"
                    ).perform(context),
                },
            )
        )

    return actions


def generate_launch_description():
    sensor_adapter_share = Path(get_package_share_directory("agt_sensor_adapters"))
    default_mid360_config = sensor_adapter_share / "config" / "mid360_network.json"

    return LaunchDescription(
        [
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument("operation_mode", default_value="monitor", choices=["monitor", "control"]),
            DeclareLaunchArgument("can_interface", default_value="can0"),
            DeclareLaunchArgument("expected_can_bitrate", default_value="0"),
            DeclareLaunchArgument("run_can_preflight", default_value="true"),
            DeclareLaunchArgument("start_safety", default_value="true"),
            DeclareLaunchArgument("start_auto_permit", default_value="false"),
            DeclareLaunchArgument("auto_permit_switch", default_value=""),
            DeclareLaunchArgument("auto_permit_enabled_value", default_value="-1"),
            DeclareLaunchArgument("auto_permit_status_timeout", default_value="0.5"),
            DeclareLaunchArgument(
                "mid360_user_config_path",
                default_value=str(default_mid360_config),
            ),
            DeclareLaunchArgument(
                "sensor_profile",
                default_value="hardware_check",
                choices=["hardware_check", "navigation"],
                description="sensor_monitor.hardware_check.yaml or sensor_monitor.navigation.yaml",
            ),
            DeclareLaunchArgument("start_camera", default_value="false"),
            DeclareLaunchArgument("camera_launch_file", default_value=""),
            DeclareLaunchArgument("start_gimbal", default_value="false"),
            DeclareLaunchArgument("gimbal_launch_file", default_value=""),
            DeclareLaunchArgument("start_inspection", default_value="false"),
            DeclareLaunchArgument(
                "inspection_camera_device_path", default_value="/dev/video0"
            ),
            DeclareLaunchArgument(
                "inspection_camera_gimbal_port", default_value="/dev/ttyUSB0"
            ),
            DeclareLaunchArgument("inspection_camera_width", default_value="1920"),
            DeclareLaunchArgument("inspection_camera_height", default_value="1080"),
            DeclareLaunchArgument("inspection_camera_fps", default_value="30.0"),
            DeclareLaunchArgument(
                "inspection_capture_output_root",
                default_value="runtime/camera_gimbal_capture",
            ),
            DeclareLaunchArgument(
                "inspection_runtime_maps_root", default_value="runtime/maps"
            ),
            DeclareLaunchArgument(
                "inspection_evidence_root", default_value="runtime/inspections"
            ),
            DeclareLaunchArgument(
                "inspection_camera_calibration_id", default_value=""
            ),
            DeclareLaunchArgument(
                "inspection_camera_calibration_sha256", default_value=""
            ),
            OpaqueFunction(function=_compose),
        ]
    )