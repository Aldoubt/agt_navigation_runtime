from agt_interfaces.action import ExecuteWaypointTask
from geometry_msgs.msg import PoseStamped
from rclpy.serialization import deserialize_message, serialize_message


def _round_trip(message):
    return deserialize_message(serialize_message(message), type(message))


def test_waypoint_task_goal_round_trip():
    message = ExecuteWaypointTask.Goal()
    message.map_id = "demo"
    message.map_version_id = "map_20260729_120000_abcdef12"
    message.task_group_id = "inspection_v01"
    message.task_revision = 3
    message.expected_content_sha256 = "sha256:" + "a" * 64
    message.client_request_id = "11111111-1111-4111-8111-111111111111"
    message.loop = True
    message.loop_count = 2
    pose = PoseStamped()
    pose.header.frame_id = "map"
    pose.pose.orientation.w = 1.0
    message.poses = [pose]
    output = _round_trip(message)
    assert output.map_id == message.map_id
    assert output.map_version_id == message.map_version_id
    assert output.task_group_id == message.task_group_id
    assert output.task_revision == 3
    assert output.expected_content_sha256 == message.expected_content_sha256
    assert output.client_request_id == message.client_request_id
    assert output.loop
    assert output.loop_count == 2
    assert output.poses[0].header.frame_id == "map"


def test_waypoint_task_result_and_feedback_round_trip():
    result = ExecuteWaypointTask.Result()
    result.success = False
    result.error_code = 42
    result.message = "missed waypoint"
    result.session_id = "session-1"
    result.blocker_code = "NAV2_FAILED"
    result.operator_message = "task failed"
    result.technical_message = "missed waypoint"
    result.missed_waypoints = [1, 3]
    output = _round_trip(result)
    assert list(output.missed_waypoints) == [1, 3]
    assert output.blocker_code == "NAV2_FAILED"

    feedback = ExecuteWaypointTask.Feedback()
    feedback.state = "RUNNING"
    feedback.loop_index = 0
    feedback.current_waypoint = 1
    feedback.total_waypoints = 4
    assert _round_trip(feedback).total_waypoints == 4
