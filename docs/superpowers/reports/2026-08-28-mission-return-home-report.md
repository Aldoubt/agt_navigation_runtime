# Mission RETURN_HOME + Report Implementation Report

Status: **CODE_LANDED / LOCAL_VERIFICATION_REQUIRED**

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

`ExecuteMission.Result` now includes `report_uri`.

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

The Git tree stores `scripts/mission_manager_node.py` as mode 0644. To avoid repeating the earlier `agt_inspection` libexec failure, CMake now stages an executable build-tree copy with owner/group/world execute permissions before `install(PROGRAMS ...)`.

## Tests landed

- `test_return_home_mission.py`
- `test_mission_report.py`
- `test_return_home_ros_contract.py`
- `test_mock_inspection_return.py`
- existing Mission Manager regression suite remains registered.

The new tests cover final-only HOME schema, formal registry binding, executor ordering, report count semantics, ROS wiring, symlink-safe packaging, and hardware-free fixture/launch contracts.

## Verification boundary

These RETURN_HOME/Mission-report changes have not been independently built or executed in the assistant environment. ROS 2 Humble build, pytest/CTest and Mission mock E2E require fresh user-machine verification before this milestone becomes GREEN.

## Local software gate

```bash
cd ~/agt_navigation_runtime
git checkout feat/inspection-multiview-evidence
git pull

source /opt/ros/humble/setup.bash

rm -rf \
  build/agt_interfaces build/agt_inspection build/agt_mission_manager \
  install/agt_interfaces install/agt_inspection install/agt_mission_manager

colcon build \
  --packages-select agt_interfaces agt_inspection agt_mission_manager \
  --symlink-install

source install/setup.bash

python3 -m pytest src/agt_mission_manager/test -q

colcon test \
  --packages-select agt_interfaces agt_inspection agt_mission_manager

colcon test-result --verbose
```

Packaging checks:

```bash
test -x install/agt_mission_manager/lib/agt_mission_manager/mission_manager_node.py \
  && echo mission_manager_exec_OK

ros2 pkg executables agt_mission_manager

test -f \
  install/agt_mission_manager/share/agt_mission_manager/fixtures/runtime/missions/mock_inspection_return/v1/mission.yaml \
  && echo mission_fixture_OK
```

## Hardware-free Mission E2E

Shell A:

```bash
rm -rf /tmp/agt_mission_mock_runtime
ros2 launch agt_mission_manager mock_inspection_return.launch.py
```

Shell B:

```bash
source /opt/ros/humble/setup.bash
source ~/agt_navigation_runtime/install/setup.bash

ros2 action send_goal \
  /agt/missions/execute \
  agt_interfaces/action/ExecuteMission \
  "{mission_id: 'mock_inspection_return', mission_version: 'v1', expected_content_sha256: 'sha256:825ea0ff78b237a64f5fea6419aac99117ff4bc870746d492410b7a1947c0ec0'}" \
  --feedback
```

Acceptance target:

```text
INSPECTION_TASK succeeds
-> RETURN_HOME formal child succeeds
-> Mission success=true
-> Goal SUCCEEDED
-> report_uri non-empty
-> report.json home_returned=true
```

Then inspect:

```bash
find /tmp/agt_mission_mock_runtime -maxdepth 10 -type f | sort
cat /tmp/agt_mission_mock_runtime/mission_reports/mock_inspection_return/*/report.json
```

## Next after GREEN

After this Mission-level E2E is green, proceed to real visual evidence adapters: encode `original.jpg`, `overlay.jpg`, `mask.png`, preserve visual model version/hash, and wire the Level-1 visual model behind `/agt/vision/inspect` without changing Mission/Nav2 ownership.
