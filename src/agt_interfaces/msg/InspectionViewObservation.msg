# One captured view admitted by the inspection executor for point-local multi-view aggregation.
# It carries typed robot/camera context plus the single-view vision result. The complete
# domain-specific instance payload remains in single_view_result_json.

string view_id
string capture_id
builtin_interfaces/Time capture_stamp

string map_id
string map_version_id
string point_id

string camera_id
string camera_calibration_id
string camera_calibration_sha256

# Actual robot pose at capture time, not the requested Nav2 target pose.
geometry_msgs/PoseWithCovarianceStamped robot_pose_map

# Optional resolved camera pose in map frame. If false, the aggregator may derive it
# from robot pose + gimbal feedback + calibrated extrinsics.
bool camera_pose_valid
geometry_msgs/PoseStamped camera_pose_map

float64 gimbal_pan_rad
float64 gimbal_tilt_rad
bool gimbal_feedback_valid

# Stable model-independent Level-1 summary.
uint32 raw_instance_count
string model_id
string model_version
float64 inference_time_ms

# Runtime-owned evidence locations for this view.
string image_uri
string overlay_uri
string mask_uri
string single_view_result_uri

# Full single-view result (instances/masks/local ids/domain fields) encoded as JSON.
string single_view_result_json
