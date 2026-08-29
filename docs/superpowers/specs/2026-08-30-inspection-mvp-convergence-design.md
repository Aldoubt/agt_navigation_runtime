# Inspection MVP Convergence Design

Date: 2026-08-30
Base branch: `feat/runtime-navigation-convergence-p1`
Delivery branch: `feat/inspection-mvp-convergence`

## 1. Goal

Converge the already-developed navigation, Mission, inspection, camera-gimbal and evidence capabilities into one vehicle-deployable litchi inspection MVP without reopening the navigation architecture.

The first field-delivery success criterion is intentionally limited to:

```text
Frozen Site active
-> Runtime navigation READY
-> Mission starts
-> navigate to inspection point
-> chassis stationary gate
-> gimbal reaches requested view
-> acquire a strictly post-settle image
-> bind image timestamp to accepted map-frame robot pose
-> persist actual gimbal feedback + image + localization context
-> continue to next point
-> optional RETURN_HOME
-> persist Mission/evidence report
```

Litchi-flower inference is **not** part of the vehicle-motion success gate for this milestone. The default field mode is offline/deferred inference after evidence collection.

## 2. Scope boundary

### In scope

1. Selectively port the inspection capability from `feat/inspection-multiview-evidence` onto the navigation convergence base.
2. Selectively import the already-frozen Autolabor C1 camera-gimbal capability from `feat/camera-gimbal-driver-import`.
3. Preserve the atomic camera-gimbal acquisition semantics of `/camera_gimbal/acquire_view`.
4. Connect Runtime inspection execution to the real camera-gimbal capability through a thin adapter/binding layer rather than duplicating serial or camera logic.
5. Preserve existing map-bound TaskGroup navigation ownership.
6. Persist observation-time robot pose, actual gimbal pose, image timestamp, image URI and localization state for every successful field capture.
7. Add an explicit `DEFERRED` vision execution mode so real-model availability cannot block data collection.
8. Preserve existing `INLINE` vision behavior for mock/regression compatibility.
9. Preserve Mission START/PAUSE/RESUME/CANCEL ownership in `agt_mission_manager` and external command transport in `agt_operator_gateway`.
10. Add hardware-free and ROS 2 Humble acceptance gates before field acceptance.

### Out of scope

1. HMI occupancy-map editing.
2. HMI persistence of newly authored waypoints/tasks.
3. PCD-to-PGM reconstruction changes.
4. New SLAM or localization algorithms.
5. RTAB-Map integration.
6. Online litchi-flower inference as a required Runtime dependency.
7. Mission-level global instance deduplication.
8. Automatic camera view planning.
9. Direct browser-to-ROS communication.
10. Changes to Nav2 safety authority, `/cmd_vel` ownership, Collision Monitor or chassis safety guards.

The HMI/map-authoring work is a separate sub-project after this Runtime vertical slice is frozen.

## 3. Source-branch policy

`feat/runtime-navigation-convergence-p1` remains the canonical product baseline. Old parallel branches are source material only.

### `feat/inspection-multiview-evidence`

Do **not** merge the branch wholesale. Selectively port only the inspection-specific behavior:

- `src/agt_inspection/**`
- inspection-related `agt_interfaces` actions/messages/services
- inspection-related Mission Manager execution/report support
- inspection-specific tests and interface documentation

Explicitly do not port that branch's divergent mapping, navigation, bringup, localization, sensor or platform files.

### `feat/camera-gimbal-driver-import`

Import the frozen vendor snapshot under:

```text
third_party/autolabor_c1_camera_gimbal/
```

Keep device paths and Runtime orchestration outside vendor source. Upstream-compatible bug fixes may be applied only when required by acceptance evidence.

The public hardware capability remains:

```text
/camera_gimbal/acquire_view
/camera_gimbal/health
```

The low-level serial action remains a driver/debug interface and must not become a Mission dependency.

## 4. Authority model

The convergence must preserve the existing ownership model:

