# Autolabor C1 camera-gimbal source import

- Upstream repository: https://github.com/LJM-224/autolabor_c1_ros2_ws
- Upstream branch: `main`
- Upstream archive: `autolabor_c1_ros2_ws_modified(1).tar.gz`
- Upstream commit at import request: `7592b291de56c06f78a3e42a99aa74a281d7fbba`
- Archive SHA256: `926b4c2526e764e3c1fef87ee09757fae625a430f39cc2294bf023c50fea36a6`
- Import policy: source snapshot only; `build/`, `install/`, `log/`, Git metadata and Python caches are excluded.
- Runtime role: camera + gimbal driver/capability; Nav2 mission logic remains outside this vendor directory.

## ROS package directories

- `autolabor_c1_bringup`
- `camera_gimbal_capability`
- `camera_gimbal_interfaces`
- `opencv_camera_node`
- `pantilt_camera_serial`
- `rviz_pantilt_plugin`

## Integration rule

Keep device paths, runtime remaps and inspection mission orchestration outside the vendor source unless an upstream-compatible bug fix is required.
