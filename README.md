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

See [`docs/architecture/runtime_boundary.md`](docs/architecture/runtime_boundary.md) for the frozen repository and package ownership boundary

## Current Status

Current milestone: **V3-02 Odometry / Localization Separation**

The V3-00 extracted ROS 2 Humble workspace completed an independent local build with 23 packages finished successfully. V3-01 then froze Vehicle Profile and deployable Site Package contracts with fail-closed validation

V3-02 replaces the inherited runtime `agt_mapping` role with `agt_odometry`. FAST-LIVO2 adapter math is intentionally unchanged; the change is package responsibility, public topic ownership, and removal of runtime PCD/map-production controls

Current migrated runtime capabilities include

- Robot description and platform profiles
- Sensor adapters and sensor health monitoring
- FAST-LIVO2 continuous odometry through `agt_odometry`
- ICP / NDT relocalization
- Local obstacle perception
- Nav2 runtime planning and control
- Safety arbitration
- Chassis adapter
- BehaviorTree capability layer
- Mission manager
- Experiment manager

## Runtime Contract Validation

Install the lightweight validation dependencies

```bash
python3 -m pip install -r requirements-contracts.txt
```

Validate the real MK-mini Vehicle Profile against a Site Package

```bash
python3 tools/validate_runtime_contracts.py \
  --vehicle profiles/platforms/mk_mini.yaml \
  --site tests/contracts/fixtures/site_valid
```

A READY package reports

```text
[PASS] vehicle schema
[PASS] site schema
[PASS] relative paths
[PASS] required assets
[PASS] navigation map image
[PASS] SHA256 integrity
[PASS] vehicle compatibility
[PASS] Ackermann geometry
Runtime contract validation: READY
```

Contract validation is fail-closed. Unsupported schema versions, unsafe paths, missing direct or transitive assets, hash failures, incompatible vehicles, or invalid Ackermann geometry return a non-zero exit code

Run the pure-Python contract and odometry-boundary regressions with

```bash
python3 -m pytest -q tests/contracts tests/odometry
```

Contract definitions are documented in

- [`docs/architecture/vehicle_profile_contract.md`](docs/architecture/vehicle_profile_contract.md)
- [`docs/architecture/site_package_contract.md`](docs/architecture/site_package_contract.md)
- [`docs/superpowers/specs/2026-08-16-v3-02-odometry-separation-design.md`](docs/superpowers/specs/2026-08-16-v3-02-odometry-separation-design.md)

## Odometry Runtime Contract

`agt_odometry` is the runtime owner of continuous local state-estimation adaptation

```text
FAST-LIVO2 backend
        |
        v
agt_odometry
├── /agt/odometry/odometry
├── /agt/odometry/registered_points
└── odom -> base_footprint
```

The backend-private registered cloud is `/agt/odometry/backend/registered_points`

`agt_odometry` does not create maps, mapping sessions, `localization_map.pcd`, map versions, or Site Package assets. `fast_livo2_odometry.launch.py` forces FAST-LIVO2 PCD saving off

Global localization remains separate: localization/global correction owns `map -> odom`

## Current Runtime Packages

```text
src/
├── agt_bt_executor
├── agt_chassis
├── agt_description
├── agt_experiment_manager
├── agt_interfaces
├── agt_localization
├── agt_localization_fusion
├── agt_mission_manager
├── agt_navigation
├── agt_odometry
├── agt_perception
├── agt_safety
├── agt_sensor_adapters
└── agt_sensor_monitor
```

The V2.5-derived `agt_mapping` package is not part of the V3 runtime source tree. Mapping and offline asset generation remain owned by `agt_navigation_v2`

## Third-party Runtime Dependencies

The runtime keeps only dependencies required by the current execution baseline

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
V3-01  Runtime contracts and boundary freeze
V3-02  Odometry / localization separation
V3-03  Navigation / safety / chassis execution
V3-04  Site runtime loading + Vehicle + Task binding
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

## Core Design Rule

```text
V2.5 owns asset production
V3 owns robot execution
V2.5 -> V3 only through versioned deployment artifacts
```
