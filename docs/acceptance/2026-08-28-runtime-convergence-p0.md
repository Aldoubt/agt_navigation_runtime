# Runtime Convergence P0 Acceptance — 2026-08-28

## Final status

```text
Selected stable baseline:                    PASS
Safety producer/consumer contract:           PASS
Pure readiness policy:                       PASS
Authoritative agt_system_manager:            PASS
System-manager executable/libexec install:   PASS
Local ROS 2 Humble full build:               PASS (26 packages)
Selected ROS package regression:             PASS (109 tests, 0 failures)
Waypoint action stability follow-up:         PASS / no reproducible defect
System-manager launch:                       PASS
RobotState topic:                            PASS
TaskReadiness topic:                         PASS
GetRobotState service:                       PASS
No-upstream fail-closed runtime smoke:        PASS
Final cloud Runtime Contracts:               PASS

P0 functional/runtime acceptance:            PASS
Clean-source fresh-clone reproduction:        DEFERRED FOLLOW-UP
```

P0 is frozen as functionally accepted on the target ROS 2 Humble workstation. A separate clean-source
fresh-clone/worktree reproduction remains desirable because the first full-workspace verification was performed
with pre-existing local modified/deleted source paths. Those local changes were intentionally preserved and were
not reset as part of this acceptance.

## Baseline

Convergence branch:

```text
feat/runtime-convergence-p0
```

Accepted source baseline:

```text
v3-03/acceptance-freeze
e62261a57cc4bd16448526e31d9897a0ef48a577
```

The baseline choice and deferred experimental branches are documented in
`docs/audits/2026-08-28-runtime-baseline-audit.md`.

## Accepted deliverables

### 1. Canonical safety diagnostic contract

The generic V3 safety controller, waypoint execution path, ROUTE runtime-gate fixture, and cloud cross-package
contract now use one canonical status identity:

```text
agt_safety/controller
```

The legacy `agt_safety/tracked_controller` identity is forbidden by the execution contract guard.

Key TDD evidence:

- run #175 / `33144895532`: RED on the new cross-package safety assertion;
- run #176: GREEN after producer/consumer alignment;
- run #192 at `b70bf5228bd418cbd96aebcb70c7f41130c66304`: RED after extending the guard to the ROUTE fixture;
- commit `3abe8a9fe0b9cd7259e939e65e1ac624f8ff34b4`: fixture aligned;
- run #193: V3-01/V3-02/V3-03/system-manager cloud stages PASS.

### 2. Fail-closed readiness core

`agt_system_manager.readiness` owns deterministic navigation readiness evaluation. Required evidence covers:

```text
required system health
active READY map identity
accepted TRACKING localization bound to that map
fresh safety status + explicit motion enable + clear E-stop latch
fresh connected chassis evidence
```

Stable blocker codes include:

```text
SYSTEM_HEALTH_UNKNOWN
SYSTEM_HEALTH_BLOCKED
ACTIVE_MAP_UNKNOWN
ACTIVE_MAP_NOT_READY
LOCALIZATION_UNKNOWN
LOCALIZATION_NOT_TRACKING
LOCALIZATION_MAP_MISMATCH
SAFETY_UNKNOWN
MOTION_DISABLED
ESTOP_LATCHED
CHASSIS_UNKNOWN
CHASSIS_DISCONNECTED
```

Key TDD evidence:

- run #178 / `33145126010`: RED because the readiness module did not exist;
- runs #180/#181: GREEN after the pure readiness implementation.

### 3. Authoritative `agt_system_manager`

Accepted package:

```text
src/agt_system_manager/
├── agt_system_manager/readiness.py
├── config/system_manager.yaml
├── launch/system_manager.launch.py
├── scripts/system_manager_node.py
└── test/test_readiness_core.py
```

Authoritative outputs:

```text
/agt/system/health
/agt/system/task_readiness
/agt/system/robot_state
```

Read services:

```text
/agt/system/health/get
/agt/system/task_readiness/evaluate
/agt/system/robot_state/get
```

