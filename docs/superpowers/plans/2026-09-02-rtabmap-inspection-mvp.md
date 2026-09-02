# RTAB-Map Inspection MVP Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a reproducible MID360 + IMU + optional RTK RTAB-Map localization path that feeds the existing Nav2/BUNKER safety chain and supports timestamped camera inspection evidence.

**Architecture:** Keep external device repositories independent and add RTAB-Map as another backend behind `agt_mapping`. Preserve the existing FAST-LIVO2 baseline, adapt Livox data in `agt_sensor_adapters`, keep local obstacle perception independent of RTAB map rate, and let mission orchestration call existing navigation and camera capabilities.

**Tech Stack:** ROS 2 Humble, C++17, Python launch, Livox Driver2 messages, sensor_msgs/PointCloud2, sensor_msgs/Imu, RTAB-Map ROS2, Nav2, tf2, rosbag2.

**Spec:** `RTABMAP_INSPECTION_MVP.md`

## Global Constraints

- Work only on `feat/rtabmap-inspection-mvp` for this plan.
- Do not delete or silently rewrite the FAST-LIVO2 baseline.
- Runtime consumes `/ins/navsatfix` and `/ins/status`; RTK parser/driver fixes belong in `Aldoubt/agt_ins_driver`.
- Exactly one publisher owns `map -> odom` and exactly one owns `odom -> base_footprint` in the RTAB path.
- Preserve Livox per-point time; do not reduce the RTAB input to plain XYZI if timing is lost.
- Reuse existing Nav2, collision monitor, safety and BUNKER watchdog paths.
- RTAB `.db` and HMI-edited PGM/YAML are different artifacts.
- Never claim `VEHICLE_VALIDATED` without a real-vehicle test.

---

### Task 1: P0 Runtime and Bag Truth Audit

**Files:**
- Create: `docs/rtabmap-inspection-mvp/records/P00_RUNTIME_TRUTH_AUDIT.md`
- Modify: `RTABMAP_INSPECTION_MVP.md`

**Interfaces:**
- Consumes: current checkout, local rosbag2 files, installed ROS package metadata.
- Produces: exact source topics/types, TF authority table, selected bag, RTAB dependency status and P1 implementation inputs.

- [ ] **Step 1: Verify repository truth**

Run:

```bash
git status --short --branch
git rev-parse HEAD
find src -maxdepth 2 -name package.xml -print | sort
find third_party -maxdepth 2 -type d -print | sort
```

Record missing/stale documentation references, including whether `src/agt_bringup` exists.

- [ ] **Step 2: Identify the first bag**

For each candidate bag:

```bash
ros2 bag info <bag_directory>
```

Choose the bag that contains MID360 lidar + MID360 IMU and the most complete TF/RTK context. Record its exact path/name and duration. Do not move or modify bag files.

- [ ] **Step 3: Inspect message and timing schemas**

Use local ROS interfaces/source:

```bash
ros2 interface show livox_ros_driver2/msg/CustomMsg
ros2 interface show livox_ros_driver2/msg/CustomPoint
ros2 interface show sensor_msgs/msg/Imu
```

Inspect the actual bag topic types. Record `timebase`, `offset_time` and IMU orientation validity based on local source/data, not memory.

- [ ] **Step 4: Audit current runtime contracts**

Inspect:

```text
src/agt_sensor_adapters/
src/agt_mapping/
src/agt_perception/
src/agt_navigation/
src/agt_safety/
src/agt_chassis/
src/agt_mission_manager/
```

Record standardized odometry, point cloud, map, local obstacle, velocity command and TF contracts.

- [ ] **Step 5: Build existing affected packages without code changes**

Run:

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install --packages-select \
  agt_sensor_adapters agt_mapping agt_perception agt_navigation \
  agt_safety agt_chassis agt_mission_manager
colcon test --packages-select \
  agt_sensor_adapters agt_mapping agt_perception agt_navigation \
  agt_safety agt_chassis agt_mission_manager
