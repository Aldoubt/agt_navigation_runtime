import json
import math
from pathlib import Path
import sys

import pytest

PACKAGE_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PACKAGE_ROOT))

from agt_navigation.qt_task_chain import (  # noqa: E402
    TaskChainError,
    Waypoint,
    load_qt_task_chain,
    point_inside_map,
)


def _write(tmp_path, points):
    path = tmp_path / "task.json"
    path.write_text(json.dumps({"points": points}), encoding="utf-8")
    return path


def _point(name, x, y, theta=0.0):
    return {"name": name, "x": x, "y": y, "theta": theta, "type": "NavGoal"}


def test_loads_vendor_task_chain(tmp_path):
    points = load_qt_task_chain(
        _write(tmp_path, [_point("row_1", 1.0, 2.0), _point("row_2", 3.0, 4.0)])
    )
    assert [point.name for point in points] == ["row_1", "row_2"]


def test_rejects_append_on_save_repeated_pattern(tmp_path):
    sequence = [_point("a", 1.0, 2.0), _point("b", 3.0, 4.0)]
    with pytest.raises(TaskChainError, match="exact repeated pattern"):
        load_qt_task_chain(_write(tmp_path, sequence + sequence))


@pytest.mark.parametrize(
    "points",
    [[], [_point("bad", math.nan, 0.0)], [_point("", 0.0, 0.0)]],
)
def test_rejects_empty_or_invalid_points(tmp_path, points):
    with pytest.raises(TaskChainError):
        load_qt_task_chain(_write(tmp_path, points))


class Value:
    pass


def _map_info(yaw=0.0):
    info = Value()
    info.width = 10
    info.height = 5
    info.resolution = 1.0
    info.origin = Value()
    info.origin.position = Value()
    info.origin.position.x = -2.0
    info.origin.position.y = -1.0
    info.origin.orientation = Value()
    info.origin.orientation.x = 0.0
    info.origin.orientation.y = 0.0
    info.origin.orientation.z = math.sin(yaw / 2.0)
    info.origin.orientation.w = math.cos(yaw / 2.0)
    return info


def test_checks_current_map_bounds():
    info = _map_info()
    assert point_inside_map(Waypoint("inside", -1.9, -0.9, 0.0), info)
    assert not point_inside_map(Waypoint("outside", 8.0, 0.0, 0.0), info)


def test_checks_rotated_map_bounds():
    info = _map_info(math.pi / 2.0)
    assert point_inside_map(Waypoint("inside", -3.0, 0.0, 0.0), info)
    assert not point_inside_map(Waypoint("outside", 0.0, 0.0, 0.0), info)
