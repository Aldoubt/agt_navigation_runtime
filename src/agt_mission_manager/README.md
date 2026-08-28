# agt_mission_manager

`agt_mission_manager` 是有限顺序 Mission 的唯一业务 owner。Sequential backend 支持：

```text
WAYPOINT_TASK
WAIT_DURATION
WAIT_EVENT
INSPECTION_TASK
RETURN_HOME
```

通过 `/agt/missions/execute` 执行，通过 `/agt/missions/set_run_state` 暂停或恢复，并在 `/agt/missions/status` 发布权威状态。

## Motion / authority boundary

普通 legacy `WAYPOINT_TASK` 继续保留当前兼容执行路径。`INSPECTION_TASK` 调用 `/agt/inspection/execute_task`。
`RETURN_HOME` 则是一个专用的最终 TaskGroup step，通过项目正式 `/agt/navigation/execute_waypoint_task` Action 下发：

```text
map_id
map_version_id
task_group_id
task_group_revision
expected_content_sha256
loop_count = 1
client_request_id
```

RETURN_HOME 不填写 deprecated `task_file / poses / loop` 输入。它在执行前重新检查 active map、定位和 `TaskReadiness`；定位丢失或 readiness blocked 时不会强制返航。

Schema 约束 RETURN_HOME 最多出现一次，并且只能是 Mission 最后一步。

## Inspection mission report

Sequential Mission 每次运行会建立：

```text
runtime/mission_reports/<mission_id>/<run_id>/
├── report.json
├── steps.csv
└── inspections.csv
```

Inspection child 的 `session_id` 和 `evidence_root_uri` 会被关联进 Mission report。若 inspection evidence 中存在 `report/report.json`，Mission report 会汇总 `raw_instance_count`，并在所有巡检都完成 POINT_LOCAL 清洗时提供：

```text
point_sum_estimate
```

它明确表示“各巡检点 point-local unique_count 的求和估计”，**不是全场 MISSION_DEDUP/global unique count**。当前 report 永远记录 `mission_dedup_applied=false`。

## Storage / restart

Mission 文件位于：

```text
runtime/missions/<mission_id>/<mission_version>/mission.yaml
```

审计日志是原子替换的 JSONL；manager 重启发现活动状态时只发布 `INTERRUPTED`，不会自动恢复运动。

## Normal launch

```bash
ros2 launch agt_mission_manager mission_manager.launch.py runtime_dir:=runtime
```

## Hardware-free inspection -> HOME acceptance

`mock_inspection_return.launch.py` 会在 `/tmp/agt_mission_mock_runtime` 创建可写的测试 Runtime，复用 `agt_inspection` 已验证的两点 × 三视角 mock stack，然后启动 Mission Manager。

Shell A:

```bash
rm -rf /tmp/agt_mission_mock_runtime
ros2 launch agt_mission_manager mock_inspection_return.launch.py
```

Shell B:

```bash
source /opt/ros/humble/setup.bash
source ~/agt_navigation_runtime/install/setup.bash

ros2 action send_goal \
  /agt/missions/execute \
  agt_interfaces/action/ExecuteMission \
  "{mission_id: 'mock_inspection_return', mission_version: 'v1', expected_content_sha256: 'sha256:825ea0ff78b237a64f5fea6419aac99117ff4bc870746d492410b7a1947c0ec0'}" \
  --feedback
```

Acceptance target:

```text
INSPECTION_TASK
  -> P001 × 3 views
  -> P002 × 3 views
  -> point-local aggregation
RETURN_HOME(home_mock)
MISSION SUCCEEDED
report_uri != empty
```

Then inspect:

```bash
find /tmp/agt_mission_mock_runtime -maxdepth 8 -type f | sort
cat /tmp/agt_mission_mock_runtime/mission_reports/mock_inspection_return/*/report.json
```
