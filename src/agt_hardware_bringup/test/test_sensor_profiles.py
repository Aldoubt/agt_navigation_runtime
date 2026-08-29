from pathlib import Path

import yaml


ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / "config"


def load_profile(name: str):
    data = yaml.safe_load((CONFIG / name).read_text(encoding="utf-8"))
    return data["agt_sensor_monitor"]["ros__parameters"]


def assert_mid360_thresholds(params):
    assert params["lidar"]["topic"] == "/agt/sensors/lidar/custom"
    assert params["lidar"]["message_type"] == "livox_custom"
    assert params["lidar"]["min_rate_hz"] == 8.0
    assert params["lidar"]["max_stale_sec"] == 0.5
    assert params["imu"]["topic"] == "/agt/sensors/imu/data"
    assert params["imu"]["min_rate_hz"] == 150.0
    assert params["imu"]["max_stale_sec"] == 0.2


def test_hardware_check_requires_only_raw_lidar_and_imu():
    params = load_profile("sensor_monitor.hardware_check.yaml")
    assert_mid360_thresholds(params)
    assert params["lidar"]["enabled"] is True
    assert params["lidar"]["required"] is True
    assert params["imu"]["enabled"] is True
    assert params["imu"]["required"] is True
    for key in ("filtered_lidar", "camera", "camera_info", "gnss"):
        assert params[key]["enabled"] is False
        assert params[key]["required"] is False


def test_navigation_requires_filtered_lidar_but_keeps_camera_optional():
    params = load_profile("sensor_monitor.navigation.yaml")
    assert_mid360_thresholds(params)
    for key in ("lidar", "filtered_lidar", "imu"):
        assert params[key]["enabled"] is True
        assert params[key]["required"] is True
    assert params["filtered_lidar"]["topic"] == "/agt/sensors/lidar/custom_filtered"
    assert params["filtered_lidar"]["message_type"] == "livox_custom"
    assert params["filtered_lidar"]["min_rate_hz"] == 8.0
    assert params["filtered_lidar"]["max_stale_sec"] == 0.5
    for key in ("camera", "camera_info", "gnss"):
        assert params[key]["enabled"] is False
        assert params[key]["required"] is False


def test_profiles_keep_common_monitor_timing_policy():
    for name in ("sensor_monitor.hardware_check.yaml", "sensor_monitor.navigation.yaml"):
        params = load_profile(name)
        assert params["publish_rate_hz"] == 2.0
        assert params["rate_window_size"] == 50
        assert params["startup_grace_sec"] == 3.0
        assert params["timestamp_rollback_tolerance_sec"] == 0.000001
