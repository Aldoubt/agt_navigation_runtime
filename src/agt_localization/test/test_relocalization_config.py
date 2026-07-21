from pathlib import Path

import yaml


def test_ndt_thread_count_uses_validated_bunker_baseline():
    config_path = Path(__file__).parents[1] / "config" / "relocalization.yaml"
    config = yaml.safe_load(config_path.read_text(encoding="utf-8"))

    num_threads = config["/**"]["ros__parameters"]["ndt_num_threads"]
    assert isinstance(num_threads, int)
    assert num_threads == 4
    assert num_threads >= 1


def test_candidate_and_action_limits_are_bounded():
    config_path = Path(__file__).parents[1] / "config" / "relocalization.yaml"
    config = yaml.safe_load(config_path.read_text(encoding="utf-8"))
    params = config["/**"]["ros__parameters"]

    assert params["candidate_max"] > 0
    assert params["max_expanded_candidates"] >= params["candidate_max"]
    assert params["action_timeout_s"] > 0.0
    assert params["ambiguity_ratio"] >= 0.0
    assert params["external_coarse_max_age_s"] > 0.0
    assert params["external_coarse_future_tolerance_s"] >= 0.0
    assert params["manual_initialpose_enabled"] is True


def test_tracking_validation_is_bounded_and_enabled_by_default():
    config_path = Path(__file__).parents[1] / "config" / "relocalization.yaml"
    config = yaml.safe_load(config_path.read_text(encoding="utf-8"))
    params = config["/**"]["ros__parameters"]

    assert params["tracking_validation_enabled"] is True
    assert params["tracking_validation_period_s"] > 0.0
    assert params["tracking_validation_timeout_s"] > 0.0
    assert params["tracking_confirmations_required"] > 0
    assert 0 < params["tracking_failures_to_recover"] <= params["tracking_failures_to_lost"]