colcon test-result --verbose
```

If dependencies require a broader build, record the exact command and reason.

- [ ] **Step 6: Write the audit record**

`P00_RUNTIME_TRUTH_AUDIT.md` must include the exact topic/type table, bag identity, point-time schema, IMU orientation state, TF authority table, current contract table, stale docs, build/test result and concrete P1 file recommendation.

- [ ] **Step 7: Mark P0 only if accepted**

Update the P0 row in `RTABMAP_INSPECTION_MVP.md` with evidence path and `STATIC_VALIDATED` or `BAG_VALIDATED` only if justified.

- [ ] **Step 8: Commit**

```bash
git add RTABMAP_INSPECTION_MVP.md docs/rtabmap-inspection-mvp/records/P00_RUNTIME_TRUTH_AUDIT.md
git commit -m "docs: audit rtabmap inspection integration baseline"
```

---

### Task 2: P1 Livox Point-Time Adapter and IMU Preparation

**Files:**
- Create: `src/agt_sensor_adapters/src/livox_custom_to_pointcloud2.cpp`
- Create: `src/agt_sensor_adapters/launch/rtab_mid360_input.launch.py`
- Create: `src/agt_sensor_adapters/config/rtab_mid360_input.yaml`
- Create: `src/agt_sensor_adapters/test/test_livox_custom_to_pointcloud2.cpp`
- Modify: `src/agt_sensor_adapters/CMakeLists.txt`
- Modify: `src/agt_sensor_adapters/package.xml`
- Modify: `src/agt_sensor_adapters/README.md`
- Create: `docs/rtabmap-inspection-mvp/records/P01_MID360_ADAPTER_IMU.md`
- Modify: `RTABMAP_INSPECTION_MVP.md`

**Interfaces:**
- Consumes: exact Livox schema and topics documented in P0.
- Produces: enriched PointCloud2 with preserved per-point time plus a valid orientation-bearing IMU topic when required.

- [ ] **Step 1: Write a failing conversion contract test**

Construct a small deterministic CustomMsg with three points and assert the output PointCloud2 contains expected field definitions and values for x/y/z/intensity/tag/line/time.

Expected initial result: test fails because the converter does not exist.

- [ ] **Step 2: Run the focused test and confirm failure**

```bash
colcon test --packages-select agt_sensor_adapters --ctest-args -R livox_custom_to_pointcloud2
colcon test-result --verbose
```

- [ ] **Step 3: Implement the smallest converter**

Implement a node/helper that performs no geometry filtering by default. Preserve the exact source point count and map the source per-point timing to a documented PointCloud2 field.

Do not reuse `livox_custom_self_filter.cpp` as a place to hide conversion behavior; keep conversion separately understandable.

- [ ] **Step 4: Add field/time tests**

Test first/middle/last point timing, frame/header propagation, point count and Livox metadata fields.

- [ ] **Step 5: Add IMU launch/config path**

If P0 proves raw MID360 IMU orientation is invalid/unset, configure an existing ROS 2 orientation filter in `rtab_mid360_input.launch.py`; keep raw and filtered topics distinct and avoid magnetometer assumptions.

- [ ] **Step 6: Build/test**

```bash
colcon build --symlink-install --packages-select agt_sensor_adapters
colcon test --packages-select agt_sensor_adapters
colcon test-result --verbose
```

- [ ] **Step 7: Replay the P0 bag**

Record input/output rates and inspect PointCloud2 fields/time values. Verify filtered IMU quaternion is finite/normalized if used.

- [ ] **Step 8: Write P1 evidence and commit**

```bash
git add src/agt_sensor_adapters RTABMAP_INSPECTION_MVP.md \
  docs/rtabmap-inspection-mvp/records/P01_MID360_ADAPTER_IMU.md
