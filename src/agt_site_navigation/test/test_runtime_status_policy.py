from __future__ import annotations

from dataclasses import replace

from agt_site_navigation.runtime_status import (
    REQUIRED_LIFECYCLE_NODES,
    STATE_BLOCKED,
    STATE_ERROR,
    STATE_READY,
    STATE_STARTING,
    STATE_UNKNOWN,
    LifecycleEvidence,
    RuntimeStatusEvidence,
    evaluate_runtime_status,
)


def _lifecycles(*, known: bool = True, active: bool = True):
    return {
        name: LifecycleEvidence(known=known, active=active)
        for name in REQUIRED_LIFECYCLE_NODES
    }


def all_ready() -> RuntimeStatusEvidence:
    return RuntimeStatusEvidence(
        binding_known=True,
        binding_ready=True,
        binding_error=False,
        binding_blocker_codes=(),
        site_id="greenhouse_01",
        site_revision="v1",
        site_hash="site-content-hash",
        localization_pcd_sha256="pcd-hash",
        localization_known=True,
        localization_tracking=True,
        localization_map_id="greenhouse_01",
        localization_map_hash="pcd-hash",
        lifecycles=_lifecycles(),
    )


def test_required_lifecycle_set_matches_production_navigation_manager():
    assert REQUIRED_LIFECYCLE_NODES == (
        "map_server",
        "planner_server",
        "smoother_server",
        "controller_server",
        "behavior_server",
        "bt_navigator",
        "waypoint_follower",
        "collision_monitor",
    )


def test_all_binding_localization_and_lifecycle_evidence_ready():
    result = evaluate_runtime_status(all_ready())

    assert result.state == STATE_READY
    assert result.localization_bound
    assert result.map_identity_known
    assert result.map_identity_match
    assert result.blocker_codes == ()


def test_missing_site_binding_is_unknown_and_suppresses_downstream_noise():
    result = evaluate_runtime_status(
        replace(
            all_ready(),
            binding_known=False,
            binding_ready=False,
            localization_known=False,
            localization_tracking=False,
            lifecycles=_lifecycles(known=False, active=False),
        )
    )

    assert result.state == STATE_UNKNOWN
    assert result.blocker_codes == ("SITE_BINDING_UNKNOWN",)
    assert not result.localization_bound
    assert not result.map_identity_known
    assert not result.map_identity_match


def test_blocked_site_binding_stays_blocked_without_nav2_secondary_errors():
    result = evaluate_runtime_status(
        replace(
            all_ready(),
            binding_ready=False,
            binding_blocker_codes=("ACTIVE_SITE_NOT_READY",),
            localization_known=False,
            lifecycles=_lifecycles(known=False, active=False),
        )
    )

    assert result.state == STATE_BLOCKED
    assert result.blocker_codes == (
        "SITE_BINDING_NOT_READY",
        "ACTIVE_SITE_NOT_READY",
    )


def test_site_binding_error_has_error_precedence():
    result = evaluate_runtime_status(
        replace(
            all_ready(),
            binding_ready=False,
            binding_error=True,
            binding_blocker_codes=("SITE_ASSET_INVALID",),
        )
    )

    assert result.state == STATE_ERROR
    assert result.blocker_codes == ("SITE_BINDING_ERROR", "SITE_ASSET_INVALID")


def test_localization_unknown_is_starting_not_mismatch():
    result = evaluate_runtime_status(
        replace(
            all_ready(),
            localization_known=False,
            localization_tracking=False,
            localization_map_id="",
            localization_map_hash="",
        )
    )

    assert result.state == STATE_STARTING
    assert "LOCALIZATION_UNKNOWN" in result.blocker_codes
    assert not result.localization_bound
    assert not result.map_identity_known
    assert not result.map_identity_match


def test_nontracking_localization_is_blocked():
    result = evaluate_runtime_status(
        replace(all_ready(), localization_tracking=False)
    )

    assert result.state == STATE_BLOCKED
    assert "LOCALIZATION_NOT_TRACKING" in result.blocker_codes
    assert not result.localization_bound


def test_incomplete_localization_identity_is_starting_not_mismatch():
    result = evaluate_runtime_status(
        replace(all_ready(), localization_map_hash="")
    )

    assert result.state == STATE_STARTING
    assert "LOCALIZATION_IDENTITY_UNKNOWN" in result.blocker_codes
    assert not result.map_identity_known
    assert not result.map_identity_match
    assert not result.localization_bound


def test_localization_map_id_mismatch_is_blocked():
    result = evaluate_runtime_status(
        replace(all_ready(), localization_map_id="greenhouse_02")
    )

    assert result.state == STATE_BLOCKED
    assert "LOCALIZATION_MAP_MISMATCH" in result.blocker_codes
    assert result.map_identity_known
    assert not result.map_identity_match
    assert not result.localization_bound


def test_localization_pcd_hash_mismatch_is_blocked():
    result = evaluate_runtime_status(
        replace(all_ready(), localization_map_hash="wrong-pcd-hash")
    )

    assert result.state == STATE_BLOCKED
    assert "LOCALIZATION_MAP_MISMATCH" in result.blocker_codes
    assert result.map_identity_known
    assert not result.map_identity_match


def test_unknown_required_lifecycle_is_starting():
    lifecycles = _lifecycles()
    lifecycles["planner_server"] = LifecycleEvidence(known=False, active=False)

    result = evaluate_runtime_status(replace(all_ready(), lifecycles=lifecycles))

    assert result.state == STATE_STARTING
    assert result.blocker_codes == ("NAV2_PLANNER_SERVER_UNKNOWN",)


def test_inactive_required_lifecycle_is_blocked():
    lifecycles = _lifecycles()
    lifecycles["controller_server"] = LifecycleEvidence(known=True, active=False)

    result = evaluate_runtime_status(replace(all_ready(), lifecycles=lifecycles))

    assert result.state == STATE_BLOCKED
    assert result.blocker_codes == ("NAV2_CONTROLLER_SERVER_INACTIVE",)


def test_missing_required_lifecycle_entry_is_fail_closed_unknown():
    lifecycles = _lifecycles()
    del lifecycles["collision_monitor"]

    result = evaluate_runtime_status(replace(all_ready(), lifecycles=lifecycles))

    assert result.state == STATE_STARTING
    assert result.blocker_codes == ("NAV2_COLLISION_MONITOR_UNKNOWN",)
