# Runtime Navigation Convergence P1 — Status and Merge Guide

Date: 2026-08-29
Canonical development branch: `feat/runtime-navigation-convergence-p1`
Base commit: `df9a8a05a537ea3d760f92cbbb13df7ead8466d6` (`feat/hardware-bringup-p0`)
Design: `docs/superpowers/specs/2026-08-29-runtime-navigation-convergence-p1-design.md`

This file is the entry point for future implementation, review and merge work. Update it at the end of every P1 slice.

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
| P1-07 | production RViz direct-goal guard | [ ] | [ ] | [ ] | [ ] |
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
```

Current completed evidence boundary:

```text
P1-02 Code:   COMPLETE
P1-02 STATIC: PASS
P1-02 HUMBLE: PENDING

P1-03 Code:   COMPLETE
P1-03 STATIC: PASS
P1-03 HUMBLE: PENDING

P1-04 Code:   COMPLETE
P1-04 STATIC: PASS
P1-04 HUMBLE: PENDING
P1-04 FIELD:  PENDING

P1-05 Code:   COMPLETE
P1-05 STATIC: PASS
P1-05 HUMBLE: PENDING
P1-05 FIELD:  PENDING

P1-06 Code:   COMPLETE
P1-06 STATIC: PASS
P1-06 HUMBLE: PENDING
P1-06 FIELD:  PENDING
```

Do not infer ROS 2 Humble or field acceptance from cloud/static evidence.

## 2. Frozen branch disposition

Do not continue feature development on old parallel branches after their required capabilities have been integrated or selectively ported.

| Source branch | Relationship | P1 action | Notes |
| --- | --- | --- | --- |
| `feat/runtime-convergence-p0` | accepted ancestor | freeze | historical P0 acceptance baseline |
| `feat/operator-gateway-p1-mission-control` | ancestor of hardware base | inherited | no separate merge needed |
| `feat/hardware-bringup-p0` | direct P1 base | inherited | monitor-first BUNKER/MID360 hardware baseline |
| `feat/runtime-site-owner-p01` | integrated in P1-02 | freeze | source head `3969b152...`; merged by PR #3 |
| `feat/field-navigation-baseline` | selectively ported in P1-06 | freeze | commissioning workflow ported; divergent history is not a runtime dependency |
| `feat/nav2-planner-smoke-harness` | older planner smoke line | freeze | superseded by headland smoke line |
| `feat/headland-planner-smoke` | planner acceptance tooling | selective port later only if required | never a production dependency |
| `feat/bunker-rtabmap-slope-nav` | alternate/experimental line | defer/freeze | do not enter current product line |
| `feat/inspection-multiview-evidence` | divergent inspection line | selective port in P1-10 | only after navigation convergence |
| V3 historical acceptance branches | historical slices | freeze | retain traceability only |

## 3. Completed P1-02 integration record

P1-02 integrated Site Runtime while preserving hardware/Gateway authorities.

```text
pre-integration plan head: d74e92bfa167eeb2ea97ecdfc4fdfce311930a2c
Site-owner source head:     3969b152157e20dddd479fb08f95a694aeb08681
integration merge commit:   60bf00e530b6e975fbb91cb62974a79573b6f678
CI branch-filter commit:     b81fe907467c79def190e3eec893cea52e99fb6f
Runtime Contracts #248:     PASS
```

Imported authorities:

```text
agt_runtime_contracts
agt_site_runtime
ValidateMapVersion.srv
/agt/maps/active
/agt/maps/list
/agt/maps/validate
/agt/maps/activate
SystemManager authoritative-map tombstone handling
```

## 4. Completed P1-03 task authority record

P1-03 separates immutable Site/map assets from mutable Task Library state:

```text
immutable:
  deployed Site package / map version assets
  runtime/maps/<site>/versions/<revision>/routes/...  # immutable Route Assets where used

mutable:
  runtime/tasks/<site>/<revision>/site_binding.json
  runtime/tasks/<site>/<revision>/<task>.json
  runtime/tasks/<site>/<revision>/<task>.route.yaml
  runtime/tasks/<site>/<revision>/archive/
```

Formal task execution now resolves the task store against the current READY/valid/active `/agt/maps/active` identity. Legacy map-local tasks are never an implicit fallback; migration is explicit and dry-run by default.

```text
Runtime Contracts #281 (33237868775): PASS
P1 task-storage group: 52 passed
```

## 5. Completed P1-04 Active Site binding record

P1-04 introduced the read-only Site-to-navigation asset binder:

```text
/agt/maps/active
  -> agt_site_navigation canonical revalidation
  -> exact Site id/revision/hash
  -> exact navigation YAML/image + hashes
  -> exact localization PCD + hash
  -> /agt/navigation/site_binding
