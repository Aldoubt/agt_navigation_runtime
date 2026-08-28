# Runtime Convergence P0 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Close the first two product-integration blockers on the accepted V3 runtime baseline: the safety diagnostic contract mismatch and the missing authoritative system-state/readiness owner.

**Architecture:** Keep all runtime business decisions inside ROS-side runtime packages. `agt_system_manager` owns authoritative `SystemHealth`, `TaskReadiness`, and `RobotState`; the future operator gateway is only a transport/translation layer. Readiness policy is implemented in a ROS-independent Python core and mapped to ROS messages by a thin node.

**Tech Stack:** ROS 2 Humble, Python 3.10, rclpy, `agt_interfaces`, pytest, GitHub Actions.

**Spec:** `docs/audits/2026-08-28-runtime-baseline-audit.md`

## Global Constraints

- Branch from accepted V3-03 baseline commit `e62261a57cc4bd16448526e31d9897a0ef48a577`.
- Do not reintroduce runtime `agt_mapping`; V3 continuous odometry remains owned by `agt_odometry`.
- Unknown or stale required evidence is fail-closed.
- The operator gateway must not own Runtime readiness/business policy.
- Do not weaken existing V3 contract, odometry, execution or MK-mini tests.
- Do not add Site/Map runtime activation or unified bringup in this P0 slice.

---

### Task 1: Enable convergence-branch CI

**Files:**
- Modify: `.github/workflows/runtime-contracts.yml`

**Interfaces:**
- Consumes: existing Runtime Contracts workflow.
- Produces: CI coverage for `feat/runtime-convergence-*` and `tests/system_manager`.

- [ ] **Step 1: Add the convergence branch pattern and system-manager test command**

Add `feat/runtime-convergence-*` to push branches, add `src/agt_system_manager/**` and `tests/system_manager/**` to pull-request paths, and add:

```bash
python -m pytest -q tests/system_manager
```

- [ ] **Step 2: Commit infrastructure change**

```bash
git add .github/workflows/runtime-contracts.yml
git commit -m "ci(runtime): cover convergence system manager"
```

### Task 2: Fix the safety producer/consumer contract with a RED regression

**Files:**
- Create: `tests/execution/test_safety_status_contract.py`
- Modify: `src/agt_navigation/scripts/waypoint_task_server.py`
- Modify: `src/agt_navigation/test/test_waypoint_task_server.py`

**Interfaces:**
- Consumes: `/agt/safety/status` DiagnosticArray.
- Produces: canonical `DiagnosticStatus.name == "agt_safety/controller"` contract shared by producer and waypoint consumer.

- [ ] **Step 1: Write the failing cross-package test**

```python
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def test_waypoint_consumer_matches_generic_safety_status_name():
    safety = (ROOT / "src/agt_safety/scripts/safety_controller.py").read_text()
    waypoint = (ROOT / "src/agt_navigation/scripts/waypoint_task_server.py").read_text()
    assert 'status.name = "agt_safety/controller"' in safety
    assert 'status.name != "agt_safety/controller"' in waypoint
    assert "agt_safety/tracked_controller" not in waypoint
```

- [ ] **Step 2: Run RED**

Run:

```bash
python -m pytest -q tests/execution/test_safety_status_contract.py
```

Expected: FAIL because the waypoint consumer still checks `agt_safety/tracked_controller`.

- [ ] **Step 3: Implement the minimal fix**

Change the waypoint server to consume `agt_safety/controller` and update the ROS package unit fixture to publish the production status name.

- [ ] **Step 4: Run GREEN**

```bash
python -m pytest -q tests/execution/test_safety_status_contract.py tests/execution
```

Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git add tests/execution/test_safety_status_contract.py src/agt_navigation/scripts/waypoint_task_server.py src/agt_navigation/test/test_waypoint_task_server.py
git commit -m "fix(runtime): align waypoint safety status contract"
```

### Task 3: Add the ROS-independent readiness core with TDD

**Files:**
- Create: `src/agt_system_manager/agt_system_manager/__init__.py`
- Create: `src/agt_system_manager/agt_system_manager/readiness.py`
- Create: `tests/system_manager/test_readiness.py`

**Interfaces:**
- Produces:
  - `Evidence` immutable dataclass.
  - `ReadinessResult` immutable dataclass.
  - `evaluate_navigation_readiness(evidence: Evidence) -> ReadinessResult`.
  - `overall_health_state(components: tuple[ComponentEvidence, ...]) -> int`.

Required `Evidence` fields:

```python
health_known: bool
health_ok: bool
map_known: bool
map_ready: bool
map_id: str
map_version_id: str
localization_known: bool
localization_tracking: bool
localization_map_id: str
safety_known: bool
motion_enabled: bool
estop_latched: bool
chassis_known: bool
chassis_connected: bool
```

Required blocker codes:

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

- [ ] **Step 1: Write failing readiness tests**

Cover all-ready success and at least unknown health, missing map, localization/map mismatch, disabled motion, latched estop, and disconnected chassis.

- [ ] **Step 2: Run RED**

```bash
python -m pytest -q tests/system_manager/test_readiness.py
```

Expected: import/module failure because `agt_system_manager.readiness` does not exist.

- [ ] **Step 3: Implement minimal pure core**

Implement immutable dataclasses and deterministic blocker ordering. `ready` is true only when blocker list is empty.

- [ ] **Step 4: Run GREEN**

```bash
PYTHONPATH=src/agt_system_manager python -m pytest -q tests/system_manager/test_readiness.py
```

Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git add src/agt_system_manager/agt_system_manager tests/system_manager
git commit -m "feat(system): add fail-closed readiness core"
```

