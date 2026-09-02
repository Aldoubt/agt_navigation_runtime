# RTAB-Map Inspection MVP

This document is the visible integration entry point for the MID360 + IMU + RTK + RTAB-Map + Nav2 + HMI + camera inspection MVP.

## Current Branch

- Repository: `Aldoubt/agt_navigation_runtime`
- Branch: `feat/rtabmap-inspection-mvp`
- Base at branch creation: `main@d433e3022bb8c7c6b6b13b5e9752882a63cedced`
- Status: DESIGN FROZEN, IMPLEMENTATION NOT STARTED
- Dependency SHAs: intentionally NOT FROZEN

Related workstream:

- `Aldoubt/agt_ins_driver`
- branch: `feat/rtabmap-gnss-contract`
- owns the RTK/GNSS/INS internal corrections and validation

## Goal

Fastest reproducible path from an existing MID360 rosbag to a working inspection data chain:

```text
MID360 CustomMsg + MID360 IMU
        -> RTAB ICP odometry
        -> RTAB mapping
        -> RTK prior when available
        -> RTAB localization
        -> Nav2/BUNKER execution
        -> stable camera acquisition
        -> image + map pose + RTK + gimbal evidence
```

The first success criterion is not perfect SLAM tuning. It is a clear, replayable, measurable data chain in which every transform, topic and repository responsibility has one owner.

## Non-Goals for the First MVP

Do not add these merely because they may be useful later:

- FAST-LIVO2 as the active RTAB-path frontend;
- a new robot_localization fusion chain;
- a separate GTSAM backend;
- ScanContext or another independent global relocalizer;
- visual RTAB-Map;
- a custom new 3D-to-2D mapper;
- a complex RTK health state machine;
- a new navigation planner/controller stack;
- a camera driver redesign;
- HMI ownership of SLAM internals;
- editing the RTAB database from the HMI.

FAST-LIVO2 remains in the repository as a baseline/reference path and must not be deleted by this MVP.

## System Boundary

```text
                           +----------------------+
                           | Aldoubt/agt_ins_driver|
                           | GNSS/INS capability  |
                           +----------+-----------+
                                      |
                            /ins/navsatfix
                            /ins/status
                                      |
                                      v
+-------------+          +------------+-------------+
| MID360      |          | agt_navigation_runtime   |
| CustomMsg   +--------->|                            |
| raw IMU     |          | agt_sensor_adapters       |
+------+------+          |   CustomMsg -> PointCloud2|
       |                 |   IMU orientation path    |
       |                 |            |               |
       |                 |            v               |
       |                 | agt_mapping                |
       |                 |   RTAB ICP odometry        |
       |                 |   RTAB mapping/localize    |
       |                 |            |               |
       |                 |            v               |
       |                 | agt_navigation / Nav2      |
       |                 |            |               |
       |                 | agt_perception + safety    |
       |                 |            |               |
       |                 | agt_chassis / BUNKER       |
       |                 +------------+---------------+
       |                              |
       |                              v
       |                      vehicle motion
       |
       |          +-------------------+-------------------+
       |          |                                       |
       v          v                                       v
+-------------+  +----------------------+       +----------------------+
| agt_robot_hmi| | Autolabor-C1-ROS2    |       | Inspection evidence  |
| map/task UI |  | AcquireView          |       | image + pose + RTK   |
+-------------+  +----------------------+       | + gimbal angles      |
                                                +----------------------+
```

The external repositories stay independent. Runtime consumes their public interfaces and does not copy their implementation.

## Repository Responsibility Matrix

| Repository | Responsibility in this MVP | Development state | SHA policy |
| --- | --- | --- | --- |
| `agt_navigation_runtime` | SLAM/backend integration, Nav2, safety, mission/evidence orchestration | active | branch fixed, SHA evolves |
| `agt_ins_driver` | ASENSING parser + correct ROS GNSS/INS contract | active parallel workstream | UNFROZEN until R acceptance |
| `agt_robot_hmi` | Qt map/task/operator workflow | later integration | UNFROZEN |
| `Autolabor-C1-ROS2` | camera/gimbal `AcquireView` capability | consume existing contract first | do not pin early |
| RTAB-Map ROS2 | ICP odometry, mapping, localization, graph | dependency to audit in P0 | do not fork/pin early |
| Livox Driver2 | source CustomMsg + MID360 IMU | existing dependency | audit exact runtime version in P0 |

