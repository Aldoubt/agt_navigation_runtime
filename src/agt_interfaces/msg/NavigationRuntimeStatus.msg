uint8 STATE_UNKNOWN=0
uint8 STATE_STARTING=1
uint8 STATE_READY=2
uint8 STATE_BLOCKED=3
uint8 STATE_ERROR=4

std_msgs/Header header
uint8 state
string site_id
string site_revision
string site_hash

bool map_server_active
bool planner_server_active
bool smoother_server_active
bool controller_server_active
bool behavior_server_active
bool bt_navigator_active
bool waypoint_follower_active
bool collision_monitor_active

bool localization_bound
bool map_identity_known
bool map_identity_match
string localization_map_id
string localization_map_hash

string[] blocker_codes
string[] blocker_messages
