# Mission Return-Home + Report Plan

Status: **PLANNED / TDD IMPLEMENTATION STARTED**

Branch: `feat/inspection-multiview-evidence`

## Goal

Extend the now-GREEN multi-view inspection task into the normal successful site mission flow:

```text
INSPECTION_TASK
-> formal RETURN_HOME TaskGroup
-> mission SUCCEEDED
-> mission-level report manifest
```

The HOME path must use the authoritative Task Registry fields on `ExecuteWaypointTask` and must not populate deprecated `task_file`, `poses`, or `loop` compatibility inputs.

## Safety / authority rules

- RETURN_HOME runs only while the normal mission map/localization/readiness gates remain valid.
- This phase does not force automatic motion after localization loss or safety/readiness loss.
- A HOME child rejection/failure fails the mission; it is not silently ignored.
- HOME is a dedicated final mission step and may appear at most once, as the final step.
- Mission-level reporting must not claim cross-point or whole-mission ID deduplication. It may report `VIEW_RAW` totals and a clearly labeled `POINT_SUM_ESTIMATE` from point-local dedup reports.

## Task 1 — RETURN_HOME schema + executor

Add `StepType.RETURN_HOME=5` and `MissionStatus.STEP_RETURN_HOME=5`.

Schema fields:

```yaml
- id: return_home
  type: RETURN_HOME
  task_group_id: home_greenhouse_01
  task_group_revision: 1
  expected_content_sha256: sha256:...
```

Constraints:

- portable task-group id;
- positive revision;
- canonical sha256;
- at most one RETURN_HOME step;
- RETURN_HOME must be final.

Executor behavior:

- revalidate mission gates immediately before HOME;
- send formal `ExecuteWaypointTask` map/task/revision/hash fields with `loop_count=1`;
- do not assign deprecated compatibility fields;
- preserve cancel/pause confirmation semantics.

## Task 2 — Mission report manifest

Create a mission report writer under:

```text
runtime/mission_reports/<mission_id>/<run_id>/
├── report.json
├── steps.csv
└── inspections.csv
```

Each inspection child records its `session_id` and `evidence_root_uri`. If `evidence_root_uri/report/report.json` exists, the mission report may summarize:

- count target;
- inspection count mode;
- raw total;
- point-local unique total;
- ambiguous total.

Whole-mission output must keep point-local semantics explicit. It must not name a sum of point-local counts `MISSION_DEDUP` or `global_unique_count`.

## Task 3 — ROS result + mock E2E

Extend `ExecuteMission.Result` with `report_uri`.

Create/extend a hardware-free mission fixture containing:

```text
INSPECTION_TASK inspection_multiview_two_point
RETURN_HOME home_mock
```

Use the existing mock map/localization/readiness, mock formal waypoint server, and inspection mock stack. Acceptance:

- inspection completes two points × three views;
- RETURN_HOME child succeeds after inspection;
- Mission Action succeeds;
- mission report exists and references inspection evidence;
- HOME uses formal Task Registry fields only.

## Verification boundary

ROS 2 Humble build/CTest/E2E must be run on the user's Runtime machine. Code landing alone is not GREEN.
