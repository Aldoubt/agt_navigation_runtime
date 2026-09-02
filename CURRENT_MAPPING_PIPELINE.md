# Current Mapping Pipeline

审计对象：当前 ROS 2 工作空间及真实 bag `runtime/rosbag/bunker_mid360_mapping_20260901_211105`。

## 1. 当前数据流

### FAST-LIO 建图前端 / FAST-LIVO2 运行时里程计

两个建图入口现在使用 `third_party/FAST_LIO_SLAM_ros2` 的 `fast_lio/fastlio_mapping`。
正常导航连续里程计仍使用 `third_party/fast_livo2_ros2`，两者职责保持分离。

建图前端启动和参数由：

- `src/agt_field_commissioning/launch/field_mapping.launch.py`
- `src/agt_map_reconstruction/launch/lio_mapping_bag.launch.py`
- `src/agt_odometry/config/fast_lio_mid360_mapping.yaml`

负责。backend 的原生输出包括：

```text
/cloud_registered
/cloud_registered_lidar
/aft_mapped_to_init
```

工程 launch 将 `/cloud_registered` 重映射到：

```text
/agt/odometry/backend/registered_points
```

适配器 `src/agt_odometry/scripts/fast_livo2_adapter.py` 再输出：

```text
/agt/odometry/odometry
/agt/odometry/registered_points
```

适配器默认把 registered cloud 标为 `odom`，并把 backend 位姿转换为 `odom -> base_footprint`。FAST-LIVO2 backend 的 `common.publish_tf` 在工程 launch 中被关闭，避免原生 TF 与适配器重复发布。

### 本次 bag 的实际 topic

bag 没有录制用户所写的旧名字 `/livox/lidar`、`/livox/imu`、`/odom`，实际使用的是：

```text
/agt/sensors/lidar/custom          livox_ros_driver2/msg/CustomMsg  3896
/agt/sensors/imu/data              sensor_msgs/msg/Imu             77909
/agt/chassis/odometry              nav_msgs/msg/Odometry            39019
/agt/commissioning/mapping/registered_points  sensor_msgs/msg/PointCloud2 3891
/tf                                0
/tf_static                         1
```

bag 中已有的 `registered_points` 可直接作为离线地图输入，但它属于 commissioning 输出，不等价于本次新模块实时订阅的 `/cloud_registered`。

### TF

bag 的固定链为：

```text
base_footprint -> base_link -> lidar_link -> livox_frame
                                      \-> imu_link
```

bag 没有动态 `/tf`，因此无法仅靠 bag 重建 FAST-LIVO2 的动态位姿。实时运行时，期望的输入链是：

```text
map -> odom -> base_footprint -> base_link -> lidar_link
```

### 新模块目标数据流

```text
PointCloud2 (/cloud_registered 或 bag registered_points)
        + Odometry (/odometry 或 /agt/odometry/odometry)
        ↓
体素降采样
        ↓
每个 XY cell 的局部地面平面/坡度估计
        ↓
ground / non-ground
        ↓
跨时间 voxel 稳定性过滤
        ↓
射线 free-space + occupied hit 的 log-odds 栅格
        ↓
OccupancyGrid + map.pgm/map.yaml + terrain.yaml + PCD debug outputs
```

## 2. 可复用模块

### `agt_map_builder`

`src/agt_map_builder` 已有 PCD 离线加载、体素降采样、地形栅格、坡度/高度差判定和 Nav2 PGM/YAML 导出能力。它适合复用其输出格式和参数思路，但当前实现：

- 输入是 PCD，不是 ROS `PointCloud2`/`Odometry`；
- 使用每 cell 最低点和 `np.gradient`，不是局部 plane 拟合；
- 没有射线 free-space 和 log-odds 累积；
- 没有时间一致性的动态过滤；
- 没有 ground/obstacle/static PCD debug 输出。

### `agt_field_commissioning`

可复用：

- `rtabmap_grid_projector.cpp` 的 PGM/YAML 导出约定、法向地面分割思路和高度/坡度参数；
- `project_navigation_map.py` 的 finalized map 工作流；
- map artifact/review 的文件组织思路。

不直接复用 RTAB-Map 作为新模块核心，因为本阶段需要保留每个 cell 的地面、障碍和动态时间统计，并输出 terrain metadata。

### FAST-LIVO2 内部体素

FAST-LIVO2 有内部 voxel map 和已注册点云，但它是估计器内部数据结构，不应作为新地图模块的接口或修改对象。

## 3. 缺失模块

当前工程缺少一个独立的 ROS 2 离线重建包，缺少：

1. `PointCloud2 + Odometry` 的统一订阅/rosbag replay 入口；
2. 使用 odometry 把各帧点云变换到固定地图 frame 的缓存/同步逻辑；
3. 适用于坡地的 XY cell 局部 plane 拟合；
4. 基于法向夹角、点到平面距离的 ground/non-ground 分类；
5. 基于 voxel 出现次数和时间窗口的静态/短时障碍判定；
6. 带 ray tracing 的 log-odds OccupancyGrid；
7. `ground_cloud.pcd`、`obstacle_cloud.pcd`、`static_cloud.pcd`、`terrain.yaml` 和处理报告的统一导出；
8. RViz2 的 ground/obstacle/static/map 调试显示。

## 4. 约束和风险

- 不修改 FAST-LIO/FAST-LIVO2 或 Nav2；
- bag 的 `/tf` 为 0，因此离线模块必须使用 bag 中已注册的全局 `registered_points`，或使用另一个包含动态位姿的 replay；
- `/agt/commissioning/mapping/registered_points` 是最可靠的本次离线输入，因为它已经由建图过程注册到连续世界坐标；
- 若直接使用逐帧 raw LiDAR，必须同时提供对应时间的 FAST-LIO odometry/TF，否则不能正确拼接地图；
- 本 bag 中的 odometry 是底盘 `bunker_odom -> base_footprint`，不是 FAST-LIO `/aft_mapped_to_init`，不能将其误当作 LiDAR 全局位姿；
- 地面分割不应依赖绝对 Z 阈值，因为 FAST-LIO 地图原点不是地面 datum，且目标场景可能有坡地。

## 5. 推荐实现边界

新包 `agt_map_reconstruction` 应首先支持两种输入模式：

- offline：订阅/读取已经注册到固定 frame 的 PointCloud2，并使用对应 odometry 做时间和 frame 校验；
- realtime-compatible：保持相同处理器接口，未来直接接入 `/cloud_registered` 与 odometry。

第一版离线验收应优先使用 bag 中已有的 `/agt/commissioning/mapping/registered_points`，同时将输入 frame、odometry frame、是否发生 TF 变换写入报告，避免把底盘 odometry 错用于点云注册。
