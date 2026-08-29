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
| P1-03 | decouple Task Registry from Site assets | [ ] | [ ] | [ ] | N/A |
| P1-04 | Active Site -> navigation binding | [ ] | [ ] | [ ] | [ ] |
| P1-05 | NavigationRuntimeStatus + SystemManager gate | [ ] | [ ] | [ ] | [ ] |
| P1-06 | selectively port field commissioning flow | [ ] | [ ] | [ ] | [ ] |
| P1-07 | production RViz direct-goal guard | [ ] | [ ] | [ ] | [ ] |
| P1-08 | full ROS 2 convergence regression | [ ] | [ ] | [ ] | N/A |
| P1-09 | BUNKER + MID360 field acceptance | [ ] | N/A | [ ] | [ ] |
| P1-10 | selectively integrate inspection capability | [ ] | [ ] | [ ] | [ ] |

P1-02 acceptance record:

```text
docs/acceptance/2026-08-29-runtime-navigation-p1-02-site-runtime-integration.md
```

Current evidence boundary:

```text
P1-02 Code:   COMPLETE
P1-02 STATIC: PASS
P1-02 HUMBLE: PENDING
```

Do not infer ROS 2 Humble or field acceptance from cloud/static evidence.

## 2. Frozen branch disposition

Do not continue feature development on old parallel branches after their required capabilities have been integrated or ported.

| Source branch | Relationship | P1 action | Notes |
| --- | --- | --- | --- |
| `feat/runtime-convergence-p0` | accepted ancestor | freeze | historical P0 acceptance baseline |
| `feat/operator-gateway-p1-mission-control` | ancestor of hardware base | inherited | no separate merge needed |
| `feat/hardware-bringup-p0` | direct P1 base | inherited | monitor-first BUNKER/MID360 hardware baseline |
| `feat/runtime-site-owner-p01` | integrated in P1-02 | freeze after integration | source head `3969b152...`; merged by PR #3 into canonical P1 |
| `feat/field-navigation-baseline` | divergent feature line | selective port in P1-06 | do not merge complete history |
| `feat/nav2-planner-smoke-harness` | older planner smoke line | freeze | superseded by later headland smoke line |
| `feat/headland-planner-smoke` | planner acceptance tooling | selective port later only if required | never a production navigation dependency |
| `feat/bunker-rtabmap-slope-nav` | alternate/experimental navigation line | defer/freeze | do not enter current product line |
| `feat/inspection-multiview-evidence` | divergent inspection line | selective port in P1-10 | only after navigation convergence is accepted |
| V3 historical acceptance branches | historical slices | freeze | retain traceability only |

## 3. Completed P1-02 integration record

Canonical P1 integrated Site Runtime with these identities:

```text
pre-integration plan head: d74e92bfa167eeb2ea97ecdfc4fdfce311930a2c
Site-owner source head:     3969b152157e20dddd479fb08f95a694aeb08681
integration merge commit:   60bf00e530b6e975fbb91cb62974a79573b6f678
CI branch-filter commit:     b81fe907467c79def190e3eec893cea52e99fb6f
```

Static/cloud evidence:

```text
PR #3 Runtime Contracts #247:     PASS
PR #3 operator-gateway-no-ros #42: PASS
Canonical branch Runtime Contracts #248: PASS
```

Relative to `feat/hardware-bringup-p0`, canonical P1 is a strict descendant (`behind_by=0`), and P1-02 did not modify production files under `agt_hardware_bringup` or `agt_operator_gateway`.

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

The Runtime Contracts workflow now includes `feat/runtime-navigation-convergence-*` in push branch coverage so subsequent P1 changes are checked on the canonical branch itself.

## 4. Merge rules

### Rule A — one canonical implementation branch

All new P1 production commits go to:

```text
feat/runtime-navigation-convergence-p1
```

Do not create another navigation convergence feature line unless this branch becomes unrecoverable.

### Rule B — freeze integrated same-generation source branches

`feat/runtime-site-owner-p01` has completed its role as the source for P1-02. Do not continue production feature development there. Any Site Runtime correction needed by later P1 work belongs on the canonical convergence branch.

Retain all of these authorities:

```text
agt_system_manager
agt_operator_gateway
agt_hardware_bringup
agt_site_runtime
agt_runtime_contracts
```

No subsystem may replace another subsystem's ownership.

### Rule C — selectively port divergent product experiments

