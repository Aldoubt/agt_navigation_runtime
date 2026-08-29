# Authoritative status for one finite inspection-task execution.
uint8 STATE_IDLE=0
uint8 STATE_VALIDATING=1
uint8 STATE_RUNNING=2
uint8 STATE_CANCELING=3
uint8 STATE_SUCCEEDED=4
uint8 STATE_FAILED=5
uint8 STATE_CANCELED=6

uint16 ERROR_NONE=0
uint16 ERROR_INVALID_TASK=1
uint16 ERROR_MAP_MISMATCH=2
uint16 ERROR_NAVIGATION=3
uint16 ERROR_NOT_STATIONARY=4
uint16 ERROR_GIMBAL=5
uint16 ERROR_CAPTURE=6
uint16 ERROR_INFERENCE=7
uint16 ERROR_CANCELED=8
uint16 ERROR_INTERNAL=255

std_msgs/Header header
uint8 state
string session_id
string inspection_task_id
uint32 task_revision
string content_sha256
string map_id
string map_version_id
uint32 current_point
uint32 total_points
string point_id
string stage
uint16 error_code
string message
