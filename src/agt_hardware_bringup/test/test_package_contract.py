from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_cmake_installs_python_package_scripts_launch_and_config():
    text = (ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
    assert "find_package(ament_cmake REQUIRED)" in text
    assert "find_package(ament_cmake_python REQUIRED)" in text
    assert "ament_python_install_package(${PROJECT_NAME})" in text
    assert "scripts/socketcan_preflight.py" in text
    assert "scripts/vehicle_preflight.py" in text
    assert "install(DIRECTORY launch config" in text
    assert "ament_package()" in text


def test_package_declares_only_composition_runtime_dependencies():
    text = (ROOT / "package.xml").read_text(encoding="utf-8")
    for dependency in (
        "agt_chassis_bunker",
        "agt_sensor_adapters",
        "agt_sensor_monitor",
        "ament_index_python",
        "launch",
        "ros2cli",
        "iproute2",
    ):
        assert f"<exec_depend>{dependency}</exec_depend>" in text
    assert "nav2_msgs" not in text
    assert "geometry_msgs" not in text
    assert "rclpy" not in text


def test_readme_is_monitor_first_and_marks_vehicle_values_unverified():
    text = (ROOT / "README.md").read_text(encoding="utf-8")
    assert "operation_mode:=monitor" in text
    assert "UNVERIFIED" in text
    assert "expected_can_bitrate:=0" in text
    assert "sensor_profile:=hardware_check" in text


def test_package_contains_no_network_mutation_or_motion_dispatch():
    forbidden = (
        "ip link set",
        "ros2 topic pub",
        "/cmd_vel",
        "NavigateToPose",
        "FollowPath",
    )
    for path in list(ROOT.rglob("*.py")) + list(ROOT.rglob("*.launch.py")):
        if path.name.startswith("test_"):
            continue
        text = path.read_text(encoding="utf-8")
        for token in forbidden:
            assert token not in text, f"{token!r} found in {path}"
