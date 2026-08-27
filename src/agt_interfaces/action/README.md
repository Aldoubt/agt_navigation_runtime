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
- `ExecuteInspectionTask.action`：执行一个版本化、地图绑定的定点巡检任务。任务点的导航姿态
  不在巡检资产中重复保存，而是引用现有单点 TaskGroup 的 id/revision/hash。
- `MoveGimbal.action`：云台 pan/tilt 能力边界，只描述目标姿态、超时与结果，不绑定厂商协议。
- `InspectImage.action`：视觉模型能力边界。任务侧只依赖稳定的模型 id/version、耗时、主置信度和
  `result_json`；PyTorch/ONNX/TensorRT 等具体实现留在视觉 adapter 内。

单张图像采集使用 `srv/CaptureImage.srv`。巡检执行器负责决定何时允许拍照；相机或视觉节点
不得自行把“收到实时图像”解释为某个任务点已经到位。
