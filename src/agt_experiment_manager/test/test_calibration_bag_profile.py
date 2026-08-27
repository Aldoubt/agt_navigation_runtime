from pathlib import Path

import yaml

from agt_experiment_manager.manager import ExperimentManager


REQUIRED_CALIBRATION_TOPICS = {
    "/tf",
    "/tf_static",
    "/agt/sensors/lidar/custom",
    "/agt/sensors/imu/data",
    "/agt/chassis/odometry",
    "/agt/chassis/status",
    "/agt/mapping/odometry",
    "/agt/mapping/registered_points",
    "/agt/navigation/cmd_vel",
    "/diagnostics",
}


class FakeRecordingProcess:
    pid = 31001
    returncode = None

    def __init__(self, command, **_kwargs):
        self.command = command

    def poll(self):
        return self.returncode


def _profiles():
    path = Path(__file__).resolve().parents[1] / "config" / "bag_profiles.yaml"
    return yaml.safe_load(path.read_text(encoding="utf-8"))["profiles"]


def test_calibration_profile_is_explicit_and_complete():
    topics = _profiles()["calibration"]["topics"]
    assert len(topics) == len(set(topics))
    assert REQUIRED_CALIBRATION_TOPICS <= set(topics)
    assert "/agt/sensors/gnss/fix" in topics
    assert "-a" not in topics


def test_calibration_record_command_never_uses_record_all(tmp_path):
    manager = ExperimentManager(
        tmp_path / "experiments", popen_factory=FakeRecordingProcess
    )
    experiment_id = manager.create(title="Calibration")
    manager.start(experiment_id)
    profile = _profiles()["calibration"]
    manager.start_bag(experiment_id, "calibration", profile)
    command = manager._bag_process.command
    assert command[:6] == [
        "ros2",
        "bag",
        "record",
        "--storage",
        "sqlite3",
        "--output",
    ]
    assert "-a" not in command
    assert REQUIRED_CALIBRATION_TOPICS <= set(command)
