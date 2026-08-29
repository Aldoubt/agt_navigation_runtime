from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
COMMISSIONING = ROOT / "src" / "agt_field_commissioning"
MAPPING_LAUNCH = COMMISSIONING / "launch" / "field_mapping.launch.py"
RUNTIME_ODOMETRY_LAUNCH = ROOT / "src" / "agt_odometry" / "launch" / "fast_livo2_odometry.launch.py"


def test_phase_a_mapping_launch_is_dedicated_and_persistent():
    text = MAPPING_LAUNCH.read_text(encoding="utf-8")

    assert 'get_package_share_directory("agt_hardware_bringup")' in text
    assert '"bunker_mid360.launch.py"' in text
    assert 'package="fast_livo"' in text
    assert 'executable="fastlivo_mapping"' in text
    assert '"pcd_save.pcd_save_en": True' in text
    assert '"pcd_save.interval": -1' in text
    assert '"pcd_save.output_directory": mapping_output_dir' in text
    assert 'sigterm_timeout="30"' in text
    assert '"/agt/commissioning/mapping/registered_points"' in text


def test_phase_a_mapping_launch_does_not_start_localization_or_navigation():
    text = MAPPING_LAUNCH.read_text(encoding="utf-8")

    assert "agt_localization" not in text
    assert "agt_site_navigation" not in text
    assert "agt_navigation" not in text
    assert "navigation.launch.py" not in text
    assert "map_server" not in text
    assert "bt_navigator" not in text


def test_phase_a_refuses_to_change_runtime_odometry_persistence_default():
    text = RUNTIME_ODOMETRY_LAUNCH.read_text(encoding="utf-8")

    assert '"pcd_save.pcd_save_en": False' in text
    assert '"pcd_save.interval": -1' in text


def test_commissioning_package_installs_launch_python_and_finalizer():
    cmake = (COMMISSIONING / "CMakeLists.txt").read_text(encoding="utf-8")
    package_xml = (COMMISSIONING / "package.xml").read_text(encoding="utf-8")

    assert "ament_python_install_package(${PROJECT_NAME})" in cmake
    assert "scripts/finalize_mapping_run.py" in cmake
    assert "launch" in cmake
    assert "ament_cmake_python" in package_xml
    assert "agt_hardware_bringup" in package_xml
    assert "agt_odometry" in package_xml
    assert "fast_livo" in package_xml
