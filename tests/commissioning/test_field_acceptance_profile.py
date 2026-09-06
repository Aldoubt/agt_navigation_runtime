from pathlib import Path

import pytest

from agt_field_commissioning.acceptance_profile import (
    AcceptanceProfileError,
    load_acceptance_profile,
)


ROOT = Path(__file__).resolve().parents[2]
PACKAGE = ROOT / "src" / "agt_field_commissioning"
WRAPPER = PACKAGE / "launch" / "field_acceptance.launch.py"
FIELD = PACKAGE / "launch" / "field_navigation.launch.py"
EDITOR = ROOT / "src" / "agt_navigation" / "scripts" / "rviz_task_editor.py"


def _write_profile(tmp_path: Path, extra: str = "") -> Path:
    candidates = tmp_path / "start_candidates.yaml"
    candidates.write_text(
        "schema_version: 1\n"
        "map_id: orchard_A\n"
        "map_hash: sha256:" + "a" * 64 + "\n"
        "candidates:\n"
        "  - id: start_gate_A\n"
        "    x: 1.0\n"
        "    y: 2.0\n"
        "    z: 0.0\n"
        "    yaw: 1.57\n",
        encoding="utf-8",
    )
    profile = tmp_path / "acceptance.yaml"
    profile.write_text(
        "schema_version: 1\n"
        "site_id: orchard_A\n"
        "site_revision: r03\n"
        "initial_pose_candidates_yaml: start_candidates.yaml\n"
        "task_group_id: inspection_route_A\n"
        "auto_load_task: true\n"
        + extra,
        encoding="utf-8",
    )
    return profile


def test_profile_resolves_candidate_path_and_never_contains_motion_start(tmp_path):
    profile_path = _write_profile(tmp_path)

    profile = load_acceptance_profile(profile_path)

    assert profile.site_id == "orchard_A"
    assert profile.site_revision == "r03"
    assert profile.task_group_id == "inspection_route_A"
    assert profile.auto_load_task is True
    assert profile.initial_pose_candidates_yaml == (
        tmp_path / "start_candidates.yaml"
    ).resolve()
    assert not hasattr(profile, "auto_start")


def test_profile_rejects_unknown_or_motion_start_fields(tmp_path):
    with pytest.raises(AcceptanceProfileError, match="unsupported field"):
        load_acceptance_profile(_write_profile(tmp_path, "auto_start: true\n"))


def test_profile_requires_existing_candidate_yaml(tmp_path):
    profile = tmp_path / "acceptance.yaml"
    profile.write_text(
        "schema_version: 1\n"
        "site_id: orchard_A\n"
        "site_revision: r03\n"
        "initial_pose_candidates_yaml: missing.yaml\n"
        "task_group_id: inspection_route_A\n"
        "auto_load_task: true\n",
        encoding="utf-8",
    )

    with pytest.raises(AcceptanceProfileError, match="does not exist"):
        load_acceptance_profile(profile)


def test_field_navigation_threads_candidate_seed_and_editor_auto_load_only():
    text = FIELD.read_text(encoding="utf-8")

    assert 'DeclareLaunchArgument("configured_candidates_yaml", default_value="")' in text
    assert '"configured_candidates_yaml": LaunchConfiguration("configured_candidates_yaml").perform(context)' in text
    assert 'DeclareLaunchArgument("rviz_auto_load_task", default_value="false")' in text
    assert '"auto_load_saved_task": _enabled(context, "rviz_auto_load_task")' in text
    assert "auto_start" not in text


def test_editor_may_auto_load_but_has_no_auto_start_parameter():
    text = EDITOR.read_text(encoding="utf-8")

    assert 'declare_parameter("auto_load_saved_task", False)' in text
    assert "_schedule_initial_load" in text
    assert '"/agt/rviz/task/start"' in text
    assert 'declare_parameter("auto_start"' not in text


def test_acceptance_wrapper_expands_profile_into_existing_field_launch():
    text = WRAPPER.read_text(encoding="utf-8")

    assert "load_acceptance_profile" in text
    assert '"field_navigation.launch.py"' in text
    assert '"site_id": profile.site_id' in text
    assert '"site_revision": profile.site_revision' in text
    assert '"configured_candidates_yaml": str(profile.initial_pose_candidates_yaml)' in text
    assert '"rviz_task_group_id": profile.task_group_id' in text
    assert '"rviz_auto_load_task": "true" if profile.auto_load_task else "false"' in text
    assert "auto_start" not in text
