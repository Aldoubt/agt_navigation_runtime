# P1-05 NavigationRuntimeStatus + SystemManager Gate Acceptance — 2026-08-29

## Decision

```text
IMPLEMENTED:       PASS
STATIC / CI:       PASS
ROS 2 HUMBLE:      NOT RUN ON CANONICAL P1 BRANCH
REAL VEHICLE:      NOT RUN
```

P1-05 is complete at source/unit/cloud-contract level. It adds an authoritative, read-only Navigation Runtime status downstream of the P1-04 Site binding and makes SystemManager require that evidence before `navigation_ready=true`.

P1-05 does **not** take Nav2 lifecycle transition ownership away from Nav2's lifecycle manager, does not publish TF, and does not claim ROS 2 Humble or field acceptance.

## Source

- Canonical branch: `feat/runtime-navigation-convergence-p1`
- P1-04 final accepted head: `40123b57da8567ac7f4d867890d93004080b764d`
- P1-05 static code head before this acceptance note: `95c6b66f557901b2edb27305ad1f6e243a573650`
- Latest code-head Runtime Contracts: run `#320` (`33239293217`), PASS

No parallel implementation branch was created.

## Implemented

### 1. Authoritative typed Navigation Runtime status

New interface:

```text
agt_interfaces/msg/NavigationRuntimeStatus.msg
```

States:

```text
STATE_UNKNOWN
STATE_STARTING
STATE_READY
STATE_BLOCKED
STATE_ERROR
```

It carries:

```text
site_id
site_revision
site_hash

map_server_active
planner_server_active
smoother_server_active
controller_server_active
behavior_server_active
bt_navigator_active
waypoint_follower_active
collision_monitor_active

localization_bound
map_identity_known
map_identity_match
localization_map_id
localization_map_hash

blocker_codes[]
blocker_messages[]
```

The lifecycle set intentionally matches the production `navigation.launch.py` lifecycle manager exactly: all eight managed nodes are required, not only the six minimum nodes named in the original design.

### 2. Pure fail-closed runtime status policy

`agt_site_navigation.runtime_status` aggregates three evidence layers in order:

```text
SiteNavigationBinding
  -> accepted LocalizationStatus identity/tracking evidence
  -> required Nav2 lifecycle evidence
```

Stable state policy:

```text
no Site binding                         -> UNKNOWN
Site binding ERROR                      -> ERROR
Site binding not READY                  -> BLOCKED
localization evidence not arrived       -> STARTING
localization not TRACKING               -> BLOCKED
localization identity not established   -> STARTING
localization Site/PCD identity mismatch -> BLOCKED
required Nav2 lifecycle unknown         -> STARTING
required Nav2 lifecycle inactive        -> BLOCKED
all required evidence valid/active      -> READY
```

Upstream failure suppresses misleading downstream noise. For example, no Site binding reports `SITE_BINDING_UNKNOWN` rather than eight secondary Nav2-unknown blockers.

### 3. Exact localization binding check

Navigation Runtime does not treat TRACKING alone as sufficient. Once identity evidence exists, it requires:

```text
LocalizationStatus.map_id == SiteNavigationBinding.site_id
LocalizationStatus.map_hash == SiteNavigationBinding.localization_pcd_sha256
```

Therefore a localization process tracking against a different Site or different PCD cannot produce Navigation Runtime READY.

Unknown identity and mismatched identity are distinct:

```text
identity not yet established -> STARTING
identity explicitly differs  -> BLOCKED
```

### 4. Read-only Nav2 lifecycle aggregation

New node:

```text
agt_site_navigation/scripts/navigation_runtime_status_node.py
```

It:

- subscribes `/agt/navigation/site_binding`;
- subscribes `/agt/localization/status`;
- calls only each required lifecycle node's `/<node>/get_state` service;
- treats only `PRIMARY_STATE_ACTIVE` as active;
- applies explicit freshness timeouts to localization and lifecycle evidence;
- publishes `/agt/navigation/runtime_status` using reliable + transient-local QoS;
- republishes periodically so downstream freshness can be evaluated independently.

Required lifecycle nodes:

```text
map_server
planner_server
smoother_server
controller_server
behavior_server
bt_navigator
waypoint_follower
collision_monitor
```

Source contracts explicitly prohibit this node from using:

