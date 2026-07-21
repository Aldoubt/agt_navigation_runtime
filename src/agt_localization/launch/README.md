# launch

`relocalization.launch.py` 启动唯一的 `agt_localization` 节点，并同时提供两条输入路径：

- 默认启用的 `/initialpose` 手动对比基线，由 `manual_initialpose_enabled` 控制；
- `/agt/localization/relocalize` 项目 Action，用于自动候选搜索和显式 Action 初值。

两条路径共用 `map -> odom` 发布器和质量门禁，不会创建第二个 TF owner。生产导航默认保持
`manual_initialpose_enabled:=true`，便于在同一地图/PCD/bag 上和自动 Action 做对照。

节点接受成功后会按参数周期执行低频只读 tracking 验证。验证线程不会发布新的 `map -> odom`；
`LOST` 状态停止定时验证，等待显式 Action 或 `/initialpose` 恢复。
