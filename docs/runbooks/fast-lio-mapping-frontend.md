# FAST-LIO 建图前端

当前仓库的两个建图入口已切换到
[`rohrschacht/FAST_LIO_SLAM_ros2`](https://github.com/rohrschacht/FAST_LIO_SLAM_ros2)：

- `agt_field_commissioning/field_mapping.launch.py`：实车/commissioning 建图，输出
  `/agt/commissioning/mapping/registered_points`，并保留原有 PCD finalize、raycast
  observer、Gateway 和自身点云滤除流程。
- `agt_map_reconstruction/lio_mapping_bag.launch.py`：bag 建图，FAST-LIO 输出先接入
  `agt_odometry` adapter，再进入 `agt_map_reconstruction` 的地形重建和 PGM 输出。

共享配置是 `agt_odometry/config/fast_lio_mid360_mapping.yaml`。本仓库的 Livox 驱动消息
是 `livox_ros_driver2/msg/CustomMsg`，因此 vendored FAST-LIO 做了消息命名兼容；其
`ikd-Tree` 子模块必须初始化。

FAST-LIO 使用 `mapping.extrinsic_T/extrinsic_R`；配置中的 `extrin_calib.extrinsic_T`
只是旧 raycast observer 的兼容镜像。正常导航的 `agt_odometry/fast_livo2_odometry.launch.py`
仍保留 FAST-LIVO2，不受本次建图前端切换影响。

```bash
git -C third_party/FAST_LIO_SLAM_ros2 submodule update --init --recursive
colcon build --symlink-install --packages-select fast_lio agt_odometry agt_field_commissioning agt_map_reconstruction
```
