# agt_slam_runtime

FAST-LIO-SAM migration runtime layer.

## Goal

Provide a stable interface between SLAM backend and the rest of the robot runtime.

Pipeline:

```
MID360 + IMU
    |
    v
FAST-LIO-SAM
    |
    v
agt_slam_runtime
    |
    +--> Nav2
    +--> Qt HMI
    +--> Camera inspection action
    +--> RTK interface
```

## Planned interfaces

### Pose

```
/agt/slam/current_pose
geometry_msgs/msg/PoseStamped
```

### Map

```
/agt/slam/save_map
/agt/slam/load_prior_map
```

### RTK placeholder

```
/agt/rtk/status
```

## Migration stages

1. Integrate FAST-LIO-SAM ROS2 baseline.
2. Verify MID360 bag replay.
3. Export optimized PCD.
4. Generate Nav2 compatible PGM/YAML.
5. Bridge pose/map services to Qt HMI.
6. Add GNSS factor interface.
