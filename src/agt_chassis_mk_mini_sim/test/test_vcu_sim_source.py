from pathlib import Path


PKG = Path(__file__).resolve().parents[1]
SCRIPT = PKG / "scripts" / "mk_mini_vcu_sim.py"


def test_vcu_simulator_node_has_socketcan_feedback_and_observability_contract():
    assert SCRIPT.is_file()
    source = SCRIPT.read_text(encoding="utf-8")
    for required in [
        "SocketCanTransport",
        "CTRL_CMD_ID",
        "CTRL_FB_ID",
        "LEFT_REAR_WHEEL_FB_ID",
        "RIGHT_REAR_WHEEL_FB_ID",
        "BMS_INFO_FB_ID",
        '"can_interface", "vcan0"',
        '"drop_feedback", False',
        '"corrupt_bcc", False',
        '"/agt/sim/mk_mini/status"',
        "command_frames",
        "checksum_failures",
        "counter_gaps",
        "feedback_frames",
    ]:
        assert required in source


def test_vcu_simulator_never_mutates_host_networking():
    source = SCRIPT.read_text(encoding="utf-8").lower()
    assert "sudo" not in source
    assert "ip link" not in source
    assert "subprocess" not in source
    assert '"can0"' not in source


def test_simulator_is_installed_as_a_ros_executable_and_config_is_installed():
    cmake = (PKG / "CMakeLists.txt").read_text(encoding="utf-8")
    assert "scripts/mk_mini_vcu_sim.py" in cmake
    assert "DIRECTORY launch config" in cmake or "DIRECTORY config" in cmake
    assert (PKG / "config" / "vcu_sim.yaml").is_file()
