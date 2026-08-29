# Inspection MVP Convergence Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Converge the existing Runtime navigation, inspection and camera-gimbal capabilities into one vehicle-deployable inspection MVP whose success gate is navigation + stable capture + observation-time pose evidence, with litchi-flower inference deferred by default.

**Architecture:** Keep `feat/runtime-navigation-convergence-p1` authority boundaries intact. Selectively port inspection-specific code from `feat/inspection-multiview-evidence`, import the frozen Autolabor C1 camera-gimbal vendor package, add a thin Runtime adapter to `/camera_gimbal/acquire_view`, and extend inspection schema/execution with an explicit `DEFERRED` vision mode. Do not merge divergent mapping/navigation/bringup code from historical branches.

**Tech Stack:** Ubuntu 22.04, ROS 2 Humble, Python 3.10, rclpy, ROS 2 Actions/Services, pytest, Nav2, FAST-LIVO2 Runtime contracts.

**Spec:** `docs/superpowers/specs/2026-08-30-inspection-mvp-convergence-design.md`

## Global Constraints

- Product base remains `feat/runtime-navigation-convergence-p1`; implementation occurs only on `feat/inspection-mvp-convergence`.
- No new publisher may own `map -> odom`, `odom -> base_footprint`, or `/cmd_vel`.
- `agt_inspection` must call the formal waypoint task capability, never Nav2 directly.
- Camera/gimbal serial protocol remains vendor-owned; Runtime receives one atomic view acquisition capability.
- Missing `vision.execution_mode` remains backward-compatible `INLINE`.
- First field assets explicitly use `DEFERRED`; deferred inference never fabricates flower counts.
- Authoritative evidence stores actual observation-time robot pose and actual gimbal feedback, not requested target values.
- Generic navigation missions must remain runnable without inspection hardware.
- Runtime map production/editing and HMI authoring are outside this plan.

---

### Task 1: Selectively port inspection package and interfaces

**Files:**
- Create: `src/agt_inspection/**` from the inspection source branch, excluding mock/model assumptions that conflict with this plan only after tests expose the conflict.
- Modify: `src/agt_interfaces/CMakeLists.txt`
- Modify: `src/agt_interfaces/package.xml`
- Create: `src/agt_interfaces/action/ExecuteInspectionTask.action`
- Create: `src/agt_interfaces/action/InspectImage.action`
- Create: `src/agt_interfaces/action/MoveGimbal.action`
- Create: `src/agt_interfaces/action/AggregateInspectionViews.action`
- Create: `src/agt_interfaces/msg/InspectionStatus.msg`
- Create: `src/agt_interfaces/msg/InspectionViewObservation.msg`
- Create: `src/agt_interfaces/srv/CaptureImage.srv`

**Interfaces:**
- Consumes: existing `ExecuteWaypointTask` and localization/runtime interfaces from convergence P1.
- Produces: `/agt/inspection/execute_task` plus inspection schema/evidence primitives used by later tasks.

- [ ] **Step 1: Add source-guard tests before production files**

Create `tests/inspection/test_inspection_selective_port_contract.py` asserting that inspection integration does not reintroduce historical mapping/navigation ownership and that the required inspection interface files exist.

- [ ] **Step 2: Run RED**

Run:

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q tests/inspection/test_inspection_selective_port_contract.py
```

Expected: FAIL because the inspection package/interfaces do not yet exist on the convergence branch.

- [ ] **Step 3: Selectively port the inspection package and interface definitions**

Copy inspection-owned files only. Do not copy `agt_mapping`, `agt_navigation`, `agt_bringup`, platform profiles, localization or sensor files from the historical branch.

- [ ] **Step 4: Run GREEN and compile Python**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q tests/inspection/test_inspection_selective_port_contract.py
python -m compileall -q src/agt_inspection
```

- [ ] **Step 5: Commit**

```bash
git add src/agt_inspection src/agt_interfaces tests/inspection/test_inspection_selective_port_contract.py
git commit -m "feat(inspection): selectively port runtime inspection capability"
```

---

### Task 2: Add explicit deferred vision schema and execution semantics

**Files:**
- Modify: `src/agt_inspection/agt_inspection/schema.py`
- Modify: `src/agt_inspection/agt_inspection/model.py`
- Modify: `src/agt_inspection/agt_inspection/multiview_execution.py`
- Modify: `src/agt_inspection/agt_inspection/multiview_evidence.py`
- Modify: `src/agt_inspection/scripts/inspection_task_server.py`
- Test: `src/agt_inspection/test/test_schema_v2.py`
- Test: `src/agt_inspection/test/test_multiview_execution.py`
- Create: `src/agt_inspection/test/test_deferred_vision.py`

