# P1-06 Field Commissioning Acceptance — 2026-08-29

## Decision

```text
IMPLEMENTED:       PASS
STATIC / CI:       PASS
ROS 2 HUMBLE:      NOT RUN ON CANONICAL P1 BRANCH
REAL VEHICLE:      NOT RUN
```

P1-06 is complete at source/unit/cloud-contract level. It selectively ports the useful BUNKER + MID360 field commissioning workflow from `feat/field-navigation-baseline` into the canonical Runtime architecture without merging the divergent branch wholesale.

P1-06 does **not** claim ROS 2 Humble execution, BUNKER/MID360 field motion acceptance, or production RViz direct-goal acceptance.

## Source

- Canonical branch: `feat/runtime-navigation-convergence-p1`
- Source branch selectively inspected: `feat/field-navigation-baseline`
- P1-06 code/docs head before this acceptance note: `2f9a381070a418c9fea444df7523fd01d638884f`
- RED Runtime Contracts: run `#341` (`33241740091`), expected isolated commissioning failure
- GREEN Runtime Contracts: run `#347` (`33241896575`), PASS

No parallel implementation branch was created.

## TDD / CI evidence

### RED

At head `b751cc355e1bacf2176314f3d07f5c6d92707d97`, Runtime Contracts run `#341` (`33241740091`) failed only in the newly connected P1 commissioning group:

```text
P1 field commissioning: 4 failed, 20 passed
```

The four expected failures were:

- `docs/runbooks/field-navigation-commissioning.md` did not yet exist;
- the dedicated `field_mapping_commissioning` bag profile did not yet exist.

All existing groups remained green in the same RED run:

```text
V3-01 contracts:        19 passed
V3-02 odometry:          9 passed
V3-03 execution:        18 passed
SystemManager:          36 passed
Site Runtime owner:     45 passed
P1 task-storage:        52 passed
P1 site-navigation:     26 passed
```

This isolated the new P1-06 contract without introducing an unrelated regression.

### GREEN

At head `2f9a381070a418c9fea444df7523fd01d638884f`, Runtime Contracts run `#347` (`33241896575`) completed successfully.

Fresh job-log counts:

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

The P1 commissioning group itself reported `24 passed`.

## Implemented

### 1. Dedicated commissioning package

New package:

```text
src/agt_field_commissioning/
```

It owns commissioning entry points only. It does not become a new Site owner, localization owner, Nav2 lifecycle owner, TF authority, task owner or rosbag recorder owner.

### 2. Phase A FAST-LIVO2 mapping entry point

Entry point:

```text
ros2 launch agt_field_commissioning field_mapping.launch.py
```

The launch:

- reuses the current `agt_hardware_bringup/bunker_mid360.launch.py` hardware composition;
- starts FAST-LIVO2 mapping directly for commissioning;
- enables PCD persistence only in this commissioning launch;
- keeps `pcd_save.interval=-1` for final shutdown save;
- writes below one unique mutable run root:
  `runtime/commissioning/<site_id>/<run_id>/mapping/`;
- refuses reuse of an existing non-empty mapping directory;
- remaps registered points to `/agt/commissioning/mapping/registered_points`;
- does not start localization or Nav2.

The normal Runtime FAST-LIVO2 odometry launch remains persistence-disabled.

### 3. Mapping artifact finalization

Entry point:

```text
ros2 run agt_field_commissioning finalize_mapping_run.py
```

The finalizer fail-closes unless the run contains:

```text
localization_map.pcd
localization_map.processing.yaml
```

It also rejects leftover `*.tmp` files and atomically writes SHA256 evidence to:

```text
runtime/commissioning/<site_id>/<run_id>/evidence/mapping_metadata.json
```

Commissioning identifiers are validated without silently trimming or rewriting malformed IDs.

### 4. ExperimentManager remains the only recorder owner

P1-06 adds one explicit profile to:

```text
src/agt_experiment_manager/config/bag_profiles.yaml
```

Profile:

```text
field_mapping_commissioning
```

It records the dedicated commissioning mapper evidence topic:

```text
/agt/commissioning/mapping/registered_points
```

plus the required raw/filtered LiDAR, IMU, chassis, TF and diagnostics evidence.

It deliberately does not treat normal Runtime `/agt/odometry/registered_points` or `/agt/map/mapping_occupancy` as commissioning mapper evidence. `agt_experiment_manager` remains the sole record/playback process owner.

