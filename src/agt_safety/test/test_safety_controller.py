import importlib.util
from pathlib import Path

from agt_interfaces.msg import LocalizationStatus


SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "tracked_safety_controller.py"
SPEC = importlib.util.spec_from_file_location("tracked_safety_controller", SCRIPT)
SAFETY = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SAFETY)


def test_localization_guard_requires_accepted_tracking_state():
    status = LocalizationStatus()
    assert not SAFETY.localization_status_is_valid(status)

    status.state = LocalizationStatus.STATE_TRACKING
    status.pose_valid = True
    status.localization_accepted = True
    status.error_code = LocalizationStatus.ERROR_NONE
    assert SAFETY.localization_status_is_valid(status)

    status.status_stale = True
    assert not SAFETY.localization_status_is_valid(status)


def test_safety_contract_exports_authoritative_estop_and_navigation_readiness():
    source = SCRIPT.read_text(encoding="utf-8")
    assert '"localization_status_timeout", 10.0' in source
    assert 'key="emergency_stop"' in source
    assert 'key="navigation_ready"' in source
    assert "MultiThreadedExecutor" in source


def test_safety_default_window_exceeds_tracking_period_plus_timeout():
    config = SCRIPT.parents[1] / "config" / "bunker_safety.yaml"
    text = config.read_text(encoding="utf-8")
    assert "localization_status_timeout: 10.0" in text
