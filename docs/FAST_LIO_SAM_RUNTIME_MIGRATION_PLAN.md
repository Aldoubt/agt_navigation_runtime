# FAST-LIO-SAM Runtime Migration Plan

## Goal

Replace the current SLAM backend path with a Fast-LIO-SAM based pipeline while keeping Nav2, HMI and camera task interfaces stable.

## Target pipeline

MID360 + IMU

```
FAST-LIO-SAM
    |
    +-- optimized trajectory
    +-- loop closure backend
    +-- global point cloud map

agt_map_export
    |
    +-- PCD
    +-- PGM/YAML

Nav2 map_server

Qt HMI
    |
    +-- waypoint editing
    +-- mission dispatch

Camera runtime
    |
    +-- photo action
    +-- pose/GNSS record
```

## Migration phases

### Phase 1: SLAM baseline

- Import ROS2 FAST-LIO-SAM package
- Verify MID360 bag replay
- Verify optimized trajectory
- Verify loop closure

### Phase 2: Map export

Add `agt_map_export`:

Input:
- optimized point cloud

Output:
- nav2 compatible pgm/yaml
- 3D map artifact

### Phase 3: Runtime interfaces

Add:

- `/agt/slam/current_pose`
- `/agt/map/save`
- `/agt/map/load`

### Phase 4: RTK preparation

Add GNSS abstraction:

Input:
- sensor_msgs/NavSatFix

Future:
- GTSAM GPS factor integration

### Phase 5: HMI integration

Keep Qt independent from SLAM implementation.

Qt consumes runtime interfaces only.
