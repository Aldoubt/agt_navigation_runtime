# 第一次整体上车测试流程

## 目标

验证固定地图、INS 重定位、Nav2 导航、Qt5 任务下发和相机单次拍照能够组成一条完整闭环。第一次上车测试默认每个任务点拍照一次，任务只执行一轮。

## 1. 建图

1. 启动 MID360、INS/里程计和 `fastlio-sam-ros2` 建图链路。
2. 驾驶车辆完整经过测试区域，保证关键通道和目标点都有足够点云覆盖。
3. 结束建图并导出原始点云，例如：

   ```text
   mapping/localization_map.pcd
   ```

4. 原始 PCD 是重定位真值输入，只读保存，不在 Qt5 或 pcd2pgm 阶段覆盖。

## 2. 从 PCD 生成导航地图

使用第三方 `pcd2pgm` 将 PCD 转换为导航栅格：

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_field_commissioning pcd_to_nav_map.launch.py \
  pcd:=/absolute/path/to/localization_map.pcd \
  output_dir:=/absolute/path/to/navigation_map
```

生成并检查：

```text
navigation.pgm
navigation.yaml
```

此时必须确认 `navigation.yaml` 的 `image` 路径、`resolution`、`origin` 和 PGM 实际内容一致。建议先用 Qt5 离线打开 PGM 做目视检查。

## 3. Qt5 地图编辑与固定

1. 启动 Qt5 离线地图编辑器，打开 `navigation.yaml` 对应的 PGM。
2. 只编辑导航 PGM：清理孤立障碍、补齐断裂区域、处理导航不可通行区域。
3. 保存为编辑副本，不覆盖原始 `localization_map.pcd`，也不覆盖 pcd2pgm 原始输出。
4. 通过 Site 发布/固定流程生成不可变版本，例如：

   ```text
   runtime/sites/bunker_mid360_first/r01/
   ```

5. 固定版本至少包含：

   ```text
   map/navigation.yaml
   map/navigation.pgm
   map/localization_map.pcd
   map/localization_map.processing.yaml
   ```

6. 激活并校验 Site：地图 YAML/PGM、PCD SHA256、车辆 profile、Ackermann 几何和文件完整性都必须通过。

地图版本关系固定为：`navigation.pgm` 服务 Nav2，原始 `localization_map.pcd` 服务 INS/LIO 重定位；两者共享同一 Site revision，但文件所有权不同。

## 4. 上车启动顺序

第一次测试使用固定 Site，启动时显式指定本地运行时目录：

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_field_commissioning field_navigation.launch.py \
  sites_root:=/home/yangxuan/agt_navigation_runtime/runtime/sites \
  state_root:=/home/yangxuan/agt_navigation_runtime/runtime/state \
  site_id:=bunker_mid360_first \
  site_revision:=r01 \
  start_hardware:=true \
  start_inspection:=true \
  field_capture_backend:=service \
  field_capture_continue_on_failure:=false \
  field_capture_retry_count:=1 \
  field_capture_settle_enabled:=true
```

启动检查顺序：

1. 底盘急停/安全许可处于安全状态，先架空或低速测试。
2. MID360、INS、里程计和 TF 正常。
3. 重定位加载的 PCD SHA256 与 Active Site 一致。
4. Nav2 加载的 YAML/PGM SHA256 与 Active Site 一致。
5. `/agt/hmi/task_status`、`/agt/camera/capture` 和 `ExecuteWaypointTask` 服务/Action 可发现。
6. 先确认定位和安全状态已新鲜、有效，再允许车辆运动。

## 5. Qt5 布置任务

1. Qt5 打开与 Active Site 相同的导航地图。
2. 在目标位置添加点位并设置朝向；点位应落在导航可行区域内。
3. 按实际巡检顺序排列点位，保存任务草稿。
4. 第一次上车测试将 Repeat 设置为单轮，即 `loop_count=1`。
5. 点击 Start Task Chain。

数据流为：

```text
Qt5 /agt/hmi/task_chain
  -> hmi_task_adapter
  -> /agt/navigation/tasks/put
  -> /agt/navigation/execute_waypoint_task
  -> field_capture_capability_server
```

## 6. 单点导航、停车、拍照和继续

对每个点位，导航后端按以下状态机执行：

```text
检查 Active Site/定位/安全
  -> NavigateToPose
  -> ARRIVED
  -> 等待线速度 < 0.05 m/s 且角速度 < 0.05 rad/s 持续 1 s
  -> SETTLED
  -> 调用 /agt/camera/capture
  -> 保存图像、时间戳、机器人位姿、云台角度
  -> WAYPOINT_SUCCESS
  -> 下一个点
```

相机驱动拥有相机和云台硬件；导航后端只通过能力服务请求拍照，不发布相机控制命令。默认策略是拍照失败重试一次，仍失败则停止任务并保留失败证据，不继续运动。只有明确配置 `field_capture_continue_on_failure:=true` 时才允许跳过失败点继续。

## 7. INS 真值验收

INS/定位是本次验收的真值输入之一。每个点位至少记录：

- Active Site 的 `localization_map.pcd` SHA256；
- 定位状态和时间戳；
- 到点时机器人位姿；
- 导航目标位姿与实际到点误差；
- 拍照文件路径、拍照时间戳和云台实际角度。

验收时重点确认：车辆在固定 PCD 上稳定重定位，导航使用同一 Site revision 的 PGM，点位到达后车辆确实静止，再产生有效照片。

## 8. 测试完成与故障处理

任务完成后检查 HMI 状态为 `FINISHED`，每个点位均有成功状态和照片；检查是否按配置返回 Home。

出现定位失效、安全许可过期、Nav2 失败或取消请求时，后端应取消当前导航目标并停止任务。不要通过 Qt5 直接发布 `/cmd_vel` 绕过安全链路。

故障排查优先顺序：

```bash
ros2 topic echo /agt/hmi/task_status
ros2 topic echo /agt/maps/active --once
ros2 topic echo /agt/localization/status --once
ros2 service list | rg 'camera/capture|navigation/tasks/put'
ros2 action list | rg 'execute_waypoint_task|navigate_to_pose'
```

如果需要重新编辑地图，应创建新的 Site revision（例如 `r02`），重新绑定任务；不要在任务执行期间替换 `r01` 中的 PGM 或 PCD。
