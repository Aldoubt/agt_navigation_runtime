# Lychee Inspection — Runtime-only Field E2E Runbook

Date: 2026-08-30  
Candidate Runtime branch: `feat/field-real-vehicle-integration`  
Companion HMI branch: `agt_operator_hmi/feat/p8-real-inspection-authoring`

Status: integrated software path. ROS 2 Humble CI/static tests do **not** replace BUNKER + MID360 + camera/gimbal physical acceptance.

> Product authority for this runbook is `agt_navigation_runtime`. Do not infer product behavior from `agt_navigation_v2`; that repository/line is experimental and is not part of this field procedure.

## 1. Frozen first-field workflow

The first field loop is intentionally narrow:

```text
physical RC/manual drive
  -> FAST-LIO commissioning mapping
  -> finalized localization_map.pcd
  -> Runtime RTAB-Map LocalGridMaker projection
  -> HMI light erase/paint review
  -> immutable Site revision
  -> explicit Site activation
  -> frozen-Site localization + Nav2
  -> HMI P01/P02/P03 + explicit HOME
  -> planner preview, including last inspection point -> HOME
  -> save schema-v2 Inspection + per-point TaskGroups + HOME TaskGroup
  -> immutable Mission: INSPECTION_TASK -> RETURN_HOME
  -> Control Lease + physical AUTO permit + Safety motion enable
  -> low-speed Mission
  -> stationary AcquireView at every point
  -> evidence with robot map pose + measured gimbal feedback + image + calibration identity
  -> formal RETURN_HOME
  -> DEFERRED/offline lychee-flower inference
  -> report
```

Not in this first-field gate:

- online flower inference;
- dynamic tree-trunk route generation;
- direct RViz goals as a production task interface;
- automatic map cleanup beyond operator erase/paint;
- silent fallback to another map, Site revision, HOME pose, RC switch, camera device or gimbal port.

## 2. One root authority for the whole run

Use one Runtime root from mapping through navigation. This prevents commissioning/HMI from writing one Site tree while navigation reads another.

```bash
cd ~/agt_navigation_runtime
source /opt/ros/humble/setup.bash
source install/setup.bash

export SITE_ID=lychee_orchard_01
export RUN_ID=$(date +%Y%m%dT%H%M%S)
export SITE_REVISION=r01
export RUNTIME_DIR="$PWD/runtime"
export SITES_ROOT="$RUNTIME_DIR/sites"
export STATE_ROOT="$RUNTIME_DIR/state"
export VEHICLE_PROFILE="$PWD/profiles/platforms/bunker.yaml"

mkdir -p "$RUNTIME_DIR" "$SITES_ROOT" "$STATE_ROOT"
```

Use a new `RUN_ID` for every mapping attempt and a new `SITE_REVISION` whenever any immutable Site asset changes. Never edit an already-saved Site revision in place.

## 3. G0 — source/build identity

Record the exact candidate before field work:

```bash
git status --short
git rev-parse HEAD
```

The working tree should be clean. Preserve the SHA with the field evidence.

For a fresh target-machine verification:

```bash
source /opt/ros/humble/setup.bash
rosdep install --from-paths src third_party/autolabor_c1_camera_gimbal/src --ignore-src -r -y
rm -rf build install log
colcon build --symlink-install
source install/setup.bash
colcon test --event-handlers console_direct+
colcon test-result --verbose
```

Pass only with zero build/test failures.

### 3.1 RTAB-Map projector is a target requirement

Generic Runtime CMake deliberately makes the projector optional. The real commissioning target must prove that RTAB-Map Core + PCL were present when `agt_field_commissioning` was built:

```bash
ros2 pkg executables agt_field_commissioning | grep rtabmap_grid_projector
```

Required result contains:

```text
agt_field_commissioning rtabmap_grid_projector
```

If it is absent, stop before mapping review. A generic successful `colcon build` is not sufficient evidence for the 3D -> 2D field path.

## 4. G1 — BUNKER + MID360 monitor gate

Do not enable autonomous motion yet.

```bash
ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  sensor_profile:=hardware_check \
  can_interface:=can0 \
  expected_can_bitrate:=<verified-bitrate-or-0-for-monitor-check>
```

