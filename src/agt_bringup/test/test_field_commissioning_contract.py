from pathlib import Path

SRC_ROOT = Path(__file__).resolve().parents[2]
SYSTEM = SRC_ROOT / "agt_bringup" / "launch" / "system.launch.py"


def test_system_exposes_safe_mapping_output_arguments():
    source = SYSTEM.read_text(encoding="utf-8")

    assert 'DeclareLaunchArgument("mapping_save_pcd", default_value="false")' in source
    assert 'DeclareLaunchArgument("mapping_pcd_save_interval", default_value="-1")' in source
    assert 'DeclareLaunchArgument("mapping_pcd_output_dir"' in source

    assert '"save_pcd": LaunchConfiguration("mapping_save_pcd")' in source
    assert '"pcd_save_interval": LaunchConfiguration("mapping_pcd_save_interval")' in source
    assert '"pcd_output_dir": LaunchConfiguration("mapping_pcd_output_dir")' in source


def test_system_production_default_does_not_enable_pcd_save():
    source = SYSTEM.read_text(encoding="utf-8")

    assert 'DeclareLaunchArgument("mapping_save_pcd", default_value="false")' in source
