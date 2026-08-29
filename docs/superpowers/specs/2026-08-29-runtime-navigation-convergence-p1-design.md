# Runtime Navigation Convergence P1 Design

Date: 2026-08-29
Branch: `feat/runtime-navigation-convergence-p1`
Base: `feat/hardware-bringup-p0` (`df9a8a05a537ea3d760f92cbbb13df7ead8466d6`)

## 1. Goal

Converge the currently scattered Runtime navigation work into one deployable ROS 2 Humble product line without introducing another mapping, localization, planner, controller, or task-execution stack.

The P1 milestone is complete when the Runtime can perform this controlled flow:

```text
BUNKER + MID360 bringup
  -> FAST-LIVO2 odometry
  -> activate one validated Site Package
  -> bind Site navigation/localization assets
  -> localization TRACKING
  -> Nav2 lifecycle ACTIVE
  -> SystemManager navigation_ready=true
  -> execute one versioned waypoint task
  -> stop fail-closed on safety/localization/runtime loss
```

P1 is deliberately a convergence milestone. New navigation algorithms are out of scope.

## 2. Frozen Architecture Boundaries

### 2.1 Site Package is immutable deployment data

`agt_site_runtime` owns discovery, validation and explicit activation of deployed Site Package revisions. It does not generate map assets and does not own Nav2/map-server process lifecycle.

A Site revision remains immutable after deployment.

### 2.2 Task Library is mutable and separate from Site Package

Task definitions must no longer be treated as files inside an immutable map/Site revision tree.

Target storage boundary:

```text
sites_root/
  <site_id>/<site_revision>/
    manifest.yaml
    navigation assets
    localization assets

runtime/tasks/
  <site_id>/<site_revision>/
    <task_group_id>.json
    backups/
```

Each task is explicitly bound to one Site identity/revision/hash. Updating a task does not require rebuilding the Site Package.

### 2.3 Navigation lifecycle has one owner

Introduce a thin Site-to-Navigation bootstrap/orchestration layer instead of expanding `agt_site_runtime`.

Its responsibility is to resolve the currently active Site assets, verify identity/hash consistency, start or configure localization/Nav2 inputs, and publish one authoritative navigation runtime status.

P1 does not support hot-switching maps while a Mission is active. Site changes are accepted only while mission/navigation execution is inactive; the safe P1 operation is activate Site, then start/restart the navigation runtime against that exact revision.

### 2.4 Existing navigation algorithms stay authoritative

Keep the existing stack:

- FAST-LIVO2 odometry path already selected by Runtime
- NDT/ICP relocalization evidence
- GlobalCorrectionManager as the only `map -> odom` authority
- Nav2 SmacPlanner2D
- Nav2 MPPI
- Nav2 BT Navigator / Waypoint Follower
- Collision Monitor
- `agt_safety`
- `navigation_capability_server.py` as the public waypoint execution capability

Do not add RTAB-Map online mapping, AMCL, a second `map -> odom` publisher, a new planner framework, or a new controller framework in P1.

## 3. Required Work Slices

Implementation must proceed serially in the following order. A later slice must not be started until the previous slice has tests and a short acceptance note.

### P1-01 — Branch and convergence documentation

Create the single integration branch from `feat/hardware-bringup-p0` and freeze this design.

Deliverables:

- this design document
- one convergence status/merge guide document
- branch inventory showing source branches and whether they are merged, selectively ported, or frozen

Acceptance:

- branch exists from the expected hardware baseline
- no production code changed in this slice

### P1-02 — Integrate Site Runtime owner

Bring the accepted `feat/runtime-site-owner-p01` functionality into this branch while preserving Gateway and hardware-bringup behavior.

Required retained capabilities:

- `agt_runtime_contracts`
- `agt_site_runtime`
- `ValidateMapVersion.srv`
- explicit Site list/validate/activate
- persisted active Site selection
- `/agt/maps/active`
- SystemManager active-map readiness integration

Do not resolve conflicts by replacing the whole V3/Gateway/hardware branch with the Site-owner branch.

Acceptance:

- Site/runtime contract tests pass
- SystemManager tests pass
- Gateway/hardware no-ROS tests continue to pass

### P1-03 — Decouple Task Registry from immutable map assets

