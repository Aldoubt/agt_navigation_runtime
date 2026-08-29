# P1-02 Site Runtime Integration Acceptance — 2026-08-29

## Decision

```text
IMPLEMENTED:       PASS
STATIC / CI:       PASS
ROS 2 HUMBLE:      NOT RUN ON CANONICAL P1 BRANCH
REAL VEHICLE:      NOT RUN / NOT REQUIRED FOR P1-02
```

P1-02 is complete at the software-source and cloud-contract level. It is **not** yet a ROS 2 Humble runtime acceptance and must not be described as field-verified.

## Source

- Canonical branch: `feat/runtime-navigation-convergence-p1`
- P1-02 pre-integration plan head: `d74e92bfa167eeb2ea97ecdfc4fdfce311930a2c`
- Imported source branch: `feat/runtime-site-owner-p01`
- Imported source head: `3969b152157e20dddd479fb08f95a694aeb08681`
- Integration PR: `#3`
- Integration merge commit: `60bf00e530b6e975fbb91cb62974a79573b6f678`
- Canonical CI coverage commit: `b81fe907467c79def190e3eec893cea52e99fb6f`

## Implemented

P1-02 integrates the accepted Site Runtime ownership slice into the single P1 navigation convergence line while preserving the hardware/Gateway baseline.

Integrated capabilities:

- installable `agt_runtime_contracts` package;
- `agt_site_runtime` package;
- `ValidateMapVersion.srv`;
- deployed Site list / validate / explicit activate services;
- authoritative transient-local `/agt/maps/active` publication;
- persisted active Site identity with validation on restart;
- UNKNOWN tombstone semantics when stale active authority must be revoked;
- SystemManager interpretation of the authoritative active Site;
- repository Runtime Contract tooling compatibility through the installable contract library;
- Site Runtime source/contract tests in Runtime Contracts CI.

The canonical Runtime Contracts workflow now also runs on:

```text
feat/runtime-navigation-convergence-*
```

so subsequent P1 commits are continuously checked on the actual convergence branch.

## Merge audit

The Site-owner source line was compared against the hardware baseline before merge. The integration delta relative to `feat/hardware-bringup-p0` contains Site Runtime, Runtime Contract, interface, SystemManager and documentation/test files only.

No production files under these inherited authorities were removed or replaced by P1-02:

```text
agt_hardware_bringup
agt_operator_gateway
```

The canonical branch remains a strict descendant of the hardware baseline (`behind_by = 0`).

Key overlap resolution was additive:

- `agt_interfaces/CMakeLists.txt`: register `ValidateMapVersion.srv` without removing existing interfaces;
- `agt_system_manager/readiness.py`: add authoritative-map tombstone interpretation;
- `system_manager_node.py`: use that interpretation while retaining existing readiness inputs/services;
- `tools/runtime_contracts/validator.py`: preserve repository import compatibility while delegating canonical validation to the installable package;
- `runtime-contracts.yml`: add Site Runtime coverage without deleting prior V3/SystemManager stages.

## Intentionally not implemented

P1-02 does **not** implement or modify:

- P1-03 mutable Task Registry relocation;
- P1-04 Active Site -> localization/Nav2 asset binding;
- P1-05 Nav2 lifecycle / NavigationRuntimeStatus aggregation;
- P1-06 field commissioning migration;
- P1-07 production RViz direct-goal guard;
- P1-09 real BUNKER/MID360 acceptance;
- P1-10 inspection capability migration.

`agt_site_runtime` remains a deployment registry/activation owner only. It does not generate maps, start Nav2, publish `map -> odom`, execute Missions, or mutate Site assets.

## Interface changes

Added service interface:

```text
agt_interfaces/srv/ValidateMapVersion.srv
```

Site Runtime authoritative APIs retained from the accepted source slice:

```text
/agt/maps/active
/agt/maps/list
/agt/maps/validate
/agt/maps/activate
```

SystemManager remains a read-model consumer of `/agt/maps/active`; it does not call activation services.

## Test evidence

### Static / cloud CI

#### Integration PR

PR `#3` source head `3969b152157e20dddd479fb08f95a694aeb08681`:

- Runtime Contracts run `#247` (`33236264032`): **PASS**
- `operator-gateway-no-ros` run `#42` (`33236264033`): **PASS**

Runtime Contracts run #247 completed these relevant steps successfully:

```text
V3-01 contract tests
V3-02 odometry source contracts
V3-03 execution source contracts
runtime system-manager contracts
runtime site-owner contracts
```

#### Canonical P1 branch

After adding the canonical branch push filter:

- Runtime Contracts run `#248` (`33236291925`): **PASS**
- head: `b81fe907467c79def190e3eec893cea52e99fb6f`

Run #248 completed all of the following with conclusion `success`:

```text
Run V3-01 contract tests
Run V3-02 odometry source contracts
Run V3-03 execution source contracts
Run runtime system-manager contracts
Run runtime site-owner contracts
```

### Hardware bringup regression

No `agt_hardware_bringup` production file changed in the P1-02 delta relative to `feat/hardware-bringup-p0`. Its no-ROS suite was therefore not artificially retriggered by modifying hardware files. The hardware baseline remains inherited unchanged; real hardware verification remains a later P1 gate.

### ROS 2 Humble

`NOT RUN` on the canonical P1 branch in this cloud-only integration step.

The imported Site-owner acceptance document itself also records its ROS 2 Humble build/test and ROS graph/runtime smoke as pending local evidence. P1-08 will close the consolidated Humble regression; it may be run earlier without changing this separation of evidence.

Recommended narrow local gate when a Humble workstation is available:

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install --packages-select \
  agt_interfaces \
  agt_runtime_contracts \
  agt_site_runtime \
  agt_system_manager

source install/setup.bash
colcon test --packages-select \
  agt_interfaces \
  agt_runtime_contracts \
  agt_site_runtime \
  agt_system_manager \
  --event-handlers console_direct+

colcon test-result --verbose
```

Hard gate: zero build failures and zero test failures.

### Real vehicle

`NOT RUN` and not required by P1-02.

## Known blockers / follow-up

1. Canonical P1 has not yet been rebuilt on a ROS 2 Humble workstation after this merge.
2. Active Site currently establishes authoritative deployment identity, but does not yet bind concrete localization/Nav2 assets; that is P1-04.
3. Task Registry still uses the old mutable-under-map layout; that is the immediate next slice P1-03.

## Handoff

P1-02 is accepted for continuation as:

```text
CODE:   COMPLETE
STATIC: PASS
HUMBLE: PENDING
FIELD:  N/A
```

The next and only development slice is:

```text
P1-03 — decouple Task Registry from immutable Site assets
```
