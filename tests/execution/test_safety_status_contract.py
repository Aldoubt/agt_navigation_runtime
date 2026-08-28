from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]


def test_waypoint_consumer_matches_generic_safety_status_name():
    safety = (ROOT / "src/agt_safety/scripts/safety_controller.py").read_text(
        encoding="utf-8"
    )
    waypoint = (
        ROOT / "src/agt_navigation/scripts/waypoint_task_server.py"
    ).read_text(encoding="utf-8")

    assert 'status.name = "agt_safety/controller"' in safety
    assert 'status.name != "agt_safety/controller"' in waypoint
    assert "agt_safety/tracked_controller" not in waypoint
