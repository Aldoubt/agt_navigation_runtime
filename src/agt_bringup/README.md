# agt_bringup

Runtime-only composition for `agt_navigation_runtime`.

It may compose robot description, sensors, sensor monitoring, continuous odometry,
localization, local perception, Nav2, safety, chassis, and Runtime experiment ownership. It must
not contain Qt, semantic-map generation, coverage planning, offline map production, or dependencies
on `agt_navigation_v2` source/install trees.

The default `system.launch.py` startup is motion-safe: localization, Nav2, GNSS, and the BUNKER CAN
driver remain opt-in until their required inputs are supplied.

## Runtime startup modes

```text
start_sensor=true          MID360 driver
start_sensor_monitor=true  stream health
start_gnss=false           canonical NavSatFix adapter; optional
start_odometry=true        FAST-LIVO2 runtime odometry, PCD saving forced off
start_perception=true      local obstacle baseline
start_localization=false   NDT/ICP + GlobalCorrectionManager, requires PCD assets
start_navigation=false     Nav2, requires localization and navigation map
start_chassis=false        BUNKER CAN driver + safety/guard, explicit opt-in
```

The BUNKER driver setting `publish_driver_odom_tf=false` is fixed by the outer Runtime composition.
`odom -> base_footprint` therefore remains owned by the FAST-LIVO2 adapter. The chassis launch owns
the safety-controller inclusion when `operation_mode:=control`, so `system.launch.py` does not
start a second standalone safety node.

## Safe default

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_bringup system.launch.py platform:=bunker
```

This starts the robot description and enabled sensor/odometry/perception baseline, but not GNSS,
localization, Nav2, or the BUNKER CAN driver.

## Optional GNSS

Runtime accepts any upstream driver that publishes `sensor_msgs/msg/NavSatFix`; the receiver-specific
topic is configured at launch and normalized to `/agt/sensors/gnss/fix` with frame `gps_link`.

```bash
ros2 launch agt_bringup system.launch.py \
  start_gnss:=true \
  gnss_input_topic:=/receiver_specific/navsat_fix
```

`/receiver_specific/navsat_fix` is only an example shape. Replace it with the actual absolute topic
reported by `ros2 topic list` and confirm its type with `ros2 topic type`. GNSS absence must not
block the MID360 + IMU + FAST-LIVO2 path.

## Navigation without chassis motion

```bash
ros2 launch agt_bringup system.launch.py \
  platform:=bunker \
  start_localization:=true \
  start_navigation:=true \
  start_chassis:=false \
  navigation_map:=/absolute/path/to/site.yaml \
  global_map_pcd:=/absolute/path/to/localization_map.pcd \
  global_map_processing_record:=/absolute/path/to/localization_map.processing.yaml
```

`start_navigation:=true` is rejected unless `start_localization:=true`. The navigation map,
localization PCD and processing record are validated as existing files before the optional
localization/Nav2 composition is admitted.

## Chassis control opt-in

Only enable the real BUNKER driver in `control` mode after sensor, TF, odometry, localization,
perception and safety gates have been checked:

```bash
ros2 launch agt_bringup system.launch.py \
  platform:=bunker \
  start_chassis:=true \
  chassis_operation_mode:=control \
  can_interface:=can0
```

In control mode the command path remains Nav2/Collision Monitor -> `agt_safety` -> chassis command
guard -> BUNKER driver. The unified bringup does not create a direct bypass.

## P1/P2 calibration capture

The dedicated capture entry is intentionally command-inert from ROS:

```bash
cd ~/agt_navigation_runtime
source /opt/ros/humble/setup.bash
source install/setup.bash
ip -details link show can0
ros2 launch agt_bringup calibration_capture.launch.py \
  can_interface:=can0 \
  start_gnss:=false
