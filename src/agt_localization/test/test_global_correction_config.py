from pathlib import Path

import yaml


ROOT = Path(__file__).parents[1]


def _params(name: str):
    return yaml.safe_load((ROOT / "config" / name).read_text(encoding="utf-8"))["/**"][
        "ros__parameters"
    ]


def test_relocalizer_does_not_own_production_map_odom_tf_or_canonical_status():
    relocalization = _params("relocalization.yaml")
    correction = _params("global_correction.yaml")
    launch = (ROOT / "launch" / "relocalization.launch.py").read_text(encoding="utf-8")

    assert relocalization["publish_tf"] is False
    assert '"publish_tf": False' in launch
    assert 'executable="global_correction_manager"' in launch
    assert '"/agt/localization/status"' in launch
    assert '"/agt/localization/evidence_status"' in launch
    assert correction["evidence_status_topic"] == "/agt/localization/evidence_status"
    assert correction["canonical_status_topic"] == "/agt/localization/status"


def test_global_correction_policy_is_fail_closed_and_state_specific():
    params = _params("global_correction.yaml")

    assert params["base_frame"] == "base_footprint"
    assert params["max_age_s"] > 0.0
    assert params["future_tolerance_s"] >= 0.0
    assert params["min_interval_s"] > 0.0
    assert params["max_fitness_score"] > 0.0
    assert 0.0 < params["tracking_max_translation_m"] < params["recovering_max_translation_m"]
    assert 0.0 < params["tracking_max_yaw_rad"] < params["recovering_max_yaw_rad"]
    assert params["allow_lost_reanchor"] is True


def test_recovery_trigger_reuses_existing_relocalize_action_and_candidates():
    params = _params("recovery_trigger.yaml")
    source = (ROOT / "src" / "recovery_trigger_manager.cpp").read_text(encoding="utf-8")

    assert params["enabled"] is True
    assert params["trigger_recovering"] is True
    assert params["trigger_lost"] is True
    assert params["use_last_valid_pose"] is True
    assert params["use_configured_candidates"] is True
    assert params["use_external_coarse_pose"] is True

    assert "MODE_LOCAL_CANDIDATES" in source
    assert "MODE_AUTO_SEARCH" in source
    assert "use_configured_candidates" in source
    assert "use_last_valid_pose" in source
    assert "use_external_coarse_pose" in source


def test_correction_manager_owns_canonical_localization_acceptance():
    source = (ROOT / "src" / "global_correction_manager.cpp").read_text(encoding="utf-8")

    assert "evidence_status_topic_" in source
    assert "canonical_status_topic_" in source
    assert "canonical_status_pub_->publish" in source
    assert "global correction rejected:" in source
    assert "STATE_RECOVERING" in source
    assert "localization_accepted = false" in source


def test_cmake_registers_v25_10_core_and_policy_tests():
    cmake = (ROOT / "CMakeLists.txt").read_text(encoding="utf-8")

    for token in (
        "agt_localization_global_correction",
        "global_correction_manager",
        "agt_localization_recovery_trigger",
        "recovery_trigger_manager",
        "test_global_correction_core",
        "test_recovery_trigger_policy",
        "test_global_correction_config",
    ):
        assert token in cmake
