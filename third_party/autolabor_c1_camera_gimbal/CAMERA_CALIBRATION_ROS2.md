# Camera Calibration — Phase 2（暂缓）

Phase 2 当前不执行。Phase 1 RAW 验收完成后，使用实体棋盘格对本机 C1 重新标定；不得把其他设备的标定文件当作本机结果。

## 计划流程

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 run camera_calibration cameracalibrator --size 8x6 --square 0.108 \
  --ros-args -r image:=/cv_camera0/image_raw
```

按实际棋盘格内角点数量和方格边长替换示例参数。结果保存为：

```text
config/calibration/user/c1_3840x2160.yaml
```

之后才启用 CameraInfo、`image_proc` 和 `/image_rect`，并单独验收内参、畸变模型和矫正图像。Phase 2 不改变 Phase 1 的 RAW 验收记录。
