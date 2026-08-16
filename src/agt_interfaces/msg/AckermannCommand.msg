# Protocol-independent Ackermann setpoint for vehicle backends.
# speed_mps is signed longitudinal speed in m/s.
# steering_angle_rad is the equivalent bicycle-model steering angle in radians.
std_msgs/Header header
float64 speed_mps
float64 steering_angle_rad
