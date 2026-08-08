import hashlib
from pathlib import Path

import pytest
import yaml

from agt_navigation.route_runtime import (
    MapOdomSnapshot,
    RouteNavigationCore,
    RouteRuntimeError,
    TrackerFeedback,
    load_route_asset,
)


class FakeTracker:
    def __init__(self):
        self.started = []
        self.cancel_count = 0

    def start(self, path):
        self.started.append(path)

    def cancel(self):
        self.cancel_count += 1


def _sha256(path: Path) -> str:
    return "sha256:" + hashlib.sha256(path.read_bytes()).hexdigest()


def _write_route(tmp_path: Path, *, status="READY", bad_hash=False):
    route_dir = tmp_path / "route"
    route_dir.mkdir()
    csv_path = route_dir / "route.csv"
    csv_path.write_text(
        "seq,segment_id,x,y,yaw,direction,v_ref,curvature,clearance,semantic_ref,event_ref\n"
        "0,s000,10.0,0.0,0.0,F,0.3,0.0,1.0,row_0,\n"
        "1,s000,11.0,0.0,0.0,F,0.3,0.0,1.0,row_0,stop_a\n"
        "2,s001,20.0,0.0,3.141592653589793,R,0.2,0.0,1.0,headland,\n"
        "3,s001,21.0,0.0,3.141592653589793,R,0.2,0.0,1.0,headland,stop_b\n",
        encoding="utf-8",
    )
    manifest = {
        "schema_version": 1,
        "route_id": "route_demo",
        "revision": 3,
        "frame_id": "map",
        "map_binding": {
            "map_id": "facility_a",
            "map_version_id": "map_v1",
            "map_content_sha256": "sha256:" + "a" * 64,
        },
        "vehicle_binding": {
            "platform_id": "mk_mini",
            "platform_profile_sha256": "sha256:" + "b" * 64,
        },
        "route_csv_sha256": "sha256:" + "0" * 64 if bad_hash else _sha256(csv_path),
        "status": status,
    }
    (route_dir / "route.yaml").write_text(yaml.safe_dump(manifest, sort_keys=False), encoding="utf-8")
    return route_dir


def test_ready_route_asset_loads_segments_and_business_events(tmp_path):
    route_dir = _write_route(tmp_path)
    asset = load_route_asset(
        route_dir,
        expected_map_content_sha256="sha256:" + "a" * 64,
        expected_vehicle_profile_sha256="sha256:" + "b" * 64,
    )

    assert asset.frame_id == "map"
    assert [segment.segment_id for segment in asset.segments] == ["s000", "s001"]
    assert [segment.direction for segment in asset.segments] == ["F", "R"]
    assert asset.segments[0].event_refs == ("stop_a",)
    assert asset.segments[1].event_refs == ("stop_b",)


def test_route_loader_fails_closed_on_non_ready_or_mutated_csv(tmp_path):
    with pytest.raises(RouteRuntimeError) as exc:
        load_route_asset(_write_route(tmp_path, status="DRAFT"))
    assert exc.value.code == "route_not_ready"

    other = tmp_path / "other"
    other.mkdir()
    with pytest.raises(RouteRuntimeError) as exc:
        load_route_asset(_write_route(other, bad_hash=True))
    assert exc.value.code == "route_csv_hash_mismatch"


def test_map_route_segment_is_projected_to_odom_with_inverse_tf(tmp_path):
    asset = load_route_asset(_write_route(tmp_path))
    tracker = FakeTracker()
    core = RouteNavigationCore(asset, tracker)

    path = core.start(MapOdomSnapshot(10.0, 0.0, 0.0, generation=1))

    assert path.frame_id == "odom"
    assert path.segment_id == "s000"
    assert path.alignment_generation == 1
    assert path.points[0].x == pytest.approx(0.0)
    assert path.points[1].x == pytest.approx(1.0)
    assert path.points[0].y == pytest.approx(0.0)


def test_active_runtime_path_does_not_jump_when_global_alignment_changes(tmp_path):
    asset = load_route_asset(_write_route(tmp_path))
    tracker = FakeTracker()
    core = RouteNavigationCore(asset, tracker)

    active = core.start(MapOdomSnapshot(10.0, 0.0, 0.0, generation=1))
    frozen_xy = tuple((point.x, point.y) for point in active.points)

    # Sparse global correction arrives while s000 is being controlled. It is
    # retained for the next segment but must not move the active RuntimePath.
    core.update_global_alignment(MapOdomSnapshot(20.0, 0.0, 0.0, generation=2))
    assert tuple((point.x, point.y) for point in core.active_path.points) == frozen_xy
    assert core.active_path.alignment_generation == 1

    completion = core.handle_tracker_feedback(TrackerFeedback("SUCCEEDED", "s000"))
    assert completion.segment_id == "s000"
    assert completion.event_refs == ("stop_a",)
    assert completion.route_complete is False

    next_path = core.active_path
    assert next_path.segment_id == "s001"
    assert next_path.alignment_generation == 2
    assert next_path.points[0].x == pytest.approx(0.0)
    assert next_path.points[1].x == pytest.approx(1.0)


def test_fake_route_integration_completes_without_global_planner_requests(tmp_path):
    asset = load_route_asset(_write_route(tmp_path))
    tracker = FakeTracker()
    core = RouteNavigationCore(asset, tracker)

    core.start(MapOdomSnapshot(10.0, 0.0, 0.0, generation=1))
    core.handle_tracker_feedback(TrackerFeedback("RUNNING", "s000", path_index=1))
    core.update_global_alignment(MapOdomSnapshot(20.0, 0.0, 0.0, generation=2))
    first = core.handle_tracker_feedback(TrackerFeedback("SUCCEEDED", "s000"))
    second = core.handle_tracker_feedback(TrackerFeedback("SUCCEEDED", "s001"))

    assert first.route_complete is False
    assert second.route_complete is True
    assert second.event_refs == ("stop_b",)
    assert core.state == "COMPLETED"
    assert core.metrics.segment_projections == 2
    assert core.metrics.tracker_starts == 2
    assert core.metrics.global_planner_requests == 0
    assert [path.segment_id for path in tracker.started] == ["s000", "s001"]
    assert [path.direction for path in tracker.started] == ["F", "R"]


def test_tracker_failure_and_cancel_are_bounded(tmp_path):
    asset = load_route_asset(_write_route(tmp_path))
    tracker = FakeTracker()
    core = RouteNavigationCore(asset, tracker)
    core.start(MapOdomSnapshot(10.0, 0.0, 0.0))

    core.handle_tracker_feedback(TrackerFeedback("FAILED", "s000", failure_reason="blocked"))
    assert core.state == "FAILED"

    tracker2 = FakeTracker()
    core2 = RouteNavigationCore(asset, tracker2)
    core2.start(MapOdomSnapshot(10.0, 0.0, 0.0))
    core2.cancel()
    core2.cancel()
    assert core2.state == "CANCELED"
    assert tracker2.cancel_count == 1