P0 evidence inputs:

```text
/diagnostics
/agt/maps/active
/agt/localization/status
/agt/missions/status
/agt/safety/status
/agt/chassis/status
/agt/chassis/connected
/agt/data/bags/status
```

The node is read-model aggregation only. It does not start algorithms, activate maps, publish velocity, execute
shell commands, or contain operator Gateway/Web transport business logic.

### 4. Symlink-install executable contract

Local runtime smoke initially exposed:

```text
executable 'system_manager_node.py' not found on the libexec directory
```

Root cause was the direct `install(PROGRAMS scripts/system_manager_node.py ...)` path under
`colcon --symlink-install`, where a repository-created 0644 source file can remain non-executable behind an
install symlink.

The fix reuses the established `agt_navigation` pattern: create a build-tree script copy with explicit executable
permissions and install that generated copy.

TDD evidence:

- run #196 at `07c0e292b2a74f4b3310564263e214ca4a6d09d5`: RED on the new libexec executable contract;
- commit `bba03211add2bb738d47eb0affa129b33178bbef`: generated executable-copy install;
- run #197 / `33152229566`: all cloud Runtime Contracts PASS.

## Local ROS 2 Humble acceptance

### Full build

A fresh build-artifact rebuild completed:

```text
colcon build --symlink-install
Summary: 26 packages finished
```

No package build failed. Existing dependency warnings did not block the build.

### Selected P0 regression

After the safety fixture remediation, the final selected package gate completed with:

```text
agt_system_manager
agt_navigation
agt_safety

Summary: 3 packages finished
Summary: 109 tests, 0 errors, 0 failures, 0 skipped
agt_navigation: 14/14 CTest targets passed
```

### Waypoint action stability follow-up

The previously observed `wait_for_server(timeout_sec=2.0)` failure could not be reproduced after the runtime-gate
fixture remediation:

```text
single previously failing case:  6/6 PASS
full pytest file:                10/10 PASS
CTest target repeat:             20/20 PASS
```

No production timeout, ROS_DOMAIN_ID, or ActionServer behavior was changed without evidence. Detailed evidence is
recorded in `docs/acceptance/2026-08-28-runtime-convergence-p0-waypoint-stability-followup.md`.

### No-upstream fail-closed runtime smoke

`ros2 launch agt_system_manager system_manager.launch.py` successfully started the production node after the
libexec remediation.

With no active-map, localization, safety, or chassis producers started, the authoritative read model reported:

```text
TaskReadiness.ready: false
RobotState.navigation_ready: false
RobotState.message: BLOCKED

blocker_codes:
- SYSTEM_HEALTH_UNKNOWN
- ACTIVE_MAP_UNKNOWN
- LOCALIZATION_UNKNOWN
- SAFETY_UNKNOWN
- CHASSIS_UNKNOWN
```

`/agt/system/robot_state`, `/agt/system/task_readiness`, and `/agt/system/robot_state/get` all returned the same
fail-closed state. This proves missing evidence does not silently promote the robot to READY.

## Remaining non-blocking follow-up

The first full-workspace build used fresh `build/`, `install/`, and `log/` artifacts but the Git source worktree
contained pre-existing local M/D changes. A fresh clone/worktree reproduction should be performed later when those
local changes can be preserved safely. This does not invalidate the completed target-machine P0 runtime smoke,
but it remains an explicit reproducibility follow-up.

## Deferred next convergence slice

P0 intentionally does not implement:

1. production Site Package / map activation owner for `/agt/maps/active`;
2. stable unified BUNKER bringup based on `agt_odometry`;
3. Nav2 lifecycle aggregation into the read model;
4. LIO/wheel/GNSS fusion;
5. traversability algorithm upgrades;
6. operator Gateway/HMI command transport.

The next convergence slice is the Site/Map runtime owner, followed by stable BUNKER unified bringup. Only after
those providers are closed should the real operator Gateway be attached to `RobotState` and `TaskReadiness`.
