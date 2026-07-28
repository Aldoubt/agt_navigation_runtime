# action

统一任务动作接口目录。

- `Relocalize.action`：项目自动重定位请求。Goal 只暴露稳定的搜索模式和限制，内部候选仍由
  `agt_localization` 管理。
- `ExecuteCoverageTask.action`：覆盖任务请求、结果与阶段反馈。TASK-13 只负责生成和序列化；
  Action Server 行为在 TASK-14 实现。
- `ManageMappingSession.action`：项目级建图会话状态机。`FINALIZE_CAPTURE` 正常收口在线资产后
  生成并质量校验离线射线 + `ground_temporal` 可编辑候选；失败的离线阶段可从固定预览重试。
  `COMMIT` 才登记新的不可变 READY 版本，并返回已登记 YAML 与版本任务目录；Result
  使用稳定错误码区分请求、服务、启动、栅格保存、正常停止、资产超时、提交和状态错误。
  不允许前端直接覆盖现有 READY 地图。
