# agt_localization

使用全局 PCD 与当前 `lidar_link` 点云执行 ICP/NDT 重定位。候选、配准和质量验证都在本节点
编排，只有通过质量门禁的结果才更新唯一的 `map -> odom`。

## 接口

- 输入点云：`/agt/mapping/registered_points` (`sensor_msgs/PointCloud2`)
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
source "$AGT_WS/install/setup.bash"
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

节点只缓存 `/agt/mapping/registered_points` 的最新一帧；一次 `runCandidates()` 固定使用
这一帧及其 `cloud_stamp`，所有候选不会切换到其他点云。动态 `odom -> tracking_frame` 查询在
该点云时间执行，静态 `base_link -> lidar_link` 外参可以使用静态 TF。

接受一次候选后进入 `TRACKING`，默认每 5 秒使用当前 odom 传播预测做一次只读验证：
`map -> tracking_frame = map -> odom * odom -> tracking_frame(cloud_stamp)`。验证成功只更新
结构化状态和质量字段，不重新计算、发布或持久化新的 `map -> odom`；验证失败依次进入
`DEGRADED`、`RECOVERING`，连续达到阈值后进入 `LOST`。`LOST` 不会自动启动无界搜索，必须由
人工 `/initialpose` 或 Action 请求显式恢复。

tracking validation 只消费时间戳严格大于上一帧的注册点云，但 duplicate 只有同时通过点云
新鲜度门禁时才会跳过。bag 和 `/clock` 一起暂停时，相同的 fresh `cloud_stamp` 不执行 NDT、
不增加成功或失败计数、不发布新状态。实车 ROS 时间继续前进而雷达或 FAST-LIVO2 停止发布时，
缓存帧超过 `max_cloud_age_s` 后不再按 duplicate 跳过，而是以 `ERROR_STALE_SCAN` 计为一次
tracking failure；持续停发会依次进入 `DEGRADED`、`RECOVERING`、`LOST`。未来超容差或无效
duplicate 同样按时间门禁拒绝。

检测到 ROS 时间回退且当前帧新鲜时，该帧只用作新的点云序列基线并跳过；再次收到同一纳秒
时间戳时按 fresh duplicate 跳过，只有后续严格增加的时间戳才恢复验证。时间回退和 fresh
duplicate 的 skip 都不更新 supervisor，也不发布 `LocalizationStatus`。

`runCandidates()` 在 tracking 模式不发布搜索、验证、TF/点云失败、候选结果或终止等中间权威
状态，只返回 accepted/rejected/skipped 三态及后端结果。每个非 skip 结果只由外层 tracking
worker 向 supervisor 提交一次并发布一次最终状态，因此成功验证不会短暂发布 `VERIFYING` 或
`pose_valid=false` 而误触发 Nav2、teach-repeat 和 safety gate。`has_converged` 保留 NDT/ICP
后端真实收敛结果；fitness/innovation 等质量门禁拒绝时，它可以为 `true`，但
`localization_accepted` 和 `pose_valid` 必须为 `false`。

初始手动 `/initialpose`、Action 和 configured candidate 仍使用各自 candidate 作为粗初值。
点云时间戳由 `max_cloud_age_s`、`max_cloud_future_tolerance_s` 和
`require_nonzero_cloud_stamp` 检查；过期、未来超容差和无效时间戳分别报告明确原因及
`ERROR_STALE_SCAN`/`ERROR_INVALID_SCAN_TIMESTAMP`。状态 header 可以是发布时间，但
`global_pose`、`aligned_points` 和持久化定位记录保留点云时间戳。

离线 rosbag 回放必须给节点设置 `use_sim_time=true`，并确认 `/clock` 正常发布；新鲜度检查只
使用 ROS clock，不使用系统墙钟。阈值和验证周期见 `config/relocalization.yaml`。

`tracking_confirmations_required` 当前固定只支持 `1`。设置为 `0`、负数或 `2` 及以上时节点会在
启动阶段明确失败，因为临时 `map -> odom`、独立新帧确认和最终 TF 提交组成的多帧 bootstrap
流程尚未实现。不要通过修改 YAML 尝试启用多帧启动确认。

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