### Task 4: Add the authoritative ROS system manager

**Files:**
- Create: `src/agt_system_manager/CMakeLists.txt`
- Create: `src/agt_system_manager/package.xml`
- Create: `src/agt_system_manager/config/system_manager.yaml`
- Create: `src/agt_system_manager/launch/system_manager.launch.py`
- Create: `src/agt_system_manager/scripts/system_manager_node.py`
- Create: `tests/system_manager/test_system_manager_source_contract.py`

**Interfaces:**
- Consumes:
  - `/diagnostics`
  - `/agt/maps/active`
  - `/agt/localization/status`
  - `/agt/missions/status`
  - `/agt/safety/status`
  - `/agt/chassis/status`
  - `/agt/chassis/connected`
  - `/agt/data/bags/status`
- Publishes:
  - `/agt/system/health` (`agt_interfaces/SystemHealth`, transient-local)
  - `/agt/system/task_readiness` (`agt_interfaces/TaskReadiness`, transient-local)
  - `/agt/system/robot_state` (`agt_interfaces/RobotState`, transient-local)
- Services:
  - `/agt/system/health/get` (`GetSystemHealth`)
  - `/agt/system/task_readiness/evaluate` (`EvaluateTaskReadiness`)
  - `/agt/system/robot_state/get` (`GetRobotState`)

- [ ] **Step 1: Write the failing source-contract test**

Assert that the package, node and launch files exist, the node imports the three service types and publishes/subscribes to the exact canonical names above, and no web/gateway dependency appears in the package.

- [ ] **Step 2: Run RED**

```bash
python -m pytest -q tests/system_manager/test_system_manager_source_contract.py
```

Expected: FAIL because `src/agt_system_manager` does not yet contain a ROS package/node.

- [ ] **Step 3: Implement the minimal ROS package/node**

The node must:

- keep latest evidence with monotonic receive timestamps;
- evaluate freshness before each publication/service response;
- translate sensor/chassis diagnostics into `ComponentHealth` entries;
- publish fail-closed `SystemHealth`;
- use the pure readiness core for `TaskReadiness`;
- copy latest map/localization/mission/bag messages into `RobotState` only when fresh;
- parse the canonical `agt_safety/controller` diagnostic values for motion/estop/navigation readiness;
- keep unknown fields explicitly unknown rather than inventing healthy defaults;
- publish at 5 Hz by default.

- [ ] **Step 4: Run GREEN source/core tests**

```bash
PYTHONPATH=src/agt_system_manager python -m pytest -q tests/system_manager
```

Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git add src/agt_system_manager tests/system_manager
git commit -m "feat(system): publish authoritative runtime read model"
```

### Task 5: Final regression and acceptance record

**Files:**
- Create: `docs/acceptance/2026-08-28-runtime-convergence-p0.md`
- Modify: `docs/superpowers/plans/2026-08-28-runtime-convergence-p0.md`

**Interfaces:**
- Produces: auditable P0 acceptance evidence and explicit local ROS verification commands.

- [ ] **Step 1: Run the complete cloud-capable regression set**

```bash
PYTHONPATH=src/agt_system_manager python -m pytest -q tests/contracts tests/odometry tests/execution tests/system_manager src/agt_chassis_mk_mini_sim/test
```

- [ ] **Step 2: Record the required local ROS 2 Humble verification**

The acceptance file must require, but must not claim until actually observed:

```bash
source /opt/ros/humble/setup.bash
rm -rf build install log
colcon build --symlink-install
source install/setup.bash
colcon test --packages-select agt_system_manager agt_navigation agt_safety
colcon test-result --verbose
ros2 launch agt_system_manager system_manager.launch.py --show-args
```

- [ ] **Step 3: Wait for final GitHub Actions result on the final HEAD**

All Runtime Contracts steps must be green before cloud acceptance is claimed.

- [ ] **Step 4: Commit acceptance record and mark the plan complete**

```bash
git add docs/acceptance/2026-08-28-runtime-convergence-p0.md docs/superpowers/plans/2026-08-28-runtime-convergence-p0.md
git commit -m "docs(runtime): record convergence p0 acceptance"
```
