# Inspection MVP Runtime Freeze — Acceptance Record

Date: 2026-08-30  
Repository: `Aldoubt/agt_navigation_runtime`  
Candidate branch: `feat/inspection-mvp-convergence`  
Canonical base branch: `feat/runtime-navigation-convergence-p1`  
Canonical base commit: `04541525ee52ca5133914675ff8acfe65682a23c`  
Frozen behavior commit: `73b0f2dfe02bb04c5940d8bebbcff2a95fd281d2`

## 1. Decision

**Runtime Inspection MVP behavior is software-frozen at commit `73b0f2dfe02bb04c5940d8bebbcff2a95fd281d2`.**

This freeze means:

- the first-field Runtime feature boundary is fixed;
- no additional product features are allowed on this candidate line;
- documentation/acceptance evidence may continue to be added after the behavior commit;
- a behavior change is permitted only to correct a defect demonstrated by a failing Humble/bench/field gate, and must create a new freeze SHA after RED -> GREEN verification.

This record does **not** claim ROS 2 Humble, BUNKER/MID360 field, or physical camera/gimbal acceptance. Those remain explicit downstream gates.

## 2. Relationship to canonical P1 convergence

`feat/inspection-mvp-convergence` was created directly from the canonical navigation convergence line and remains ahead of that base without a divergent merge base.

The candidate selectively ports the required inspection/camera-gimbal behavior. It does not whole-merge the old divergent inspection or alternate navigation branches.

This document does not change the status of the canonical P1 gates:

```text
P1-08 full ROS 2 Humble convergence regression: PENDING
P1-09 BUNKER + MID360 field acceptance:          PENDING
P1-10 inspection candidate Code/STATIC:          COMPLETE/PASS
P1-10 inspection candidate HUMBLE/FIELD:         PENDING
```

Therefore this branch is a **frozen P1-10 software candidate**, not proof that the canonical branch is ready to merge to `main`.

## 3. Frozen product boundary

The accepted first-field Runtime path is:

```text
immutable active Site
  -> exact navigation/localization binding
  -> accepted TRACKING localization
  -> Mission Manager
  -> INSPECTION_TASK
  -> versioned single-point TaskGroup navigation
  -> chassis stationary gate
  -> atomic camera-gimbal AcquireView
     -> gimbal motion
     -> stable measured feedback
     -> settle
     -> new image after settle
  -> validate capture timing
  -> associate final image timestamp with localization
  -> persist actual observation context
  -> next view / point
  -> RETURN_HOME
  -> Mission report
```

Real C1 first-field constraints:

```text
schema_version: 2
vision.execution_mode: DEFERRED
online flower inference: OFF
real view acquisition: /camera_gimbal/acquire_view
real capability health: /camera_gimbal/health
inspection hardware opt-in: start_inspection:=true
```

## 4. Frozen ownership model

The selective integration preserves existing Runtime authority boundaries.

```text
agt_site_runtime
  Site validation/activation authority

agt_site_navigation
  active Site -> exact navigation/localization asset binding

agt_localization + GlobalCorrectionManager
  accepted localization + unique map -> odom authority

Nav2 lifecycle manager
  lifecycle authority

agt_navigation
  planning/control/waypoint capability/Collision Monitor

agt_system_manager
  final readiness aggregate

agt_operator_gateway
  external Mission command transport

agt_mission_manager
  finite Mission sequencing + INSPECTION_TASK + RETURN_HOME

agt_inspection
  map-bound inspection orchestration + observation evidence
  does not own Nav2/cmd_vel/TF/Site/safety

camera_gimbal_capability
  atomic gimbal-arrival + post-settle camera acquisition

agt_hardware_bringup
  monitor-first hardware composition and explicit inspection opt-in
```

No new Site, TF, Nav2 lifecycle, recorder, Mission, or chassis command authority was introduced.

## 5. Accepted implementation slices