Refactor Task Registry so its mutable root is `runtime/tasks` (or an explicitly configured `tasks_root`) instead of writing into `runtime/maps/<map>/versions/<version>/tasks`.

Task identity must carry Site binding. The registry must reject execution or mutation when the requested task binding does not match a validated Site identity.

Required behavior:

- list/get/put/archive remain available
- optimistic revision checks remain available
- `content_sha256` remains authoritative
- arbitrary client filesystem paths remain forbidden
- task writes never mutate Site navigation/localization assets
- old task layout may be read only through an explicit migration/import path; no implicit dual-authority mode

Acceptance:

- unit tests prove tasks are written only below `tasks_root`
- tests prove path traversal/symlink protections remain fail-closed
- tests prove task/Site binding mismatch is rejected
- existing task execution hash/revision checks remain green

### P1-04 — Add Active Site to Navigation bootstrap binding

Add one small runtime package/component, tentatively `agt_site_navigation`, that converts the authoritative active Site selection into concrete navigation/localization asset bindings.

Responsibilities:

- subscribe to `/agt/maps/active`
- resolve exact navigation YAML/image, localization PCD and processing record from the validated Site revision
- verify identities/hashes before declaring READY
- expose the resolved binding to launch/orchestration code
- never publish `map -> odom`
- never execute a Mission
- never mutate Site assets

P1 switching policy:

```text
mission inactive
  -> activate exact Site revision
  -> validate binding
  -> start/restart localization + Nav2
  -> wait for TRACKING and lifecycle ACTIVE
  -> permit navigation readiness
```

Acceptance:

- no-active-Site is fail-closed
- missing/corrupt asset is fail-closed
- hash mismatch is fail-closed
- exact active Site produces a deterministic resolved binding

### P1-05 — Add authoritative NavigationRuntimeStatus and SystemManager gate

SystemManager must not infer navigation readiness from map/localization/safety/chassis alone.

Add an authoritative navigation runtime status containing, at minimum:

```text
state: UNKNOWN | STARTING | READY | BLOCKED | ERROR
site_id
site_revision
site_hash
map_server_active
planner_active
controller_active
bt_navigator_active
waypoint_follower_active
collision_monitor_active
localization_bound
map_identity_match
blocker_codes[]
```

SystemManager readiness gains stable blockers such as:

```text
NAVIGATION_UNKNOWN
NAVIGATION_NOT_ACTIVE
NAVIGATION_MAP_MISMATCH
```

Target invariant:

```text
navigation_ready =
  Site READY
  && Localization TRACKING
  && localization/Site identity match
  && Nav2 required lifecycle nodes ACTIVE
  && NavigationRuntimeStatus READY
  && Safety READY and motion explicitly enabled
  && Chassis connected
```

Acceptance:

- missing Nav2 evidence never yields `navigation_ready=true`
- lifecycle loss while executing becomes BLOCKED
- Site/hash mismatch becomes BLOCKED
- SystemManager read model stays fail-closed

### P1-06 — Selectively port field commissioning capabilities

Do not merge the complete `feat/field-navigation-baseline` history.

Port only the product-compatible capabilities:

- `field_mapping.launch.py`
- `field_navigation.launch.py`
- commissioning RViz configuration
- named rosbag recording profiles needed by field acceptance
- map/Site freeze helper logic that remains valid under Site Package 1.0
- field navigation runbook and acceptance gates

Adapt the old freeze flow to the current contract:

```text
field mapping
  -> offline map reconstruction/export
  -> build Site Package 1.0
  -> runtime-contract validation
  -> deploy under sites_root
  -> explicit Site activation
```

Runtime must never navigate against a continuously changing commissioning map.

Acceptance:

- Phase A mapping starts with localization/navigation disabled
- Phase C navigation requires frozen Site assets
- normal production defaults are unchanged
- outputs are never silently overwritten

### P1-07 — Close direct-goal safety boundary

Production `navigation.launch.py` must not unconditionally start the RViz `/goal_pose` bridge.

Required default:

```text
enable_rviz_goal_bridge=false
```

Commissioning launch may explicitly set it to true.

Production mission motion authority remains:

```text
MissionManager
  -> ExecuteWaypointTask
  -> navigation capability server
  -> Nav2
```

