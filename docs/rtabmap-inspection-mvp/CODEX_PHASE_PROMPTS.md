# Codex Phase Prompts — RTAB-Map Inspection MVP

These prompts are intended to be executed one phase at a time in a local checkout of `Aldoubt/agt_navigation_runtime` on branch `feat/rtabmap-inspection-mvp`.

Do not paste multiple phase prompts into one Codex run. Each phase is a reviewable gate.

Before every phase, Codex must read:

- `AGENTS.md`
- `RTABMAP_INSPECTION_MVP.md`
- this file
- the previous phase record, if it exists

## P0 — Repository and Rosbag Truth Audit

```text
You are working in the local repository Aldoubt/agt_navigation_runtime.

Required branch:
  feat/rtabmap-inspection-mvp

This is P0 of the RTAB-Map inspection MVP. Do not implement RTAB-Map integration code in this phase. The purpose is to establish repository and rosbag truth before any architecture is changed.

Read first:
  AGENTS.md
  RTABMAP_INSPECTION_MVP.md
  docs/rtabmap-inspection-mvp/CODEX_PHASE_PROMPTS.md

Hard constraints:
- Do not modify FAST-LIVO2 behavior.
- Do not modify Nav2, safety, chassis, HMI or camera behavior.
- Do not add RTAB packages/configuration yet.
- Do not trust stale README text without checking the actual checkout.
- Do not invent topic names, frame names, message fields or launch paths.
- Do not mark anything VEHICLE_VALIDATED.

Tasks:
1. Confirm git status, branch, HEAD, remotes, and whether the working tree is clean.
2. Enumerate the actual ROS 2 packages under src/ and the relevant third_party dependencies.
3. Audit src/agt_mapping, src/agt_sensor_adapters, src/agt_perception, src/agt_navigation, src/agt_safety, src/agt_chassis and src/agt_mission_manager.
4. Explicitly identify references in documentation/tests to packages or launches that do not exist in this checkout. In particular verify whether src/agt_bringup exists rather than assuming it does.
5. Locate existing rosbag2 datasets available in or near the workspace. If multiple bags exist, list them and choose the best candidate for the first MID360 replay based on topic content and duration; do not delete or move bags.
6. For the selected bag, run ros2 bag info and record exact topic names, message types, message counts and duration for:
   - MID360 lidar;
   - MID360 IMU;
   - /tf and /tf_static;
   - wheel/chassis odometry if present;
   - /ins/navsatfix and /ins/status if present;
   - camera topics if present.
7. Inspect the actual Livox message definition used by the bag. Determine whether lidar is livox_ros_driver2/msg/CustomMsg or sensor_msgs/msg/PointCloud2 and list the exact per-point fields.
8. If CustomMsg is present, inspect the installed/source message definition and document timebase/offset_time units and fields. Do not infer the unit from memory if source is available locally.
9. Inspect the MID360 IMU messages in the bag/source and determine whether orientation quaternion is populated and valid or left unspecified.
10. Inspect current TF/static-transform configuration for base_footprint, base_link, MID360 and any INS/GNSS frames. Produce a proposed current TF authority table, but do not change it.
11. Inspect current agt_mapping public contracts, especially /agt/mapping/odometry, /agt/mapping/registered_points and TF publication ownership.
12. Inspect the existing Nav2 odometry/map/local-obstacle topic expectations and the BUNKER safety chain.
13. Determine how RTAB-Map is currently available on the machine: apt-installed ROS packages, source workspace, or not installed. Record package versions/paths without installing anything unless installation is already part of the local environment setup and explicitly safe.
14. Run the existing relevant package tests/build checks without changing code. Prefer:
    colcon build --symlink-install --packages-select agt_sensor_adapters agt_mapping agt_perception agt_navigation agt_safety agt_chassis agt_mission_manager
    and existing tests for those packages, adjusting only if package dependencies require a documented broader build.
15. Create docs/rtabmap-inspection-mvp/records/P00_RUNTIME_TRUTH_AUDIT.md containing:
    - git state;
    - actual package/launch/config structure;
    - stale documentation findings;
    - selected bag identity/path/duration;
    - exact topic/type table;
    - Livox point/time schema;
    - IMU orientation status;
    - TF authority table;
    - mapping/Nav2/safety contract table;
    - RTAB dependency availability;
    - current build/test results;
    - concrete P1 implementation recommendation;
    - blockers and unknowns;
    - validation label STATIC_VALIDATED or BAG_VALIDATED only if supported by evidence.
16. Update only the Current Status table in RTABMAP_INSPECTION_MVP.md if P0 actually passes.
17. Show me the audit summary and files changed before committing.
18. Commit only documentation/audit changes with:
    docs: audit rtabmap inspection integration baseline

Acceptance:
- No algorithm implementation is introduced.
- The selected bag and exact sensor/time/TF contracts are known.
- P1 can be implemented without guessing message fields or topic names.
```

