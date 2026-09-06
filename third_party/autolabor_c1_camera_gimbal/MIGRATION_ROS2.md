# ROS1 -> ROS2 / Capability 化变更说明

## ROS2 驱动层

1. catkin/roscpp/rospy/ROS1 RViz 迁移到 ament/rclcpp/rclpy/RViz2。
2. `PantiltAngleInfo` 增加 `std_msgs/Header`。
3. 默认云台查询频率从 1 Hz 提升为 10 Hz。
4. Service 不再无条件 `success=true`；未知命令、参数、范围、串口写失败均显式失败。
5. 新增 `MovePantilt.action`，以新编码器反馈、容差和连续稳定样本判断真正到位。
6. 新增 `PantiltStatus`：串口、反馈、目标、稳定计数、CRC/协议错误等可观察。
7. 手动/兼容运动命令会清除旧 `REACHED` 并标记 `UNVERIFIED`。
8. Action 运行期间拒绝会修改云台行为的兼容 Service，避免控制源冲突。
9. 取消/运动超时时，在反馈仍新鲜时 best-effort 下发当前编码器角度保持命令。

## Capability 层

新增独立：

- `camera_gimbal_interfaces`
- `camera_gimbal_capability`

业务公开接口变为 `/camera_gimbal/acquire_view`。它内部组合：

```text
MovePantilt
  -> stable REACHED
  -> settle_time
  -> strictly fresh Image
  -> optional save
  -> structured Result
```

Nav2、巡检点、地图和任务编排不进入本模块。

## 验收工具

新增：

- `tools/run_acceptance.sh offline`
- `tools/run_acceptance.sh simulated`
- `tools/run_acceptance.sh hardware`
- `tools/validate_acceptance.py`
- deterministic fake camera/gimbal
- camera-stale / gimbal-unavailable / post-motion-image-timeout / motion-failure / cancel negative gates
- `CODEX_ACCEPTANCE_PROMPT.md`
- `HUMAN_ACCEPTANCE_CHECKLIST.md`

机器通过和人工物理确认被明确拆开，模拟测试不能替代实机验收。

## 未擅自修改的协议点

原源码注释称 int16 “低位在前”，实际发送实现为高字节在前；反馈解析实际按低位在前。缺少厂商协议文档或实机抓包时继续保持旧实现实际行为，避免迁移本身改变硬件协议。
