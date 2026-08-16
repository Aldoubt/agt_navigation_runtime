from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    backend_share = Path(get_package_share_directory("agt_chassis_bunker"))
    chassis_share = Path(get_package_share_directory("agt_chassis"))
    safety_share = Path(get_package_share_directory("agt_safety"))

    use_sim_time = LaunchConfiguration("use_sim_time")
    return LaunchDescription(
        [
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            DeclareLaunchArgument(
                "operation_mode",
                default_value="control",
                choices=["control", "monitor"],
                description="control enables command execution; monitor is read-only telemetry",
            ),
            DeclareLaunchArgument("can_interface", default_value="can0"),
            DeclareLaunchArgument("command_topic", default_value="/agt/chassis/cmd_vel"),
            DeclareLaunchArgument("is_bunker_mini", default_value="false"),
            DeclareLaunchArgument("start_driver", default_value="true"),
            DeclareLaunchArgument("start_safety", default_value="true"),
            DeclareLaunchArgument("publish_driver_odom_tf", default_value="false"),
            DeclareLaunchArgument(
                "chassis_config",
                default_value=str(chassis_share / "config" / "chassis.yaml"),
            ),
            DeclareLaunchArgument(
                "backend_config",
                default_value=str(backend_share / "config" / "bunker.yaml"),
            ),
            DeclareLaunchArgument(
                "safety_config",
                default_value=str(backend_share / "config" / "bunker_safety.yaml"),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    str(safety_share / "launch" / "safety.launch.py")
                ),
                condition=IfCondition(
                    PythonExpression(
                        [
                            "'",
                            LaunchConfiguration("start_safety"),
                            "'.lower() in ('true', '1', 'yes', 'on') and '",
                            LaunchConfiguration("operation_mode"),
                            "' == 'control'",
                        ]
                    )
                ),
                launch_arguments={
                    "safety_config": LaunchConfiguration("safety_config"),
                    "use_sim_time": use_sim_time,
                }.items(),
            ),
            Node(
                package="agt_chassis",
                executable="chassis_command_guard.py",
                name="agt_chassis_command_guard",
                output="screen",
                parameters=[
                    LaunchConfiguration("chassis_config"),
                    {"use_sim_time": use_sim_time},
                ],
                condition=IfCondition(
                    PythonExpression(
                        ["'", LaunchConfiguration("operation_mode"), "' == 'control'"]
                    )
                ),
            ),
            Node(
                package="agt_chassis_bunker",
                executable="bunker_status_bridge.py",
                name="agt_bunker_status_bridge",
                output="screen",
                parameters=[
                    LaunchConfiguration("backend_config"),
                    {"use_sim_time": use_sim_time},
                ],
            ),
            Node(
                package="bunker_base",
                executable="bunker_base_node",
                name="agt_bunker_base",
                output="screen",
                emulate_tty=True,
                condition=IfCondition(LaunchConfiguration("start_driver")),
                parameters=[
                    {
                        "use_sim_time": use_sim_time,
                        "port_name": LaunchConfiguration("can_interface"),
                        "odom_frame": "bunker_odom",
                        "base_frame": "base_footprint",
                        "odom_topic_name": "/agt/chassis/odometry",
                        "is_bunker_mini": ParameterValue(
                            LaunchConfiguration("is_bunker_mini"), value_type=bool
                        ),
                        "publish_odom_tf": ParameterValue(
                            LaunchConfiguration("publish_driver_odom_tf"), value_type=bool
                        ),
                        "command_timeout": 0.25,
                    }
                ],
                remappings=[
                    ("/cmd_vel", LaunchConfiguration("command_topic")),
                    ("/bunker_status", "/agt/chassis/status/raw"),
                    ("/bunker_rc_state", "/agt/chassis/rc_state"),
                ],
            ),
        ]
    )