## P1 — MID360 CustomMsg Adapter and IMU Preparation

```text
You are implementing P1 in Aldoubt/agt_navigation_runtime on branch feat/rtabmap-inspection-mvp.

Read:
  AGENTS.md
  RTABMAP_INSPECTION_MVP.md
  docs/rtabmap-inspection-mvp/records/P00_RUNTIME_TRUTH_AUDIT.md

Do not start if P0 did not establish the actual lidar/IMU schemas.

Goal:
Create the thinnest reusable sensor path that converts the existing MID360 source into an RTAB-compatible PointCloud2 while preserving point timing, and prepares a valid orientation-bearing IMU stream if the raw MID360 IMU needs it.

Hard constraints:
- Keep the raw Livox CustomMsg source available.
- Do not convert to plain XYZ/XYZI if that drops per-point time.
- Do not patch RTAB-Map or Livox upstream source unless P0 demonstrated that a thin adapter is impossible.
- Do not add SLAM/mapping logic to agt_sensor_adapters.
- Do not touch RTK code in this repository.
- Do not change Nav2/safety/chassis behavior.

Implementation target:
- Put the Livox conversion in src/agt_sensor_adapters using the package's existing C++/launch/config conventions.
- Use an output topic name under the existing sensor/runtime namespace chosen consistently with P0; if no suitable standard exists, prefer /agt/sensors/lidar/points for the enriched PointCloud2 and document it.
- Preserve x/y/z, intensity or reflectivity, tag, line, and per-point time when present.
- Document the PointCloud2 time field name, datatype, unit and relation to header.stamp.
- If P0 shows raw IMU orientation is invalid/unset, add a launch/configurable orientation-filter path using an existing ROS 2 package rather than writing a new AHRS algorithm. Disable magnetometer assumptions when there is no magnetometer input.
- Keep IMU raw and filtered topics distinct.

Testing requirements:
1. Write/extend unit or contract tests before the converter implementation where practical.
2. Test that converted point count matches accepted input point count unless explicitly filtered; this adapter should not filter geometry by default.
3. Test XYZ numeric preservation within the exact representation tolerance.
4. Test intensity/reflectivity mapping.
5. Test tag and line preservation when the source fields exist.
6. Test first/middle/last point time conversion from the source timing representation.
7. Test output PointCloud2 field definitions and point_step layout.
8. Test header/frame propagation.
9. Build agt_sensor_adapters and run its tests.
10. Replay the P0 bag with use_sim_time as appropriate and record input/output rates and any conversion errors.
11. Inspect several output messages with ros2 topic echo/field inspection or a small diagnostic script to prove the time field is populated.
12. If the IMU filter path is enabled, verify output orientation is finite, normalized and changes continuously during motion; do not claim absolute yaw accuracy.

Deliverable:
Create docs/rtabmap-inspection-mvp/records/P01_MID360_ADAPTER_IMU.md with:
- exact source/output topics and types;
- field mapping table;
- time conversion equation/units;
- test results;
- bag replay rates;
- IMU raw/filtered behavior;
- known limitations;
- BAG_VALIDATED only if replay succeeds.

Update RTABMAP_INSPECTION_MVP.md P1 status only after evidence passes.

Before commit, show the diff summary and verification evidence.

Suggested commit:
  feat(sensor): preserve livox point timing for rtabmap
```

## P2 — RTAB ICP Odometry Baseline

