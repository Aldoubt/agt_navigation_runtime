from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_preview_launch_is_planner_only_and_uses_offline_gui_profile():
    source = (ROOT / "launch" / "waypoint_preview.launch.py").read_text(
        encoding="utf-8"
    )
    assert 'executable="planner_server"' in source
    assert 'executable="waypoint_preview_planner.py"' in source
    assert '"profile": "offline"' in source
    assert '"navigation_footprint"' in source
    assert '"footprint_json": json.dumps(footprint)' in source
    assert 'DeclareLaunchArgument("start_rviz", default_value="true")' in source
    assert 'executable="start_waypoint_preview_rviz.sh"' in source
    for forbidden in (
        "controller_server",
        "bt_navigator",
        "waypoint_follower",
        "collision_monitor",
        "cmd_vel",
    ):
        assert forbidden not in source


def test_preview_rviz_layers_static_map_inflation_path_and_polygon():
    source = (ROOT / "config" / "waypoint_preview.rviz").read_text(
        encoding="utf-8"
    )
    for topic in (
        "/agt/map/global_occupancy",
        "/global_costmap/costmap",
        "/plan",
        "/agt/navigation/preview_footprint",
    ):
        assert topic in source


def test_preview_rviz_wrapper_removes_snap_gui_paths():
    source = (ROOT / "scripts" / "start_waypoint_preview_rviz.sh").read_text(
        encoding="utf-8"
    )
    assert "GTK_PATH GIO_MODULE_DIR" in source
    assert '"${path}" == /snap/*' in source
    assert 'exec ros2 run rviz2 rviz2 "$@"' in source
