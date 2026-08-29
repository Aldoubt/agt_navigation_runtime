# Runtime Navigation Convergence P1 — Status and Merge Guide

Date: 2026-08-29
Canonical development branch: `feat/runtime-navigation-convergence-p1`
Base commit: `df9a8a05a537ea3d760f92cbbb13df7ead8466d6` (`feat/hardware-bringup-p0`)
Design: `docs/superpowers/specs/2026-08-29-runtime-navigation-convergence-p1-design.md`

This is the canonical status/merge entry point. Update it after every P1 slice. Do not infer ROS 2 Humble or real-vehicle acceptance from Python/static/cloud-contract evidence.

## 1. Current milestone state

Legend:

- `[ ]` not implemented / not verified
- `[x]` implementation slice completed / evidence passed
- `STATIC` unit/static/cloud-contract evidence
- `HUMBLE` verified on ROS 2 Humble runtime
- `FIELD` verified on real BUNKER/MID360 hardware

| Slice | Scope | Code | STATIC | HUMBLE | FIELD |
| --- | --- | --- | --- | --- | --- |
| P1-01 | branch + design + merge/status docs | [x] | [x] | N/A | N/A |
| P1-02 | integrate Site Runtime owner | [x] | [x] | [ ] | N/A |
| P1-03 | decouple Task Registry from Site assets | [x] | [x] | [ ] | N/A |
| P1-04 | Active Site -> navigation binding | [x] | [x] | [ ] | [ ] |
| P1-05 | NavigationRuntimeStatus + SystemManager gate | [x] | [x] | [ ] | [ ] |
| P1-06 | selectively port field commissioning flow | [x] | [x] | [ ] | [ ] |
| P1-07 | production RViz direct-goal guard | [x] | [x] | [ ] | [ ] |
| P1-08 | full ROS 2 convergence regression | [ ] | [ ] | [ ] | N/A |
| P1-09 | BUNKER + MID360 field acceptance | [ ] | N/A | [ ] | [ ] |
| P1-10 | selectively integrate inspection capability | [ ] | [ ] | [ ] | [ ] |

Acceptance records:

```text
docs/acceptance/2026-08-29-runtime-navigation-p1-02-site-runtime-integration.md
docs/acceptance/2026-08-29-runtime-navigation-p1-03-task-registry-decoupling.md
docs/acceptance/2026-08-29-runtime-navigation-p1-04-active-site-navigation-binding.md
docs/acceptance/2026-08-29-runtime-navigation-p1-05-navigation-runtime-readiness.md
docs/acceptance/2026-08-29-runtime-navigation-p1-06-field-commissioning.md
docs/acceptance/2026-08-29-runtime-navigation-p1-07-rviz-direct-goal-guard.md
```

Current completed evidence boundary:

```text
P1-02 through P1-07 Code:   COMPLETE
P1-02 through P1-07 STATIC: PASS
P1-02 through P1-07 HUMBLE: PENDING where applicable
P1-04 through P1-07 FIELD:  PENDING where applicable
```

## 2. Frozen branch disposition

Do not continue product development on old parallel branches after the required behavior has been integrated or selectively ported.

| Source branch | Relationship | P1 action | Notes |
| --- | --- | --- | --- |
| `feat/runtime-convergence-p0` | accepted ancestor | freeze | historical P0 baseline |
| `feat/operator-gateway-p1-mission-control` | ancestor of hardware base | inherited | no separate merge required |
| `feat/hardware-bringup-p0` | direct P1 base | inherited | monitor-first BUNKER/MID360 hardware baseline |
| `feat/runtime-site-owner-p01` | integrated in P1-02 | freeze | source head `3969b152...`; merged by PR #3 |
| `feat/field-navigation-baseline` | selectively ported in P1-06 | freeze | commissioning behavior ported; divergent history is not a runtime dependency |
| `feat/nav2-planner-smoke-harness` | older planner smoke line | freeze | superseded by later planner smoke work |
| `feat/headland-planner-smoke` | acceptance tooling | selective port only if P1-08 requires it | never a production dependency |
| `feat/bunker-rtabmap-slope-nav` | alternate experimental line | defer/freeze | not part of current product line |
| `feat/inspection-multiview-evidence` | divergent inspection line | selective port in P1-10 | only after navigation convergence |
| V3 historical acceptance branches | historical slices | freeze | traceability only |

## 3. Authority model after P1-07

