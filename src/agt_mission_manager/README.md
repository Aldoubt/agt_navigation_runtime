# agt_mission_manager

`agt_mission_manager` 是有限顺序 Mission 的唯一业务 owner。它支持 `WAYPOINT_TASK`、
`WAIT_DURATION` 和 `WAIT_EVENT`，通过 `/agt/missions/execute` 执行，通过
`/agt/missions/set_run_state` 暂停或恢复，并在 `/agt/missions/status` 发布权威状态。

Waypoint 步骤只调用项目 `/agt/navigation/execute_waypoint_task` Action；本包不调用 Nav2 原生
Action、不启动 launch、不发布 TF 或速度。父任务暂停/取消会等待子 Action 确认取消；恢复前
重新检查 active map、定位与 `TaskReadiness`，并从已记录 waypoint feedback 生成剩余子目标。
等待步骤均有正有限上限，暂停期间不消耗剩余时间。

Mission 文件位于 `runtime/missions/<mission_id>/<mission_version>/mission.yaml`。schema、hash、
路径与地图绑定规则见 `docs/interfaces/mission_schema.md`。审计日志是原子替换的 JSONL；manager
重启发现活动状态时只发布 `INTERRUPTED`，不会自动恢复运动。

启动：

```bash
ros2 launch agt_mission_manager mission_manager.launch.py runtime_dir:=runtime
```
