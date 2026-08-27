from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, OpaqueFunction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def _enabled(context, name: str) -> bool:
    return LaunchConfiguration(name).perform(context).strip().lower() in {
        "true",
        "1",
        "yes",
        "on",
    }


def _validate(context):
    platform = LaunchConfiguration("platform").perform(context)
    if platform != "bunker":
        raise RuntimeError(f"P0 supports only platform:=bunker, got {platform!r}")

    start_localization = _enabled(context, "start_localization")
    start_navigation = _enabled(context, "start_navigation")
    if start_navigation and not start_localization:
        raise RuntimeError("navigation requires start_localization:=true")

    if _enabled(context, "start_gnss"):
        input_topic = LaunchConfiguration("gnss_input_topic").perform(context).strip()
        if not input_topic.startswith("/"):
            raise RuntimeError("start_gnss requires an absolute gnss_input_topic")
        if input_topic == "/agt/sensors/gnss/fix":
            raise RuntimeError("gnss_input_topic must not equal canonical GNSS output")

    required_files = []
    if start_localization:
        required_files.extend(["global_map_pcd", "global_map_processing_record"])
    if start_navigation:
        required_files.append("navigation_map")

    for name in required_files:
        path = Path(LaunchConfiguration(name).perform(context)).expanduser()
        if not path.is_file():
            raise RuntimeError(f"{name} must be a file: {path}")
    return []


def generate_launch_description():
    description_share = Path(get_package_share_directory("agt_description"))
    sensor_share = Path(get_package_share_directory("agt_sensor_adapters"))
    monitor_share = Path(get_package_share_directory("agt_sensor_monitor"))
    mapping_share = Path(get_package_share_directory("agt_mapping"))
    perception_share = Path(get_package_share_directory("agt_perception"))
    localization_share = Path(get_package_share_directory("agt_localization"))
    navigation_share = Path(get_package_share_directory("agt_navigation"))
    chassis_share = Path(get_package_share_directory("agt_chassis"))

    use_sim_time = LaunchConfiguration("use_sim_time")

    return LaunchDescription(
        [
            DeclareLaunchArgument("platform", default_value="bunker"),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument("start_sensor", default_value="true"),
            DeclareLaunchArgument("start_sensor_monitor", default_value="true"),
            DeclareLaunchArgument("start_gnss", default_value="false"),
            DeclareLaunchArgument("gnss_input_topic", default_value=""),
            DeclareLaunchArgument("start_odometry", default_value="true"),
            DeclareLaunchArgument("start_perception", default_value="true"),
            DeclareLaunchArgument("start_localization", default_value="false"),
            DeclareLaunchArgument("start_navigation", default_value="false"),
            DeclareLaunchArgument("start_chassis", default_value="false"),
            DeclareLaunchArgument("chassis_operation_mode", default_value="control"),
            DeclareLaunchArgument("can_interface", default_value="can0"),
            DeclareLaunchArgument("navigation_map", default_value=""),
            DeclareLaunchArgument("global_map_pcd", default_value=""),
            DeclareLaunchArgument("global_map_processing_record", default_value=""),
            DeclareLaunchArgument("map_id", default_value=""),
            DeclareLaunchArgument("map_hash", default_value=""),
            DeclareLaunchArgument("localization_backend", default_value="ndt"),
            DeclareLaunchArgument("localization_status_timeout", default_value="10.0"),
            OpaqueFunction(function=_validate),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(description_share / "launch" / "bunker_description.launch.py")
                ),
                launch_arguments={"use_sim_time": use_sim_time}.items(),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(sensor_share / "launch" / "mid360.launch.py")
                ),
                launch_arguments={"use_sim_time": use_sim_time}.items(),
                condition=IfCondition(LaunchConfiguration("start_sensor")),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(sensor_share / "launch" / "gnss_navsat.launch.py")
                ),
                launch_arguments={
                    "input_topic": LaunchConfiguration("gnss_input_topic"),
                    "output_topic": "/agt/sensors/gnss/fix",
                    "frame_id": "gps_link",
                    "use_sim_time": use_sim_time,
                }.items(),
                condition=IfCondition(LaunchConfiguration("start_gnss")),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(monitor_share / "launch" / "sensor_monitor.launch.py")
                ),
                launch_arguments={
                    "use_sim_time": use_sim_time,
                    "gnss_enabled": LaunchConfiguration("start_gnss"),
                }.items(),
                condition=IfCondition(LaunchConfiguration("start_sensor_monitor")),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(mapping_share / "launch" / "fast_livo2_mapping.launch.py")
                ),
                launch_arguments={
                    "use_sim_time": use_sim_time,
                    "save_pcd": "false",
                }.items(),
                condition=IfCondition(LaunchConfiguration("start_odometry")),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(perception_share / "launch" / "local_obstacles.launch.py")
                ),
                launch_arguments={"use_sim_time": use_sim_time}.items(),
                condition=IfCondition(LaunchConfiguration("start_perception")),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(localization_share / "launch" / "relocalization.launch.py")
                ),
                launch_arguments={
                    "global_map_pcd": LaunchConfiguration("global_map_pcd"),
                    "global_map_processing_record": LaunchConfiguration(
                        "global_map_processing_record"
                    ),
                    "map_id": LaunchConfiguration("map_id"),
                    "map_hash": LaunchConfiguration("map_hash"),
                    "backend": LaunchConfiguration("localization_backend"),
                    "use_sim_time": use_sim_time,
                }.items(),
                condition=IfCondition(LaunchConfiguration("start_localization")),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(navigation_share / "launch" / "navigation.launch.py")
                ),
                launch_arguments={
                    "map": LaunchConfiguration("navigation_map"),
                    "map_id": LaunchConfiguration("map_id"),
                    "current_localization_pcd_sha256": LaunchConfiguration("map_hash"),
                    "localization_status_timeout": LaunchConfiguration(
                        "localization_status_timeout"
                    ),
                    "use_sim_time": use_sim_time,
                    "autostart": "false",
                }.items(),
                condition=IfCondition(LaunchConfiguration("start_navigation")),
            ),
            Node(
                package="agt_bringup",
                executable="localization_navigation_gate.py",
                name="agt_localization_navigation_gate",
                output="screen",
                parameters=[
                    {
                        "localization_status_timeout": ParameterValue(
                            LaunchConfiguration("localization_status_timeout"),
                            value_type=float,
                        )
                    }
                ],
                condition=IfCondition(LaunchConfiguration("start_navigation")),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(chassis_share / "launch" / "bunker.launch.py")
                ),
                launch_arguments={
                    "use_sim_time": use_sim_time,
                    "operation_mode": LaunchConfiguration("chassis_operation_mode"),
                    "can_interface": LaunchConfiguration("can_interface"),
                    "start_driver": "true",
                    "start_safety": "true",
                    "publish_driver_odom_tf": "false",
                }.items(),
                condition=IfCondition(LaunchConfiguration("start_chassis")),
            ),
        ]
    )