```

Typed output:

```text
agt_interfaces/msg/SiteNavigationBinding
```

It uses reliable + transient-local QoS and replaces any previous READY binding with fresh UNKNOWN/BLOCKED/ERROR evidence when Site authority is revoked, missing, changed or corrupted.

It does not publish TF, execute Missions, control Nav2 lifecycle transitions, publish velocity commands, or mutate Site assets.

```text
Runtime Contracts #298 (33238275311): PASS
P1 active-site navigation binding group: 10 passed
```

## 6. Completed P1-05 Navigation Runtime readiness record

P1-05 adds one authoritative read-only navigation runtime status downstream of the P1-04 binding:

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

New typed interface:

```text
agt_interfaces/msg/NavigationRuntimeStatus
```

Runtime status states:

```text
UNKNOWN | STARTING | READY | BLOCKED | ERROR
```

The required lifecycle set matches the production Nav2 lifecycle manager exactly:

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

`agt_site_navigation` is only a lifecycle **observer**. It calls `GetState` and never `ChangeState`; Nav2 lifecycle manager remains transition owner.

Localization binding requires both:

```text
LocalizationStatus.map_id   == SiteNavigationBinding.site_id
LocalizationStatus.map_hash == SiteNavigationBinding.localization_pcd_sha256
```

SystemManager now adds a freshness-gated `/agt/navigation/runtime_status` input and stable blockers:

```text
NAVIGATION_UNKNOWN
NAVIGATION_NOT_ACTIVE
NAVIGATION_MAP_MISMATCH
```

Final readiness invariant implemented by P1-05:

```text
navigation_ready =
  required SystemHealth acceptable
  && authoritative Active Site READY
  && accepted Localization TRACKING
  && localization map identity matches Active Site
  && fresh NavigationRuntimeStatus READY
  && NavigationRuntimeStatus Site id/revision/hash matches Active Site
  && NavigationRuntimeStatus localization identity established + matching
  && Safety fresh + motion enabled + no E-stop latch
  && Chassis fresh + connected
```

`RobotState.navigation_ready` is now assigned from this final aggregate result, not copied from the safety diagnostic's subsystem-local `navigation_ready` value.

Static/TDD evidence includes:

```text
#301 RED  - first SystemManager navigation evidence contract
#303 PASS - navigation blockers + root-cause ordering
#304 RED  - identity-known distinction
#305 PASS - unknown identity vs explicit mismatch
#307 RED  - runtime status policy missing
#308 PASS - pure runtime status policy
#309 RED  - typed status/node/launch missing
#315 PASS - read-only lifecycle observer
#316 RED  - SystemManager ROS integration missing
#317 PASS - SystemManager integration
#320 PASS - current code-head regression + Humble interface smoke registration
```

Current P1-05 code-head static evidence before documentation:

```text
95c6b66f557901b2edb27305ad1f6e243a573650
Runtime Contracts #320 (33239293217): PASS
```

Detailed record:

```text
docs/acceptance/2026-08-29-runtime-navigation-p1-05-navigation-runtime-readiness.md
```

## 7. Completed P1-06 field commissioning record

P1-06 selectively ports the useful field workflow from `feat/field-navigation-baseline` into the current Site Package + NavigationRuntimeStatus architecture without whole-merging the divergent branch.

The accepted flow is:

```text
mutable commissioning run
  -> agt_experiment_manager / field_mapping_commissioning bag
  -> agt_field_commissioning Phase A FAST-LIVO2 mapper
  -> normal ROS shutdown save
  -> finalize_mapping_run.py + SHA256 evidence
  -> external offline reconstruction/export
  -> immutable Site Package 1.0
  -> deploy a new revision under sites_root
  -> agt_site_runtime /agt/maps/validate
  -> agt_site_runtime /agt/maps/activate (revalidates before persistence)
  -> /agt/maps/active
  -> agt_field_commissioning frozen-Site Phase C
  -> SiteNavigationBinding + Localization + Nav2 + NavigationRuntimeStatus
