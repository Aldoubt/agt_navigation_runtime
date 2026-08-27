# agt_bringup

Runtime-only composition for `agt_navigation_runtime`.

It may compose robot description, sensors, sensor monitoring, continuous odometry,
localization, local perception, Nav2, safety, and chassis. It must not contain Qt,
semantic-map generation, coverage planning, offline map production, or dependencies on
`agt_navigation_v2` source/install trees.

The default `system.launch.py` startup is motion-safe: localization, Nav2, and the BUNKER
CAN driver remain opt-in until their required map/calibration inputs are supplied.

## P0 startup modes

```text
start_sensor=true          MID360 driver
start_sensor_monitor=true  stream health
start_odometry=true        FAST-LIVO2 runtime odometry, PCD saving forced off
start_perception=true      local obstacle baseline
start_localization=false   NDT/ICP + GlobalCorrectionManager, requires PCD assets
start_navigation=false     Nav2, requires localization and navigation map
start_chassis=false        BUNKER CAN driver + safety/guard, explicit opt-in
```

The BUNKER driver setting `publish_driver_odom_tf=false` is fixed by the outer Runtime
composition. `odom -> base_footprint` therefore remains owned by the FAST-LIVO2 adapter.
The chassis launch owns the safety-controller inclusion when `operation_mode:=control`, so
`system.launch.py` does not start a second standalone safety node.

## Safe default

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_bringup system.launch.py platform:=bunker
```

This starts the robot description and the enabled sensor/odometry/perception baseline, but
not localization, Nav2, or the BUNKER CAN driver.

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

## Chassis opt-in

Only enable the real BUNKER driver after sensor, TF, odometry, localization, perception and
safety gates have been checked:

```bash
ros2 launch agt_bringup system.launch.py \
  platform:=bunker \
  start_chassis:=true \
  can_interface:=can0
```

In control mode the command path remains Nav2/Collision Monitor -> `agt_safety` -> chassis
command guard -> BUNKER driver. The unified bringup does not create a direct bypass.
