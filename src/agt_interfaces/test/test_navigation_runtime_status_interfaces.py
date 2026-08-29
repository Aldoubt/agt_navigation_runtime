from agt_interfaces.msg import NavigationRuntimeStatus


def test_navigation_runtime_status_defaults_fail_closed():
    message = NavigationRuntimeStatus()

    assert message.state == NavigationRuntimeStatus.STATE_UNKNOWN
    assert message.site_id == ""
    assert message.site_revision == ""
    assert not message.map_server_active
    assert not message.planner_server_active
    assert not message.controller_server_active
    assert not message.bt_navigator_active
    assert not message.waypoint_follower_active
    assert not message.collision_monitor_active
    assert not message.localization_bound
    assert not message.map_identity_known
    assert not message.map_identity_match
    assert message.blocker_codes == []
    assert message.blocker_messages == []


def test_navigation_runtime_status_ready_payload_round_trip_fields():
    message = NavigationRuntimeStatus()
    message.state = NavigationRuntimeStatus.STATE_READY
    message.site_id = "greenhouse_a"
    message.site_revision = "r01"
    message.site_hash = "a" * 64
    message.map_server_active = True
    message.planner_server_active = True
    message.smoother_server_active = True
    message.controller_server_active = True
    message.behavior_server_active = True
    message.bt_navigator_active = True
    message.waypoint_follower_active = True
    message.collision_monitor_active = True
    message.localization_bound = True
    message.map_identity_known = True
    message.map_identity_match = True
    message.localization_map_id = "greenhouse_a"
    message.localization_map_hash = "b" * 64

    assert message.state == NavigationRuntimeStatus.STATE_READY
    assert message.site_id == "greenhouse_a"
    assert message.site_revision == "r01"
    assert message.controller_server_active
    assert message.localization_bound
    assert message.map_identity_match
