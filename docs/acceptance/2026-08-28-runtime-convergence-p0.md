# Runtime Convergence P0 Acceptance — 2026-08-28

## Status

```text
Selected stable baseline: PASS
Safety producer/consumer contract: PASS (cloud regression + ROS fixture guard)
Pure readiness policy: PASS (cloud regression)
System-manager source/read-model contract: PASS (cloud regression)
Final cloud Runtime Contracts: PASS at 3abe8a9
Local ROS 2 Humble full build: PASS on verification attempt #1 (26 packages)
Local clean-Git-worktree build: PENDING (attempt #1 carried pre-existing local M/D changes)
Local ROS package tests: RERUN REQUIRED after fixture fix
System-manager launch --show-args: PASS
System-manager no-motion runtime smoke: PENDING
Overall P0 acceptance: PENDING LOCAL RERUN + RUNTIME SMOKE
```

This record intentionally distinguishes cloud/source evidence, a successful local build, and the remaining
runtime acceptance gates. It also does not treat deletion of build/install/log as proof of a clean Git source
workspace.

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

The waypoint task server and ROUTE runtime-gate test fixture now consume/construct that same production
status identity. The legacy `agt_safety/tracked_controller` identity is forbidden by the cloud execution
contract guard.

Initial RED evidence:

- GitHub Actions run `33144895532` (`Runtime Contracts` run #175)
- V3-01 contracts: PASS
- V3-02 odometry contracts: PASS
- V3-03 execution contracts: FAIL on the new cross-package assertion

Initial GREEN evidence:

- run #176 at `1bf0284ab8bb5263a84800391dfe16d4218d4332`: PASS
- run #177 at `772efbe85070da2786b0ff1b9e0915d84d96eb8d`: PASS

Local ROS verification exposed one missed fixture in
`src/agt_navigation/test/test_navigation_capability_runtime_gates.py`. The fixture still emitted the legacy
status name, so a safety-required ROUTE harness failed closed before its child FollowPath action started.
Because construction failed before normal teardown, the remaining parameterized cases observed leftover action
servers and produced cascading duplicate-goal / wrong-blocker symptoms.

Regression strengthening evidence:

- run #192 at `b70bf5228bd418cbd96aebcb70c7f41130c66304`: RED by design; V3-03 execution contracts reject the stale ROUTE fixture
- commit `3abe8a9fe0b9cd7259e939e65e1ac624f8ff34b4`: fixture aligned to `agt_safety/controller`
- run #193: PASS for V3-01, V3-02, V3-03 and system-manager cloud stages

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
- run #193 at `3abe8a9fe0b9cd7259e939e65e1ac624f8ff34b4`: PASS after strengthening the Safety fixture contract

Run #193 passed all cloud-capable workflow stages:

```text
V3-01 contract tests                 PASS
V3-02 odometry source contracts      PASS
V3-03 execution source contracts     PASS
runtime system-manager contracts     PASS
```

## Local ROS 2 Humble verification attempt #1

Observed on the target Ubuntu/ROS2 workstation after deleting `build/`, `install/`, and `log/`:

```text
colcon build --symlink-install
Summary: 26 packages finished
```

No package build failed. Third-party/dependency stderr consisted of existing warnings such as PCL CMake policy
and optional pcap/png feature warnings.

The source Git worktree was not clean when the convergence branch was selected. Pre-existing modified/deleted
paths were present under `agt_bt_executor`, `agt_localization`, `agt_navigation`, and `agt_sensor_monitor`.
Therefore attempt #1 proves a full fresh build-artifact rebuild, but not a clean-source-tree reproduction.
Those local changes must be preserved rather than reset blindly.

Selected package test results before the fixture remediation:

```text
agt_system_manager: PASS (1/1 CTest; readiness core passed)
agt_safety:         PASS (1/1 CTest; 4 pytest cases passed)
agt_navigation:     FAIL (13/14 CTest programs passed)
```

The single failing CTest program was:

```text
test_navigation_capability_runtime_gates
```

Inside that pytest file, three of five parameterized/runtime-gate cases failed. Root cause was the stale legacy
Safety fixture described above, not a system-manager build or launch failure. The remote branch now contains the
fixture fix at `3abe8a9fe0b9cd7259e939e65e1ac624f8ff34b4`, but the local ROS test suite must be rerun before the package
test gate is promoted to PASS.

The following launch argument check succeeded during attempt #1:

```bash
ros2 launch agt_system_manager system_manager.launch.py --show-args
```

Resolved arguments included `system_manager_config` and `use_sim_time`; no package/import/config resolution
error was reported.

## Required local ROS 2 Humble rerun gate

First preserve and inspect the pre-existing local source changes. Do not run `git reset --hard` or `git clean`.

```bash
cd ~/agt_navigation_runtime
git status --short
git diff > ~/agt_navigation_runtime_pre_convergence_worktree.patch

git fetch origin
git pull --ff-only origin feat/runtime-convergence-p0
source /opt/ros/humble/setup.bash
source install/setup.bash
```

Run the previously failing test first:

```bash
colcon test \
  --packages-select agt_navigation \
  --ctest-args -R test_navigation_capability_runtime_gates --output-on-failure
colcon test-result --verbose
```

If that passes, rerun the complete selected P0 package gate:

```bash
colcon test \
  --packages-select agt_system_manager agt_navigation agt_safety \
  --event-handlers console_direct+
colcon test-result --verbose
```

Expected gate:

```text
agt_system_manager / agt_navigation / agt_safety tests: zero failures
```

A separate clean-source-tree reproduction can be performed later from a fresh clone/worktree after the current
local modifications have been safely preserved.

Then perform the no-motion startup smoke:

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
