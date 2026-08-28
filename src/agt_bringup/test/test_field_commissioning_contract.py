import re
from pathlib import Path

SRC_ROOT = Path(__file__).resolve().parents[2]
SYSTEM = SRC_ROOT / "agt_bringup" / "launch" / "system.launch.py"


def _declares_argument(source: str, name: str, default: str) -> bool:
    pattern = (
        rf'DeclareLaunchArgument\(\s*"{re.escape(name)}"\s*,\s*'
        rf'default_value="{re.escape(default)}"'
    )
    return re.search(pattern, source) is not None


def test_system_exposes_safe_mapping_output_arguments():
    source = SYSTEM.read_text(encoding="utf-8")

    assert _declares_argument(source, "mapping_save_pcd", "false")
    assert _declares_argument(source, "mapping_pcd_save_interval", "-1")
    assert _declares_argument(
        source,
        "mapping_pcd_output_dir",
        "runtime/maps/fast_livo2",
    )

    assert '"save_pcd": LaunchConfiguration("mapping_save_pcd")' in source
    assert '"pcd_save_interval": LaunchConfiguration("mapping_pcd_save_interval")' in source
    assert '"pcd_output_dir": LaunchConfiguration("mapping_pcd_output_dir")' in source


def test_system_production_default_does_not_enable_pcd_save():
    source = SYSTEM.read_text(encoding="utf-8")

    assert _declares_argument(source, "mapping_save_pcd", "false")
