# BUNKER + MID360 + FAST-LIVO2 + RTAB-Map + GNSS + Nav2 坡地导航设计

日期：2026-08-27
分支：`feat/bunker-rtabmap-slope-nav`
状态：设计冻结，待实现计划

## 1. 仓库边界

本次功能正式落在 `agt_navigation_runtime`。`agt_navigation_v2` 继续承担离线 Site Asset 生产：基础地图处理、语义地图、Keepout、任务/路线资产、版本与 READY 部署包；`agt_navigation_runtime` 只消费 READY 资产并负责真机运行。

```text
agt_navigation_v2
  -> versioned READY Site Package
  -> agt_navigation_runtime
```

Runtime 不得依赖 V2 源码、V2 install、V2 workspace overlay 或相对路径。

## 2. 本次目标

在现有 Runtime 的 BUNKER / MID360 / FAST-LIVO2 / Nav2 / Safety 基线上完成一条可真机验证的室外坡地导航链：

1. BUNKER CAN、轮速里程计、MID360、IMU、GNSS、TF 一体化启动与诊断。
2. FAST-LIVO2 继续作为高频局部 LiDAR-Inertial odometry 前端。
3. 录制 rosbag2，同时保存 wheel odom、LIO odom、LiDAR、IMU、GNSS、TF、cmd_vel。
4. 离线估计和验证 `base_link -> lidar_link` 平面外参、wheel/LIO 时间偏移和轮速尺度。
5. RTAB-Map 消费外部 LIO、注册点云、IMU、GNSS，提供回环和全局校正证据。
6. GlobalCorrectionManager 继续唯一拥有 `map -> odom`；RTAB-Map 不直接成为项目 TF 权威。
7. RTAB-Map 2D OccupancyGrid 作为 Nav2 global costmap 的静态地图来源之一。
8. `agt_perception` 升级坡地地面分割，输出 `/agt/perception/obstacle_cloud` 给 Nav2 local VoxelLayer 和 Collision Monitor。
9. 最终完成平地、缓坡和 5 m / 7 m / 10 m 定点导航验收。

## 3. Runtime 当前基线与保留约束

必须保持：

- `/agt/mapping/odometry` 是连续 odometry 标准接口。
- `/agt/mapping/registered_points` 是注册点云标准接口。
- FAST-LIVO2 adapter 唯一发布 `odom -> base_footprint`。
- GlobalCorrectionManager 唯一发布 `map -> odom`。
- `agt_safety` 与 chassis guard 不得绕过。
- Nav2 速度链保持 `controller -> collision_monitor -> agt_safety -> agt_chassis`。
- Runtime 默认行为不因本功能启用而改变；RTAB-Map、GNSS、slope profile 都必须显式启用。
- 当前 `agt_mapping` 包名暂不重构，避免下周真机前扩大变更面。

## 4. 目标架构

```text
MID360 + IMU
    |
    v
FAST-LIVO2 -------------------------+
    |                               |
    | odom                          | registered cloud
    v                               v
/agt/mapping/odometry          RTAB-Map backend <----- GNSS NavSatFix
    |                               |
    |                               | global correction evidence
    |                               v
    +----------------------> GlobalCorrectionManager
                                    |
                                    v
                               map -> odom
                                    |
                                    v
                                   Nav2
                         +-----------+-----------+
                         |                       |
                  global costmap          local costmap
                  StaticLayer             VoxelLayer
                  RTAB/READY 2D map       slope-filtered cloud
```

RTAB-Map 是全局校正/图优化后端，不绕开项目已有 localization contract。

## 5. P0：Runtime 独立性与统一 bringup

当前 Runtime 仍残留对 `agt_bringup` 的引用，但仓库内没有对应正式 runtime bringup 包。第一阶段先补一个最小 `agt_bringup`，只负责真机运行组件组合，不迁移 V2 的 Qt、semantic、coverage 逻辑。

最小组成：

```text
agt_description
agt_sensor_adapters
agt_sensor_monitor
agt_mapping
agt_localization / agt_localization_fusion
agt_perception
agt_navigation
agt_safety
agt_chassis
```

目标入口：

```bash
ros2 launch agt_bringup system.launch.py platform:=bunker
```

P0 完成标准：Runtime 在不 source V2 的情况下可独立 build，统一 launch 不引用 V2 install/source tree。

## 6. P1：BUNKER + MID360 + GNSS 硬件基线

冻结 TF：

