# agt_odometry

`agt_odometry` owns continuous local odometry adaptation for the V3 runtime.

## Public runtime contract

```text
/agt/odometry/odometry
/agt/odometry/registered_points
odom -> base_footprint
```

The current backend is FAST-LIVO2. Backend-native topics remain private implementation details; `/agt/odometry/backend/registered_points` is the internal registered-cloud bridge into the adapter.

The adapter preserves the V3-00/V3-01 pose and twist conversion behavior: it converts the backend IMU pose to `base_footprint` using the configured static extrinsic, accounts for the sensor lever arm in twist, republishes registered points in the same continuous world coordinates with frame `odom`, and optionally publishes the unique `odom -> base_footprint` TF.

## Runtime-only boundary

This package does **not** produce navigation assets. It must not create or persist:

- `localization_map.pcd`
- map versions
- mapping sessions
- Site Package assets

`fast_livo2_odometry.launch.py` forces FAST-LIVO2 PCD saving off. Mapping and map-asset production remain owned by `agt_navigation_v2`.

## Launch

```bash
ros2 launch agt_odometry fast_livo2_odometry.launch.py
```

The normal MID360 input is `/agt/sensors/lidar/custom_filtered`, produced by `agt_livox_self_filter`. `start_lidar_self_filter:=false` is retained only for explicit baseline/debug use and switches the backend input to `/agt/sensors/lidar/custom`.

FAST-LIVO2 remains vendor-pinned under `third_party/fast_livo2_ros2`; V3-02 does not change its estimation algorithm or the adapter math.
