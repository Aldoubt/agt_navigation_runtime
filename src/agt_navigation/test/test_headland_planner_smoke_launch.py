from pathlib import Path

import yaml


ROOT = Path(__file__).resolve().parents[1]


def test_headland_smoke_launch_is_planner_only_and_artifact_driven():
    source = (ROOT / "launch" / "headland_planner_smoke.launch.py").read_text(
        encoding="utf-8"
    )
    for required in (
        'DeclareLaunchArgument("map")',
        'DeclareLaunchArgument("planner_pairs")',
        'DeclareLaunchArgument("gap_diagnostics")',
        'DeclareLaunchArgument("output")',
        'executable="map_server"',
        'executable="planner_server"',
        'executable="headland_planner_smoke.py"',
    ):
        assert required in source
    for forbidden in (
        "controller_server",
        "bt_navigator",
        "waypoint_follower",
        "collision_monitor",
        "velocity_smoother",
        "cmd_vel",
    ):
        assert forbidden not in source


def test_headland_smoke_nav2_config_freezes_r020_and_unknown_blocking():
    config = yaml.safe_load(
        (ROOT / "config" / "headland_planner_smoke_nav2.yaml").read_text(
            encoding="utf-8"
        )
    )
    planner = config["planner_server"]["ros__parameters"]
    assert planner["planner_plugins"] == ["GridBased"]
    assert planner["GridBased"]["plugin"] == "nav2_smac_planner/SmacPlanner2D"
    assert planner["GridBased"]["allow_unknown"] is False
    assert planner["GridBased"]["tolerance"] == 0.0

    global_costmap = config["global_costmap"]["global_costmap"]["ros__parameters"]
    assert global_costmap["robot_radius"] == 0.20
    assert global_costmap["track_unknown_space"] is True
    assert global_costmap["static_layer"]["map_topic"] == "/agt/map/global_occupancy"
    assert global_costmap["inflation_layer"]["inflation_radius"] == 0.75


def test_headland_smoke_runner_calls_compute_path_without_motion_actions():
    source = (ROOT / "scripts" / "headland_planner_smoke.py").read_text(
        encoding="utf-8"
    )
    for required in (
        "ComputePathToPose",
        "build_smoke_manifest",
        "finalize_smoke_results",
        "write_smoke_bundle",
        "goal.use_start = True",
        "goal.planner_id",
    ):
        assert required in source
    for forbidden in (
        "NavigateToPose",
        "FollowWaypoints",
        "FollowPath",
        "cmd_vel",
    ):
        assert forbidden not in source


def test_headland_smoke_runner_is_installed_by_agt_navigation():
    source = (ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
    assert "headland_planner_smoke.py" in source
    assert "test_headland_planner_smoke" in source
    assert "test_headland_planner_smoke_launch" in source