```text
map -> odom                 GlobalCorrectionManager
odom -> base_footprint      FAST-LIVO2 adapter
base_footprint -> base_link description
base_link -> lidar_link     static/calibrated
base_link -> imu_link       static/calibrated
base_link -> gps_link       static/calibrated
```

禁止第二个发布者拥有上述动态 TF edge。

标准 bag 至少录制：

```text
/agt/sensors/lidar/custom
/agt/sensors/imu/data
/agt/chassis/odometry
/agt/chassis/status
/agt/mapping/odometry
/agt/mapping/registered_points
/agt/sensors/gnss/fix        # 可选但推荐
/agt/navigation/cmd_vel
/tf
/tf_static
```

采集轨迹：静止、前后直线、大半径左右转、8 字、±90°/±180°、缓坡上下坡、静止。

## 7. P2：wheel odom / LIO 离线联合标定

第一阶段优化变量：

```text
x_BL, y_BL, yaw_BL
wheel/LIO time offset dt
linear scale k_v
angular scale k_w
```

`z / roll / pitch` 由机械测量、地面平面和 IMU 重力方向确定，不与 skid-steer 运动学一起全自由优化。

两条轨迹构造相邻运动：

```text
A_i = inv(T_wheel_i) * T_wheel_{i+1}
B_i = inv(T_lio_i)   * T_lio_{i+1}
A_i X = X B_i
```

先求 hand-eye 初值，再做鲁棒非线性 refinement。BUNKER wheel odom 不是 ground truth：直线、大半径转弯高权重；原地急转、明显滑移、强坡滑段降权或剔除。

输出必须包含：候选外参、时间偏移、尺度、训练 bag 残差、独立验证 bag 残差和数据质量报告。

离线 commissioning 工具优先放 `tools/calibration/`，不为了目录形式新建在线 ROS 包。

## 8. P3：FAST-LIVO2 连续 odometry

保持当前 `agt_mapping` Runtime 接口，不重命名包。

验收：

- `/agt/mapping/odometry` 频率、时间戳连续。
- `odom -> base_footprint` 唯一且连续。
- 注册点云 frame 与 odom 语义一致。
- 平地与缓坡上均无明显姿态跳变。
- 不因 mapping/PCD 保存逻辑影响 navigation mode。

## 9. P4：RTAB-Map + GNSS

RTAB-Map 默认使用外部 odometry，关闭自身 ICP/视觉 odometry。输入固定为项目标准接口：

```text
odom       <- /agt/mapping/odometry
scan_cloud <- /agt/mapping/registered_points
imu        <- /agt/sensors/imu/data
gps/fix    <- /agt/sensors/gnss/fix
```

GNSS 是低频全局 prior，不作为 `odom -> base` 高频来源。无有效 fix、时间戳异常或 covariance 不可信时不得作为强 prior。

第一阶段不引入双 EKF `robot_localization + navsat_transform`，避免同时引入第二套 global-frame ownership。

## 10. GlobalCorrectionManager 接入

本次修改后的核心原则：RTAB-Map 不直接成为项目 `map -> odom` 权威。

```text
NDT/ICP evidence ---------+
                          |
RTAB-Map evidence --------+--> GlobalCorrectionManager --> /agt/localization/status
          ^               |                              --> map -> odom
          |
         GNSS
```

优先将 RTAB-Map/GNSS adapter 放入 `agt_localization_fusion`，使其从当前空壳演进为真正的多源全局校正证据层。

后端选择应可显式配置，例如：

```text
global_correction_backend:=ndt
global_correction_backend:=rtabmap
```

第一阶段允许只激活一个权威证据源；多源同时加权融合留到后续版本。

## 11. RTAB-Map 地图与 Nav2

地图产品分三类：

1. 2D `nav_msgs/OccupancyGrid`：可作为 Nav2 global StaticLayer 输入。
2. 3D cloud / OctoMap：用于调试、地图质量检查、坡地结构可视化，不直接作为 Nav2 唯一规划地图。
3. Runtime commissioning map：只用于现场测试或形成原始资产；若要成为正式 READY 部署地图，必须回到 V2 完成地图处理、语义/任务资产和版本检查后再交回 Runtime。

Runtime 不负责生产最终 Site Package。

## 12. P5：坡地 local perception

现有高度阈值 obstacle filter 会在坡面上产生系统性误判，因此 local obstacle 主链升级为：

