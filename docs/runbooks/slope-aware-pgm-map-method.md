# 坡地 PGM 导航地图工具：方法收集（暂不实现）

本文只冻结第一版工具的输入、算法和验收方法，不新增可执行程序。后续工具应优先扩展
`src/agt_map_builder` 的 PCD/PGM 导出能力，并复用 `src/agt_map_reconstruction` 的
2.5D 地形栅格和射线证据设计；不要修改 FAST-LIVO2、Nav2 或第三方驱动。

## 当前导航启动链与传感器

正常 BUNKER 导航由 `agt_hardware_bringup/bunker_mid360.launch.py`、
`agt_odometry/fast_livo2_odometry.launch.py`、定位和 `agt_navigation/navigation.launch.py`
组成：

| 输入/设备 | 当前接口 | 使用方法 |
|---|---|---|
| MID360 LiDAR | `/agt/sensors/lidar/custom`，`livox_ros_driver2/msg/CustomMsg` | `agt_livox_self_filter` 去除车体自身点后，作为 FAST-LIVO2 LiDAR 输入 |
| MID360 内置 IMU | `/agt/sensors/imu/data`，`sensor_msgs/msg/Imu` | FAST-LIVO2 的惯导、重力/偏置估计和扫描去畸变 |
| 轮速/底盘里程计 | `/agt/chassis/odometry` | 底盘状态和相关运行检查；不是已注册点云的全局位姿 |
| 注册点云 | `/agt/odometry/registered_points` | 定位 ICP/NDT、局部障碍物过滤 |
| 局部障碍物 | `/agt/perception/obstacle_cloud` | Nav2 global/local costmap 与 Collision Monitor 的 pointcloud 观测 |
| 相机/GNSS | 默认关闭/非必需 | 不属于当前 BUNKER 导航主传感器闭环 |

FAST-LIVO2 原生 TF 在工程启动中关闭，由适配器输出 `odom -> base_footprint`；固定链由
`robot_state_publisher` 发布：

```text
base_footprint -> base_link -> lidar_link -> livox_frame / imu_link
```

Nav2 采用 `map` 为全局坐标、`base_footprint` 为机器人基座，规划/控制使用
`/agt/odometry/odometry` 和 `/agt/perception/obstacle_cloud`。

## 指定 bag 的可用证据

数据源：`runtime/rosbag/bunker_mid360_mapping_20260901_211105`。

- `/agt/sensors/imu/data`：77909 条，约 200 Hz；初始稳定段重力方向对应简化倾角约 14.8°。
- `/agt/sensors/lidar/custom`：3896 条，约 10 Hz，保留逐点时间。
- `/agt/commissioning/mapping/registered_points`：3891 条，已处于连续建图坐标，可作为离线地图首选输入。
- `/tf`：0 条；`/tf_static`：1 条。因此不能用该 bag 对 raw LiDAR 逐帧重建全局地图，除非另有动态位姿。

本次初步外参把 `base_link -> lidar_link` 的 pitch 设置为 `0.2580 rad`（约 14.8°），
并在固定描述包中保留 CAD 名义 pitch 加小 residual 的分层表达。两处均为
`calibration_verified: false`，不可视为最终标定。

## 计划中的坡地 PGM 工具方法

### 输入模式

第一版优先支持已注册点云离线模式：输入 `PointCloud2`/PCD、固定地图 frame、输出目录和
参数 YAML。使用本 bag 时选 `/agt/commissioning/mapping/registered_points`；不要把
`/agt/chassis/odometry` 冒充 LiDAR 全局位姿。实时兼容模式再接入
`/cloud_registered + odometry`，要求逐帧时间同步和 TF 可查询。

### 地形与坡度判定

1. 体素降采样并剔除 NaN、超量程和明显离群点。
2. 在 XY 栅格内用局部邻域平面拟合（法向量与点到平面残差），不依赖绝对 Z 阈值。
3. 用平面法向量与重力方向计算坡度：`slope = acos(|n · g|)`。
4. 结合局部高度差、平面残差和法向一致性，把点分为 ground / obstacle / unknown。
5. 用时间窗口内的出现次数和位置稳定性抑制动态物体；保留 ground、obstacle、static
   点云作为调试产物。

### PGM 输出语义

使用 Nav2 标准 `map.yaml + map.pgm`：free=254、occupied=0、unknown=205，原点为
地图左下角，PGM 行按图像坐标翻转。坡度阈值建议分为：可通行 free、保守 unknown、
不可通行 occupied；阈值必须进入 `terrain.yaml` 和处理报告。同步输出高程、坡度、
粗糙度/置信度栅格，避免 PGM 丢失坡度依据。

### 验收方法

先在指定 bag 上离线重放并检查输入 frame、点云数量、地图原点和像素尺寸；再用 RViz
同时显示 ground/obstacle/map，人工检查斜坡、障碍物、空洞和未知区域。最后运行 Nav2
map_server 加载生成的 YAML，并用地图审查/版本封装流程确认 hash。工具实现前不生成或
替换生产导航地图。