git commit -m "feat(sensor): preserve livox point timing for rtabmap"
```

---

### Task 3: P2 RTAB ICP Odometry Backend

**Files:**
- Create: `src/agt_mapping/launch/rtabmap_icp_odometry.launch.py`
- Create: `src/agt_mapping/config/rtabmap_icp_mid360.yaml`
- Create: `src/agt_mapping/test/test_rtabmap_backend_contract.py`
- Modify: `src/agt_mapping/CMakeLists.txt`
- Modify: `src/agt_mapping/package.xml`
- Modify: `src/agt_mapping/README.md`
- Create: `docs/rtabmap-inspection-mvp/records/P02_RTAB_ICP_ODOM.md`
- Modify: `RTABMAP_INSPECTION_MVP.md`

**Interfaces:**
- Consumes: P1 PointCloud2 and prepared IMU.
- Produces: `/agt/mapping/odometry` and the sole RTAB-path `odom -> base_footprint` transform.

- [ ] **Step 1: Add a failing launch/contract test**

Assert the new launch/config references the P1 point cloud input, produces/remaps the standardized odometry topic and does not enable graph mapping or GPS.

- [ ] **Step 2: Confirm failure**

```bash
colcon test --packages-select agt_mapping
colcon test-result --verbose
```

- [ ] **Step 3: Implement RTAB ICP launch/config**

Use the locally installed RTAB ROS 2 node/package names established by P0. Keep ICP odometry separate from graph mapping and do not patch RTAB source.

- [ ] **Step 4: Ensure TF uniqueness**

Disable any competing vendor/backend `odom -> base_footprint` TF in this launch path. Add a documented launch argument if necessary, rather than changing unrelated defaults globally.

- [ ] **Step 5: Run A0/A1/A2 bag replay**

Use one fixed bag interval:

```text
A0 ICP baseline
A1 ICP + point-time/deskew
A2 ICP + point-time/deskew + prepared IMU
```

Record rate, lost events, jumps, stationary and turn behavior.

- [ ] **Step 6: Select the P3 baseline and commit**

```bash
git add src/agt_mapping RTABMAP_INSPECTION_MVP.md \
  docs/rtabmap-inspection-mvp/records/P02_RTAB_ICP_ODOM.md
git commit -m "feat(mapping): add rtabmap icp odometry backend"
```

---

### Task 4: P3 RTAB Mapping Backend

**Files:**
- Create: `src/agt_mapping/launch/rtabmap_mapping.launch.py`
- Create: `src/agt_mapping/config/rtabmap_mapping_mid360.yaml`
- Extend: `src/agt_mapping/test/test_rtabmap_backend_contract.py`
- Modify: `src/agt_mapping/README.md`
- Create: `docs/rtabmap-inspection-mvp/records/P03_RTAB_MAPPING.md`
- Modify: `RTABMAP_INSPECTION_MVP.md`

**Interfaces:**
- Consumes: accepted P2 odometry.
- Produces: RTAB database, `map -> odom`, occupancy `/map` and raw exportable navigation-map artifact.

- [ ] **Step 1: Write mapping-mode contract tests**

Assert mapping launch reuses the accepted odometry path, has one `map -> odom` authority, keeps GPS disabled by default and exposes a database path argument.

- [ ] **Step 2: Implement mapping launch/config**

Configure LiDAR/scan-cloud operation without RGB/depth dependence and request 2D occupancy output for later HMI/Nav2 export.

- [ ] **Step 3: Start from a new database and replay**

Record exact database path, final size, graph/node/loop evidence and `/map` resolution/dimensions.

- [ ] **Step 4: Export raw PGM/YAML**

Save a raw navigation-map candidate. Do not edit it in runtime and do not feed HMI edits back into the RTAB database.

- [ ] **Step 5: Verify TF and map quality**

Inspect for gross double walls/discontinuities and verify unique `map -> odom` / `odom -> base_footprint` ownership.

- [ ] **Step 6: Commit**

```bash
git add src/agt_mapping RTABMAP_INSPECTION_MVP.md \
  docs/rtabmap-inspection-mvp/records/P03_RTAB_MAPPING.md
