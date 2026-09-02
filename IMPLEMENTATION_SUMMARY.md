# Implementation Summary

已创建独立 ROS 2 Humble package：`src/agt_map_reconstruction`。

## 已实现

- `PointCloud2` 订阅，兼容 `/cloud_registered` 和 bag 中已有的 registered cloud topic；
- `Odometry` 订阅，若 odometry 与 cloud frame 一致可做位姿变换；
- 体素降采样；
- 基于 XY 邻域 PCA 局部平面拟合，不使用简单 Z 高度阈值；
- 点到平面距离与法向-Z 夹角的 ground/non-ground 分类；
- 跨帧体素出现次数的静态物体保留；
- OccupancyGrid、PGM/YAML、ground/obstacle/static PCD 输出；
- terrain 高程、坡度、粗糙度 NPY sidecar 和 `terrain.yaml` 索引；
- `/map`、`/ground_cloud`、`/obstacle_cloud`、`/static_cloud`；
- 默认实时兼容参数和真实 bag 专用抽样参数；
- RViz 配置：`src/agt_map_reconstruction/rviz/reconstruction.rviz`。

## 真实 bag 验证

执行了：

```bash
source install/setup.bash
ros2 launch agt_map_reconstruction reconstruction.launch.py \
  config:=/home/yangxuan/agt_navigation_runtime/src/agt_map_reconstruction/config/reconstruction_realbag.yaml \
  bag:=/home/yangxuan/agt_navigation_runtime/runtime/rosbag/bunker_mid360_mapping_20260901_211105 \
  play_bag:=true bag_rate:=30.0
```

构建和回放成功，结果目录为：

```text
results/bunker_mid360_mapping_20260901_211105/
```

最终验收统计：抽样输入 `2,334,000` 点，体素地图 `300,000` 点，ground `27,518` 点，non-ground `272,482` 点，static `70,083` 点；free `26,528` cells，occupied `24,233` cells，unknown `1,392,068` cells。输出包含 `map.pgm`、`map.yaml`、`terrain.yaml`、三个 PCD 和三个 terrain NPY sidecar。

本次 bag 使用 `/agt/commissioning/mapping/registered_points`，因为 bag 没有 `/tf` 动态数据。其点云 frame 是 `camera_init`，因此不能假设存在从 `bunker_odom` 到 `camera_init` 的可用 TF；真实 bag 配置显式设置 `assume_registered_cloud=true`、`raytrace_enabled=false`。这种模式生成的是已注册点云的二维投影，未伪造 free-space 射线。

真实 bag 验收采用每 5 帧取 1 帧、每帧最多 3,000 点、最终拟合最多 300,000 点，以避免 Python 端对约 3,400 万点做全量局部 SVD 时耗尽内存。报告中的 `raw_cloud_points_sampled` 明确标识了这一点。

## 运行命令

实时兼容默认入口：

```bash
source install/setup.bash
ros2 launch agt_map_reconstruction reconstruction.launch.py
```

自定义 cloud/odom：通过复制并修改 `config/reconstruction.yaml`，或传入自己的 ROS 参数文件。真实 bag：

```bash
source install/setup.bash
ros2 launch agt_map_reconstruction reconstruction.launch.py \
  config:=/home/yangxuan/agt_navigation_runtime/src/agt_map_reconstruction/config/reconstruction_realbag.yaml \
  bag:=/home/yangxuan/agt_navigation_runtime/runtime/rosbag/bunker_mid360_mapping_20260901_211105 \
  play_bag:=true bag_rate:=10.0
```

## 当前限制

- 没有动态 `/tf` 的 bag 无法恢复每帧传感器原点，因此不会错误地生成射线 free-space；
- 当前动态过滤使用注册地图中的跨帧体素出现次数，是第一版保守代理，不是基于完整轨迹的贝叶斯跟踪；
- 真实 bag 配置采用抽样，若要生产级干净地图，建议先录制包含 FAST-LIO `/cloud_registered`、`/aft_mapped_to_init` 或唯一动态 TF 的 bag，再启用 ray tracing 并提高点数上限；
- `terrain.yaml` 通过 NPY sidecar 保存 dense grid，避免将百万级浮点数组展开成超大 YAML；
- 未修改 FAST-LIO/FAST-LIVO2、Nav2 或既有包。
