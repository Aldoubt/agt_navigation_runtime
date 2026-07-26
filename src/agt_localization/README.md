# agt_localization

使用全局 PCD 与当前 `lidar_link` 点云执行 ICP/NDT 重定位。候选、配准和质量验证都在本节点
编排，只有通过质量门禁的结果才更新唯一的 `map -> odom`。

## 接口

- 输入点云：`/agt/mapping/registered_points_lidar` (`sensor_msgs/PointCloud2`)
- 手动对比入口：`/initialpose` (`geometry_msgs/PoseWithCovarianceStamped`，语义为 `map -> base_link`，默认启用)
- 结构化状态：`/agt/localization/status` (`agt_interfaces/LocalizationStatus`)
- 兼容文本状态：`/agt/localization/status_text` (`std_msgs/String`)
- 重定位 Action：`/agt/localization/relocalize` (`agt_interfaces/action/Relocalize`)
- 外部粗位姿输入：`/agt/localization/coarse_pose`
- 当前候选调试位姿：`/agt/localization/candidate_pose`
- 最终全局位姿：`/agt/localization/global_pose`
- 对齐点云：`/agt/localization/aligned_points`
- TF：成功后持续发布 `map -> odom`

`LocalizationStatus.map_hash` 是当前定位 PCD 内容的 `sha256:<64位小写十六进制>` 身份。节点在
加载候选和 last pose 前重新计算该摘要；processing record 如包含 `pcd_sha256`，必须与实际 PCD
一致。历史记录缺少摘要时仍可读取，但启动日志会明确提示记录级 hash 未验证。

节点会从 TF 查询 `base_link -> lidar_link` 来修正配准初值，因此应先启动
`agt_description` 并填写车辆到雷达外参。MID360 雷达到内置 IMU 的内部外参仍由
FAST-LIVO2 参数管理，不应重复填入这里。

## 启动

先启动机器人描述与连续里程计，再提供与二维导航地图同源的全局 PCD：

```bash
source /opt/ros/humble/setup.bash
source /home/yangxuan/ros2_ws/install/setup.bash
source install/setup.bash
ros2 launch agt_localization relocalization.launch.py \
  global_map_pcd:=/absolute/path/to/global_map.pcd \
  global_map_processing_record:=/absolute/path/to/localization_map.processing.yaml \
  backend:=ndt use_sim_time:=true
```

在 RViz2/Qt 中使用 `2D Pose Estimate` 发布手动对比初值，或调用
`/agt/localization/relocalize` Action 执行自动候选搜索。两条路径复用同一个配准和质量门禁，
但状态来源分别记录为 `manual_initialpose` 与 Action 的候选来源，便于比较成功率、fitness、
耗时和拒绝原因。调试时可将 `backend:=icp`；参数阈值见
`config/relocalization.yaml`。候选示例见 `config/candidates.example.yaml`。
当前只有 PGM/YAML 栅格图，不能替代重定位所需的三维 PCD。

`manual_initialpose_enabled` 默认是 `true`，用于保留原始人工定位基线。只有在需要验证纯
Action/自动模式时才显式设为 `false`；关闭后 `/initialpose` 会发布明确的拒绝状态，不会静默
改走自动候选或直接更新 TF。

导航启动自动 Action、候选 YAML、手动 `/initialpose` 和两种方式的技术差异见
[`docs/workflows/relocalization_usage.md`](../../docs/workflows/relocalization_usage.md)。启动自动
模式必须显式设置 `auto_relocalize_on_start:=true`，并准备 last pose、configured candidates 或
external coarse pose 中至少一种有界来源。

## Tracking supervisor

节点只缓存 `/agt/mapping/registered_points_lidar` 的最新一帧；一次 `runCandidates()` 固定使用
这一帧及其 `cloud_stamp`，所有候选不会切换到其他点云。动态 `odom -> tracking_frame` 查询在
该点云时间执行，静态 `base_link -> lidar_link` 外参可以使用静态 TF。

接受一次候选后进入 `TRACKING`，默认每 5 秒使用当前 odom 传播预测做一次只读验证：
`map -> tracking_frame = map -> odom * odom -> tracking_frame(cloud_stamp)`。验证成功只更新
结构化状态和质量字段，不重新计算、发布或持久化新的 `map -> odom`；验证失败依次进入
`DEGRADED`、`RECOVERING`，连续达到阈值后进入 `LOST`。`LOST` 不会自动启动无界搜索，必须由
人工 `/initialpose` 或 Action 请求显式恢复。

初始手动 `/initialpose`、Action 和 configured candidate 仍使用各自 candidate 作为粗初值。
点云时间戳由 `max_cloud_age_s`、`max_cloud_future_tolerance_s` 和
`require_nonzero_cloud_stamp` 检查；过期、未来超容差和无效时间戳分别报告明确原因及
`ERROR_STALE_SCAN`/`ERROR_INVALID_SCAN_TIMESTAMP`。状态 header 可以是发布时间，但
`global_pose`、`aligned_points` 和持久化定位记录保留点云时间戳。

离线 rosbag 回放必须给节点设置 `use_sim_time=true`，并确认 `/clock` 正常发布；新鲜度检查只
使用 ROS clock，不使用系统墙钟。阈值和验证周期见 `config/relocalization.yaml`。

`tracking_confirmations_required` 默认保持 `1` 以兼容当前 Bunker 单次重定位基线；提高该值后，
Action 结果会在连续确认完成前保持非导航有效状态，适合后续接入重复扫描验证。

## NDT 线程参数

`ndt_num_threads` 必须大于等于 `1`，Bunker 实车验证基线固定为 `4`。ROS 参数入口会拒绝
`0` 和负数；重定位核心与 NDT-OMP 还会将绕过 ROS 参数入口的非正值钳制为 `1`，避免
按零线程创建工作数组后发生越界。2026-07-19 实车使用 `4` 线程重定位成功，观察到的
fitness 约为 `0.01`–`0.02`；该结果仍需在完整导航启动前使用最终导航 PCD 复验。

## 待验证

- 用同一建图数据导出的 PCD 检查 NDT/ICP 收敛率、fitness 和恢复时间。
- 标定 `base_link -> lidar_link` 后验证非零外参下的 `map -> odom`。
- 检查系统中没有第二个 `map -> odom` 发布者，并对错误初值执行拒绝测试。
- 用 `LocalizationStatus` 和 Action result 验证候选歧义、取消、超时和地图身份拒绝。
- 对同一 bag 先执行手动 `/initialpose` 基线，再执行自动 Action；按 `candidate_source` 分组
  比较 `fitness_score`、`runtime_ms`、`tested_candidates`、最终状态和失败原因。
