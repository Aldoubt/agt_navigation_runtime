# Inspection Schema v2 / Multi-View Execution Implementation Report

Status: **USER-MACHINE GREEN / MOCK E2E PASSED**

Branch: `feat/inspection-multiview-evidence`

## Goal

Make one inspection navigation point execute multiple explicit gimbal views without re-navigating between views, keep every Level-1 image/count as independent evidence, and run point-local ID cleaning only as a nonblocking Level-2 enhancement.

## Landed

### Schema v2

- Top-level `count_target` is required.
- Each point keeps one versioned single-point TaskGroup navigation binding.
- Point-level gimbal pose is removed from v2; ordered `views[]` own gimbal pan/tilt/timeout/settle settings.
- `camera.capture_count` must equal `1` in v2. Distinct viewpoints must be represented explicitly by `views[]`.
- `aggregation.enabled`, `aggregation.aggregation_profile` and a finite timeout control optional point-local association.
- Schema v1 remains supported as a separate legacy shape.

### Execution

For each schema-v2 point:

```text
ExecuteWaypointTask once
-> stationary gate
-> view[0]: gimbal -> settle -> capture -> Level-1 vision -> persist
-> view[1]: gimbal -> settle -> capture -> Level-1 vision -> persist
-> ...
-> optional AggregateInspectionViews
-> report
```

Level 1 is blocking and authoritative. The single-view model result must contain a JSON object with a non-negative integer `raw_count`.

Level 2 is optional and nonblocking. The ROS aggregator adapter has finite server/result/cancel waits; its default result timeout is 10 seconds. Unavailable/rejected/failed/timed-out aggregation preserves Level-1 evidence and is recorded as `aggregation/failure.json` instead of blocking the inspection mission. User cancellation remains authoritative.

### Capture-time spatial evidence

`RosViewContextProvider` keeps recent accepted `/agt/localization/status` samples and associates each camera `Image.header.stamp` with the nearest accepted TRACKING global pose. Evidence therefore records the observation-time map pose rather than simply using the Nav2 target pose or the latest pose after model inference.

The context also records final gimbal feedback and camera calibration identity. `camera_pose_map` remains optional; the current Runtime does not claim a calibrated camera map pose until the full camera/gimbal extrinsic chain is available.

### Evidence / report

`InspectionEvidenceStore` records terminal session state and nonblocking aggregation failures. Reports remain valid in all supported modes:

- `VIEW_RAW`: Level-1 evidence only or Level-2 failed/disabled.
- `POINT_DEDUP`: every point has a successful point-local aggregation.
- `MIXED`: only some points have successful aggregation.

### Hardware-free E2E fixture

A schema-v2 fixture is installed with the package:

```text
inspection_multiview_two_point
P001: left / center / right
P002: left / center / right
```

Mock Level 1 emits `raw_count=3` per view. The mock aggregator remains a deliberate no-dedup baseline, so a complete mock run yields 18 raw and 18 point-local unique instances with `dedup_applied=false`; this proves integration only and does not claim real ID cleaning.

## User-machine verification history

The user reports the schema-v2 build, direct pytest/CTest and package-level software gates completed with **0 failures**.

### E2E issue 1: Python libexec packaging

The first hardware-free E2E launch failed because installed Python entry points were not executable under `--symlink-install`. `agt_inspection` now stages every ROS Python entry through an executable build-tree copy before `install(PROGRAMS ...)`. User-machine evidence confirmed all seven executables were discoverable and launchable.

### E2E issue 2: fixture install path

The launch consumed fixtures from `share/agt_inspection/fixtures/runtime/maps` while CMake originally installed them below `share/agt_inspection/test/fixtures/runtime/maps`. The install path is now aligned to `share/${PROJECT_NAME}/fixtures`, and a regression contract binds the CMake destination to the launch lookup path.

### E2E issue 3: Humble Action mock asyncio incompatibility

Waypoint, gimbal and single-view vision mocks originally used `await asyncio.sleep()` inside rclpy Action execute callbacks. On ROS 2 Humble this aborted with `RuntimeError: no running event loop`. All three now use synchronous execute callbacks, short `time.sleep()` steps, `ReentrantCallbackGroup`, and `MultiThreadedExecutor(num_threads=2)`. A regression test forbids reintroducing the unsafe pattern.

### Final hardware-free E2E result

User-machine evidence confirms the complete two-point × three-view flow passed end-to-end:

```text
P001 NAVIGATING
-> WAITING_ROBOT_STABLE
-> three × (MOVING_GIMBAL -> WAITING_GIMBAL_STABLE -> CAPTURING -> INFERENCING -> SAVING_RESULT)
-> AGGREGATING_VIEWS
-> P002 with the same three-view sequence
-> AGGREGATING_VIEWS
-> success=true, error_code=0
-> Goal status SUCCEEDED
```

The successful run produced an inspection evidence root below `/tmp/agt_inspection_mock_evidence/...` and returned `multiview inspection completed`.

## Verification boundary

The ROS build/tests and hardware-free launch/E2E were performed on the user's Runtime machine and supplied as logs. They were not independently executed in the assistant environment. This milestone is therefore **USER-MACHINE GREEN** rather than assistant-local ROS verified.

## Next milestone

Proceed to Mission-level orchestration:

1. formal HOME TaskGroup / return-home step using Task Registry fields, not deprecated pose/task-file compatibility inputs;
2. Mission-level report manifest linking inspection evidence roots and count summaries;
3. then real image encoding/overlay/mask export and the Level-1 visual-model bridge.

## Known pending real-hardware adapters

- Current mock image evidence is raw ROS image bytes (`original.bin`), not a user-facing JPEG/PNG. Real camera/vision integration must export encoded `original`, `overlay` and `mask` files/URIs.
- Real camera calibration identity and camera/gimbal extrinsics must be supplied before geometric Level-2 association can be treated as calibrated evidence.
- The mock aggregator proves only integration. It must never be reported as successful real ID cleaning.
- Mission-level HOME return and final report orchestration are the next development milestone.
