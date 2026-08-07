# agt_mapping

隔离 FAST-LIVO2 等后端并输出统一接口：

- `/agt/mapping/odometry`：`odom` 下的 `base_footprint` 里程计。
- `/agt/mapping/registered_points`：注册点云。
- FAST-LIVO2 的 backend 输入 topic 是 adapter 内部接口，不属于对外 topic contract；adapter
  将其标准化后只对外发布 `/agt/mapping/registered_points`。

FAST-LIVO2 的正常 MID360 输入为 `/agt/sensors/lidar/custom_filtered`。该 topic 由
`agt_livox_self_filter` 从保留的原始 `/agt/sensors/lidar/custom` 生成，因此车体点不会
进入 FAST-LIVO2 配准、局部体素地图或本次会话生成的 PCD；后置
`agt_perception/local_obstacle_filter` 仍继续保护 Nav2 障碍输入。
- `odom -> base_footprint`：由当前连续里程计唯一发布。

建图模式由 `agt_bringup` 覆盖 `pcd_save.pcd_save_en=true`。LIO-only 模式在运行中使用
带符号 64 位稀疏体素键累计质心，正常退出时直接输出 `localization_map.pcd` 和
`localization_map.processing.yaml`，不再为关机降采样保留完整原始点云。Bunker 基线体素为
`0.25 m`，绝对坐标保护上限为 `10000 m`；非有限点和越界点会被拒绝并写入处理记录。
只有处理记录为 `state: ready` 的 PCD 才能交给重定位。导航模式明确覆盖保存为 false，
只提供连续里程计和当前帧点云。应通过
`agt_bringup/system.launch.py` 切换模式，不要直接修改基础 YAML，避免导航时覆盖地图。

x86 构建固定使用通用 `x86-64` 指令集并仅以 `-mtune=native` 调优，保持 Eigen 与系统
PCL 的 16 字节对齐 ABI 一致。不要重新加入 `-march=native`，否则 PCL `VoxelGrid`
分配的点缓冲区可能在 FAST-LIVO 析构时以不同策略释放并崩溃。

算法基线固定为 `Aldoubt/FASTLIVO2_ROS2@a713004`，MID360 使用 Livox
`CustomMsg` 输入。该版本无条件发布 `camera_init -> aft_mapped`。使用前必须应用
`patches/fast_livo2_publish_tf.patch`；启动文件会设置 `common.publish_tf=false`，adapter
结合 `agt_description` 外参转换并发布标准 TF。未应用补丁时禁止同时启动机器人描述。
同时应用 `patches/fast_livo2_cmake_portability.patch`，移除算法仓库对工作区
`../../install` 布局的硬编码，改用 vikit 导出的 CMake target。算法源码已固定在
`third_party/fast_livo2_ros2` 并随本项目编译。`vikit_common` 和 `vikit_ros` 也已按固定提交
vendor 到 `third_party/rpg_vikit_ros2_fisheye`，全新工作区只需 source ROS 后构建本仓库；
禁止再 source 旧工作区来提供 vikit，以免隐藏依赖或加载错误 ABI 的共享库。
该分支在 `common.img_en=false` 时仍初始化相机模型，因此 launch 会额外加载
`config/camera_disabled_placeholder.yaml`。其中是上游示例占位值，不是 MID360 或机器人
相机标定，也不会启用图像订阅。
该分支原生注册点云固定使用 `camera_init` frame，backend 先发布到内部 topic
`/agt/mapping/backend/registered_points`，adapter 再将同一世界坐标语义统一为 `odom` 并发布
公共接口。点数据不做二次坐标变换。
注册点云保持 FAST-LIVO2 的 reliable QoS，以兼容 OctoMap 的 reliable 订阅。

```bash
ros2 launch agt_description description.launch.py
source install/setup.bash
ros2 launch agt_mapping fast_livo2_mapping.launch.py
```

当前已完成接口隔离、位姿换算、本仓库算法编译和局部雷达帧点云回放验证；完整 bag 的新旧
轨迹/地图质量对比与实机验收仍待执行。
