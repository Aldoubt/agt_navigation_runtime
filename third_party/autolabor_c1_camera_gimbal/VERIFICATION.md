# Verification status

## 源码环境验证（2026-08-29）

- Python/source contract regression: 33 passed
- Pure C++ arrival/stability judge test: PASS
- Pure C++ serial protocol compatibility test: PASS
- Python syntax compilation: 14 files PASS
- XML parsing: 6 files PASS
- YAML/RViz parsing: 3 files PASS
- ROS2 launch Python AST parsing: 3 files PASS
- Active source scan: no catkin/rospy/ROS1 found

## 实机验证（Ubuntu 22.04 + ROS2 Humble，2026-08-29）

测试机器：ASUS TUF Gaming FA608FM

### 编译

- colcon build: 5 包全部编译通过（修复 std::max 后）
- 新增 opencv_camera_node 包：编译通过

### 设备识别

| 设备 | USB ID | 设备路径 |
|---|---|---|
| C1 相机（Wasintek） | 2aad:6373 | /dev/video0 |
| 云台串口（CH340） | 1a86:7523 | /dev/ttyUSB0 |

### 相机帧率测试

| 分辨率 | usb_cam | opencv_camera_node | v4l2-ctl 直测 |
|---|---|---|---|
| 3840x2160 (4K) | 0.15 Hz | 2-3 Hz | ~30 fps |
| 1920x1080 | 2-3 Hz | 27-28 Hz | ~30 fps |
| 1280x720 | 2-3 Hz | 27-28 Hz | ~30 fps |

结论：usb_cam 的 mmap IO 与该相机不兼容，改用 opencv_camera_node 后 1080p 稳定 27-28 fps。

### 云台运动测试

- 健康检查 check_status.py: PASS
- MovePantilt（容差 3.0、超时 20s）: success: true, result_code: 0
- 实测到位偏差：heading ~1-2 度、roll ~1-1.6 度、pitch ~2.5 度
- 默认容差 1.5 度过严，建议 3.0 度

### AcquireView 测试

- success: true, error_code: 0
- image_stamp > reached_stamp（到位后获取了新图像）
- 图像成功保存到文件系统

### 拍照脚本测试

- save_with_angle.py: 成功保存图像 + 云台角度
- auto_save_with_angle.py: 自动连续保存正常
- QoS 修复：角度话题需用 qos_profile_sensor_data

### RViz2 测试

- gui:=true 启动 RViz2 正常
- Image 显示面板可实时显示 1080p 画面

## 未验证项

- tools/run_acceptance.sh offline/simulated/hardware
- RViz2 云台控制插件运行时加载
- 4K 分辨率下的 AcquireView
