# V3-02 Odometry / Localization Separation Design

## Status

Approved implementation direction for V3-02

## Goal

Replace the V2.5-derived `agt_mapping` runtime role with an explicitly runtime-only `agt_odometry` package while preserving FAST-LIVO2 behavior and the existing `odom -> base_footprint` ownership contract.

V3-02 is a responsibility and interface migration. It is not an algorithm change.

## Current Problem

The current `agt_mapping` package mixes two meanings:

1. runtime state estimation
   - adapt FAST-LIVO2 odometry
   - convert the backend IMU pose to `base_footprint`
   - publish continuous odometry
   - publish registered point cloud
   - own `odom -> base_footprint`
2. mapping / asset production
   - expose `save_pcd`
   - expose `pcd_save_interval`
   - expose `pcd_output_dir`
   - validate a PCD output directory
   - document `localization_map.pcd` production

The second group belongs to the V2.5 asset-production repository and conflicts with the frozen V3 boundary.

The current public topics are also named under `/agt/mapping/*`, even though runtime consumers use them as continuous odometry/state-estimation outputs.

## Considered Approaches

### A. Rename `agt_mapping` in place

Rename the directory/package/topics immediately and update all consumers in one commit.

Advantages:
- shortest final diff
- no temporary duplicate package

Disadvantages:
- no behavior-parity checkpoint
- package/topic migration and behavior changes are mixed
- harder to prove that the old and new adapters are equivalent

### B. Permanent compatibility wrapper

Add `agt_odometry`, retain `agt_mapping` as a compatibility wrapper indefinitely, and dual-publish old/new topics.

Advantages:
- safest for unknown external consumers
- old launch commands keep working

Disadvantages:
- V3 permanently carries a misleading mapping package
- duplicate topics create ownership ambiguity
- extends migration debt into later milestones

### C. Staged replacement, then remove legacy package

Add `agt_odometry` alongside `agt_mapping`, prove adapter behavior parity, migrate every in-repository consumer, then delete `agt_mapping` before V3-02 closes.

Advantages:
- preserves a comparison point during migration
- final repository has one owner and one canonical topic namespace
- keeps the final package count unchanged
- matches the V3 runtime boundary

Disadvantages:
- more commits than an in-place rename

**Selected: C.**

## Final Package Responsibility

`agt_odometry` owns continuous local state estimation backend adaptation.

It may:
- launch a selected continuous odometry backend
- adapt backend-native frames/topics into AGT runtime contracts
- publish canonical odometry
- publish the current registered point cloud
- publish the unique `odom -> base_footprint` transform
- configure runtime LiDAR self-filter input

It must not:
- save or accumulate global PCD maps
- produce `localization_map.pcd`
- create mapping sessions
- generate map metadata or map versions
- own Site Package assets
- expose mapping-mode switches

## Canonical Runtime Interface

### Public topics

```text
/agt/odometry/odometry
/agt/odometry/registered_points
```

### Backend-private topics

```text
/agt/odometry/backend/registered_points
```

`/aft_mapped_to_init` remains a FAST-LIVO2 backend-native input to the adapter and is not an AGT public contract.

### Frames

```text
odom -> base_footprint
```

`agt_odometry` remains the unique owner of this transform while the FAST-LIVO2 backend is active.

Global `map -> odom` remains owned by localization/global correction and is outside `agt_odometry`.

## FAST-LIVO2 Runtime Launch

The new launch entry is:

```text
agt_odometry/fast_livo2_odometry.launch.py
```

It launches:
- optional LiDAR self-filter
- FAST-LIVO2 backend
- `agt_odometry_fast_livo2_adapter`

The launch does not expose:

```text
save_pcd
pcd_save_interval
pcd_output_dir
```

It forces backend PCD saving off for runtime use.

The backend registered cloud is remapped to:

```text
/agt/odometry/backend/registered_points
```

The adapter republishes the same continuous world-coordinate points with frame `odom` on:

```text
/agt/odometry/registered_points
```

No second geometric transform is applied to point data.

## Adapter Behavior Parity

The mathematical behavior of the current adapter is preserved:

