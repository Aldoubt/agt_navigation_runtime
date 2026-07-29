# Authoritative waypoint-task session state owned by agt_navigation.
# Published reliable + transient_local on /agt/navigation/session_status.

uint8 STATE_IDLE=0
uint8 STATE_VALIDATING=1
uint8 STATE_REJECTED=2
uint8 STATE_ACCEPTED=3
uint8 STATE_RUNNING=4
uint8 STATE_CANCELING=5
uint8 STATE_SUCCEEDED=6
uint8 STATE_FAILED=7
uint8 STATE_CANCELED=8

std_msgs/Header header
string session_id
string client_request_id

string map_id
string map_version_id

string task_group_id
uint32 task_revision
string task_content_sha256

uint8 state
uint32 loop_index
uint32 current_waypoint
uint32 total_waypoints
uint32[] missed_waypoints

uint16 error_code
string blocker_code
string operator_message
string technical_message

builtin_interfaces/Time started_at
builtin_interfaces/Time updated_at

bool terminal
bool success