```

It fixes the composition to MID360 on, sensor monitor on, FAST-LIVO2 on, BUNKER driver on in
`monitor` mode, perception/localization/navigation off, and starts `agt_experiment_manager`.
In monitor mode the BUNKER driver's ROS `/cmd_vel` subscription is remapped to an unpublished sink;
this launch intentionally provides no ROS motion command path. Dynamic excitation must therefore use
an independently validated manual/RC chassis control path. If such a path is unavailable, do not
turn this capture launch into control mode as a shortcut; validate a separate controlled-motion
procedure first.

For a GNSS-equipped capture:

```bash
ros2 launch agt_bringup calibration_capture.launch.py \
  can_interface:=can0 \
  start_gnss:=true \
  gnss_input_topic:=/receiver_specific/navsat_fix
```

Again, replace the example receiver topic with the actual standard `NavSatFix` topic discovered on
the machine.

### Capture preflight

Before recording, verify the required streams and static frames:

```bash
ros2 topic hz /agt/sensors/lidar/custom
ros2 topic hz /agt/sensors/imu/data
ros2 topic hz /agt/chassis/odometry
ros2 topic hz /agt/mapping/odometry
ros2 topic hz /agt/mapping/registered_points
ros2 run tf2_ros tf2_echo base_link lidar_link
ros2 run tf2_ros tf2_echo base_link gps_link
```

For GNSS-enabled runs also require:

```bash
ros2 topic type /agt/sensors/gnss/fix
ros2 topic echo /agt/sensors/gnss/fix --once
```

Expected GNSS type: `sensor_msgs/msg/NavSatFix`.

### Create the experiment and start recording

Run the launch from the repository root so the relative platform profile below resolves to the
tracked Runtime file. Create and immediately start an experiment:

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 5,
  experiment_title: 'bunker-wheel-lio-calibration',
  objective: 'collect synchronized BUNKER wheel odom and FAST-LIVO2 evidence',
  profile_id: '',
  platform_profile: 'profiles/platforms/bunker.yaml',
  calibration_profile: 'bunker-wheel-lio-p1',
  start_experiment: true
}"
```

Copy the returned `experiment_id`, replace `<returned_experiment_id>` below with that actual value,
and start the explicit `calibration` profile:

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 1,
  experiment_id: '<returned_experiment_id>',
  profile_id: 'calibration'
}"
```

Do not start another `ros2 bag record` process manually; `agt_experiment_manager` is the sole
recording owner.

### Excitation sequence

Keep one continuous bag spanning:

```text
1. static at start
2. straight forward
3. straight backward
4. large-radius left turn
5. large-radius right turn
6. figure eight
7. approximately +90/-90 degree turns
8. approximately +180/-180 degree turns
9. gentle slope up/down when available
10. static at end
```

Spin-in-place and visibly slipping segments may be retained for diagnosis, but P3 will down-weight or
exclude them rather than treat tracked-wheel odometry as ground truth.

### Stop and complete

Stop the manager-owned recorder:

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 2,
  experiment_id: '<returned_experiment_id>'
}"
```

Then complete the experiment:

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 6,
  experiment_id: '<returned_experiment_id>',
  result_status: 'COMPLETED'
}"
```

### Validate the completed bag

Use the actual experiment and bag directory returned by the manager; the angle-bracket values are
only documentation placeholders:

```bash
python3 tools/calibration/validate_calibration_bag.py \
  runtime/experiments/<experiment_id>/rosbag/<calibration_bag_directory>
```

For a GNSS-required dataset:

```bash
python3 tools/calibration/validate_calibration_bag.py \
  runtime/experiments/<experiment_id>/rosbag/<calibration_bag_directory> \
  --require-gnss
```

The recording profile includes `/agt/navigation/cmd_vel` for auditability, but a command-inert
monitor capture is valid with zero command messages. The metadata gate requires non-empty TF,
MID360, IMU, BUNKER wheel odometry/status, FAST-LIVO2 odometry/registered cloud and diagnostics;
GNSS becomes mandatory only with `--require-gnss`.
