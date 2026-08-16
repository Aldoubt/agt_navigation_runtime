from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
PKG = ROOT / "src" / "agt_chassis_mk_mini"


def read(path: str) -> str:
    return (ROOT / path).read_text(encoding="utf-8")


def test_mk_mini_can_backend_layers_exist():
    assert (PKG / "agt_chassis_mk_mini" / "mk_mini_protocol.py").is_file()
    assert (PKG / "agt_chassis_mk_mini" / "mk_mini_command_state.py").is_file()
    assert (PKG / "agt_chassis_mk_mini" / "socketcan_transport.py").is_file()
    assert (PKG / "scripts" / "mk_mini_can_backend.py").is_file()


def test_mk_mini_backend_does_not_vendor_unlicensed_yhs_packages():
    package_xml = read("src/agt_chassis_mk_mini/package.xml").lower()
    cmake = read("src/agt_chassis_mk_mini/CMakeLists.txt").lower()
    assert "yhs_can_control" not in package_xml + cmake
    assert "yhs_can_interfaces" not in package_xml + cmake
    assert not (ROOT / "src" / "yhs_can_control").exists()
    assert not (ROOT / "src" / "yhs_can_interfaces").exists()


def test_backend_contract_uses_existing_ackermann_boundary_and_safe_default_mode():
    backend = read("src/agt_chassis_mk_mini/scripts/mk_mini_can_backend.py")
    assert '"/agt/chassis/backend/ackermann_command"' in backend
    assert '"operation_mode", "monitor"' in backend
    assert '"tx_period_sec", 0.01' in backend
    assert "AckermannCommand" in backend


def test_backend_exposes_canonical_feedback_and_diagnostics_topics():
    backend = read("src/agt_chassis_mk_mini/scripts/mk_mini_can_backend.py")
    assert '"/agt/chassis/backend/ackermann_feedback"' in backend
    assert '"/agt/chassis/connected"' in backend
    assert '"/agt/chassis/status"' in backend
    assert '"/agt/chassis/wheel_twist"' in backend
    assert '"/battery"' in backend


def test_backend_has_explicit_calibration_and_command_freshness_gates():
    backend = read("src/agt_chassis_mk_mini/scripts/mk_mini_can_backend.py")
    assert "steering_calibration_confirmed" in backend
    assert "allow_uncalibrated_control" in backend
    assert "command_timeout" in backend
    assert "feedback_timeout" in backend


def test_mk_mini_full_launch_exists_and_never_configures_can_with_shell_commands():
    launch_path = PKG / "launch" / "mk_mini.launch.py"
    assert launch_path.is_file()
    launch = launch_path.read_text(encoding="utf-8")
    assert "mk_mini_adapter.py" in launch
    assert "mk_mini_can_backend.py" in launch
    lowered = launch.lower()
    assert "sudo" not in lowered
    assert "ip link" not in lowered


def test_full_launch_exposes_explicit_safe_steering_calibration_gates():
    launch = read("src/agt_chassis_mk_mini/launch/mk_mini.launch.py")
    assert '"steering_calibration_confirmed", default_value="false"' in launch
    assert '"allow_uncalibrated_control", default_value="false"' in launch
    assert 'LaunchConfiguration("steering_calibration_confirmed")' in launch
    assert 'LaunchConfiguration("allow_uncalibrated_control")' in launch
