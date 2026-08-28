# Visual Evidence Level-1 Bridge — Implementation Report

Date: 2026-08-28

Status: **USER-MACHINE FULL MOCK E2E GREEN / CORRECTNESS FOLLOW-UP GREEN**

This report freezes the software-only milestone for the Level-1 visual evidence bridge on branch `feat/inspection-multiview-evidence`. Evidence below is from the user's ROS 2 Humble machine unless explicitly stated otherwise; it is not assistant-side ROS execution evidence.

## Scope completed

The runtime inspection path now carries and persists one canonical visual evidence bundle per successful view:

```text
view_<id>/
├── original.jpg
├── overlay.jpg
├── mask.png
└── result.json
```

The ROS vision action result exposes model weights identity plus overlay and mask images. The inspection ROS adapter validates canonical Level-1 JSON, JPEG-encodes original/overlay images, PNG-encodes the mask, carries explicit media suffixes through `CaptureResult` / `VisionResult`, and persists them through `InspectionEvidenceStore`.

The mock vision stack now uses a deterministic canonical Level-1 payload and emits deterministic overlay/mask ROS images. The mock result is intentionally synthetic and does not claim real segmentation quality.

## Frozen contracts

Level-1 result payload includes:

- `schema_version = 1`
- non-empty `count_target`
- typed and JSON-mirrored `model_id`, `model_version`, `weights_sha256`
- non-negative integer `raw_count`
- `instances[]`
- `quality{}`
- `warnings[]`

`raw_count` and `instances[]` are intentionally independent contract fields. The parser does not impose an extra `len(instances) == raw_count` invariant.

For Schema-v2 execution, the parsed Level-1 `count_target` must exactly match the inspection task's frozen `task.count_target`. A mismatch is rejected as an inference failure before evidence persistence or point-local aggregation. The diagnostic includes both expected and actual targets for auditability.

Evidence codecs are:

- `original.jpg`: JPEG
- `overlay.jpg`: JPEG
- `mask.png`: lossless PNG

The Mission-level count semantics remain conservative:

- inspection child count mode: `POINT_DEDUP`
- Mission summary: `POINT_SUM_ESTIMATE`
- `mission_dedup_applied = false`
- no `global_unique_count` claim

Therefore the current value `18` is not a mission-global strict unique-object count.

## TDD / targeted acceptance evidence

The following gates were reported passing on the user machine during implementation:

- InspectImage visual evidence interface contract: GREEN
- deterministic image codec contract: GREEN
- canonical Level-1 result parser contract: GREEN
- executor / ROS visual evidence handoff: GREEN
- canonical visual evidence file-format regression set: **14 passed**
- deterministic canonical mock payload: **2 passed**
- mock Level-1 ROS action result + canonical mock payload regression set: **4 passed**
- generated-script freshness regression: **1 passed**

Correctness follow-up was completed with strict RED -> GREEN cycles:

- canonical parser now requires and exposes non-empty `count_target`
- parser no longer requires `len(instances) == raw_count`
- Schema-v2 executor rejects a valid Level-1 payload whose `count_target` differs from `task.count_target`
- mismatch diagnostics report both expected and actual target values
- targeted multiview execution regression: **USER-MACHINE GREEN**
- combined visual contract regression set: **USER-MACHINE GREEN**

The final two GREEN claims above are user-reported test results from the user's machine; they are not assistant-side test execution.

## Full hardware-free Mission E2E

Mission fixture:

```text
mock_inspection_return/v1
```

Execution flow observed on the user machine:

```text
INSPECTION_TASK
  -> P001 x 3 views
  -> P002 x 3 views
  -> point-local aggregation
RETURN_HOME(home_mock)
MISSION SUCCEEDED
```

Action result reported:

- `success: true`
- `error_code: 0`
- final state `SUCCEEDED`
- non-empty audit log URI
- non-empty Mission report URI
- `Goal finished with status: SUCCEEDED`

## Visual filesystem acceptance

Fresh mock run reported:

```text
original.jpg: 6
overlay.jpg : 6
mask.png    : 6
original.bin: 0
```

This closes the old transitional `.bin` persistence path for the Schema-v2 mock visual run.

## Mission report acceptance

The user ran a report validator against the generated Mission report and obtained:

```text
MISSION_REPORT_VALIDATION: PASS
Mission success           : true
Mission state             : SUCCEEDED
RETURN_HOME               : PASS
Inspection task           : PASS
count_target              : litchi_flower
count_mode                : POINT_DEDUP
raw_instance_count        : 18
point_sum_estimate        : 18
ambiguous_instance_count  : 0
count_semantics           : POINT_SUM_ESTIMATE
mission_dedup_applied     : false
global_unique_count       : not claimed
original.jpg              : 6
overlay.jpg               : 6
mask.png                  : 6
original.bin              : 0
```

## Generated-script freshness incident and fix

A hardware-free E2E initially succeeded at Mission level but persisted six `original.bin` files and no overlay/mask files, despite source-level visual tests passing.

Root cause was the executable-script staging mechanism in `agt_inspection/CMakeLists.txt`: source scripts are copied to `build/agt_inspection/generated_scripts` using `file(COPY ...)`, and the install tree points to those generated copies under `--symlink-install`. Incremental builds could therefore launch stale generated scripts while tests read current source files.

Fix: register each source script as `CMAKE_CONFIGURE_DEPENDS` so a script change triggers CMake reconfigure and refreshes generated executable copies. The corresponding source-order test was corrected to validate the real dependency semantics instead of requiring an irrelevant textual order between `CMAKE_CONFIGURE_DEPENDS` and `file(COPY)`.

After rebuild, the full visual filesystem acceptance changed from the stale `.bin` layout to the canonical `6 x original.jpg + 6 x overlay.jpg + 6 x mask.png + 0 x original.bin` layout.

## Evidence boundary / non-goals

This milestone does **not** prove:

- real BUNKER hardware operation
- real camera capture quality
- a trained litchi-flower detector/segmenter
- true Level-2 geometric association quality
- mission-global cross-point deduplication
- globally accurate object positions

The mock aggregator remains non-authoritative for real dedup quality. Mission-level `point_sum_estimate` must not be relabeled as a global unique count.

## Correctness follow-up status

The previously open Level-1 correctness cleanup is now **CLOSED / USER-MACHINE GREEN**:

1. `count_target` is a required canonical Level-1 field and is exposed by the parser result.
2. `raw_count` and `instances[]` are no longer forced to have equal lengths.
3. Schema-v2 execution binds result `count_target` to the task's expected target and rejects mismatches before evidence persistence or aggregation.
4. Mismatch diagnostics include both expected and actual targets.

No further Mission/RETURN_HOME architecture change is required for this milestone. The next implementation line should focus on real camera/model integration while preserving the frozen runtime/evidence contracts above.
