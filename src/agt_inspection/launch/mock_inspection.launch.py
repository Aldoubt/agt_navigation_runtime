from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription(
        [
            DeclareLaunchArgument("runtime_maps_root", default_value="runtime/maps"),
            DeclareLaunchArgument("evidence_root", default_value="runtime/inspections"),
            DeclareLaunchArgument("gimbal_delay_s", default_value="0.05"),
            DeclareLaunchArgument("vision_delay_s", default_value="0.05"),
            Node(
                package="agt_inspection",
                executable="mock_gimbal_server.py",
                name="agt_mock_gimbal",
                output="screen",
                parameters=[{"delay_s": LaunchConfiguration("gimbal_delay_s")}],
            ),
            Node(
                package="agt_inspection",
                executable="mock_camera_server.py",
                name="agt_mock_camera",
                output="screen",
            ),
            Node(
                package="agt_inspection",
                executable="mock_vision_server.py",
                name="agt_mock_vision",
                output="screen",
                parameters=[{"delay_s": LaunchConfiguration("vision_delay_s")}],
            ),
            Node(
                package="agt_inspection",
                executable="inspection_task_server.py",
                name="agt_inspection_task_server",
                output="screen",
                parameters=[
                    {
                        "runtime_maps_root": LaunchConfiguration("runtime_maps_root"),
                        "evidence_root": LaunchConfiguration("evidence_root"),
                    }
                ],
            ),
        ]
    )
