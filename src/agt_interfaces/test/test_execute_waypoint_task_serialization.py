from agt_interfaces.action import ExecuteWaypointTask
from geometry_msgs.msg import PoseStamped
from rclpy.serialization import deserialize_message, serialize_message


def _round_trip(message):
    return deserialize_message(serialize_message(message), type(message))


def test_waypoint_task_goal_round_trip():
    message = ExecuteWaypointTask.Goal()
    message.task_file = "/runtime/maps/demo/task.json"
    message.loop = True
    message.loop_count = 2
    pose = PoseStamped()
    pose.header.frame_id = "map"
    pose.pose.orientation.w = 1.0
    message.poses = [pose]
    output = _round_trip(message)
    assert output.task_file == message.task_file
    assert output.loop
    assert output.loop_count == 2
    assert output.poses[0].header.frame_id == "map"


def test_waypoint_task_result_and_feedback_round_trip():
    result = ExecuteWaypointTask.Result()
    result.success = False
    result.error_code = 42
    result.message = "missed waypoint"
    result.missed_waypoints = [1, 3]
    output = _round_trip(result)
    assert list(output.missed_waypoints) == [1, 3]

    feedback = ExecuteWaypointTask.Feedback()
    feedback.state = "RUNNING"
    feedback.loop_index = 0
    feedback.current_waypoint = 1
    feedback.total_waypoints = 4
    assert _round_trip(feedback).total_waypoints == 4
