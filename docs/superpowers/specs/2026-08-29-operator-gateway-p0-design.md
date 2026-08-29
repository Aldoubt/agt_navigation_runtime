# Operator Gateway P0 Design

## Goal

Add a robot-side read-only HTTP/WebSocket gateway that translates the authoritative `agt_system_manager` read model into the existing `agt_operator_hmi` gateway v1 contract, without becoming a second runtime authority.

## Branch / merge strategy

This work is based on `feat/runtime-convergence-p0`, not on the divergent inspection feature history. P0 changes are intentionally isolated to a new `src/agt_operator_gateway/` package plus gateway-specific docs.

Rules:

1. Do not modify navigation, chassis, safety, localization, mission execution, or system-manager policy in P0.
2. Do not add new `agt_interfaces` messages/services in P0.
3. Consume `/agt/system/robot_state` as the primary authoritative snapshot.
4. Treat missing/stale runtime evidence as unavailable; never promote UNKNOWN to healthy/ready.
5. Keep gateway API/version names compatible with HMI P3: `agt.operator.gateway/v1` and `agt.operator.stream/v1`.
6. Rebase/merge the active convergence baseline into this branch regularly. Because P0 is additive, later migration should normally reduce to replaying the new package and docs.
7. Inspection write/control APIs are deferred until the runtime inspection capability is converged onto the active runtime baseline.

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

Default freshness limit: 1.5 s. This matches the HMI stale threshold and can be configured.

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

## Dependencies

- ROS 2 Humble / `rclpy`
- `agt_interfaces`
- Python `aiohttp`
- ament_cmake / ament_cmake_python

No rosbridge dependency.

## P0 acceptance

1. Pure projection tests cover readiness, localization, mission state, unknown handling and API envelopes.
2. Gateway package builds without changing existing runtime packages.
3. With `agt_system_manager` publishing RobotState, HMI can hydrate the four GET endpoints and receive stream envelopes.
4. Killing/stalling RobotState input causes the HMI freshness state to degrade rather than continuing to receive fake heartbeats.
5. No P0 code path can send a motion or mission command.

## Deferred

- Mission start/pause/resume/cancel.
- Inspection authoring/execution.
- Map editing and map-version writes.
- Image/report artifact serving.
- HMI static-file hosting and Wi-Fi deployment.
- richer map/path/point-cloud streams.