```

New/updated product assets:

```text
src/agt_field_commissioning/
docs/runbooks/field-navigation-commissioning.md
src/agt_experiment_manager/config/bag_profiles.yaml :: field_mapping_commissioning
tests/commissioning/
```

P1-06 keeps normal Runtime FAST-LIVO2 PCD persistence disabled. Commissioning writes only below a unique mutable `runtime/commissioning/<site>/<run>/` root and cannot be used directly as a navigation map. Phase C exposes no manual `global_map_pcd` or `navigation_map` launch arguments; it consumes only a persisted, revalidated Active Site and Site-derived hashes/paths.

ExperimentManager remains the sole rosbag process owner. Site Runtime remains the sole Site validation/activation authority. GlobalCorrectionManager remains the sole `map -> odom` correction authority. Nav2 lifecycle manager remains transition owner.

TDD evidence:

```text
Runtime Contracts #341 (33241740091): expected RED
P1 commissioning group: 4 failed, 20 passed
failure scope: missing runbook + missing dedicated commissioning bag profile only

Runtime Contracts #347 (33241896575): PASS
P1 commissioning group: 24 passed
```

Full #347 group counts:

```text
V3-01 contracts:               19 passed
V3-02 odometry:                 9 passed
V3-03 execution:               18 passed
SystemManager:                 36 passed
Site Runtime owner:            45 passed
P1 task-storage:               52 passed
P1 site-navigation:            26 passed
P1 field commissioning:        24 passed
```

Detailed record:

```text
docs/acceptance/2026-08-29-runtime-navigation-p1-06-field-commissioning.md
```

P1-06 does not claim ROS 2 Humble or real-vehicle acceptance. Production RViz direct-goal guarding is intentionally P1-07.

## 8. Merge rules

### Rule A — one canonical implementation branch

All new P1 production commits go to:

```text
feat/runtime-navigation-convergence-p1
```

Do not create another navigation convergence feature line unless this branch becomes unrecoverable.

### Rule B — preserve ownership boundaries

Retain these authorities:

```text
agt_site_runtime
  Active Site discovery / validation / activation authority

agt_site_navigation
  exact Site asset binding
  + read-only Nav2/localization runtime evidence aggregation

agt_localization + GlobalCorrectionManager
  localization/relocalization evidence
  + unique map -> odom correction authority

Nav2 lifecycle manager
  lifecycle transition authority

agt_navigation
  planning / control / BT / waypoint capability / Collision Monitor

agt_system_manager
  final fail-closed health/readiness/RobotState aggregate

agt_operator_gateway
  external HMI transport and guarded Mission commands

agt_hardware_bringup
  monitor-first vehicle/sensor preflight and bringup composition

Task Registry
  mutable versioned task definitions below tasks_root
```

No subsystem may silently replace another subsystem's authority.

### Rule C — selectively port divergent product experiments

For `field-navigation-baseline`, `inspection-multiview-evidence` and planner-smoke branches, move only required behavior/files into the canonical P1 architecture. Do not merge divergent history wholesale.

Each selective port must document:

- source branch / commit;
- files/behavior ported;
- behavior intentionally not ported;
- compatibility changes for current contracts;
- tests proving the ported behavior.

### Rule D — no new navigation algorithms inside convergence

P1 is not the place to add another SLAM/localization/planner/controller stack.

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
  -> read-only NavigationRuntimeStatus observer sees all eight ACTIVE
  -> /agt/navigation/runtime_status READY
  -> agt_system_manager navigation_ready=true
  -> MissionManager may start a bound versioned task
  -> navigation_capability_server
  -> Nav2
  -> Collision Monitor
  -> agt_safety
  -> chassis
```

Task editing/execution remains separated from immutable Site assets:

```text
HMI / Gateway (future publication bridge)
  -> Task Registry
  -> runtime/tasks/<site>/<revision>/<task>.json

Mission / ExecuteWaypointTask
  -> exact Active Site + task binding checks
  -> final SystemManager readiness
  -> MAP or ROUTE backend
```

## 10. P1 acceptance invariants

1. There is exactly one canonical `map -> odom` authority.
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
12. `RobotState.navigation_ready` must equal final SystemManager aggregate readiness, not a subsystem-local flag.

## 11. Merge-to-main gate

Do not merge this convergence branch to `main` merely because source exists.

Minimum software merge gate:

- P1-02 through P1-08 complete;
- current branch builds on ROS 2 Humble;
- selected/full regression has zero failures in changed Runtime packages;
- exact Site activation -> localization binding -> Nav2 lifecycle -> SystemManager readiness smoke passes;
- no old parallel branch is required at runtime;
- documentation identifies remaining real-hardware-only gates.

Preferred field release gate additionally requires P1-09.

## 12. Next action

The only active development slice is now:

```text
P1-07 — production RViz direct-goal guard
```

P1-07 must ensure a standard production Runtime cannot bypass Mission/Gateway/task ownership by sending an RViz/Nav2 pose goal directly. Any commissioning-only direct-goal path must be explicit, guarded and disabled by default in production composition.

Do not begin P1-08 until P1-07 has its own tests and acceptance note.