```text
registered_points
      |
      v
transform to gravity/base aligned frame
      |
      v
local ground estimation
      |
      +--> ground
      |
      +--> obstacle cloud
              |
              v
/agt/perception/obstacle_cloud
              |
        +-----+------+
        |            |
   Nav2 VoxelLayer  Collision Monitor
```

地面判断使用局部法向与重力夹角、局部高度残差和邻域连续性，禁止简单全局 `z > threshold` 作为坡地最终方案。

地面拟合失败、TF 缺失、点云过期必须诊断并 fail-closed；不能静默把全部点标记为 free。

## 13. Nav2 层

全局：

```text
StaticLayer -> optional KeepoutFilter -> InflationLayer
```

局部：

```text
VoxelLayer(/agt/perception/obstacle_cloud) -> InflationLayer
```

Collision Monitor 继续共享 `/agt/perception/obstacle_cloud`。

第一阶段继续使用当前 Runtime 的 SmacPlanner2D + MPPI DiffDrive；不为了本次测试更换主 planner/controller。

## 14. 实现顺序

```text
P0  Runtime 独立性 / 最小 agt_bringup
P1  BUNKER + MID360 + IMU + wheel odom + GNSS bringup
P2  rosbag 标定资产
P3  wheel <-> LIO 外参与时间联合标定
P4  FAST-LIVO2 连续 odometry 验证
P5  RTAB-Map external LIO 接入
P6  GNSS prior / RTAB global evidence
P7  GlobalCorrectionManager 统一 map -> odom
P8  RTAB/READY 2D OccupancyGrid -> Nav2 global costmap
P9  slope-aware perception -> VoxelLayer
P10 平地导航
P11 缓坡导航
P12 5 m / 7 m / 10 m 精度验收
```

## 15. 明确不做

本轮不做：

- 不把 wheel odom 在线紧耦合进 FAST-LIVO2 状态量。
- 不做三维 planner。
- 不升级 ROS2 Jazzy。
- 不移植 Jazzy Ground Consistency Layer。
- 不把 OctoMap 直接作为 Nav2 唯一地图。
- 不重构 `agt_mapping` 包名。
- 不迁移 V2 的 Qt、semantic、coverage 子系统到 Runtime。
- 不让 Runtime 依赖 V2 workspace。
- 不在第一版同时融合 NDT、RTAB、GNSS 多个动态权重证据源。

## 16. 测试与 Gate

静态/合同测试：

- Runtime 独立 build。
- 不存在 V2 workspace/source-tree 依赖。
- TF edge 唯一所有权。
- RTAB-Map 默认关闭。
- GNSS 可选且失效时不破坏纯 LIO 模式。
- local VoxelLayer 只消费项目 obstacle topic。
- 安全速度链没有绕过。

rosbag 测试：

- wheel/LIO 时间与相对运动残差。
- 独立 bag 外参验证误差。
- RTAB 输入频率和图优化连续性。
- GNSS fix/covariance/time gate。
- 坡面误占据率、真实障碍保留率、地面拟合失败率。
- TF continuity。

真机 Gate：

```text
G0 Runtime 独立启动
G1 BUNKER cmd_vel/odom/safety
G2 MID360/IMU/GNSS/time/TF
G3 wheel-LIO 离线外参验证
G4 FAST-LIVO2 稳定 odom
G5 RTAB-Map + GNSS evidence
G6 GlobalCorrectionManager 稳定 map -> odom
G7 global map -> Nav2
G8 slope obstacle -> local VoxelLayer
G9 平地连续导航
G10 缓坡连续导航
G11 5m/7m/10m 定点精度
```

## 17. 完成定义

本阶段完成必须同时满足：

1. `agt_navigation_runtime` 独立构建，不 source V2。
2. 有统一 BUNKER Runtime 启动入口。
3. 能录制完整 calibration/navigation rosbag。
4. 能输出 wheel/LIO 外参、时间偏移、尺度和独立验证结果。
5. FAST-LIVO2 连续 odometry 正常。
6. RTAB-Map 能使用外部 LIO、点云、IMU 和可选 GNSS。
7. RTAB evidence 经过 GlobalCorrectionManager 后唯一产生 `map -> odom`。
8. 2D map 可供 Nav2 global costmap 使用。
9. 坡面不会大面积进入 obstacle cloud，实体障碍仍进入 local costmap/Collision Monitor。
10. 现有 safety/chassis/navigation contract 不回归。
11. 平地和缓坡真机流程可重复执行。
12. 完成 5 m / 7 m / 10 m 定点导航验收记录。
