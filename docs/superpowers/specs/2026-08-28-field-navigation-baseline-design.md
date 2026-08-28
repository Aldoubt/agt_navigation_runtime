# BUNKER Field Navigation Commissioning Baseline Design

日期：2026-08-28
分支：`feat/bunker-rtabmap-slope-nav`
状态：**FROZEN FOR IMPLEMENTATION**

## 1. 目标

冻结一条用于 BUNKER + MID360 + 单 RTK 天线真机 commissioning、数据采集、FAST-LIVO2 LIO-only 建图、先验地图重定位、Nav2 RViz 打点导航和后续 RTK↔LIO 联合标定的基线流程。

本 baseline 的核心原则是：**建图与导航分两次运行，不在同一次现场运行中让地图持续变化并同时做重定位/导航。**

## 2. Runtime 边界

保持现有职责：

- FAST-LIVO2：高频 LIO，唯一 `odom -> base_footprint` 权威。
- Relocalization：只产生全局校正 evidence，不直接发布 `map -> odom`。
- GlobalCorrectionManager：唯一 `map -> odom` 权威。
- Nav2：消费冻结后的 2D navigation map 和有效 localization status。
- V2：正式 Site Asset 工厂；Runtime 本 baseline 只允许产生 commissioning 资产，不替代正式 READY Site Package 流程。
- RViz goal 只属于 commissioning 模式，不成为正式 Mission/Task 权威入口。

不得引入第二个 `map -> odom` 或 `odom -> base_footprint` 发布者。

## 3. 冻结的现场流程

### Phase A：Field Mapping / Calibration Capture

用途：第一次到场或地图需要重建时，使用 MID360 + IMU 的 FAST-LIVO2 LIO-only 生成 commissioning PCD，同时录制完整 calibration bag。

冻结入口：

```bash
ros2 launch agt_bringup field_mapping.launch.py \
  platform:=bunker \
  start_gnss:=true \
  gnss_input_topic:=<ABSOLUTE_RAW_NAVSATFIX_TOPIC> \
  start_chassis:=true \
  chassis_operation_mode:=monitor \
  map_id:=<MAP_ID> \
  run_id:=<RUN_ID>
```

如果 GNSS 暂时不可用：

```bash
ros2 launch agt_bringup field_mapping.launch.py \
  platform:=bunker \
  start_gnss:=false \
  start_chassis:=true \
  chassis_operation_mode:=monitor \
  map_id:=<MAP_ID> \
  run_id:=<RUN_ID>
```

`field_mapping.launch.py` 必须：

- 启动 description、MID360、IMU、FAST-LIVO2 LIO-only、sensor monitor。
- 可选启动 GNSS canonical adapter。
- 可选启动 BUNKER monitor-only driver，driver 不得订阅正常控制命令链。
- 强制 `start_localization=false`、`start_navigation=false`。
- FAST-LIVO2 `save_pcd=true`。
- PCD 输出目录必须是本次运行独占的新目录，禁止覆盖已有资产。
- 同时启动 calibration bag recording，记录本规范第 5 节的完整 topic 集。

### Phase B：Map Freeze / Navigation Asset Preparation

Phase A 结束后必须先停止 Runtime，再处理资产。

commissioning 资产至少包含：

```text
runtime/commissioning/<map_id>/<run_id>/
├── mapping/
│   └── global_map.pcd
├── bag/
│   └── <rosbag2 files>
├── metadata/
│   ├── run.yaml
│   ├── bag_validation.json
│   └── map_manifest.json
└── navigation/
    ├── map.yaml
    └── map.pgm
```

`map_manifest.json` 必须至少冻结：

- `map_id`
- `run_id`
- PCD SHA256
- navigation YAML SHA256
- navigation image SHA256
- mapping source = `FAST_LIVO2_LIO_ONLY`
- generation timestamp
- calibration status（允许 `UNVERIFIED`）

2D navigation map 可以由已有离线地图工具产生；本 baseline 不允许在导航进程中在线重建静态地图。

### Phase C：Field Navigation / RViz Goal

冻结入口：

