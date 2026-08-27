# Inspection Multi-View Vision and Evidence Contract v1

## Scope

This contract freezes the two-level visual workflow for stop-and-inspect missions.

- Level 1 (`VIEW_RAW`) is mandatory: every captured image is independently inspected and keeps its raw instance count and segmentation evidence.
- Level 2 (`POINT_DEDUP`) is optional/enhanced: observations from the same `session_id + point_id` are associated and duplicate local instances are merged into point-local global ids.
- Level 2 never blocks the existence or export of Level-1 evidence.
- V1 does not define cross-point, cross-session or cross-day Re-ID.

## Runtime flow

```text
Navigate point
  -> wait robot stationary
  -> move gimbal
  -> capture image
  -> InspectImage (Level 1)
  -> persist view observation
  -> repeat views
  -> AggregateInspectionViews (Level 2, optional)
  -> persist point aggregation
  -> build report
```

`InspectionViewObservation.robot_pose_map` is the actual capture-time pose. The requested Nav2 goal is task intent, not visual geometry evidence.

## ROS interfaces

### `/agt/vision/inspect`

Single image -> model-independent summary + model-specific `result_json`.

The Level-1 JSON should preserve instance-level local ids, confidence, bbox/mask representation and `raw_count`.

### `/agt/vision/aggregate_views`

Action type: `agt_interfaces/action/AggregateInspectionViews`.

V1 aggregation scope is fixed to `POINT_LOCAL`. Inputs are `InspectionViewObservation[]`; output exposes:

- `raw_instance_count`: sum/authoritative raw observation count before ID cleaning;
- `unique_instance_count`: deduplicated point-local count;
- `ambiguous_instance_count`: associations intentionally left unresolved;
- `association_confidence`: model/algorithm-level summary, not a navigation confidence;
- `result_json`: global instance membership and domain details.

A mock baseline is allowed to return `unique == raw` with `dedup_applied=false`; it must not pretend that ID cleaning was performed.

## Evidence layout

Canonical v1 layout:

```text
runtime/inspections/<inspection_task_id>/<session_id>/
├── session.json
├── points/
│   └── P001/
│       ├── view_001/
│       │   ├── original.<encoded suffix>
│       │   ├── overlay.<encoded suffix>
│       │   ├── mask.<encoded suffix>
│       │   └── result.json
│       ├── view_002/...
│       └── aggregation/
│           ├── result.json
│           └── association_overlay.<encoded suffix>
└── report/
    ├── report.json
    ├── points.csv
    ├── views.csv
    └── instances.csv
```

The pure evidence store does not invent image codecs. ROS/camera adapters supply encoded bytes and a matching suffix (`.jpg`, `.png`, etc.). Tests may use `.bin`.

## View result minimum content

Each `points/<point>/<view>/result.json` carries:

- session/task/map/point identity;
- capture stamp;
- actual `robot_pose_map`;
- gimbal pan/tilt and whether real feedback was available;
- camera calibration id/hash;
- evidence file names/URIs;
- Level-1 model id/version/inference time/raw count;
- complete model-specific result JSON or equivalent nested data;
- warnings.

## Aggregation result minimum content

Each `points/<point>/aggregation/result.json` carries:

- `aggregation_scope = POINT_LOCAL`;
- aggregator id/version;
- raw/unique/ambiguous counts;
- association confidence;
- `global_instances[]` with point-local `global_instance_id` and member `(view_id, local_instance_id)` pairs;
- warnings.

Uncertain matches should remain `AMBIGUOUS`; aggressive merging is not an acceptable fallback.

## Report semantics

`report/report.json` uses one of three count modes:

- `VIEW_RAW`: no point aggregation exists;
- `POINT_DEDUP`: all recorded points have point-local aggregation;
- `MIXED`: only some points have Level-2 aggregation.

`points.csv` reports each point's view count and raw/unique/ambiguous values. `views.csv` preserves capture pose, gimbal pose, model version and raw count. `instances.csv` expands global-instance memberships when Level 2 exists.

When observation regions of different navigation points overlap, summing point-local `unique_count` is only a point-sum estimate. V1 does not claim mission-wide unique counting.

## Version and experiment rules

Always preserve Level-1 outputs even after Level-2 aggregation so experiments can compare:

```text
VIEW_RAW baseline
vs
POINT_DEDUP enhanced
```

Every exported result should remain traceable to model/aggregator ids and versions and, where available, weight/calibration hashes.
