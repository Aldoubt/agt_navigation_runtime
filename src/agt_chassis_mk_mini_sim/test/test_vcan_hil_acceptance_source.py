from pathlib import Path


PKG = Path(__file__).resolve().parents[1]
SCRIPT = PKG / "scripts" / "vcan_hil_acceptance.py"


def test_acceptance_runner_covers_all_five_bounded_scenarios():
    assert SCRIPT.is_file()
    source = SCRIPT.read_text(encoding="utf-8")
    for scenario in [
        "monitor_only",
        "forward",
        "reverse_interlock",
        "command_timeout",
        "feedback_fault",
    ]:
        assert scenario in source
    for surface in [
        '"/agt/chassis/cmd_vel"',
        '"/agt/chassis/connected"',
        '"/agt/chassis/status"',
        '"/agt/chassis/backend/ackermann_feedback"',
        '"/agt/chassis/wheel_twist"',
    ]:
        assert surface in source
    assert "timeout" in source.lower()
    assert "CTRL_CMD_ID" in source
    assert "CTRL_FB_ID" in source


def test_acceptance_runner_does_not_create_or_configure_vcan():
    source = SCRIPT.read_text(encoding="utf-8").lower()
    assert "sudo" not in source
    assert "ip link" not in source
    assert "modprobe" not in source
    assert "subprocess" not in source


def test_acceptance_runner_is_installed():
    cmake = (PKG / "CMakeLists.txt").read_text(encoding="utf-8")
    assert "scripts/vcan_hil_acceptance.py" in cmake