- normalize backend orientation quaternion
- apply base-to-sensor extrinsic inverse to recover base pose
- account for the sensor lever arm in twist conversion
- support equal backend/base frames with an in-process identity transform
- publish `Odometry` with parent `odom` and child `base_footprint`
- optionally broadcast the same pose as TF

V3-02 does not change these equations.

## Consumer Migration

All in-repository consumers move from `/agt/mapping/*` to `/agt/odometry/*` in the same milestone.

Known consumer categories include:
- `agt_localization` relocalization cloud input
- `agt_perception` local obstacle cloud input
- experiment recording topic profiles
- route/navigation smoke utilities that synthesize or subscribe to odometry
- V2.5-named validation utilities retained in the extracted runtime
- README/config/launch documentation

All package-level references to `agt_mapping` are migrated to `agt_odometry` where they represent runtime state estimation.

Historical text that explicitly describes V2.5 provenance may retain the word `mapping`, but executable package/topic dependencies may not.

## Migration Sequence

### Phase 1. Establish tests and new package

Create `agt_odometry` from the runtime-only portions of `agt_mapping`.

Before modifying adapter math, run the same unit vectors against both modules and require identical results.

### Phase 2. Establish new topic contract

Change only the new package defaults/config/launch to `/agt/odometry/*`.

Keep the legacy package present during this checkpoint so differences can be inspected.

### Phase 3. Migrate consumers

Update all runtime consumers and tests to the new package/topic contract.

Repository-wide checks must show no executable/config dependency on `/agt/mapping/`.

### Phase 4. Remove mapping production and legacy package

Delete `src/agt_mapping` after consumer migration passes.

No compatibility dual-publisher is retained in the final V3-02 tree.

## Fail-Closed Rules

The runtime launch must not silently enable PCD saving.

The new package does not accept a PCD output directory because asset production is not a valid runtime behavior.

If the static `base_footprint -> backend_body_frame` transform is unavailable, the adapter keeps the existing behavior: do not emit a converted odometry sample and warn while waiting for TF.

## Testing Strategy

### Unit tests

Preserve and migrate the existing adapter math tests:
- translation extrinsic
- orientation extrinsic
- zero quaternion rejection
- lever-arm twist correction
- equal-frame identity behavior

### Contract tests

Add source-level tests that assert:
- package name is `agt_odometry`
- canonical outputs use `/agt/odometry/*`
- runtime launch contains no PCD-save launch arguments
- FAST-LIVO2 PCD save is forced false
- no runtime config uses `/agt/mapping/`
- no runtime package depends on `agt_mapping`

### Build acceptance

From an environment containing only ROS 2 Humble as the workspace prefix:

```bash
rm -rf build install log
colcon build --symlink-install
```

Expected final result:

```text
23 packages finished
```

The package replacement is one-for-one: add `agt_odometry`, remove `agt_mapping`.

### Runtime smoke acceptance

When hardware/bag input is available, verify:
- `/agt/odometry/odometry` publishes
- child frame is `base_footprint`
- `/agt/odometry/registered_points` publishes with frame `odom`
- exactly one `odom -> base_footprint` publisher exists
- localization consumes the new registered cloud
- perception consumes the new registered cloud

Hardware/bag smoke is not replaced by source-level tests, but V3-02 source/build acceptance does not require changing FAST-LIVO2 algorithm behavior.

## Non-Goals

V3-02 does not:
- add wheel odometry fusion
- add GNSS fusion
- change ICP/NDT relocalization
- tune FAST-LIVO2
- change Nav2 planner/controller parameters
- implement Site Manager
- implement unified bringup
- redesign `map -> odom` authority
- rename the global `odom` frame

## Completion Criteria

V3-02 is complete when:

1. `agt_odometry` is the only runtime package owning continuous odometry adaptation
2. `agt_mapping` is absent from the final source tree
3. public runtime topics are `/agt/odometry/odometry` and `/agt/odometry/registered_points`
4. PCD-saving controls are absent from the V3 odometry launch
5. in-repository runtime consumers use the new contract
6. adapter unit tests pass
7. migration contract tests pass
8. V3-01 contract tests still pass
9. an independent ROS 2 Humble build finishes the same 23 packages