```text
agt_site_runtime
  owns Site discovery / validation / activation

agt_site_navigation
  owns Active Site -> exact navigation/localization asset binding
  + read-only NavigationRuntimeStatus

agt_localization + GlobalCorrectionManager
  owns localization evidence and map -> odom correction authority

Nav2 lifecycle manager
  owns Nav2 lifecycle transitions

agt_navigation
  owns waypoint navigation capability and Nav2 execution boundary

Task Registry
  owns mutable versioned task definitions

agt_inspection
  owns stop-and-inspect execution and evidence persistence
  does not own Nav2, TF authority, Site activation, camera serial protocol or model implementation

camera_gimbal_capability
  owns atomic gimbal motion + settle + fresh-image acquisition
  does not own navigation points, Mission order or robot localization

agt_mission_manager
  owns finite sequential Mission lifecycle and Mission report

agt_operator_gateway
  owns HMI transport and guarded Mission lifecycle commands

agt_system_manager
  owns final readiness/blocker aggregation
```

No adapter introduced by this milestone may publish `map -> odom`, `odom -> base_footprint`, `/cmd_vel`, or directly call Nav2 outside the existing navigation capability.

## 5. Inspection task schema

The authoritative field asset remains map/Site-bound and references Task Registry navigation definitions rather than duplicating x/y/yaw.

Schema-v2 multi-view structure remains supported. Add one backward-compatible vision field:

```json
{
  "vision": {
    "execution_mode": "DEFERRED",
    "task_id": "litchi_flower_instance_seg",
    "model_profile": "default",
    "minimum_confidence": 0.6,
    "timeout_s": 10.0
  }
}
```

Allowed values:

```text
INLINE
DEFERRED
```

Compatibility rule:

- missing `execution_mode` => `INLINE`
- explicit `INLINE` => preserve existing Level-1 `InspectImage` requirement
- explicit `DEFERRED` => capture evidence is authoritative and no online `InspectImage` server is required

The first vehicle MVP task should use one view per point unless a multi-view task is intentionally selected. Multi-view support is retained; it is not removed or redesigned.

## 6. Real camera-gimbal binding

The vendor capability already guarantees the critical observation ordering:

```text
gimbal accepted
-> gimbal feedback fresh
-> stable arrival
-> settle_time elapsed
-> obtain a new image generated after settle
-> image_stamp > reached_stamp
-> optional image save succeeds
```

Runtime must reuse this guarantee.

### Binding rule

`agt_inspection` receives a hardware backend implementation that maps one inspection view request to `/camera_gimbal/acquire_view`.

Inspection view semantics:

```text
requested pan/tilt/roll
-> convert Runtime radians to vendor degrees at one boundary only
-> call AcquireView
-> validate success + error_code
-> receive image URI / image stamp / reached stamp / actual feedback fields exposed by the frozen capability
-> construct Runtime observation context
```

If the current vendor result does not expose all required final actual-angle values, the adapter may associate the closest fresh `PantiltAngleInfo`/status sample at or after `reached_stamp`; this association must be explicit, freshness-bounded and tested. The inspection layer must never substitute the requested angle for the actual measured angle when writing authoritative evidence.

### Failure mapping

Vendor error codes map to Runtime stage failures without parsing human-readable strings:

```text
100 invalid goal       -> configuration error / no retry beyond task policy
101 busy               -> retryable gimbal acquisition failure
200 unavailable        -> hardware unavailable
201 rejected           -> gimbal rejected
202 motion failed      -> gimbal failed
300 camera unavailable -> capture unavailable
301 image timeout      -> capture timeout
302 save failed        -> evidence persistence failure
400 canceled           -> authoritative cancellation
900 internal           -> internal failure
```

Mission/inspection retry counts remain task-owned.

## 7. Observation-time pose binding

A capture is valid only when all required observation context is internally consistent.

For every successful view, persist:

```text
session_id
inspection_task_id
point_id
view_id
image_uri
image_stamp
camera_id
camera_calibration_id
requested_gimbal_pose
actual_gimbal_pose
reached_stamp
localization_stamp
robot_pose_map: x, y, z, qx, qy, qz, qw
localization_state
localization_pose_valid
localization_accepted
localization_age_s
```

Pose association rule:

1. Use the image's ROS timestamp as the observation timestamp.
2. Select the nearest fresh accepted `LocalizationStatus` / map-frame pose sample according to the existing inspection evidence policy.
3. Require localization state `TRACKING`, `pose_valid=true`, `localization_accepted=true`.
4. Reject evidence if no sample satisfies the finite freshness bound.
5. Never use the navigation target pose as a substitute for actual observation-time robot pose.

The evidence store remains the authority for persisted observation metadata.

## 8. Deferred vision mode

`DEFERRED` is the default mode for the first litchi field deployment task assets, but not the parser's backwards-compatibility default.

Execution in `DEFERRED` mode:

```text
ExecuteWaypointTask
-> stationary gate
-> acquire each camera-gimbal view
-> persist original image + observation metadata
-> mark vision_status = PENDING_OFFLINE
-> do not call /agt/vision/inspect_image
-> do not call multi-view vision aggregation
-> point succeeds when all required captures/evidence succeed
```

Runtime report rules in deferred mode:

- report capture success/failure counts
- report completed/failed inspection points
- report image/evidence URIs
- do not invent flower counts
- do not expose `raw_instance_count` as zero merely because inference was deferred
- use an explicit nullable/absent inference result plus `vision_status=PENDING_OFFLINE`

A later offline inference process may write derived artifacts below the same immutable session evidence tree, but must not overwrite the original image or observation metadata.

Recommended derived layout:

```text
runtime/inspections/<inspection_task_id>/<session_id>/
├── session.json
├── points/
│   └── P001/
│       └── center/
│           ├── original.jpg
│           ├── observation.json
│           └── derived/
│               └── litchi_flower_instance_seg/
│                   ├── result.json
│                   ├── overlay.jpg
│                   └── masks/
└── report/
    ├── report.json
    ├── points.csv
    └── views.csv
```

Offline model integration itself is not implemented in this milestone.

## 9. Mission integration

Selectively preserve the existing inspection Mission step and RETURN_HOME semantics.

Supported first-field Mission shape:

```text
INSPECTION_TASK
-> optional RETURN_HOME
```

Within the inspection task, each point's navigation is still executed through `/agt/navigation/execute_waypoint_task` using its frozen TaskGroup identity.

The Mission Manager must not know camera serial topics or vendor action types. It only invokes the inspection capability and records child session/report identities.

Pause/resume/cancel semantics remain Runtime-owned. Cancellation must propagate through inspection to any active camera-gimbal acquisition and navigation action using existing action cancellation paths.

## 10. Bringup and configuration

Normal navigation startup remains safe and inspection-off by default.

Add an explicit opt-in inspection composition rather than silently starting camera hardware on every navigation run.

Required Runtime-facing launch/config concepts:

```text
start_inspection=false
inspection_backend=camera_gimbal
camera_device_path=/dev/video0
camera_gimbal_port=/dev/ttyUSB0
camera_width=1920
camera_height=1080
camera_fps=30.0
capture_output_root=<runtime-owned path>
```

For vehicle deployment, stable device aliases under `/dev/serial/by-id/...` and, where practical, `/dev/v4l/by-id/...` should be preferred over volatile ttyUSB/video indices. The repository default must remain non-motion-safe and must not assume a specific field machine device path.

The camera-gimbal capability's current known limitation that serial disconnect does not auto-reconnect remains visible as a health blocker; this milestone does not hide it.

## 11. Runtime readiness

Inspection capability must expose or contribute health sufficient for operator diagnostics.

At minimum distinguish:

```text
READY
BUSY
DEGRADED
ERROR
```

The vehicle Mission start path must fail closed when an inspection Mission requires camera-gimbal hardware but the capability is not READY/usable.

