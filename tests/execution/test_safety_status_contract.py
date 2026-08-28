from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]


def test_navigation_safety_producer_consumers_and_runtime_fixture_share_status_name():
    safety = (ROOT / "src/agt_safety/scripts/safety_controller.py").read_text(
        encoding="utf-8"
    )
    waypoint = (
        ROOT / "src/agt_navigation/scripts/waypoint_task_server.py"
    ).read_text(encoding="utf-8")
    route_runtime_gate_test = (
        ROOT
        / "src/agt_navigation/test/test_navigation_capability_runtime_gates.py"
    ).read_text(encoding="utf-8")

    canonical = "agt_safety/controller"
    legacy = "agt_safety/tracked_controller"

    assert f'status.name = "{canonical}"' in safety
    assert f'status.name != "{canonical}"' in waypoint
    assert f'status.name = "{canonical}"' in route_runtime_gate_test
    assert legacy not in waypoint
    assert legacy not in route_runtime_gate_test