```text
ChangeState / change_state
TF broadcasters
ActionServer / ActionClient
cmd_vel
FollowPath / FollowWaypoints
filesystem writes
```

Nav2's lifecycle manager therefore remains the lifecycle transition owner.

### 5. Runtime status launch entry point

New launch:

```text
ros2 launch agt_site_navigation navigation_runtime_status.launch.py
```

Parameters:

```text
localization_timeout_s:=2.0
lifecycle_timeout_s:=3.0
lifecycle_poll_period_s:=0.5
```

P1-06 will compose the Site binding/runtime-status entry points into the field commissioning/navigation launch flow. P1-05 does not introduce a second product launch authority.

### 6. SystemManager now requires Navigation Runtime evidence

SystemManager now subscribes:

```text
/agt/navigation/runtime_status
```

with a configured freshness gate:

```text
navigation_status_timeout_s: 2.0
```

Its pure readiness contract now requires:

```text
System health known/acceptable
AND Active Site authoritative + READY
AND localization fresh + accepted TRACKING
AND localization map id matches Active Site
AND NavigationRuntimeStatus fresh + READY
AND NavigationRuntimeStatus Site id/revision/hash matches Active Site
AND NavigationRuntimeStatus identity evidence is established + matching
AND safety fresh + motion explicitly enabled + no E-stop latch
AND chassis connectivity fresh + connected
```

Stable new blockers:

```text
NAVIGATION_UNKNOWN
NAVIGATION_NOT_ACTIVE
NAVIGATION_MAP_MISMATCH
```

The distinction is fail-closed and deterministic:

- missing/stale NavigationRuntimeStatus -> `NAVIGATION_UNKNOWN`;
- status present but identity not yet established or lifecycle not READY -> `NAVIGATION_NOT_ACTIVE`;
- explicit Site/hash/localization binding disagreement -> `NAVIGATION_MAP_MISMATCH`.

### 7. RobotState final navigation readiness authority corrected

Previously `RobotState.navigation_ready` copied the local `navigation_ready` key from the safety diagnostic payload. That was only a subsystem-local condition and could not prove Site/localization/Nav2 readiness.

P1-05 removes that shortcut. The field is now assigned only from:

```text
state.navigation_ready = bool(readiness_result.ready)
```

`RobotState.nav2_state` is also derived from the authoritative NavigationRuntimeStatus:

```text
missing/stale or UNKNOWN -> NAV2_UNKNOWN
STARTING/BLOCKED         -> NAV2_INACTIVE
READY                    -> NAV2_ACTIVE
ERROR                    -> NAV2_ERROR
```

SystemManager itself does not call lifecycle `GetState`; it consumes the already aggregated NavigationRuntimeStatus.

## Intentionally not implemented

P1-05 does **not**:

- call Nav2 `ChangeState`;
- start/stop Nav2 lifecycle nodes;
- start/stop localization;
- publish `map -> odom`;
- replace GlobalCorrectionManager;
- hot-switch Sites during a Mission;
- add a planner/controller/localization algorithm;
- bypass Mission, Collision Monitor, safety or chassis ownership;
- compose the final field navigation launch flow; that is P1-06;
- close ROS 2 Humble or real-vehicle acceptance.

## Interface / topic additions

```text
/agt/navigation/runtime_status
  type: agt_interfaces/msg/NavigationRuntimeStatus
  QoS: RELIABLE + TRANSIENT_LOCAL
```

SystemManager is now a consumer of that topic. It remains the final read-model owner of:

```text
/agt/system/health
/agt/system/task_readiness
/agt/system/robot_state
```

## TDD evidence

P1-05 was implemented in explicit RED/GREEN slices.

### A. SystemManager pure readiness gate

RED:

```text
Runtime Contracts #301 (33238733705)
```

New tests required Navigation Runtime evidence; existing production `Evidence` did not yet carry those fields.

Intermediate implementation exposed one diagnostic issue: when Active Site itself was unknown, the first implementation also emitted a secondary `NAVIGATION_MAP_MISMATCH`. That was corrected so the upstream root cause remains stable.

GREEN:

```text
Runtime Contracts #303 (33238786398): PASS
```

### B. Unknown identity vs explicit mismatch

RED:

```text
Runtime Contracts #304 (33238828258)
```

The test introduced `navigation_identity_known`; failures were limited to the missing field.

GREEN:

