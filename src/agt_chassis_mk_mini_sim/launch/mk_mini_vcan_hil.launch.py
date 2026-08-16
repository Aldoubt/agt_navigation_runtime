from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    sim_share = Path(get_package_share_directory("agt_chassis_mk_mini_sim"))
    real_share = Path(get_package_share_directory("agt_chassis_mk_mini"))

    can_interface = LaunchConfiguration("can_interface")
    operation_mode = LaunchConfiguration("operation_mode")
    use_sim_time = LaunchConfiguration("use_sim_time")
    steering_calibration_confirmed = LaunchConfiguration(
        "steering_calibration_confirmed"
    )
    allow_uncalibrated_control = LaunchConfiguration(
        "allow_uncalibrated_control"
    )
    drop_feedback = LaunchConfiguration("drop_feedback")
    corrupt_bcc = LaunchConfiguration("corrupt_bcc")
    sim_config = LaunchConfiguration("sim_config")

    real_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(str(real_share / "launch" / "mk_mini.launch.py")),
        launch_arguments={
            "operation_mode": operation_mode,
            "can_interface": can_interface,
            "use_sim_time": use_sim_time,
            "start_adapter": LaunchConfiguration("start_adapter"),
            "start_backend": LaunchConfiguration("start_backend"),
            "steering_calibration_confirmed": steering_calibration_confirmed,
            "allow_uncalibrated_control": allow_uncalibrated_control,
        }.items(),
    )

    simulator = Node(
        package="agt_chassis_mk_mini_sim",
        executable="mk_mini_vcu_sim.py",
        name="agt_mk_mini_vcu_sim",
        output="screen",
        parameters=[
            sim_config,
            {
                "can_interface": can_interface,
                "use_sim_time": ParameterValue(use_sim_time, value_type=bool),
                "drop_feedback": ParameterValue(drop_feedback, value_type=bool),
                "corrupt_bcc": ParameterValue(corrupt_bcc, value_type=bool),
            },
        ],
        condition=IfCondition(LaunchConfiguration("start_simulator")),
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument("can_interface", default_value="vcan0"),
            DeclareLaunchArgument(
                "operation_mode",
                default_value="monitor",
                choices=["monitor", "control"],
            ),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument("start_adapter", default_value="true"),
            DeclareLaunchArgument("start_backend", default_value="true"),
            DeclareLaunchArgument("start_simulator", default_value="true"),
            DeclareLaunchArgument("steering_calibration_confirmed", default_value="false"),
            DeclareLaunchArgument("allow_uncalibrated_control", default_value="false"),
            DeclareLaunchArgument("drop_feedback", default_value="false"),
            DeclareLaunchArgument("corrupt_bcc", default_value="false"),
            DeclareLaunchArgument(
                "sim_config",
                default_value=str(sim_share / "config" / "vcu_sim.yaml"),
            ),
            real_launch,
            simulator,
        ]
    )
