# Operator Gateway P1 Mission Control Design

## Goal

Add authenticated, idempotent Mission start/pause/resume/cancel transport on top of the P0 read-only Gateway without moving Mission authority into the Gateway and without exposing Nav2/chassis commands.

## Branch strategy

P1 is stacked on the verified `feat/operator-gateway-p0` branch:

```text
feat/runtime-convergence-p0
  -> feat/operator-gateway-p0
       -> feat/operator-gateway-p1-mission-control
```

P0 remains the stable read-only fallback. P1 may modify only `src/agt_operator_gateway/`, gateway-specific docs/CI, and later the dedicated HMI integration branch.

## Runtime ownership

`agt_mission_manager` remains the only Mission execution owner:

- execute action: `/agt/missions/execute` (`agt_interfaces/action/ExecuteMission`)
- pause/resume service: `/agt/missions/set_run_state` (`agt_interfaces/srv/SetMissionRunState`)
- authoritative status: `/agt/missions/status`, already projected through `RobotState`

Gateway P1 must not:

- call Nav2 actions;
- publish `/cmd_vel`;
- call chassis APIs;
- duplicate readiness/map/localization gating;
- invent Mission state.

## Single-active-mission and restart-safe cancel

The current Mission Manager rejects a new ExecuteMission goal while `self._active` is true, so it is a single-active-mission owner.

P1 cancellation must not depend on a Gateway-retained goal handle because the Gateway may restart while a Mission continues. Instead P1 calls the standard action cancel service:

```text
/agt/missions/execute/_action/cancel_goal
```

with zero goal UUID and zero timestamp. ROS 2 action semantics define that request as cancel-all. Under the frozen single-active-mission owner contract this means cancel the one active Mission, including after a Gateway restart.

A no-ROS contract test pins the single-active-mission assumption; if Mission Manager later permits concurrency, P1 cancellation must be redesigned before CI can pass.

## HTTP endpoints

P1 adds:

- `POST /api/v1/mission/start`
- `POST /api/v1/mission/pause`
- `POST /api/v1/mission/resume`
- `POST /api/v1/mission/cancel`

P0 GET/WebSocket endpoints are unchanged.

### Start request

```json
{
  "clientRequestId": "uuid-or-other-unique-id",
  "missionId": "inspection_001",
  "missionVersion": "v1",
  "expectedContentSha256": "sha256:..."
}
```

`expectedContentSha256` may be empty to use Mission Manager's existing optional optimistic-lock behavior.

### Pause/resume/cancel request

```json
{
  "clientRequestId": "uuid-or-other-unique-id",
  "missionId": "inspection_001"
}
```

### Response

```json
{
  "apiVersion": "agt.operator.gateway/v1",
  "clientRequestId": "...",
  "command": "START",
  "state": "ACCEPTED",
  "missionId": "inspection_001",
  "errorCode": 0,
  "message": "mission goal accepted"
}
```

`state` is one of:

- `ACCEPTED`
- `REJECTED`
- `IN_PROGRESS`

HTTP status mapping:

- 200/202: accepted or same-request replay/in-flight acknowledgement;
- 400: malformed request;
- 401: missing/invalid command token;
- 409: idempotency-key conflict or Runtime command rejection;
- 503: Mission Action/Service unavailable;
- 504: finite command timeout.

## Authentication

Write APIs are disabled unless both are true:

1. ROS parameter `write_api_enabled:=true`;
2. environment variable `AGT_OPERATOR_COMMAND_TOKEN` contains a non-empty secret.

The secret is never stored in repository YAML and never returned by any endpoint.

Browser/CLI clients send:

```text
Authorization: Bearer <token>
```

Comparison uses constant-time `hmac.compare_digest`.

P0 read-only endpoints remain available when write API is disabled.

## Browser origin policy

CORS is not authorization. The bearer token is the command authorization boundary.

For P1 browser commands:

- the server handles `OPTIONS` preflight;
- allowed request headers include `Authorization` and `Content-Type`;
- no credential cookies are used;
- deployments should configure explicit `cors_allowed_origins` for the HMI when enabling writes;
- a startup warning is emitted if writes are enabled while wildcard origin access is configured.

## Idempotency

Every POST command requires `clientRequestId`.

A bounded in-memory replay store prevents browser/network retry from dispatching the same command twice:

- first `(requestId, canonical payload)` becomes `IN_PROGRESS` then completed;
- same request ID + same payload while in-flight returns `IN_PROGRESS` without a second ROS call;
- same request ID + same payload after completion replays the stored HTTP result;
- same request ID + different payload returns conflict;
- completed records expire after a finite configurable TTL and the cache has a finite maximum size.

Mission Manager remains the final execution authority; idempotency is only transport-level retry protection.

## ROS adapter

A new `MissionCommandAdapter` is attached to the existing Gateway ROS node and owns only:

- `ActionClient(ExecuteMission, /agt/missions/execute)` for START;
- `SetMissionRunState` client for PAUSE/RESUME;
- `action_msgs/srv/CancelGoal` client for restart-safe CANCEL.

All ROS waits have finite timeouts. HTTP/aiohttp execution uses a worker thread so the Web event loop is not blocked while the main ROS executor spins callbacks.

## Failure behavior

- If the Mission server/service is absent, return unavailable; never fall through to a lower-level motion command.
- If a start goal is rejected, return REJECTED and let `/agt/system/robot_state` remain authoritative for actual state.
- Pause/resume responses propagate Mission Manager success/error/message.
- Cancel success means at least one goal transitioned to CANCELING; final CANCELED state is observed asynchronously via RobotState.
- Gateway restart does not auto-start, auto-resume or auto-cancel any Mission.

## No-ROS verification

P1 extends the existing CI with:

- auth unit tests;
- request validation tests;
- idempotency tests including in-flight/replay/conflict;
- HTTP command endpoint tests using a fake command port;
- static ROS ownership test that forbids Nav2/chassis/cmd_vel references;
- static Mission Manager single-active-owner contract;
- interface compatibility for ExecuteMission, SetMissionRunState and CancelGoal usage;
- Python compileall.

Actual ROS 2 Humble build/action/service/cancel testing remains deferred until a ROS environment is available.

## Deferred

- Mission authoring/registry REST API.
- Waypoint/map editor persistence.
- Inspection-specific authoring and camera/gimbal controls.
- User/account identity and multi-user RBAC.
- TLS/VPN provisioning.
- automatic Wi-Fi AP configuration.