```text
Runtime Contracts #305 (33238885012): PASS
```

Resulting contract:

```text
identity unknown  -> NAVIGATION_NOT_ACTIVE
identity mismatch -> NAVIGATION_MAP_MISMATCH
```

### C. Pure NavigationRuntimeStatus policy

RED:

```text
Runtime Contracts #307 (33238954012)
```

All previous suites passed; only the missing `agt_site_navigation.runtime_status` module failed.

GREEN:

```text
Runtime Contracts #308 (33238985169): PASS
```

### D. Typed ROS status + lifecycle observer

RED:

```text
Runtime Contracts #309 (33239015406)
```

Pure policy tests remained green; exactly three new surfaces were missing:

```text
NavigationRuntimeStatus.msg
navigation_runtime_status_node.py
navigation_runtime_status.launch.py
```

GREEN:

```text
Runtime Contracts #315 (33239108421): PASS
```

### E. SystemManager ROS integration

RED:

```text
Runtime Contracts #316 (33239181577)
```

SystemManager group result:

```text
32 passed
4 failed
```

The four failures were exactly the new P1-05 requirements:

```text
runtime_status subscription missing
NavigationRuntimeStatus interface missing in node
navigation freshness/evidence wiring missing
final RobotState.navigation_ready aggregate assignment missing
```

GREEN:

```text
Runtime Contracts #317 (33239248443): PASS
```

### F. Current code-head regression

After adding explicit SystemManager config and a Humble interface smoke test registration:

```text
Runtime Contracts #320 (33239293217): PASS
code head: 95c6b66f557901b2edb27305ad1f6e243a573650
```

Cloud Runtime Contracts covers the source/unit policy but does not build generated ROS interfaces on Humble.

## ROS 2 Humble

`NOT RUN` in this implementation session.

A NavigationRuntimeStatus interface smoke test has been registered under `agt_interfaces`, but its execution is intentionally left as Humble evidence rather than misreported from cloud static CI.

Recommended narrow P1-05 Humble gate:

```bash
source /opt/ros/humble/setup.bash

colcon build --symlink-install --packages-select \
  agt_interfaces \
  agt_runtime_contracts \
  agt_site_runtime \
  agt_site_navigation \
  agt_system_manager

source install/setup.bash

colcon test --packages-select \
  agt_interfaces \
  agt_runtime_contracts \
  agt_site_runtime \
  agt_site_navigation \
  agt_system_manager \
  --event-handlers console_direct+

colcon test-result --verbose
```

Runtime smoke should then prove:

1. no Site binding -> NavigationRuntimeStatus UNKNOWN;
2. valid binding but no localization evidence -> STARTING;
3. accepted TRACKING with matching PCD hash but Nav2 unavailable -> STARTING/BLOCKED, never READY;
4. all eight lifecycle nodes ACTIVE -> NavigationRuntimeStatus READY;
5. lifecycle loss -> NavigationRuntimeStatus BLOCKED;
6. Site/hash mismatch -> BLOCKED;
7. stale runtime status -> SystemManager `NAVIGATION_UNKNOWN`;
8. exact matching status + safety/chassis evidence -> SystemManager `navigation_ready=true`;
9. lifecycle loss/mismatch immediately returns `navigation_ready=false`;
10. no additional TF publisher or lifecycle transition owner appears.

Hard gate: zero build/test failures and every missing/stale/mismatched evidence path remains fail-closed.

## Real vehicle

`NOT RUN`.

Real BUNKER/MID360/Nav2 field evidence remains P1-09. P1-05 only establishes the software authority/readiness contract used by that later acceptance.

## Known follow-up

1. P1-02 through P1-05 Humble evidence remains pending until local/P1-08 regression.
2. P1-06 must selectively port the field commissioning flow and actually compose Site binding + NavigationRuntimeStatus into the production field navigation startup path.
3. P1-07 still must disable the RViz direct goal bridge by production default.
4. P1-08 must run consolidated Humble build/test and exact Site -> localization -> Nav2 -> SystemManager smoke.

## Handoff

```text
P1-05 Code:   COMPLETE
P1-05 STATIC: PASS
P1-05 HUMBLE: PENDING
P1-05 FIELD:  PENDING
```

The next development slice, only after the final documentation head also passes canonical Runtime Contracts, is:

```text
P1-06 — selectively port field commissioning flow
```
