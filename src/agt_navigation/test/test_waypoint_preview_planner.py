import math
from pathlib import Path
import sys

from geometry_msgs.msg import Pose, PoseStamped
from nav_msgs.msg import Path as NavPath


SCRIPT_DIR = Path(__file__).resolve().parents[1] / "scripts"
sys.path.insert(0, str(SCRIPT_DIR))

from waypoint_preview_planner import (  # noqa: E402
    append_segment,
    planning_progress,
    valid_pose,
    validated_segment_timeout,
)


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


def test_preview_progress_reports_current_and_total_segments():
    assert planning_progress(1, 4) == "planning:1/3"
    assert planning_progress(3, 4) == "planning:3/3"


def test_preview_segment_timeout_must_be_positive_and_finite():
    assert validated_segment_timeout(30) == 30.0
    for value in (0, -1, math.inf, math.nan):
        try:
            validated_segment_timeout(value)
        except ValueError:
            continue
        raise AssertionError(f"invalid timeout accepted: {value}")
