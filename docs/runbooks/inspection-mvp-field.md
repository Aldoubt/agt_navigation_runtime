# Inspection MVP — Humble / Bench / Field Freeze Runbook

Date: 2026-08-30  
Candidate branch: `feat/inspection-mvp-convergence`  
Frozen behavior commit: `73b0f2dfe02bb04c5940d8bebbcff2a95fd281d2`  
Canonical base: `feat/runtime-navigation-convergence-p1` @ `04541525ee52ca5133914675ff8acfe65682a23c`

> This runbook verifies the already-frozen Runtime behavior. It does not authorize new product features. STATIC/cloud evidence is not ROS 2 Humble, bench, or real-vehicle evidence.

## 1. Frozen first-field scope

The first physical inspection path is intentionally narrow:

```text
frozen Site + localization + Nav2
  -> versioned Mission
  -> INSPECTION_TASK
  -> ExecuteWaypointTask
  -> continuous chassis stationary gate
  -> atomic /camera_gimbal/acquire_view
     -> gimbal arrival + stable feedback
     -> settle
     -> fresh image after settle
  -> image_stamp
  -> nearest fresh accepted TRACKING LocalizationStatus
  -> evidence:
       image
       capture timestamp
       robot_pose_map
       actual pan/tilt/roll
       camera calibration identity
       PENDING_OFFLINE vision state
  -> next view / point
  -> RETURN_HOME
  -> Mission report
```

For this field freeze:

- real C1 inspection uses schema v2;
- `vision.execution_mode` is `DEFERRED`;
- online litchi-flower inference is excluded;
- point/view aggregation is excluded from the real first-field gate;
- map editing and HMI authoring are excluded;
- direct RViz pose goals are not a production Mission interface;
- inspection does not own Nav2, `cmd_vel`, `map -> odom`, Site activation, or safety authority.

## 2. Evidence directory

Create one immutable acceptance directory before testing:

```bash
export AGT_ACCEPT_ROOT="$HOME/agt_acceptance/inspection_mvp_$(date +%Y%m%d_%H%M%S)"
mkdir -p "$AGT_ACCEPT_ROOT"/{source,humble,hardware,camera_gimbal,navigation,mission,evidence}
```

Do not overwrite a previous acceptance directory. Preserve raw command output and copied Runtime reports.

## 3. G0 — source identity gate

On the target Ubuntu 22.04 / ROS 2 Humble machine:

```bash
cd ~/agt_navigation_runtime
source /opt/ros/humble/setup.bash

git fetch origin
git checkout feat/inspection-mvp-convergence
git status --short | tee "$AGT_ACCEPT_ROOT/source/git_status.txt"
git rev-parse HEAD | tee "$AGT_ACCEPT_ROOT/source/head.txt"
git merge-base HEAD origin/feat/runtime-navigation-convergence-p1 \
  | tee "$AGT_ACCEPT_ROOT/source/merge_base.txt"
```

Pass criteria:

- working tree is clean before build/test;
- candidate contains the frozen behavior commit `73b0f2dfe02bb04c5940d8bebbcff2a95fd281d2`;
- merge-base remains the intended canonical P1 line;
- no old inspection/camera branch is required at runtime.

Useful verification:

```bash
git merge-base --is-ancestor \
  73b0f2dfe02bb04c5940d8bebbcff2a95fd281d2 HEAD

echo $?
```

Expected: `0`.

## 4. G1 — ROS 2 Humble clean build/test gate

Resolve dependencies without inventing package names:

```bash
cd ~/agt_navigation_runtime
source /opt/ros/humble/setup.bash

rosdep install \
  --from-paths src third_party/autolabor_c1_camera_gimbal/src \
  --ignore-src -r -y \
  2>&1 | tee "$AGT_ACCEPT_ROOT/humble/rosdep.txt"
```

Then force a clean build:

```bash
rm -rf build install log

colcon build --symlink-install \
  2>&1 | tee "$AGT_ACCEPT_ROOT/humble/colcon_build.txt"

source install/setup.bash
```

Run the full repository test set:

```bash
colcon test --event-handlers console_direct+ \
  2>&1 | tee "$AGT_ACCEPT_ROOT/humble/colcon_test.txt"

colcon test-result --verbose \
  2>&1 | tee "$AGT_ACCEPT_ROOT/humble/colcon_test_result.txt"
```

Pass criteria:

- clean build returns 0;
- no changed Runtime/vendor package fails to build;
- `colcon test-result --verbose` reports zero failures/errors;
- `agt_inspection` executes its registered Humble tests, including:
  - schema-v2/multiview;
  - DEFERRED vision;
  - camera-gimbal adapter;
  - atomic view acquisition;
  - camera-gimbal health gate.

If G1 fails, stop. A fix is allowed only as a freeze bugfix with a new RED reproducer, GREEN evidence, and a new freeze SHA.

## 5. G2 — BUNKER + MID360 monitor-only gate

Do not enable chassis motion yet.

First verify SocketCAN and the core sensor/chassis streams using the existing navigation hardware procedure. Example monitor launch:

