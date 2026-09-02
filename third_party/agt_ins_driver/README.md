# agt_ins_driver

ROS 2 Humble INS abstraction driver. The first supported device is ASENSING INS.

## Build and run

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
ros2 launch agt_asensing_driver asensing.launch.py
```

The driver supports ASENSING INS on ROS 2 Humble and publishes:

| Topic | Type |
| --- | --- |
| `/ins/navsatfix` | `sensor_msgs/NavSatFix` |
| `/ins/pose` | `geometry_msgs/PoseStamped` |
| `/ins/velocity` | `geometry_msgs/TwistStamped` |
| `/ins/odom` | `nav_msgs/Odometry` |
| `/ins/status` | `agt_asensing_driver/INSStatus` |

The status message retains GPS week/time, temperature, wheel-speed status,
solution types, satellite count, and standard deviations. RTK-fixed solution
types are configurable with `rtk_fixed_types` in `config/asensing.yaml`.

The intended integration path is:

```text
agt_ins_driver -> robot_localization -> GTSAM GPSFactor -> FAST-LIO2 global optimization
```

The serial protocol parser is independent of ROS and retains the original ASENSING
frame header, offsets, lengths, and XOR checksums.