git commit -m "feat(mapping): add rtabmap lidar mapping profile"
```

---

### Task 5: P4 Optional RTK Prior

**Files:**
- Modify: `src/agt_mapping/launch/rtabmap_mapping.launch.py`
- Modify: `src/agt_mapping/config/rtabmap_mapping_mid360.yaml`
- Extend: `src/agt_mapping/test/test_rtabmap_backend_contract.py`
- Create: `docs/rtabmap-inspection-mvp/records/P04_RTAB_RTK.md`
- Modify: `RTABMAP_INSPECTION_MVP.md`

**Interfaces:**
- Consumes: `/ins/navsatfix` and `/ins/status` from an R2-accepted `agt_ins_driver` branch.
- Produces: configurable RTAB global-prior behavior; no new runtime-specific GNSS message.

- [ ] **Step 1: Verify RTK prerequisite**

Read the exact R2 record in the RTK repository under test. Stop if covariance/frame/status persistence is not accepted for that data.

- [ ] **Step 2: Add a disabled-by-default GPS launch/config path**

Use the installed RTAB NavSatFix/GPS interface established locally. Ensure graph priors are actually enabled when the option is on; do not confuse subscription with optimization use.

- [ ] **Step 3: Add contract tests**

Assert GPS is off by default, uses `/ins/navsatfix` when enabled, and does not introduce `/ins/odom`/`/ins/velocity` dependencies.

- [ ] **Step 4: Run B0/B1 A/B replay**

```text
B0 accepted P3 config, RTK disabled
B1 identical config, RTK enabled
```

Record fix rate/status/covariance, graph/map changes and visible distortions.

- [ ] **Step 5: Diagnose before tuning**

If B1 is worse, investigate timestamp, covariance, solution state, antenna frame, lever arm and coordinate convention before changing ICP.

- [ ] **Step 6: Record ENABLE/DISABLE/NEEDS_RTK_FIX and commit**

```bash
git add src/agt_mapping RTABMAP_INSPECTION_MVP.md \
  docs/rtabmap-inspection-mvp/records/P04_RTAB_RTK.md
git commit -m "feat(localization): wire accepted gnss prior into rtabmap"
```

---

### Task 6: P5 RTAB Localization-Only Profile

**Files:**
- Create: `src/agt_mapping/launch/rtabmap_localization.launch.py`
- Create: `src/agt_mapping/config/rtabmap_localization_mid360.yaml`
- Extend: `src/agt_mapping/test/test_rtabmap_backend_contract.py`
- Modify: `src/agt_mapping/README.md`
- Create: `docs/rtabmap-inspection-mvp/records/P05_RTAB_LOCALIZATION.md`
- Modify: `RTABMAP_INSPECTION_MVP.md`

**Interfaces:**
- Consumes: accepted RTAB database and P2 odometry.
- Produces: localization-only `map -> odom` and stable runtime pose/map contract.

- [ ] **Step 1: Add localization-mode tests**

Assert an existing database is required/loaded, incremental mapping is disabled according to the installed RTAB version and no second odometry frontend is started.

- [ ] **Step 2: Implement localization launch/profile**

Keep RTK optional according to P4's evidence outcome.

- [ ] **Step 3: Replay L0/L1/L2 cases**

Test start-of-bag, later start and a repetitive-row segment. Record first localization time, losses/recovery and pose/TF jumps.

- [ ] **Step 4: Commit**

```bash
git add src/agt_mapping RTABMAP_INSPECTION_MVP.md \
  docs/rtabmap-inspection-mvp/records/P05_RTAB_LOCALIZATION.md
