uint8 STATE_NOT_READY=0
uint8 STATE_READY=1
uint8 STATE_BUSY=2
uint8 STATE_DEGRADED=3
uint8 STATE_ERROR=4

std_msgs/Header header
uint8 state
bool camera_alive
bool gimbal_serial_connected
bool gimbal_feedback_alive
bool move_action_ready
bool busy
float64 camera_age
string last_error
