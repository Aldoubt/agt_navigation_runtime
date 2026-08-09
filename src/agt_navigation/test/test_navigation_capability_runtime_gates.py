import importlib.util
from pathlib import Path
import threading
import time

from action_msgs.msg import GoalStatus
from agt_interfaces.action import ExecuteWaypointTask
from agt_interfaces.msg import LocalizationStatus, TaskReadiness
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus, KeyValue
from nav2_msgs.action import FollowPath
import pytest
import rclpy
from rclpy.action import ActionClient, ActionServer, CancelResponse
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.parameter import Parameter


HELPERS_PATH = Path(__file__).with_name("test_navigation_capability_server.py")
HELPERS_SPEC = importlib.util.spec_from_file_location(
    "navigation_capability_test_helpers", HELPERS_PATH
)
HELPERS = importlib.util.module_from_spec(HELPERS_SPEC)
HELPERS_SPEC.loader.exec_module(HELPERS)
SERVER = HELPERS.SERVER


def _wait(future, timeout=4.0):
    deadline = time.monotonic() + timeout
    while not future.done() and time.monotonic() < deadline:
        time.sleep(0.01)
    assert future.done()
    return future.result()


def _wait_until(predicate, timeout=2.0):
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        if predicate():
            return
        time.sleep(0.01)
    assert predicate()


def _safety_message(*, ready: bool, estop: bool = False) -> DiagnosticArray:
    message = DiagnosticArray()
    status = DiagnosticStatus()
    status.name = "agt_safety/tracked_controller"
    status.values = [
        KeyValue(key="motion_enabled", value="true" if ready else "false"),
        KeyValue(key="estop_latched", value="true" if estop else "false"),
    ]
    message.status = [status]
    return message


def _localization_message(*, ready: bool, generation=None) -> LocalizationStatus:
    message = LocalizationStatus()
    message.state = LocalizationStatus.STATE_TRACKING
    message.pose_valid = bool(ready)
    message.localization_accepted = bool(ready)
    message.error_code = LocalizationStatus.ERROR_NONE
    message.status_stale = False
    message.map_id = "site"
    message.map_hash = "sha256:pcd"
    message.correction_generation = (1 if ready else 0) if generation is None else generation
    return message


def _task_readiness_message(*, ready: bool) -> TaskReadiness:
    message = TaskReadiness()
    message.ready = bool(ready)
    message.map_id = "site"
    message.map_version_id = "map_v1"
    return message


class RuntimeHarness:
    def __init__(
        self,
        tmp_path,
        *,
        require_safety=False,
        require_localization=False,
        require_task_readiness=False,
        request_id="route_runtime_gate",
    ):
        self.task, self.profile, _version = HELPERS._prepare_assets(tmp_path)
        if not rclpy.ok():
            rclpy.init()

        self.server = SERVER.NavigationCapabilityServer(
            route_snapshot_provider=lambda: HELPERS.MapOdomSnapshot(
                10.0, 20.0, 0.0, generation=1
            ),
            parameter_overrides=[
                Parameter("require_map", value=False),
                Parameter("require_safety_ready", value=bool(require_safety)),
                Parameter(
                    "require_localization_valid", value=bool(require_localization)
                ),
                Parameter(
                    "require_task_readiness", value=bool(require_task_readiness)
                ),
                Parameter("maps_root", value=str(tmp_path)),
                Parameter("execution_vehicle_profile", value=str(self.profile)),
                Parameter("route_controller_id_forward", value="RouteForward"),
                Parameter("route_controller_id_reverse", value="RouteReverse"),
                Parameter("safety_status_timeout", value=5.0),
                Parameter("localization_status_timeout", value=5.0),
                Parameter("task_readiness_timeout", value=5.0),
            ],
        )
        HELPERS._set_active_map(self.server)
        if require_safety:
            self.server._safety_callback(_safety_message(ready=True))
        if require_localization:
            self.server._localization_callback(_localization_message(ready=True))
        if require_task_readiness:
            self.server._task_readiness_callback(_task_readiness_message(ready=True))

        self.child_started = threading.Event()
        self.child_canceled = threading.Event()
        self.child_node = Node(f"mock_follow_path_{request_id}")

        def execute_follow_path(goal_handle):
            self.child_started.set()
            deadline = time.monotonic() + 3.0
            while time.monotonic() < deadline:
                if goal_handle.is_cancel_requested:
                    self.child_canceled.set()
                    goal_handle.canceled()
                    return FollowPath.Result()
                time.sleep(0.005)
            goal_handle.abort()
            return FollowPath.Result()

        self.child_server = ActionServer(
            self.child_node,
            FollowPath,
            "follow_path",
            execute_follow_path,
            cancel_callback=lambda _goal: CancelResponse.ACCEPT,
        )
        self.client_node = Node(f"route_runtime_gate_client_{request_id}")
        self.client = ActionClient(
            self.client_node,
            ExecuteWaypointTask,
            "/agt/navigation/execute_waypoint_task",
        )
        self.executor = MultiThreadedExecutor(num_threads=6)
        for value in (self.server, self.child_node, self.client_node):
            self.executor.add_node(value)
        self.thread = threading.Thread(target=self.executor.spin, daemon=True)
        self.thread.start()
        assert self.client.wait_for_server(timeout_sec=2.0)
        self.handle = _wait(
            self.client.send_goal_async(HELPERS._formal_request(self.task, request_id))
        )
        assert self.handle.accepted
        assert self.child_started.wait(timeout=2.0)
        _wait_until(self._child_goal_handle_ready)

    def _child_goal_handle_ready(self):
        executor = self.server._route_executor
        if executor is None or executor._core is None:
            return False
        tracker = executor._core.tracker
        return getattr(tracker, "_goal_handle", None) is not None

    def result(self):
        return _wait(self.handle.get_result_async())

    def close(self):
        self.executor.shutdown(timeout_sec=2.0)
        self.thread.join(timeout=2.0)
        self.child_server.destroy()
        for value in (self.client_node, self.child_node, self.server):
            value.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


