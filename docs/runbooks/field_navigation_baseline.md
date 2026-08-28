# BUNKER Field Navigation Baseline Runbook

状态：Commissioning baseline / software-gated, hardware evidence pending

本手册固定第一次实车的 Phase A → Phase B → Phase C 操作顺序。它用于 BUNKER + MID360/IMU + FAST-LIVO2 LIO-only + 现有 relocalization/GlobalCorrectionManager + Nav2 的现场建图、地图冻结和 RViz 打点导航。

边界必须保持不变：FAST-LIVO2 adapter 是唯一 `odom -> base_footprint` 权威；GlobalCorrectionManager 是唯一 `map -> odom` 权威；RViz direct goal 只用于 commissioning；第一轮 Phase C 不启用 RTAB-Map，也不把 GNSS 接入在线全局校正。

`agt_experiment_manager` is the **sole** Runtime owner of rosbag recording. `field_mapping.launch.py` 和 `field_navigation.launch.py` 只启动 Runtime 组件，不自行执行 `ros2 bag record`。**one run_id/bag per experiment**：每个现场实验只绑定一个 run_id 和一份 baseline bag，失败后新建 run_id，不覆盖旧证据。

## 0. Fresh shell 与现场变量

每个终端都从干净 shell 开始：

```bash
cd ~/agt_navigation_runtime
source /opt/ros/humble/setup.bash
source install/setup.bash

export MAP_ID=greenhouse_01
export RUN_ID=mapping_001
export RUNTIME_DIR=$PWD/runtime
```

确认当前分支和工作区：

```bash
git status --short --branch
ros2 pkg prefix agt_bringup
ros2 pkg prefix agt_experiment_manager
```

首次接 BUNKER CAN：

```bash
cd ~/agt_navigation_runtime
bash third_party/ugv_sdk/scripts/bringup_can2usb_500k.bash
ip -details link show can0
```

预期 `can0` 为 UP，bitrate 500000。CAN 未正常建立时不进入采集或导航。

## 1. 启动 ExperimentManager

单独终端启动唯一 recorder owner：

```bash
cd ~/agt_navigation_runtime
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_experiment_manager experiment_manager.launch.py \
  runtime_dir:=$RUNTIME_DIR
```

### 创建并启动一个实验

以下命令一次完成 CREATE + START；从响应中记录 `experiment_id`：

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 5,
  experiment_title: '${MAP_ID}_${RUN_ID}',
  objective: 'field navigation baseline commissioning',
  tags_json: '[\"field-baseline\", \"commissioning\"]',
  operator_note: 'one run_id/bag per experiment',
  map_id: '${MAP_ID}',
  launch_profile: 'field_mapping',
  start_experiment: true
}"
```

把响应中的 ID 保存：

```bash
export EXP_ID=<RESPONSE_EXPERIMENT_ID>
```

检查：

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession \
  "{operation: 0}"
```

## 2. Phase A — Field Mapping / Calibration Capture

Phase A 只做 LIO-only commissioning 建图和标定数据采集，不启动 localization/Nav2。

### 2.1 无 GNSS 的安全入口

```bash
ros2 launch agt_bringup field_mapping.launch.py \
  platform:=bunker \
  runtime_dir:=$RUNTIME_DIR \
  map_id:=$MAP_ID \
  run_id:=$RUN_ID \
  start_gnss:=false \
  start_chassis:=true \
  chassis_operation_mode:=monitor \
  can_interface:=can0
```

### 2.2 有 GNSS 时

原始输入必须是绝对 NavSatFix topic，且不能直接使用 canonical 输出 `/agt/sensors/gnss/fix` 作为输入：

```bash
export RAW_GNSS_TOPIC=/your/raw/navsatfix

ros2 launch agt_bringup field_mapping.launch.py \
  platform:=bunker \
  runtime_dir:=$RUNTIME_DIR \
  map_id:=$MAP_ID \
  run_id:=$RUN_ID \
  start_gnss:=true \
  gnss_input_topic:=$RAW_GNSS_TOPIC \
  start_chassis:=true \
  chassis_operation_mode:=monitor \
  can_interface:=can0
```

Phase A PCD 输出根目录固定为：

```text
runtime/commissioning/<map_id>/<run_id>/mapping/
```

该目录不得复用已有非空目录。

