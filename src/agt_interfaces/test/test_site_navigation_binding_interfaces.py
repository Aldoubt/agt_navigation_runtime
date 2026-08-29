from agt_interfaces.msg import SiteNavigationBinding


def test_site_navigation_binding_defaults_fail_closed():
    message = SiteNavigationBinding()

    assert message.state == SiteNavigationBinding.STATE_UNKNOWN
    assert message.site_id == ""
    assert message.site_revision == ""
    assert message.navigation_yaml == ""
    assert message.navigation_image == ""
    assert message.localization_pcd == ""
    assert message.blocker_codes == []
    assert message.messages == []


def test_site_navigation_binding_ready_payload_round_trip_fields():
    message = SiteNavigationBinding()
    message.state = SiteNavigationBinding.STATE_READY
    message.site_id = "greenhouse_a"
    message.site_revision = "r01"
    message.site_hash = "a" * 64
    message.manifest_sha256 = "b" * 64
    message.navigation_yaml = "/opt/agt/sites/greenhouse_a/r01/map/navigation.yaml"
    message.navigation_yaml_sha256 = "c" * 64
    message.navigation_image = "/opt/agt/sites/greenhouse_a/r01/map/navigation.pgm"
    message.navigation_image_sha256 = "d" * 64
    message.localization_pcd = "/opt/agt/sites/greenhouse_a/r01/map/localization_map.pcd"
    message.localization_pcd_sha256 = "e" * 64
    message.processing_record = ""

    assert message.state == SiteNavigationBinding.STATE_READY
    assert message.site_id == "greenhouse_a"
    assert message.site_revision == "r01"
    assert message.blocker_codes == []
