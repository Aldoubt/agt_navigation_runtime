# Manager-owned experiment lifecycle summary.
uint8 STATE_UNKNOWN=0
uint8 STATE_CREATED=1
uint8 STATE_RUNNING=2
uint8 STATE_COMPLETED=3
uint8 STATE_INTERRUPTED=4
uint8 STATE_INVALID=5

std_msgs/Header header
string experiment_id
string title
uint8 state
string created_at
string start_time
string end_time
string platform_profile
string map_id
string map_version_id
string map_hash
string mission_id
string mission_version
string mission_sha256
string launch_profile
string result_status
uint32 config_snapshot_count
string message