```text
You are implementing P2 in Aldoubt/agt_navigation_runtime on branch feat/rtabmap-inspection-mvp.

Read AGENTS.md, RTABMAP_INSPECTION_MVP.md, P00 and P01 records.

Goal:
Establish stable RTAB-Map ICP odometry from the P1 enriched MID360 PointCloud2 and prepared IMU path, without RTAB graph mapping and without RTK.

Hard constraints:
- Do not enable RTK/GPS in this phase.
- Do not enable graph mapping in order to hide a bad odometry frontend.
- Do not delete FAST-LIVO2.
- Do not create a second odom -> base_footprint authority.
- Do not change Nav2/safety/chassis tuning.
- Prefer launch/config in agt_mapping over patching RTAB source.

Implementation:
1. Inspect the currently installed/source RTAB ROS 2 launch/node interfaces before writing launch files.
2. Add an RTAB ICP odometry backend configuration under src/agt_mapping following the package's existing layout.
3. Map the RTAB odometry output to the existing standardized /agt/mapping/odometry contract when semantically compatible.
4. Ensure the TF relationship for the RTAB path is exactly one odom -> base_footprint publisher.
5. Consume the P1 PointCloud2 topic.
6. Consume prepared IMU only through supported RTAB/deskew/orientation interfaces established from actual installed RTAB packages.
7. Start with a minimal planar/2.5D-friendly profile appropriate for the first BUNKER bag, but do not hard-code assumptions that contradict the bag. Parameter changes must be documented.
8. Add launch/config contract tests where the repo already uses them.

A/B replay:
Run at least these comparable modes on the same bag segment:
A0: ICP without IMU/deskew support if the RTAB path permits this cleanly.
A1: ICP with point timing/deskew support.
A2: ICP with prepared MID360 IMU support.

For each mode record:
- exact parameters;
- odometry output rate;
- lost/reinitialization events;
- discontinuities/jumps;
- stationary drift observations;
- turning/corner behavior;
- TF continuity;
- CPU/memory if easy to collect consistently.

Do not cherry-pick only the best segment. Use the same bag interval for the comparison.

Deliverable:
Create docs/rtabmap-inspection-mvp/records/P02_RTAB_ICP_ODOM.md with the A0/A1/A2 table and a selected P3 baseline configuration.

Acceptance:
- /agt/mapping/odometry is continuous enough for graph mapping experiments.
- no duplicate dynamic TF authority exists.
- selected configuration is justified by bag evidence.

Update the status table only if accepted.

Suggested commit:
  feat(mapping): add rtabmap icp odometry backend
```

## P3 — RTAB LiDAR Mapping Baseline

```text
You are implementing P3 in Aldoubt/agt_navigation_runtime on branch feat/rtabmap-inspection-mvp.

Read AGENTS.md, RTABMAP_INSPECTION_MVP.md and P00-P02 records.

Goal:
Build a LiDAR+IMU RTAB graph/mapping baseline on top of the accepted P2 ICP odometry, with RTK/GPS disabled.

Hard constraints:
- Do not add GPS/RTK yet.
- Do not use HMI map edits as RTAB graph input.
- Keep exactly one map -> odom authority.
- Do not fork RTAB unless a concrete upstream blocker is documented.
- Do not tune Nav2 in this phase.

Implementation:
1. Add mapping-mode RTAB launch/config under the agt_mapping backend boundary.
2. Reuse the accepted P2 odometry rather than launching a competing second odometry source.
3. Configure RTAB for scan-cloud/LiDAR operation without RGB/depth dependence.
4. Enable generation/publication of a 2D occupancy map appropriate for later HMI/Nav2 export, without claiming this is the final edited navigation map.
5. Define a deterministic database path argument/configuration and safe behavior for new-map vs reuse cases.
6. Make mapping mode and localization mode separable; do not implement P5 behavior yet beyond keeping configuration structure clean.
7. Document all non-default RTAB parameters in config comments or the P3 record.

Replay and evidence:
- Start from an empty/new database.
- Replay the same accepted bag/interval.
- Record database path and final size.
- Record graph/node count and loop/proximity closure evidence available from RTAB logs/topics/database tools.
- Verify /map publication and map dimensions/resolution.
- Inspect for gross double walls, discontinuities and map jumps.
- Verify map -> odom and odom -> base_footprint ownership.
- Save/export a raw PGM/YAML navigation-map candidate without editing it.

Deliverable:
Create docs/rtabmap-inspection-mvp/records/P03_RTAB_MAPPING.md containing parameters, graph/map evidence, artifact paths, known map defects and PASS/FAIL.

Acceptance:
A reproducible LiDAR+IMU RTAB mapping baseline exists before adding GNSS priors.

Suggested commit:
  feat(mapping): add rtabmap lidar mapping profile
```

## P4 — Integrate Accepted RTK/GNSS Prior

