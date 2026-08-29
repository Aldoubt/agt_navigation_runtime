from dataclasses import replace

from agt_system_manager.readiness import (
    Evidence,
    authoritative_map_known,
    evaluate_navigation_readiness,
)


def all_ready() -> Evidence:
    return Evidence(
        health_known=True,
        health_ok=True,
        map_known=True,
        map_ready=True,
        map_id="greenhouse_01",
        map_version_id="v1",
        map_hash="site-content-hash",
        localization_known=True,
        localization_tracking=True,
        localization_map_id="greenhouse_01",
        navigation_known=True,
        navigation_ready=True,
        navigation_site_id="greenhouse_01",
        navigation_site_revision="v1",
        navigation_site_hash="site-content-hash",
        navigation_map_identity_match=True,
        safety_known=True,
        motion_enabled=True,
        estop_latched=False,
        chassis_known=True,
        chassis_connected=True,
    )


def test_all_required_evidence_ready_allows_navigation():
    result = evaluate_navigation_readiness(all_ready())
    assert result.ready
    assert result.blocker_codes == ()
    assert result.map_id == "greenhouse_01"
    assert result.map_version_id == "v1"


def test_unknown_health_is_fail_closed():
    result = evaluate_navigation_readiness(replace(all_ready(), health_known=False))
    assert not result.ready
    assert result.blocker_codes == ("SYSTEM_HEALTH_UNKNOWN",)


def test_required_health_error_blocks_navigation():
    result = evaluate_navigation_readiness(replace(all_ready(), health_ok=False))
    assert not result.ready
    assert result.blocker_codes == ("SYSTEM_HEALTH_BLOCKED",)


def test_missing_active_map_is_fail_closed():
    result = evaluate_navigation_readiness(
        replace(
            all_ready(),
            map_known=False,
            map_ready=False,
            map_id="",
            map_version_id="",
            map_hash="",
        )
    )
    assert not result.ready
    assert result.blocker_codes == ("ACTIVE_MAP_UNKNOWN",)


def test_explicit_no_active_tombstone_revokes_authoritative_map_identity():
    known = authoritative_map_known(
        received=True,
        state=0,
        unknown_state=0,
        active=False,
        valid=False,
    )
    result = evaluate_navigation_readiness(
        replace(
            all_ready(),
            map_known=known,
            map_ready=False,
            map_id="",
            map_version_id="",
            map_hash="",
        )
    )
    assert not known
    assert not result.ready
    assert result.blocker_codes == ("ACTIVE_MAP_UNKNOWN",)


def test_received_invalid_or_inactive_map_is_known_but_not_ready():
    assert authoritative_map_known(
        received=True,
        state=4,
        unknown_state=0,
        active=False,
        valid=False,
    )
    assert authoritative_map_known(
        received=True,
        state=3,
        unknown_state=0,
        active=False,
        valid=True,
    )
    assert not authoritative_map_known(
        received=False,
        state=0,
        unknown_state=0,
        active=False,
        valid=False,
    )


def test_non_ready_active_map_blocks_navigation():
    result = evaluate_navigation_readiness(replace(all_ready(), map_ready=False))
    assert not result.ready
    assert result.blocker_codes == ("ACTIVE_MAP_NOT_READY",)


def test_unknown_localization_is_fail_closed():
    result = evaluate_navigation_readiness(
        replace(all_ready(), localization_known=False, localization_tracking=False)
    )
    assert not result.ready
    assert result.blocker_codes == ("LOCALIZATION_UNKNOWN",)


def test_non_tracking_localization_blocks_navigation():
    result = evaluate_navigation_readiness(
        replace(all_ready(), localization_tracking=False)
    )
    assert not result.ready
    assert result.blocker_codes == ("LOCALIZATION_NOT_TRACKING",)


def test_localization_must_match_active_map():
    result = evaluate_navigation_readiness(
        replace(all_ready(), localization_map_id="greenhouse_02")
    )
    assert not result.ready
    assert result.blocker_codes == ("LOCALIZATION_MAP_MISMATCH",)


def test_unknown_navigation_runtime_is_fail_closed():
    result = evaluate_navigation_readiness(
        replace(all_ready(), navigation_known=False, navigation_ready=False)
    )
    assert not result.ready
    assert result.blocker_codes == ("NAVIGATION_UNKNOWN",)


def test_non_ready_navigation_runtime_blocks_navigation():
    result = evaluate_navigation_readiness(replace(all_ready(), navigation_ready=False))
    assert not result.ready
    assert result.blocker_codes == ("NAVIGATION_NOT_ACTIVE",)


def test_navigation_runtime_site_identity_must_match_active_site():
    result = evaluate_navigation_readiness(
        replace(all_ready(), navigation_site_revision="v2")
    )
    assert not result.ready
    assert result.blocker_codes == ("NAVIGATION_MAP_MISMATCH",)


def test_navigation_runtime_rejects_localization_binding_mismatch():
    result = evaluate_navigation_readiness(
        replace(all_ready(), navigation_map_identity_match=False)
    )
    assert not result.ready
    assert result.blocker_codes == ("NAVIGATION_MAP_MISMATCH",)


def test_unknown_safety_is_fail_closed():
    result = evaluate_navigation_readiness(replace(all_ready(), safety_known=False))
    assert not result.ready
    assert result.blocker_codes == ("SAFETY_UNKNOWN",)


def test_motion_must_be_explicitly_enabled():
    result = evaluate_navigation_readiness(replace(all_ready(), motion_enabled=False))
    assert not result.ready
    assert result.blocker_codes == ("MOTION_DISABLED",)


def test_latched_estop_blocks_even_when_motion_flag_is_true():
    result = evaluate_navigation_readiness(replace(all_ready(), estop_latched=True))
    assert not result.ready
    assert result.blocker_codes == ("ESTOP_LATCHED",)


def test_unknown_chassis_is_fail_closed():
    result = evaluate_navigation_readiness(
        replace(all_ready(), chassis_known=False, chassis_connected=False)
    )
    assert not result.ready
    assert result.blocker_codes == ("CHASSIS_UNKNOWN",)


def test_disconnected_chassis_blocks_navigation():
    result = evaluate_navigation_readiness(replace(all_ready(), chassis_connected=False))
    assert not result.ready
    assert result.blocker_codes == ("CHASSIS_DISCONNECTED",)


def test_blockers_have_deterministic_system_to_actuator_order():
    result = evaluate_navigation_readiness(
        Evidence(
            health_known=False,
            health_ok=False,
            map_known=False,
            map_ready=False,
            map_id="",
            map_version_id="",
            map_hash="",
            localization_known=False,
            localization_tracking=False,
            localization_map_id="",
            navigation_known=False,
            navigation_ready=False,
            navigation_site_id="",
            navigation_site_revision="",
            navigation_site_hash="",
            navigation_map_identity_match=False,
            safety_known=False,
            motion_enabled=False,
            estop_latched=True,
            chassis_known=False,
            chassis_connected=False,
        )
    )
    assert result.blocker_codes == (
        "SYSTEM_HEALTH_UNKNOWN",
        "ACTIVE_MAP_UNKNOWN",
        "LOCALIZATION_UNKNOWN",
        "NAVIGATION_UNKNOWN",
        "SAFETY_UNKNOWN",
        "CHASSIS_UNKNOWN",
    )
