# agt_inspection

`agt_inspection` owns map-bound stop-and-inspect task assets and their Runtime execution. It deliberately does **not** own map generation, Nav2, chassis velocity, TF, vendor camera/gimbal internals, or the litchi visual-model implementation.

Inspection assets live below one immutable map version:

```text
runtime/maps/<map_id>/versions/<map_version_id>/inspections/<inspection_task_id>.json
```

Each inspection point references an existing **single-point TaskGroup** by `task_group_id + task_revision + expected_content_sha256`; x/y/yaw are therefore not duplicated in the inspection JSON. A future map/task editor writes navigation points through the existing Task Registry and only then binds inspection settings to that TaskGroup.

## Frozen MVP boundary

The first real-vehicle inspection MVP is intentionally limited to:

```text
Navigate to bound point
-> continuous chassis stationary gate
-> atomic camera-gimbal AcquireView
-> post-settle image
-> actual image timestamp + actual gimbal feedback
-> nearest fresh accepted TRACKING LocalizationStatus
-> persist image + robot_pose_map + gimbal + camera calibration identity
-> next view / next point
-> Mission RETURN_HOME
-> report
```

The real C1 backend uses the vendored `camera_gimbal_capability` through `/camera_gimbal/acquire_view` and admits new inspection goals only while `/camera_gimbal/health` is fresh and READY.

For this frozen MVP, real C1 tasks must use schema v2 and:

```json
"vision": {
  "task_id": "litchi_flower_instance_seg",
  "model_profile": "default",
  "minimum_confidence": 0.6,
  "timeout_s": 10.0,
  "execution_mode": "DEFERRED"
}
```

`DEFERRED` means Runtime captures authoritative evidence but does **not** invoke online flower inference or view aggregation. Evidence and reports use `PENDING_OFFLINE`; unknown counts remain unknown and are never rewritten as zero.

The legacy/inline mock path remains for software regression and future model integration, but it is not the first field-deployment path.

## Schema versions

Schema v1 remains supported as the legacy single-view shape:

```text
point.gimbal + camera.capture_count
```

Schema v2 is the authoritative true multi-view shape. It adds a task-level `count_target`, removes the point-level gimbal pose and requires explicit ordered `views[]` entries. `camera.capture_count` must be `1` in schema v2; repeated captures are not reinterpreted as different viewpoints.

Example point:

```json
{
  "id": "P001",
  "navigation": {
    "task_group_id": "inspection-P001-nav",
    "task_revision": 1,
    "expected_content_sha256": "sha256:..."
  },
  "stabilization": {
    "linear_velocity_max_mps": 0.02,
    "angular_velocity_max_radps": 0.03,
    "stable_duration_s": 0.8,
    "timeout_s": 5.0
  },
  "camera": {
    "camera_id": "inspection_camera",
    "capture_count": 1,
    "capture_interval_s": 0.0
  },
  "vision": {
    "task_id": "litchi_flower_instance_seg",
    "model_profile": "default",
    "minimum_confidence": 0.6,
    "timeout_s": 10.0,
    "execution_mode": "DEFERRED"
  },
  "retry": {
    "navigation": 1,
    "gimbal": 1,
    "capture": 2,
    "inference": 1
  },
  "aggregation": {
    "enabled": false,
    "aggregation_profile": "default"
  },
  "views": [
    {
      "id": "view_left",
      "gimbal": {
        "pan_rad": -0.5236,
        "tilt_rad": -0.1745,
        "timeout_s": 5.0,
        "settle_duration_s": 0.5
      }
    },
    {
      "id": "view_center",
      "gimbal": {
        "pan_rad": 0.0,
        "tilt_rad": -0.1745,
        "timeout_s": 5.0,
        "settle_duration_s": 0.5
      }
    },
    {
      "id": "view_right",
      "gimbal": {
        "pan_rad": 0.5236,
        "tilt_rad": -0.1745,
        "timeout_s": 5.0,
        "settle_duration_s": 0.5
      }
    }
  ]
}
```

## Execution semantics

### Real frozen C1 backend

With `view_backend=camera_gimbal`, schema v2 and `DEFERRED`:

```text
ExecuteWaypointTask once
-> continuous chassis stationary gate
-> for each ordered view:
     AcquireView
       -> gimbal motion
       -> stable feedback
       -> settle
       -> new image after settle
     -> validate image_stamp > reached_stamp
     -> capture-time LocalizationStatus association
     -> persist view evidence as PENDING_OFFLINE
-> build session report
```

