# agt_safety

本包独立完成速度仲裁、急停、定位/传感器健康门禁、超时和履带底盘运动约束，不依赖 Nav2 是否正常运行。

## 仲裁规则

- 新鲜的 `/agt/cmd_vel_manual` 优先于 `/agt/navigation/cmd_vel`
- 导航输入必须有新鲜且已接受的 `LocalizationStatus`（`TRACKING`、`pose_valid`、`localization_accepted` 且无错误）；定位失效时安全层立即阻断导航输入
- 当 `require_sensor_input_ready=true` 时，导航输入还必须有新鲜的 `agt_sensor_monitor/summary` 证据，且 `required_streams_healthy=true`；required LiDAR/IMU 断流或诊断过期时立即输出零速，原因记为 `sensor_input_unhealthy`
- 传感器和定位门禁仅阻断导航输入；手动输入仍保持最高软件仲裁优先级，便于故障恢复，但不能绕过急停
- 手动命令超过 0.35 秒、导航命令超过 0.50 秒即失效
- 启动默认禁止运动，必须调用 `/agt/safety/set_motion_enabled` 明确使能
- `/agt/safety/emergency_stop=true` 会锁存急停并立即输出零速；输入恢复后仍需调用 `/agt/safety/reset_emergency_stop`，再重新使能运动
- `/agt/safety/status` 是急停锁存和导航门禁的权威诊断源，包含 `emergency_stop`、`navigation_ready`、`localization_valid`、`sensor_input_ready`、`motion_enabled` 和输出速度
- 非有限数命令被拒绝；横移、升降、滚转和俯仰速度不会传给履带底盘
- 对 `linear.x`、`angular.z` 做速度和加速度限制，并根据差速履带模型约束左右履带速度

默认参数在 `config/bunker_safety.yaml`。BUNKER 默认配置要求新鲜的传感器健康证据，`sensor_status_timeout=1.5 s`。当前速度与加速度值是低速联调起点，不是最终实车认证值；尤其 `effective_track_width=0.62 m` 是根据外廓宽度做的保守估计，需要测量左右履带中心距离并通过原地转向测试校准。

定位状态每 5 秒执行一次低频 tracking validation，单次配准最多 3 秒；真机默认使用 `localization_status_timeout=10.0`，避免把正常的定位验证周期误判为失联。SOFTWARE_ONLY Gazebo 验证由于 canonical localization evidence 是稀疏事件，会在仿真 launch 中单独放宽 freshness window；LOST/invalid 状态仍在回调到达时立即生效，不改变真机默认配置。

关闭软件运动时，先调用 `/agt/safety/set_motion_enabled` 并确认诊断中的 `linear_output=0.0000`、`angular_output=0.0000`。

急停示例：

```bash
# 由已接入的硬件急停适配器发布 /agt/safety/emergency_stop；不要手工伪造清除信号
ros2 service call /agt/safety/reset_emergency_stop std_srvs/srv/Trigger "{}"
```

软件急停不能替代硬件急停。第一次实车测试应架空履带，随后在空旷区域以不高于 `0.15 m/s` 测量通信中断和急停制动距离，再逐级放开配置上限。
