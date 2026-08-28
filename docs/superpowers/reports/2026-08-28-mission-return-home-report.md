# Mission RETURN_HOME + Report Implementation Report

Status: **USER-MACHINE E2E GREEN / TEST PATH FIX LANDED / RERUN REQUIRED**

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

## Test-suite issue found during verification

The Mission Manager regression run exposed one repository-layout bug in the newly added ROS contract test:

```text
FileNotFoundError:
/home/yangxuan/agt_navigation_runtime/agt_interfaces/msg/MissionStatus.msg
```

The test incorrectly searched for sibling package `agt_interfaces` at repository root, while packages live under `<repo>/src/`.

The production runtime was not affected; the Mission E2E still completed successfully. The test path was corrected to resolve sibling packages from `src/` in commit:

```text
dd51791 fix(mission-test): resolve sibling interfaces under src
```

Before this fix, the Mission Manager pytest output showed 51 passed and one failed test case. `colcon test-result` represented the same failing contract through its CTest/xUnit layers; this is not treated as two independent runtime defects.

A fresh rerun is still required before marking the whole software test suite GREEN.

The initial `AMENT_PREFIX_PATH` / `CMAKE_PREFIX_PATH` warnings came from stale environment entries after deleting selected install prefixes. They are build-shell hygiene warnings, not the cause of the failing test. Starting a fresh shell and sourcing only `/opt/ros/humble/setup.bash` before rebuilding avoids them.

## Tests landed

- `test_return_home_mission.py`
- `test_mission_report.py`
- `test_return_home_ros_contract.py`
- `test_mock_inspection_return.py`
- existing Mission Manager regression suite remains registered.

The tests cover final-only HOME schema, formal registry binding, executor ordering, report count semantics, ROS wiring, symlink-safe packaging, and hardware-free fixture/launch contracts.

## Verification boundary

Current evidence supports:

```text
Mission mock E2E: USER-MACHINE GREEN
Packaging checks: USER-MACHINE GREEN
RETURN_HOME: USER-MACHINE GREEN in mock path
Mission report export: USER-MACHINE GREEN
Full software regression: PENDING RERUN AFTER TEST-PATH FIX
Real hardware: NOT PART OF THIS ACCEPTANCE
```

No assistant-side ROS 2 Humble build or execution is claimed.

## Rerun gate after test-path fix

Use a fresh shell to avoid stale install-prefix warnings:

```bash
cd ~/agt_navigation_runtime
git checkout feat/inspection-multiview-evidence
git pull

source /opt/ros/humble/setup.bash

python3 -m pytest \
  src/agt_mission_manager/test/test_return_home_ros_contract.py \
  -q

python3 -m pytest \
  src/agt_mission_manager/test \
  -q

colcon test \
  --packages-select agt_interfaces agt_inspection agt_mission_manager

colcon test-result --verbose
```

If the installed packages need rebuilding after the pull:

```bash
rm -rf \
  build/agt_interfaces build/agt_inspection build/agt_mission_manager \
  install/agt_interfaces install/agt_inspection install/agt_mission_manager

source /opt/ros/humble/setup.bash
colcon build \
  --packages-select agt_interfaces agt_inspection agt_mission_manager \
  --symlink-install
source install/setup.bash
```

## Next after full software GREEN

After the regression rerun is clean, freeze this hardware-free Mission milestone and proceed to real visual evidence adapters: encode `original.jpg`, `overlay.jpg`, `mask.png`, preserve visual model version/hash, and wire the Level-1 visual model behind `/agt/vision/inspect` without changing Mission/Nav2 ownership.
