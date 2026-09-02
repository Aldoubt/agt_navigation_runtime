# FAST-LIO-SAM Bag Validation Plan

## Goal

Verify that FAST-LIO-SAM can replace the current SLAM backend for the AGT runtime workflow.

## Workspace

Create an isolated ROS2 Humble workspace:

```
~/agt_fastlio_sam_ws/src
```

Keep this workspace independent from the production runtime workspace.

## Validation pipeline

```
rosbag2
  |
  +-- livox lidar
  +-- imu
  |
FAST-LIO-SAM mapping
  |
  +-- optimized trajectory
  +-- registered cloud
  +-- pose graph
  |
map export
  |
  +-- pcd
  +-- pgm/yaml
```

## Acceptance

- no TF tree conflict
- stable odometry
- loop closure works
- optimized map exported
- Nav2 can load generated map

## Next integration

After validation:

1. expose pose through agt_slam_runtime
2. connect Qt HMI waypoint workflow
3. add RTK interface