### 2.3 启动 `field_mapping_baseline` bag

确认 ExperimentManager 已启动且 EXP_ID 对应当前 RUN_ID 后：

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 1,
  experiment_id: '${EXP_ID}',
  profile_id: 'field_mapping_baseline'
}"
```

确认状态为 RECORDING：

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession \
  "{operation: 0}"
```

## 3. Phase A pre-motion gate

**下列 gate 全部通过后才能移动机器人。**

检查传感器/LIO/底盘证据：

```bash
ros2 topic hz /agt/sensors/lidar/custom
ros2 topic hz /agt/sensors/imu/data
ros2 topic hz /agt/mapping/odometry
ros2 topic hz /agt/mapping/registered_points
ros2 topic hz /agt/chassis/odometry
ros2 topic echo --once /agt/chassis/status
```

确认 TF 存在：

```bash
ros2 run tf2_ros tf2_echo odom base_footprint
ros2 run tf2_ros tf2_echo base_link lidar_link
ros2 run tf2_ros tf2_echo base_link imu_link
# GNSS 启用时：
ros2 run tf2_ros tf2_echo base_link gps_link
```

同时检查 `/tf` 与 `/tf_static`：

```bash
ros2 topic info /tf --verbose
ros2 topic info /tf_static --verbose
```

`odom -> base_footprint` 必须只有 FAST-LIVO adapter 一个变换权威；发现重复 TF authority 立即停止。

BUNKER 在 monitor 模式时检查 command-inert sink：

```bash
ros2 topic info /agt/chassis/monitor_only_cmd_vel_disabled --verbose
```

判断标准：`monitor_only_cmd_vel_disabled` 的 **Publisher count 0**。如果出现 publisher，不进入采集轨迹。

如果本轮要求 GNSS：

```bash
ros2 topic hz /agt/sensors/gnss/fix
ros2 topic echo --once /agt/sensors/gnss/fix
```

检查 status/covariance 不应明显异常。

最后再次确认 recorder 已启动：

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession \
  "{operation: 0}"
```

任何 required gate 不满足：不要移动。

## 4. Phase A 冻结标定轨迹

按下列顺序采集，不允许只录匀速直线：

```text
1. static 30 s
2. forward：低速 -> 中速 -> 低速直线
3. reverse 直线
4. left large circle
5. right large circle
6. S-turn
7. figure-eight
8. 左右 ±90° 转向
9. 左右 ±180° 转向
10. slope：现场允许时缓坡上坡/下坡
11. static 30 s
```

速度必须保守，优先保证时间同步、LIO 连续和数据完整。出现明显 LIO 跳变、轮速异常、传感器时间戳中断或安全问题时立即中止本 run。

## 5. Phase A 收尾与 bag 验证

先停止录包：

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 2,
  experiment_id: '${EXP_ID}'
}"
```

再停止 Phase A Runtime。不要在 Runtime 仍运行时进入 Phase B 地图资产处理。

ExperimentManager 的 bag 证据实际位于：

```text
runtime/experiments/<experiment_id>/rosbag/field_mapping_baseline_<timestamp>/
```

找到本轮 bag：

```bash
find "$RUNTIME_DIR/experiments/$EXP_ID/rosbag" -maxdepth 2 -name metadata.yaml -print
export BAG_DIR=<ABSOLUTE_FIELD_MAPPING_BAG_DIR>
```

结构验证：

```bash
python3 tools/calibration/validate_calibration_bag.py "$BAG_DIR"
```

若本轮声明 GNSS 必须存在：

```bash
python3 tools/calibration/validate_calibration_bag.py "$BAG_DIR" --require-gnss
```

不通过的 bag 不进入正式标定/验收，只保留为 failure evidence。

## 6. Phase B — Map Freeze / Navigation Asset Preparation

Phase B 必须在 Phase A Runtime 完全停止后执行。

推荐 commissioning 资产布局：

```text
runtime/commissioning/<map_id>/<run_id>/
├── mapping/
│   └── global_map.pcd
├── metadata/
│   ├── global_map_processing_record.yaml
│   ├── bag_validation.json
│   └── map_manifest.json
└── navigation/
    ├── map.yaml
    └── map.pgm
```

注意：ExperimentManager 的 rosbag 保持在 `runtime/experiments/<experiment_id>/rosbag/...`，不要创建第二套 recorder。通过 `EXP_ID + MAP_ID + RUN_ID` 保持追溯关系即可。

