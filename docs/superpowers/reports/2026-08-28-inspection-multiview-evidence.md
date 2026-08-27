# Inspection Multi-View / Evidence v1 Implementation Report

Status: **USER-MACHINE GREEN / 0 FAILURES**

Branch: `feat/inspection-multiview-evidence`

## Landed

- `agt_interfaces/msg/InspectionViewObservation.msg`
  - capture-time robot pose, optional camera pose, gimbal feedback, calibration identity;
  - typed Level-1 raw count/model version and evidence URIs;
  - full single-view result remains in JSON.
- `agt_interfaces/action/AggregateInspectionViews.action`
  - point-local multi-view association only;
  - typed raw/unique/ambiguous counts and association confidence;
  - fail-closed map/calibration/association error codes.
- `agt_inspection.multiview_evidence.InspectionEvidenceStore`
  - canonical `session -> points -> views -> aggregation -> report` layout;
  - atomic JSON/binary/CSV writes;
  - report exports `report.json`, `points.csv`, `views.csv`, `instances.csv`;
  - count modes `VIEW_RAW`, `POINT_DEDUP`, `MIXED`.
- `mock_view_aggregator_server.py`
  - serves `/agt/vision/aggregate_views`;
  - intentionally performs no dedup and returns `unique == raw` with `dedup_applied=false`;
  - validates point/map and camera calibration consistency.
- Static/pure-Python regression contracts added for interfaces, evidence layout and mock ROS boundary.
- Interface/evidence design frozen in `docs/interfaces/inspection-multiview-v1.md`.

## Verification history

The Runtime-machine verification exposed three inherited verification/test-contract defects and one stale deprecated-field assertion. They were corrected without weakening the production navigation boundary:

1. Package-importing pytest now runs after build/source.
2. Forbidden Nav2 token scanning is restricted to production Python instead of scanning the test itself.
3. Runtime dependency tests accept either ROS package `<depend>` or `<exec_depend>` declarations.
4. The inspection adapter is required to leave deprecated `ExecuteWaypointTask` direct inputs untouched instead of explicitly assigning their generated defaults.

After these fixes, the user reported the affected local verification rerun completed with **0 failures**. This report records that as user-machine evidence; no claim is made that ROS/colcon was independently executed in the assistant environment.

## Frozen v1 boundary

- Level 1 remains independently usable as per-view `VIEW_RAW` evidence.
- Level 2 is `POINT_LOCAL`; no cross-point or cross-session identity recovery is claimed.
- `mock_view_aggregator_server.py` is a no-dedup integration baseline, not a real ID-cleaning implementation.

## Successor work

Schema-v2 multi-view execution is being implemented on the same feature branch in `docs/superpowers/reports/2026-08-28-inspection-schema-v2-multiview-execution.md`.