**Interfaces:**
- Consumes: parsed inspection task schema.
- Produces: `vision.execution_mode` with values `INLINE` and `DEFERRED`; deferred observations use `vision_status=PENDING_OFFLINE` and no online inference result.

- [ ] **Step 1: Write failing schema tests**

Add tests requiring:

```python
assert parse_task(task_without_mode).vision.execution_mode == "INLINE"
assert parse_task(task_with_deferred).vision.execution_mode == "DEFERRED"
```

Reject any other value.

- [ ] **Step 2: Run RED**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q \
  src/agt_inspection/test/test_schema_v2.py \
  src/agt_inspection/test/test_deferred_vision.py
```

Expected: FAIL because `execution_mode` is not implemented.

- [ ] **Step 3: Implement minimal schema support**

Add the enum-like validation with parser default `INLINE`; do not change existing INLINE behavior.

- [ ] **Step 4: Write failing deferred execution tests**

Test a valid DEFERRED point with a fake acquisition backend and an inference callable that raises if invoked. Assert:

```python
assert result.success is True
assert inference_calls == 0
assert observation["vision_status"] == "PENDING_OFFLINE"
assert "raw_count" not in observation
```

- [ ] **Step 5: Run RED, implement minimal deferred branch, run GREEN**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q \
  src/agt_inspection/test/test_schema_v2.py \
  src/agt_inspection/test/test_multiview_execution.py \
  src/agt_inspection/test/test_deferred_vision.py
```