There is no requested-angle fallback in this path. If image timestamp, accepted localization, or actual gimbal feedback is unavailable, the view fails closed rather than inventing observation metadata.

### Legacy / INLINE backend

The compatibility path remains:

```text
ExecuteWaypointTask once
-> continuous chassis stationary gate
-> for each ordered view:
     MoveGimbal
     -> gimbal settle
     -> CaptureImage
     -> InspectImage (Level 1)
     -> persist view evidence
-> optional AggregateInspectionViews (Level 2)
-> persist point aggregation/failure
-> build session report
```

For `INLINE`, Level 1 is authoritative for task progress. Every successful view must produce valid JSON containing a non-negative integer `raw_count`; a Level-1 capture/inference failure fails the inspection point.

Level 2 is optional and only performs `POINT_LOCAL` association for one `session_id + point_id`. If aggregation is unavailable or fails, Level-1 evidence remains authoritative and the failure is nonblocking. This does not claim whole-mission/global identity deduplication.

## Capture context and evidence

Capture evidence records the actual observation context, not only the requested navigation target. Runtime associates the final image timestamp with the nearest fresh, accepted `LocalizationStatus` in `TRACKING`, records the map-frame pose, records final measured gimbal feedback, and records camera calibration identity.

`InspectionEvidenceStore` owns:

```text
runtime/inspections/<inspection_task_id>/<session_id>/
├── session.json
├── points/
│   └── P001/
│       ├── view_left/
│       │   ├── original.*
│       │   └── result.json
│       ├── view_center/
│       ├── view_right/
│       └── aggregation/
│           ├── result.json
│           └── failure.json
└── report/
    ├── report.json
    ├── points.csv
    ├── views.csv
    └── instances.csv
```

Mission-level evidence is written separately under:

```text
runtime/mission_reports/<mission_id>/<run_id>/
├── report.json
├── steps.csv
└── inspections.csv
```

The Mission report links child inspection evidence; it does not re-own or silently rewrite it.

## Real C1 bringup

The preferred field entry point is the hardware composition, with inspection disabled unless explicitly enabled:

```bash
ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  sensor_profile:=hardware_check \
  start_inspection:=true \
  inspection_camera_device_path:=/dev/video0 \
  inspection_camera_gimbal_port:=/dev/ttyUSB0 \
  inspection_camera_calibration_id:=<verified-calibration-id> \
  inspection_camera_calibration_sha256:=<verified-calibration-sha256>
```

The standalone inspection composition is:

```bash
ros2 launch agt_inspection camera_gimbal_inspection.launch.py \
  camera_device_path:=/dev/video0 \
  camera_gimbal_port:=/dev/ttyUSB0 \
  camera_calibration_id:=<verified-calibration-id> \
  camera_calibration_sha256:=<verified-calibration-sha256>
```

Do not combine `start_inspection:=true` with the generic `start_camera` / `start_gimbal` hooks.

## Hardware-free mock acceptance

After building and sourcing `agt_interfaces` and `agt_inspection`:

```bash
rm -rf /tmp/agt_inspection_mock_evidence
ros2 launch agt_inspection mock_inspection.launch.py
```

In a second shell:

```bash
source /opt/ros/humble/setup.bash
source ~/agt_navigation_runtime/install/setup.bash

ros2 action send_goal \
  /agt/inspection/execute_task \
  agt_interfaces/action/ExecuteInspectionTask \
  "{map_id: 'mock_map', map_version_id: 'v1', inspection_task_id: 'inspection_multiview_two_point', task_revision: 1, expected_content_sha256: 'sha256:aaa7c6b351e434dbcb2c903dcb4801a0a621c6fcf64ab0506de766528b7191cf', client_request_id: 'mock-multiview-001'}" \
  --feedback
```

The fixture contains two navigation points and three ordered views per point. The mock INLINE path proves the integration contract only; it does not constitute real model, real camera/gimbal, Humble target-machine, or field acceptance.

## Freeze evidence

The frozen inspection-MVP software record and field procedure are:

- `docs/acceptance/2026-08-30-inspection-mvp-runtime-freeze.md`
- `docs/runbooks/inspection-mvp-field.md`

Static/cloud evidence must not be relabeled as ROS 2 Humble or physical-vehicle evidence.
