from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    bringup_share = Path(get_package_share_directory("agt_bringup"))
    experiment_share = Path(get_package_share_directory("agt_experiment_manager"))

    use_sim_time = LaunchConfiguration("use_sim_time")
    runtime_dir = LaunchConfiguration("runtime_dir")

    return LaunchDescription(
        [
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument("can_interface", default_value="can0"),
            DeclareLaunchArgument("start_gnss", default_value="false"),
            DeclareLaunchArgument("gnss_input_topic", default_value=""),
            DeclareLaunchArgument("runtime_dir", default_value="runtime"),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(bringup_share / "launch" / "system.launch.py")
                ),
                launch_arguments={
                    "platform": "bunker",
                    "use_sim_time": use_sim_time,
                    "start_sensor": "true",
                    "start_sensor_monitor": "true",
                    "start_gnss": LaunchConfiguration("start_gnss"),
                    "gnss_input_topic": LaunchConfiguration("gnss_input_topic"),
                    "start_odometry": "true",
                    "start_perception": "false",
                    "start_localization": "false",
                    "start_navigation": "false",
                    "start_chassis": "true",
                    "chassis_operation_mode": "monitor",
                    "can_interface": LaunchConfiguration("can_interface"),
                }.items(),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(
                        experiment_share
                        / "launch"
                        / "experiment_manager.launch.py"
                    )
                ),
                launch_arguments={
                    "runtime_dir": runtime_dir,
                }.items(),
            ),
        ]
    )