- [ ] **Step 6: Run inspection regression set**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q src/agt_inspection/test
```

- [ ] **Step 7: Commit**

```bash
git add src/agt_inspection
git commit -m "feat(inspection): support deferred offline vision mode"
```

---

### Task 3: Import frozen camera-gimbal capability and add Runtime adapter

**Files:**
- Create: `third_party/autolabor_c1_camera_gimbal/**` from `feat/camera-gimbal-driver-import`
- Create: `src/agt_inspection/agt_inspection/camera_gimbal_adapter.py`
- Create: `src/agt_inspection/test/test_camera_gimbal_adapter.py`
- Modify: `src/agt_inspection/package.xml`

**Interfaces:**
- Consumes: `/camera_gimbal/acquire_view` (`camera_gimbal_interfaces/action/AcquireView`) and `/camera_gimbal/health`.
- Produces: an inspection-facing acquisition result containing success/error category, `image_uri`, `image_stamp`, `reached_stamp`, and actual gimbal feedback.

- [ ] **Step 1: Write failing pure adapter tests**

Cover radians-to-degrees conversion, deterministic vendor error-code mapping, cancellation mapping, and rejection of request-angle substitution when actual feedback is unavailable/stale.

- [ ] **Step 2: Run RED**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q src/agt_inspection/test/test_camera_gimbal_adapter.py
```

- [ ] **Step 3: Import the frozen vendor tree without modifications**

The import must retain `CAPABILITY_INTERFACE.md`, `README.md`, `camera_gimbal_interfaces`, `camera_gimbal_capability`, serial driver, bringup and acceptance tools.

- [ ] **Step 4: Implement minimal adapter core**

Keep ROS-independent conversion/error mapping in pure functions. ROS action-client wiring may wrap those functions but must not leak vendor types into Mission Manager.

- [ ] **Step 5: Run GREEN plus vendor source guard**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q \
  src/agt_inspection/test/test_camera_gimbal_adapter.py \
  tests/inspection/test_inspection_selective_port_contract.py
python -m compileall -q src/agt_inspection third_party/autolabor_c1_camera_gimbal/src/camera_gimbal_capability
```

- [ ] **Step 6: Commit**

```bash
git add third_party/autolabor_c1_camera_gimbal src/agt_inspection
git commit -m "feat(inspection): bind frozen camera gimbal acquisition capability"
```

---

### Task 4: Port Mission inspection step and report integration onto the convergence Mission Manager

**Files:**
- Modify: `src/agt_mission_manager/agt_mission_manager/mission_model.py`
- Modify: `src/agt_mission_manager/agt_mission_manager/mission_schema.py`
- Modify: `src/agt_mission_manager/agt_mission_manager/mission_executor.py`
- Modify: `src/agt_mission_manager/scripts/mission_manager_node.py`
- Create/modify: `src/agt_mission_manager/agt_mission_manager/mission_report.py`
- Modify: `src/agt_mission_manager/CMakeLists.txt`
- Modify: `src/agt_mission_manager/package.xml`
- Test: inspection/RETURN_HOME tests under `src/agt_mission_manager/test/`

**Interfaces:**
- Consumes: `/agt/inspection/execute_task` and the existing formal waypoint capability for RETURN_HOME.
- Produces: sequential Mission support for `INSPECTION_TASK` followed optionally by `RETURN_HOME`, with report links to inspection evidence.

- [ ] **Step 1: Add/port failing Mission tests first**

Require that `INSPECTION_TASK` is accepted by schema, invokes the inspection action exactly through its capability boundary, and that `RETURN_HOME` remains last-only.

- [ ] **Step 2: Run RED**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q \
  src/agt_mission_manager/test/test_inspection_mission_step.py \
  src/agt_mission_manager/test/test_inspection_mission_executor.py \
  src/agt_mission_manager/test/test_return_home_mission.py
```

- [ ] **Step 3: Selectively port only Mission inspection/report behavior**

Preserve convergence branch navigation/task/site changes. Do not replace current Mission Manager wholesale with the historical file versions.

- [ ] **Step 4: Run GREEN and Mission regression set**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q src/agt_mission_manager/test
python -m compileall -q src/agt_mission_manager
```

- [ ] **Step 5: Commit**

```bash
git add src/agt_mission_manager
git commit -m "feat(mission): integrate inspection evidence mission step"
```

---

### Task 5: Add opt-in inspection bringup and task-specific readiness

**Files:**
- Modify: Runtime composition package appropriate to current convergence branch (`agt_hardware_bringup`/top-level launch only; do not resurrect historical `agt_bringup` ownership).
- Create: inspection launch/config owned by the current Runtime composition boundary.
- Modify: system/readiness aggregation only where task-specific inspection readiness is required.
- Create: tests under `tests/inspection/` and/or current package tests.

**Interfaces:**
- Consumes: camera-gimbal health and inspection action server availability.
- Produces: explicit `start_inspection=false` default and a launch path that starts inspection hardware only when requested.

- [ ] **Step 1: Write failing launch/readiness source-contract tests**

Assert generic navigation startup contains no unconditional camera-gimbal process and that inspection mode has finite, explicit device/config arguments.

- [ ] **Step 2: Run RED**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q tests/inspection
```

- [ ] **Step 3: Implement minimal opt-in composition**

Use stable by-id paths when supplied; retain `/dev/video0` and `/dev/ttyUSB0` only as development defaults in vendor code, not as field-machine authority.

- [ ] **Step 4: Run GREEN and current Runtime contract regressions**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q \
  tests/inspection \
  tests/contracts \
  tests/navigation \
  tests/system_manager
```

- [ ] **Step 5: Commit**

```bash
git add src tests/inspection
git commit -m "feat(bringup): add opt in inspection hardware composition"
```

---

### Task 6: Freeze hardware-free and vehicle acceptance procedure

**Files:**
- Create: `docs/acceptance/2026-08-30-inspection-mvp-humble-acceptance.md`
- Create: `docs/acceptance/2026-08-30-inspection-mvp-field-acceptance.md`
- Create: `docs/runbooks/inspection-mvp-field.md`
- Modify: `docs/convergence/runtime-navigation-convergence-p1.md` only after implementation evidence is available, marking P1-10 code/static status accurately and leaving HUMBLE/FIELD unchecked until actually run.

**Interfaces:**
- Produces: copy/paste acceptance commands and evidence paths for ROS 2 Humble, camera-gimbal bench and 3-point field mission.

- [ ] **Step 1: Add documentation contract test**

Require the runbook to contain the three-point mission, deferred-vision requirement, camera health gate, localization TRACKING gate, and evidence validation fields.

- [ ] **Step 2: Run RED, write docs, run GREEN**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q tests/inspection/test_inspection_runbook_contract.py
```

- [ ] **Step 3: Run full static verification available in this environment**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q \
  tests/inspection \
  src/agt_inspection/test \
  src/agt_mission_manager/test \
  tests/contracts \
  tests/navigation \
  tests/system_manager
python -m compileall -q src/agt_inspection src/agt_mission_manager
```

- [ ] **Step 4: Record unresolved machine-side gates without claiming pass**

The document must leave ROS 2 Humble build/test, physical camera-gimbal bench and real BUNKER field acceptance unchecked until those commands are executed on the target machine.

- [ ] **Step 5: Commit**

```bash
git add docs tests/inspection
git commit -m "docs: freeze inspection mvp acceptance workflow"
```