Freeze interfaces first. Freeze dependency SHAs only after the relevant gate is accepted.

## Runtime Package Ownership

### `agt_sensor_adapters`

Owns format adaptation, not SLAM.

Planned RTAB-path additions:

- Livox `CustomMsg` to enriched `sensor_msgs/msg/PointCloud2` adapter;
- preservation of per-point timing and Livox metadata needed for reproducible conversion;
- launch/configuration for MID360 IMU orientation preparation when the raw IMU has no valid orientation quaternion.

It must not perform graph optimization or mission logic.

### `agt_mapping`

Owns mapping/continuous-odometry backend abstraction.

RTAB-Map is added here as a backend, alongside the retained FAST-LIVO2 baseline.

Expected public/backend-neutral outputs:

- `/agt/mapping/odometry`
- `/agt/mapping/registered_points` where useful/available
- `map -> odom`
- `odom -> base_footprint`
- occupancy map output used for export/HMI/Nav2
- RTAB database path/state as a backend artifact

Do not create a separate monolithic `agt_rtabmap` package unless P0 proves the existing abstraction cannot represent the backend cleanly.

### `agt_perception`

Owns local obstacle preprocessing for Nav2/collision monitoring.

The no-FAST-LIVO path should use a correctly transformed raw/enriched MID360 PointCloud2 source rather than depend on RTAB map publication rate.

### `agt_navigation`

Reuse the existing Nav2 path. The integration goal is to feed it a valid map/localization/odometry contract, not redesign planning/control.

### `agt_safety` and `agt_chassis`

Preserve the existing BUNKER safety chain and watchdog behavior. This MVP should require zero or minimal changes here.

### `agt_mission_manager`

Owns high-level sequencing:

```text
waypoint request
 -> Nav2 NavigateToPose
 -> navigation success
 -> camera AcquireView one or more times
 -> timestamped evidence capture
```

Mission code must not reimplement camera hardware control or RTK parser logic.

## Sensor Data Contract

### LiDAR source

Keep the raw Livox `CustomMsg` for archival/replay compatibility.

The RTAB adapter output must preserve at least:

```text
x y z
intensity/reflectivity
tag
line
per-point time
```

The exact PointCloud2 time field name/type/unit is a P0/P1 truth item and must be documented and tested before deskew is trusted.

Do not silently convert to plain PointXYZI.

### IMU

MID360 IMU is used as an RTAB auxiliary source for:

- orientation initialization;
- gravity reference;
- rotational/motion guess support;
- point-cloud deskew support where the RTAB pipeline/configuration supports it.

This path is not described as tightly coupled LIO. ICP remains the local geometric odometry baseline.

If the raw MID360 IMU does not carry a valid orientation quaternion, the runtime must insert an orientation filter through a small launch/config layer rather than invent orientation in the mapping backend.

### RTK/GNSS

Runtime initially consumes only:

```text
/ins/navsatfix  sensor_msgs/msg/NavSatFix
/ins/status     agt_asensing_driver/msg/INSStatus
```

The RTK package itself is repaired and validated in `Aldoubt/agt_ins_driver`. Runtime does not absorb those fixes.

Until the RTK contract accepts them, do not use these as runtime navigation sources:

```text
/ins/odom
/ins/velocity
/ins/pose
```

## TF Ownership

Target RTAB path:

```text
map
 |
 | RTAB-Map only
 v
odom
 |
 | RTAB ICP odometry only
 v
base_footprint
 |
 v
base_link
 |\
 | +-- mid360_link
 | +-- rtk_antenna_link
 | +-- camera/gimbal frames
 |
 robot_description/static TF
```