```text
You are implementing P4 in Aldoubt/agt_navigation_runtime on branch feat/rtabmap-inspection-mvp.

Prerequisites:
- P3 accepted.
- The exact agt_ins_driver branch under test has passed its R2 ROS GNSS contract for /ins/navsatfix and /ins/status.
- Read that RTK repository's RTK_GNSS_CONTRACT.md and R02 record before integrating.

Goal:
Feed the accepted NavSatFix/status contract into RTAB as an optional global prior and prove whether it improves or at least does not damage the P3 map on the same bag/data.

Hard constraints:
- Do not patch ASENSING parser/node in runtime.
- Do not consume /ins/odom, /ins/velocity or /ins/pose for this phase.
- Do not add robot_localization or a separate GTSAM backend.
- Do not assume NavSatFix frame TF automatically compensates antenna lever arm inside RTAB.
- Keep RTK integration configurable/off by default until the A/B result is accepted.

Implementation:
1. Inspect the actual installed RTAB GPS/NavSatFix interface and parameter names rather than relying on memory.
2. Add runtime launch/remap/config to consume /ins/navsatfix.
3. Configure graph prior behavior explicitly so GPS data is not merely subscribed while priors are ignored.
4. Keep GPS candidate filtering and graph-prior optimization concepts documented separately if RTAB exposes both.
5. Add minimal gating only if necessary to reject clearly invalid/non-finite fixes; do not create a large RTK state machine.
6. Expose/document whether RTK prior is enabled in launch/config.

A/B experiment on identical bag interval:
B0: accepted P3 mapping configuration with RTK disabled.
B1: same configuration with RTK enabled.

Record:
- NavSatFix receive count/rate;
- status/solution observations;
- covariance values used by RTAB;
- graph/map differences;
- loop/closure changes if any;
- visible map quality differences;
- any jumps or distortions;
- timestamp offsets/irregularities observed;
- antenna lever-arm magnitude/configuration if known.

If B1 is worse than B0, STOP before tuning ICP. Investigate timestamp, covariance, RTK solution status, frame semantics, lever arm and coordinate conventions first.

Deliverable:
Create docs/rtabmap-inspection-mvp/records/P04_RTAB_RTK.md with B0/B1 evidence and recommendation: ENABLE, DISABLE, or NEEDS_RTK_FIX. Do not force ENABLE.

Suggested commit if integration itself is valid:
  feat(localization): wire accepted gnss prior into rtabmap
```

## P5 — RTAB Localization Mode

```text
You are implementing P5 in Aldoubt/agt_navigation_runtime on branch feat/rtabmap-inspection-mvp.

Read P3/P4 records and use the accepted RTAB database/map configuration. If P4 concluded RTK should remain disabled, localization must still proceed without forcing RTK.

Goal:
Run RTAB in localization-only mode against an accepted database and provide stable map/odom/robot pose for Nav2.

Hard constraints:
- Do not modify the HMI yet.
- Do not start Nav2 tuning to mask localization problems.
- Do not continuously grow the mapping database in the localization profile.
- Keep TF authority unique.

Implementation:
1. Add a clearly separate localization launch/profile under agt_mapping.
2. Load an existing accepted database through a launch argument/configured path.
3. Configure RTAB localization/non-incremental memory behavior using the actual installed version's parameters.
4. Reuse the accepted P2 odometry frontend.
5. Keep RTK optional according to P4 result.
6. Publish the backend-neutral runtime pose/map/TF contract needed by Nav2.

Replay tests:
L0: start replay from the mapping run's beginning.
L1: start from a later bag position where local geometry is distinctive.
L2: test at least one repetitive greenhouse-row segment if present.

Record:
- time to first accepted localization;
- localization loss/recovery observations;
- pose jumps;
- map -> odom continuity;
- behavior in repetitive rows;
- whether RTK helps/hurts if enabled.

Deliverable:
Create docs/rtabmap-inspection-mvp/records/P05_RTAB_LOCALIZATION.md.

Acceptance:
Localization-only mode provides a stable enough runtime pose contract to begin Nav2/HMI integration.

Suggested commit:
  feat(localization): add rtabmap localization runtime profile
```

## P6 — HMI, Nav2 and BUNKER Safety Integration

