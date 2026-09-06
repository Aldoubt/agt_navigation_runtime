# Field navigation rosbag acceptance

This is a software-chain acceptance procedure. `field_capture_backend` remains
`placeholder`; no real camera is started or claimed to be tested.

## Phase A — development-machine evidence

An old MID360 sensor-only bag does **not** verify a real Nav2 motion closed
loop. Split the software acceptance into two independent gates.

### A1 — rosbag data chain

For bags whose topics are `/livox/lidar` and `/livox/imu`, replay with the
runtime topic names:

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 bag play <MID360_BAG> --clock \
  --remap /livox/lidar:=/agt/sensors/lidar/custom \
  --remap /livox/imu:=/agt/sensors/imu/data
```

Start the odometry/filter path appropriate for the bag. With
`start_hardware:=false`, `field_navigation` does not start robot description,
hardware TF, or the self-filter; provide those explicitly from the installed
description/static TF launch before starting the data consumers:

```bash
ros2 launch agt_description bunker_description.launch.py
ros2 launch agt_sensor_adapters lidar_self_filter.launch.py \
  platform_profile:=$VEHICLE_PROFILE \
  input_topic:=/agt/sensors/lidar/custom \
  output_topic:=/agt/sensors/lidar/custom_filtered \
  use_sim_time:=true
```

Use the actual launch argument names exposed by `--show-args` on the installed
packages. Alternatively replay a bag that already contains `/tf_static` and a
valid `robot_description` publisher. Verify only the data chain:

```bash
ros2 topic echo --once /agt/sensors/lidar/custom
ros2 topic echo --once /agt/sensors/imu/data
ros2 topic echo --once /agt/odometry/odometry
ros2 run tf2_ros tf2_echo odom base_footprint
ros2 run tf2_ros tf2_echo base_footprint base_link
ros2 run tf2_ros tf2_echo base_link lidar_link
```

The odometry message must have `header.frame_id=odom` and
`child_frame_id=base_footprint`. Confirm that low-speed samples remain fresh
for the configured stable window and that stale/invalid data does not settle.

### A2 — mock/sim task chain

Use a Nav2/mock setup that actually provides `NavigateToPose` success; do not
claim that A1 alone proves this chain. Start the field entry point with the
deployed Site arguments:

```bash
ros2 launch agt_field_commissioning field_navigation.launch.py \
  site_id:=$SITE_ID site_revision:=$SITE_REVISION \
  sites_root:=$SITES_ROOT state_root:=$STATE_ROOT \
  site_vehicle_profile:=$VEHICLE_PROFILE runtime_dir:=$RUNTIME_DIR \
  start_hardware:=false use_sim_time:=true \
  field_capture_backend:=placeholder \
  field_capture_settle_enabled:=true
```

In RViz create ordered P01/P02/P03 and verify:
`Nav2 success → ARRIVED → WAITING_FOR_SETTLE → SETTLED → placeholder capture →
RETURNING_HOME → SUCCEEDED`. A missing/stale odometry stream or settle timeout
must fail before capture. This validates task ordering and evidence, not
physical vehicle motion.

```bash
ros2 topic list
ros2 node list
ros2 action list
ros2 service list
```

The result message prints `images saved to: <run_dir>`. Inspect that directory:

```bash
find "$RUNTIME_DIR" -path '*/inspection_runs/*' -maxdepth 5 -type f | sort
cat "$RUN_DIR/summary.json"
cat "$RUN_DIR/P01_*/result.json"
```

The placeholder artifact is `image.pgm`; `summary.json` must include a
successful HOME result and every waypoint result must include a `settle` record.

## Phase B — BUNKER real closed loop

Record at least `/tf`, `/tf_static`, `/agt/odometry/odometry`, FAST-LIVO2
inputs/outputs, Nav2 feedback/commands, and the required safety topics. With
the vehicle stationary, test 30 seconds, straight/reverse motion, left/right
turns, in-place rotation, and motion-then-stop. Then run one Nav2 stop, a
three-point inspection, and HOME return at low speed under the approved safety
procedure. Tune only these launch parameters from the bag:

```text
field_capture_settle_linear_velocity_threshold
field_capture_settle_angular_velocity_threshold
field_capture_settle_stable_duration
field_capture_settle_timeout
field_capture_settle_odom_stale_timeout
```

This is the first gate that can claim `Nav2 → BUNKER → settle → capture → HOME`.
Run it at low speed under the approved safety procedure. Real camera acceptance
is separate: only after this placeholder chain passes,
start the camera capability at `/agt/camera/capture` and select
`field_capture_backend:=service`.
