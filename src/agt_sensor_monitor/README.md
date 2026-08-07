# agt_sensor_monitor

Read-only sensor input health evidence for V2.5. The node subscribes to the
configured raw streams and publishes one `diagnostic_msgs/DiagnosticStatus` per
stream plus `agt_sensor_monitor/summary` on `/diagnostics`.

It does not republish sensor data, alter timestamps, synchronize messages,
publish TF/odometry, or participate in localization. Message age uses ROS time;
receive age and the finite rate window use steady time, so paused bag playback
can still be detected as stopped input. Camera, CameraInfo, and GNSS are
disabled and optional in the baseline configuration.

The values in `config/sensor_monitor.yaml` are deployment baselines, not
vehicle validation results. The system manager consumes the structured
diagnostic evidence and keeps TaskReadiness fail-closed for raw LiDAR, filtered
LiDAR, and IMU.
