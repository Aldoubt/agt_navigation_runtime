# agt_map_builder

`agt_map_builder` 是独立的离线地图生成模块。它读取 FAST-LIVO2 已注册的三维点云 PCD，在点云已经处于现有 `map` 坐标系的前提下生成 Nav2 可加载的二维地图包。模块不修改 FAST-LIVO2、Nav2 或 TF，也不重新定义任何 frame；后续可由 `Ros_Qt5_Gui_App` 调用同一个 Python API/CLI。

## 使用

在 ROS 2 工作空间中构建后：

```bash
ros2 run agt_map_builder build_map \
  --input /data/registered_cloud.pcd \
  --output /data/inspection_maps/site_001 \
  --config /path/to/map_builder.yaml
```

如果不传 `--config`，使用内置默认参数。`--output` 是地图包目录；生成后可直接交给 Nav2 `map_server`：

```bash
ros2 run nav2_map_server map_server --ros-args \
  -p yaml_filename:=/data/inspection_maps/site_001/map.yaml
```

流程为：ASCII PCD → 体素降采样 → 每个 XY 栅格的最低点地面高度 → 高程梯度坡度 → 可通行性。低于 `max_slope_deg` 的栅格是 free，介于两个坡度阈值之间是 unknown，高于 `unknown_slope_deg` 是 occupied；同一栅格内高程差超过 `obstacle_height_m` 也会标为 occupied。无点栅格保持 unknown。

输出包含 `map.yaml`/`map.pgm`（Nav2 标准输入）、`metadata.yaml`、`elevation_map.pgm`、`traversability_map.pgm` 和 `manifest.json`。manifest 中的 `hash.sha256` 是 `map.pgm` 字节紧接 `map.yaml` 字节后的 SHA-256，用于现场版本确认。

第一阶段支持 ASCII 和普通 binary PCD（字段中必须包含 `x y z`）；binary_compressed PCD 会明确报错。点云应由 FAST-LIVO2 注册到现有地图坐标系，模块不会偷偷进行 TF 变换。

## 测试

```bash
pytest src/agt_map_builder/test
```