| Slice | Code | STATIC | HUMBLE | BENCH | FIELD |
| --- | --- | --- | --- | --- | --- |
| Inspection selective port | [x] | [x] | [ ] | N/A | [ ] |
| Schema-v2 multiview contracts | [x] | [x] | [ ] | N/A | [ ] |
| DEFERRED/PENDING_OFFLINE execution | [x] | [x] | [ ] | N/A | [ ] |
| Frozen C1 camera/gimbal vendor snapshot | [x] | [x] | [ ] | [ ] | [ ] |
| Camera-gimbal adapter/error mapping | [x] | [x] | [ ] | [ ] | [ ] |
| Atomic AcquireView executor integration | [x] | [x] | [ ] | [ ] | [ ] |
| Capture-time localization + measured gimbal evidence | [x] | [x] | [ ] | [ ] | [ ] |
| Mission INSPECTION_TASK + RETURN_HOME | [x] | [x] | [ ] | N/A | [ ] |
| Mission/inspection reports | [x] | [x] | [ ] | N/A | [ ] |
| `start_inspection` explicit bringup | [x] | [x] | [ ] | [ ] | [ ] |
| Fresh READY camera-gimbal health admission gate | [x] | [x] | [ ] | [ ] | [ ] |

Legend:

- `STATIC`: source contracts / pure-Python / cloud runner evidence;
- `HUMBLE`: clean Ubuntu 22.04 ROS 2 Humble build/test/runtime evidence;
- `BENCH`: physical camera/gimbal stationary bench evidence;
- `FIELD`: physical robot mission evidence.

## 6. Static freeze evidence

Final behavior integration used RED -> GREEN gating.

### 6.1 Health admission RED

Commit:

```text
e439a488f5efbf5c49606442e4406bc75265b3f8
```

Workflow run:

```text
Inspection MVP / 33281377933
```

Expected RED result:

```text
3 failed, 10 passed
```

The failures were specifically:

- missing `CapabilityHealth` subscription;
- missing camera-gimbal health goal rejection;
- missing Humble CMake registration for health policy test.

### 6.2 Final behavior GREEN

Verified patch workflow:

```text
Apply Inspection Health Freeze / 33281449193
```

The runner patched the candidate working tree, executed all required static regressions, and only then committed the verified result as the frozen behavior SHA.

Observed results:

```text
inspection source/bringup contracts: 13 passed
inspection pure-Python freeze suite: 36 passed
Mission freeze regression:           37 passed
Python compileall:                    PASS
```

The inspection freeze suite includes:

- schema-v2 validation;
- multiview execution;
- DEFERRED vision;
- camera-gimbal adapter;
- atomic view acquisition;
- camera-gimbal health policy.

The resulting commit is:

```text
73b0f2dfe02bb04c5940d8bebbcff2a95fd281d2
fix(inspection): gate real missions on fresh camera gimbal health
```

## 7. Safety/correctness invariants frozen by this candidate

### 7.1 No fake inference result

When `execution_mode=DEFERRED`:

- Runtime does not call online vision inference;
- Runtime does not run point-local aggregation;
- view evidence records `PENDING_OFFLINE`;
- missing inference is not converted to raw/unique count `0`;
- Mission summary keeps deferred count state unknown/pending.

### 7.2 Atomic camera/gimbal observation

The real backend uses one `AcquireView` operation for:

```text
gimbal move -> stable arrival -> settle -> fresh frame -> saved image
```

Runtime validates that the final image is newer than the reached timestamp.

### 7.3 Actual observation metadata only

For real C1 evidence:

- missing image timestamp is an error;
- missing accepted TRACKING localization is an error;
- missing measured gimbal feedback is an error;
- requested pan/tilt values are not substituted for missing measured feedback;
- measured pan, tilt, and roll are persisted when supplied by the atomic C1 backend.

### 7.4 Health fail-closed before mission admission

With `view_backend=camera_gimbal`, a new inspection goal is rejected unless the latest `/camera_gimbal/health` sample is fresh and satisfies:

```text
state == READY
camera_alive == true
gimbal_serial_connected == true
gimbal_feedback_alive == true
move_action_ready == true
busy == false
```

Default admission freshness: `1.5 s`.

### 7.5 Hardware integration remains opt-in

