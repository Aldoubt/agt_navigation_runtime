import importlib.util
from pathlib import Path

from agt_interfaces.msg import LocalizationStatus
from nav2_msgs.srv import ManageLifecycleNodes


SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "localization_navigation_gate.py"
SPEC = importlib.util.spec_from_file_location("localization_navigation_gate", SCRIPT)
GATE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(GATE)


def test_gate_requires_accepted_tracking_status():
    status = LocalizationStatus()
    assert not GATE.localization_status_is_ready(status)

    status.state = LocalizationStatus.STATE_TRACKING
    status.pose_valid = True
    status.localization_accepted = True
    status.error_code = LocalizationStatus.ERROR_NONE
    assert GATE.localization_status_is_ready(status)

    status.status_stale = True
    assert not GATE.localization_status_is_ready(status)


def test_gate_default_freshness_window_matches_navigation_launch():
    source = SCRIPT.read_text(encoding="utf-8")
    assert 'declare_parameter("localization_status_timeout", 10.0)' in source
    launch = SCRIPT.parents[1] / "launch" / "navigation.launch.py"
    assert 'DeclareLaunchArgument("localization_status_timeout", default_value="10.0")' in launch.read_text(encoding="utf-8")


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


def test_rejected_startup_enters_reset_recovery():
    gate = _GateState(ManageLifecycleNodes.Request.STARTUP)
    GATE.LocalizationNavigationGate._command_done(gate, _Future(success=False))
    assert not gate._in_flight
    assert gate._pending_command is None
    assert gate._recovery_reset_required


def test_lifecycle_service_exception_remains_fail_closed():
    gate = _GateState(ManageLifecycleNodes.Request.RESUME)
    GATE.LocalizationNavigationGate._command_done(
        gate, _Future(error=RuntimeError("service unavailable"))
    )
    assert not gate._nav_started
    assert gate._recovery_reset_required


def test_reset_failure_does_not_leave_gate_stuck_in_reset_loop():
    gate = _GateState(ManageLifecycleNodes.Request.RESET)
    gate._recovery_reset_required = True
    GATE.LocalizationNavigationGate._command_done(gate, _Future(success=False))
    assert not gate._recovery_reset_required
