from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    OpaqueFunction,
    SetLaunchConfiguration,
)
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration


_TRUE_VALUES = {"true", "1", "yes", "on"}


def _enabled(context, name: str) -> bool:
    return LaunchConfiguration(name).perform(context).strip().lower() in _TRUE_VALUES


def _prepare_mapping_output(context):
    map_id = LaunchConfiguration("map_id").perform(context).strip()
    run_id = LaunchConfiguration("run_id").perform(context).strip()

    if not map_id:
        raise RuntimeError("map_id must not be empty")
    if not run_id:
        raise RuntimeError("run_id must not be empty")

    if _enabled(context, "start_gnss"):
        input_topic = LaunchConfiguration("gnss_input_topic").perform(context).strip()
        if not input_topic.startswith("/"):
            raise RuntimeError("start_gnss requires an absolute gnss_input_topic")
        if input_topic == "/agt/sensors/gnss/fix":
            raise RuntimeError("gnss_input_topic must not equal canonical GNSS output")

    runtime_dir = Path(LaunchConfiguration("runtime_dir").perform(context)).expanduser()
    mapping_output_dir = runtime_dir / "commissioning" / map_id / run_id / "mapping"

    if mapping_output_dir.exists() and not mapping_output_dir.is_dir():
        raise RuntimeError(
            f"commissioning mapping output path is not a directory: {mapping_output_dir}"
        )

    existing = (
        sorted(path.name for path in mapping_output_dir.iterdir())
        if mapping_output_dir.is_dir()
        else []
    )
    if existing:
        raise RuntimeError(
            "refusing to reuse populated commissioning mapping directory: "
            f"{mapping_output_dir} ({', '.join(existing[:8])})"
        )

    return [
        SetLaunchConfiguration("mapping_output_dir", str(mapping_output_dir)),
    ]


def generate_launch_description():
    bringup_share = Path(get_package_share_directory("agt_bringup"))

    return LaunchDescription(
        [
            DeclareLaunchArgument("platform", default_value="bunker"),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument("runtime_dir", default_value="runtime"),
            DeclareLaunchArgument("map_id"),
            DeclareLaunchArgument("run_id"),
            DeclareLaunchArgument("start_gnss", default_value="false"),
            DeclareLaunchArgument("gnss_input_topic", default_value=""),
            DeclareLaunchArgument("start_chassis", default_value="true"),
            DeclareLaunchArgument("chassis_operation_mode", default_value="monitor"),
            DeclareLaunchArgument("can_interface", default_value="can0"),
            OpaqueFunction(function=_prepare_mapping_output),
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
                    "start_perception": "false",
                    "start_localization": "false",
                    "start_navigation": "false",
                    "start_chassis": LaunchConfiguration("start_chassis"),
                    "chassis_operation_mode": LaunchConfiguration(
                        "chassis_operation_mode"
                    ),
                    "can_interface": LaunchConfiguration("can_interface"),
                    "mapping_save_pcd": "true",
                    "mapping_pcd_save_interval": "-1",
                    "mapping_pcd_output_dir": LaunchConfiguration(
                        "mapping_output_dir"
                    ),
                }.items(),
            ),
        ]
    )
