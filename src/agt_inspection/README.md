# agt_inspection

`agt_inspection` owns map-bound stop-and-inspect task assets and their Runtime execution. It deliberately does **not** own map generation, Nav2, chassis velocity, TF, a camera driver, a gimbal protocol or a visual-model implementation.

Inspection assets live below one immutable map version:

```text
runtime/maps/<map_id>/versions/<map_version_id>/inspections/<inspection_task_id>.json
```

Each inspection point references an existing **single-point TaskGroup** by `task_group_id + task_revision + expected_content_sha256`; x/y/yaw are therefore not duplicated in the inspection JSON. A future map editor writes navigation points through the existing Task Registry and only then binds inspection settings to that TaskGroup.

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
    "timeout_s": 10.0
  },
  "retry": {
    "navigation": 1,
    "gimbal": 1,
    "capture": 2,
    "inference": 1
  },
  "aggregation": {
    "enabled": true,
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

Schema-v2 execution is:

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

Level 1 is authoritative for task progress. Every successful view must produce valid JSON containing a non-negative integer `raw_count`; a Level-1 capture/inference failure fails the inspection point.

Level 2 is an optional enhancement path. `/agt/vision/aggregate_views` performs only `POINT_LOCAL` association for one `session_id + point_id`. If the aggregation server is unavailable, rejects the goal, fails, or exceeds its finite Runtime timeout, the executor preserves all Level-1 evidence, writes `aggregation/failure.json`, reports `VIEW_RAW`, and continues. Cancellation remains authoritative.

Capture evidence records the actual observation context, not only the requested navigation target. The Runtime associates the camera image timestamp with the nearest fresh, accepted `LocalizationStatus` in `TRACKING`, records that map-frame pose, and records final gimbal feedback plus camera calibration identity.

## Evidence layout

`agt_inspection.multiview_evidence.InspectionEvidenceStore` owns:

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
│           ├── result.json       # successful Level 2
│           └── failure.json      # nonblocking Level-2 failure
└── report/
    ├── report.json
    ├── points.csv
    ├── views.csv
    └── instances.csv
```

The pure evidence store does not invent JPEG/PNG codecs. The current mock path stores raw ROS image bytes as `original.bin`; real camera/vision adapters are responsible for exporting user-facing encoded original/overlay/mask assets and providing their URIs.

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

The fixture contains two navigation points and three ordered views per point. Mock Level 1 returns `raw_count=3` per view. The mock aggregator is deliberately a **no-dedup baseline** (`dedup_applied=false`), so a successful mock run reports 18 raw and 18 point-local unique instances while proving the Runtime integration path without claiming real ID cleaning.

See:

- `docs/superpowers/specs/2026-08-27-inspection-mission-design.md`
- `docs/superpowers/plans/2026-08-27-inspection-mission-i0-i6.md`
- `docs/interfaces/inspection-multiview-v1.md`
- `docs/superpowers/reports/2026-08-28-inspection-schema-v2-multiview-execution.md`
