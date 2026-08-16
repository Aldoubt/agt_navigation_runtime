from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
SIM = ROOT / "src" / "agt_chassis_mk_mini_sim"
REAL = ROOT / "src" / "agt_chassis_mk_mini"


def read(path: Path) -> str:
    return path.read_text(encoding="utf-8")


def test_simulator_is_a_separate_ros_package():
    assert (SIM / "package.xml").is_file()
    assert (SIM / "CMakeLists.txt").is_file()
    package_xml = read(SIM / "package.xml")
    assert "<name>agt_chassis_mk_mini_sim</name>" in package_xml


def test_real_backend_never_depends_on_simulator():
    real_manifest = read(REAL / "package.xml")
    real_cmake = read(REAL / "CMakeLists.txt")
    assert "agt_chassis_mk_mini_sim" not in real_manifest + real_cmake


def test_sim_protocol_is_independent_from_real_feedback_decoder():
    protocol = SIM / "agt_chassis_mk_mini_sim" / "vcu_protocol.py"
    assert protocol.is_file()
    source = read(protocol)
    assert "def decode_ctrl_command" in source
    assert "def encode_ctrl_feedback" in source
    assert "def encode_wheel_feedback" in source
    assert "def encode_bms_info" in source
    assert "decode_ctrl_feedback" not in source
    assert "decode_wheel_feedback" not in source
    assert "decode_bms_info" not in source


def test_simulator_runtime_defaults_to_vcan_and_has_no_host_network_mutation():
    tree_text = "\n".join(
        read(path)
        for path in SIM.rglob("*")
        if path.is_file() and path.suffix in {".py", ".yaml", ".xml", ".txt"}
    )
    assert "vcan0" in tree_text
    lowered = tree_text.lower()
    assert "sudo " not in lowered
    assert "ip link" not in lowered
    assert "subprocess" not in lowered