For `field-navigation-baseline`, `inspection-multiview-evidence` and planner-smoke branches, move only the required files/behavior into the canonical P1 architecture. Do not merge branch history wholesale.

Each selective port must document:

- source branch;
- source commit(s);
- files/behavior ported;
- behavior intentionally not ported;
- compatibility changes made for current contracts;
- tests proving the ported behavior.

### Rule D — no new navigation algorithm work inside convergence

P1 is not a place to add new localization/planner/controller stacks. Algorithm changes require a separate future milestone after P1 acceptance.

## 5. Canonical ownership after P1

```text
agt_site_runtime
  owns: deployed Site discovery / validation / active Site authority

agt_site_navigation (planned P1-04)
  owns: Active Site -> resolved localization/navigation asset binding
        + navigation runtime lifecycle evidence

agt_localization + GlobalCorrectionManager
  owns: relocalization evidence and unique map -> odom correction authority

Nav2 / agt_navigation
  owns: planning / control / BT / waypoint capability / collision monitor

agt_system_manager
  owns: fail-closed aggregate RobotState / TaskReadiness

agt_operator_gateway
  owns: external HMI transport and guarded Mission commands

agt_hardware_bringup
  owns: monitor-first vehicle/sensor preflight and bringup composition

Task Registry
  owns: mutable versioned task definitions below tasks_root (target of P1-03)
```

## 6. Expected runtime data flow

```text
Site Package install
  -> agt_site_runtime validate + activate
  -> /agt/maps/active
  -> agt_site_navigation resolve exact assets
  -> localization starts/binds exact PCD
  -> GlobalCorrectionManager TRACKING / map -> odom
  -> Nav2 required lifecycle nodes ACTIVE
  -> NavigationRuntimeStatus READY
  -> agt_system_manager navigation_ready=true
  -> MissionManager may start a bound versioned task
  -> navigation_capability_server
  -> Nav2
  -> Collision Monitor
  -> agt_safety
  -> chassis
```

Task editing target boundary:

```text
HMI / Gateway
  -> Task Registry
  -> runtime/tasks/<site>/<revision>/<task>.json
```

P1-02 does not yet implement that target storage; P1-03 does.

## 7. P1 acceptance invariants

The following must remain true throughout implementation:

1. There is exactly one canonical `map -> odom` authority.
2. Runtime never navigates against a map that is still being commissioned/generated.
3. Unknown or stale readiness evidence is never treated as success.
4. A task cannot execute against a different Site identity/revision/hash than the one it was validated for.
5. Site activation never silently falls back to another revision.
6. Production direct RViz pose goals are disabled by default.
7. No new component bypasses Collision Monitor, `agt_safety`, chassis guard or Mission ownership.
8. Software acceptance and real-vehicle acceptance are recorded separately.

## 8. Per-slice documentation template

At the end of every implementation slice, add a dated report using this structure:

```markdown
# P1-0X <name> Acceptance — YYYY-MM-DD

## Source
- branch:
- start commit:
- end commit:
- imported source branch/commits, if any:

## Implemented
- ...

## Intentionally not implemented
- ...

## Interface changes
- ...

## Tests
### Static/unit
- command
- result

### ROS 2 Humble
- command
- result

### Real vehicle
- command/procedure
- result or NOT RUN

## Known blockers
- ...

## Decision
IMPLEMENTED / STATIC VERIFIED / HUMBLE VERIFIED / FIELD VERIFIED / BLOCKED
```

Then update the table at the top of this file.

## 9. Merge-to-main gate

Do not merge this convergence branch to `main` merely because source code exists.

Minimum software merge gate:

- P1-02 through P1-08 complete;
- current branch builds on ROS 2 Humble;
- selected/full regression has zero failures in changed Runtime packages;
- exact Site activation -> localization binding -> Nav2 lifecycle -> SystemManager readiness smoke passes;
- no old parallel branch is required at runtime;
- documentation identifies any remaining real-hardware-only gates.

Preferred field release gate additionally requires P1-09.

Inspection integration P1-10 may either be included before main merge or follow immediately after navigation release, but it must not destabilize the accepted navigation ownership model.

## 10. Next action

The only active development slice is now:

```text
P1-03 — decouple Task Registry from immutable Site assets
```

P1-03 must move mutable task authority out of the Site/map asset tree while preserving revision/hash checks and execution compatibility. Do not begin P1-04 until P1-03 has its own tests and acceptance note.