This does not mean generic navigation Missions require inspection hardware. Readiness is capability/task specific; camera failure must not make an unrelated navigation-only Mission impossible.

## 12. Tests and acceptance

### Static / pure-Python gate

Required before ROS integration claims:

- schema parses `INLINE` and `DEFERRED`
- missing execution mode remains `INLINE`
- deferred execution never dispatches the vision action
- deferred reports never fabricate counts
- hardware adapter maps vendor success/failure codes deterministically
- requested radians -> vendor degrees conversion is tested
- actual gimbal feedback, not request value, is persisted
- stale localization prevents successful evidence persistence
- cancellation is propagated
- selective-port source guard prevents reintroduction of divergent mapping/navigation ownership

### ROS 2 Humble gate

On Ubuntu 22.04 / ROS 2 Humble:

1. Build selected packages and vendor dependencies from a clean workspace overlay.
2. Run package tests with zero errors/failures.
3. Run a hardware-free full Mission E2E using mock navigation plus fake camera-gimbal capability in `DEFERRED` mode.
4. Verify the Mission succeeds without any vision server running.
5. Inspect generated evidence and verify every image observation contains a map pose and actual gimbal pose.
6. Run cancel during gimbal acquisition and verify authoritative cancellation.

### Camera-gimbal bench gate

With the physical C1 camera/gimbal but chassis motion disabled:

1. Confirm `/camera_gimbal/health` transitions to READY.
2. Execute center, left and right acquisitions.
3. Verify `image_stamp > reached_stamp` for every successful capture.
4. Verify actual feedback is within configured tolerance.
5. Verify image files decode and have expected dimensions.
6. Disconnect/reconnect failure is surfaced as non-READY and does not return false success.

### Vehicle field gate

Begin with a frozen Site and three inspection points:

```text
P01 center
P02 center
P03 center
RETURN_HOME
```

Acceptance:

- Runtime navigation reaches all three points through the formal waypoint capability.
- stationary gate passes before each view acquisition.
- exactly one valid image/evidence observation is produced per point.
- each observation contains fresh accepted map-frame robot pose.
- each observation contains actual gimbal feedback.
- no online vision server is required.
- Mission reaches SUCCEEDED and optional RETURN_HOME succeeds.
- generated report references all three evidence observations.
- physical E-stop remains available during the test.

Only after this gate is green should field tasks expand to three views per point or online inference.

## 13. Non-regression requirements

The implementation must not regress:

- Site Package validation/activation
- NavigationRuntimeStatus fail-closed semantics
- Task Registry storage and Site binding
- direct RViz goal guard
- Mission command idempotency/auth guard
- BUNKER monitor-first bringup
- FAST-LIVO2 odometry ownership
- GlobalCorrectionManager TF ownership
- Collision Monitor / `agt_safety` command path
- normal navigation-only operation without camera hardware

## 14. Merge strategy

Implementation work stays on `feat/inspection-mvp-convergence` until all static and Humble gates are green.

Preferred integration sequence:

```text
1. inspection interfaces/schema/evidence pure logic
2. deferred-vision execution path
3. Mission inspection/report selective port
4. vendor camera-gimbal snapshot import
5. camera-gimbal inspection adapter
6. optional bringup composition + capability readiness
7. mock full Mission E2E
8. camera-gimbal bench acceptance
9. three-point vehicle acceptance
```

Do not merge this branch back to the navigation convergence line merely because static tests pass. The merge decision requires at least the ROS 2 Humble gate; vehicle acceptance may be recorded as a separate field gate if the product branch needs to proceed to HMI integration first.

## 15. Follow-on sub-projects

After the Runtime vertical slice is frozen, create separate specs/plans for:

1. HMI real occupancy-map preview + minimal erase/polygon-erase/undo editing.
2. Map edit revision persistence and Site Package regeneration/activation.
3. HMI waypoint/inspection-task authoring persistence through a guarded Runtime API.
4. Offline litchi-flower inference and report enrichment.

These follow-on features must consume the Runtime contracts from this design rather than changing the navigation authority model again.
