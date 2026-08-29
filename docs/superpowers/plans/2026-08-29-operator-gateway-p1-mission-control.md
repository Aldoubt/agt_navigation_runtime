# Operator Gateway P1 Mission Control Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add authenticated and idempotent Mission start/pause/resume/cancel HTTP transport while keeping Mission Manager as the execution authority.

**Architecture:** Extend the P0 Gateway with a pure authentication/idempotency layer, inject a Mission command port into aiohttp, and implement that port as a thin ROS Action/Service adapter. Cancel uses the standard action cancel service instead of a retained goal handle so Gateway restart does not remove cancellation capability.

**Tech Stack:** Python 3.10, aiohttp, ROS 2 Humble/rclpy, `agt_interfaces`, `action_msgs`, pytest.

**Spec:** `docs/superpowers/specs/2026-08-29-operator-gateway-p1-mission-control-design.md`

## Global Constraints

- Base branch: `feat/operator-gateway-p0`.
- No Nav2/chassis/cmd_vel access from P1 Gateway.
- No new `agt_interfaces` definitions.
- Write API disabled by default.
- Write API requires `AGT_OPERATOR_COMMAND_TOKEN`.
- Every POST command requires `clientRequestId`.
- All ROS waits use finite timeouts.
- Cancellation must remain possible after Gateway restart.
- No-ROS CI is required now; ROS 2 Humble integration remains explicitly deferred.

---

### Task 1: Authentication and idempotency primitives

**Files:**
- Create: `src/agt_operator_gateway/agt_operator_gateway/command_guard.py`
- Test: `src/agt_operator_gateway/test/test_command_guard.py`

**Interfaces:**
- Produces: `verify_bearer_token(header: str | None, expected_token: str) -> bool`.
- Produces: `CommandReplayStore.begin(request_id, fingerprint)` and `.complete(...)`.

- [ ] Write failing tests for valid/invalid/missing bearer tokens and constant API behavior.
- [ ] Write failing tests for NEW, IN_PROGRESS, replay and conflicting request IDs.
- [ ] Run the focused tests and verify RED.
- [ ] Implement the minimal pure-Python guard/store.
- [ ] Run focused tests and verify GREEN.

### Task 2: Mission command HTTP contract

**Files:**
- Create: `src/agt_operator_gateway/agt_operator_gateway/mission_commands.py`
- Create: `src/agt_operator_gateway/test/test_mission_command_http.py`
- Modify: `src/agt_operator_gateway/agt_operator_gateway/server.py`

**Interfaces:**
- Consumes: injected command port with `start/pause/resume/cancel` synchronous methods.
- Produces: four authenticated POST endpoints under `/api/v1/mission/*`.

- [ ] Write fake-port tests for request validation, authentication and HTTP status mapping.
- [ ] Add tests that repeated identical request IDs never invoke the fake port twice.
- [ ] Add tests for CORS OPTIONS with Authorization/Content-Type.
- [ ] Run tests and verify RED.
- [ ] Add command request parsing/result dataclasses and server handlers.
- [ ] Run focused and existing P0 server/CORS tests and verify GREEN.

### Task 3: ROS Mission command adapter

**Files:**
- Create: `src/agt_operator_gateway/agt_operator_gateway/mission_ros_adapter.py`
- Create: `src/agt_operator_gateway/test/test_mission_ros_contract.py`
- Modify: `src/agt_operator_gateway/scripts/operator_gateway_node.py`
- Modify: `src/agt_operator_gateway/package.xml`
- Modify: `src/agt_operator_gateway/config/operator_gateway.yaml`

**Interfaces:**
- START: `/agt/missions/execute` + `ExecuteMission`.
- PAUSE/RESUME: `/agt/missions/set_run_state` + `SetMissionRunState`.
- CANCEL: `/agt/missions/execute/_action/cancel_goal` + `action_msgs/srv/CancelGoal` using zero GoalInfo.

- [ ] Write static failing tests for exact ROS endpoints/types and absence of Nav2/chassis references.
- [ ] Write static failing test pinning Mission Manager single-active-goal rejection.
- [ ] Verify RED.
- [ ] Implement finite-timeout ROS adapter and node wiring.
- [ ] Add `action_msgs` dependency and disabled-by-default write config.
- [ ] Verify static tests GREEN.

### Task 4: Field/preflight command checks

**Files:**
- Modify: `src/agt_operator_gateway/scripts/operator_gateway_preflight.py`
- Modify: `src/agt_operator_gateway/agt_operator_gateway/preflight.py`
- Create/modify: `src/agt_operator_gateway/test/test_preflight.py`
- Create: `docs/acceptance/2026-08-29-operator-gateway-p1-mission-control-field-acceptance.md`

**Interfaces:**
- Preflight remains read-only by default.
- `--check-write-api` verifies auth rejection/availability without dispatching a Mission.

- [ ] Add tests that default preflight never sends a POST.
- [ ] Add authenticated write-availability probe that cannot start/pause/resume/cancel a mission.
- [ ] Freeze later ROS/hardware acceptance commands and evidence paths.
- [ ] Verify no-ROS tests GREEN.

### Task 5: CI and branch isolation

**Files:**
- Modify: `.github/workflows/operator-gateway-p0.yml`
- Modify: `src/agt_operator_gateway/CMakeLists.txt`

- [ ] Extend branch trigger to P1 and run all P0+P1 no-ROS tests.
- [ ] Add new tests to ament test registration.
- [ ] Run GitHub Actions and require all test/compile steps GREEN.
- [ ] Compare P1 against P0 and verify changes are limited to Gateway/docs/isolated CI.

### Task 6: HMI command transport (separate stacked HMI branch)

**Files:**
- Create branch from `feat/p4-gateway-p0-integration`.
- Add runtime mission command client and tests.
- Keep UI command controls disabled until a command token is explicitly supplied.

- [ ] Add typed POST request/response parser.
- [ ] Add bearer token injection without embedding a token in the build.
- [ ] Add start/pause/resume/cancel client methods.
- [ ] Verify existing Mock Gateway, unit tests and production build remain GREEN.
- [ ] Defer actual command-button vehicle acceptance until ROS 2/vehicle environment exists.
