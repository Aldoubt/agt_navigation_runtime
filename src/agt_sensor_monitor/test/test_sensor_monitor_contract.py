from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[1]


def test_contract_has_required_raw_streams_and_optional_defaults():
    text = (ROOT / "config" / "sensor_monitor.yaml").read_text()
    assert "/agt/sensors/lidar/custom" in text
    assert "/agt/sensors/lidar/custom_filtered" in text
    assert "message_type: livox_custom" in text
    assert "/agt/sensors/imu/data" in text
    assert "camera: {enabled: false, required: false" in text
    assert "gnss: {enabled: false, required: false" in text


def test_node_only_publishes_diagnostics_supports_laserscan_and_has_strict_required_summary():
    text = (ROOT / "src" / "sensor_monitor_node.cpp").read_text()
    header = (ROOT / "include" / "agt_sensor_monitor" / "sensor_monitor_node.hpp").read_text()
    cmake = (ROOT / "CMakeLists.txt").read_text()
    package = (ROOT / "package.xml").read_text()
    assert '"/diagnostics"' in text
    assert "create_publisher<diagnostic_msgs::msg::DiagnosticArray>" in text
    assert "create_publisher<" not in text.replace(
        "create_publisher<diagnostic_msgs::msg::DiagnosticArray>", ""
    )
    assert 'message_type == "laser_scan"' in text
    assert "sensor_msgs::msg::LaserScan" in text
    assert "bool required_streams_healthy = true" in text
    assert "result.enabled && result.required && !result.healthy" in text
    assert 'kv.key = "required_streams_healthy"' in text
    assert "AGT_SENSOR_MONITOR_HAS_LIVOX" in header
    assert "find_package(livox_ros_driver2 QUIET)" in cmake
    assert "<depend>livox_ros_driver2</depend>" not in package


def test_bringup_and_safety_consume_monitor_evidence():
    bringup = (ROOT.parent / "agt_bringup" / "launch" / "system.launch.py").read_text()
    safety_config = yaml.safe_load(
        (ROOT.parent / "agt_safety" / "config" / "bunker_safety.yaml").read_text()
    )["agt_tracked_safety_controller"]["ros__parameters"]
    safety_controller = (
        ROOT.parent / "agt_safety" / "scripts" / "tracked_safety_controller.py"
    ).read_text()

    assert "start_sensor_monitor" in bringup
    assert "agt_sensor_monitor" in bringup

    assert safety_config["require_sensor_input_ready"] is True
    assert safety_config["sensor_diagnostics_topic"] == "/diagnostics"
    assert safety_config["sensor_summary_name"] == "agt_sensor_monitor/summary"

    assert "required_streams_healthy" in safety_controller
    assert "sensor_summary_is_ready" in safety_controller
    assert "sensor_input_unhealthy" in safety_controller
