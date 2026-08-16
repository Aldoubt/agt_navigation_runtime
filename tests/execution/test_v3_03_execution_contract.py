from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]


def read(path: str) -> str:
    return (ROOT / path).read_text(encoding="utf-8")


def test_navigation_launch_is_self_contained_and_has_single_raw_command_owner():
    launch = read("src/agt_navigation/launch/navigation.launch.py")
    assert 'package="agt_bringup"' not in launch
    assert launch.count('(\"cmd_vel\", \"/agt/navigation/cmd_vel_raw\")') == 2


def test_collision_monitor_is_the_only_raw_to_filtered_boundary():
    params = read("src/agt_navigation/config/nav2_bunker.yaml")
    assert "cmd_vel_in_topic: /agt/navigation/cmd_vel_raw" in params
    assert "cmd_vel_out_topic: /agt/navigation/cmd_vel" in params


def test_safety_owns_filtered_navigation_to_safety_command_boundary():
    safety = read("src/agt_safety/scripts/safety_controller.py")
    assert '"/agt/navigation/cmd_vel"' in safety
    assert '"/agt/safety/cmd_vel"' in safety
    assert "project_track_speeds" not in safety
    assert "max_track_speed" not in safety
    assert "effective_track_width" not in safety
    assert 'hardware_id = "bunker"' not in safety


def test_generic_chassis_has_no_bunker_dependencies_and_owns_final_twist_boundary():
    package_xml = read("src/agt_chassis/package.xml")
    guard = read("src/agt_chassis/scripts/chassis_command_guard.py")
    assert "bunker_base" not in package_xml
    assert "bunker_msgs" not in package_xml
    assert '"/agt/safety/cmd_vel"' in guard
    assert '"/agt/chassis/cmd_vel"' in guard


def test_vehicle_backends_are_split_into_distinct_packages():
    assert (ROOT / "src/agt_chassis_bunker/package.xml").is_file()
    assert (ROOT / "src/agt_chassis_mk_mini/package.xml").is_file()


def test_mk_mini_backend_uses_protocol_independent_ackermann_command():
    interface = read("src/agt_interfaces/msg/AckermannCommand.msg")
    adapter = read("src/agt_chassis_mk_mini/scripts/mk_mini_adapter.py")
    assert "float64 speed_mps" in interface
    assert "float64 steering_angle_rad" in interface
    assert '"/agt/chassis/cmd_vel"' in adapter
    assert '"/agt/chassis/backend/ackermann_command"' in adapter
    assert "socket" not in adapter.lower()
    assert "0x18c4" not in adapter.lower()
