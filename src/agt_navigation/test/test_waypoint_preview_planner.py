import math
from pathlib import Path
import sys

from geometry_msgs.msg import Pose, PoseStamped
from nav_msgs.msg import Path as NavPath


SCRIPT_DIR = Path(__file__).resolve().parents[1] / "scripts"
sys.path.insert(0, str(SCRIPT_DIR))

from waypoint_preview_planner import append_segment, valid_pose  # noqa: E402


def _pose(x, y):
    pose = Pose()
    pose.position.x = x
    pose.position.y = y
    pose.orientation.w = 1.0
    return pose


def _segment(*coordinates):
    path = NavPath()
    for x, y in coordinates:
        stamped = PoseStamped()
        stamped.pose = _pose(x, y)
        path.poses.append(stamped)
    return path


def test_pose_validation_rejects_non_finite_values():
    assert valid_pose(_pose(1.0, 2.0))
    invalid = _pose(math.nan, 2.0)
    assert not valid_pose(invalid)


def test_segments_join_without_duplicate_boundary_pose():
    joined = []
    append_segment(joined, _segment((0.0, 0.0), (1.0, 0.0)))
    append_segment(joined, _segment((1.0, 0.0), (2.0, 0.0)))
    assert [(p.pose.position.x, p.pose.position.y) for p in joined] == [
        (0.0, 0.0),
        (1.0, 0.0),
        (2.0, 0.0),
    ]
