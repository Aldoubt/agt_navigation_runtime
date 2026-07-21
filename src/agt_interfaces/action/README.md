# action

统一任务动作接口目录。

- `Relocalize.action`：项目自动重定位请求。Goal 只暴露稳定的搜索模式和限制，内部候选仍由
  `agt_localization` 管理。
- `ExecuteCoverageTask.action`：覆盖任务请求、结果与阶段反馈。TASK-13 只负责生成和序列化；
  Action Server 行为在 TASK-14 实现。
