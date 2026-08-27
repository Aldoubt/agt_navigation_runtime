from pathlib import Path


PACKAGE = Path(__file__).resolve().parents[1]


def _read(relative: str) -> str:
    return (PACKAGE / relative).read_text(encoding="utf-8")


def test_multiview_interfaces_are_registered():
    cmake = _read("CMakeLists.txt")
    assert '"msg/InspectionViewObservation.msg"' in cmake
    assert '"action/AggregateInspectionViews.action"' in cmake


def test_view_observation_carries_pose_gimbal_and_single_view_result():
    message = _read("msg/InspectionViewObservation.msg")
    for token in (
        "string view_id",
        "string capture_id",
        "builtin_interfaces/Time capture_stamp",
        "string map_id",
        "string map_version_id",
        "string point_id",
        "string camera_id",
        "string camera_calibration_id",
        "string camera_calibration_sha256",
        "geometry_msgs/PoseWithCovarianceStamped robot_pose_map",
        "bool camera_pose_valid",
        "geometry_msgs/PoseStamped camera_pose_map",
        "float64 gimbal_pan_rad",
        "float64 gimbal_tilt_rad",
        "bool gimbal_feedback_valid",
        "uint32 raw_instance_count",
        "string model_id",
        "string model_version",
        "float64 inference_time_ms",
        "string image_uri",
        "string overlay_uri",
        "string mask_uri",
        "string single_view_result_uri",
        "string single_view_result_json",
    ):
        assert token in message


def test_aggregate_action_is_point_local_and_reports_raw_unique_and_ambiguous_counts():
    action = _read("action/AggregateInspectionViews.action")
    for token in (
        "string request_id",
        "string session_id",
        "string point_id",
        "string map_id",
        "string map_version_id",
        "string count_target",
        "string aggregation_profile",
        "agt_interfaces/InspectionViewObservation[] views",
        "uint16 ERROR_INSUFFICIENT_VIEWS=2",
        "uint16 ERROR_MAP_MISMATCH=3",
        "uint16 ERROR_CALIBRATION_MISMATCH=4",
        "uint16 ERROR_ASSOCIATION_FAILED=5",
        "string aggregator_id",
        "string aggregator_version",
        "uint32 raw_instance_count",
        "uint32 unique_instance_count",
        "uint32 ambiguous_instance_count",
        "float64 association_confidence",
        "string result_uri",
        "string result_json",
        "uint32 current_view",
        "uint32 total_views",
        "float32 progress",
    ):
        assert token in action
