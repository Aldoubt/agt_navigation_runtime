# Inspection Schema v2 / Multi-View Execution Implementation Report

Status: **SOFTWARE GATES USER-MACHINE GREEN / MOCK E2E RERUN REQUIRED**

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

Mock Level 1 emits `raw_count=3` per view. The mock aggregator remains a deliberate no-dedup baseline, so a complete mock run should yield 18 raw and 18 unique instances with `dedup_applied=false`.

## User-machine verification history

The user reports the schema-v2 build, direct pytest/CTest and package-level software gates completed with **0 failures**.

### E2E issue 1: Python libexec packaging

The first hardware-free E2E launch failed before any mock node started because installed Python entry points were not executable under `--symlink-install`. The repository Git tree records the scripts as mode `100644`.

`agt_inspection` now stages every ROS Python entry through an executable build-tree copy (`OWNER/GROUP/WORLD_EXECUTE`) before `install(PROGRAMS ...)`. User-machine evidence then confirmed all seven executables were discoverable and launchable.

### E2E issue 2: fixture install path

The launch consumed fixtures from:

```text
share/agt_inspection/fixtures/runtime/maps
```

while CMake originally installed them under:

```text
share/agt_inspection/test/fixtures/runtime/maps
```

The install path is now aligned to `share/${PROJECT_NAME}/fixtures`, and a regression contract binds the CMake destination to the launch lookup path. User-machine evidence then showed the inspection Action accepted the schema-v2 task and entered `P001 / NAVIGATING`.

### E2E issue 3: Humble Action mock asyncio incompatibility

The next E2E run reached the waypoint mock, which aborted with:

```text
RuntimeError: no running event loop
```

The traceback originated from `await asyncio.sleep(step)` inside the rclpy Action execute callback. ROS 2 Humble's rclpy ActionServer may drive a coroutine callback without providing an asyncio event loop suitable for `asyncio.sleep()`.

The same unsafe pattern was present in waypoint, gimbal and single-view vision mocks. All three now use:

```text
synchronous execute callback
+ short time.sleep() steps
+ ReentrantCallbackGroup
+ MultiThreadedExecutor(num_threads=2)
```

This keeps the mocks independent of an asyncio event loop while still allowing cancel callbacks to execute concurrently. A new regression test (`test_mock_action_executor_contract.py`) forbids `asyncio.sleep()`/async execute callbacks in these Humble hardware-free Action mocks.

## Verification boundary

The ROS build/tests and launch were performed on the user's Runtime machine. They were not independently executed in the assistant environment. The latest Humble Action mock fix is code-landed but its E2E rerun is pending user-machine evidence.

## Required E2E rerun

Use a fresh shell and rebuild `agt_inspection` so the staged build-tree script copies contain the latest mock sources:

```bash
cd ~/agt_navigation_runtime
git checkout feat/inspection-multiview-evidence
git pull

source /opt/ros/humble/setup.bash

rm -rf build/agt_inspection install/agt_inspection
colcon build --packages-select agt_interfaces agt_inspection --symlink-install
source install/setup.bash

python3 -m pytest \
  src/agt_inspection/test/test_multiview_v2_ros_contract.py \
  src/agt_inspection/test/test_mock_action_executor_contract.py -q

colcon test --packages-select agt_inspection
colcon test-result --verbose
```

Then retry:

```bash
rm -rf /tmp/agt_inspection_mock_evidence
ros2 launch agt_inspection mock_inspection.launch.py
```

Send the schema-v2 Action goal from a second sourced shell and inspect both Action feedback/result and launch-side tracebacks. The milestone remains open until the complete two-point × three-view mock run and generated report are verified.

## Known pending real-hardware adapters

- Current mock image evidence is raw ROS image bytes (`original.bin`), not a user-facing JPEG/PNG. Real camera/vision integration must export encoded `original`, `overlay` and `mask` files/URIs.
- Real camera calibration identity and camera/gimbal extrinsics must be supplied before geometric Level-2 association can be treated as calibrated evidence.
- The mock aggregator proves only integration. It must never be reported as successful real ID cleaning.
- HOME return and final mission-level export orchestration remain Mission Manager work after schema-v2 E2E is GREEN.