In another shell verify at minimum:

```bash
ros2 topic hz /agt/sensors/lidar/custom
ros2 topic hz /agt/sensors/imu/data
ros2 topic echo --once /agt/chassis/status
ros2 topic echo /agt/chassis/rc_state
ros2 run tf2_ros tf2_echo odom base_footprint
```

Do not continue if required streams/TF are absent or stale.

### 4.1 Discover the physical AUTO switch; do not guess it

Keep:

```bash
ros2 topic echo /agt/chassis/rc_state
```

running while physically moving the intended AUTO-enable switch. Record:

```text
AUTO_PERMIT_SWITCH=swa|swb|swc|swd
AUTO_PERMIT_ENABLED_VALUE=<observed integer>
```

Export the observed values only after the physical check:

```bash
export AUTO_PERMIT_SWITCH=<observed-switch>
export AUTO_PERMIT_ENABLED_VALUE=<observed-integer>
```

The Runtime adapter is fail-closed: an unset mapping, stale RC status or non-matching value must not grant autonomous permit.

Stop this monitor launch before starting the dedicated mapping launch.

## 5. G2 — commissioning mapping

Use physical RC/manual driving. The Runtime launch remains monitor-only:

```bash
ros2 launch agt_field_commissioning field_mapping.launch.py \
  site_id:=$SITE_ID \
  run_id:=$RUN_ID \
  runtime_dir:=$RUNTIME_DIR \
  operation_mode:=monitor \
  start_hardware:=true \
  start_lidar_self_filter:=true
```

Before moving, verify:

```bash
ros2 topic hz /agt/sensors/lidar/custom
ros2 topic hz /agt/sensors/imu/data
ros2 topic hz /agt/commissioning/mapping/registered_points
```

Drive one representative loop with a static start/end, both turn directions, row/road entrances and any representative slopes that are safe to traverse. Avoid aggressive motion during the first map.

### 5.1 Normal shutdown is part of the save contract

Finish with normal `Ctrl+C` / ROS shutdown in the mapping terminal. Do **not** use `SIGKILL`. FAST-LIVO2 persists the final PCD through its normal shutdown path.

Then finalize:

```bash
ros2 run agt_field_commissioning finalize_mapping_run.py \
  --runtime-dir "$RUNTIME_DIR" \
  --site-id "$SITE_ID" \
  --run-id "$RUN_ID"
```

Required artifacts:

```text
$RUNTIME_DIR/commissioning/$SITE_ID/$RUN_ID/mapping/localization_map.pcd
$RUNTIME_DIR/commissioning/$SITE_ID/$RUN_ID/mapping/localization_map.processing.yaml
$RUNTIME_DIR/commissioning/$SITE_ID/$RUN_ID/evidence/mapping_metadata.json
```

The finalizer must reject empty PCDs and leftover temporary files.

## 6. G3 — reopen the finalized run for HMI map review

`field_mapping.launch.py` exits its Gateway together with the mapper. Do not restart FAST-LIVO2 merely to review the saved PCD. Reopen the same commissioning run using the existing delivery Gateway only.

The Gateway write API is fail-closed without a command token:

```bash
export AGT_OPERATOR_COMMAND_TOKEN='<robot-local-field-token>'
```

Start the review Gateway:

```bash
ros2 run agt_operator_gateway operator_delivery_gateway_node.py --ros-args \
  -p host:=127.0.0.1 \
  -p port:=8765 \
  -p write_api_enabled:=true \
  -p commissioning_enabled:=true \
  -p commissioning_site_id:=$SITE_ID \
  -p commissioning_run_id:=$RUN_ID \
  -p commissioning_runtime_dir:=$RUNTIME_DIR \
  -p commissioning_sites_root:=$SITES_ROOT \
  -p commissioning_state_root:=$STATE_ROOT \
  -p commissioning_vehicle_profile:=$VEHICLE_PROFILE
```

This process owns no SLAM, Nav2 or chassis velocity. It only reopens the filesystem-backed commissioning run and HTTP/HMI control surface.

### 6.1 HMI access

Production topology remains:

```text
Browser -> Caddy :80 -> /api/* -> 127.0.0.1:8765 -> Gateway -> Runtime
```

