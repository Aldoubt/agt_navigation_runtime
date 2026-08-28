from pathlib import Path

import yaml

from agt_experiment_manager.manager import ExperimentManager


PACKAGE_ROOT = Path(__file__).resolve().parents[1]
README = PACKAGE_ROOT / "README.md"

REQUIRED_FIELD_MAPPING_TOPICS = {
    "/tf",
    "/tf_static",
    "/agt/sensors/lidar/custom",
    "/agt/sensors/imu/data",
    "/agt/chassis/odometry",
    "/agt/chassis/status",
    "/agt/mapping/odometry",
    "/agt/mapping/registered_points",
    "/agt/navigation/cmd_vel",
}

REQUIRED_FIELD_NAVIGATION_TOPICS = {
    "/tf",
    "/tf_static",
    "/agt/mapping/odometry",
    "/agt/mapping/registered_points",
    "/agt/localization/status",
    "/agt/perception/obstacle_cloud",
    "/agt/navigation/cmd_vel_raw",
    "/agt/navigation/cmd_vel",
    "/plan",
    "/global_costmap/costmap",
    "/local_costmap/costmap",
    "/agt/chassis/odometry",
    "/agt/chassis/status",
}


class FakeRecordingProcess:
    pid = 32001
    returncode = None

    def __init__(self, command, **_kwargs):
        self.command = command

    def poll(self):
        return self.returncode


def _profiles():
    path = PACKAGE_ROOT / "config" / "bag_profiles.yaml"
    return yaml.safe_load(path.read_text(encoding="utf-8"))["profiles"]


def _assert_explicit_profile(profile_name: str, required_topics: set[str]):
    profile = _profiles()[profile_name]
    topics = profile["topics"]

    assert len(topics) == len(set(topics))
    assert required_topics <= set(topics)
    assert "/agt/sensors/gnss/fix" in topics
    assert "-a" not in topics


def test_field_mapping_baseline_profile_is_explicit_and_complete():
    _assert_explicit_profile(
        "field_mapping_baseline",
        REQUIRED_FIELD_MAPPING_TOPICS,
    )


def test_field_navigation_baseline_profile_is_explicit_and_complete():
    _assert_explicit_profile(
        "field_navigation_baseline",
        REQUIRED_FIELD_NAVIGATION_TOPICS,
    )


def test_field_baseline_record_commands_never_use_record_all(tmp_path):
    profiles = _profiles()

    for index, (profile_name, required_topics) in enumerate(
        (
            ("field_mapping_baseline", REQUIRED_FIELD_MAPPING_TOPICS),
            ("field_navigation_baseline", REQUIRED_FIELD_NAVIGATION_TOPICS),
        ),
        start=1,
    ):
        manager = ExperimentManager(
            tmp_path / f"experiments_{index}",
            popen_factory=FakeRecordingProcess,
        )
        experiment_id = manager.create(title=profile_name)
        manager.start(experiment_id)
        manager.start_bag(experiment_id, profile_name, profiles[profile_name])

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
        assert required_topics <= set(command)


def test_readme_documents_sole_recorder_and_field_profile_flow():
    text = README.read_text(encoding="utf-8").lower()
    required_fragments = (
        "field_mapping.launch.py",
        "field_navigation.launch.py",
        "field_mapping_baseline",
        "field_navigation_baseline",
        "sole runtime owner",
        "before moving the robot",
    )
    missing = [fragment for fragment in required_fragments if fragment not in text]
    assert not missing, f"README is missing field baseline recorder guidance: {missing}"
