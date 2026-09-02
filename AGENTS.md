# AGT Navigation Runtime Agent Guide

This file defines hard constraints for Codex and other agentic developers working on the RTAB-Map inspection MVP in `agt_navigation_runtime`.

## Active Integration

- Branch: `feat/rtabmap-inspection-mvp`
- Base at branch creation: `main@d433e3022bb8c7c6b6b13b5e9752882a63cedced`
- Primary design/status document: `RTABMAP_INSPECTION_MVP.md`
- Phase prompts: `docs/rtabmap-inspection-mvp/CODEX_PHASE_PROMPTS.md`
- Implementation plan: `docs/superpowers/plans/2026-09-02-rtabmap-inspection-mvp.md`

## Mission

Reach the shortest reproducible data chain from an existing MID360 rosbag to:

```text
MID360 CustomMsg + MID360 IMU
          -> RTAB-Map ICP odometry
          -> RTAB-Map mapping / localization
          -> optional RTK global prior
          -> Nav2 execution
          -> camera inspection evidence
```

The MVP favors interface stability, observable experiments, minimal changes, and recoverable commits over broad refactoring.

## Repository Boundary

`agt_navigation_runtime` owns runtime integration and robot execution. It does not own the internal implementation of external device packages.

External repositories remain independent:

- `Aldoubt/agt_ins_driver`: owns ASENSING parser, GNSS/INS ROS semantics, RTK status, GNSS timestamp policy, antenna frame semantics, and future lever-arm correction capability.
- `Aldoubt/agt_robot_hmi`: owns Qt operator UI, map display/editing, task editing, and operator-facing workflow.
- `Aldoubt/Autolabor-C1-ROS2`: owns camera/gimbal hardware and the stable `AcquireView` acquisition capability.

Runtime may consume their public ROS contracts. Do not copy their implementation into this repository.

## Frozen Responsibility Split

```text
RTAB-Map              = online SLAM backend, graph and localization
agt_mapping           = backend abstraction and standardized mapping outputs
agt_sensor_adapters   = sensor-format adaptation only
agt_perception        = local obstacle cloud for Nav2/collision safety
agt_navigation        = Nav2 planner/controller/costmaps
agt_safety            = velocity safety arbitration
agt_chassis           = BUNKER hardware execution
agt_mission_manager   = navigation/camera task orchestration
agt_robot_hmi         = operator/map/task UI in its own repository
agt_ins_driver        = GNSS/INS capability in its own repository
Autolabor-C1-ROS2     = camera/gimbal capability in its own repository
```

Do not create a new monolithic package that duplicates these responsibilities.

## Mapping Backend Rule

`agt_mapping` already abstracts the mapping/continuous-odometry backend. Add RTAB-Map as another backend under this boundary instead of deleting or renaming the FAST-LIVO2 baseline.

Public contracts should remain backend-neutral where practical:

- `/agt/mapping/odometry`
- `/agt/mapping/registered_points`
- `map -> odom`
- `odom -> base_footprint`

Do not make Nav2, HMI, mission code, or camera code depend on RTAB-specific internal topics when a standardized runtime interface can be used.

## FAST-LIVO2 Baseline

FAST-LIVO2 remains a regression/reference backend during this MVP.

Never:

- delete FAST-LIVO2 code or configuration merely because RTAB-Map is added;
- silently change the existing FAST-LIVO2 topic contract;
- reuse a FAST-LIVO2-only assumption as a generic mapping contract;
- claim RTAB-Map has replaced FAST-LIVO2 until the MVP acceptance gates pass.

## TF Authority: Hard Rule

There must be exactly one authority for each dynamic transform.

Target ownership for the RTAB path:

```text
map -> odom
  RTAB-Map only

odom -> base_footprint
  RTAB ICP odometry only

base_footprint -> base_link
base_link -> mid360_link
base_link -> rtk_antenna_link
base_link -> camera/gimbal frames
  robot_description / static TF only
```

Do not enable vendor wheel-odometry TF simultaneously with the RTAB odometry TF. Wheel odometry may remain a message source, but must not become a competing transform authority unless the architecture is explicitly redesigned.

Before any TF change, run and record a TF-tree inspection. A duplicate TF authority is a blocking defect.

## MID360 Data Rule

The raw Livox `CustomMsg` is the archival/source representation. Do not reduce it to a plain XYZI cloud for convenience.

A PointCloud2 adapter used by RTAB must preserve, where present:

- x, y, z;
- reflectivity/intensity;
- tag;
- line;
- per-point time relative to the packet/header time.

The adapter must document the output time-field name, type, unit, epoch/relative meaning, and relation to `header.stamp`.

Do not modify upstream Livox messages unless necessary. Prefer a thin adapter in `agt_sensor_adapters`.

## MID360 IMU Rule

MID360 raw IMU can support orientation estimation, gravity constraints, ICP motion guess, and point-cloud deskewing.

Do not describe the RTAB path as tightly coupled LIO. ICP remains the primary local geometric odometry in this MVP.

If raw IMU lacks a valid orientation quaternion, add/use an orientation filter through configuration/launch before passing it to RTAB. Do not invent magnetometer data. Any yaw behavior without an absolute heading source must be documented as relative/drifting.

## RTK Boundary

Runtime must not fix ASENSING protocol/parser issues. Those changes belong in `Aldoubt/agt_ins_driver` on its dedicated workstream.

Runtime consumes, initially:

- `/ins/navsatfix` (`sensor_msgs/msg/NavSatFix`)
- `/ins/status` (`agt_asensing_driver/msg/INSStatus`)

