from pathlib import Path
import importlib.util

import yaml


SCRIPT = Path(__file__).with_name("validate_calibration_bag.py")
spec = importlib.util.spec_from_file_location("validate_calibration_bag", SCRIPT)
validator = importlib.util.module_from_spec(spec)
spec.loader.exec_module(validator)


REQUIRED = list(validator.REQUIRED_TOPICS)


def _metadata(counts, duration=1_000_000_000):
    return {
        "rosbag2_bagfile_information": {
            "duration": {"nanoseconds": duration},
            "topics_with_message_count": [
                {
                    "topic_metadata": {
                        "name": topic,
                        "type": "test/msg/Type",
                        "serialization_format": "cdr",
                        "offered_qos_profiles": "",
                    },
                    "message_count": count,
                }
                for topic, count in counts.items()
            ],
        }
    }


def test_complete_required_topics_are_accepted_without_gnss():
    result = validator.validate_metadata(_metadata({topic: 1 for topic in REQUIRED}))
    assert result["accepted"] is True
    assert result["missing_topics"] == []
    assert result["empty_topics"] == []
    assert result["gnss_present"] is False


def test_missing_wheel_odometry_is_rejected():
    counts = {topic: 1 for topic in REQUIRED if topic != "/agt/chassis/odometry"}
    result = validator.validate_metadata(_metadata(counts))
    assert result["accepted"] is False
    assert result["missing_topics"] == ["/agt/chassis/odometry"]


def test_required_topic_with_zero_messages_is_rejected():
    counts = {topic: 1 for topic in REQUIRED}
    counts["/agt/mapping/odometry"] = 0
    result = validator.validate_metadata(_metadata(counts))
    assert result["accepted"] is False
    assert result["empty_topics"] == ["/agt/mapping/odometry"]


def test_missing_command_topic_is_valid_for_command_inert_monitor_capture():
    counts = {
        topic: 1
        for topic in REQUIRED
        if topic != "/agt/navigation/cmd_vel"
    }
    result = validator.validate_metadata(_metadata(counts))
    assert result["accepted"] is True
    assert "/agt/navigation/cmd_vel" not in result["missing_topics"]


def test_missing_gnss_is_optional_by_default_and_required_on_request():
    metadata = _metadata({topic: 1 for topic in REQUIRED})
    assert validator.validate_metadata(metadata)["accepted"] is True
    required = validator.validate_metadata(metadata, require_gnss=True)
    assert required["accepted"] is False
    assert required["missing_topics"] == [validator.GNSS_TOPIC]


def test_present_nonempty_gnss_satisfies_required_mode():
    counts = {topic: 1 for topic in REQUIRED}
    counts[validator.GNSS_TOPIC] = 5
    result = validator.validate_metadata(_metadata(counts), require_gnss=True)
    assert result["accepted"] is True
    assert result["gnss_present"] is True


def test_cli_fixture_shape_uses_metadata_yaml(tmp_path):
    bag = tmp_path / "bag"
    bag.mkdir()
    (bag / "metadata.yaml").write_text(
        yaml.safe_dump(_metadata({topic: 1 for topic in REQUIRED})),
        encoding="utf-8",
    )
    result = validator.validate_bag_directory(bag)
    assert result["accepted"] is True
    assert result["duration_nanoseconds"] == 1_000_000_000
