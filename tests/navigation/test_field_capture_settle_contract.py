from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
SERVER = (ROOT / "src/agt_navigation/scripts/field_capture_capability_server.py").read_text()
LAUNCH = (ROOT / "src/agt_field_commissioning/launch/field_navigation.launch.py").read_text()


def test_field_capture_requires_settle_before_capture():
    assert '"WAITING_FOR_SETTLE"' in SERVER
    assert '"SETTLED"' in SERVER
    assert '"CAPTURING"' in SERVER
    assert SERVER.index('"WAITING_FOR_SETTLE"') < SERVER.index('"CAPTURING"')
    assert "field_capture_settle_enabled" in SERVER
    assert "Odometry" in SERVER


def test_field_navigation_defaults_to_fail_closed_settle_gate():
    assert 'DeclareLaunchArgument("field_capture_settle_enabled", default_value="true")' in LAUNCH
    assert 'DeclareLaunchArgument("field_capture_settle_odom_topic", default_value="/agt/odometry/odometry")' in LAUNCH
    assert 'DeclareLaunchArgument("field_capture_continue_on_failure", default_value="false")' in LAUNCH