Normal BUNKER/MID360 startup does not require camera/gimbal hardware.

```text
start_inspection=false   # default
```

`start_inspection=true` explicitly composes the frozen C1 capability and inspection server. It cannot be combined with the legacy generic `start_camera`/`start_gimbal` hooks, preventing double ownership of the same hardware.

## 8. Explicitly excluded from this freeze

The following are intentionally not part of the frozen Runtime MVP:

- online litchi-flower model weights/inference;
- cross-view/global flower identity deduplication for real field output;
- HMI map display/editing;
- HMI task authoring/persistence;
- automatic map cleanup;
- new SLAM/localization/planner/controller algorithms;
- direct production RViz goal control;
- camera/gimbal automatic serial reconnect claims not proven on hardware;
- any change to existing Site/TF/lifecycle/safety/chassis authority.

These must be developed after the Runtime field baseline is accepted, preferably outside the frozen candidate until a new scoped milestone is opened.

## 9. Evidence contract for physical acceptance

Every accepted real view must eventually demonstrate:

```text
image exists and non-empty
capture_stamp from final acquired image
robot_pose_map in map frame
localization accepted/TRACKING at capture association
actual gimbal pan_rad
actual gimbal tilt_rad
actual gimbal roll_rad
feedback_valid=true
roll_feedback_valid=true
camera calibration ID
camera calibration SHA256
vision_status=PENDING_OFFLINE
```

The accepted Mission must demonstrate:

```text
P01 -> capture
P02 -> capture
P03 -> capture
RETURN_HOME
final Mission state consistent with reality
inspection evidence linked into Mission report
```

The exact target-machine procedure is frozen in:

```text
docs/runbooks/inspection-mvp-field.md
```

## 10. Remaining gates before physical release

The following remain open and must not be inferred from STATIC evidence:

- [ ] clean Ubuntu 22.04 / ROS 2 Humble `rosdep` + `colcon build`;
- [ ] full `colcon test` with zero failures/errors;
- [ ] BUNKER SocketCAN monitor acceptance;
- [ ] MID360 real stream/timestamp acceptance;
- [ ] real camera device identity/resolution/FPS;
- [ ] real gimbal serial identity/baud/zero/direction/limits;
- [ ] camera calibration identity/hash acceptance;
- [ ] `/camera_gimbal/health` READY/stale/fault behavior;
- [ ] physical atomic `AcquireView` center capture;
- [ ] camera/gimbal disconnect fail-closed check;
- [ ] frozen Site + localization + Nav2 readiness;
- [ ] low-speed P01/P02/P03 + RETURN_HOME mission;
- [ ] per-view evidence audit;
- [ ] Mission report audit.

## 11. Post-freeze change policy

After behavior commit `73b0f2dfe02bb04c5940d8bebbcff2a95fd281d2`:

Allowed without reopening product development:

- acceptance documentation;
- machine/bench/field evidence;
- corrections to documentation that does not match frozen behavior.

A behavior change is allowed only when a downstream gate demonstrates a defect. Required process:

```text
record failing evidence
-> write minimal RED regression
-> implement minimal fix
-> run GREEN static/Humble regression
-> assign new frozen behavior SHA
-> invalidate and rerun affected downstream evidence
```

Forbidden on this frozen line:

- feature expansion;
- online model integration;
- HMI/map editor implementation;
- whole-branch merge from old divergent lines;
- new motion/control authority;
- bypass of Runtime readiness/safety ownership.

## 12. Freeze status

```text
Runtime Inspection MVP behavior:       FROZEN
Frozen behavior SHA:                   73b0f2dfe02bb04c5940d8bebbcff2a95fd281d2
Code/STATIC candidate evidence:        PASS
ROS 2 Humble evidence:                 PENDING
Camera/gimbal physical bench evidence: PENDING
BUNKER/MID360 field evidence:           PENDING
Three-point inspection Mission:        PENDING
Merge-to-main authority:               NOT CLAIMED
```

No further Runtime feature work should be added to this candidate before the pending target-machine and physical gates are executed.
