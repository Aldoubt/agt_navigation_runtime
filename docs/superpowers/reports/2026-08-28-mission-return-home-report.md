# Mission RETURN_HOME + Report Implementation Report

Status: **USER-MACHINE GREEN / FULL SOFTWARE REGRESSION GREEN / MOCK MISSION E2E GREEN**

Branch: `feat/inspection-multiview-evidence`

## Prerequisite milestone

Inspection Schema v2 / MultiView hardware-free E2E is user-machine GREEN. The supplied run completed P001 and P002, each with three explicit views and point-local aggregation, then returned `success=true`, `error_code=0`, and Action status `SUCCEEDED`.

## Goal

Extend the successful inspection child into the normal field mission shape:

```text
INSPECTION_TASK
-> RETURN_HOME
-> Mission SUCCEEDED
-> Mission report export
```

This milestone does not implement unconditional recovery-home after a fault. HOME motion remains gated by active map identity, accepted localization, and TaskReadiness.

## RETURN_HOME contract

`StepType.RETURN_HOME=5` / `MissionStatus.STEP_RETURN_HOME=5` is a dedicated final mission step.

Schema:

```yaml
- id: return_home
  type: RETURN_HOME
  task_group_id: home_greenhouse_01
  task_group_revision: 1
  expected_content_sha256: sha256:...
```

Rules:

- at most one RETURN_HOME;
- RETURN_HOME must be the final step;
- portable TaskGroup id;
- positive revision;
- canonical sha256;
- map/localization/readiness revalidated immediately before motion.

`RosTaskGroupRunner` sends only the formal `ExecuteWaypointTask` registry fields:

```text
map_id
map_version_id
task_group_id
task_revision
expected_content_sha256
loop_count=1
client_request_id
```

It does not populate deprecated `task_file`, `poses`, or `loop` compatibility inputs.

## Mission report

`MissionReportWriter` creates:

```text
runtime/mission_reports/<mission_id>/<run_id>/
├── report.json
├── steps.csv
└── inspections.csv
```

Inspection child `session_id` and `evidence_root_uri` are preserved. When `<evidence_root_uri>/report/report.json` exists, the Mission report summarizes:

- count target;
- inspection count mode;
- raw instance total;
- point-local unique total;
- ambiguous total.

Cross-point semantics remain explicit. A sum of successful `POINT_DEDUP` child totals is exported only as:

```text
point_sum_estimate
count_semantics = POINT_SUM_ESTIMATE
mission_dedup_applied = false
```

The report does not expose `global_unique_count` or claim whole-mission ID cleaning.

`ExecuteMission.Result` includes `report_uri`.

## Hardware-free Mission fixture

Fixture:

```text
mock_inspection_return / v1
```

Mission hash:

```text
sha256:825ea0ff78b237a64f5fea6419aac99117ff4bc870746d492410b7a1947c0ec0
```

Steps:

```text
INSPECTION_TASK inspection_multiview_two_point
RETURN_HOME home_mock
```

`mock_inspection_return.launch.py` copies the installed mission fixture into a writable `/tmp/agt_mission_mock_runtime`, includes the existing `agt_inspection` mock stack, and starts Mission Manager with the sequential backend after a short delay so mock localization/readiness is fresh.

No real BUNKER/CAN/Nav2 launch is part of this hardware-free acceptance.

## Symlink-install packaging

The Git tree stores `scripts/mission_manager_node.py` as mode 0644. To avoid repeating the earlier `agt_inspection` libexec failure, CMake stages an executable build-tree copy with owner/group/world execute permissions before `install(PROGRAMS ...)`.

User-machine packaging checks passed:

```text
mission_manager_exec_OK
agt_mission_manager mission_manager_node.py
mission_fixture_OK
```

## User-machine Mission E2E evidence

The user-machine hardware-free Mission run completed the intended sequence:

```text
VALIDATING
-> RUNNING
-> INSPECTION_TASK (step type 4)
-> RETURN_HOME (step type 5)
-> Mission state 9 / completed
```

Action result:

```text
success: true
error_code: 0
Goal finished with status: SUCCEEDED
```

The returned report URI was non-empty and resolved to an exported report under:

```text
/tmp/agt_mission_mock_runtime/mission_reports/mock_inspection_return/<run_id>/report.json
```

The supplied report verified:

```text
home_returned = true
success = true
state = SUCCEEDED
inspection_summary.count_semantics = POINT_SUM_ESTIMATE
inspection_summary.mission_dedup_applied = false
inspection_summary.point_sum_estimate = 18
inspection_summary.raw_instance_count = 18
```

Both Mission steps are recorded as successful, including the `RETURN_HOME` child session.

Inspection evidence, aggregation JSON, per-view results, Mission audit log, Mission report JSON, `steps.csv`, and `inspections.csv` were all present in the supplied filesystem listing.

Therefore the **hardware-free Mission E2E is GREEN on the user machine**.

## Regression issue and closure

During the first regression run, `test_return_home_ros_contract.py` incorrectly resolved sibling package `agt_interfaces` at repository root instead of `<repo>/src/agt_interfaces`. The production runtime was unaffected and the Mission E2E still succeeded.

The test path was corrected in commit:

```text
dd51791 fix(mission-test): resolve sibling interfaces under src
```

The user subsequently reran the requested targeted pytest, full Mission Manager pytest suite, and selected-package CTest gate and reported that **all tests passed with 0 failures**.

The earlier `AMENT_PREFIX_PATH` / `CMAKE_PREFIX_PATH` warnings were stale shell entries after deleting selected install prefixes and were not causal.

## Verification boundary

Current evidence supports:

```text
Inspection Schema v2 / MultiView mock E2E: USER-MACHINE GREEN
Mission mock E2E: USER-MACHINE GREEN
Packaging checks: USER-MACHINE GREEN
RETURN_HOME: USER-MACHINE GREEN in mock path
Mission report export: USER-MACHINE GREEN
Full selected software regression: USER-REPORTED GREEN / 0 FAILURES
Real hardware: NOT PART OF THIS ACCEPTANCE
```

No assistant-side ROS 2 Humble build or execution is claimed.

## Frozen milestone

This hardware-free Mission milestone is now frozen. Further work should not expand Mission Manager unless a concrete runtime requirement demands it.

The next implementation line is real visual evidence integration:

```text
Capture sensor_msgs/Image
-> encode original.jpg
-> Level-1 /agt/vision/inspect
-> persist overlay.jpg + mask.png + result.json
-> preserve model_id / model_version / weights_sha256
-> Mission report references those artifacts
```

Mission, Nav2, localization, and motion ownership remain unchanged.
