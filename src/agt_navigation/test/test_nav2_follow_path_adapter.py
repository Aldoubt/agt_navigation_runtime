from types import SimpleNamespace

from action_msgs.msg import GoalStatus
from builtin_interfaces.msg import Time

from agt_navigation.nav2_follow_path_adapter import (
    Nav2FollowPathTrackerAdapter,
    runtime_path_to_nav_path,
)
from agt_navigation.route_runtime import RuntimePath, RuntimePathPoint


class ImmediateFuture:
    def __init__(self, value):
        self._value = value

    def result(self):
        return self._value

    def add_done_callback(self, callback):
        callback(self)


class FakeGoalHandle:
    def __init__(self, *, accepted=True, status=GoalStatus.STATUS_SUCCEEDED, error_code=0):
        self.accepted = accepted
        self.cancel_count = 0
        self._wrapped = SimpleNamespace(
            status=status,
            result=SimpleNamespace(error_code=error_code, error_msg=""),
        )

    def get_result_async(self):
        return ImmediateFuture(self._wrapped)

    def cancel_goal_async(self):
        self.cancel_count += 1
        return ImmediateFuture(SimpleNamespace(goals_canceling=[1]))


class FakeActionClient:
    def __init__(self, handle):
        self.handle = handle
        self.goals = []
        self.feedback_callbacks = []
        self.wait_count = 0

    def wait_for_server(self, timeout_sec):
        self.wait_count += 1
        return True

    def send_goal_async(self, goal, feedback_callback=None):
        self.goals.append(goal)
        self.feedback_callbacks.append(feedback_callback)
        return ImmediateFuture(self.handle)


def _path(direction="F"):
    return RuntimePath(
        frame_id="odom",
        route_id="route_demo",
        revision=1,
        segment_id="s000",
        direction=direction,
        alignment_generation=4,
        points=(
            RuntimePathPoint(0.0, 0.0, 0.0, direction, 0.2, "row_0", ""),
            RuntimePathPoint(1.0, 0.0, 0.0, direction, 0.2, "row_0", "stop_0"),
        ),
    )


def test_runtime_path_becomes_odom_nav_path():
    message = runtime_path_to_nav_path(_path(), Time(sec=12))

    assert message.header.frame_id == "odom"
    assert message.header.stamp.sec == 12
    assert len(message.poses) == 2
    assert all(pose.header.frame_id == "odom" for pose in message.poses)
    assert message.poses[1].pose.position.x == 1.0


def test_follow_path_goal_selects_controller_by_route_direction():
    client = FakeActionClient(FakeGoalHandle())
    adapter = Nav2FollowPathTrackerAdapter(
        action_client=client,
        controller_id_forward="RouteForward",
        controller_id_reverse="RouteReverse",
        goal_checker_id="RouteGoalChecker",
        stamp_provider=lambda: Time(sec=1),
    )

    forward = adapter.build_goal(_path("F"))
    reverse = adapter.build_goal(_path("R"))

    assert forward.path.header.frame_id == "odom"
    assert forward.controller_id == "RouteForward"
    assert reverse.controller_id == "RouteReverse"
    assert forward.goal_checker_id == "RouteGoalChecker"


def test_follow_path_adapter_emits_terminal_success_without_global_planning():
    events = []
    client = FakeActionClient(FakeGoalHandle())
    adapter = Nav2FollowPathTrackerAdapter(
        action_client=client,
        controller_id_forward="RouteForward",
        feedback_sink=events.append,
        stamp_provider=lambda: Time(),
    )

    adapter.start(_path("F"))

    assert client.wait_count == 1
    assert len(client.goals) == 1
    assert client.goals[0].path.header.frame_id == "odom"
    assert events[-1].status == "SUCCEEDED"
    assert events[-1].active_segment_id == "s000"
    assert adapter.active_segment_id == ""


def test_follow_path_rejection_is_reported_as_tracker_failure():
    events = []
    client = FakeActionClient(FakeGoalHandle(accepted=False))
    adapter = Nav2FollowPathTrackerAdapter(
        action_client=client,
        feedback_sink=events.append,
        stamp_provider=lambda: Time(),
    )

    adapter.start(_path())

    assert events[-1].status == "FAILED"
    assert "rejected" in events[-1].failure_reason.lower()
    assert adapter.active_segment_id == ""
