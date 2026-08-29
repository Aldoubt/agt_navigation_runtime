# Runtime Navigation Convergence P1 — Status and Merge Guide

Date: 2026-08-29
Canonical development branch: `feat/runtime-navigation-convergence-p1`
Base commit: `df9a8a05a537ea3d760f92cbbb13df7ead8466d6` (`feat/hardware-bringup-p0`)
Design: `docs/superpowers/specs/2026-08-29-runtime-navigation-convergence-p1-design.md`

This file is the entry point for future implementation, review and merge work. Update it at the end of every P1 slice.

## 1. Current milestone state

Legend:

- `[ ]` not implemented
- `[x]` implementation slice completed
- `STATIC` unit/static evidence only
- `HUMBLE` verified on ROS 2 Humble runtime
- `FIELD` verified on real BUNKER/MID360 hardware

| Slice | Scope | Code | STATIC | HUMBLE | FIELD |
| --- | --- | --- | --- | --- | --- |
| P1-01 | branch + design + merge/status docs | [x] | [x] | N/A | N/A |
| P1-02 | integrate Site Runtime owner | [ ] | [ ] | [ ] | N/A |
| P1-03 | decouple Task Registry from Site assets | [ ] | [ ] | [ ] | N/A |
| P1-04 | Active Site -> navigation binding | [ ] | [ ] | [ ] | [ ] |
| P1-05 | NavigationRuntimeStatus + SystemManager gate | [ ] | [ ] | [ ] | [ ] |
| P1-06 | selectively port field commissioning flow | [ ] | [ ] | [ ] | [ ] |
| P1-07 | production RViz direct-goal guard | [ ] | [ ] | [ ] | [ ] |
| P1-08 | full ROS 2 convergence regression | [ ] | [ ] | [ ] | N/A |
| P1-09 | BUNKER + MID360 field acceptance | [ ] | N/A | [ ] | [ ] |
| P1-10 | selectively integrate inspection capability | [ ] | [ ] | [ ] | [ ] |

P1-01 changes documentation only. No production source has been changed on this branch yet.

## 2. Frozen branch disposition

Do not continue feature development on old parallel branches after their required capabilities have been integrated or ported.

| Source branch | Relationship | P1 action | Notes |
| --- | --- | --- | --- |
| `feat/runtime-convergence-p0` | accepted ancestor | freeze | historical P0 acceptance baseline |
| `feat/operator-gateway-p1-mission-control` | ancestor of hardware base | inherited | no separate merge needed |
| `feat/hardware-bringup-p0` | direct P1 base | inherited | monitor-first BUNKER/MID360 hardware baseline |
| `feat/runtime-site-owner-p01` | diverged from common convergence base | integrate in P1-02 | preserve Gateway/hardware branch behavior during conflict resolution |
| `feat/field-navigation-baseline` | divergent feature line | selective port in P1-06 | do not merge complete history |
| `feat/nav2-planner-smoke-harness` | older planner smoke line | freeze | superseded by later headland smoke line |
| `feat/headland-planner-smoke` | planner acceptance tooling | selective port later only if required | never a production navigation dependency |
| `feat/bunker-rtabmap-slope-nav` | alternate/experimental navigation line | defer/freeze | do not enter current product line |
| `feat/inspection-multiview-evidence` | divergent inspection line | selective port in P1-10 | only after navigation convergence is accepted |
| V3 historical acceptance branches | historical slices | freeze | retain traceability only |

## 3. Merge rules

### Rule A — one canonical implementation branch

All new P1 production commits go to:

```text
feat/runtime-navigation-convergence-p1
```

Do not create another navigation convergence feature line unless this branch becomes unrecoverable.

### Rule B — merge only same-generation architecture branches

`feat/runtime-site-owner-p01` may be integrated because it is a convergence-era runtime subsystem with a clear ownership boundary.

During conflict resolution, retain all of these authorities:

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

- source branch
- source commit(s)
- files/behavior ported
- behavior intentionally not ported
- compatibility changes made for current contracts
- tests proving the ported behavior

### Rule D — no new navigation algorithm work inside convergence

P1 is not a place to add new localization/planner/controller stacks. Algorithm changes require a separate future milestone after P1 acceptance.

## 4. Canonical ownership after P1

```text
agt_site_runtime
  owns: deployed Site discovery / validation / active Site authority

agt_site_navigation (planned)
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
  owns: mutable versioned task definitions below tasks_root
```

## 5. Expected runtime data flow

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

Task editing remains outside immutable Site assets:

```text
HMI / Gateway
  -> Task Registry
  -> runtime/tasks/<site>/<revision>/<task>.json
```

## 6. P1 acceptance invariants

The following must remain true throughout implementation:

1. There is exactly one canonical `map -> odom` authority.
2. Runtime never navigates against a map that is still being commissioned/generated.
3. Unknown or stale readiness evidence is never treated as success.
4. A task cannot execute against a different Site identity/revision/hash than the one it was validated for.
5. Site activation never silently falls back to another revision.
6. Production direct RViz pose goals are disabled by default.
7. No new component bypasses Collision Monitor, `agt_safety`, chassis guard or Mission ownership.
8. Software acceptance and real-vehicle acceptance are recorded separately.

## 7. Per-slice documentation template

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

## 8. Merge-to-main gate

Do not merge this convergence branch to `main` merely because source code exists.

Minimum software merge gate:

- P1-02 through P1-08 complete
- current branch builds on ROS 2 Humble
- selected/full regression has zero failures in changed Runtime packages
- exact Site activation -> localization binding -> Nav2 lifecycle -> SystemManager readiness smoke passes
- no old parallel branch is required at runtime
- documentation identifies any remaining real-hardware-only gates

Preferred field release gate additionally requires P1-09.

Inspection integration P1-10 may either be included before main merge or follow immediately after navigation release, but it must not destabilize the accepted navigation ownership model.

## 9. Next action

Next slice after design approval:

```text
P1-02 — integrate feat/runtime-site-owner-p01
```

Before resolving any conflict, compare the branch against the P1 base and preserve Gateway/hardware changes. After integration, run the Site/runtime contract, SystemManager, Gateway and hardware no-ROS regression set before starting P1-03.
