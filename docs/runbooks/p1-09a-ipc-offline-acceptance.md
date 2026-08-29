# P1-09A 工控机离线验收 Runbook

> 目标：在 **不连接 BUNKER、不连接 MID360、不发送真实底盘运动命令** 的条件下，在工控机上验证 ROS 2 Humble 构建、P1 Runtime 核心合同、Nav2 离线闭环、生产 `/goal_pose` 防旁路，以及 Site Runtime 的 fail-closed 行为。
>
> 本文只覆盖 `P1-09A IPC OFFLINE`。它不能替代后续 `P1-09B` 原地硬件验收和 `P1-09C` 场地导航验收。

---

## 0. 验收边界

通过本阶段只能说明：

- Ubuntu 22.04 / ROS 2 Humble 环境可以构建当前 convergence core；
- 关键 ROS interface 可以正常生成和 import；
- Nav2 + safety + 差速履带 simulator 可以在工控机上形成闭环；
- Collision Monitor 的离线阻停链可以工作；
- production `navigation.launch.py` 默认不接受 RViz `/goal_pose` 旁路；
- Site Runtime 在没有 Active Site / 非法 Site 时 fail-closed；
- 如果有真实 Site Package，可在完全不接硬件的情况下验证 deploy / validate / activate。

本阶段 **不验收**：

- CAN、BUNKER 驱动；
- MID360 / IMU；
- FAST-LIVO2 实际传感器输入；
- `map -> odom` 实机重定位；
- 实际制动距离、障碍物检测能力；
- 实车 waypoint / Mission 执行。

---

## 1. 测试前记录版本

```bash
cd ~/agt_navigation_runtime

git checkout feat/runtime-navigation-convergence-p1
git pull --ff-only

git status --short
git rev-parse HEAD

lsb_release -ds
uname -a
source /opt/ros/humble/setup.bash
echo "ROS_DISTRO=$ROS_DISTRO"
python3 --version
colcon version-check || true
```

通过标准：

```text
[ ] Ubuntu 22.04
[ ] ROS_DISTRO=humble
[ ] git status 无未解释的源码修改
[ ] 当前 commit SHA 已记录
```

建议创建本轮证据目录：

```bash
export P1_RUN="$(date +%Y%m%dT%H%M%S)"
export P1_EVIDENCE="$PWD/results/p1_09a_ipc_offline/$P1_RUN"
mkdir -p "$P1_EVIDENCE"

git rev-parse HEAD | tee "$P1_EVIDENCE/git_head.txt"
lsb_release -a 2>&1 | tee "$P1_EVIDENCE/os.txt"
env | grep -E '^ROS_|^RMW_' | sort | tee "$P1_EVIDENCE/ros_env.txt"
```

---

## 2. 依赖准备

如果工控机已经装好依赖，可以直接进入第 3 节。

如果之后要物理断网，请在断网前执行一次：

```bash
source /opt/ros/humble/setup.bash

sudo rosdep init 2>/dev/null || true
rosdep update

rosdep install --from-paths \
  src/agt_interfaces \
  src/agt_runtime_contracts \
  src/agt_site_runtime \
  src/agt_site_navigation \
  src/agt_system_manager \
  src/agt_navigation \
  src/agt_safety \
  src/agt_operator_gateway \
  src/agt_description \
  --ignore-src --rosdistro humble -r -y
```

之后的软件验收不依赖网络。

---

## 3. Gate A — Humble 干净构建

先复现 CI 的 convergence core，并额外构建离线 simulator 所需的 `agt_description`：

```bash
cd ~/agt_navigation_runtime
source /opt/ros/humble/setup.bash

colcon build \
  --symlink-install \
  --event-handlers console_direct+ \
  --packages-select \
    agt_interfaces \
    agt_runtime_contracts \
    agt_site_runtime \
    agt_site_navigation \
    agt_system_manager \
    agt_navigation \
    agt_safety \
    agt_operator_gateway \
    agt_description \
  2>&1 | tee "$P1_EVIDENCE/colcon_build.log"
```

构建后：

```bash
source install/setup.bash
ros2 pkg prefix agt_navigation
ros2 pkg prefix agt_site_runtime
ros2 pkg prefix agt_site_navigation
ros2 pkg prefix agt_description
```

