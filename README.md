# AGT Navigation Runtime

ROS 2 runtime for agricultural robot autonomous navigation

## Project Positioning

This repository owns the runtime execution side of the AGT navigation system

```text
Site Package + Vehicle Profile + Task
                 |
                 v
             Odometry
                 |
                 v
            Localization
                 |
                 v
       Local Perception / Costmap
                 |
                 v
       Planner / Controller
                 |
                 v
          Mission / BehaviorTree
                 |
                 v
              Safety
                 |
                 v
              Chassis
```

Offline mapping, map processing, semantic-map generation, route-asset generation, and Site Package production remain outside this repository

## V2.5 Boundary

`agt_navigation_v2` produces versioned READY deployment assets

`agt_navigation_runtime` consumes those assets for robot execution

The runtime repository must not depend on the V2.5 source tree, V2.5 install space, relative paths into V2.5, or a V2.5 ROS workspace overlay

The intended repository boundary is

```text
agt_navigation_v2
        |
        | produces
        v
Versioned READY deployment artifact
        |
        | consumes
        v
agt_navigation_runtime
```

## Current Status

Current milestone: **V3 Runtime Bringup Integration**

The extracted ROS 2 Humble workspace previously completed an independent local build with 23 packages. The current BUNKER runtime branch adds the Runtime-owned `agt_bringup` package; that package must pass the P0 independent-build gate before this branch is treated as runtime-validated.

Current migrated runtime capabilities include

- Robot description and platform profiles
- Sensor adapters and sensor health monitoring
- FAST-LIVO2 runtime backend
- ICP / NDT relocalization
- Local obstacle perception
- Nav2 runtime planning and control
- Safety arbitration
- Chassis adapter
- BehaviorTree capability layer
- Mission manager
- Experiment manager
- Runtime-owned unified bringup

## Current Runtime Packages

```text
src/
├── agt_bringup
├── agt_bt_executor
├── agt_chassis
├── agt_description
├── agt_experiment_manager
├── agt_interfaces
├── agt_localization
├── agt_localization_fusion
├── agt_mapping
├── agt_mission_manager
├── agt_navigation
├── agt_perception
├── agt_safety
├── agt_sensor_adapters
└── agt_sensor_monitor
```

`agt_mapping` is retained temporarily during extraction compatibility work and will be narrowed toward continuous odometry/runtime estimator ownership in a later V3 milestone

## Third-party Runtime Dependencies

The initial extraction keeps only dependencies required by the current runtime baseline

```text
third_party/
├── bunker_ros2
├── fast_livo2_ros2
├── livox_ros_driver2
├── ndt_omp_ros2
├── relocalization_core
├── rpg_vikit_ros2_fisheye
└── ugv_sdk
```

Qt map tooling and offline coverage-planning dependencies are intentionally excluded from the V3 runtime core

## Development Roadmap

```text
V3-00  Runtime extraction baseline
V3-01  Runtime contracts and package cleanup
V3-02  Odometry / localization separation
V3-03  Navigation / safety / chassis execution
V3-04  Site + Vehicle + Task contracts
V3-05  BehaviorTree / Mission integration
V3-06  Unified runtime bringup
V3-07  Ackermann greenhouse validation
```

## Build

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
```

A valid V3 workspace must build without sourcing `agt_navigation_v2/install/setup.bash`

## Unified Runtime Bringup

P0 introduces a Runtime-owned system entry point. The safe default starts no Nav2,
localization, or chassis driver:

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_bringup system.launch.py platform:=bunker
```

For real navigation, provide the READY map/PCD inputs explicitly and enable each layer:

```bash
ros2 launch agt_bringup system.launch.py \
  platform:=bunker \
  start_localization:=true \
  start_navigation:=true \
  navigation_map:=/absolute/path/to/site.yaml \
  global_map_pcd:=/absolute/path/to/localization_map.pcd \
  global_map_processing_record:=/absolute/path/to/localization_map.processing.yaml
```

`start_chassis:=true` is a separate explicit action and does not bypass `agt_safety`.
The outer Runtime launch fixes the BUNKER driver's `publish_driver_odom_tf` to `false`, so FAST-LIVO2 remains the only `odom -> base_footprint` publisher.

## Core Design Rule

```text
V2.5 owns asset production
V3 owns robot execution
V2.5 -> V3 only through versioned deployment artifacts
```