```bash
source /opt/ros/humble/setup.bash
source ~/agt_navigation_runtime/install/setup.bash

ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  sensor_profile:=hardware_check \
  can_interface:=can0 \
  expected_can_bitrate:=<verified-bunker-bitrate-or-0-for-monitor-only>
```

In another shell:

```bash
source /opt/ros/humble/setup.bash
source ~/agt_navigation_runtime/install/setup.bash

ros2 run agt_hardware_bringup socketcan_preflight.py \
  --interface can0 \
  --expected-bitrate <same-value> \
  --json-output "$AGT_ACCEPT_ROOT/hardware/can_preflight.json"

ros2 run agt_hardware_bringup vehicle_preflight.py \
  --json-output "$AGT_ACCEPT_ROOT/hardware/vehicle_preflight.json"
```

Pass criteria:

- SocketCAN exists, is UP, and not BUS-OFF;
- BUNKER monitor connection is true;
- MID360 lidar + IMU streams are present/fresh;
- sensor monitor required streams are healthy.

Do **not** use `vehicle_preflight --require-camera --require-gimbal` as authoritative proof for the frozen C1 path. Those legacy flags inspect the older `/agt/sensors/camera/*` and `/agt/gimbal/state` boundaries. The frozen C1 authority is `/camera_gimbal/health` plus `AcquireView`.

## 6. G3 — C1 camera/gimbal bench gate

Before sending any gimbal motion:

- physically verify the gimbal zero convention and safe mechanical limits;
- verify the actual video device path;
- verify the actual serial device path;
- verify serial baud/configuration;
- verify camera calibration identity and SHA256 used in evidence.

Start the inspection stack in monitor mode with inspection explicitly opted in:

```bash
source /opt/ros/humble/setup.bash
source ~/agt_navigation_runtime/install/setup.bash

ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  sensor_profile:=hardware_check \
  can_interface:=can0 \
  expected_can_bitrate:=<verified-bunker-bitrate-or-0-for-monitor-only> \
  start_inspection:=true \
  inspection_camera_device_path:=<verified-/dev/videoX> \
  inspection_camera_gimbal_port:=<verified-/dev/ttyXXX> \
  inspection_camera_calibration_id:=<verified-calibration-id> \
  inspection_camera_calibration_sha256:=<verified-calibration-sha256>
```

Record graph and health evidence:

```bash
ros2 topic list \
  | tee "$AGT_ACCEPT_ROOT/camera_gimbal/topic_list.txt"

ros2 action list \
  | tee "$AGT_ACCEPT_ROOT/camera_gimbal/action_list.txt"

ros2 topic echo /camera_gimbal/health --once \
  | tee "$AGT_ACCEPT_ROOT/camera_gimbal/health_once.txt"
```

Required interfaces:

```text
/camera_gimbal/health
/camera_gimbal/acquire_view
/agt/inspection/execute_task
```

Health pass criteria before a new inspection goal:

```text
state == STATE_READY
camera_alive == true
gimbal_serial_connected == true
gimbal_feedback_alive == true
move_action_ready == true
busy == false
```

The Runtime admission gate also requires a fresh health sample; default freshness is 1.5 s.

### G3.1 Direct atomic AcquireView bench check

Only after the operator has verified that the requested zero/center pose is physically safe, send one center acquisition:

```bash
ros2 action send_goal \
  /camera_gimbal/acquire_view \
  camera_gimbal_interfaces/action/AcquireView \
  "{heading: 0.0, roll: 0.0, pitch: 0.0, tolerance: 3.0, timeout: 20.0, stable_samples: 2, settle_time: 0.5, image_timeout: 5.0, save_image: true, tag: 'bench-center'}" \
  --feedback \
  | tee "$AGT_ACCEPT_ROOT/camera_gimbal/acquire_view_center.txt"
```

Pass criteria:

- result `success=true`, `error_code=0`;
- `image_stamp > reached_stamp`;
- image path exists and file is non-empty;
- `actual_heading`, `actual_roll`, `actual_pitch` are populated from feedback/result;
- no second/manual capture is needed after `AcquireView`.

### G3.2 Fail-closed fault checks

With robot motion disabled, deliberately test at least:

1. camera stream absent/stale;
2. gimbal serial disconnected or feedback absent;
3. capability not READY;
4. stale health publication.

For each condition, a **new** `/agt/inspection/execute_task` goal must be rejected or fail before producing a false-success view. Record topic/action output in `camera_gimbal/`.

The imported serial driver has historically required node restart after some serial disconnects. Treat observed reconnect behavior as field evidence; do not claim automatic recovery unless the target-machine test proves it.

## 7. G4 — frozen Site/localization/navigation gate

Complete the existing frozen-Site navigation procedure in:

```text
docs/runbooks/field-navigation-commissioning.md
```

Before inspection motion, confirm all of the following on the same Site revision:

- active Site is the intended immutable revision;
- `SiteNavigationBinding` resolves the exact frozen navigation/localization assets;
- localization reports accepted `TRACKING` with valid map identity;
- unique `map -> odom` authority remains unchanged;
- required Nav2 lifecycle nodes are active;
- `NavigationRuntimeStatus` is READY;
- `TaskReadiness.navigation_ready` is true;
- Collision Monitor / safety / chassis guards are active;
- production RViz direct-goal bridge remains disabled unless an explicit commissioning-only test calls for it.

