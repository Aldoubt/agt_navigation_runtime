from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument("runtime_dir", default_value="runtime"),
        DeclareLaunchArgument("execution_backend", default_value="sequential"),
        DeclareLaunchArgument("start_bt_executor", default_value="auto"),
        Node(
            package="agt_mission_manager",
            executable="mission_manager_node.py",
            name="agt_mission_manager",
            output="screen",
            parameters=[{"runtime_dir": LaunchConfiguration("runtime_dir"), "execution_backend": LaunchConfiguration("execution_backend")}],
        ),
        Node(
            package="agt_bt_executor",
            executable="bt_executor_node",
            name="agt_bt_executor",
            output="screen",
            condition=IfCondition(PythonExpression(["'", LaunchConfiguration("execution_backend"), "' == 'behavior_tree' and ('", LaunchConfiguration("start_bt_executor"), "' == 'true' or '", LaunchConfiguration("start_bt_executor"), "' == 'auto')"])),
        ),
    ])
