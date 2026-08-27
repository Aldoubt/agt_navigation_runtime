from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription(
        [
            DeclareLaunchArgument("input_topic", default_value=""),
            DeclareLaunchArgument(
                "output_topic", default_value="/agt/sensors/gnss/fix"
            ),
            DeclareLaunchArgument("frame_id", default_value="gps_link"),
            DeclareLaunchArgument("use_sim_time", default_value="false"),
            Node(
                package="agt_sensor_adapters",
                executable="navsat_fix_adapter",
                name="agt_navsat_fix_adapter",
                output="screen",
                parameters=[
                    {
                        "input_topic": LaunchConfiguration("input_topic"),
                        "output_topic": LaunchConfiguration("output_topic"),
                        "frame_id": LaunchConfiguration("frame_id"),
                        "use_sim_time": LaunchConfiguration("use_sim_time"),
                    }
                ],
            ),
        ]
    )