def test_parent_cancel_reaches_active_route_follow_path_child(tmp_path):
    harness = RuntimeHarness(tmp_path, request_id="parent_cancel")
    try:
        response = _wait(harness.handle.cancel_goal_async())
        assert response.goals_canceling
        wrapped = harness.result()

        assert wrapped.status == GoalStatus.STATUS_CANCELED
        assert not wrapped.result.success
        assert wrapped.result.blocker_code == "CANCELED"
        assert harness.child_canceled.wait(timeout=2.0)
    finally:
        harness.close()


@pytest.mark.parametrize(
    "gate_name,trigger,expected_blocker",
    [
        (
            "safety",
            lambda server: server._safety_callback(_safety_message(ready=False)),
            "SAFETY_NOT_READY",
        ),
        (
            "localization",
            lambda server: server._localization_callback(
                _localization_message(ready=False)
            ),
            "LOCALIZATION_NOT_READY",
        ),
        (
            "task_readiness",
            lambda server: server._task_readiness_callback(
                _task_readiness_message(ready=False)
            ),
            "TASK_READINESS_NOT_READY",
        ),
    ],
)
def test_runtime_gate_loss_fails_parent_and_cancels_follow_path(
    tmp_path, gate_name, trigger, expected_blocker
):
    harness = RuntimeHarness(
        tmp_path,
        require_safety=gate_name == "safety",
        require_localization=gate_name == "localization",
        require_task_readiness=gate_name == "task_readiness",
        request_id=f"gate_{gate_name}",
    )
    try:
        trigger(harness.server)
        wrapped = harness.result()

        assert wrapped.status == GoalStatus.STATUS_ABORTED
        assert not wrapped.result.success
        # The parent Action may summarize the backend failure, but the structured
        # final NavigationSessionStatus must preserve the runtime gate that caused
        # motion to stop. This is the authoritative diagnostic identity.
        assert wrapped.result.final_status.blocker_code == expected_blocker
        assert wrapped.result.final_status.technical_message
        assert harness.child_canceled.wait(timeout=2.0)
    finally:
        harness.close()


def test_route_generation_zero_fails_closed_and_rejected_status_cancels(tmp_path):
    if not rclpy.ok():
        rclpy.init()
    server = SERVER.NavigationCapabilityServer(
        route_snapshot_provider=lambda: HELPERS.MapOdomSnapshot(
            10.0, 20.0, 0.0, generation=1
        ),
        parameter_overrides=[
            Parameter("require_map", value=False),
            Parameter("require_safety_ready", value=False),
            Parameter("require_localization_valid", value=True),
            Parameter("require_task_readiness", value=False),
            Parameter("maps_root", value=str(tmp_path)),
            Parameter("localization_status_timeout", value=5.0),
        ],
    )
    try:
        class FakeExecutor:
            def fail(self, reason):
                self.reason = reason

            def cancel(self):
                pass

        server._localization_callback(_localization_message(ready=True, generation=0))
        server._route_executor = FakeExecutor()
        server._active = True
        problem = server._runtime_gate_problem()
        assert problem.code == "ROUTE_ALIGNMENT_GENERATION_UNAVAILABLE"

        server._localization_callback(_localization_message(ready=False, generation=7))
        assert not server._localization_is_ready()
        assert server._localization_correction_generation == 7
    finally:
        server.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()