```text
agt_site_runtime
  owns Site discovery / validation / activation

agt_site_navigation
  owns Active Site -> exact navigation/localization asset binding
  + read-only NavigationRuntimeStatus aggregation
  does not transition lifecycle nodes or publish map -> odom

agt_localization + GlobalCorrectionManager
  owns localization/relocalization evidence
  + unique map -> odom correction authority

Nav2 lifecycle manager
  owns Nav2 lifecycle transitions

agt_navigation
  owns planning / control / BT / waypoint capability / Collision Monitor

agt_system_manager
  owns final fail-closed RobotState / TaskReadiness aggregate

agt_operator_gateway
  owns external HMI transport and guarded Mission commands

agt_hardware_bringup
  owns monitor-first vehicle/sensor preflight and bringup composition

agt_experiment_manager
  owns rosbag record/playback processes

Task Registry
  owns mutable versioned task definitions below tasks_root

agt_field_commissioning
  owns commissioning-only entry points and mutable source artifacts
  never becomes a Site, TF, lifecycle, recorder or Mission authority
```

No subsystem may silently replace another subsystem's authority.

## 4. P1-02 through P1-04 summary

P1-02 integrated the Site Runtime authority, including `/agt/maps/active`, list/validate/activate services and fail-closed authoritative-map handling.

```text
integration merge commit: 60bf00e530b6e975fbb91cb62974a79573b6f678
Runtime Contracts #248:  PASS
```

P1-03 separated immutable Site assets from mutable tasks:

```text
runtime/tasks/<site>/<revision>/site_binding.json
runtime/tasks/<site>/<revision>/<task>.json
runtime/tasks/<site>/<revision>/<task>.route.yaml
runtime/tasks/<site>/<revision>/archive/
```

Legacy map-local tasks require explicit migration; there is no Runtime fallback.

```text
Runtime Contracts #281 (33237868775): PASS
P1 task-storage: 52 passed
```

P1-04 added exact read-only Site-to-navigation asset binding:

```text
/agt/maps/active
  -> canonical Site revalidation
  -> exact navigation YAML/image + hashes
  -> exact localization PCD + hash
  -> /agt/navigation/site_binding
```

```text
Runtime Contracts #298 (33238275311): PASS
P1 active-site navigation binding: 10 passed
```

## 5. P1-05 Navigation Runtime readiness

P1-05 added one fail-closed readiness aggregate:

```text
/agt/navigation/site_binding
        +
/agt/localization/status
        +
8 x Nav2 /<node>/get_state
        ↓
/agt/navigation/runtime_status
        ↓
agt_system_manager
        ↓
/agt/system/task_readiness
/agt/system/robot_state
```

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

`agt_site_navigation` observes `GetState` only; it never calls `ChangeState`.

Localization evidence must match the bound Site localization PCD identity, and SystemManager adds stable fail-closed blockers including `NAVIGATION_UNKNOWN`, `NAVIGATION_NOT_ACTIVE` and `NAVIGATION_MAP_MISMATCH`.

```text
Runtime Contracts #320 (33239293217): PASS
```

Detailed record:

```text
docs/acceptance/2026-08-29-runtime-navigation-p1-05-navigation-runtime-readiness.md
```

## 6. P1-06 field commissioning

P1-06 selectively ported the useful field workflow without whole-merging `feat/field-navigation-baseline`:

```text
mutable commissioning run
  -> agt_experiment_manager / field_mapping_commissioning bag
  -> Phase A FAST-LIVO2 mapper
  -> normal ROS shutdown save
  -> finalize_mapping_run.py + SHA256 evidence
  -> external offline reconstruction/export
  -> immutable Site Package 1.0
  -> deploy new revision under sites_root
  -> /agt/maps/validate
  -> /agt/maps/activate
  -> /agt/maps/active
  -> frozen-Site Phase C
  -> SiteNavigationBinding + Localization + Nav2 + NavigationRuntimeStatus
```

Commissioning output can never be used directly as navigation authority. Normal Runtime FAST-LIVO2 keeps PCD persistence disabled. ExperimentManager remains the only recorder owner.

TDD evidence:

```text
#341 / 33241740091: expected RED, 4 failed + 20 passed in commissioning group
#347 / 33241896575: PASS, commissioning group 24 passed
final P1-06 head 2347f00044e49cdd57d44ad109379b0311d82079
final-head Runtime Contracts 33241998549: PASS
```

Detailed record:

```text
docs/acceptance/2026-08-29-runtime-navigation-p1-06-field-commissioning.md
```

## 7. P1-07 production RViz direct-goal guard

Before P1-07, the standard production `navigation.launch.py` unconditionally started `goal_pose_bridge.py`, which subscribes `/goal_pose` and directly sends Nav2 `NavigateToPose` goals.

P1-07 makes the compatibility bridge opt-in:

