# Autolabor C1 Camera-Gimbal ROS2 Capability

这是 Autolabor C1 相机云台的 ROS2 Humble 原子能力交付包。目标不是承担导航或巡检任务编排，而是向任意任务控制系统提供一个稳定的：

> 姿态目标 -> 云台真正稳定到位 -> 获取稳定后的新图像 -> 结构化返回

## 包结构

src/
├── camera_gimbal_interfaces/      # 对控制系统公开的 Action/Health
├── camera_gimbal_capability/      # AcquireView 业务能力层
├── pantilt_camera_serial/         # 串口协议 + MovePantilt 低层可靠运动
├── autolabor_c1_bringup/          # 一键启动、实机/模拟验收工具、拍照脚本
├── opencv_camera_node/            # OpenCV 相机节点（替代 usb_cam）
└── rviz_pantilt_plugin/           # RViz2 人工调试面板

## 环境

- Ubuntu 22.04
- ROS2 Humble
- opencv_camera_node（自建，基于 OpenCV VideoCapture，替代 usb_cam）
- Boost.Asio / OpenCV / cv_bridge
- RViz2（仅调试需要）

### 为什么不用 usb_cam

实测 usb_cam 在目标相机上帧率极低（4K 仅 0.15 Hz，720p 仅 2-3 Hz）。
改用 opencv_camera_node 后，1080p MJPG 可稳定 27-28 fps。
详见 MODIFICATIONS.md。

## 启动

ros2 launch autolabor_c1_bringup autolabor_c1.launch.py \
  gui:=true \
  device_path:=/dev/video0 \
  port_name:=/dev/ttyUSB0 \
  image_width:=1920 \
  image_height:=1080 \
  fps:=30.0

### 启动参数

| 参数 | 默认值 | 说明 |
|---|---|---|
| device_path | /dev/video0 | 相机设备路径 |
| image_width | 1920 | 图像宽度（4K 太慢，建议 1080p） |
| image_height | 1080 | 图像高度 |
| fps | 30.0 | 帧率 |
| port_name | /dev/ttyUSB0 | 云台串口路径 |
| baud_rate | 115200 | 串口波特率 |
| query_rate | 10.0 | 编码器反馈查询频率 |
| gui | true | 是否启动 RViz2 |
| capture_output_root | ~/autolabor_c1_capture | 图像保存根目录 |

## 公开接口

| 接口 | 类型 | 定位 |
|---|---|---|
| /camera_gimbal/acquire_view | AcquireView action | 控制系统首选公开接口 |
| /camera_gimbal/health | CapabilityHealth | READY/BUSY/DEGRADED/ERROR |
| /pantilt_camera_serial0/move_pantilt | MovePantilt action | 驱动级运动验收/调试 |
| /cv_camera0/image_raw | Image | 标准相机流 |

### AcquireView 示例（实测推荐参数）

ros2 action send_goal /camera_gimbal/acquire_view \
  camera_gimbal_interfaces/action/AcquireView \
  "{heading: -30.0, roll: 0.0, pitch: 0.0, tolerance: 3.0, timeout: 20.0, stable_samples: 2, settle_time: 0.5, image_timeout: 5.0, save_image: true, tag: 'P01_left'}" \
  --feedback

注意：默认容差 1.5 度实测过严，建议传 3.0。默认超时 8s 大角度运动可能不够，建议传 20.0。

## 拍照脚本

手动拍一张（带云台角度）：
ros2 run autolabor_c1_bringup save_with_angle.py

自动连续拍照（每 60 帧保存一张）：
ros2 run autolabor_c1_bringup auto_save_with_angle.py

照片保存在 ~/autolabor_c1_capture/saved_images_with_angle/

## 实测推荐参数

| 参数 | 推荐值 | 默认值 | 说明 |
|---|---|---|---|
| image_width/height | 1920x1080 | 3840x2160 | 4K 帧率极低 |
| tolerance | 3.0 | 1.5 | 默认过严 |
| timeout | 20.0 | 8.0 | 大角度运动不够 |
| stable_samples | 2 | 3 | 减少等待 |
| settle_time | 0.5 | 0.25 | 到位后等更久 |
| image_timeout | 5.0 | 2.0 | 给图像更多时间 |

## 错误码

| code | 含义 |
|---:|---|
| 0 | 成功 |
| 100 | 参数非法 |
| 101 | 正忙 |
| 200 | 云台不可用 |
| 201 | 低层 goal 被拒绝 |
| 202 | 低层运动失败 |
| 300 | 相机不可用 |
| 301 | 到位后无新图像 |
| 302 | 图像保存失败 |
| 400 | 取消 |
| 900 | 内部异常 |

## 当前限制

- 串口断开不自动重连，需重启节点
- 4K 分辨率帧率极低，建议 1080p
- 默认容差 1.5 度过严，建议 3.0
- 取消/超时的 hold 命令不是安全急停
