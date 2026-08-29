from agt_system_manager.readiness import Evidence, evaluate_navigation_readiness


def test_startup_waits_for_required_runtime_evidence():
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
            navigation_identity_known=False,
            navigation_map_identity_match=False,
            safety_known=False,
            motion_enabled=False,
            estop_latched=False,
            chassis_known=False,
            chassis_connected=False,
        )
    )
    assert result.ready is False
    assert "SYSTEM_HEALTH_UNKNOWN" in result.blocker_codes
    assert "ACTIVE_MAP_UNKNOWN" in result.blocker_codes
    assert "LOCALIZATION_UNKNOWN" in result.blocker_codes
    assert "NAVIGATION_UNKNOWN" in result.blocker_codes
    assert "SAFETY_UNKNOWN" in result.blocker_codes
    assert "CHASSIS_UNKNOWN" in result.blocker_codes
