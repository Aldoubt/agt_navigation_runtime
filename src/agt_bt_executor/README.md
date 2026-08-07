# agt_bt_executor

This package is the V25-05 BehaviorTree.CPP capability layer. It registers
project-owned BT nodes for `EvaluateTaskReadiness`, `Relocalize`, and
`ExecuteWaypointTask`. Nodes call only the project ROS interfaces; they do not
call Nav2 actions, publish velocity, or publish TF.

The package is a development smoke runner in V25-05. `agt_mission_manager`
remains the only Mission owner and the package is intentionally not included in
normal bringup. `v25_05_smoke.xml` is loaded by an installed package path, not
an arbitrary user-supplied filename. Groot2 monitoring is optional and off by
default.
