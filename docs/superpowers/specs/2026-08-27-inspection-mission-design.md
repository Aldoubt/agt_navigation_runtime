# Map-Bound Inspection Mission Design

Date: 2026-08-27
Branch: `feat/bunker-rtabmap-slope-nav`

## Goal

Add a reusable inspection workflow to `agt_navigation_runtime` for the sequence:

```text
localize on frozen map
-> navigate to inspection pose
-> confirm robot is stationary
-> move gimbal
-> wait for gimbal/camera stabilization
-> capture one or more images
-> invoke a model through a stable vision Action
-> persist image/result evidence
-> continue to the next inspection point
```

The first implementation must be testable without a BUNKER, real gimbal, real camera, or real model by replacing those leaf capabilities with mocks. Real hardware/model adapters are plugged in later without changing the inspection task schema or mission contract.

## Architectural boundary

- `agt_navigation_runtime` owns execution, safety gates, task state, audit and ROS interfaces.
- A future `agt_mission_console` repository owns map visualization and authoring only. It must not publish chassis velocity commands.
- `agt_navigation` remains the only navigation capability boundary. Inspection execution must not call Nav2 native actions directly.
- Existing map-versioned `TaskGroup` assets remain the source of navigation poses. Each inspection point references a finite single-point TaskGroup created through the existing Task Registry (`PutTaskGroup/GetTaskGroup/ExecuteWaypointTask`).
- New package `agt_inspection` owns inspection-task schema, inspection execution, evidence persistence and mock leaf capabilities.
- `agt_mission_manager` remains the owner of finite multi-step missions. It gains an `INSPECTION_TASK` step that delegates to `/agt/inspection/execute_task` and does not directly call gimbal/camera/vision leaves.
- Vision model code is not embedded into `agt_mission_manager` or `agt_navigation`. A stable `/agt/vision/inspect` Action separates model implementation from mission execution.

## Why inspection points reference TaskGroup instead of storing raw x/y/yaw

The Runtime already has a versioned, map-bound Task Registry and a formal `ExecuteWaypointTask` action. Reusing it avoids creating a second navigation-point authority. A map editor may let the operator click `(x, y, yaw)`, but saving the navigation pose first creates or updates a single-point TaskGroup under the active map version. The inspection asset then binds to that TaskGroup by id, revision and hash.

This gives three fail-closed checks before the robot moves:

1. inspection task map binding matches the active map version;
2. referenced TaskGroup revision/hash is exactly the one authored;
3. `ExecuteWaypointTask` performs the existing navigation/readiness validation.

## Inspection task asset

Storage target:

```text
runtime/maps/<map_id>/versions/<map_version_id>/inspections/<inspection_task_id>.json
```

Schema version 1:

```json
{
  "schema_version": 1,
  "inspection_task_id": "greenhouse_camera_route_01",
  "name": "Greenhouse camera route 01",
  "description": "Stop-and-inspect route",
  "revision": 1,
  "content_sha256": "sha256:<64 lowercase hex>",
  "map_binding": {
    "map_id": "greenhouse_01",
    "map_version_id": "v1",
    "manifest_sha256": "sha256:<64 lowercase hex>"
  },
  "points": [
    {
      "id": "P001",
      "navigation": {
        "task_group_id": "inspection-P001-nav",
        "task_revision": 1,
        "expected_content_sha256": "sha256:<64 lowercase hex>"
      },
      "stabilization": {
        "linear_velocity_max_mps": 0.02,
        "angular_velocity_max_radps": 0.03,
        "stable_duration_s": 0.8,
        "timeout_s": 5.0
      },
      "gimbal": {
        "pan_rad": 0.35,
        "tilt_rad": -0.20,
        "timeout_s": 5.0,
        "settle_duration_s": 0.5
      },
      "camera": {
        "camera_id": "front_inspection",
        "capture_count": 1,
        "capture_interval_s": 0.0
      },
      "vision": {
        "task_id": "crop_disease_detection",
        "model_profile": "default",
        "minimum_confidence": 0.70,
        "timeout_s": 10.0
      },
      "retry": {
        "navigation": 1,
        "gimbal": 1,
        "capture": 2,
        "inference": 1
      }
    }
  ]
}
```

The schema is strict: unknown keys, non-finite numbers, negative timeouts, invalid hashes, duplicate point ids, empty point lists and non-positive retry/capture limits are rejected. `content_sha256` is the SHA-256 of canonical JSON with `content_sha256` removed.

The inspection asset deliberately does not duplicate the navigation pose. The pose remains in the referenced TaskGroup and can be displayed by the authoring client through `GetTaskGroup`.

## Stable ROS capability interfaces

### `/agt/inspection/execute_task`

Type: `agt_interfaces/action/ExecuteInspectionTask`.

Goal:

```text
string map_id
string map_version_id
string inspection_task_id
uint32 task_revision
string expected_content_sha256
string client_request_id
```

Result:

```text
bool success
uint16 error_code
string session_id
string evidence_root_uri
string message
```

Feedback:

```text
string state
uint32 current_point
uint32 total_points
string point_id
string stage
```

Stable stages are `NAVIGATING`, `WAITING_ROBOT_STABLE`, `MOVING_GIMBAL`, `WAITING_GIMBAL_STABLE`, `CAPTURING`, `INFERENCING`, `SAVING_RESULT`.

### `/agt/gimbal/move`

Type: `agt_interfaces/action/MoveGimbal`.

Goal contains `request_id`, `pan_rad`, `tilt_rad`, `timeout_s`. Result contains success/error code, measured/final pan and tilt when available, and message. Feedback contains state/current pan/current tilt. The interface describes desired orientation only; serial/CAN/SDK protocol remains adapter-specific.

### `/agt/camera/capture`

Type: `agt_interfaces/srv/CaptureImage`.

