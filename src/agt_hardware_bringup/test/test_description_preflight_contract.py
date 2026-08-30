from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
LAUNCH = ROOT / "launch" / "bunker_mid360.launch.py"
PACKAGE = ROOT / "package.xml"


def test_hardware_bringup_composes_description_owner_by_default():
    text = LAUNCH.read_text(encoding="utf-8")
    assert 'get_package_share_directory("agt_description")' in text
    assert 'DeclareLaunchArgument("start_description", default_value="true")' in text
    assert '"bunker_description.launch.py"' in text


def test_hardware_bringup_declares_description_runtime_dependency():
    text = PACKAGE.read_text(encoding="utf-8")
    assert "<exec_depend>agt_description</exec_depend>" in text
