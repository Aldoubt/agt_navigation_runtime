from pathlib import Path
import re


ROOT = Path(__file__).resolve().parents[2]
SERVER = ROOT / "src" / "agt_navigation" / "scripts" / "field_capture_capability_server.py"
NAV_LAUNCH = ROOT / "src" / "agt_navigation" / "launch" / "navigation.launch.py"
FIELD_LAUNCH = ROOT / "src" / "agt_field_commissioning" / "launch" / "field_navigation.launch.py"


def test_field_capture_server_defaults_to_fail_closed():
    text = SERVER.read_text(encoding="utf-8")
    assert re.search(
        r'declare_parameter\(\s*"field_capture_continue_on_failure",\s*False\s*\)',
        text,
    ), "field capture server must stop the inspection after retry exhaustion by default"


def test_navigation_launch_defaults_to_fail_closed():
    text = NAV_LAUNCH.read_text(encoding="utf-8")
    assert 'DeclareLaunchArgument("field_capture_continue_on_failure", default_value="false")' in text


def test_field_navigation_launch_defaults_to_fail_closed():
    text = FIELD_LAUNCH.read_text(encoding="utf-8")
    assert 'DeclareLaunchArgument("field_capture_continue_on_failure", default_value="false")' in text


def test_continue_mode_remains_explicitly_configurable():
    server = SERVER.read_text(encoding="utf-8")
    nav_launch = NAV_LAUNCH.read_text(encoding="utf-8")
    field_launch = FIELD_LAUNCH.read_text(encoding="utf-8")

    assert "self.field_capture_continue_on_failure" in server
    assert 'LaunchConfiguration("field_capture_continue_on_failure")' in nav_launch
    assert 'LaunchConfiguration("field_capture_continue_on_failure")' in field_launch
