# agt_sensor_monitor

Read-only sensor input health evidence for V2.5. The node subscribes to the configured raw streams and publishes one `diagnostic_msgs/DiagnosticStatus` per stream plus `agt_sensor_monitor/summary` on `/diagnostics`.

It does not republish sensor data, alter timestamps, synchronize messages, publish TF/odometry, or participate in localization. Message age uses ROS time; receive age and the finite rate window use steady time, so paused bag playback can still be detected as stopped input. Camera, CameraInfo, and GNSS are disabled and optional in the baseline configuration.

`required_streams_healthy` is fail-closed and is independent of startup severity: a required stream that has not actually become healthy keeps this field `false` even while the per-stream diagnostic level is only `WARN` during startup grace. `agt_safety` may consume this field as an immediate navigation gate.

## LiDAR message backends

`lidar.message_type` and `filtered_lidar.message_type` support:

- `livox_custom`: `livox_ros_driver2/msg/CustomMsg`, used by the production MID360 configuration
- `laser_scan`: `sensor_msgs/msg/LaserScan`, used by SOFTWARE_ONLY Gazebo validation and other standard 2D scan sources

`livox_ros_driver2` is an optional CMake backend rather than a hard rosdep dependency. If the package is available in the sourced workspace, Livox support is compiled automatically. If it is absent, the package can still build and run standard-message monitoring; requesting `message_type=livox_custom` then fails explicitly at startup instead of silently falling back.

The values in `config/sensor_monitor.yaml` are deployment baselines, not vehicle validation results. The system manager consumes the structured diagnostic evidence and keeps TaskReadiness fail-closed for raw LiDAR, filtered LiDAR, and IMU. SOFTWARE_ONLY Gazebo uses a separate validation config with LaserScan LiDAR and no filtered-LiDAR requirement.
