# Runtime Boundary

## Repository Ownership

`agt_navigation_v2` owns offline navigation asset production

`agt_navigation_runtime` owns robot-side execution of versioned deployment assets

The only supported cross-repository dependency is a deployable Site Package artifact

```text
agt_navigation_v2
        |
        | produces
        v
Versioned READY Site Package
        |
        | consumes read-only
        v
agt_navigation_runtime
```

The runtime repository must not require

- the V2.5 source tree
- the V2.5 install space
- a V2.5 ROS workspace overlay
- a Git submodule pointing to V2.5
- absolute or relative filesystem paths into a V2.5 checkout

## Runtime Package Ownership

### Foundation

- `agt_interfaces`
- `agt_description`
- `agt_sensor_adapters`
- `agt_sensor_monitor`

### State Estimation

- `agt_mapping`
- `agt_localization`
- `agt_localization_fusion`

`agt_mapping` is transitional in V3-01. It may provide continuous runtime LIO odometry and registered cloud behavior required for compatibility, but no new map production, PCD artifact production, offline processing, or Site Package responsibilities may be added

### Navigation Runtime

- `agt_perception`
- `agt_navigation`
- `agt_safety`
- `agt_chassis`

### Mission and Operations

- `agt_bt_executor`
- `agt_mission_manager`
- `agt_experiment_manager`

## V3-01 Compatibility Rule

V3-01 freezes contracts before package surgery. Existing runtime packages keep their names and algorithm behavior so the independent 23-package colcon baseline remains comparable

Package renaming, dependency cleanup, `agt_mapping` extraction, Site Manager implementation, and chassis backend splitting belong to later milestones