通过标准：

```text
[ ] colcon build 返回 0
[ ] 上述 4 个 package 都能从 install space 找到
[ ] 无 unresolved symbol / missing shared library / package not found
```

如果这里失败，**停止后续验收**，先保存 `colcon_build.log`。

---

## 4. Gate B — Humble 单元/接口回归

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash

colcon test \
  --event-handlers console_direct+ \
  --packages-select \
    agt_interfaces \
    agt_runtime_contracts \
    agt_site_runtime \
    agt_site_navigation \
    agt_system_manager \
    agt_navigation \
    agt_safety \
    agt_operator_gateway \
  2>&1 | tee "$P1_EVIDENCE/colcon_test.log"

colcon test-result --verbose \
  2>&1 | tee "$P1_EVIDENCE/colcon_test_result.log"
```

通过标准：

```text
[ ] colcon test 执行完成
[ ] colcon test-result 无 failed test
```

### 4.1 安装后 interface + fail-closed smoke

```bash
python3 - <<'PY' | tee "$P1_EVIDENCE/interface_smoke.txt"
from agt_interfaces.msg import NavigationRuntimeStatus, SiteNavigationBinding
from agt_site_navigation.resolver import (
    ActiveSiteNavigationResolver,
    SiteNavigationBindingError,
)

assert NavigationRuntimeStatus.STATE_READY == 2
assert SiteNavigationBinding.STATE_READY == 1

resolver = ActiveSiteNavigationResolver(
    sites_root='/tmp/agt-p1-09a-no-sites',
    vehicle_profile='/tmp/agt-p1-09a-no-profile.yaml',
    vehicle_schema='/tmp/agt-p1-09a-no-vehicle-schema.json',
    site_schema='/tmp/agt-p1-09a-no-site-schema.json',
)

try:
    resolver.resolve(None)
except SiteNavigationBindingError as exc:
    assert exc.code == 'NO_ACTIVE_SITE', exc.code
    print('PASS:', exc.code)
else:
    raise AssertionError('missing Active Site must fail closed')
PY
```

必须输出：

```text
PASS: NO_ACTIVE_SITE
```

---

## 5. Gate C — production RViz 直接目标防旁路

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash

NAV_SHARE="$(ros2 pkg prefix --share agt_navigation)"

grep -F 'DeclareLaunchArgument("enable_rviz_goal_bridge", default_value="false")' \
  "$NAV_SHARE/launch/navigation.launch.py"

grep -F 'condition=IfCondition(LaunchConfiguration("enable_rviz_goal_bridge"))' \
  "$NAV_SHARE/launch/navigation.launch.py"
```

通过标准：

```text
[ ] production navigation.launch.py 默认 enable_rviz_goal_bridge=false
[ ] goal_pose_bridge 受 IfCondition 控制
```

注意：后面的 `offline_navigation.launch.py` **会故意显式打开 bridge**，仅用于离线仿真，不代表生产默认行为。

---

## 6. Gate D — 无车 Nav2 离线闭环

### 6.1 启动正常离线场景

终端 A：

```bash
cd ~/agt_navigation_runtime
source /opt/ros/humble/setup.bash
source install/setup.bash

ros2 launch agt_navigation offline_navigation.launch.py \
  2>&1 | tee "$P1_EVIDENCE/offline_navigation.log"
```

该入口使用：

- package 内置测试地图；
- `differential_drive_simulator.py`；
- `/agt/odometry/odometry`；
- `map -> odom -> base_footprint` simulator TF；
- `/agt/perception/obstacle_cloud`；
- Nav2；
- Collision Monitor；
- `agt_safety`；
- 仅离线场景允许的 `/goal_pose` bridge。

### 6.2 检查 Nav2 lifecycle

终端 B：

```bash
source /opt/ros/humble/setup.bash
source ~/agt_navigation_runtime/install/setup.bash

for n in \
  map_server \
  planner_server \
  smoother_server \
  controller_server \
  behavior_server \
  bt_navigator \
  waypoint_follower \
  collision_monitor
do
  echo "===== $n ====="
  ros2 lifecycle get "/$n"
done | tee "$P1_EVIDENCE/nav2_lifecycle.txt"
```

必须全部为：

```text
active [3]
```

### 6.3 检查 simulator 数据链

