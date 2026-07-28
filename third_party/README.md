# Third-party dependencies

## livox_ros_driver2

- 来源：旧工作区 `/home/yangxuan/ros2_ws/src/livox_ros_driver2`
- 旧仓库：`https://github.com/Aldoubt/ros2_3d-nav.git`
- 基线提交：`115c7beeaea02593957af46ccbecc263bc5cf12f`
- 上游许可证：MIT，见 `livox_ros_driver2/LICENSE.txt`
- 本地调整：旧仓库版本已支持相邻 Livox-SDK2 或 `/usr/local` 系统安装回退；为兼容
  当前系统 SDK，移除了本项目不使用的 MID360s 枚举分支，MID360 数据路径保持不变

第三方源码只做必要的构建兼容调整。设备 IP、topic remap 和 V2 frame 规则放在
`agt_sensor_adapters`，不写入 vendor 目录。

## FASTLIVO2_ROS2

- 来源：`https://github.com/Aldoubt/FASTLIVO2_ROS2.git`
- 固定提交：`a713004f0ba0624c8fb80d85c7047fe62523c6fb`
- 目录：`third_party/fast_livo2_ros2`
- 上游许可证：GPL-2.0，见 `fast_livo2_ros2/LICENSE`
- 本地调整：增加原生 TF 发布开关；使用 vikit 导出的 CMake target；增加
  `/cloud_registered_lidar` 当前帧雷达坐标点云，供 OctoMap 使用动态传感器原点；修正
  上游 `package.xml` 与实际 GPL-2.0 许可证不一致的声明

FAST-LIVO2 已 vendor 到主仓库，不再由 `nav_dependencies.repos` 下载，也不依赖 `/tmp`
安装空间。算法接口和 topic remap 仍由 `agt_mapping` 管理。

## rpg_vikit_ros2_fisheye

- 来源：`https://github.com/Rhymer-Lcy/rpg_vikit_ros2_fisheye.git`
- 固定提交：`fee3d50ae2af472fb27eb62b4526dd4b32ede8ef`
- 目录：`third_party/rpg_vikit_ros2_fisheye`
- 导入范围：仅 FAST-LIVO 使用的 `vikit_common`、`vikit_ros`；不导入 `vikit_py`、嵌套
  Git 元数据、备份和上游 `ername` 残留
- 本地调整：补齐 `ament_cmake` build type，移除失效的 `cmake_modules` manifest 依赖，
  x86 使用 `-march=x86-64 -mtune=native` 保持与系统 PCL/FAST-LIVO 的 Eigen 对齐 ABI 一致
- 许可证状态：两个 package manifest 均声明 GPLv3，但固定提交没有独立 LICENSE/COPYING；
  正式对外发布前必须完成来源和许可证文本审计，详见 `AGT_VENDOR.md`

Vikit 已随主仓库构建，不再由 `nav_dependencies.repos` 导入，也不允许通过旧工作区 overlay
掩盖缺失依赖。

## relocalization_core / ndt_omp_ros2

- `relocalization_core` 来源：旧工作区 `relocalization_module/relocalization_core`，Apache-2.0，
  见 `relocalization_core/LICENSE`
- `ndt_omp_ros2` 来源：旧工作区同名包，基线提交
  `115c7beeaea02593957af46ccbecc263bc5cf12f`，BSD-2-Clause
- 目录：`third_party/relocalization_core`、`third_party/ndt_omp_ros2`
- 本地调整：移除与算法库无关的 NDT 示例程序和数据；移除 core 中多余的直接 libusb
  链接。ROS/TF 适配由 `agt_localization` 实现，不写入第三方核心。

## Ros_Qt5_Gui_App

