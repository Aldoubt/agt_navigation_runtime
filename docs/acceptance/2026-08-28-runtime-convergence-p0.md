# Runtime Convergence P0 Acceptance — 2026-08-28

## Status

```text
Selected stable baseline: PASS
Safety producer/consumer contract: PASS (cloud regression)
Pure readiness policy: PASS (cloud regression)
System-manager source/read-model contract: PASS (cloud regression)
Final cloud Runtime Contracts: PASS
Local ROS 2 Humble clean build: PENDING
Local ROS package tests: PENDING
System-manager launch/runtime smoke: PENDING
Overall P0 acceptance: PENDING LOCAL ROS VERIFICATION
```

This record intentionally does not convert cloud/source evidence into a ROS-runtime claim.

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

## P0 deliverables

### 1. Canonical safety diagnostic contract

The generic V3 safety controller publishes:

```text
agt_safety/controller
```

The waypoint task server now consumes that same production status name. The old
`agt_safety/tracked_controller` fixture contract was removed from the waypoint consumer/test path.

RED evidence:

- GitHub Actions run `33144895532` (`Runtime Contracts` run #175)
- V3-01 contracts: PASS
- V3-02 odometry contracts: PASS
- V3-03 execution contracts: FAIL on the new cross-package assertion

GREEN evidence:

- run #176 at `1bf0284ab8bb5263a84800391dfe16d4218d4332`: PASS
- run #177 at `772efbe85070da2786b0ff1b9e0915d84d96eb8d`: PASS

### 2. ROS-independent readiness policy

Added `agt_system_manager.readiness` with immutable evidence/result models and deterministic
fail-closed navigation blocker ordering.

Required evidence covers:

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

RED evidence:

- GitHub Actions run `33145126010` (#178)
- V3-01/V3-02/V3-03 steps: PASS
- new system-manager step: FAIL because the readiness module did not yet exist

GREEN evidence:

- run #180 after the core implementation: PASS
- run #181 at `f4659ce8eb120b3aa615cfeae23da802a6df58dc`: PASS

### 3. Authoritative `agt_system_manager`

Added a new ROS package:

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

P0 input evidence:

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

Heartbeat-like safety evidence is freshness-gated with monotonic receive time. State-like map,
mission and bag snapshots remain known after receipt and expose their age in `RobotState`.

The node does not start algorithms, activate maps, publish velocity, execute shell commands, or contain an
operator Web/Gateway dependency.

`EvaluateTaskReadiness` P0 supports only `PROFILE_TASK_EXECUTION`. Unsupported profiles and
`validate_task:=true` are rejected explicitly rather than silently claiming support. Navigation task
file/revision/hash validation remains owned by the navigation task registry.

RED evidence:

- GitHub Actions run `33145287692` (#182): FAIL after adding the ROS source contract before the package existed

GREEN/source evidence:

- run #187 at the production node implementation: PASS
- run #188 at `7d75949ec487f29bffe890f1138eeb42d6f49d4a`: PASS
- run #190 at `a9c6ed3c6720e75759811b439ffc4a1a2dfa3233`: PASS, including Python AST parsing of the node/launch sources

Run #190 passed all cloud-capable workflow stages:

```text
V3-01 contract tests                 PASS
V3-02 odometry source contracts      PASS
V3-03 execution source contracts     PASS
runtime system-manager contracts     PASS
```

## Required local ROS 2 Humble gate

The cloud workflow does not provide a ROS 2 Humble build/runtime environment. Before this P0 can be frozen as
fully accepted, run the following on the target Ubuntu/ROS2 workstation.

```bash
cd ~/agt_navigation_runtime
git fetch origin
git switch feat/runtime-convergence-p0
git pull --ff-only origin feat/runtime-convergence-p0

source /opt/ros/humble/setup.bash
rm -rf build install log
colcon build --symlink-install
source install/setup.bash

colcon test \
  --packages-select agt_system_manager agt_navigation agt_safety \
  --event-handlers console_direct+
colcon test-result --verbose

ros2 launch agt_system_manager system_manager.launch.py --show-args
```

Expected gate:

```text
clean workspace build: zero package failures
agt_system_manager / agt_navigation / agt_safety tests: zero failures
system_manager.launch.py --show-args: resolves without package/import/config error
```

Then perform a no-motion startup smoke:

```bash
ros2 launch agt_system_manager system_manager.launch.py
```

In another terminal:

```bash
source ~/agt_navigation_runtime/install/setup.bash
ros2 topic echo /agt/system/robot_state --once
ros2 topic echo /agt/system/task_readiness --once
ros2 service call /agt/system/robot_state/get \
  agt_interfaces/srv/GetRobotState "{include_details: true}"
```

With no upstream runtime producers started, the expected state is **BLOCKED**, with unknown/missing evidence
reported explicitly. It must never start as READY by default.

## Deferred next convergence slice

P0 deliberately does not implement:

1. production Site Package / map activation owner for `/agt/maps/active`;
2. stable unified BUNKER bringup based on `agt_odometry`;
3. Nav2 lifecycle aggregation into the read model;
4. LIO/wheel/GNSS fusion;
5. traversability algorithm upgrades;
6. operator Gateway/HMI command transport.

The next recommended slice is the Site/Map runtime owner followed by stable BUNKER unified bringup. Only after
those providers are closed should the real operator Gateway be connected to `RobotState`/`TaskReadiness`.
