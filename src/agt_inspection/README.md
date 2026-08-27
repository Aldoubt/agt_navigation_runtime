# agt_inspection

`agt_inspection` owns map-bound stop-and-inspect task assets and their Runtime execution. It deliberately does **not** own map generation, Nav2, chassis velocity, TF, a camera driver, a gimbal protocol or a visual-model implementation.

Inspection assets live below one immutable map version:

```text
runtime/maps/<map_id>/versions/<map_version_id>/inspections/<inspection_task_id>.json
```

Each inspection point references an existing **single-point TaskGroup** by
`task_group_id + task_revision + expected_content_sha256`; x/y/yaw are therefore not duplicated in the inspection JSON. A future map editor writes navigation points through the existing Task Registry and only then binds gimbal/camera/vision settings to that TaskGroup.

Schema v1 is strict and hash-bound. The pure Python parser/repository are intentionally ROS-free so they can be reused by headless validation tools and a future `agt_mission_console`.

The current Level-1 execution order is:

```text
ExecuteWaypointTask
-> continuous chassis stationary gate
-> MoveGimbal
-> gimbal settle delay
-> CaptureImage
-> InspectImage
-> persist single-view evidence
```

Visual counting is split into two independent levels:

- **Level 1 / VIEW_RAW**: every captured image keeps its own instance result and `raw_count`. This is mandatory and must remain usable even if cross-view ID association is unfinished.
- **Level 2 / POINT_DEDUP**: `/agt/vision/aggregate_views` associates multiple `InspectionViewObservation` records from the same `session_id + point_id` and returns raw/unique/ambiguous counts. V1 does not perform cross-point or cross-session Re-ID.

`agt_inspection.multiview_evidence.InspectionEvidenceStore` freezes the canonical multi-view evidence/report layout under:

```text
runtime/inspections/<inspection_task_id>/<session_id>/
```

with `points/<point>/view_*`, optional `points/<point>/aggregation`, and `report/{report.json,points.csv,views.csv,instances.csv}`. The pure store does not invent JPEG/PNG codecs; camera/vision adapters provide encoded bytes and matching suffixes.

`mock_view_aggregator_server.py` is deliberately a **no-dedup baseline**: it exposes the final ROS Action contract but returns `unique == raw` and `dedup_applied=false`. It exists so Runtime integration is not blocked while the vision team develops real point-local ID cleaning.

See:

- `docs/superpowers/specs/2026-08-27-inspection-mission-design.md`
- `docs/superpowers/plans/2026-08-27-inspection-mission-i0-i6.md`
- `docs/interfaces/inspection-multiview-v1.md`
