# Machine-readable health result for one configured component.
uint8 STATE_UNKNOWN=0
uint8 STATE_OK=1
uint8 STATE_WARN=2
uint8 STATE_ERROR=3

std_msgs/Header header
string component_id
string display_name
uint8 state
bool required
bool present
float64 observed_rate_hz
float64 message_age_sec
uint64 message_count
string[] missing_topics
string[] missing_frames
string[] missing_nodes
string[] lifecycle_failures
string[] condition_failures
string[] warnings
string[] errors
string detail