- 项目维护 fork：`https://github.com/Aldoubt/Ros_Qt5_Gui_App.git`
- 分支：`agt-navigation-v2`
- 固定提交：`82d44b08bcce2286183f8bf9df33ab457fa2d1b7`
- 原始上游：`https://github.com/chengyangkj/Ros_Qt5_Gui_App.git`
- 目录：`third_party/ros_qt5_gui_app`
- 上游许可证：GPL-2.0，见 `ros_qt5_gui_app/LICENSE`
- 本地策略：主仓库内置 fork 的固定源码快照，配置和构建时不联网；Qt 修改同步到上述
  分支并同时更新固定提交。源码包含项目多点 Action、地图加载保护、可配置 `FixedFrameId`、
  通信线程安全退出和幂等 ROS shutdown；新增版本化 Task Library、C++ 任务数据模型/原子仓库、
  地图绑定与基础栅格校验、地图两点击定姿/拖动编辑、Task Center 内嵌页签，以及 schema-v1
  任务文件到项目 Action 的提交和 missed-waypoint 反馈；Task Library 可从实时刷新的拓扑点
  下拉框快照点名、米制位姿和 yaw；新增 transient-local 示教路线/方向/
  转弯标注显示、首次路线视野适配，并允许只读 profile 禁止手动速度 publisher、隐藏控制面板；
  navigation/offline profile 隐藏底图写回和旧拓扑任务页，统一使用 Task Library，新建任务后
  直接进入两点击定姿，空任务保存显示可操作提示；任务保存只校验启用端点，不再把点间显示
  连线当作直线路径，Task Library 可直接提交当前草稿到 Nav2 planner-only 预览链；任务点
  数字覆盖在朝向箭头之上，预览链会反馈逐段规划进度并在后端缺失时立即提示；候选地图 profile
  可独立禁止另存为和打开其他地图，只允许将编辑原位保存到受管候选文件。当前快照新增
  `control-center-v1`/`legacy` 可替换壳层、light/dark token 主题、profile 驱动能力策略，
  并通过 ViewModel 和 ROS2 channel 消费 `RobotState`、`MissionStatus`、`ExecuteMission`、
  `SetMissionRunState` 和 `ChangeSystemMode`；旧 waypoint 执行与 `/goal_pose` 仅保留为
  默认关闭的兼容/调试入口。受管建图、重定位、地图资产以及 Bag/实验页面分别调用
  `ManageMappingSession`、`Relocalize`、map manager 和 experiment manager 的项目接口；
  navigation 模式参数只使用 RobotState 中 map manager 返回的活动地图资产；手动速度 topic
  即使缺少 profile 覆盖也 fail-safe 默认到 `/agt/cmd_vel_manual`。
  构建产物写入
  `build/ros_qt5_gui_app`，不提交 Git。

## BUNKER ROS2

- 来源：`https://github.com/agilexrobotics/bunker_ros2.git`
- 分支：`humble`
- 固定提交：`c4737f249129e88c8e9e0bfeb3af81b498a0ebbe`
- 目录：`third_party/bunker_ros2`
- 上游许可证：Apache-2.0（仓库 LICENSE）；package 元数据标记 BSD
- 本地调整：增加 odom TF 开关和底层命令超时，项目默认关闭其 TF，避免与定位链冲突。

## UGV SDK

- 来源：`https://github.com/agilexrobotics/ugv_sdk.git`
- 分支：`main`（浅克隆后 vendor）
- 固定提交：`c3dfaf444f9bae10757e546acae055aaf4a13de7`
- 目录：`third_party/ugv_sdk`
- 上游许可证：BSD，见目录内 LICENSE
- 本地调整：将旧 catkin 元数据适配为 ament/colcon，默认不构建示例程序，并修复 BUNKER
  执行器状态数组从 3 项复制到 2 项目标数组时的越界写入；CAN 协议解析不改。未保留与
  编译无关、体积约 113 MB 的多车型 PDF/DOCX `docs/` 目录。

## opennav_coverage / Fields2Cover

- `opennav_coverage` 来源：`https://github.com/open-navigation/opennav_coverage.git`
- 目标分支：`humble-v2`；固定提交：`f413d0da7b4e52249b9abdb9d1fec7cef0238449`
- 上游许可证：Apache-2.0
- `Fields2Cover` 来源：`https://github.com/Fields2Cover/Fields2Cover.git`
- 目标 tag：`v2.0.0`；固定提交：`3613525c241538fa9fd9df3e1209ae8184627958`
- 上游许可证：BSD-3-Clause
- F2C 的 `steering_functions`、`matplotplusplus` 和 `nlohmann/json` 传递源码也按其
  `F2CUtils.cmake` 中的提交固定在 `nav_dependencies.repos`
- 获取方式：由 `nav_dependencies.repos` 导入独立外部工作区，不 vendor 到本仓库

`humble-v2` 明确适配 Fields2Cover v2，并在上游 CI 的 Humble 工作流中使用 `v2.0.0`。
本项目第一版只依赖 `ComputeCoveragePath`、Coverage Server、Row Coverage Server 和消息；
不把 Coverage Navigator backport、BT 节点或 demo 作为必需运行链。构建时使用系统
`ros-humble-ortools-vendor`，并通过 `FETCHCONTENT_SOURCE_DIR_*` 使用清单中的传递源码，
禁止 Fields2Cover 在 CMake 阶段联网获取依赖。

完整导入、rosdep、构建及版本核验流程见
[`docs/development/coverage_dependencies.md`](../docs/development/coverage_dependencies.md)。
