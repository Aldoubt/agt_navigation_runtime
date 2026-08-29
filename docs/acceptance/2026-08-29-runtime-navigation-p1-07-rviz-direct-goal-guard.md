# P1-07 RViz Direct-Goal Guard Acceptance — 2026-08-29

## Decision

```text
IMPLEMENTED:       PASS
STATIC / CI:       PASS
ROS 2 HUMBLE:      NOT RUN ON CANONICAL P1 BRANCH
REAL VEHICLE:      NOT RUN
```

P1-07 closes the production `/goal_pose -> NavigateToPose` bypass while preserving explicit non-production developer/commissioning paths.

It does not change Mission, task, action, TF, lifecycle, safety or chassis ownership.

## Source

- Canonical branch: `feat/runtime-navigation-convergence-p1`
- P1-07 code head before documentation: `cacd0d4a48f1a43e1bf70f8bdc3b9d8dd9d757b4`
- Initial RED Runtime Contracts: `#351` / `33242069289`
- First GREEN Runtime Contracts: `#353` / `33242117197`
- Offline-compatibility RED: `#354` / `33242175974`
- Final code-head GREEN: `#355` / `33242202456`

## Problem closed

Before P1-07, `src/agt_navigation/launch/navigation.launch.py` unconditionally started:

```text
goal_pose_bridge.py
```

The bridge subscribes `/goal_pose` and sends `nav2_msgs/action/NavigateToPose` directly. That allowed a standard production navigation composition to bypass Mission/Task ownership.

The formal capability server already had:

```text
allow_direct_pose_goals=False
```

Therefore P1-07 changes only the launch exposure of the compatibility bridge; it does not redesign navigation execution.

## Accepted behavior

### Production Runtime

`navigation.launch.py` now declares:

```text
enable_rviz_goal_bridge=false
```

and starts `goal_pose_bridge.py` only under an `IfCondition` on that flag.

Default production motion remains:

```text
MissionManager
  -> ExecuteWaypointTask
  -> navigation_capability_server.py
  -> Nav2
  -> Collision Monitor
  -> agt_safety
  -> chassis
```

`navigation_capability_server.py` remains fail-closed for direct pose goals:

```text
allow_direct_pose_goals=False
```

### Offline simulator

`offline_navigation.launch.py` explicitly passes:

```text
enable_rviz_goal_bridge=true
```

This preserves the existing offline `/goal_pose` developer workflow without changing the production default.

### Field commissioning

`agt_field_commissioning/launch/field_navigation.launch.py` declares:

```text
enable_rviz_goal_bridge=false
```

and only forwards an explicit operator opt-in to the production navigation launch. It does not create a second goal bridge and contains no separate `NavigateToPose` client.

Ordinary Phase C commissioning therefore remains guarded by default. A later controlled single-goal field acceptance may explicitly use:

```text
enable_rviz_goal_bridge:=true
```

but this must never become the production composition default.

## TDD evidence

### Initial RED — production and commissioning guard absent

Runtime Contracts `#351` (`33242069289`) failed only the new P1-07 group:

```text
P1 RViz direct-goal guard: 2 failed, 2 passed
```

All pre-existing groups remained green in the same run:

```text
V3-01 contracts:               19 passed
V3-02 odometry:                 9 passed
V3-03 execution:               18 passed
SystemManager:                 36 passed
Site Runtime owner:            45 passed
P1 task-storage:               52 passed
P1 site-navigation:            26 passed
P1 field commissioning:        24 passed
```

The two failures were exactly the missing default-disabled production flag and missing commissioning opt-in surface.

### First GREEN

After guarding production and commissioning, Runtime Contracts `#353` (`33242117197`) passed.

```text
P1 RViz direct-goal guard: 4 passed
```

### Compatibility RED — offline developer path

A follow-up contract made the existing offline `/goal_pose` behavior explicit rather than allowing it to disappear implicitly.

Runtime Contracts `#354` (`33242175974`) failed only:

```text
test_offline_simulation_explicitly_keeps_direct_goal_bridge_enabled
```

Result:

```text
P1 RViz direct-goal guard: 1 failed, 4 passed
```

All other groups stayed green.

### Final code-head GREEN

After `offline_navigation.launch.py` explicitly opted in, Runtime Contracts `#355` (`33242202456`) passed at code head `cacd0d4a48f1a43e1bf70f8bdc3b9d8dd9d757b4`.

Fresh job-log counts:

```text
V3-01 contracts:               19 passed
V3-02 odometry:                 9 passed
V3-03 execution:               18 passed
SystemManager:                 36 passed
Site Runtime owner:            45 passed
P1 task-storage:               52 passed
P1 site-navigation:            26 passed
P1 field commissioning:        24 passed
P1 RViz direct-goal guard:      5 passed
```

## Invariants preserved

P1-07 does not:

- change `ExecuteWaypointTask` or Mission schemas;
- add a second direct-goal bridge;
- change GlobalCorrectionManager or `map -> odom` ownership;
- change Nav2 lifecycle transition ownership;
- bypass Collision Monitor, `agt_safety` or chassis guards;
- mark a direct RViz goal as a production Mission;
- claim ROS 2 Humble or real-hardware validation.

## Gate state

```text
P1-07 Code   [x]
P1-07 STATIC [x]
P1-07 HUMBLE [ ]
P1-07 FIELD  [ ]
```

This status is based on code-head run `#355`. A fresh Runtime Contracts run is still required after the acceptance/convergence documentation commits before final-head verification is complete.
