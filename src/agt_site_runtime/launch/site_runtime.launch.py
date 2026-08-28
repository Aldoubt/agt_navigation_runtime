from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    package_share = Path(get_package_share_directory("agt_site_runtime"))
    config = package_share / "config" / "site_runtime.yaml"
    return LaunchDescription(
        [
            Node(
                package="agt_site_runtime",
                executable="site_runtime_node.py",
                name="agt_site_runtime",
                output="screen",
                parameters=[str(config)],
            )
        ]
    )
