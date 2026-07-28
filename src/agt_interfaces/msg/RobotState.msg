# Unified read model for interchangeable operator clients.
uint8 MODE_UNKNOWN=0
uint8 MODE_IDLE=1
uint8 MODE_SENSOR_ONLY=2
uint8 MODE_MAPPING=3
uint8 MODE_LOCALIZATION_DEBUG=4
uint8 MODE_NAVIGATION=5
uint8 MODE_ERROR=6

uint8 NAV2_UNKNOWN=0
uint8 NAV2_INACTIVE=1
uint8 NAV2_ACTIVE=2
uint8 NAV2_ERROR=3

uint8 CHASSIS_MODE_UNKNOWN=0
uint8 CHASSIS_MODE_MONITOR=1
uint8 CHASSIS_MODE_CONTROL=2

std_msgs/Header header
uint64 revision
uint8 system_mode
string active_profile
uint32 managed_process_count
uint32 running_process_count
agt_interfaces/SystemHealth system_health
agt_interfaces/TaskReadiness task_readiness
agt_interfaces/MapVersionSummary active_map
agt_interfaces/LocalizationStatus localization
agt_interfaces/MissionStatus mission
uint8 nav2_state
float64 nav2_freshness_s
bool safety_status_known
bool safety_motion_enabled
bool emergency_stop
bool estop_latched
bool navigation_ready
float64 safety_freshness_s
bool chassis_status_known
bool chassis_connected
uint8 chassis_control_mode
float64 chassis_status_freshness_s
float64 chassis_odometry_freshness_s
agt_interfaces/BagSessionSummary bag_session
uint16 error_code
string[] blocker_codes
string[] blocker_messages
string message
