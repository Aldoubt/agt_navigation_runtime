# Codex 验收 Prompt

将本文件内容作为 Codex 的执行约束。目标是验证 **camera-gimbal 原子能力**，不是验证 Nav2、巡检点或任务编排。

## 规则

1. 不得把模拟测试结果当作实机通过。
2. 不得因为节点存在、Service/Action goal 被接受就判定动作成功。
3. `AcquireView` 只有在 `MovePantilt` 成功、稳定等待完成、且 `image_stamp > reached_stamp` 时才能 PASS。
4. 任意自动化命令返回非零退出码时，停止验收并定位原因，不要修改验收标准绕过失败。
5. 实机测试必须有人在设备旁，确认云台运动方向和机械安全。
6. 不修改 Nav2、地图、巡检点或任务系统。
7. 如果 Codex 为修复失败而修改代码，必须从 `offline -> simulated` 重新完整跑一遍；不得只重跑曾失败的单项就宣告通过。
8. 不得降低角度容差、超时、freshness 判断或删除反例测试来换取 PASS。

## 执行顺序

### A. 离线门禁

```bash
cd <workspace>
./tools/run_acceptance.sh offline
```

要求：`colcon build`、`colcon test`、`colcon test-result --verbose` 全部成功。

### B. 无硬件集成门禁

```bash
./tools/run_acceptance.sh simulated
```

要求：

- 正常链路中心、-30°、+30°、回中全部 PASS，且 `image_stamp > reached_stamp`；
- 非法 999° 返回 `ERROR_INVALID_GOAL=100`；
- 云台不可用返回 `ERROR_GIMBAL_UNAVAILABLE=200`；
- 云台运动失败返回 `ERROR_GIMBAL_FAILED=202`；
- 执行前相机断流返回 `ERROR_CAMERA_UNAVAILABLE=300`；
- 运动后相机断流返回 `ERROR_IMAGE_TIMEOUT=301`，不得复用旧图像；
- 取消公共 Action 返回 `ERROR_CANCELED=400`，且低层 `target_active` 必须退出。

### C. 实机机器门禁

先由人工确认设备周围安全，再运行：

```bash
CAMERA_DEVICE=/dev/video4 \
GIMBAL_PORT=/dev/ttyUSB0 \
./tools/run_acceptance.sh hardware
```

如果系统已经由外部启动：

```bash
MANAGE_LAUNCH=0 ./tools/run_acceptance.sh hardware
```

要求：脚本最终输出 `MACHINE PASS`，并生成：

- `capability_summary.json`
- `machine_validation.json`
- 中心/左/右/回中图像
- build/test/status/launch 日志

## Codex 最终报告格式

只报告以下四项：

1. Offline gate: PASS/FAIL
2. Simulated gate: PASS/FAIL
3. Hardware machine gate: PASS/FAIL/NOT RUN
4. 未通过项及对应日志路径

Hardware 未运行时必须写 `NOT RUN`，禁止推断通过。
