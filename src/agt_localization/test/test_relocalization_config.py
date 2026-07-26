from pathlib import Path
import re

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


def test_cloud_freshness_parameters_are_fail_closed():
    config_path = Path(__file__).parents[1] / "config" / "relocalization.yaml"
    params = yaml.safe_load(config_path.read_text(encoding="utf-8"))["/**"]["ros__parameters"]

    assert params["max_cloud_age_s"] == 0.5
    assert params["max_cloud_age_s"] > 0.0
    assert params["max_cloud_future_tolerance_s"] == 0.1
    assert params["max_cloud_future_tolerance_s"] >= 0.0
    assert params["require_nonzero_cloud_stamp"] is True


def test_tracking_validation_is_bounded_and_enabled_by_default():
    config_path = Path(__file__).parents[1] / "config" / "relocalization.yaml"
    config = yaml.safe_load(config_path.read_text(encoding="utf-8"))
    params = config["/**"]["ros__parameters"]

    assert params["tracking_validation_enabled"] is True
    assert params["tracking_validation_period_s"] > 0.0
    assert params["tracking_validation_timeout_s"] > 0.0
    assert params["tracking_confirmations_required"] == 1
    assert 0 < params["tracking_failures_to_recover"] <= params["tracking_failures_to_lost"]


def test_bootstrap_confirmation_parameter_rejects_every_value_except_one():
    source_path = Path(__file__).parents[1] / "src" / "relocalization_node.cpp"
    source = source_path.read_text(encoding="utf-8")

    assert "tracking_confirmations_required != 1" in source
    assert "tracking_confirmations_required currently supports only 1" in source
    assert "multi-frame bootstrap confirmation is not implemented" in source


def test_tracking_validation_state_update_is_owned_by_outer_worker():
    source_path = Path(__file__).parents[1] / "src" / "relocalization_node.cpp"
    source = source_path.read_text(encoding="utf-8")
    run_candidates = source.split("GoalRunResult runCandidates(", 1)[1].split(
        "relocalization_core::RegistrationBackendType parseBackend", 1
    )[0]
    tracking_worker = source.split("void maybeStartTrackingValidation()", 1)[1].split(
        "relocalization_core::Relocalizer relocalizer_", 1
    )[0]

    assert "supervisor_.trackingValidation(" not in run_candidates
    assert tracking_worker.count("supervisor_.trackingValidation(accepted)") == 1
    assert "RunDisposition::kSkipped" in tracking_worker
    assert tracking_worker.count("publishStatus(status);") == 1


def test_only_fresh_duplicate_is_skipped():
    header_path = (
        Path(__file__).parents[1]
        / "include"
        / "agt_localization"
        / "localization_timing.hpp"
    )
    source = header_path.read_text(encoding="utf-8")
    decision = source.split("inline TrackingCloudDisposition decideTrackingCloudDisposition(", 1)[
        1
    ].split("inline CloudTimeDecision validateCloudTimestamp(", 1)[0]

    assert "cloud_time.accepted && sequence_status == CloudSequenceStatus::kDuplicate" in decision
    assert decision.index("cloud_time.accepted &&") < decision.index("if (!cloud_time.accepted)")


def test_tracking_validation_run_does_not_publish_intermediate_status():
    source_path = Path(__file__).parents[1] / "src" / "relocalization_node.cpp"
    source = source_path.read_text(encoding="utf-8")
    run_candidates = source.split("GoalRunResult runCandidates(", 1)[1].split(
        "relocalization_core::RegistrationBackendType parseBackend", 1
    )[0]
    status_helper = source.split("LocalizationStatus makeRunStatus(", 1)[1].split(
        "void publishTerminalStatus(", 1
    )[0]

    assert re.search(r"\bpublishStatus\s*\(", run_candidates) is None
    assert re.search(r"\bpublishTerminalStatus\s*\(", run_candidates) is None
    publication_policies = re.findall(r"makeRunStatus\(\s*([^,\s]+)", run_candidates)
    assert publication_policies
    assert set(publication_policies) == {"tracking_validation"}
    assert "if (!tracking_validation)" in status_helper


def test_relocalization_uses_cloud_time_for_dynamic_tf_and_results():
    source_path = Path(__file__).parents[1] / "src" / "relocalization_node.cpp"
    source = source_path.read_text(encoding="utf-8")

    assert "odom_frame_, tracking_frame_, cloud_stamp" in source
    assert "odom_frame_, tracking_frame_, tf2::TimePointZero" not in source
    assert "predictMapFromTracking" in source
    assert "aligned_msg.header.stamp = cloud_stamp" in source
    assert "poseStampedFromEigen(best.map_to_base, cloud_stamp)" in source
