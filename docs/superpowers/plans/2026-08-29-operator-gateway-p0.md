# Operator Gateway P0 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a read-only HTTP/WebSocket gateway that projects the authoritative `agt_system_manager` RobotState into the existing `agt_operator_hmi` gateway v1 contract.

**Architecture:** `agt_system_manager` remains the only runtime read-model authority. A new additive `agt_operator_gateway` ROS 2 package subscribes to `/agt/system/robot_state`, performs a conservative pure-data projection, and serves the HMI over aiohttp. No existing runtime package or interface is modified in P0.

**Tech Stack:** ROS 2 Humble, rclpy, agt_interfaces, aiohttp, ament_cmake_python, pytest.

**Spec:** `docs/superpowers/specs/2026-08-29-operator-gateway-p0-design.md`

## Global Constraints

- Base branch: `feat/runtime-convergence-p0`.
- Additive changes only under `src/agt_operator_gateway/` plus gateway docs.
- No changes to `agt_interfaces` in P0.
- No mission/motion/map write endpoints in P0.
- API version: `agt.operator.gateway/v1`.
- stream schema: `agt.operator.stream/v1`.
- Primary runtime source: `/agt/system/robot_state`.
- Missing/stale evidence must never be represented as healthy or ready.

---

### Task 1: Pure HMI projection contract

**Files:**
- Create: `src/agt_operator_gateway/agt_operator_gateway/contract.py`
- Test: `src/agt_operator_gateway/test/test_contract.py`

**Interfaces:**
- Consumes: RobotState-like Python objects with the fields defined in `agt_interfaces/RobotState`.
- Produces: `build_robot_snapshot(state, robot_id, robot_name)`, `build_navigation_view(state)`, `build_mission_view(state)`, `build_capabilities()`.

- [ ] **Step 1: Write failing tests**

Cover READY/BLOCKED projection, accepted localization pose/yaw, unknown localization, active map identity, mission RUNNING/PAUSED/terminal mapping, and the `__none__` mission sentinel.

- [ ] **Step 2: Run RED test**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q src/agt_operator_gateway/test/test_contract.py
```

Expected: import failure because `agt_operator_gateway.contract` does not exist.

- [ ] **Step 3: Implement minimal projection**

Use only attribute access and standard-library math/time helpers. Do not import rclpy in `contract.py` so the projection is unit-testable without ROS.

- [ ] **Step 4: Run GREEN test**

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q src/agt_operator_gateway/test/test_contract.py
```

Expected: all projection tests pass.

- [ ] **Step 5: Commit**

```bash
git add src/agt_operator_gateway/agt_operator_gateway/contract.py src/agt_operator_gateway/test/test_contract.py
git commit -m "feat(gateway): add conservative hmi projection"
```

### Task 2: Thread-safe runtime state store

**Files:**
- Create: `src/agt_operator_gateway/agt_operator_gateway/state_store.py`
- Test: `src/agt_operator_gateway/test/test_state_store.py`

**Interfaces:**
- Produces: `GatewayStateStore.update(...)`, `snapshot()`, `is_runtime_connected(now_ms)`, and monotonically increasing revisions.

- [ ] **Step 1: Write failing tests** for empty state, update/revision, copy isolation, and freshness expiry.
- [ ] **Step 2: Run RED test** with pytest.
- [ ] **Step 3: Implement using `threading.RLock`**; default freshness is 1500 ms.
- [ ] **Step 4: Run GREEN test**.
- [ ] **Step 5: Commit** with `feat(gateway): add runtime snapshot store`.

### Task 3: HTTP/WebSocket transport

**Files:**
- Create: `src/agt_operator_gateway/agt_operator_gateway/server.py`
- Test: `src/agt_operator_gateway/test/test_server_contract.py`

**Interfaces:**
- Consumes: `GatewayStateStore`.
- Produces: aiohttp application routes `/api/v1/health`, `/capabilities`, `/robot`, `/mission`, `/stream`.

