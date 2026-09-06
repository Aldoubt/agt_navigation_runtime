builtin_interfaces/Time stamp

# raw encoder feedback
float32 yaw_encoder
float32 pitch_encoder

# filtered value
float32 yaw_filtered
float32 pitch_filtered

# attitude feedback
float32 ground_roll
float32 ground_pitch
float32 ground_yaw

# state
bool stable
bool healthy

string status