### 5. Offline reconstruction boundary remains external

P1-06 does not add a hidden Runtime PCD-to-PGM/map reconstruction pipeline.

The flow is explicitly:

```text
mutable commissioning source/evidence
  -> external offline reconstruction/export
  -> complete Site Package 1.0
```

The Runtime consumes only the exported Site contract. It never promotes a raw commissioning PCD directly into navigation authority.

### 6. Immutable Site deployment and explicit activation

The runbook freezes the correct current Site Runtime sequence:

```text
export Site Package 1.0
  -> deploy new revision under sites_root
  -> /agt/maps/validate
  -> /agt/maps/activate
  -> /agt/maps/active
```

A plan-era assumption about an `expected` activation lock was corrected during implementation because the current canonical `ActivateMapVersion.srv` uses:

```text
map_id
map_version_id
client_request_id
```

The actual `SiteRuntimePolicy.activate()` re-runs full deployed-Site validation before persisting the active selection. The acceptance therefore records the current implementation rather than inventing a stale interface.

Similarly, `/agt/maps/validate` is correctly run **after deployment**, because Site Runtime validates candidates under `sites_root`.

### 7. Frozen-Site Phase C navigation entry point

Entry point:

```text
ros2 launch agt_field_commissioning field_navigation.launch.py
```

Phase C requires an exact persisted Active Site selection and re-runs the canonical Site validator. It derives the navigation/localization asset paths and hashes from the immutable deployed Site and injects those values into the current localization/Nav2 stack.

Operator-provided launch arguments such as:

```text
global_map_pcd
navigation_map
```

are intentionally absent. There is no fallback to `runtime/commissioning/...` map assets.

The composed stack keeps the existing authorities:

```text
agt_site_runtime
agt_site_navigation
agt_hardware_bringup
agt_odometry
agt_localization + GlobalCorrectionManager
agt_safety
agt_navigation / Nav2
agt_system_manager
```

### 8. Field commissioning runbook

New runbook:

```text
docs/runbooks/field-navigation-commissioning.md
```

It freezes the ordered operator flow:

```text
Phase A mapping
  -> explicit field_mapping_commissioning bag
  -> normal Ctrl+C / ROS shutdown
  -> finalize_mapping_run.py
  -> offline reconstruction/export
  -> Site Package 1.0
  -> deploy under sites_root
  -> /agt/maps/validate
  -> /agt/maps/activate
  -> Phase C navigation
```

It explicitly states:

```text
commissioning output is mutable
Site Package is immutable
changing tasks never rebuilds the Site Package
do not navigate directly from commissioning output
```

### 9. CI coverage

`.github/workflows/runtime-contracts.yml` now includes:

```text
tests/commissioning/**
src/agt_field_commissioning/**
docs/runbooks/field-navigation-commissioning.md
```

and executes `tests/commissioning` with the required Python module paths.

## Ownership / safety invariants preserved

P1-06 preserves all of the following:

```text
agt_experiment_manager
  sole rosbag record/playback process owner

agt_site_runtime
  sole deployed Site validation/activation authority

agt_site_navigation
  Site binding + read-only navigation runtime evidence

agt_localization + GlobalCorrectionManager
  unique map -> odom correction authority

Nav2 lifecycle manager
  lifecycle transition authority

agt_navigation
  planning/control/BT/waypoint/collision-monitor capability

agt_system_manager
  final fail-closed readiness aggregate
```

P1-06 does not add another TF broadcaster, planner, controller, localization algorithm, lifecycle transition owner, task store, Mission executor or map writer in the normal Runtime path.

## Intentionally not accepted in P1-06

P1-06 does **not** close:

- ROS 2 Humble build/launch/runtime regression — P1-08;
- production RViz direct-goal guarding — P1-07;
- real BUNKER + MID360 navigation motion acceptance — P1-09;
- inspection capability integration — P1-10;
- online map mutation or hot Site switching during a Mission;
- RTAB-Map production navigation;
- new planner/controller/localization algorithms.

## Gate state

```text
P1-06 Code   [x]
P1-06 STATIC [x]
P1-06 HUMBLE [ ]
P1-06 FIELD  [ ]
```

This gate state is based on run `#347` for the code/docs head before this acceptance record. The canonical branch head still requires a fresh post-document Runtime Contracts run before the acceptance status is considered final-head verified.