Save relevant status echoes in `$AGT_ACCEPT_ROOT/navigation/`.

## 8. G5 — inspection task/Mission asset gate

For the first physical mission, keep it deliberately small:

```text
P01 center
P02 center
P03 center
RETURN_HOME
```

A center-only task is sufficient for the first end-to-end vehicle gate. Add left/right views only after the center path is proven.

Each inspection point must:

- bind an existing single-point TaskGroup by ID/revision/content SHA;
- bind the exact active map ID/version/manifest SHA;
- use schema v2;
- use `vision.execution_mode="DEFERRED"`;
- preferably set aggregation disabled for this field gate;
- use a verified camera ID;
- use only physically verified gimbal poses.

The Mission must:

- contain versioned `INSPECTION_TASK` steps or the intended inspection sequence;
- finish with `RETURN_HOME`;
- keep RETURN_HOME last;
- bind exact content hashes;
- be started through the formal Mission/Gateway path, not a direct Nav2 goal.

Archive the exact task and Mission assets used under `$AGT_ACCEPT_ROOT/mission/`.

## 9. G6 — low-speed physical mission gate

Only after G0-G5 pass:

1. enable the verified chassis control mode;
2. set conservative field speed limits;
3. keep hardware E-stop/operator stop available;
4. run the three-point mission once;
5. do not add more points/views until this run passes.

Required sequence:

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
  -> RETURN_HOME
  -> SUCCEEDED
```

A camera/gimbal failure must not be converted into a successful inspection step. A localization/readiness loss must remain fail-closed according to the existing Runtime authority model.

Save the complete Mission report and inspection evidence roots after the run.

## 10. G7 — evidence audit gate

For every captured view, open its `result.json` and verify:

```text
view_id / capture_id
capture_stamp
robot_pose_map.frame_id == map
robot_pose_map.x/y/z/yaw
robot_pose_map.covariance

gimbal.pan_rad
gimbal.tilt_rad
gimbal.roll_rad
gimbal.feedback_valid == true
gimbal.roll_feedback_valid == true   # real C1 atomic backend

camera.camera_id
camera.calibration_id
camera.calibration_sha256

evidence.image
vision_status == PENDING_OFFLINE
vision.status == PENDING_OFFLINE
```

Hard pass criteria:

- original image file exists and is non-empty;
- capture timestamp came from the final image, not wall-clock fallback;
- robot pose is associated with a fresh accepted TRACKING localization sample;
- actual gimbal feedback is present; no requested-angle substitution occurred;
- real C1 path contains roll feedback as well as pan/tilt;
- camera calibration identity/hash is non-empty and matches the accepted calibration;
- no deferred/raw/unique flower count is silently written as zero merely because inference has not run.

Mission-level audit:

```text
runtime/mission_reports/<mission_id>/<run_id>/report.json
runtime/mission_reports/<mission_id>/<run_id>/steps.csv
runtime/mission_reports/<mission_id>/<run_id>/inspections.csv
```

Verify:

- Mission final state matches reality;
- inspection evidence root(s) are linked;
- `home_returned=true` only after successful RETURN_HOME;
- deferred inspection summary remains `PENDING_OFFLINE` / unknown where inference has not been performed.

Copy the accepted run into:

```bash
cp -a runtime/inspections "$AGT_ACCEPT_ROOT/evidence/"
cp -a runtime/mission_reports "$AGT_ACCEPT_ROOT/evidence/"
```

## 11. Freeze decision table

| Gate | Required for software freeze | Required before physical release |
| --- | --- | --- |
| STATIC/TDD | yes | yes |
| G1 ROS 2 Humble clean build/test | no, currently pending | yes |
| G2 BUNKER/MID360 monitor | no | yes |
| G3 C1 bench + health + AcquireView | no | yes |
| G4 frozen Site/navigation readiness | no | yes |
| G5 exact task/Mission assets | no | yes |
| G6 3-point low-speed Mission | no | yes |
| G7 evidence audit | no | yes |

Software freeze means the implementation boundary is fixed. It does **not** mean the robot has passed release/field acceptance.

## 12. Allowed changes after freeze

After the frozen behavior commit, permitted Runtime changes are limited to:

- acceptance evidence/docs;
- corrections to misleading documentation;
- a bugfix required by a failing Humble/bench/field gate.

A behavior bugfix requires:

```text
failing acceptance evidence
-> minimal RED reproducer
-> minimal fix
-> GREEN regression
-> update frozen behavior SHA
-> rerun affected downstream gates
```

Not allowed on this frozen line:

- online litchi model integration;
- new SLAM/localization/planner/controller stack;
- HMI/map-editor features;
- new mission semantics unrelated to a discovered freeze defect;
- whole-merging old divergent branches;
- bypassing Site, Mission, Nav2 lifecycle, Collision Monitor, safety, or chassis ownership.