Acceptance:

- standard navigation launch does not expose the direct-goal bridge by default
- commissioning launch can opt in
- waypoint/task action execution remains unaffected

### P1-08 — Full ROS 2 regression and convergence acceptance

Run on ROS 2 Humble:

- full or selected colcon build sufficient to cover all changed packages
- package tests for interfaces, runtime contracts, Site Runtime, SystemManager, navigation, safety, Gateway and hardware bringup
- no-upstream fail-closed smoke
- exact Site activation/binding smoke
- Nav2 lifecycle aggregation smoke

Record commands and results in a dated acceptance report. Do not mark hardware-only checks PASS from static/unit evidence.

### P1-09 — BUNKER field acceptance

Close the real hardware gates using BUNKER + MID360 and the final installed TF/profile.

Minimum sequence:

```text
hardware preflight
sensor health
FAST-LIVO2 odometry
Site activation
NDT/ICP TRACKING
Nav2 ACTIVE
SystemManager navigation_ready=true
single NavigateToPose commissioning check
versioned waypoint task execution
safety stop/cancel
localization-loss BLOCKED behavior
explicit relocalization
manual RESUME
```

Store field evidence under a deterministic acceptance output directory and reference it from the acceptance report.

### P1-10 — Integrate inspection capability after navigation is frozen

Only after P1-08/P1-09 navigation gates are stable should the multiview inspection capability be selectively migrated from `feat/inspection-multiview-evidence`.

Do not merge the entire divergent branch.

Preserve the existing navigation/Mission ownership and attach inspection as a consumer of successful point arrival/stationary evidence.

## 4. Branch Disposition

| Branch | P1 treatment |
| --- | --- |
| `feat/runtime-convergence-p0` | frozen historical acceptance baseline |
| `feat/operator-gateway-p1-mission-control` | already inherited by hardware baseline |
| `feat/hardware-bringup-p0` | P1 base |
| `feat/runtime-site-owner-p01` | integrate into P1 |
| `feat/field-navigation-baseline` | selective port only |
| `feat/nav2-planner-smoke-harness` | superseded by headland smoke line; no direct merge |
| `feat/headland-planner-smoke` | later acceptance-tool selective port only |
| `feat/bunker-rtabmap-slope-nav` | freeze/defer; do not enter current product line |
| `feat/inspection-multiview-evidence` | selective port after navigation convergence |
| historical V3 acceptance branches | keep for traceability; no new feature development |

## 5. Non-Goals

P1 explicitly does not implement:

- online navigation against a map still being built
- hot map switching during an active Mission
- RTAB-Map production navigation
- GNSS as a second independent `map -> odom` authority
- AMCL
- automatic unbounded relocalization search after LOST
- new global/local planner families
- new controller families
- traversability algorithm redesign
- inspection model training
- mission-global visual deduplication

These may be separate future milestones only after the current Runtime navigation line is accepted.

## 6. Error and Safety Policy

All new orchestration is fail-closed.

Unknown evidence is not success. A missing Site, mismatched hash, stale localization state, inactive required Nav2 lifecycle node, disconnected chassis, stale safety status, disabled motion or latched E-stop must prevent `navigation_ready=true`.

No new component may bypass Collision Monitor, `agt_safety`, chassis guard or Mission ownership.

## 7. Documentation Contract

Every implementation slice must add or update:

1. a short dated implementation/acceptance note under `docs/acceptance/` or `docs/superpowers/reports/`;
2. the convergence status document with completed checkboxes, source commits and test evidence;
3. interface/runbook documentation when a public topic/service/action or operator workflow changes.

The convergence status document is the entry point for future maintainers and merge review. It must distinguish:

- implemented in code
- unit/static verified
- ROS 2 Humble runtime verified
- real-vehicle verified

These states must never be collapsed into a single ambiguous "done" label.

## 8. Final P1 Acceptance Definition

P1 navigation convergence is considered software-complete only when one branch contains the canonical Site owner, mutable Task Registry, Site-to-Navigation binding, Nav2 lifecycle readiness, field commissioning entry points and production direct-goal guard with passing ROS 2 regression evidence.

P1 field-complete requires separate real BUNKER/MID360 evidence. Software acceptance must not be reported as field acceptance.
