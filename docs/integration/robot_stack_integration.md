# 传感器、建图、导航上位机接入逻辑

## 当前接入关系

```text
ASENSING INS -> /ins/{pose,odom,navsatfix,velocity,status}
                         │
                         └─ 验收/对比输入（当前不发布 TF、不直接融合）

Livox MID360 -> FAST-LIO (`fast_lio/fastlio_mapping`)
                         │
                         └─ finalized localization_map.pcd
                                      │
                                      └─ pcd2pgm（离线）-> navigation.pgm + navigation.yaml
                                                         │
                                                         └─ review/activate -> Nav2 `/map`

Autolabor C1:
  usb_cam `/cv_camera0/image_raw`
  pantilt_camera_serial `/pantilt_camera_serial0/move_pantilt`
                         │
                         └─ camera_gimbal `/camera_gimbal/acquire_view`
                                      │
                                      └─ agt_inspection -> evidence/vision result

agt_robot_hmi -> `/map`、机器人状态显示、任务编辑、导航点交互
              -> 当前上游的字符串占位接口（见下文边界）
```

## 推荐运行顺序

1. 传感器预检：启动 `bunker_mid360.launch.py`，按需打开 `start_ins:=true`；确认
   `/ins/status`、雷达 topic 和底盘状态新鲜。
2. 建图：运行 `field_mapping.launch.py`。建图前端固定使用
   `third_party/FAST_LIO_SLAM_ros2`，正常退出以触发 PCD 保存。
3. 地图转换：运行 `pcd_to_nav_map.launch.py` 调用 `pcd2pgm`，人工检查 PGM/YAML
   后再通过现有 map review / activation 流程登记版本。
4. 导航：只从已激活 Site Package 加载 Nav2 地图与定位 PCD；HMI 负责显示和点位编辑，
   任务执行仍由 `agt_navigation` / `agt_mission_manager` 所有。
5. 到点拍照：导航 Action 成功到达并通过停车稳定门禁后，inspection 调用
   `/camera_gimbal/acquire_view`。该 Action 的顺序是“云台运动 -> 编码器连续稳定 ->
   等待 timestamp 晚于到位时刻的新图 -> 保存并返回路径/时间戳”。成功条件不是串口写入成功。
6. 验收：用 INS 的 `/ins/pose` 或 `/ins/odom` 与运行时定位输出做时间对齐、位置/航向误差统计；
   INS 当前是验收真值输入，不替代 FAST-LIO 或 `map -> odom` 的唯一 TF owner。

## 相机当前控制与返回

当前 C1 驱动由 `autolabor_c1_camera_gimbal` 提供：

- 图像：`usb_cam` 发布 `/cv_camera0/image_raw`。
- 云台低层：`pantilt_camera_serial` 提供 `MovePantilt`，依赖新鲜编码器反馈、角度容差和连续稳定帧。
- 原子能力：`camera_gimbal_capability` 提供
  `/camera_gimbal/acquire_view`，结果含 `success`、`error_code`、`image_path`、
  `reached_stamp`、`image_stamp`、实际角度和消息。
- 上层适配：`agt_inspection` 使用该 Action；失败按错误码处理，不解析 message。

典型失败分支包括：云台不可用 `200`、运动失败 `202`、相机断流 `300`、到位后没有新图 `301`、
保存失败 `302`、取消 `400`。因此“等待相机拍照返回成功指令”已经有明确的原子接口，
但真实硬件 PASS 仍需在 C1 实机上执行上游验收，当前环境不能代替实机验收。

## HMI 边界与后续对接

`agt_robot_hmi` 已作为独立 ROS 2/Qt5 包接入并可单独构建。上游当前显示 `/map`、
`/agt/robot/pose`、`/agt/robot/battery`，导航点和任务控制使用 `/agt/...` 字符串/Trigger
占位接口；本工程正式控制链使用版本化 `ExecuteWaypointTask`、`ExecuteInspectionTask`、
`GetRobotState` 等接口。因此本阶段不让 HMI 直接写 Nav2、底盘、相机或云台，也不把占位
topic 伪装成已完成的正式控制对接。下一阶段应增加一个单独的 HMI adapter，将 HMI 的点位
提交映射到项目 Action/Service，并继续保持 HMI 不拥有机器人业务状态。

## 地图资产隔离规则

`pcd2pgm`、Qt5 HMI 和 Active Site 使用不同目录角色，禁止原位互相覆盖：

```text
commissioning/<run>/mapping/localization_map.pcd       # 原始/重定位输入，只读
commissioning/<run>/navigation_map_pcd2pgm/             # pcd2pgm 输出，只读基线
runtime/hmi_working/<site>/<revision>/                  # HMI 编辑副本
/opt/agt/sites/<site>/versions/<revision>/map/           # 审核后冻结的 Active Site 资产
```

- `pcd2pgm` 只读取 `localization_map.pcd`，输出到新的 `navigation_map_pcd2pgm` 目录。
- HMI 查看时加载 `navigation.yaml`；编辑前先复制整个地图 YAML/PGM 到
  `runtime/hmi_working/...`，不要在 commissioning 输出目录或 Active Site 中点击保存。
- HMI 保存功能会写回所加载地图的 PGM/YAML，并可能写 `.topology`，因此不能把 Active Site
  路径直接交给 HMI 的编辑/另存流程。
- 编辑完成后生成新的候选 revision，做栅格、路径、点位检查，并重新绑定 PCD/YAML/image
  SHA256，再由 Site Registry/Active Store 执行 review -> activate。
- 导航启动只解析 Active Site，不扫描 commissioning 或 HMI 工作目录；激活后的地图资产视为
  不可变文件，任何修改都必须产生新 revision。