```bash
ros2 launch agt_bringup field_navigation.launch.py \
  platform:=bunker \
  global_map_pcd:=<ABSOLUTE_PCD> \
  global_map_processing_record:=<ABSOLUTE_PROCESSING_RECORD> \
  navigation_map:=<ABSOLUTE_MAP_YAML> \
  map_id:=<MAP_ID> \
  map_hash:=<PCD_SHA256> \
  start_chassis:=true \
  chassis_operation_mode:=control \
  start_rviz:=true
```

`field_navigation.launch.py` 必须：

- 启动 MID360 + IMU + FAST-LIVO2 LIO-only odometry。
- `save_pcd=false`。
- 启动 existing relocalization + GlobalCorrectionManager。
- 启动 Nav2，但保持现有 localization lifecycle gate。
- 启动 BUNKER control + safety chain。
- 显式启用 commissioning-only RViz goal bridge。
- 可选启动 `field_navigation.rviz`。
- 不启动 RTAB-Map，不在 baseline 第一轮同时引入 GNSS global correction。

## 4. RViz 行为冻结

新增 `src/agt_navigation/config/field_navigation.rviz`。

Fixed Frame：`map`。

必须显示：

- `/agt/map/global_occupancy`
- `/agt/mapping/registered_points`
- `/plan`
- `/global_costmap/costmap`
- `/local_costmap/costmap`
- TF
- RobotModel

必须包含：

- `2D Pose Estimate`：发布 `/initialpose`，只用于 commissioning 粗初始化。
- `2D Goal Pose`：发布 `/goal_pose`。

现有 `goal_pose_bridge.py` 保留，但 `navigation.launch.py` 新增：

```text
enable_rviz_goal_bridge:=false
```

正式 Runtime 默认关闭；只有 `field_navigation.launch.py` 显式设置为 `true`。

RViz goal bridge 不绕过 localization gate、Nav2 lifecycle、collision monitor、agt_safety 或 chassis guard。

## 5. 真机 baseline 必采 topics

Phase A calibration/mapping bag 必须包含：

```text
/agt/sensors/lidar/custom
/agt/sensors/imu/data
/agt/chassis/odometry
/agt/chassis/status
/agt/mapping/odometry
/agt/mapping/registered_points
/agt/navigation/cmd_vel
/tf
/tf_static
```

若 GNSS 启用，必须额外包含：

```text
/agt/sensors/gnss/fix
```

Phase C navigation validation bag 至少包含：

```text
/agt/mapping/odometry
/agt/mapping/registered_points
/agt/localization/status
/agt/navigation/cmd_vel_raw
/agt/navigation/cmd_vel
/plan
/tf
/tf_static
/agt/chassis/odometry
/agt/chassis/status
```

若 GNSS 可用，Phase C 也记录 `/agt/sensors/gnss/fix`，但 baseline 第一轮只作为外部评价/后处理数据，不直接修改 localization ownership。

## 6. 标定轨迹冻结

Phase A 数据采集顺序：

```text
1. 静止 30 s
2. 前进直线：低速 -> 中速 -> 低速
3. 后退直线
4. 左大圆
5. 右大圆
6. S 弯
7. 8 字
8. 左右 ±90° 转向
9. 左右 ±180° 转向
10. 缓坡上坡/下坡（现场允许时）
11. 静止 30 s
```

禁止只用匀速直线数据做 RTK↔LIO 联合标定。

## 7. 第一版 RTK↔LIO 优化变量

针对单 RTK 天线 + MID360，第一版离线标定只释放：

```text
dt
lever_arm_x
lever_arm_y
world_yaw
world_tx
world_ty
```

其中：

- `dt`：GNSS 与 LIO 时间偏移。
- `lever_arm_x/y`：LIO/MID360 frame 到 RTK antenna phase center 的水平杆臂。
- `world_yaw/tx/ty`：LIO world 到 ENU 的水平对齐。

`lever_arm_z / roll / pitch` 不在第一版全自由优化；使用机械测量、IMU 重力和坡地数据作为后续约束来源。

优化器输出固定为：

```text
calibration.yaml
residuals.csv
observability.json
validation_report.json
```

训练 bag 与 validation bag 必须分离；不能只报告训练数据 residual。

## 8. Field Mapping Gate

开始移动前必须检查：

