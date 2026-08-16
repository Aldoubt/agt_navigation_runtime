from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    share = Path(get_package_share_directory("agt_chassis_mk_mini"))
    config = LaunchConfiguration("config_file")
    use_sim_time = ParameterValue(LaunchConfiguration("use_sim_time"), value_type=bool)
    steering_calibration_confirmed = ParameterValue(
        LaunchConfiguration("steering_calibration_confirmed"), value_type=bool
    )
    allow_uncalibrated_control = ParameterValue(
        LaunchConfiguration("allow_uncalibrated_control"), value_type=bool
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "config_file",
                default_value=str(share / "config" / "mk_mini.yaml"),
            ),
            DeclareLaunchArgument(
                "operation_mode",
                default_value="monitor",
                choices=["monitor", "control"],
                description="monitor receives telemetry only; control enables periodic VCU commands",
            ),
            DeclareLaunchArgument("can_interface", default_value="can0"),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument("start_adapter", default_value="true"),
            DeclareLaunchArgument("start_backend", default_value="true"),
            DeclareLaunchArgument(
                "steering_calibration_confirmed", default_value="false"
            ),
            DeclareLaunchArgument(
                "allow_uncalibrated_control", default_value="false"
            ),
            Node(
                package="agt_chassis_mk_mini",
                executable="mk_mini_adapter.py",
                name="agt_mk_mini_adapter",
                output="screen",
                parameters=[config, {"use_sim_time": use_sim_time}],
                condition=IfCondition(LaunchConfiguration("start_adapter")),
            ),
            Node(
                package="agt_chassis_mk_mini",
                executable="mk_mini_can_backend.py",
                name="agt_mk_mini_can_backend",
                output="screen",
                parameters=[
                    config,
                    {
                        "operation_mode": LaunchConfiguration("operation_mode"),
                        "can_interface": LaunchConfiguration("can_interface"),
                        "steering_calibration_confirmed": steering_calibration_confirmed,
                        "allow_uncalibrated_control": allow_uncalibrated_control,
                        "use_sim_time": use_sim_time,
                    },
                ],
                condition=IfCondition(LaunchConfiguration("start_backend")),
            ),
        ]
    )
