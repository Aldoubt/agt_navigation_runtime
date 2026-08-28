from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
RUNBOOK = ROOT / "docs" / "runbooks" / "field_navigation_baseline.md"


def _runbook_text() -> str:
    assert RUNBOOK.is_file(), "field_navigation_baseline.md must exist"
    return RUNBOOK.read_text(encoding="utf-8").lower()


def _require_fragments(text: str, fragments: tuple[str, ...]) -> None:
    missing = [fragment for fragment in fragments if fragment.lower() not in text]
    assert not missing, f"runbook is missing required fragments: {missing}"


def test_runbook_freezes_phase_a_b_c_and_recorder_ownership():
    text = _runbook_text()

    _require_fragments(
        text,
        (
            "phase a",
            "field_mapping.launch.py",
            "field_mapping_baseline",
            "phase b",
            "freeze_map_assets.py",
            "map_manifest.json",
            "phase c",
            "field_navigation.launch.py",
            "field_navigation_baseline",
            "agt_experiment_manager",
            "sole",
            "one run_id/bag per experiment",
            "bringup_can2usb_500k.bash",
        ),
    )


def test_runbook_freezes_pre_motion_gates_and_calibration_trajectory():
    text = _runbook_text()

    _require_fragments(
        text,
        (
            "/agt/sensors/lidar/custom",
            "/agt/sensors/imu/data",
            "/agt/mapping/odometry",
            "/agt/mapping/registered_points",
            "/agt/chassis/odometry",
            "/agt/chassis/status",
            "/tf",
            "/tf_static",
            "odom -> base_footprint",
            "monitor_only_cmd_vel_disabled",
            "publisher count 0",
            "static 30 s",
            "forward",
            "reverse",
            "left large circle",
            "right large circle",
            "s-turn",
            "figure-eight",
            "±90",
            "±180",
            "slope",
        ),
    )


def test_runbook_freezes_navigation_gate_n0_n6_and_stop_conditions():
    text = _runbook_text()

    _require_fragments(
        text,
        (
            "start_chassis:=false",
            "tracking",
            "pose_valid=true",
            "localization_accepted=true",
            "status_stale=false",
            "map -> odom",
            "/agt/perception/obstacle_cloud",
            "collision monitor",
            "agt_safety",
            "setinitialpose",
            "setgoal",
            "n0",
            "60 s",
            "n1",
            "2 m",
            "n2",
            "5 m",
            "n3",
            "90°",
            "n4",
            "n5",
            "7 m",
            "n6",
            "10 m",
            "evaluation evidence only",
            "localization invalid",
            "collision stop",
            "wrong point cloud",
            "control oscillation",
            "tf authority conflict",
        ),
    )