- [ ] **Step 1: Write failing transport tests** using aiohttp test utilities.
- [ ] **Step 2: Run RED test**.
- [ ] **Step 3: Implement endpoints**. `/robot` and `/mission` return 503 before first valid runtime state. WebSocket emits only when a new runtime revision is available; do not emit fake freshness heartbeats.
- [ ] **Step 4: Run GREEN test**.
- [ ] **Step 5: Commit** with `feat(gateway): serve readonly gateway v1`.

### Task 4: ROS adapter and package integration

**Files:**
- Create: `src/agt_operator_gateway/agt_operator_gateway/ros_adapter.py`
- Create: `src/agt_operator_gateway/scripts/operator_gateway_node.py`
- Create: `src/agt_operator_gateway/launch/operator_gateway.launch.py`
- Create: `src/agt_operator_gateway/config/operator_gateway.yaml`
- Create: `src/agt_operator_gateway/CMakeLists.txt`
- Create: `src/agt_operator_gateway/package.xml`
- Create: `src/agt_operator_gateway/README.md`
- Test: `src/agt_operator_gateway/test/test_ros_contract.py`

**Interfaces:**
- Subscription default: `/agt/system/robot_state` (`agt_interfaces/RobotState`) using reliable transient-local QoS.
- Parameters: `host`, `port`, `robot_id`, `robot_name`, `robot_state_topic`, `runtime_freshness_ms`.

- [ ] **Step 1: Write static/contract tests** verifying topic name, no publisher/action/client for command interfaces, package dependencies, and launch parameters.
- [ ] **Step 2: Run RED test**.
- [ ] **Step 3: Implement adapter/node/package**. ROS executor stays on the main thread; aiohttp runs in a dedicated thread/event loop and reads only from `GatewayStateStore`.
- [ ] **Step 4: Build/test**:

```bash
colcon build --packages-select agt_interfaces agt_system_manager agt_operator_gateway --symlink-install
source install/setup.bash
colcon test --packages-select agt_operator_gateway
colcon test-result --verbose
```

- [ ] **Step 5: Commit** with `feat(gateway): integrate robot state transport`.

### Task 5: Hardware-free smoke acceptance

**Files:**
- Create: `src/agt_operator_gateway/scripts/mock_robot_state_publisher.py`
- Create: `src/agt_operator_gateway/launch/operator_gateway_mock.launch.py`
- Test: `src/agt_operator_gateway/test/test_mock_gateway_contract.py`

**Interfaces:**
- Mock publishes only `/agt/system/robot_state`; gateway must behave identically to real system-manager input.

- [ ] **Step 1: Write failing smoke contract test**.
- [ ] **Step 2: Implement mock publisher/launch**.
- [ ] **Step 3: Start mock stack**:

```bash
ros2 launch agt_operator_gateway operator_gateway_mock.launch.py
```

- [ ] **Step 4: Verify endpoints**:

```bash
curl -fsS http://127.0.0.1:8765/api/v1/health
curl -fsS http://127.0.0.1:8765/api/v1/capabilities
curl -fsS http://127.0.0.1:8765/api/v1/robot
curl -fsS http://127.0.0.1:8765/api/v1/mission
```

Expected: gateway v1 payloads hydrate successfully, runtime reports connected, and stopping the mock publisher allows freshness to expire.

- [ ] **Step 5: Commit** with `test(gateway): add hardware free acceptance`.

### Task 6: Upstream-convergence check before merge

**Files:**
- Modify only if required by upstream changes: gateway package/docs.

- [ ] **Step 1:** compare `feat/operator-gateway-p0` against the then-current runtime integration branch.
- [ ] **Step 2:** rebase or merge that integration branch into the gateway branch; resolve only genuine contract changes.
- [ ] **Step 3:** rerun gateway package tests and runtime contract CI.
- [ ] **Step 4:** verify no P0 changes leaked into navigation/chassis/safety/localization/mission execution.
- [ ] **Step 5:** merge only after the additive diff is clean and reviewable.