```text
production navigation.launch.py
  enable_rviz_goal_bridge=false by default
  goal_pose_bridge.py starts only under IfCondition

formal navigation capability
  allow_direct_pose_goals=False unchanged

offline_navigation.launch.py
  explicitly passes enable_rviz_goal_bridge=true

field_navigation.launch.py
  enable_rviz_goal_bridge=false by default
  may forward explicit commissioning-only opt-in
  does not create a second bridge
```

Production Mission motion remains:

```text
MissionManager
  -> ExecuteWaypointTask
  -> navigation_capability_server.py
  -> Nav2
  -> Collision Monitor
  -> agt_safety
  -> chassis
```

TDD evidence:

```text
#351 / 33242069289: RED, RViz guard 2 failed + 2 passed
#353 / 33242117197: GREEN, RViz guard 4 passed
#354 / 33242175974: compatibility RED, 1 failed + 4 passed
#355 / 33242202456: GREEN, RViz guard 5 passed
code head: cacd0d4a48f1a43e1bf70f8bdc3b9d8dd9d757b4
```

Full #355 regression counts:

```text
V3-01 contracts:               19 passed
V3-02 odometry:                 9 passed
V3-03 execution:               18 passed
SystemManager:                 36 passed
Site Runtime owner:            45 passed
P1 task-storage:               52 passed
P1 site-navigation:            26 passed
P1 field commissioning:        24 passed
P1 RViz direct-goal guard:      5 passed
```

Detailed record:

```text
docs/acceptance/2026-08-29-runtime-navigation-p1-07-rviz-direct-goal-guard.md
```

P1-07 does not claim ROS 2 Humble or real-vehicle acceptance.

## 8. Merge rules

1. All new P1 product commits remain on `feat/runtime-navigation-convergence-p1`.
2. Preserve the authority model above; do not add a second Site, TF, lifecycle, recorder, Mission or task authority.
3. Divergent experiment branches are selectively ported, never whole-merged by default.
4. P1 convergence does not add another SLAM/localization/planner/controller algorithm stack.
5. Static/cloud evidence and ROS 2 Humble/field evidence remain separate gates.

## 9. Expected runtime data flow

```text
Site Package install
  -> agt_site_runtime validate + activate
  -> /agt/maps/active
  -> agt_site_navigation resolve exact assets
  -> /agt/navigation/site_binding
  -> localization binds exact PCD
  -> GlobalCorrectionManager TRACKING / map -> odom
  -> Nav2 lifecycle manager activates required nodes
  -> NavigationRuntimeStatus sees all required evidence READY
  -> /agt/navigation/runtime_status READY
  -> agt_system_manager navigation_ready=true
  -> MissionManager may start a bound versioned task
  -> navigation_capability_server
  -> Nav2
  -> Collision Monitor
  -> agt_safety
  -> chassis
```

Task editing remains separate from immutable Site assets:

```text
HMI / Gateway
  -> Task Registry
  -> runtime/tasks/<site>/<revision>/<task>.json
```

## 10. P1 acceptance invariants

1. Exactly one canonical `map -> odom` authority exists.
2. Runtime never navigates against a map still being commissioned/generated.
3. Unknown or stale readiness evidence is never success.
4. A task cannot execute against a different Site identity/revision/hash than validated.
5. Site activation never silently falls back to another revision.
6. Production direct RViz pose goals are disabled by default.
7. No component bypasses Collision Monitor, `agt_safety`, chassis guard or Mission ownership.
8. Software and real-vehicle acceptance remain separate.
9. Mutable task edits never mutate immutable Site package integrity.
10. Legacy map-local tasks require explicit migration; no Runtime fallback.
11. `agt_site_navigation` may observe lifecycle state but may not transition Nav2 lifecycle nodes.
12. `RobotState.navigation_ready` equals final SystemManager aggregate readiness, not a subsystem-local flag.
13. Offline or commissioning direct-goal support must be explicit opt-in and must not alter the production default.

## 11. Merge-to-main gate

Do not merge this convergence branch to `main` merely because source/static contracts exist.

Minimum software merge gate:

- P1-02 through P1-08 complete;
- current canonical branch builds on ROS 2 Humble;
- selected/full regression has zero failures in changed Runtime packages;
- exact Site activation -> localization binding -> Nav2 lifecycle -> SystemManager readiness smoke passes;
- no old parallel branch is required at runtime;
- documentation identifies remaining real-hardware-only gates.

Preferred field release gate additionally requires P1-09.

## 12. Next action

The only active development slice is now:

```text
P1-08 — full ROS 2 Humble convergence regression
```

P1-08 must provide fresh ROS 2 Humble build/test/runtime evidence for the canonical branch. The existing Ubuntu 24.04 Python Runtime Contracts workflow remains STATIC evidence only and must not be relabeled as HUMBLE.

Do not begin P1-09 until P1-08 has its own acceptance record and fresh Humble evidence.
