from agt_navigation.route_runtime import (
    MapOdomSnapshot,
    RouteAsset,
    RouteNavigationCore,
    RoutePoint,
    RouteSegment,
    TrackerFeedback,
)


class RecordingTracker:
    def __init__(self):
        self.paths = []

    def start(self, path):
        self.paths.append(path)

    def cancel(self):
        pass


def _asset():
    segment_zero = RouteSegment(
        "s000",
        "F",
        (
            RoutePoint(0, "s000", 10.0, 0.0, 0.0, "F", 0.2, 0.0, 1.0, "row", ""),
            RoutePoint(1, "s000", 11.0, 0.0, 0.0, "F", 0.2, 0.0, 1.0, "row", ""),
        ),
        (),
    )
    segment_one = RouteSegment(
        "s001",
        "F",
        (
            RoutePoint(2, "s001", 12.0, 0.0, 0.0, "F", 0.2, 0.0, 1.0, "row", ""),
            RoutePoint(3, "s001", 13.0, 0.0, 0.0, "F", 0.2, 0.0, 1.0, "row", ""),
        ),
        (),
    )
    return RouteAsset(
        "route",
        1,
        "map",
        "site",
        "map_v1",
        "sha256:map",
        "sha256:vehicle",
        None,
        (segment_zero, segment_one),
    )


def test_two_segment_route_consumes_correction_only_at_boundary():
    canonical = {"generation": 7, "x": 10.0, "y": 0.0}
    tracker = RecordingTracker()
    core = RouteNavigationCore(_asset(), tracker)

    def snapshot():
        return MapOdomSnapshot(canonical["x"], canonical["y"], 0.0, canonical["generation"])

    first = core.start(snapshot())
    first_points = first.points
    canonical.update(generation=8, x=20.0)

    assert core.active_path.points == first_points
    assert core.active_path.alignment_generation == 7
    assert len(tracker.paths) == 1

    core.update_global_alignment(snapshot())
    completion = core.handle_tracker_feedback(TrackerFeedback("SUCCEEDED", "s000"))

    assert completion.segment_id == "s000"
    assert core.active_path.alignment_generation == 8
    assert core.active_path.points != first_points
    assert len(tracker.paths) == 2
    assert core.metrics.global_planner_requests == 0


def test_segments_without_new_correction_reuse_generation():
    canonical = {"generation": 7, "x": 10.0, "y": 0.0}
    tracker = RecordingTracker()
    core = RouteNavigationCore(_asset(), tracker)

    snapshot = lambda: MapOdomSnapshot(canonical["x"], canonical["y"], 0.0, canonical["generation"])
    core.start(snapshot())
    core.update_global_alignment(snapshot())
    core.handle_tracker_feedback(TrackerFeedback("SUCCEEDED", "s000"))

    assert core.active_path.alignment_generation == 7
    assert len(tracker.paths) == 2