### 6.1 固定 PCD

确认 FAST-LIVO2 实际输出 PCD，人工检查后将本轮被采用的文件固定为：

```bash
export ASSET_ROOT="$RUNTIME_DIR/commissioning/$MAP_ID/$RUN_ID"
export PCD="$ASSET_ROOT/mapping/global_map.pcd"
ls -lh "$PCD"
```

如果底层保存文件名不是 `global_map.pcd`，在 Phase B 显式复制/重命名一次，然后不再改动。不要覆盖旧 RUN_ID。

### 6.2 生成 2D Nav2 静态地图

使用已有离线地图处理流程，从本轮 PCD 生成：

```text
$ASSET_ROOT/navigation/map.pgm
$ASSET_ROOT/navigation/map.yaml
```

本 baseline 仓库当前没有新增 PCD→PGM 转换器，因此这里不得假装存在某个生成命令。要求只有两个：`map.yaml` 能被 Nav2 map_server 读取；其中 `image:` 必须能解析到实际 map image。

同时保存与本轮 PCD 对应的 `global_map_processing_record`，Phase C 必须传入该文件。

### 6.3 使用 `freeze_map_assets.py`

```bash
mkdir -p "$ASSET_ROOT/metadata"

python3 tools/commissioning/freeze_map_assets.py \
  --pcd "$PCD" \
  --navigation-yaml "$ASSET_ROOT/navigation/map.yaml" \
  --map-id "$MAP_ID" \
  --run-id "$RUN_ID" \
  --manifest "$ASSET_ROOT/metadata/map_manifest.json"
```

该命令计算 PCD、navigation YAML、navigation image 的 SHA256，并写入 `map_manifest.json`。已有 manifest 会拒绝覆盖。初始 `calibration_status` 为 `UNVERIFIED`。

读取 PCD hash，后续 Phase C 的 `map_hash` 必须用这个值：

```bash
python3 - <<'PY'
import json, os
from pathlib import Path
p = Path(os.environ['ASSET_ROOT']) / 'metadata' / 'map_manifest.json'
m = json.loads(p.read_text())
print(m['pcd_sha256'])
PY
```

保存：

```bash
export MAP_HASH=sha256:<64_lowercase_hex_from_manifest>
export PROCESSING_RECORD="$ASSET_ROOT/metadata/global_map_processing_record.yaml"
export NAV_MAP="$ASSET_ROOT/navigation/map.yaml"
```

## 7. Phase C — Field Navigation / RViz Goal，先禁用底盘运动

第一次启动必须显式：`start_chassis:=false`。

```bash
ros2 launch agt_bringup field_navigation.launch.py \
  platform:=bunker \
  global_map_pcd:=$PCD \
  global_map_processing_record:=$PROCESSING_RECORD \
  navigation_map:=$NAV_MAP \
  map_id:=$MAP_ID \
  map_hash:=$MAP_HASH \
  start_gnss:=false \
  start_chassis:=false \
  start_rviz:=true
```

如果有 RTK 且希望同步记录外部评价证据，可以在 Phase C 启动 canonical GNSS adapter：

```bash
start_gnss:=true gnss_input_topic:=$RAW_GNSS_TOPIC
```

第一轮 Phase C 中 GNSS 是 **evaluation evidence only**；它不拥有 `map -> odom`，不直接修改 GlobalCorrectionManager/localization ownership。

## 8. Phase C navigation gate

在允许任何 RViz goal 前，必须确认：

```bash
ros2 topic hz /agt/mapping/odometry
ros2 topic hz /agt/mapping/registered_points
ros2 topic echo --once /agt/localization/status
ros2 topic hz /agt/perception/obstacle_cloud
ros2 run tf2_ros tf2_echo map odom
```

`/agt/localization/status` 必须同时满足：

```text
TRACKING
pose_valid=true
localization_accepted=true
status_stale=false
```

并确认：

- PCD、processing record、navigation YAML 存在且与当前 MAP_ID/MAP_HASH 匹配。
- FAST-LIVO2 odometry 连续。
- GlobalCorrectionManager 是唯一 `map -> odom` 权威。
- Nav2 lifecycle 已由 localization gate 启动。
- `/agt/perception/obstacle_cloud` 持续有效。
- Collision Monitor 正常。
- `agt_safety` 正常，无 emergency stop。

