# agt_interfaces

职责：定义统一的消息、服务、动作和状态契约；本包只定义接口，不实现业务逻辑或 Action Server。

当前主要接口：

- `msg/ComponentHealth.msg`、`msg/SystemHealth.msg`：配置驱动的机器可解析健康快照。
- `msg/TaskReadiness.msg`：Web、Qt bridge 和 Action 服务端共享的 fail-closed 任务门禁。
- `msg/SemanticWaypoint.msg`、`msg/SemanticWaypointArray.msg`：V2.5 schema-1.1 命名语义路点库；
  数组绑定 `map_id`/基础地图 SHA256，但不携带任务执行顺序。
- `srv/GetSystemHealth.srv`、`srv/EvaluateTaskReadiness.srv`：一次性健康/门禁查询。
- `srv/SetLocalizationMode.srv`：有界 `MANUAL_ONLY`、`AUTO_ON_START`、`AUTO_RECOVERY` 策略选择。
- `msg/LocalizationStatus.msg`：机器可解析的全局定位状态、质量和稳定错误码。
- `action/ChangeSystemMode.action`：白名单系统模式切换，不接受任意命令。
- `action/ManageMappingSession.action`：统一建图会话的启动、采集完成、候选提交和状态查询；
  前端不得自行编排栅格保存、建图停止、PCD 等待或地图版本登记。
- `action/OptimizeMap.action`：离线优化接口预留，当前实现 fail-closed 未实现。
- `action/Relocalize.action`：项目统一自动重定位 Goal、Feedback 和 Result 边界。
- `action/ExecuteCoverageTask.action`：覆盖任务 Goal、Result 和 Feedback 数据结构。
- `action/ExecuteWaypointTask.action`：Qt/其他前端到可靠 Nav2 多点执行器的任务边界。

构建后可通过生成的 Python/C++ 类型使用。包内测试验证关键接口生成产物与 Python 序列化往返。

`SemanticWaypointArray` 是地图语义产品，不等于 `ExecuteWaypointTask`。命名锚点的持久化与发布
属于 `agt_ui_bridge/agt_semantic_map_server`；有序 waypoint task 的版本、hash、loop、cancel 和
session 语义仍由 `agt_navigation` 的 Task Registry / project Action 负责。

覆盖任务服务端属于 `agt_coverage_planning`，多点导航任务服务端属于 `agt_navigation`。
自动重定位服务端属于 `agt_localization`；本包不实现候选搜索、配准、TF 或安全门禁。
系统健康节点属于 `agt_system_manager`，任务服务端仍必须在 Action 执行层再次检查
`TaskReadiness`。

建图 Action 的字段、状态、时序和错误码见
[`docs/interfaces/mapping_session_action.md`](../../docs/interfaces/mapping_session_action.md)。
语义路点合同见
[`docs/interfaces/semantic_waypoints.md`](../../docs/interfaces/semantic_waypoints.md)。
