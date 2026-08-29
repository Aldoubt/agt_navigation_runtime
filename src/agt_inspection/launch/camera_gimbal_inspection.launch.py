from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    vendor_share = Path(get_package_share_directory("autolabor_c1_bringup"))

    vendor = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(str(vendor_share / "launch" / "autolabor_c1.launch.py")),
        launch_arguments={
            "device_path": LaunchConfiguration("camera_device_path"),
            "image_width": LaunchConfiguration("camera_width"),
            "image_height": LaunchConfiguration("camera_height"),
            "fps": LaunchConfiguration("camera_fps"),
            "port_name": LaunchConfiguration("camera_gimbal_port"),
            "capture_output_root": LaunchConfiguration("capture_output_root"),
            "gui": "false",
        }.items(),
    )

    inspection_server = Node(
        package="agt_inspection",
        executable="inspection_task_server.py",
        name="inspection_task_server",
        output="screen",
        parameters=[
            {
                "view_backend": "camera_gimbal",
                "runtime_maps_root": LaunchConfiguration("runtime_maps_root"),
                "evidence_root": LaunchConfiguration("evidence_root"),
                "camera_calibration_id": LaunchConfiguration("camera_calibration_id"),
                "camera_calibration_sha256": LaunchConfiguration(
                    "camera_calibration_sha256"
                ),
                "capture_localization_timeout_s": LaunchConfiguration(
                    "capture_localization_timeout_s"
                ),
                "camera_gimbal_health_freshness_s": LaunchConfiguration(
                    "camera_gimbal_health_freshness_s"
                ),
            }
        ],
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument("camera_device_path", default_value="/dev/video0"),
            DeclareLaunchArgument("camera_gimbal_port", default_value="/dev/ttyUSB0"),
            DeclareLaunchArgument("camera_width", default_value="1920"),
            DeclareLaunchArgument("camera_height", default_value="1080"),
            DeclareLaunchArgument("camera_fps", default_value="30.0"),
            DeclareLaunchArgument(
                "capture_output_root", default_value="runtime/camera_gimbal_capture"
            ),
            DeclareLaunchArgument("runtime_maps_root", default_value="runtime/maps"),
            DeclareLaunchArgument("evidence_root", default_value="runtime/inspections"),
            DeclareLaunchArgument("camera_calibration_id", default_value=""),
            DeclareLaunchArgument("camera_calibration_sha256", default_value=""),
            DeclareLaunchArgument(
                "capture_localization_timeout_s", default_value="2.0"
            ),
            DeclareLaunchArgument(
                "camera_gimbal_health_freshness_s", default_value="1.5"
            ),
            vendor,
            inspection_server,
        ]
    )
