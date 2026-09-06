from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import Command, LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import PathJoinSubstitution


def generate_launch_description():
    package_share = FindPackageShare("agt_description")
    model = PathJoinSubstitution([package_share, "urdf", "tracked_chassis.urdf.xacro"])
    default_calibration = PathJoinSubstitution(
        [package_share, "config", "cad_alignment.initial_guess.yaml"]
    )
    calibration_file = LaunchConfiguration("calibration_file")
    robot_description = ParameterValue(
        Command(["xacro ", model, " calibration_file:=", calibration_file]),
        value_type=str,
    )
    return LaunchDescription(
        [
            DeclareLaunchArgument("calibration_file", default_value=default_calibration),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            Node(
                package="robot_state_publisher",
                executable="robot_state_publisher",
                name="agt_tracked_chassis_robot_state_publisher",
                output="screen",
                parameters=[
                    {
                        "robot_description": robot_description,
                        "use_sim_time": LaunchConfiguration("use_sim_time"),
                    }
                ],
            ),
        ]
    )