A second laptop on the robot LAN opens the robot's fixed-IP HTTP address. Internet access is not required. Do not expose Gateway `:8765` or ROS 2 DDS directly to the public network.

Enter the same command token in the HMI session when a write operation is required.

## 7. G4 — PCD -> 2D grid -> light map review

The expected commissioning state after finalization is `PCD_READY`.

In HMI:

1. verify the displayed `siteId` and `runId` match this run;
2. click **Generate 2D map**;
3. wait for `MAP_READY`;
4. inspect the generated occupancy image;
5. erase only obvious false black obstacles/clutter;
6. paint only corrections the operator can justify from field context;
7. use undo/redo when needed;
8. do not hide uncertain areas merely to make Nav2 look cleaner.

Projection authority is:

```text
localization_map.pcd
  -> agt_field_commissioning/rtabmap_grid_projector
  -> rtabmap::LocalGridMaker::segmentCloud()
  -> raw_map.pgm/raw_map.yaml
  -> HMI review draft
```

RTAB-Map is the grid projector/classifier here; FAST-LIO is the commissioning 3D mapping source
and FAST-LIVO2 remains the normal navigation odometry source.

## 8. G5 — save and activate the immutable Site

In HMI, save the reviewed map as the new `SITE_REVISION`, then activate that exact revision.

The save operation packages and validates at least:

```text
$SITES_ROOT/$SITE_ID/$SITE_REVISION/
├── manifest.yaml
├── hashes.yaml
├── map/
│   ├── navigation.yaml
│   ├── navigation.pgm
│   ├── localization_map.pcd
│   └── localization_map.processing.yaml
├── semantic/
│   └── semantic_map.yaml
├── routes/
│   └── route_graph.yaml
└── commissioning/
    ├── projection_record.json
    └── map_edits.json
```

Activation persists into the same `$STATE_ROOT` that navigation will consume.

After save/activation, stop the review-only Gateway before starting `field_navigation.launch.py`; the navigation composition will start the single normal Gateway instance.

## 9. G6 — camera/gimbal bench gate

Before the full navigation composition, physically verify:

- actual `/dev/videoX`;
- actual gimbal serial device;
- safe gimbal zero convention and mechanical limits;
- camera calibration ID;
- camera calibration SHA256.

Export only verified values:

```bash
export CAMERA_DEVICE=<verified-/dev/videoX>
export GIMBAL_PORT=<verified-/dev/ttyXXX>
export CAMERA_CALIBRATION_ID=<verified-id>
export CAMERA_CALIBRATION_SHA256=<verified-sha256>
```

Use `docs/runbooks/inspection-mvp-field.md` G3 once on the actual hardware to prove `/camera_gimbal/health` and one safe atomic `AcquireView` before combining camera/gimbal motion with vehicle motion.

Required runtime interfaces are:

```text
/camera_gimbal/health
/camera_gimbal/acquire_view
/agt/inspection/execute_task
```

## 10. G7 — start the frozen-Site navigation/inspection composition

Use the same roots that the review Gateway used:

```bash
ros2 launch agt_field_commissioning field_navigation.launch.py \
  site_id:=$SITE_ID \
  site_revision:=$SITE_REVISION \
  sites_root:=$SITES_ROOT \
  state_root:=$STATE_ROOT \
  site_vehicle_profile:=$VEHICLE_PROFILE \
  runtime_dir:=$RUNTIME_DIR \
  operation_mode:=control \
  start_hardware:=true \
  start_auto_permit:=true \
  auto_permit_switch:=$AUTO_PERMIT_SWITCH \
  auto_permit_enabled_value:=$AUTO_PERMIT_ENABLED_VALUE \
  start_inspection:=true \
  inspection_camera_device_path:=$CAMERA_DEVICE \
  inspection_camera_gimbal_port:=$GIMBAL_PORT \
  inspection_capture_output_root:=$RUNTIME_DIR/camera_gimbal_capture \
  inspection_runtime_maps_root:=$RUNTIME_DIR/maps \
  inspection_evidence_root:=$RUNTIME_DIR/inspections \
  inspection_camera_calibration_id:=$CAMERA_CALIBRATION_ID \
  inspection_camera_calibration_sha256:=$CAMERA_CALIBRATION_SHA256 \
  enable_rviz_goal_bridge:=false
```

