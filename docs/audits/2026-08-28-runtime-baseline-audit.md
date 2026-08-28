# Runtime Baseline Audit — 2026-08-28

## Scope

This audit selects the integration baseline for the operator-HMI/runtime convergence work and records the blocking gaps that must be closed before a real gateway is treated as a product boundary.

## Selected baseline

Baseline branch: `v3-03/acceptance-freeze`

Baseline commit: `e62261a57cc4bd16448526e31d9897a0ef48a577`

Reasons:

- V3-02 formally separated continuous odometry from offline mapping and removed runtime `agt_mapping` ownership.
- V3-03 formally accepted the navigation/safety/chassis execution chain.
- The baseline has recorded local ROS 2 Humble build/test evidence and green Runtime Contracts CI.
- Later feature branches (`feat/bunker-rtabmap-slope-nav`, `feat/inspection-multiview-evidence`, `feat/headland-planner-smoke`) diverge from an older `main` and must not replace the accepted V3 execution baseline wholesale.

`v3-04/build-warning-cleanup` is a useful source for later MK-mini work but is not required for the BUNKER/operator integration spine. Its own acceptance record still marks full-workspace clean build after simulator integration and physical vehicle acceptance as pending.

## Package maturity summary

| Area | Rating | Audit result |
| --- | --- | --- |
| Runtime contracts / Site + Vehicle schema | A- | Strong fail-closed schemas and validation. |
| Description / TF | B+ | Clear ownership; final hardware extrinsics still require acceptance. |
| Sensor adapters | B | MID360 and self-filter integration exist; physical rate/QoS/loss acceptance remains. |
| Sensor monitor | B | Structured health evidence exists; product-level aggregator is missing. |
| `agt_odometry` | A- | Accepted V3 owner, tested adapter math, canonical odom/cloud contract. |
| `agt_localization` | B+ | Substantial relocalization/tracking implementation; final map/extrinsic/recovery acceptance remains. |
| `agt_localization_fusion` | D | Boundary only; no production fusion implementation. |
| `agt_perception` | C+ | Height/range geometry filter baseline only; slope/negative-obstacle robustness not established. |
| Nav2 runtime | B+ | Planner/controller/collision chain is structurally mature. |
| Waypoint capability integration | C | Rich implementation, but safety diagnostic producer/consumer contract is inconsistent. |
| `agt_safety` | B | Good fail-closed logic; cross-package status-name bug blocks real waypoint readiness. |
| BUNKER chassis | B | Clean generic/backend split; physical braking/CAN takeover acceptance remains. |
| Mission manager | B | Strong bounded mission semantics, but depends on missing runtime providers. |
| BT executor | B- | Valid optional capability bridge; not the product state owner. |
| Experiment manager | B+ | Good session, interruption and explicit-bag ownership. |
| Active Site/Map runtime owner | D | Interfaces exist; production activation/provider path is not closed. |
| System manager / RobotState owner | D | Interfaces exist; production aggregation/provider is missing. |
| Unified bringup | C- | Experimental branches contain bringup work, but stable V3 convergence is incomplete. |
| CI integration coverage | C+ | Source contracts are useful; producer/consumer ROS integration coverage is incomplete. |

## P0 blocker 1 — safety diagnostic contract mismatch

Production safety publishes a `DiagnosticStatus` named:

```text
agt_safety/controller
```

The waypoint task server currently searches for:

```text
agt_safety/tracked_controller
```

Its existing unit fixture also uses the obsolete name, so package-local tests can pass while the real producer and consumer disagree. With `require_safety_ready:=true`, a real waypoint task can remain fail-closed even when the safety controller is healthy.

Required convergence action:

- make `agt_safety/controller` the canonical status name for the generic V3 safety controller;
- make waypoint execution consume the same contract;
- add a cross-package regression that reads both production files rather than recreating the old fixture contract.

## P0 blocker 2 — missing system-manager product spine

The repository already defines `SystemHealth`, `TaskReadiness`, `RobotState`, `GetSystemHealth`, `EvaluateTaskReadiness`, and `GetRobotState`, but there is no production `agt_system_manager` owner in the accepted V3 source tree.

The operator gateway must not infer readiness from arbitrary ROS topics. Runtime must publish authoritative read models first.

Required P0 outputs:

```text
/agt/system/health
/agt/system/task_readiness
/agt/system/robot_state
/agt/system/health/get
/agt/system/task_readiness/evaluate
/agt/system/robot_state/get
```

P0 readiness is deliberately narrow and fail-closed. Navigation task readiness requires fresh/valid evidence for:

- system required health;
- active READY map identity;
- accepted TRACKING localization bound to that map;
- safety motion enabled with no emergency-stop latch;
- connected chassis.

Unknown or stale required evidence is a blocker, never an implicit READY state.

## Deferred to the next convergence slice

The following are intentionally not folded into this P0 change:

1. Production Site/Map runtime loader and `/agt/maps/active` owner.
2. Stable unified BUNKER bringup composed on top of `agt_odometry` rather than the old experimental `agt_mapping` launch.
3. GNSS/LIO/wheel fusion implementation.
4. Terrain/traversability algorithm upgrades.
5. Operator gateway and HMI write/control commands.

These are sequenced after the P0 safety + system-state spine so later layers consume one authoritative Runtime contract instead of duplicating decisions.

## Acceptance target for this convergence slice

The slice is accepted when:

- the cross-package safety diagnostic regression fails on the baseline and passes after the fix;
- `agt_system_manager` has a ROS-independent readiness core with fail-closed unit coverage;
- the ROS node publishes the three authoritative read models and exposes the three read services;
- CI runs on `feat/runtime-convergence-*` and executes the new source/core regressions;
- no existing V3 contract, odometry, execution or MK-mini pure test is removed or weakened.