Exactly one publisher must own each dynamic edge.

A duplicate `odom -> base_footprint` or `map -> odom` publisher is a blocking defect, not a tuning issue.

## RTK Lever Arm

The measured `base_link -> rtk_antenna_link` transform belongs in robot geometry/profile configuration.

Static TF is necessary for correct system geometry but must not be assumed to make RTAB's GNSS prior automatically refer to the robot base. Explicit antenna-to-base compensation, if required, belongs to the GNSS capability path and must be optional until heading/ENU/NED conventions are verified.

## Map Artifacts

Keep two different authorities:

```text
site.db
  RTAB graph/localization database
  never HMI-edited

site_nav_raw.pgm + site_nav_raw.yaml
  exported RTAB occupancy map

site_nav_edited.pgm + site_nav_edited.yaml
  operator-edited Nav2 navigation map
```

HMI edits are navigation asset edits, not SLAM graph edits.

## HMI Contract

The current HMI already consumes occupancy-map and robot/task interfaces. The integration should preserve a backend-neutral operator flow:

```text
RTAB /map
 -> HMI display/export
 -> operator edit
 -> edited PGM/YAML
 -> Nav2 map_server
```

Task/waypoint requests should continue through the existing runtime-facing navigation/task interfaces rather than directly binding HMI logic to RTAB internals.

## Camera/Evidence Contract

Use the existing public camera/gimbal `AcquireView` capability.

For every saved image, the evidence recorder should associate at least:

- task id;
- waypoint id;
- image path;
- image timestamp;
- map-frame robot pose at/near image timestamp;
- GNSS latitude/longitude/altitude at/near image timestamp;
- RTK/status fields available from the accepted GNSS contract;
- actual gimbal heading/roll/pitch returned by camera capability;
- map/database/version identifiers where practical.

Suggested output layout:

```text
inspection/YYYYMMDD_HHMMSS/
  manifest.json
  inspection.csv
  images/
    P001_001.jpg
    P001_002.jpg
```

## Development Gates

### P0 - Runtime and rosbag truth audit

No algorithm implementation.

Verify from the actual local checkout and bag:

- git state and current branch;
- real package/launch/config structure;
- stale docs (including references to absent packages such as current `agt_bringup` references);
- exact Livox topic type and fields;
- exact MID360 IMU topic/type/frame/orientation validity;
- `/tf` and `/tf_static` availability;
- RTK topics if present;
- existing mapping/navigation/perception tests;
- RTAB-Map installation/source/version availability;
- current standardized odometry/topic/TF contract.

Deliverable: `docs/rtabmap-inspection-mvp/records/P00_RUNTIME_TRUTH_AUDIT.md`.

Gate: no implementation starts until input schema and TF ownership are known.

### P1 - MID360 adapter and IMU preparation

Build the thinnest adapter path required by the P0 bag.

Required evidence:

- converted point count;
- preserved XYZ/intensity/tag/line fields where present;
- verified per-point-time conversion;
- documented time units/semantics;
- IMU orientation validity before RTAB input;
- unit/contract tests;
- rosbag replay output rates.

Deliverable: `P01_MID360_ADAPTER_IMU.md`.

Gate: RTAB never receives a cloud whose point-time semantics are unknown.

### P2 - RTAB ICP odometry only

Run ICP odometry without graph mapping and without RTK.

Publish through the existing standardized runtime odometry contract where practical.

Measure:

- output frequency;
- lost/recovery events;
- jumps;
- TF continuity;
- stationary behavior;
- turning behavior;
- effect of deskew/IMU support.

Deliverable: `P02_RTAB_ICP_ODOM.md`.

Gate: stable local odometry before graph/GPS complexity is added.

### P3 - RTAB LiDAR mapping

Add RTAB graph/mapping without RTK first.

Validate:

- database creation/growth;
- `/map` occupancy output;
- `map -> odom` uniqueness;
- no gross double walls or graph discontinuity;
- loop/proximity behavior on the bag;
- map export path.

Deliverable: `P03_RTAB_MAPPING.md`.

