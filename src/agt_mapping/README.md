# agt_mapping

隔离 FAST-LIVO2 等后端并输出统一接口：

- `/agt/mapping/odometry`：`odom` 下的 `base_footprint` 里程计。
- `/agt/mapping/registered_points`：注册点云。
- FAST-LIVO2 的 backend 输入 topic 是 adapter 内部接口，不属于对外 topic contract；adapter
  将其标准化后只对外发布 `/agt/mapping/registered_points`。

FAST-LIVO2 的正常 MID360 输入为 `/agt/sensors/lidar/custom_filtered`。该 topic 由
`agt_livox_self_filter` 从保留的原始 `/agt/sensors/lidar/custom` 生成。Runtime 默认
`geometry_source:=urdf`：过滤器读取当前 `robot_description` 的 collision geometry，在
`base_link`/collision link 中临时判断自身返回，但保留通过点的原始 Livox 坐标与逐点字段后再送入
FAST-LIVO2。profile 模式保留为 A/B 回归，后置 `agt_perception/local_obstacle_filter` 仍继续保护
Nav2 障碍输入。

URDF 模式要求 `robot_description` 与当前平台严格匹配。BUNKER 不得先启动通用
`description.launch.py` 的默认 MK-mini 几何再运行 BUNKER odometry；应由 Runtime `agt_bringup`
统一启动，或者显式使用平台专用 description：

```bash
# 推荐：Runtime 统一保证平台描述、self-filter 和 FAST-LIVO2 参数一致；P0 强制关闭 PCD 保存
ros2 launch agt_bringup system.launch.py \
  platform:=bunker \
  start_navigation:=false \
  start_localization:=false \
  start_chassis:=false

# 仅做 FAST-LIVO2 模块调试时，BUNKER 必须先加载 BUNKER description
ros2 launch agt_description bunker_description.launch.py
source install/setup.bash
ros2 launch agt_mapping fast_livo2_mapping.launch.py \
  lidar_self_filter_geometry_source:=urdf
```

需要对照旧过滤几何时：

```bash
ros2 launch agt_mapping fast_livo2_mapping.launch.py \
  lidar_self_filter_geometry_source:=profile
```

完全绕过过滤只用于显式 baseline：

```bash
ros2 launch agt_mapping fast_livo2_mapping.launch.py \
  start_lidar_self_filter:=false
```

`odom -> base_footprint` 由当前连续里程计唯一发布。

Runtime 的 `agt_bringup/system.launch.py` 在 P0 中固定传入 `save_pcd:=false`，因此正式运行链只提供
连续里程计和注册点云，不承担 READY 地图资产生产。若需调试 FAST-LIVO2 的 PCD 保存能力，可直接
启动 `fast_livo2_mapping.launch.py` 并显式设置 `save_pcd:=true`；由这条调试链生成的 PCD 仍只是
commissioning/raw asset，正式地图处理、语义、版本与 READY Site Package 由
`agt_navigation_v2` 离线侧完成后再交给 Runtime 消费。不要通过修改基础 YAML 让导航运行时写图。

LIO-only 保存实现使用带符号 64 位稀疏体素键累计质心，正常退出时可输出
`localization_map.pcd` 和 `localization_map.processing.yaml`。Bunker 基线体素为 `0.25 m`，
绝对坐标保护上限为 `10000 m`；非有限点和越界点会被拒绝并写入处理记录。只有处理记录为
`state: ready` 的 PCD 才可作为后续离线处理或定位验证候选；Runtime 正式导航仍应消费已验收的
READY 资产。

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

当前已完成接口隔离、位姿换算、本仓库算法编译和局部雷达帧点云回放基础。URDF self-filter 的
代码/配置/单测已迁入 Runtime，但完整 `raw/profile/urdf` 同 bag 轨迹、地图质量、误删/漏删和实机
验收仍待执行；验收前不得把该能力标记为 vehicle-validated DONE。
