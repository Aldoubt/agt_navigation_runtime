from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_preview_launch_is_planner_only_and_uses_offline_gui_profile():
    source = (ROOT / "launch" / "waypoint_preview.launch.py").read_text(
        encoding="utf-8"
    )
    assert 'executable="planner_server"' in source
    assert 'executable="waypoint_preview_planner.py"' in source
    assert '"profile": "offline"' in source
    for forbidden in (
        "controller_server",
        "bt_navigator",
        "waypoint_follower",
        "collision_monitor",
        "cmd_vel",
    ):
        assert forbidden not in source
