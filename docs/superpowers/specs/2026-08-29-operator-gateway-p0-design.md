# Operator Gateway P0 Design

## Goal

Add a robot-side read-only HTTP/WebSocket gateway that translates the authoritative `agt_system_manager` read model into the existing `agt_operator_hmi` gateway v1 contract, without becoming a second runtime authority.

## Branch / merge strategy

This work is based on `feat/runtime-convergence-p0`, not on the divergent inspection feature history. P0 changes are intentionally isolated to a new `src/agt_operator_gateway/` package, gateway-specific docs, and one gateway-only no-ROS CI workflow.

Rules:

1. Do not modify navigation, chassis, safety, localization, mission execution, or system-manager policy in P0.
2. Do not add new `agt_interfaces` messages/services in P0.
3. Consume `/agt/system/robot_state` as the primary authoritative snapshot.
4. Treat missing/stale runtime evidence as unavailable; never promote UNKNOWN to healthy/ready.
5. Keep gateway API/version names compatible with HMI P3: `agt.operator.gateway/v1` and `agt.operator.stream/v1`.
6. Rebase/merge the active convergence baseline into this branch regularly. Because P0 is additive, later migration should normally reduce to replaying the new package, docs, and isolated CI workflow.
7. Inspection write/control APIs are deferred until the runtime inspection capability is converged onto the active runtime baseline.
8. Browser-origin policy is transport configuration only; it must never change Runtime readiness or motion authority.

## Ownership

```text
agt_system_manager (authority)
  /agt/system/robot_state
            |
            v
agt_operator_gateway (transport/projection only)
            |
       HTTP / WebSocket
            |
            v
agt_operator_hmi
```

The gateway does not decide readiness, activate maps, start Nav2, issue chassis commands, or own mission state.

## P0 endpoints

- `GET /api/v1/health`
- `GET /api/v1/capabilities`
- `GET /api/v1/robot`
- `GET /api/v1/mission`
- `GET /api/v1/stream` (WebSocket)

P0 has no write endpoint.

## Runtime connection semantics

`/agt/system/robot_state` is published as a reliable transient-local snapshot at 5 Hz by `agt_system_manager`.

Gateway behavior:

- Before the first valid RobotState: robot/mission endpoints return HTTP 503.
- Fresh RobotState: runtime is connected and stream messages are emitted.
- No fresh RobotState: gateway stops emitting runtime envelopes. The existing HMI freshness logic transitions LIVE -> STALE -> OFFLINE.
- Gateway health remains queryable and exposes `runtime.connected` separately.

Default freshness limit: 1.5 s. This matches the HMI stale threshold and can be configured. Offline/stream-expiry threshold defaults to 5 s.

## Browser/LAN transport

The HMI may run on an operator laptop/tablet while the Gateway runs on the robot, so browser CORS must be handled explicitly.

P0 behavior:

- `cors_allowed_origins` is a ROS parameter consumed only by the HTTP transport.
- P0 default is `['*']` because every exposed endpoint is read-only and carries no credentials.
- `Access-Control-Allow-Credentials` is not enabled.
- deployments may replace `*` with explicit HMI origins; unexpected explicit Origins are rejected.
- before any P1 write endpoint is enabled, wildcard origin access must be replaced by explicit trusted origins and the command/authentication policy reviewed.

This policy enables ordinary browser fetch/WebSocket use over the robot LAN without exposing ROS DDS directly to the HMI.

## HMI projection

### RobotSnapshot

Source authority is `RobotState` and nested read models.

- readiness/blockers/warnings come only from `TaskReadiness`.
- active map comes only from `RobotState.active_map`.
- localization state/pose comes only from `RobotState.localization` when known and pose-valid.
- active mission comes only from `RobotState.mission` when known.
- values not represented in current RobotState (battery, IMU rate, etc.) are exposed as unknown/null-compatible conservative placeholders; their health is never reported OK.

### NavigationView

P0 exposes robot pose from accepted localization. Path, obstacle, terrain, point-cloud and map geometry layers remain empty/null until their authoritative runtime sources are explicitly integrated.

### MissionView

P0 projects current mission progress from `MissionStatus`. The current HMI contract requires a MissionView even with no active mission, so P0 uses an explicit sentinel id `__none__` with zero steps. This is a compatibility shim; HMI should later allow `mission: null`.

## Stream envelopes

On every accepted RobotState revision, emit:

1. `robot_snapshot`
2. `navigation_pose`
3. `mission_view`

Each envelope uses monotonically increasing gateway-local `seq`, ISO-8601 UTC timestamp, and schema `agt.operator.stream/v1`.

## Hardware-free and field acceptance assets

The package ships two acceptance paths that deliberately reuse the production contract:

1. `mock_robot_state_publisher.py` publishes deterministic `agt_interfaces/RobotState` on the production `/agt/system/robot_state` topic using the production reliable/transient-local QoS.
2. `operator_gateway_mock.launch.py` starts only that publisher plus the production Gateway.
3. `operator_gateway_preflight.py` checks the RobotState topic type/sample and the health/capabilities/robot/mission HTTP contract, writes `agt.operator.gateway.preflight/v1` JSON evidence, and exits non-zero on failure.

The mock publisher is an acceptance fixture only. The production Gateway contains no mock-data fallback.

## Verification split while no ROS 2 environment is available

The branch-specific `operator-gateway-p0-no-ros` GitHub Actions workflow is the immediate integration gate. It runs pure projection/state/HTTP/CORS/preflight tests, static read-only ROS boundary checks, and Python syntax compilation on Ubuntu 22.04/Python 3.10.

This no-ROS gate cannot prove:

- `colcon build` against ROS 2 Humble;
- generated `agt_interfaces` Python compatibility;
- DDS topic discovery/QoS behavior;
- real `agt_system_manager` data flow;
- LAN/browser behavior on the target robot;
- navigation or motion safety.

Those remain explicit ROS/hardware gates in `docs/acceptance/2026-08-29-operator-gateway-p0-field-acceptance.md`.

## Dependencies

- ROS 2 Humble / `rclpy`
- `agt_interfaces`
- Python `aiohttp`
- ament_cmake / ament_cmake_python

No rosbridge dependency.

## P0 acceptance

1. Pure projection tests cover readiness, localization, mission state, unknown handling and API envelopes.
2. Gateway changes remain isolated from existing Runtime execution packages.
3. No-ROS CI passes projection/store/HTTP/CORS/static/preflight checks.
4. In a ROS 2 Humble workspace, `colcon build/test` passes for `agt_interfaces`, `agt_system_manager`, and `agt_operator_gateway`.
5. With mock or real `agt_system_manager` RobotState input, HMI hydrates the four GET endpoints and receives stream envelopes.
6. Killing/stalling RobotState input causes the HMI freshness state to degrade rather than continuing to receive fake heartbeats.
7. No P0 code path can send a motion or mission command.

Items 4-6 must not be marked complete until executed in the target-capable ROS environment.

## Deferred

- Mission start/pause/resume/cancel.
- Inspection authoring/execution.
- Map editing and map-version writes.
- Image/report artifact serving.
- HMI static-file hosting and Wi-Fi/AP provisioning.
- richer map/path/point-cloud streams.
