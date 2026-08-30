from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
COMMISSIONING = ROOT / "src" / "agt_field_commissioning"
MAPPING_LAUNCH = COMMISSIONING / "launch" / "field_mapping.launch.py"
NAVIGATION_LAUNCH = COMMISSIONING / "launch" / "field_navigation.launch.py"
MAPPING_RVIZ = COMMISSIONING / "rviz" / "field_mapping.rviz"
NAVIGATION_RVIZ = COMMISSIONING / "rviz" / "field_navigation.rviz"
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


def test_phase_a_mapping_launch_exposes_same_run_to_delivery_gateway():
    text = MAPPING_LAUNCH.read_text(encoding="utf-8")

    assert 'package="agt_operator_gateway"' in text
    assert 'executable="operator_delivery_gateway_node.py"' in text
    assert '"commissioning_enabled": True' in text
    assert '"commissioning_site_id": site_id' in text
    assert '"commissioning_run_id": run_id' in text
    assert '"commissioning_runtime_dir": runtime_dir' in text
    assert '"commissioning_vehicle_profile": LaunchConfiguration("platform_profile").perform(context)' in text
    assert 'DeclareLaunchArgument("start_operator_gateway", default_value="true")' in text
    assert 'DeclareLaunchArgument("gateway_write_api_enabled", default_value="true")' in text
    assert 'DeclareLaunchArgument("gateway_host", default_value="127.0.0.1")' in text


def test_phase_a_mapping_launch_does_not_start_localization_or_navigation():
    text = MAPPING_LAUNCH.read_text(encoding="utf-8")

    assert "agt_localization" not in text
    assert "agt_site_navigation" not in text
    assert "agt_navigation" not in text
    assert "navigation.launch.py" not in text
    assert "map_server" not in text
    assert "bt_navigator" not in text


def test_phase_a_mapping_has_dedicated_optional_rviz():
    launch = MAPPING_LAUNCH.read_text(encoding="utf-8")

    assert 'DeclareLaunchArgument("start_rviz", default_value="false")' in launch
    assert 'package="rviz2"' in launch
    assert 'executable="rviz2"' in launch
    assert '"field_mapping.rviz"' in launch

    rviz = MAPPING_RVIZ.read_text(encoding="utf-8")
    assert "Fixed Frame: camera_init" in rviz
    assert "Value: /agt/commissioning/mapping/registered_points" in rviz
    assert "Decay Time: 30" in rviz
    assert "Value: /path" in rviz


def test_phase_c_navigation_uses_navigation_specific_rviz():
    launch = NAVIGATION_LAUNCH.read_text(encoding="utf-8")
    rviz = NAVIGATION_RVIZ.read_text(encoding="utf-8")

    assert '"field_navigation.rviz"' in launch
    assert '"field_commissioning.rviz"' not in launch
    assert "Fixed Frame: map" in rviz
    assert "Value: /map" in rviz
    assert "Value: /global_costmap/costmap" in rviz


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


def test_finalizer_is_staged_executable_for_symlink_install():
    cmake = (COMMISSIONING / "CMakeLists.txt").read_text(encoding="utf-8")

    assert "AGT_FIELD_COMMISSIONING_GENERATED_SCRIPT_DIR" in cmake
    assert "file(COPY" in cmake
    assert "scripts/finalize_mapping_run.py" in cmake
    assert "FILE_PERMISSIONS" in cmake
    assert "OWNER_EXECUTE" in cmake
    assert "GROUP_EXECUTE" in cmake
    assert "WORLD_EXECUTE" in cmake
    assert "install(PROGRAMS" in cmake
