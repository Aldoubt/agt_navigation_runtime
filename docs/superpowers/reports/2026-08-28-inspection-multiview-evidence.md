# Inspection Multi-View / Evidence v1 Implementation Report

Status: **CODE_LANDED / LOCAL_VERIFICATION_REQUIRED**

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

## Deliberately not changed in this round

The existing inspection task schema/executor still represents one gimbal pose plus captures. It is not silently reinterpreted as a true multi-view route. A later task must explicitly add a versioned `views[]` inspection-point schema and then invoke `AggregateInspectionViews` after all Level-1 views for that point have been persisted.

This separation keeps the already-tested I0-I6 single-view execution path stable while the multi-view interface and evidence contract are reviewed.

## Required local verification

```bash
source /opt/ros/humble/setup.bash

python3 -m pytest \
  src/agt_interfaces/test/test_multiview_interfaces.py \
  src/agt_inspection/test/test_multiview_evidence.py \
  src/agt_inspection/test/test_multiview_ros_contract.py -q

colcon build --packages-select agt_interfaces agt_inspection --symlink-install
source install/setup.bash
colcon test --packages-select agt_interfaces agt_inspection
colcon test-result --verbose

ros2 interface show agt_interfaces/msg/InspectionViewObservation
ros2 interface show agt_interfaces/action/AggregateInspectionViews
ros2 run agt_inspection mock_view_aggregator_server.py
```

Until these commands pass on the ROS 2 Humble Runtime machine, this milestone is not marked DONE.

## Next task after GREEN

Upgrade the inspection asset schema from one point-level gimbal pose to explicit ordered `views[]` entries, preserve Level-1 evidence for each view, call `/agt/vision/aggregate_views` once all views at a point complete, and feed the aggregation URI/counts into the point/session report.
