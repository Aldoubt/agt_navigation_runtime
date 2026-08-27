# Inspection Multi-View / Evidence v1 Implementation Report

Status: **CODE_LANDED / LOCAL_VERIFICATION_RERUN_REQUIRED**

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

## Verification round 1 findings

The Runtime machine successfully built `agt_interfaces` and `agt_inspection`, and `ros2 interface show` expanded both new multi-view interfaces. Three verification/test-contract defects were identified and corrected:

1. The first direct source pytest was run before `agt_inspection` had been built and sourced, so Python could not import the package. Verification order is now build -> source -> pytest.
2. `test_ros_contract.py` scanned its own test sources for forbidden navigation tokens, so the literal `nav2_msgs` assertion self-matched. The scan is now restricted to production package/scripts.
3. The same contract test required the exact XML tag `<exec_depend>`, although ROS package `<depend>` also satisfies runtime dependency semantics. The contract now accepts either valid declaration.

## Verification round 2 finding

The Runtime machine then reached 9 passing direct tests with one remaining failure in `test_inspection_ros_nodes_use_only_project_navigation_boundary`. The failure was a stale contract assertion requiring the inspection adapter to explicitly assign the deprecated `ExecuteWaypointTask` compatibility inputs:

```text
goal.task_file = ""
goal.poses = []
goal.loop = False
```

The production adapter correctly never touches those fields; generated ROS messages already initialize them to their empty/false defaults. The formal Runtime path sets only the versioned Task Registry fields (`map_id`, `map_version_id`, `task_group_id`, `task_revision`, hash, loop_count and idempotency key). The test now asserts that assignments to deprecated compatibility fields are absent rather than requiring explicit empty assignments.

A fresh local rerun is required before this milestone can be marked DONE.

## Deliberately not changed in this round

The existing inspection task schema/executor still represents one gimbal pose plus captures. It is not silently reinterpreted as a true multi-view route. A later task must explicitly add a versioned `views[]` inspection-point schema and then invoke `AggregateInspectionViews` after all Level-1 views for that point have been persisted.

This separation keeps the already-tested I0-I6 single-view execution path stable while the multi-view interface and evidence contract are reviewed.

## Required local verification

The latest change is test-only, so after pulling it no rebuild is required if the existing `agt_interfaces` / `agt_inspection` build and install trees are still present:

```bash
cd ~/agt_navigation_runtime
git checkout feat/inspection-multiview-evidence
git pull

source /opt/ros/humble/setup.bash
source install/setup.bash

python3 -m pytest src/agt_inspection/test/test_ros_contract.py -q

colcon test --packages-select agt_inspection
colcon test-result --verbose
```

For a clean full rerun, use:

```bash
colcon build --packages-select agt_interfaces agt_inspection --symlink-install
source install/setup.bash

python3 -m pytest \
  src/agt_interfaces/test/test_multiview_interfaces.py \
  src/agt_inspection/test/test_multiview_evidence.py \
  src/agt_inspection/test/test_multiview_ros_contract.py \
  src/agt_inspection/test/test_ros_contract.py -q

colcon test --packages-select agt_interfaces agt_inspection
colcon test-result --verbose
```

The Runtime machine has already shown that both interfaces are generated and discoverable:

```bash
ros2 interface show agt_interfaces/msg/InspectionViewObservation
ros2 interface show agt_interfaces/action/AggregateInspectionViews
```

Optional mock server smoke test:

```bash
ros2 run agt_inspection mock_view_aggregator_server.py
```

Until the test rerun reports zero failures on the ROS 2 Humble Runtime machine, this milestone is not marked DONE.

## Next task after GREEN

Upgrade the inspection asset schema from one point-level gimbal pose to explicit ordered `views[]` entries, preserve Level-1 evidence for each view, call `/agt/vision/aggregate_views` once all views at a point complete, and feed the aggregation URI/counts into the point/session report.
