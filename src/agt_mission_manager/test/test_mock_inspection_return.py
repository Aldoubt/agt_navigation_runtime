from pathlib import Path

from agt_mission_manager.mission_model import StepType
from agt_mission_manager.mission_schema import load_mission


PACKAGE = Path(__file__).resolve().parents[1]
FIXTURE = (
    PACKAGE
    / "test"
    / "fixtures"
    / "runtime"
    / "missions"
    / "mock_inspection_return"
    / "v1"
    / "mission.yaml"
)


def test_mock_mission_fixture_binds_green_multiview_inspection_then_home():
    mission = load_mission(FIXTURE)
    assert mission.mission_id == "mock_inspection_return"
    assert mission.content_sha256 == (
        "sha256:825ea0ff78b237a64f5fea6419aac99117ff4bc870746d492410b7a1947c0ec0"
    )
    assert [step.type for step in mission.steps] == [
        StepType.INSPECTION_TASK,
        StepType.RETURN_HOME,
    ]
    inspection, home = mission.steps
    assert inspection.inspection_task_id == "inspection_multiview_two_point"
    assert inspection.expected_content_sha256 == (
        "sha256:aaa7c6b351e434dbcb2c903dcb4801a0a621c6fcf64ab0506de766528b7191cf"
    )
    assert home.task_group_id == "home_mock"
    assert home.task_group_revision == 1


def test_mock_launch_uses_inspection_stack_and_writable_tmp_runtime_only():
    launch = (PACKAGE / "launch" / "mock_inspection_return.launch.py").read_text(
        encoding="utf-8"
    )
    cmake = (PACKAGE / "CMakeLists.txt").read_text(encoding="utf-8")

    assert 'get_package_share_directory("agt_inspection")' in launch
    assert '"mock_inspection.launch.py"' in launch
    assert '/tmp/agt_mission_mock_runtime' in launch
    assert '"execution_backend": "sequential"' in launch
    assert '"mission_report_root"' in launch
    assert '"evidence_root"' in launch
    assert "shutil.copytree" in launch

    for forbidden in ("nav2_bringup", "bunker", "can0"):
        assert forbidden not in launch.lower()

    assert "install(DIRECTORY test/fixtures/" in cmake
    assert "DESTINATION share/${PROJECT_NAME}/fixtures" in cmake
