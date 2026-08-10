import importlib.util
from pathlib import Path

from agt_interfaces.msg import LocalizationStatus
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus, KeyValue


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


def test_sensor_summary_guard_requires_fresh_required_stream_evidence():
    array = DiagnosticArray()
    unrelated = DiagnosticStatus()
    unrelated.name = "other/component"
    array.status = [unrelated]
    assert SAFETY.sensor_summary_is_ready(array) is None

    summary = DiagnosticStatus()
    summary.name = SAFETY.SENSOR_SUMMARY_NAME
    summary.level = DiagnosticStatus.OK
    summary.values = [KeyValue(key="required_streams_healthy", value="true")]
    array.status = [summary]
    assert SAFETY.sensor_summary_is_ready(array) is True

    summary.level = DiagnosticStatus.ERROR
    assert SAFETY.sensor_summary_is_ready(array) is False

    summary.level = DiagnosticStatus.OK
    summary.values = [KeyValue(key="required_streams_healthy", value="false")]
    assert SAFETY.sensor_summary_is_ready(array) is False


def test_safety_contract_exports_authoritative_estop_navigation_and_sensor_readiness():
    source = SCRIPT.read_text(encoding="utf-8")
    assert '"localization_status_timeout", 10.0' in source
    assert '"require_sensor_input_ready", False' in source
    assert '"sensor_status_timeout", 1.5' in source
    assert '"sensor_input_unhealthy"' in source
    assert 'key="emergency_stop"' in source
    assert 'key="navigation_ready"' in source
    assert 'key="sensor_input_ready"' in source
    assert "MultiThreadedExecutor" in source


def test_bunker_config_requires_sensor_gate_and_localization_window():
    config = SCRIPT.parents[1] / "config" / "bunker_safety.yaml"
    text = config.read_text(encoding="utf-8")
    assert "localization_status_timeout: 10.0" in text
    assert "require_sensor_input_ready: true" in text
    assert "sensor_status_timeout: 1.5" in text
    assert "sensor_summary_name: agt_sensor_monitor/summary" in text