This composition has one Safety owner, starts Mission Manager by default, keeps direct RViz goal bridging disabled, binds navigation/localization/task authoring to the exact active Site, and requires the physical AUTO permit for autonomous Navigation velocity.

## 11. G8 — readiness before authoring/running

Keep the physical AUTO switch **not enabled** while first checking the stack.

```bash
ros2 topic echo --once /agt/maps/active
ros2 topic echo --once /agt/navigation/site_binding
ros2 topic echo --once /agt/localization/status
ros2 topic echo --once /agt/navigation/runtime_status
ros2 topic echo --once /agt/system/task_readiness
ros2 topic echo --once /camera_gimbal/health
ros2 topic echo --once /agt/safety/status
ros2 run tf2_ros tf2_echo map odom
ros2 run tf2_ros tf2_echo odom base_footprint
```

Required before motion:

- intended Site/revision is active and hash-valid;
- localization is accepted `TRACKING` and fresh;
- Nav2 runtime is ready;
- camera/gimbal health is READY/fresh;
- no physical/emergency stop is active;
- direct RViz goal bridge remains disabled;
- physical AUTO permit can be observed changing false -> true only when the chosen RC switch enters the verified AUTO position.

Check permit explicitly:

```bash
ros2 topic echo /agt/chassis/auto_permit
```

## 12. G9 — author P01/P02/P03 + explicit HOME in HMI

Use a deliberately small first mission.

In the HMI task/inspection workspace:

1. add ordered `P01`, `P02`, `P03` on the active Site map;
2. set an independent explicit `HOME` pose;
3. keep first-field inspection at the frozen center view;
4. run planner preview;
5. require every inspection segment **and P03 -> HOME** to preview successfully;
6. save the inspection.

The Runtime save creates:

```text
P01 single-point TaskGroup
P02 single-point TaskGroup
P03 single-point TaskGroup
schema-v2 Inspection (vision.execution_mode=DEFERRED)
HOME single-point TaskGroup
Mission
  -> INSPECTION_TASK
  -> RETURN_HOME
```

The HMI records the returned Mission ID/version/content SHA for Mission Control. Do not replace this with a direct Nav2 goal.

### 12.1 Save retry contract

For a lost HTTP/Gateway response, retry the **same unchanged save request** rather than changing IDs/revisions blindly.

Current guarantees:

- Task PUT uses a deterministic logical request ID, so an exact lost-response retry can hit Task Registry duplicate suppression while that Registry process remains alive;
- Inspection authoring reconciles only an exact already-committed `expectedRevision + 1` document with the exact candidate SHA;
- Mission versions are immutable and an exact same-content retry is accepted;
- stale revision with changed content remains a conflict.

Current non-guarantee:

- Task Registry duplicate receipts are in-memory. If the Task Registry itself restarts/power-cycles after committing a TaskGroup but before the client receives the response, do **not** assume the old request can be replayed safely. Stop, inspect persisted TaskGroup revisions, and recover deliberately.

## 13. G10 — acquire control, grant physical AUTO, then enable Safety motion

The browser must hold the Gateway Control Lease before sending Mission lifecycle commands. Keep the command token in session storage only.

Only after G0-G9 pass:

1. keep an operator at the physical E-stop/RC;
2. move the verified RC switch into the AUTO-permit position;
3. confirm `/agt/chassis/auto_permit` is fresh `true`;
4. re-check Runtime readiness;
5. enable Safety motion explicitly:

```bash
ros2 service call /agt/safety/set_motion_enabled std_srvs/srv/SetBool "{data: true}"
```

Expected response: `success: true` and `motion enabled`.

Do not enable motion if the physical E-stop is active/latched. The Safety service must reject that condition.

## 14. G11 — low-speed Mission

Load the authored Mission in Mission Control and start only the three-point first-field run.

Expected sequence:

```text
START
  -> P01 navigation
  -> stationary gate
  -> center AcquireView
  -> P02 navigation
  -> stationary gate
  -> center AcquireView
  -> P03 navigation
  -> stationary gate
  -> center AcquireView
  -> RETURN_HOME TaskGroup
  -> SUCCEEDED
```

