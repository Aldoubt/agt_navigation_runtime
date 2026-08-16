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

- `agt_odometry`
- `agt_localization`
- `agt_localization_fusion`

`agt_odometry` owns continuous local odometry backend adaptation, the canonical runtime odometry and registered-cloud outputs, and the unique `odom -> base_footprint` transform while its backend is active

Its public runtime outputs are

```text
/agt/odometry/odometry
/agt/odometry/registered_points
```

The FAST-LIVO2 backend-private registered cloud is

```text
/agt/odometry/backend/registered_points
```

`agt_odometry` must not create or persist maps, PCD map artifacts, mapping sessions, map versions, or Site Package assets. Runtime FAST-LIVO2 launch forces PCD saving off

`agt_localization` and the global-correction authority remain separate from local odometry. They own accepted global-pose evidence and canonical `map -> odom`; they do not publish `odom -> base_footprint`

### Navigation Runtime

- `agt_perception`
- `agt_navigation`
- `agt_safety`
- `agt_chassis`

### Mission and Operations

- `agt_bt_executor`
- `agt_mission_manager`
- `agt_experiment_manager`

## V3-02 Ownership Rule

V3-02 removes the inherited runtime `agt_mapping` package instead of retaining a permanent compatibility wrapper

The final state-estimation chain is

```text
sensor adapters
      |
      v
FAST-LIVO2 backend
      |
      v
agt_odometry
  |         |
  |         +----> /agt/odometry/registered_points ----> localization / perception
  |
  +--------------> /agt/odometry/odometry
  |
  +--------------> odom -> base_footprint

agt_localization / global correction
  +--------------> map -> odom
```

Algorithm behavior is intentionally unchanged in V3-02; the milestone separates responsibilities and freezes the runtime interface before later fusion, navigation, and bringup work
