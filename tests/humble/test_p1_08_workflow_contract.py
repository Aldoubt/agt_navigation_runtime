from pathlib import Path

import yaml


ROOT = Path(__file__).resolve().parents[2]
WORKFLOW = ROOT / ".github" / "workflows" / "runtime-humble.yml"

CORE_PACKAGES = {
    "agt_interfaces",
    "agt_runtime_contracts",
    "agt_site_runtime",
    "agt_site_navigation",
    "agt_system_manager",
    "agt_navigation",
    "agt_safety",
    "agt_operator_gateway",
}


def _workflow_text() -> str:
    assert WORKFLOW.exists(), "P1-08 requires a real ROS 2 Humble workflow"
    return WORKFLOW.read_text(encoding="utf-8")


def test_workflow_runs_in_real_humble_jammy_environment():
    data = yaml.safe_load(_workflow_text())
    jobs = data["jobs"]
    assert jobs, "at least one Humble regression job is required"

    job = next(iter(jobs.values()))
    assert job.get("runs-on") == "ubuntu-22.04"
    container = job.get("container", {})
    image = container.get("image", "") if isinstance(container, dict) else str(container)
    assert "humble" in image.lower()
    assert "jammy" in image.lower()


def test_workflow_installs_rosdeps_and_builds_selected_core():
    text = _workflow_text()

    assert "rosdep install" in text
    assert "colcon build" in text
    assert "--packages-up-to" in text or "--packages-select" in text
    for package in CORE_PACKAGES:
        assert package in text


def test_workflow_keeps_apt_metadata_available_for_rosdep():
    text = _workflow_text()
    rosdep_index = text.index("rosdep install")
    cleanup_index = text.find("rm -rf /var/lib/apt/lists/*")

    if cleanup_index != -1 and cleanup_index < rosdep_index:
        between = text[cleanup_index:rosdep_index]
        assert "apt-get update" in between, (
            "APT metadata was deleted before rosdep install without refreshing it; "
            "rosdep apt dependencies will be reported as unavailable"
        )


def test_workflow_runs_colcon_tests_and_fails_on_test_failures():
    text = _workflow_text()

    assert "colcon test" in text
    assert "colcon test-result --verbose" in text


def test_workflow_has_post_install_humble_smoke():
    text = _workflow_text()

    assert "source install/setup.bash" in text
    assert "NavigationRuntimeStatus" in text
    assert "SiteNavigationBinding" in text
    assert "enable_rviz_goal_bridge" in text
    assert "false" in text
    assert "NO_ACTIVE_SITE" in text or "NAVIGATION_UNKNOWN" in text


def test_workflow_does_not_claim_physical_hardware_acceptance():
    text = _workflow_text()

    forbidden = (
        "can0 up",
        "candump can0",
        "livox_ros_driver2",
        "fast_livo2",
        "BUNKER FIELD PASS",
    )
    for marker in forbidden:
        assert marker not in text