可辅助查看：

```bash
ros2 node list | grep -E 'collision|safety|controller|planner|map_server'
ros2 topic echo --once /agt/safety/status
ros2 lifecycle get /controller_server
ros2 lifecycle get /planner_server
```

未进入 TRACKING 或任一安全 gate 不满足，不得启用底盘运动。

## 9. 通过静态 gate 后，重启 Phase C 并启用 BUNKER control

先正常停止 `start_chassis:=false` 的 Phase C，再重启：

```bash
ros2 launch agt_bringup field_navigation.launch.py \
  platform:=bunker \
  global_map_pcd:=$PCD \
  global_map_processing_record:=$PROCESSING_RECORD \
  navigation_map:=$NAV_MAP \
  map_id:=$MAP_ID \
  map_hash:=$MAP_HASH \
  start_gnss:=false \
  start_chassis:=true \
  chassis_operation_mode:=control \
  can_interface:=can0 \
  start_rviz:=true
```

重新确认第 8 节 gate；重启后不能沿用重启前的 TRACKING 结论。

## 10. RViz commissioning 操作

`field_navigation.rviz` 使用 `map` Fixed Frame。

1. 必要时使用 **SetInitialPose**（2D Pose Estimate）发布 `/initialpose`，仅做 commissioning 粗初始化。
2. 等待 localization 回到 TRACKING，并再次确认 `pose_valid=true / localization_accepted=true / status_stale=false`。
3. 使用 **SetGoal**（2D Goal Pose）发布 `/goal_pose`。
4. RViz goal bridge 只将 commissioning goal 送入 Nav2；它不能绕过 localization lifecycle gate、Collision Monitor、`agt_safety` 或 chassis guard。

## 11. Phase C `field_navigation_baseline` 录包

每个 N0–N6 都使用新的 RUN_ID/实验和独立 bag。不要把多个距离阶段塞进同一验收 bag。

创建新的 experiment，得到新的 `EXP_ID` 后启动：

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 1,
  experiment_id: '${EXP_ID}',
  profile_id: 'field_navigation_baseline'
}"
```

每个实验完成后：

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 2,
  experiment_id: '${EXP_ID}'
}"
```

成功实验再 finalize；失败实验 interrupt/invalid，并保留完整证据。

## 12. N0–N6 第一轮导航顺序

严格从低风险到高风险，不跳级：

```text
N0  原地定位稳定观察 60 s
N1  2 m 直线目标
N2  5 m 直线目标
N3  左 90° 与右 90° 目标（分开执行/记录）
N4  5 m 带转弯路径
N5  7 m 路径
N6  10 m 路径
```

每个 run 记录至少：cross-track error、yaw error、stop overshoot、settling time、`wz` zero-crossing、command saturation、controller timing、localization transitions、recovery count。

第一轮保持现有 `nav2_bunker.yaml` baseline，不进行大范围 MPPI 调参。先处理定位/时间/外参，再处理底盘真实能力，然后才考虑 `wz_std`、PathAlign 等控制器参数。

## 13. 强制停止条件

出现任一条件立即停止当前实验，不继续加距离/速度：

```text
localization invalid
collision stop
wrong point cloud
control oscillation
tf authority conflict
```

具体包括：

- localization 从 TRACKING 退化或 `pose_valid/localization_accepted/status_stale` gate 失败；
- Collision Monitor 或 `agt_safety` 触发 stop；
- 障碍点云明显错位、冻结地图/实时点云对不上；
- 车体持续摆动、角速度反复过零、明显 control oscillation；
- 出现第二个 `map -> odom` 或 `odom -> base_footprint` 发布权威，即 TF authority conflict；
- CAN、底盘状态、LIO、IMU/LiDAR 时间戳异常。

失败后停止 bag，记录 failure evidence，换新的 RUN_ID 重新开始；不得覆盖旧资产或把失败 run 当作验收通过。

## 14. 软件通过与实车通过的边界

本 runbook、launch contract、bag profile、map manifest 测试通过，只代表软件 baseline 已冻结。第一次真实车辆运行仍需独立验证 MID360/IMU/LIO/GNSS/TF/chassis/safety 和 N0–N6 证据；在这些证据出现之前，不标记为 hardware-green。
