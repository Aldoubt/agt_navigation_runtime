import ast
from pathlib import Path


PKG = Path(__file__).resolve().parents[1]
LAUNCH = PKG / "launch" / "mk_mini_vcan_hil.launch.py"


def test_hil_launch_composes_real_backend_and_virtual_vcu_with_safe_defaults():
    assert LAUNCH.is_file()
    source = LAUNCH.read_text(encoding="utf-8")
    ast.parse(source, filename=str(LAUNCH))
    for required in [
        "agt_chassis_mk_mini",
        "mk_mini.launch.py",
        "mk_mini_vcu_sim.py",
        'DeclareLaunchArgument("can_interface", default_value="vcan0")',
        'default_value="monitor"',
        'DeclareLaunchArgument("steering_calibration_confirmed", default_value="false")',
        'DeclareLaunchArgument("allow_uncalibrated_control", default_value="false")',
        'DeclareLaunchArgument("drop_feedback", default_value="false")',
        'DeclareLaunchArgument("corrupt_bcc", default_value="false")',
    ]:
        assert required in source


def test_hil_launch_never_mutates_host_networking():
    source = LAUNCH.read_text(encoding="utf-8").lower()
    assert "sudo" not in source
    assert "ip link" not in source
    assert "executeprocess" not in source
    assert "subprocess" not in source


def test_hil_launch_is_installed():
    cmake = (PKG / "CMakeLists.txt").read_text(encoding="utf-8")
    assert "DIRECTORY launch config" in cmake
