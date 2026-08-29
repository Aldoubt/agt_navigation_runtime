# rviz_pantilt_plugin (RViz2)

ROS2 Humble 的 RViz2 云台控制面板。

- 自动发现 `*/pantilt_angle_info` 并选择云台命名空间；
- 显示编码器角与 `PantiltStatus`；
- 角度设置/回中通过 `MovePantilt` Action，只有稳定到位才显示 `REACHED`；
- 模式切换通过 `PantiltCommand` Service；
- W/A/S/D 提供人工速度控制；
- 已修复原 ROS1 插件“FullFollow 按钮实际发送 HeadingPitchFollow”的命令错误。

编译：

```bash
source /opt/ros/humble/setup.bash
colcon build --packages-select pantilt_camera_serial rviz_pantilt_plugin --symlink-install
source install/setup.bash
```

在 RViz2 中选择：`Panels -> Add New Panel -> rviz_pantilt_plugin/PantiltRvizPanel`。