- MID360 topic 有数据且时间戳连续。
- IMU topic 有数据且时间戳连续。
- `/agt/mapping/odometry` 连续。
- `/agt/mapping/registered_points` 连续。
- `odom -> base_footprint` 只有一个发布权威。
- `/tf_static` 中 `base_link -> lidar_link / imu_link / gps_link` 符合当前配置。
- 若要求 GNSS，`/agt/sensors/gnss/fix` 存在且状态/covariance 非明显异常。
- BUNKER monitor mode 的 normal command sink 没有 Publisher。
- rosbag recording 已经开始。

任何 required gate 不满足都不得进入正式采集轨迹。

## 9. Field Navigation Gate

允许 RViz 下发目标前必须满足：

- PCD、processing record、navigation YAML 均存在。
- `map_id` 和 PCD hash 与本次资产一致。
- FAST-LIVO2 odometry 正常。
- localization status 为 `TRACKING`。
- `pose_valid=true`。
- `localization_accepted=true`。
- `status_stale=false`。
- GlobalCorrectionManager 正常发布唯一 `map -> odom`。
- Nav2 lifecycle 已由 localization gate 启动。
- `/agt/perception/obstacle_cloud` 正常。
- Collision Monitor 与 agt_safety 正常。

如果 localization 从 TRACKING 退化，现有 gate 继续负责 pause Nav2；不允许 RViz goal 绕过该行为。

## 10. 导航采集实验顺序

第一轮仅做低风险 commissioning：

```text
N0  原地定位稳定观察 60 s
N1  RViz 目标 2 m 直线
N2  RViz 目标 5 m 直线
N3  左右各一个 90° 转弯目标
N4  5 m 带转弯路径
N5  7 m 路径
N6  10 m 路径
```

每个实验都保存独立 run_id 和 bag；出现 localization invalid、collision stop、明显点云错误或控制震荡时立即停止，不继续提高距离/速度。

## 11. Baseline 参数策略

第一轮不大规模调 MPPI。保持当前 `nav2_bunker.yaml` 作为 baseline，只允许通过独立实验分支逐项改变参数。

第一轮重点记录：

- cross-track error
- yaw error
- stop overshoot
- settling time
- `wz` zero-crossing count
- command saturation ratio
- controller cycle timing
- localization state transitions
- recovery count

参数调节顺序冻结为：

```text
1. 定位/时间/外参
2. 底盘实际速度与角速度能力
3. MPPI wz_std
4. MPPI PathAlignCritic weight
5. 其余 critics / horizon / costmap
```

禁止用 controller 参数去补偿明显的 localization 或时间同步误差。

## 12. 新增/修改文件范围

本 baseline 实现阶段预计：

```text
src/agt_bringup/launch/field_mapping.launch.py
src/agt_bringup/launch/field_navigation.launch.py
src/agt_bringup/test/test_field_commissioning_contract.py
src/agt_navigation/config/field_navigation.rviz
src/agt_navigation/launch/navigation.launch.py
src/agt_navigation/test/test_rviz_goal_bridge_contract.py
src/agt_experiment_manager/config/bag_profiles.yaml
docs/runbooks/field_navigation_baseline.md
tools/calibration/lio_gnss_*.py
tools/calibration/test_*.py
```

如实现时发现需要扩大 Runtime/V2 边界、改 TF ownership 或改变正式 Mission 权威，必须停止并重新评审设计。

## 13. 完成定义

A-E commissioning baseline 完成必须满足：

1. `field_mapping.launch.py` 能明确启动 LIO-only mapping + PCD save + calibration bag，且不启动 localization/Nav2。
2. `field_navigation.launch.py` 能明确启动 LIO-only odometry + relocalization + GlobalCorrectionManager + Nav2 + safety + optional RViz。
3. 正式 `navigation.launch.py` 默认 `enable_rviz_goal_bridge=false`。
4. commissioning navigation 显式开启 `/goal_pose -> NavigateToPose` bridge。
5. RViz 配置包含地图、点云、TF、RobotModel、plan、global/local costmap 和 2D Pose/Goal tools。
6. mapping/navigation bag profiles 固定并可验证必需 topics。
7. Runbook 给出 Phase A/B/C 的可复制命令、检查项、停止条件和输出路径。
8. 不改变现有 TF ownership、安全速度链和 Runtime/V2 边界。

RTK↔LIO calibrator 是该 baseline 的后续独立实现计划，使用 Phase A 产生的 bag，不阻塞 A-E 首轮现场采集能力。