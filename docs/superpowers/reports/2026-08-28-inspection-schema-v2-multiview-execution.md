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

The first hardware-free E2E launch then failed before any mock node started:

```text
executable 'mock_runtime_context.py' not found on the libexec directory
.../install/agt_inspection/lib/agt_inspection
```

Root-cause inspection showed that the script was already present in the CMake install list, so the failure was not a missing filename. The repository Git tree records all `agt_inspection/scripts/*.py` entries as mode `100644`. With `colcon --symlink-install`, source-backed libexec entries can therefore remain non-executable. This is the same packaging class previously handled in `agt_bringup`.

`agt_inspection` now stages every ROS Python entry through an executable build-tree copy (`OWNER/GROUP/WORLD_EXECUTE`) before `install(PROGRAMS ...)`. A regression contract requires this symlink-safe staging. The mock E2E must be rerun after a clean package rebuild before this milestone is marked GREEN.

## Verification boundary

The ROS build/tests and launch were performed on the user's Runtime machine. They were not independently executed in the assistant environment. The packaging fix is code-landed but its E2E rerun is still pending user-machine evidence.

## Required packaging/E2E rerun

Use a fresh shell and remove the stale package-specific build/install trees:

```bash
cd ~/agt_navigation_runtime
git checkout feat/inspection-multiview-evidence
git pull

source /opt/ros/humble/setup.bash

rm -rf build/agt_inspection install/agt_inspection
colcon build --packages-select agt_interfaces agt_inspection --symlink-install
source install/setup.bash

python3 -m pytest src/agt_inspection/test/test_multiview_v2_ros_contract.py -q

ls -l install/agt_inspection/lib/agt_inspection
test -x install/agt_inspection/lib/agt_inspection/mock_runtime_context.py && echo runtime_context_OK
test -x install/agt_inspection/lib/agt_inspection/mock_waypoint_task_server.py && echo waypoint_mock_OK
ros2 pkg executables agt_inspection
```

Then retry:

```bash
rm -rf /tmp/agt_inspection_mock_evidence
ros2 launch agt_inspection mock_inspection.launch.py
```

Only after the launch stays up should the schema-v2 Action goal be sent from a second shell.

## Known pending real-hardware adapters

- Current mock image evidence is raw ROS image bytes (`original.bin`), not a user-facing JPEG/PNG. Real camera/vision integration must export encoded `original`, `overlay` and `mask` files/URIs.
- Real camera calibration identity and camera/gimbal extrinsics must be supplied before geometric Level-2 association can be treated as calibrated evidence.
- The mock aggregator proves only integration. It must never be reported as successful real ID cleaning.
- HOME return and final mission-level export orchestration remain Mission Manager work after schema-v2 E2E is GREEN.