Gate: a usable LiDAR+IMU RTAB baseline exists before GNSS priors.

### P4 - RTK prior integration

Blocked on the RTK repository reaching at least software-contract readiness for `/ins/navsatfix` and `/ins/status`.

Compare the same bag/config with RTK disabled and enabled.

If RTK worsens the map, inspect before tuning ICP:

- timestamp alignment;
- covariance;
- solution/status stability;
- frame/antenna semantics;
- lever arm;
- coordinate conventions.

Deliverable: `P04_RTAB_RTK.md`.

Gate: RTK is demonstrably neutral or beneficial; not merely subscribed.

### P5 - RTAB localization mode

Load an accepted `.db` and validate localization without incremental mapping.

Test:

- restart at known start;
- restart later in bag;
- ambiguous/repetitive row areas;
- localization recovery behavior;
- map/odom/pose stability.

Deliverable: `P05_RTAB_LOCALIZATION.md`.

Gate: localization mode can support Nav2 without continuously rebuilding the map.

### P6 - HMI + Nav2 + BUNKER safety

Connect the accepted localization/map contract to the existing navigation chain.

Expected flow:

```text
RTAB localization
 -> map/odom/robot pose
edited PGM/YAML
 -> Nav2 map_server
HMI waypoint/task
 -> runtime mission/navigation bridge
 -> NavigateToPose
 -> collision monitor
 -> safety
 -> BUNKER
```

Validate the local obstacle path independently of RTAB map rate.

Deliverable: `P06_NAVIGATION_HMI.md`.

Gate: a waypoint can be issued through the intended operator/runtime boundary without bypassing safety.

### P7 - Camera inspection evidence

On navigation success, invoke `AcquireView` and record synchronized evidence.

Validate at least one multi-waypoint replay/simulation or vehicle run, depending on available hardware.

Deliverable: `P07_INSPECTION_EVIDENCE.md`.

Gate: each image is traceable to waypoint, image timestamp, robot map pose, GNSS sample and actual gimbal angles.

## Parallel RTK Workstream Dependency

The runtime P phases do not own R phases.

Expected relationship:

```text
agt_ins_driver
R0 truth audit
 -> R1 parser/state correctness
 -> R2 ROS GNSS contract correctness
 -> R3 real hardware validation

runtime
P0 -> P1 -> P2 -> P3
                 |
                 +---- P4 may begin when R2 is accepted for the data being tested

Final vehicle acceptance of P4+ requires R3 vehicle evidence.
```

Do not block P1-P3 waiting for RTK. Do not fake P4 by patching RTK internals inside runtime.

## Validation Labels

Use only:

- `STATIC_VALIDATED`: build/unit/static checks passed;
- `BAG_VALIDATED`: rosbag replay passed;
- `VEHICLE_VALIDATED`: real vehicle test passed.

No phase may be promoted beyond the evidence actually collected.

## Current Status Table

| Gate | State | Evidence |
| --- | --- | --- |
| Branch creation | DONE | `feat/rtabmap-inspection-mvp` |
| Architecture freeze | DONE | this document + `AGENTS.md` |
| P0 runtime/bag audit | NOT STARTED | none |
| P1 MID360 adapter/IMU | BLOCKED BY P0 | none |
| P2 RTAB ICP odometry | BLOCKED BY P1 | none |
| P3 RTAB mapping | BLOCKED BY P2 | none |
| P4 RTK prior | BLOCKED BY P3 + RTK contract | none |
| P5 localization | BLOCKED BY P3/P4 decision | none |
| P6 HMI/Nav2/safety | BLOCKED BY P5 | none |
| P7 camera/evidence | BLOCKED BY P6 | none |

## Files to Read Before Any Implementation

1. `AGENTS.md`
2. `RTABMAP_INSPECTION_MVP.md`
3. `docs/rtabmap-inspection-mvp/CODEX_PHASE_PROMPTS.md`
4. the current phase record, if one exists
5. the actual source/config files being changed

Do not infer current repository structure from old chat logs or stale README text.