```text
You are implementing the runtime side of P6 in Aldoubt/agt_navigation_runtime on branch feat/rtabmap-inspection-mvp.

The HMI repository remains separate. Do not copy Qt code into runtime.

Read P5 record and inspect the current Nav2/safety/chassis contracts before changing anything.

Goal:
Connect accepted RTAB localization and edited navigation-map assets to the existing Nav2 + collision monitor + safety + BUNKER execution chain, while preserving the existing HMI-facing task/navigation boundary.

Hard constraints:
- Reuse the current Nav2 planner/controller unless a measured defect requires a focused change.
- Do not bypass collision monitor or /agt/safety/cmd_vel chain.
- Do not enable vendor odom TF as a competing odom -> base_footprint source.
- Keep HMI backend-neutral; runtime translates its waypoint/task request to Nav2.
- RTAB .db is never HMI-edited.

Tasks:
1. Verify current Nav2 expects global_frame=map, robot_base_frame=base_footprint and the standardized odometry topic.
2. Remap/update only the minimum topic/config needed so the accepted RTAB odometry/localization path satisfies those contracts.
3. Keep the raw/enriched MID360 local obstacle path feeding agt_perception and collision monitoring independently of RTAB map rate.
4. Define/verify map-server flow for the HMI-edited PGM/YAML artifact.
5. Preserve the existing HMI-facing /agt/navigation/go_point or current equivalent contract after verifying the actual current code.
6. Have the runtime mission/navigation layer call Nav2 NavigateToPose rather than making HMI directly own the action.
7. Run static/launch tests and, where safe, bag/simulation smoke tests without commanding real vehicle motion unexpectedly.
8. If doing vehicle testing, explicitly verify emergency stop/slowdown/watchdog behavior before autonomous waypoint motion.

Deliverables:
- docs/rtabmap-inspection-mvp/records/P06_NAVIGATION_HMI.md
- exact runtime launch sequence
- exact HMI-side contract list for the separate agt_robot_hmi workstream
- proof that safety/collision chain remains in the command path.

Acceptance:
A waypoint can traverse HMI/runtime/Nav2 boundaries without backend-specific coupling or safety bypass.

Suggested runtime commit:
  feat(navigation): connect rtabmap localization to nav2 runtime
```

## P7 — Camera Inspection Evidence Chain

```text
You are implementing P7 in Aldoubt/agt_navigation_runtime on branch feat/rtabmap-inspection-mvp.

Read P6 record and inspect the current agt_mission_manager interfaces. The camera driver remains in Aldoubt/Autolabor-C1-ROS2.

Goal:
After a successful navigation waypoint, call the existing public AcquireView camera/gimbal action and write traceable inspection evidence containing image, robot map pose, GNSS sample/status and actual gimbal angles.

Hard constraints:
- Do not reimplement pan/tilt serial control in runtime.
- Do not use internal camera topics when AcquireView already provides the stable acquisition boundary.
- Use image_stamp, not navigation-arrival time, as the primary image evidence timestamp.
- Do not add RTK parser logic here.

Tasks:
1. Inspect the installed camera_gimbal_interfaces/action/AcquireView definition and current runtime dependencies.
2. Extend mission orchestration minimally so a waypoint action can request one or more AcquireView captures after Nav2 success.
3. Add an evidence recorder component/package location consistent with current runtime architecture; prefer agt_mission_manager unless a focused existing evidence/experiment component is clearly better.
4. For each returned image, associate:
   - task id;
   - waypoint id;
   - image path;
   - image_stamp;
   - reached_stamp if useful;
   - actual gimbal heading/roll/pitch;
   - map-frame robot pose obtained at/nearest image_stamp through TF;
   - nearest accepted /ins/navsatfix sample;
   - nearest /ins/status sample;
   - map/database identifier.
5. Write manifest.json and inspection.csv with deterministic column/field names.
6. Use a directory layout under an operator-configurable output root, e.g. inspection/<run-id>/images.
7. Add tests for metadata serialization and timestamp association logic.
8. Run a replay/simulation/integration smoke test where camera hardware availability permits; if real hardware is unavailable, clearly label the evidence STATIC_VALIDATED/BAG_VALIDATED rather than VEHICLE_VALIDATED.

Deliverable:
Create docs/rtabmap-inspection-mvp/records/P07_INSPECTION_EVIDENCE.md and a sample generated manifest/csv from the test run if safe to commit as a small fixture.

Acceptance:
Every saved image is traceable to waypoint, image timestamp, map pose, GNSS/status and actual gimbal orientation.

Suggested commit:
  feat(inspection): record synchronized inspection evidence
```

## End-of-Phase Review Prompt

Use this after any P phase before moving to the next one:

```text
Review the just-completed RTAB inspection MVP phase as a skeptical SLAM/navigation maintainer.

Read AGENTS.md, RTABMAP_INSPECTION_MVP.md, the phase record, git diff/commit and relevant tests.

Check specifically for:
- duplicate TF publishers;
- stale topic/frame assumptions;
- point-time loss or undocumented units;
- hidden dependency on FAST-LIVO2 in the RTAB path;
- RTK logic accidentally implemented in runtime;
- HMI/camera implementation copied into runtime;
- Nav2/safety bypass;
- a build-only success claim without bag evidence where bag evidence is required;
- VEHICLE_VALIDATED claims without a real vehicle run;
- parameters changed without an A/B reason.

Report blockers first. Do not begin the next phase. If fixes are needed, make only phase-local corrections and rerun the phase acceptance evidence.
```
