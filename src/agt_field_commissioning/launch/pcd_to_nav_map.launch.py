from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument("pcd_path"),
        DeclareLaunchArgument("output_dir", default_value="runtime/maps/pcd2pgm"),
        DeclareLaunchArgument("save_map_name", default_value="navigation"),
        DeclareLaunchArgument("resolution", default_value="0.10"),
        DeclareLaunchArgument("min_points_per_cell", default_value="1"),
        DeclareLaunchArgument("h_min", default_value="0.10"),
        DeclareLaunchArgument("h_max", default_value="1.50"),
        DeclareLaunchArgument("downsample_leaf_size", default_value="0.25"),
        Node(
            package="pcd2pgm",
            executable="pcd2pgm_node",
            name="pcd2pgm_node",
            output="screen",
            parameters=[{
                "pcd_path": LaunchConfiguration("pcd_path"),
                "output_dir": LaunchConfiguration("output_dir"),
                "save_map_name": LaunchConfiguration("save_map_name"),
                "resolution": LaunchConfiguration("resolution"),
                "min_points_per_cell": LaunchConfiguration("min_points_per_cell"),
                "h_min": LaunchConfiguration("h_min"),
                "h_max": LaunchConfiguration("h_max"),
                "downsample_leaf_size": LaunchConfiguration("downsample_leaf_size"),
            }],
        ),
    ])
