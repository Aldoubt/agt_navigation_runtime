from pathlib import Path


PACKAGE = Path(__file__).resolve().parents[1]


def test_mock_aggregator_serves_stable_action_and_is_installed():
    script = (PACKAGE / "scripts" / "mock_view_aggregator_server.py").read_text(encoding="utf-8")
    cmake = (PACKAGE / "CMakeLists.txt").read_text(encoding="utf-8")

    assert "AggregateInspectionViews" in script
    assert '"/agt/vision/aggregate_views"' in script
    assert "ActionServer" in script
    assert "raw_instance_count" in script
    assert "unique_instance_count" in script
    assert "ambiguous_instance_count" in script
    assert "mock_view_aggregator_server.py" in cmake


def test_mock_aggregator_is_explicitly_no_dedup_baseline():
    script = (PACKAGE / "scripts" / "mock_view_aggregator_server.py").read_text(encoding="utf-8")
    assert "mock-passthrough-aggregator" in script
    assert '"aggregation_scope": "POINT_LOCAL"' in script
    assert '"dedup_applied": False' in script