分别执行：

```bash
ros2 topic hz /agt/odometry/odometry
```

观察几秒后 `Ctrl+C`；预期约 30 Hz。

```bash
ros2 topic hz /agt/perception/obstacle_cloud
```

再检查 TF：

```bash
ros2 run tf2_ros tf2_echo map odom
ros2 run tf2_ros tf2_echo odom base_footprint
```

通过标准：

```text
[ ] /agt/odometry/odometry 连续发布
[ ] /agt/perception/obstacle_cloud 连续发布
[ ] map -> odom 存在
[ ] odom -> base_footprint 存在
```

### 6.4 发送一个软件模拟目标

这一步只驱动 simulator，不连接真实底盘：

```bash
ros2 action send_goal /navigate_to_pose nav2_msgs/action/NavigateToPose \
  "{pose: {header: {frame_id: map}, pose: {position: {x: 1.0, y: 0.0}, orientation: {w: 1.0}}}}" \
  --feedback
```

同时可观察：

```bash
ros2 topic echo /agt/odometry/odometry
```

通过标准：

```text
[ ] NavigateToPose goal 被接受
[ ] simulator 位姿发生连续变化
[ ] action 最终成功完成
[ ] 无 lifecycle node 意外掉到 inactive/error
```

完成后关闭终端 A。

---

## 7. Gate E — Collision Monitor 离线阻停

这是 Gate E 的 canonical acceptance path。不要再手工依赖 `ros2 topic echo` 来做最终判定。

重新启动离线场景：

```bash
ros2 launch agt_navigation offline_navigation.launch.py \
  synthetic_obstacle_enabled:=true \
  synthetic_obstacle_x:=0.7 \
  synthetic_obstacle_y:=0.0 \
  2>&1 | tee "$P1_EVIDENCE/offline_collision_monitor.log"
```

另一个终端运行 checker：

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash

ros2 run agt_navigation p1_09a_collision_monitor_gate.py \
  2>&1 | tee "$P1_EVIDENCE/p1_09a_collision_monitor_gate.log"
```

通过标准：

```bash
grep -E '^GATE_E_' "$P1_EVIDENCE/p1_09a_collision_monitor_gate.log"
```

必须看到：

```bash
GATE_E_OBSTACLE_PRESENT=PASS
GATE_E_RAW_COMMAND=PASS
GATE_E_COLLISION_STOP=PASS
GATE_E_SAFETY_STOP=PASS
GATE_E_ODOM_STOP=PASS
GATE_E=PASS
```

并且日志里应包含实际观测值：

```text
raw_max_linear
filtered_max_linear_after_settle
safety_max_linear_after_settle
odom_displacement
```

本 Gate 的目标是验证 Collision Monitor + Safety Controller 的离线截停链，并确认机器人没有明显位移。

---

## 8. Gate F — Site Runtime 无硬件 fail-closed

这一节完全不需要 Nav2、FAST-LIVO2、BUNKER 或 MID360。

```bash
cd ~/agt_navigation_runtime
source /opt/ros/humble/setup.bash
source install/setup.bash

export IPC_SITE_TEST="$PWD/runtime/p1_09a_site_test"
export SITES_ROOT="$IPC_SITE_TEST/sites"
export STATE_ROOT="$IPC_SITE_TEST/state"
export VEHICLE_PROFILE="$(realpath profiles/platforms/bunker.yaml)"

rm -rf "$IPC_SITE_TEST"
mkdir -p "$SITES_ROOT" "$STATE_ROOT"
```

启动 Site Runtime：

```bash
ros2 run agt_site_runtime site_runtime_node.py --ros-args \
  -p sites_root:="$SITES_ROOT" \
  -p state_root:="$STATE_ROOT" \
  -p vehicle_profile:="$VEHICLE_PROFILE"
```

另一个终端执行：

```bash
source /opt/ros/humble/setup.bash
source ~/agt_navigation_runtime/install/setup.bash

ros2 topic echo --once /agt/maps/active \
  --qos-durability transient_local \
  --qos-reliability reliable
```

空 `sites_root` 必须表现为无 Active Site / tombstone，不能伪造 READY。

再验证不存在的 Site：

```bash
ros2 service call /agt/maps/validate agt_interfaces/srv/ValidateMapVersion \
  "{map_id: 'missing_site', map_version_id: 'missing_revision'}"