Request contains `request_id` and `camera_id`. Response contains success/error code, `sensor_msgs/Image image`, optional `image_uri`, and message. The camera adapter owns exposure/driver details. Inspection execution decides when capture is permitted.

### `/agt/vision/inspect`

Type: `agt_interfaces/action/InspectImage`.

Goal:

```text
string request_id
string task_id
string model_profile
string camera_id
sensor_msgs/Image image
string metadata_json
```

Result:

```text
bool success
uint16 error_code
string model_id
string model_version
float64 inference_time_ms
float64 primary_confidence
string result_json
string message
```

Feedback contains `stage` and `progress` in `[0,1]`.

The vision adapter may wrap PyTorch, ONNX, TensorRT, a Python package or a local network service. The mission side only relies on this Action contract. The first version intentionally keeps domain-specific detections inside `result_json`; model-independent fields stay typed.

## Vision-team handoff contract

The vision owner must provide enough information to implement one adapter without guessing:

- exact input modality: RGB/RGB-D, image encoding, accepted resolution, whether camera intrinsics are required;
- a runnable inference entry point and trained weights/artifact, not training code alone;
- environment: Python, CUDA, framework and accelerator requirements;
- deterministic output schema for `result_json`, with at least one positive and one no-target example;
- model id/version, expected mean and worst-case inference latency on target hardware;
- behavior for no target, low confidence, invalid input and model/runtime exceptions;
- at least five representative test images and their expected qualitative outputs.

The adapter, not the mission executor, translates that model-specific output into `InspectImage.Result`.

## Evidence layout

Each execution gets a session id. Evidence is written under:

```text
runtime/inspections/<inspection_task_id>/<session_id>/
  session.json
  P001/
    capture_0001.png-or-original-format
    capture_0001.result.json
  P002/
    ...
```

`session.json` records map id/version/hash, inspection task revision/hash, point outcomes, timestamps and child-action status. A result record includes `mission_id` when the inspection is launched as an `INSPECTION_TASK` mission step.

## Robot-stationary gate

`NavigateToPose` success alone is insufficient. The inspection executor must wait until chassis odometry satisfies:

```text
abs(linear.x) <= linear_velocity_max_mps
abs(angular.z) <= angular_velocity_max_radps
continuously for stable_duration_s
```

before moving the gimbal/capturing. Missing or stale odometry is not considered stationary. Timeout fails that point unless its retry budget permits another navigation attempt.

## Retry and failure semantics

Retries are finite and per stage. The default policy for schema v1 is fail-fast at a point after its retry budget is exhausted; later schema versions may add `continue_on_failure` if required. Canceling an inspection task must cancel any active navigation/gimbal/vision child Action and stop before beginning another capture.

No retry may bypass map/readiness or motion-safety gates.

## Mission integration

Mission schema keeps version 1 but extends its step enum with `INSPECTION_TASK=4`. The step contains:

```yaml
- id: inspect_greenhouse
  type: INSPECTION_TASK
  inspection_task_id: greenhouse_camera_route_01
  inspection_task_revision: 1
  expected_content_sha256: sha256:...
```

The parent Mission map binding remains authoritative. `agt_mission_manager` passes its `map_id` and `map_version_id` to `ExecuteInspectionTask`, waits for cancellation confirmation on pause/cancel, and revalidates mission gates before resume. It still does not publish TF, cmd_vel, camera commands or model requests directly.

## Mock-first execution

Before hardware integration, `agt_inspection` provides mock servers for:

- single-point navigation runner or an injected fake `ExecuteWaypointTask` child;
- gimbal: returns success after a bounded delay;
- camera: returns a deterministic generated `sensor_msgs/Image`;
- vision: returns deterministic JSON such as `{"class":"test_target","confidence":0.93}`.

The inspection-core test must prove the order:

```text
navigate -> stationary gate -> gimbal -> settle -> capture -> vision -> persist
```

and prove that capture cannot occur before the stationary and gimbal-settle gates complete.

## Future mission console

Create a separate `agt_mission_console` repository only after the Runtime contracts above are green. First UI scope:

- select READY map version;
- render map image;
- click/drag to author one navigation pose;
- create/update the corresponding single-point TaskGroup through `PutTaskGroup`;
- set pan/tilt, camera id and vision task/profile;
- save/update inspection task;
- start/cancel mission through Runtime Actions;
- display read-only execution status and latest result.

It must not publish `/cmd_vel`, manipulate lifecycle nodes directly, or write Runtime files by arbitrary filesystem paths.

## Non-goals for the first implementation

- no real gimbal protocol until hardware/SDK is supplied;
- no model-specific messages for every detector class;
- no live video streaming in the mission contract;
- no visual servoing while the chassis is moving;
- no concurrent inspection points;
- no direct Nav2 calls from `agt_inspection`;
- no new map format;
- no upper-computer implementation before mock Runtime execution is green.

## Acceptance gates

I0/I1 interface freeze is accepted when interfaces compile and serialization/static contract tests pass.

I2 inspection asset layer is accepted when strict schema/hash/map-binding/repository tests pass using no ROS runtime.

I3 mock execution is accepted when deterministic tests prove the required stage order, retry limits, cancel behavior and evidence output without robot hardware.

I4 navigation integration is accepted when inspection uses `/agt/navigation/execute_waypoint_task` and does not import/call Nav2 native action types.

I5 mission integration is accepted when an `ExecuteMission` containing an `INSPECTION_TASK` delegates correctly and pause/cancel remain fail-closed.

I6 simulation acceptance requires at least two inspection points to complete end-to-end with mock gimbal/camera/vision and navigation in simulation or a controlled fake navigation server.

I7 real integration is accepted only after actual gimbal/camera/model contracts and hardware/model evidence are supplied.