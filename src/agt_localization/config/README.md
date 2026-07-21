# config

`relocalization.yaml` 保存 Bunker 基线默认参数，路径类参数默认为空，必须由 launch 或部署配置
显式提供。`candidates.example.yaml` 只展示 schema，不指向真实用户、工作空间、设备或地图路径。

候选配置和 `last_valid_pose.yaml` 都必须带 `map_id` 与 `map_hash`。运行时会在展开前限制候选
总量，在加载 last pose 时拒绝地图身份不匹配的记录。

`map_hash` 的运行时规范是对应定位 PCD 内容的 `sha256:<64位小写十六进制>`。启动时会重新计算
PCD 摘要；如果 processing record 有 `pcd_sha256`（兼容读取 `map_hash`），必须与实际文件一致，
显式传入的 `map_hash` 也必须与实际文件一致。没有摘要字段的旧 processing record 暂时保持可读，
但启动诊断会明确告警“已计算、未记录”，新地图发布流程应写入 `pcd_sha256`。

`manual_initialpose_enabled: true` 是保留的人工对比基线开关。它控制原始 `/initialpose` 入口，
不控制 Action；手动结果来源固定为 `manual_initialpose`，Action 中显式初值来源固定为
`action_initial_pose`。

`tracking_validation_enabled` 默认启用低频只读验证。`tracking_validation_period_s` 和
`tracking_validation_timeout_s` 必须为正数；`tracking_confirmations_required`、
`tracking_failures_to_recover`、`tracking_failures_to_lost` 必须为正数且按恢复、丢失顺序递增。
