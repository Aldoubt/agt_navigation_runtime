# agt_inspection

`agt_inspection` owns map-bound stop-and-inspect task assets and, in later implementation tasks,
their Runtime execution. It deliberately does **not** own map generation, Nav2, chassis velocity,
TF, a camera driver, a gimbal protocol or a model implementation.

Inspection assets live below one immutable map version:

```text
runtime/maps/<map_id>/versions/<map_version_id>/inspections/<inspection_task_id>.json
```

Each inspection point references an existing **single-point TaskGroup** by
`task_group_id + task_revision + expected_content_sha256`; x/y/yaw are therefore not duplicated in
the inspection JSON. A future map editor writes navigation points through the existing Task Registry
and only then binds gimbal/camera/vision settings to that TaskGroup.

Schema v1 is strict and hash-bound. The pure Python parser/repository are intentionally ROS-free so
they can be reused by headless validation tools and a future `agt_mission_console`.

Execution order frozen by the design spec is:

```text
ExecuteWaypointTask
-> continuous chassis stationary gate
-> MoveGimbal
-> gimbal settle delay
-> CaptureImage
-> InspectImage
-> persist evidence
```

See `docs/superpowers/specs/2026-08-27-inspection-mission-design.md` and
`docs/superpowers/plans/2026-08-27-inspection-mission-i0-i6.md`.