git commit -m "feat(localization): add rtabmap localization runtime profile"
```

---

### Task 7: P6 Nav2, Local Obstacles and HMI Runtime Boundary

**Files:**
- Modify only if P5 truth requires it: `src/agt_navigation/config/nav2_bunker.yaml`
- Modify: `src/agt_perception/config/local_obstacle_filter.yaml`
- Modify the current navigation/mission bridge files identified by P0 rather than creating a parallel gateway.
- Create: `docs/rtabmap-inspection-mvp/records/P06_NAVIGATION_HMI.md`
- Modify: `RTABMAP_INSPECTION_MVP.md`

**Interfaces:**
- Consumes: localization/map/odometry contract, edited PGM/YAML asset and existing HMI task/navigation request.
- Produces: Nav2 NavigateToPose through collision monitor/safety/BUNKER command chain.

- [ ] **Step 1: Verify existing Nav2 contract before changing YAML**

Confirm `map`, `base_footprint`, standardized odometry, MPPI, SmacPlanner2D and collision monitor expectations in the current file.

- [ ] **Step 2: Make minimum odometry/map remaps**

Prefer satisfying the existing `/agt/mapping/odometry` contract so `nav2_bunker.yaml` needs no unnecessary rewrite.

- [ ] **Step 3: Decouple local obstacle source from RTAB map rate**

Change `local_obstacle_filter.yaml` input to the accepted raw/enriched MID360 PointCloud2 source when the FAST-LIVO registered cloud is absent in the RTAB path. Preserve target frame/body/range filtering.

- [ ] **Step 4: Preserve HMI/runtime boundary**

Use the actual existing `/agt/navigation/go_point` or current equivalent after P0 verification. Runtime calls Nav2; HMI does not directly own the backend.

- [ ] **Step 5: Verify safety command chain**

Record the path from Nav2 output through collision monitor, safety and chassis watchdog. Vehicle testing must verify stop/slowdown/watchdog before autonomous mission use.

- [ ] **Step 6: Commit runtime side only**

```bash
git add src/agt_navigation src/agt_perception src/agt_mission_manager \
  RTABMAP_INSPECTION_MVP.md docs/rtabmap-inspection-mvp/records/P06_NAVIGATION_HMI.md
git commit -m "feat(navigation): connect rtabmap localization to nav2 runtime"
```

HMI repository changes are a separate repository/commit and must not be copied here.

---

### Task 8: P7 Inspection Evidence Orchestration

**Files:**
- Modify the actual mission-manager implementation identified in P0/P6.
- Create focused evidence helper files under `src/agt_mission_manager/` if no existing experiment/evidence component fits.
- Add tests under `src/agt_mission_manager/test/`.
- Create: `docs/rtabmap-inspection-mvp/records/P07_INSPECTION_EVIDENCE.md`
- Modify: `RTABMAP_INSPECTION_MVP.md`

**Interfaces:**
- Consumes: Nav2 waypoint success, camera `AcquireView` result, TF, `/ins/navsatfix`, `/ins/status`.
- Produces: `manifest.json`, `inspection.csv`, saved images and traceable timestamps/metadata.

- [ ] **Step 1: Write failing evidence-association/serialization tests**

Use synthetic timestamps and samples to prove nearest/accepted GNSS sample selection, TF timestamp use and deterministic CSV/JSON field names.

- [ ] **Step 2: Add the smallest mission hook**

After Nav2 success, request one or more `AcquireView` captures through the existing public action. Do not access internal serial pan/tilt commands.

- [ ] **Step 3: Associate evidence at image timestamp**

Record task/waypoint/image path/image_stamp, actual gimbal angles, map pose at/near image_stamp, nearest GNSS fix/status and map/database identifier.

- [ ] **Step 4: Write deterministic artifacts**

Use an operator-configurable output root and a run directory containing `manifest.json`, `inspection.csv` and `images/`.

- [ ] **Step 5: Build/test/integration smoke**

Run mission-manager tests and the safest available integration environment. Label evidence correctly if camera/vehicle hardware is unavailable.

- [ ] **Step 6: Commit**

```bash
git add src/agt_mission_manager RTABMAP_INSPECTION_MVP.md \
  docs/rtabmap-inspection-mvp/records/P07_INSPECTION_EVIDENCE.md
git commit -m "feat(inspection): record synchronized inspection evidence"
```

---

## Final Verification

After P7, run a full branch review before merging:

```bash
git status --short --branch
colcon build --symlink-install
colcon test
colcon test-result --verbose
```

Then verify the documented launch sequence on the accepted bag and, separately, on the real vehicle before assigning `VEHICLE_VALIDATED`.

The merge review must confirm:

- FAST-LIVO2 baseline remains available;
- RTAB path has no duplicate TF authority;
- point-time preservation is tested;
- RTK driver internals were not copied into runtime;
- local obstacles still feed collision monitoring;
- HMI edits affect Nav2 occupancy assets, not RTAB `.db`;
- camera evidence uses image timestamp and actual returned gimbal angles;
- every claimed validation level has evidence.
