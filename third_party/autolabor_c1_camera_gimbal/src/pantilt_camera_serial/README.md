# pantilt_camera_serial (ROS2 Humble)

Autolabor C1 云台 ROS2 驱动。串口协议本身与原 ROS1 驱动保持兼容，但控制接口被拆成两层：

- `send_command` Service：兼容底层命令，只确认参数合法和串口写入；
- `move_pantilt` Action：用于巡检/自动化，等待编码器反馈连续稳定后才返回成功。

## 编译

```bash
source /opt/ros/humble/setup.bash
colcon build --packages-select pantilt_camera_serial --symlink-install
source install/setup.bash
```

## 启动

```bash
ros2 launch pantilt_camera_serial pantilt_camera.launch.py \
  port_name:=/dev/ttyUSB0 baud_rate:=115200 query_rate:=10.0
```

## 反馈

`pantilt_angle_info` 为 `PantiltAngleInfo`，包含：

- `header.stamp`：接收并解析该反馈帧时的 ROS 时间；
- `heading/roll/pitch`：原协议中的对地角；
- `encoder_heading/encoder_roll/encoder_pitch`：相对基座的编码器角。

可靠到位判断使用 **encoder 三轴角度**，因为 Action 的目标是相对云台基座的机械目标。

## MovePantilt Action

机械范围：

- Heading: `[-160°, 160°]`
- Roll: `[-40°, 40°]`
- Pitch: `[-90°, 90°]`

默认判断：`tolerance=1.5°`，连续 `3` 个新反馈帧满足三轴最大误差约束才 `REACHED`。反馈超过 `feedback_timeout` 未更新会以 `RESULT_FEEDBACK_TIMEOUT` 失败；总运动时间超过 goal timeout 会以 `RESULT_MOTION_TIMEOUT` 失败。

## 状态

`pantilt_status` 同时提供串口连接、反馈新鲜度、目标状态、最大误差、稳定计数、有效接收帧数、CRC/协议错误数和 `last_error`。底层手动运动会标记 `UNVERIFIED`，不会伪装成 `REACHED`。

## 速度接口

`pantilt_vel` 保留原映射：`angular.z` 为 heading、`linear.x` 为 pitch。输入必须为有限值且在 `[-2.0, 2.0]`，异常值会被拒绝而不是直接窄化为 `int16_t`。