Phase-1 runtime must not depend on `/ins/odom`, `/ins/velocity`, or `/ins/pose` for navigation until their coordinate/frame semantics are explicitly accepted by the RTK repository.

The RTK repository is intentionally UNFROZEN during development. Freeze interfaces first; freeze a SHA only after its own acceptance gates pass.

## RTK Lever Arm Rule

`base_link -> rtk_antenna_link` must be represented in robot geometry/configuration once measured.

Do not assume RTAB automatically compensates GNSS antenna lever arm through `NavSatFix.header.frame_id`. If explicit compensation is introduced later, it must be optional and based on a verified orientation convention. Do not implement antenna-to-base correction by guessing yaw/NED/ENU conventions.

## HMI Boundary

The HMI should remain backend-neutral.

Use two distinct map artifacts:

```text
*.db
  RTAB graph/localization database; never edited by HMI.

*.pgm + *.yaml
  exported navigation occupancy map; may be edited by HMI and served to Nav2.
```

Do not write HMI occupancy edits back into the RTAB graph/database.

Do not make the HMI directly own BUNKER safety or RTAB graph logic.

## Navigation and Safety Boundary

Reuse the existing Nav2 and BUNKER safety chain unless a measured failure requires a focused change.

Do not bypass:

- local obstacle perception;
- Nav2 collision monitoring;
- safety command arbitration;
- chassis command watchdogs.

Do not replace SmacPlanner2D/MPPI merely as part of the RTAB integration.

Local obstacle perception should remain independent of RTAB map publication rate. For the no-FAST-LIVO path, prefer a correctly transformed raw/enhanced MID360 PointCloud2 source for the local obstacle pipeline.

## Camera Boundary

Mission code calls the public camera/gimbal acquisition interface from `Autolabor-C1-ROS2`. Do not move mission sequencing into the camera driver.

Use the returned image timestamp as the evidence timestamp. At that timestamp, record the nearest/appropriate:

- `map -> base_link` or `map -> base_footprint` pose;
- GNSS fix/status sample;
- actual gimbal angles;
- image path and waypoint/task identifiers.

## Experiment Discipline for SLAM

SLAM work is not accepted by `colcon build` alone.

Every phase that changes sensor, odometry, mapping, localization, or navigation behavior must produce an experiment record containing at least:

- git commit under test;
- rosbag identifier/path (path may be local-only, but bag identity must be reproducible);
- bag duration;
- input topic names/types/rates;
- parameters/config files used;
- output topic rates;
- TF ownership/tree summary;
- lost/reinitialization/jump observations;
- RTAB database size and graph/node/loop information when applicable;
- RTK received/accepted status when applicable;
- PASS/FAIL and known limitations.

Store records under:

`docs/rtabmap-inspection-mvp/records/`

Never label rosbag-only evidence as `VEHICLE_VALIDATED`.

Use these validation labels consistently:

- `STATIC_VALIDATED`: compile/unit/static-contract checks only.
- `BAG_VALIDATED`: passed recorded-data replay.
- `VEHICLE_VALIDATED`: passed real-vehicle test.

## Phase Order

Follow the phase gates in `RTABMAP_INSPECTION_MVP.md`.

Do not skip directly to full-system bringup. In particular:

1. audit repository and rosbag truth;
2. validate Livox conversion/time and IMU orientation path;
3. validate ICP odometry without graph/GPS;
4. validate RTAB mapping without RTK;
5. add RTK only after the GNSS contract is ready enough;
6. validate localization mode;
7. connect HMI/Nav2/safety;
8. connect camera/evidence logging.

## Codex Workflow

Before modifying a phase:

1. read this file and `RTABMAP_INSPECTION_MVP.md`;
2. confirm current branch and clean/dirty git state;
3. inspect the actual files and launch paths in the current checkout;
4. identify stale documentation instead of trusting it blindly;
5. state the smallest file set to modify;
6. identify the exact test/replay that proves the change;
7. implement the smallest change;
8. run build/tests/replay;
9. update the phase status/record;
10. commit the phase independently.

Prefer TDD for adapters, parser-independent helpers, parameter validation, and contract tests.

## Stop Conditions

Stop the current phase and diagnose rather than piling on tuning when any of these occur:

- duplicate TF authority;
- point timestamp semantics are unknown;
- PointCloud2 conversion drops per-point time unexpectedly;
- ICP repeatedly loses or jumps;
- RTK makes a previously stable map worse;
- map frame convention changes without documentation;
- local obstacle data disappears when RTAB map rate changes;
- navigation bypasses safety/collision monitor;
- a referenced package/launch file does not exist in the checkout.

## Dependency Policy

Do not pin or vendor RTAB-Map, `agt_ins_driver`, HMI, or camera commits merely to make documentation look stable. Record the branch/ref under test and freeze a SHA only after the relevant acceptance gate passes.

Do not fork RTAB-Map unless an upstream limitation is demonstrated and documented. Prefer launch/config/adapters first.

## Commit Policy

One phase or coherent correction per commit. Good examples:

```text
docs: audit rtabmap inspection integration baseline
feat(sensor): preserve livox point timing for rtabmap
feat(mapping): add rtabmap icp odometry backend
feat(mapping): add rtabmap lidar mapping profile
feat(localization): wire accepted gnss prior into rtabmap
feat(navigation): connect rtabmap localization to nav2 runtime
feat(inspection): record synchronized inspection evidence
```

Do not mix unrelated cleanup into an integration phase.
