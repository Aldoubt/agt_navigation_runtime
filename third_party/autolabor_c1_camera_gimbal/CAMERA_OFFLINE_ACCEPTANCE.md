# Camera Offline Acceptance — Phase 1 RAW

本文定义不依赖云台、runtime、Nav2 或 SLAM 的相机验收。环境为 ROS 2 Humble / Ubuntu 22.04，驱动使用 `usb_cam`。

## 冻结配置

- 优先验证 `3840x2160@30`；若设备或 USB 带宽不支持，记录实际协商结果，不得据此宣称 4K30 通过。
- 使用 `/cv_camera0/image_raw`，保留原始广角畸变。
- `camera_info_url: ""`；不启动 `image_proc`，不使用 `image_rect`。
- 不要求标定板或相机内参。

## 操作

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch autolabor_c1_bringup autolabor_c1.launch.py \
  gui:=false \
  device_path:=/dev/v4l/by-id/<C1-video-device> \
  port_name:=/dev/serial/by-id/<C1-control-device> \
  image_width:=3840 image_height:=2160 fps:=30.0
```

```bash
ros2 topic hz /cv_camera0/image_raw
ros2 topic echo --once /cv_camera0/image_raw/header
ros2 topic info /cv_camera0/image_raw -v
```

## 判定与证据

记录设备路径、像素格式、协商分辨率、实际 FPS、采集持续时间和首尾 timestamp。PASS 必须有真实输出证据，且满足：UVC 可打开、分辨率和 FPS 符合目标、timestamp 单调递增、持续采集无断流。未连接真实 C1 时只能报告未执行，不能报告硬件 PASS。

云台联动的“到位后新图”门禁属于 AcquireView 验收：必须证明 `image_stamp > reached_stamp`，不能复用到位前旧帧。
