import importlib.util
from pathlib import Path

from agt_interfaces.msg import LocalizationStatus
from nav2_msgs.srv import ManageLifecycleNodes


SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "localization_navigation_gate.py"
SPEC = importlib.util.spec_from_file_location("localization_navigation_gate", SCRIPT)
GATE = importlib.util.module_from_spec(SPEC)


def _load_gate():
    SPEC.loader.exec_module(GATE)
    return GATE


def test_gate_requires_fresh_accepted_tracking_status():
    gate = _load_gate()
    status = LocalizationStatus()
    assert not gate.localization_status_is_ready(status)
    status.state = LocalizationStatus.STATE_TRACKING
    status.pose_valid = True
    status.localization_accepted = True
    status.error_code = LocalizationStatus.ERROR_NONE
    assert gate.localization_status_is_ready(status)
    status.status_stale = True
    assert not gate.localization_status_is_ready(status)


def test_gate_keeps_ten_second_default_freshness_window():
    source = SCRIPT.read_text(encoding="utf-8")
    assert 'declare_parameter("localization_status_timeout", 10.0)' in source


class _Logger:
    def error(self, *_args):
        pass

    def info(self, *_args):
        pass

    def warn(self, *_args):
        pass


class _GateState:
    def __init__(self, command):
        self._in_flight = True
        self._pending_command = command
        self._nav_started = False
        self._nav_paused = False
        self._recovery_reset_required = False
        self._logger = _Logger()

    def get_logger(self):
        return self._logger


class _Future:
    def __init__(self, *, success=None, error=None):
        self._success = success
        self._error = error

    def result(self):
        if self._error is not None:
            raise self._error
        response = ManageLifecycleNodes.Response()
        response.success = self._success
        return response


def test_rejected_startup_is_fail_closed_and_requires_reset():
    gate_module = _load_gate()
    state = _GateState(ManageLifecycleNodes.Request.STARTUP)
    gate_module.LocalizationNavigationGate._command_done(state, _Future(success=False))
    assert not state._nav_started
    assert state._recovery_reset_required


def test_lifecycle_service_exception_is_fail_closed():
    gate_module = _load_gate()
    state = _GateState(ManageLifecycleNodes.Request.RESUME)
    gate_module.LocalizationNavigationGate._command_done(
        state, _Future(error=RuntimeError("service unavailable"))
    )
    assert not state._nav_started
    assert state._recovery_reset_required