```

通过标准：

```text
[ ] 空 registry 不会发布一个假的 READY Active Site
[ ] 不存在的 Site validation 返回失败
[ ] 无 crash / traceback / 非预期 Active Site 恢复
```

---

## 9. Gate G — 可选：真实 Site Package 离线验收

如果已经有离线地图重建仓库导出的完整 Site Package 1.0，可以在 **临时 test root** 中验证，不要直接写 `/opt/agt/sites`。

```bash
export SITE_ID=greenhouse_01
export SITE_REVISION=r01
export SITE_EXPORT=/absolute/path/to/export/$SITE_ID/$SITE_REVISION
export DEPLOY_DIR="$SITES_ROOT/$SITE_ID/$SITE_REVISION"

# 必须先停止上一节的 Site Runtime

test -f "$SITE_EXPORT/manifest.yaml"
test -f "$SITE_EXPORT/hashes.yaml"
test ! -e "$DEPLOY_DIR"
mkdir -p "$SITES_ROOT/$SITE_ID"
cp -a "$SITE_EXPORT" "$DEPLOY_DIR"
```

重新启动 Site Runtime 后验证：

```bash
ros2 service call /agt/maps/validate agt_interfaces/srv/ValidateMapVersion "{
  map_id: '${SITE_ID}',
  map_version_id: '${SITE_REVISION}'
}"
```

必须：

```text
success: true
version.state: READY
version.valid: true
```

然后显式激活：

```bash
export ACTIVATE_REQUEST_ID="p1-09a-${SITE_ID}-${SITE_REVISION}-${P1_RUN}"

ros2 service call /agt/maps/activate agt_interfaces/srv/ActivateMapVersion "{
  map_id: '${SITE_ID}',
  map_version_id: '${SITE_REVISION}',
  client_request_id: '${ACTIVATE_REQUEST_ID}'
}"
```

确认：

```bash
ros2 topic echo --once /agt/maps/active \
  --qos-durability transient_local \
  --qos-reliability reliable
```

通过标准：

```text
[ ] validate success=true
[ ] Site state=READY / valid=true
[ ] activate success=true
[ ] /agt/maps/active identity 与请求完全一致
[ ] map_hash / manifest/navigation/image/PCD hash 均非空且稳定
```

此处仍然 **不启动 field_navigation.launch.py**。真实 localization + Nav2 + sensor 输入属于 P1-09B/P1-09C。

---

## 10. 最终验收表

```text
P1-09A IPC OFFLINE

Environment
[ ] Ubuntu 22.04
[ ] ROS 2 Humble
[ ] branch/head 已记录
[ ] 工作区无未解释修改

Build/Test
[ ] selected-core colcon build PASS
[ ] selected-core colcon test PASS
[ ] colcon test-result 无失败
[ ] generated interfaces import PASS
[ ] NO_ACTIVE_SITE fail-closed PASS

Production guard
[ ] navigation.launch.py direct RViz goal 默认关闭

Offline Nav2
[ ] 8 个 required lifecycle nodes ACTIVE
[ ] simulator odometry 正常
[ ] map -> odom -> base_footprint 正常
[ ] 无障碍 NavigateToPose PASS
[ ] synthetic obstacle 阻停 PASS

Site Runtime
[ ] 空 Site registry fail-closed
[ ] missing Site validation fail-closed
[ ] （可选）真实 Site Package validate PASS
[ ] （可选）真实 Site Package activate PASS

P1-09A RESULT
[ ] PASS
[ ] FAIL — 保存日志，不进入 P1-09B
```

---

## 11. PASS 后下一步

只有本 Runbook 全部必选项通过后，才进入：

```text
P1-09B 原地硬件 Runtime
  BUNKER CAN
  MID360 + IMU
  TF
  FAST-LIVO2 odometry
  Site binding
  localization
  NavigationRuntimeStatus
  SystemManager
  全程默认 monitor / 禁止自主运动

P1-09C 场地运动验收
  单点
  waypoint
  cancel
  obstacle
  localization loss
  recovery
  Mission
```

不要因为 P1-09A 离线 simulator 成功，就把 BUNKER + MID360 `FIELD` gate 标绿。
