from pathlib import Path
import importlib.util

import yaml


ROOT = Path(__file__).resolve().parents[1]


def _load_runner_module():
    script = ROOT / "scripts" / "headland_planner_smoke.py"
    spec = importlib.util.spec_from_file_location("headland_planner_smoke_runner", script)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


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
        "OnProcessExit",
        "Shutdown",
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


def test_f4_unknown_clearance_contract_changes_only_unknown_inflation_policy():
    baseline = yaml.safe_load(
        (ROOT / "config" / "headland_planner_smoke_nav2.yaml").read_text(
            encoding="utf-8"
        )
    )
    experimental = yaml.safe_load(
        (
            ROOT
            / "config"
            / "headland_planner_smoke_nav2_unknown_clearance.yaml"
        ).read_text(encoding="utf-8")
    )

    baseline_planner = baseline["planner_server"]["ros__parameters"]
    experimental_planner = experimental["planner_server"]["ros__parameters"]
    assert experimental_planner == baseline_planner

    baseline_costmap = baseline["global_costmap"]["global_costmap"]["ros__parameters"]
    experimental_costmap = experimental["global_costmap"]["global_costmap"]["ros__parameters"]

    for key in (
        "resolution",
        "track_unknown_space",
        "robot_radius",
        "footprint_padding",
        "plugins",
        "static_layer",
        "always_send_full_costmap",
    ):
        assert experimental_costmap[key] == baseline_costmap[key]

    baseline_inflation = baseline_costmap["inflation_layer"]
    experimental_inflation = experimental_costmap["inflation_layer"]
    assert baseline_inflation["plugin"] == experimental_inflation["plugin"]
    assert baseline_inflation["cost_scaling_factor"] == experimental_inflation["cost_scaling_factor"]
    assert baseline_inflation["inflation_radius"] == experimental_inflation["inflation_radius"] == 0.75
    assert baseline_inflation["inflate_unknown"] is False
    assert baseline_inflation["inflate_around_unknown"] is False
    assert experimental_inflation["inflate_unknown"] is False
    assert experimental_inflation["inflate_around_unknown"] is True


def test_f4_launch_accepts_planner_params_and_contract_label():
    source = (ROOT / "launch" / "headland_planner_smoke.launch.py").read_text(
        encoding="utf-8"
    )
    assert 'DeclareLaunchArgument("planner_params"' in source
    assert 'DeclareLaunchArgument("planner_contract"' in source
    assert 'LaunchConfiguration("planner_params")' in source
    assert '"--planner-contract"' in source
    assert 'LaunchConfiguration("planner_contract")' in source


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


def test_headland_smoke_runner_strips_ros_launch_arguments_before_argparse():
    runner = _load_runner_module()
    args = runner._parse_cli_args(
        [
            "--planner-pairs",
            "/tmp/planner_pairs.yaml",
            "--gap-diagnostics",
            "/tmp/headland_gap_diagnostics.json",
            "--map-yaml",
            "/tmp/navigation_base_map.yaml",
            "--output",
            "/tmp/planner_smoke",
            "--planner-id",
            "GridBased",
            "--ros-args",
            "-r",
            "__node:=agt_headland_planner_smoke",
        ]
    )

    assert args.planner_pairs == "/tmp/planner_pairs.yaml"
    assert args.gap_diagnostics == "/tmp/headland_gap_diagnostics.json"
    assert args.map_yaml == "/tmp/navigation_base_map.yaml"
    assert args.output == "/tmp/planner_smoke"
    assert args.planner_id == "GridBased"


def test_f4_runner_parses_contract_label_for_result_provenance():
    runner = _load_runner_module()
    args = runner._parse_cli_args(
        [
            "--planner-pairs",
            "/tmp/planner_pairs.yaml",
            "--gap-diagnostics",
            "/tmp/headland_gap_diagnostics.json",
            "--map-yaml",
            "/tmp/navigation_base_map.yaml",
            "--output",
            "/tmp/planner_smoke",
            "--planner-contract",
            "unknown_clearance",
        ]
    )
    assert args.planner_contract == "unknown_clearance"


def test_entrypoint_materialization_reconfigures_when_source_scripts_change():
    source = (ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
    assert "CMAKE_CONFIGURE_DEPENDS" in source
    assert 'scripts/${_script}' in source


def test_headland_smoke_runner_is_installed_by_agt_navigation():
    source = (ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
    assert "headland_planner_smoke.py" in source
    assert "test_headland_planner_smoke" in source
    assert "test_headland_planner_smoke_launch" in source
