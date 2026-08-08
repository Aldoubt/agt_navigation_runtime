from pathlib import Path
from types import SimpleNamespace

from action_msgs.msg import GoalStatus
from builtin_interfaces.msg import Time

from agt_navigation.nav2_follow_path_adapter import (
    Nav2FollowPathTrackerAdapter,
    runtime_path_to_nav_path,
)
from agt_navigation.route_runtime import (
    MapOdomSnapshot,
    RouteAsset,
    RouteNavigationCore,
    RoutePoint,
    RouteSegment,
    RuntimePath,
    RuntimePathPoint,
)


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
        self.handles = list(handle) if isinstance(handle, (list, tuple)) else [handle]
        self.goals = []
        self.feedback_callbacks = []
        self.wait_count = 0

    def wait_for_server(self, timeout_sec):
        self.wait_count += 1
        return True

    def send_goal_async(self, goal, feedback_callback=None):
        self.goals.append(goal)
        self.feedback_callbacks.append(feedback_callback)
        return ImmediateFuture(self.handles.pop(0))


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


def _asset():
    s0_points = (
        RoutePoint(0, "s000", 10.0, 0.0, 0.0, "F", 0.3, 0.0, 1.0, "row_0", ""),
        RoutePoint(1, "s000", 11.0, 0.0, 0.0, "F", 0.3, 0.0, 1.0, "row_0", "stop_a"),
    )
    s1_points = (
        RoutePoint(2, "s001", 20.0, 0.0, 3.141592653589793, "R", 0.2, 0.0, 1.0, "headland", ""),
        RoutePoint(3, "s001", 21.0, 0.0, 3.141592653589793, "R", 0.2, 0.0, 1.0, "headland", "stop_b"),
    )
    return RouteAsset(
        route_id="route_demo",
        revision=1,
        frame_id="map",
        map_id="facility_a",
        map_version_id="map_v1",
        map_content_sha256="sha256:" + "a" * 64,
        vehicle_profile_sha256="sha256:" + "b" * 64,
        route_dir=Path("/tmp/route_demo"),
        segments=(
            RouteSegment("s000", "F", s0_points, ("stop_a",)),
            RouteSegment("s001", "R", s1_points, ("stop_b",)),
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


def test_route_core_drives_forward_and_reverse_follow_path_segments_without_planner():
    client = FakeActionClient([FakeGoalHandle(), FakeGoalHandle()])
    completions = []
    holder = {}

    def sink(feedback):
        completion = holder["core"].handle_tracker_feedback(feedback)
        if completion is not None:
            completions.append(completion)

    adapter = Nav2FollowPathTrackerAdapter(
        action_client=client,
        controller_id_forward="RouteForward",
        controller_id_reverse="RouteReverse",
        feedback_sink=sink,
        stamp_provider=lambda: Time(),
    )
    core = RouteNavigationCore(_asset(), adapter)
    holder["core"] = core

    core.start(MapOdomSnapshot(10.0, 0.0, 0.0, generation=1))

    assert core.state == "COMPLETED"
    assert [goal.controller_id for goal in client.goals] == ["RouteForward", "RouteReverse"]
    assert all(goal.path.header.frame_id == "odom" for goal in client.goals)
    assert [item.segment_id for item in completions] == ["s000", "s001"]
    assert completions[-1].route_complete is True
    assert core.metrics.global_planner_requests == 0
