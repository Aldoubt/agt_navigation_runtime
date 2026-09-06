from pathlib import Path
import shutil

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, OpaqueFunction, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node


RUNTIME_ROOT = Path("/tmp/agt_mission_mock_runtime")


def _prepare_mock_runtime(_context):
    mission_share = Path(get_package_share_directory("agt_mission_manager"))
    inspection_share = Path(get_package_share_directory("agt_inspection"))
    fixture_runtime = mission_share / "fixtures" / "runtime"

    if RUNTIME_ROOT.exists():
        shutil.rmtree(RUNTIME_ROOT)
    shutil.copytree(fixture_runtime, RUNTIME_ROOT)

    inspection_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            str(inspection_share / "launch" / "mock_inspection.launch.py")
        ),
        launch_arguments={
            "evidence_root": str(RUNTIME_ROOT / "inspections"),
        }.items(),
    )

    mission_manager = Node(
        package="agt_mission_manager",
        executable="mission_manager_node.py",
        name="agt_mission_manager",
        output="screen",
        parameters=[
            {
                "runtime_dir": str(RUNTIME_ROOT),
                "mission_root": str(RUNTIME_ROOT / "missions"),
                "mission_report_root": str(RUNTIME_ROOT / "mission_reports"),
                "execution_backend": "sequential",
                "waypoint_server_wait_timeout_s": 2.0,
                "inspection_server_wait_timeout_s": 2.0,
                "localization_status_timeout_s": 2.0,
                "task_readiness_timeout_s": 2.0,
            }
        ],
    )

    # Start the mission manager shortly after the mock context so its first
    # mission validation sees fresh localization/readiness samples.
    return [inspection_launch, TimerAction(period=0.5, actions=[mission_manager])]


def generate_launch_description():
    return LaunchDescription([OpaqueFunction(function=_prepare_mock_runtime)])
