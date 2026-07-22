# agt_interfaces

职责：定义统一的消息、服务、动作和状态契约。

TASK-13 已启用 ROSIDL 代码生成，当前接口：

- `msg/ComponentHealth.msg`、`msg/SystemHealth.msg`：配置驱动的机器可解析健康快照。
- `msg/TaskReadiness.msg`：Web、Qt bridge 和 Action 服务端共享的 fail-closed 任务门禁。
- `srv/GetSystemHealth.srv`、`srv/EvaluateTaskReadiness.srv`：一次性健康/门禁查询。
- `srv/SetLocalizationMode.srv`：有界 `MANUAL_ONLY`、`AUTO_ON_START`、`AUTO_RECOVERY` 策略选择。
- `msg/LocalizationStatus.msg`：机器可解析的全局定位状态、质量和稳定错误码。
- `action/ChangeSystemMode.action`：白名单系统模式切换，不接受任意命令。
- `action/OptimizeMap.action`：离线优化接口预留，当前实现 fail-closed 未实现。
- `action/Relocalize.action`：项目统一自动重定位 Goal、Feedback 和 Result 边界。
- `action/ExecuteCoverageTask.action`：覆盖任务 Goal、Result 和 Feedback 数据结构。
- `action/ExecuteWaypointTask.action`：Qt/其他前端到可靠 Nav2 多点执行器的任务边界。

构建后可通过 Python 的 `agt_interfaces.action.ExecuteCoverageTask` 或 C++ 的
`agt_interfaces/action/execute_coverage_task.hpp` 使用。包内测试会验证两种语言的生成产物，并对
Goal、Result、Feedback 执行 Python 序列化往返。

本包只定义数据接口，不实现 Action Server。覆盖任务服务端属于
`agt_coverage_planning`，多点导航任务服务端属于 `agt_navigation`。
自动重定位服务端属于 `agt_localization`；本包不实现候选搜索、配准、TF 或安全门禁。
系统健康节点属于 `agt_system_manager`，任务服务端仍必须在 Action 执行层再次检查
`TaskReadiness`。
