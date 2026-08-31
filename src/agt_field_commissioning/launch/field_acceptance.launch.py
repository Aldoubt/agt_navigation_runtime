from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, OpaqueFunction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

from agt_field_commissioning.acceptance_profile import load_acceptance_profile


def _compose(context):
    profile_path = LaunchConfiguration("acceptance_profile").perform(context)
    profile = load_acceptance_profile(profile_path)
    share = Path(get_package_share_directory("agt_field_commissioning"))

    forwarded = {
        "site_id": profile.site_id,
        "site_revision": profile.site_revision,
        "configured_candidates_yaml": str(profile.initial_pose_candidates_yaml),
        "rviz_task_group_id": profile.task_group_id,
        "rviz_auto_load_task": "true" if profile.auto_load_task else "false",
        "sites_root": LaunchConfiguration("sites_root").perform(context),
        "state_root": LaunchConfiguration("state_root").perform(context),
        "site_vehicle_profile": LaunchConfiguration("site_vehicle_profile").perform(context),
        "runtime_dir": LaunchConfiguration("runtime_dir").perform(context),
        "tasks_root": LaunchConfiguration("tasks_root").perform(context),
        "operation_mode": LaunchConfiguration("operation_mode").perform(context),
        "can_interface": LaunchConfiguration("can_interface").perform(context),
        "expected_can_bitrate": LaunchConfiguration("expected_can_bitrate").perform(context),
        "field_capture_backend": LaunchConfiguration("field_capture_backend").perform(context),
        "start_inspection": LaunchConfiguration("start_inspection").perform(context),
        "start_rviz": LaunchConfiguration("start_rviz").perform(context),
    }
    return [
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(str(share / "launch" / "field_navigation.launch.py")),
            launch_arguments=forwarded.items(),
        )
    ]


def generate_launch_description():
    return LaunchDescription(
        [
            DeclareLaunchArgument("acceptance_profile"),
            DeclareLaunchArgument("sites_root", default_value="/opt/agt/sites"),
            DeclareLaunchArgument(
                "state_root", default_value="~/.local/state/agt_navigation_runtime"
            ),
            DeclareLaunchArgument(
                "site_vehicle_profile", default_value="/opt/agt/profiles/bunker.yaml"
            ),
            DeclareLaunchArgument("runtime_dir", default_value="runtime"),
            DeclareLaunchArgument("tasks_root", default_value=""),
            DeclareLaunchArgument("operation_mode", default_value="control"),
            DeclareLaunchArgument("can_interface", default_value="can0"),
            DeclareLaunchArgument("expected_can_bitrate", default_value="0"),
            DeclareLaunchArgument("field_capture_backend", default_value="placeholder"),
            DeclareLaunchArgument("start_inspection", default_value="false"),
            DeclareLaunchArgument("start_rviz", default_value="true"),
            OpaqueFunction(function=_compose),
        ]
    )