Any localization/readiness/camera/gimbal failure must remain fail-closed. A failed capture must not be converted into a successful inspection point.

After the run, disable motion even if the Mission succeeded:

```bash
ros2 service call /agt/safety/set_motion_enabled std_srvs/srv/SetBool "{data: false}"
```

Return the RC switch to the non-AUTO position and confirm `/agt/chassis/auto_permit` becomes false.

## 15. G12 — evidence audit

For every captured view verify the existing inspection evidence contains:

```text
image path + non-empty image
capture timestamp
robot_pose_map in frame map
localization covariance / accepted TRACKING association
measured gimbal pan/tilt/roll feedback
camera_id
camera calibration_id
camera calibration_sha256
vision_status == PENDING_OFFLINE
```

Do not substitute requested gimbal angles for measured feedback and do not write a flower count of zero merely because inference has not run.

Mission evidence is expected under:

```text
$RUNTIME_DIR/mission_reports/<mission_id>/<run_id>/report.json
$RUNTIME_DIR/mission_reports/<mission_id>/<run_id>/steps.csv
$RUNTIME_DIR/mission_reports/<mission_id>/<run_id>/inspections.csv
```

Verify `home_returned=true` only after the formal `RETURN_HOME` step actually succeeded.

## 16. G13 — offline lychee-flower inference/report

Only after the navigation/capture/evidence chain passes, run the current lychee-flower model offline against the accepted image evidence. Preserve the original images/evidence and write inference/report outputs separately.

First-field product semantics remain:

```text
capture now
  -> evidence PENDING_OFFLINE
  -> offline model inference
  -> post-process/count
  -> report
```

Online model execution is a later upgrade and is not a prerequisite for proving the vehicle inspection data path.

## 17. Stop conditions

Stop the field run rather than bypassing authority if any of these occur:

```text
RTAB projector executable absent
MID360/IMU/chassis stream stale
FAST-LIO map save/finalize failure
Site validation/activation failure
wrong Site/revision/hash
localization not accepted TRACKING
Nav2 runtime not ready
camera/gimbal health not READY
AUTO switch/value not physically verified
AUTO permit stale/false
physical E-stop active/latched
planner preview cannot reach any point or HOME
Mission/Inspection/Task revision conflict not explained by an exact retry
capture evidence missing actual gimbal feedback or calibration identity
RETURN_HOME fails
```

Do not work around these by sending direct Nav2 goals, editing immutable Site files, disabling Safety, hard-coding AUTO permit true, or substituting requested camera/gimbal state for measured evidence.

## 18. First real-vehicle acceptance checklist

```text
[ ] exact Runtime/HMI SHAs recorded
[ ] clean Humble build/test passes on target
[ ] rtabmap_grid_projector executable exists on target
[ ] BUNKER + MID360 monitor gate passes
[ ] RC AUTO switch/value physically discovered and recorded
[ ] FAST-LIO mapping run ends through normal shutdown
[ ] finalize_mapping_run.py accepts localization artifacts
[ ] review-only Gateway reopens the same SITE_ID/RUN_ID
[ ] HMI Generate 2D map reaches MAP_READY
[ ] light map edits are reviewed and recorded
[ ] immutable Site revision validates and activates
[ ] camera/gimbal bench health + one safe AcquireView passes
[ ] field_navigation uses the exact same sites/state/runtime roots
[ ] localization/Nav2/readiness gates pass
[ ] P01/P02/P03 + explicit HOME planner preview passes
[ ] Inspection + HOME TaskGroup + Mission save succeeds
[ ] Mission is exactly INSPECTION_TASK -> RETURN_HOME
[ ] Control Lease is held by the intended browser
[ ] physical AUTO permit is fresh true only in verified RC position
[ ] Safety motion is explicitly enabled only after all readiness gates
[ ] low-speed three-point Mission succeeds
[ ] every view has image + map pose + measured gimbal state + calibration identity
[ ] formal RETURN_HOME succeeds
[ ] Safety motion is disabled after the run
[ ] offline inference/report runs without modifying raw evidence
```

Software/CI green means this workflow is internally integrated. Physical release is not complete until the checklist above is backed by fresh BUNKER + MID360 + camera/gimbal field evidence.
