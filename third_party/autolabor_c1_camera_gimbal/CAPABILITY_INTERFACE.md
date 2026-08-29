# Camera-Gimbal Capability 接口冻结

## 1. 模块边界

对任务控制系统公开的业务接口只有：

- `/camera_gimbal/acquire_view` — `camera_gimbal_interfaces/action/AcquireView`
- `/camera_gimbal/health` — `camera_gimbal_interfaces/msg/CapabilityHealth`

底层 `/pantilt_camera_serial0/move_pantilt` 属于驱动/调试接口。导航、Nav2、巡检点、地图、机器人 TF、任务顺序和报告不属于本模块。

## 2. AcquireView 语义

一次成功调用严格表示：

1. 请求参数合法；
2. 云台串口、反馈和低层 Action 可用；
3. 相机流处于新鲜状态；
4. `MovePantilt` 返回真正稳定到位；
5. 完成额外 `settle_time`；
6. 收到一帧**在 settle 完成之后产生的新图像**；
7. `image_stamp > reached_stamp`；
8. 若 `save_image=true`，图像已成功写入本机文件系统。

任一条件不满足均不能返回业务 SUCCESS。

## 3. Goal

```text
float64 heading
float64 roll
float64 pitch
float64 tolerance      # 0 = 使用节点默认值
float64 timeout        # 0 = 使用节点默认值
uint32 stable_samples  # 0 = 使用节点默认值
float64 settle_time    # 0 = 使用节点默认值
float64 image_timeout  # 0 = 使用节点默认值
bool save_image
string tag
```

机械范围继承驱动：

- heading: `[-160°, +160°]`
- roll: `[-40°, +40°]`
- pitch: `[-90°, +90°]`

负数超时/容差、NaN/Inf、越机械限位都会返回 `ERROR_INVALID_GOAL`，不会向云台发运动命令。

## 4. Result Error Code

| Code | 名称 | 含义 |
|---:|---|---|
| 0 | `ERROR_OK` | 云台稳定到位并获取新图像 |
| 100 | `ERROR_INVALID_GOAL` | 参数非法/越机械范围 |
| 101 | `ERROR_BUSY` | 已有 AcquireView 正在执行 |
| 200 | `ERROR_GIMBAL_UNAVAILABLE` | 串口/反馈/低层 Action 未就绪 |
| 201 | `ERROR_GIMBAL_REJECTED` | 低层 MovePantilt 拒绝 goal |
| 202 | `ERROR_GIMBAL_FAILED` | 低层运动反馈超时/运动超时/串口等失败 |
| 300 | `ERROR_CAMERA_UNAVAILABLE` | 调用前相机流不新鲜 |
| 301 | `ERROR_IMAGE_TIMEOUT` | 到位后没有获得严格新图像 |
| 302 | `ERROR_IMAGE_SAVE_FAILED` | 新图像获得，但保存失败 |
| 400 | `ERROR_CANCELED` | 上层取消 |
| 900 | `ERROR_INTERNAL` | 未预期内部错误 |

上层控制程序必须根据 `success + error_code` 判断结果，不解析 `message` 字符串。

## 5. 快速调用

只指定姿态，其余数值传 `0` 使用节点默认值：

```bash
ros2 action send_goal /camera_gimbal/acquire_view \
  camera_gimbal_interfaces/action/AcquireView \
  "{heading: -30.0, roll: 0.0, pitch: 0.0, tolerance: 0.0, timeout: 0.0, stable_samples: 0, settle_time: 0.0, image_timeout: 0.0, save_image: true, tag: 'P01_left'}" \
  --feedback
```

典型任务控制逻辑只需要：

```text
导航系统完成自己的 NavigateToPose
        ↓
控制系统调用 AcquireView(P01_left)
        ↓
success=true ? 保存结果元数据 : 按 error_code 决定 retry/abort
        ↓
控制系统继续自己的下一任务
```

本模块不接收巡检点，也不调用 Nav2。

## 6. Result 时间戳

`reached_stamp`：低层云台已经连续稳定判定成功后，由 capability 记录的 ROS time。

`image_stamp`：最终返回的新图像原始 `Image.header.stamp`。

验收强制要求：

```text
image_stamp > reached_stamp
```

如果上层需要机器人位姿，可用 `image_stamp` 查询自己的 `map -> base_link` TF；该职责不进入云台模块。

## 7. 取消/超时

低层 `MovePantilt` 在收到取消或运动超时时，会在编码器反馈仍新鲜时尝试发送“当前编码器姿态”的角度命令作为 best-effort hold。公共 `AcquireView` 取消时会等待低层取消流程短暂完成后再返回。

这不是安全级急停：若串口断开、反馈已经陈旧或硬件不响应，软件无法保证物理立即停止。正式设备的急停仍应由独立硬件/整机安全链路负责。
