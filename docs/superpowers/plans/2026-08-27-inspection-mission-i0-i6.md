# Inspection Mission I0-I6 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a map-bound, mock-first stop-and-inspect mission path that reuses the existing Task Registry/navigation Action, stabilizes the robot before capture, moves a gimbal, captures an image, invokes a model through a stable Action, stores evidence, and can be delegated from the existing Mission Manager.

**Architecture:** Add stable inspection leaf interfaces to `agt_interfaces`, a new `agt_inspection` package for strict task assets/execution/mocks, and one new `INSPECTION_TASK` step in `agt_mission_manager`. Navigation remains behind `/agt/navigation/execute_waypoint_task`; inspection references existing single-point TaskGroups instead of introducing a second navigation-pose authority. The future upper computer is deliberately excluded until mock end-to-end execution is green.

**Tech Stack:** ROS 2 Humble, Python 3, rclpy Actions/Services, `sensor_msgs/Image`, existing `agt_interfaces`, existing Task Registry/`ExecuteWaypointTask`, pytest/ament.

**Spec:** `docs/superpowers/specs/2026-08-27-inspection-mission-design.md`

## Global Constraints

- Runtime execution must not depend on V2 source/install/workspace overlays.
- `agt_inspection` must not call or import Nav2 native Action APIs; navigation goes only through `/agt/navigation/execute_waypoint_task`.
- Inspection assets reference versioned single-point TaskGroups by id/revision/hash and do not duplicate raw x/y/yaw.
- Map binding is fail-closed and checked before any navigation child is submitted.
- Capture is forbidden before continuous stationary evidence and gimbal-settle completion.
- Real gimbal/camera/model SDK details are not invented; leaf capabilities stay behind stable ROS interfaces.
- All retries are finite; cancel must cancel an active child before progressing.
- No new TF or cmd_vel publisher is introduced by `agt_inspection`.
- Model-domain details remain in `result_json`; model-independent status/version/timing/confidence stay typed.
- The authoring console is not implemented in I0-I6.

---

## File Structure Locked by This Plan

### Interfaces

- `src/agt_interfaces/msg/InspectionStatus.msg`
- `src/agt_interfaces/action/ExecuteInspectionTask.action`
- `src/agt_interfaces/action/MoveGimbal.action`
- `src/agt_interfaces/action/InspectImage.action`
- `src/agt_interfaces/srv/CaptureImage.srv`
- `src/agt_interfaces/test/test_inspection_interfaces.py`
- `src/agt_interfaces/CMakeLists.txt`
- `src/agt_interfaces/package.xml`

### New package `agt_inspection`

- `src/agt_inspection/package.xml`
- `src/agt_inspection/CMakeLists.txt`
- `src/agt_inspection/README.md`
- `src/agt_inspection/agt_inspection/__init__.py`
- `src/agt_inspection/agt_inspection/model.py`
- `src/agt_inspection/agt_inspection/schema.py`
- `src/agt_inspection/agt_inspection/repository.py`
- `src/agt_inspection/agt_inspection/execution.py`
- `src/agt_inspection/agt_inspection/evidence.py`
- `src/agt_inspection/scripts/inspection_task_server.py`
- `src/agt_inspection/scripts/mock_gimbal_server.py`
- `src/agt_inspection/scripts/mock_camera_server.py`
- `src/agt_inspection/scripts/mock_vision_server.py`
- `src/agt_inspection/launch/mock_inspection.launch.py`
- `src/agt_inspection/test/test_schema.py`
- `src/agt_inspection/test/test_repository.py`
- `src/agt_inspection/test/test_execution.py`
- `src/agt_inspection/test/test_ros_contract.py`

### Mission integration

- `src/agt_interfaces/msg/MissionStatus.msg`
- `src/agt_mission_manager/agt_mission_manager/mission_model.py`
- `src/agt_mission_manager/agt_mission_manager/mission_schema.py`
- `src/agt_mission_manager/agt_mission_manager/mission_executor.py`
- `src/agt_mission_manager/scripts/mission_manager_node.py`
- `src/agt_mission_manager/package.xml`
- `src/agt_mission_manager/test/test_mission_schema.py`
- `src/agt_mission_manager/test/test_mission_executor.py`
- `src/agt_mission_manager/README.md`

---

### Task 1: Freeze inspection ROS interfaces

**Files:**
- Create: `src/agt_interfaces/msg/InspectionStatus.msg`
- Create: `src/agt_interfaces/action/ExecuteInspectionTask.action`
- Create: `src/agt_interfaces/action/MoveGimbal.action`
- Create: `src/agt_interfaces/action/InspectImage.action`
- Create: `src/agt_interfaces/srv/CaptureImage.srv`
- Create: `src/agt_interfaces/test/test_inspection_interfaces.py`
- Modify: `src/agt_interfaces/CMakeLists.txt`
- Modify: `src/agt_interfaces/package.xml`
- Modify: `src/agt_interfaces/action/README.md`

**Interfaces:**
- Produces `/agt/inspection/execute_task`, `/agt/gimbal/move`, `/agt/camera/capture`, `/agt/vision/inspect` message types used by all later tasks.
- Adds `sensor_msgs` as an interface dependency only because `CaptureImage` and `InspectImage` transport one captured frame.

- [ ] **Step 1: Add a failing static interface contract test**

Create `test_inspection_interfaces.py` that checks the files are registered, `sensor_msgs` is declared, and stable fields/error constants exist. The contract must require `sensor_msgs/Image image` in both the capture response and vision goal; `InspectImage.Result` must contain `model_id`, `model_version`, `inference_time_ms`, `primary_confidence`, `result_json`; `ExecuteInspectionTask.Feedback` must contain `current_point`, `total_points`, `point_id`, `stage`.

- [ ] **Step 2: Run RED**

```bash
python3 -m pytest src/agt_interfaces/test/test_inspection_interfaces.py -q
```

Expected: FAIL because the new interface files are absent.

- [ ] **Step 3: Add minimal interface definitions**

`InspectionStatus.msg`:

```text
uint8 STATE_IDLE=0
uint8 STATE_VALIDATING=1
uint8 STATE_RUNNING=2
uint8 STATE_CANCELING=3
uint8 STATE_SUCCEEDED=4
uint8 STATE_FAILED=5
uint8 STATE_CANCELED=6
uint16 ERROR_NONE=0
uint16 ERROR_INVALID_TASK=1
uint16 ERROR_MAP_MISMATCH=2
uint16 ERROR_NAVIGATION=3
uint16 ERROR_NOT_STATIONARY=4
uint16 ERROR_GIMBAL=5
uint16 ERROR_CAPTURE=6
uint16 ERROR_INFERENCE=7
uint16 ERROR_CANCELED=8
uint16 ERROR_INTERNAL=255
std_msgs/Header header
uint8 state
string session_id
string inspection_task_id
uint32 task_revision
string content_sha256
string map_id
string map_version_id
uint32 current_point
uint32 total_points
string point_id
string stage
uint16 error_code
string message
```

`ExecuteInspectionTask.action`:

```text
string map_id
string map_version_id
string inspection_task_id
uint32 task_revision
string expected_content_sha256
string client_request_id
---
bool success
uint16 error_code
string session_id
string evidence_root_uri
string message
agt_interfaces/InspectionStatus final_status
---
string state
uint32 current_point
uint32 total_points
string point_id
string stage
agt_interfaces/InspectionStatus status
```

`MoveGimbal.action`:

```text
string request_id
float64 pan_rad
float64 tilt_rad
float64 timeout_s
---
uint16 ERROR_NONE=0
uint16 ERROR_INVALID_REQUEST=1
uint16 ERROR_TIMEOUT=2
uint16 ERROR_HARDWARE=3
uint16 ERROR_CANCELED=4
bool success
uint16 error_code
float64 final_pan_rad
float64 final_tilt_rad
string message
---
string state
float64 current_pan_rad
float64 current_tilt_rad
```

`CaptureImage.srv`:

```text
string request_id
string camera_id
---
uint16 ERROR_NONE=0
uint16 ERROR_INVALID_REQUEST=1
uint16 ERROR_CAMERA_UNAVAILABLE=2
uint16 ERROR_CAPTURE_FAILED=3
bool success
uint16 error_code
sensor_msgs/Image image
string image_uri
string message
```

`InspectImage.action`:

```text
string request_id
string task_id
string model_profile
string camera_id
sensor_msgs/Image image
string metadata_json
---
uint16 ERROR_NONE=0
uint16 ERROR_INVALID_REQUEST=1
uint16 ERROR_MODEL_UNAVAILABLE=2
uint16 ERROR_INFERENCE_FAILED=3
uint16 ERROR_CANCELED=4
bool success
uint16 error_code
string model_id
string model_version
float64 inference_time_ms
float64 primary_confidence
string result_json
string message
---
string stage
float32 progress
```

- [ ] **Step 4: Register `sensor_msgs` and all interfaces**

Add `find_package(sensor_msgs REQUIRED)`, `<depend>sensor_msgs</depend>`, the five files to `rosidl_generate_interfaces`, and `sensor_msgs` to `DEPENDENCIES`.

- [ ] **Step 5: Run interface build/tests GREEN on Runtime machine**

```bash
colcon build --packages-select agt_interfaces --symlink-install
source install/setup.bash
python3 -m pytest src/agt_interfaces/test/test_inspection_interfaces.py -q
colcon test --packages-select agt_interfaces
colcon test-result --verbose
```

- [ ] **Step 6: Commit**

```bash
git add src/agt_interfaces
git commit -m "feat(interfaces): add inspection capability contracts"
```

---

### Task 2: Add strict inspection asset schema and repository

**Files:**
- Create new package files listed under `agt_inspection` above for `model.py`, `schema.py`, `repository.py` and tests.

**Interfaces:**
- Produces `InspectionTask`, `InspectionPoint`, `NavigationBinding`, `StabilizationPolicy`, `GimbalPose`, `CameraPolicy`, `VisionPolicy`, `RetryPolicy` dataclasses.
- Produces `parse_inspection_task(value) -> InspectionTask`, `canonical_hash(value) -> str`, `InspectionRepository.load(...)`.
- Storage: `runtime/maps/<map_id>/versions/<map_version_id>/inspections/<inspection_task_id>.json`.

- [ ] **Step 1: Write schema RED tests**

Tests must cover valid one-point task plus rejection of unknown keys, duplicate point ids, invalid sha256, hash mismatch, zero capture count, negative timeout, non-finite pan/tilt/confidence, confidence outside `[0,1]`, retry values outside `0..10`, empty points and map-binding mismatch.

- [ ] **Step 2: Run RED**

```bash
python3 -m pytest src/agt_inspection/test/test_schema.py -q
```

Expected: import/module failure before production files exist.

- [ ] **Step 3: Implement immutable dataclasses and strict parser**

Use exact-key checking and canonical JSON hashing (`sort_keys=True`, separators `(',', ':')`). `expected_content_sha256` and task `content_sha256` require `sha256:<64 lowercase hex>`. Portable ids use `^[A-Za-z0-9][A-Za-z0-9._-]{0,127}$`.

- [ ] **Step 4: Write repository RED tests**

Require safe path components, load only below the bound map/version inspection directory, exact `inspection_task_id`, revision and content hash matching, and no `..`/absolute path inputs.

- [ ] **Step 5: Implement repository and run GREEN**

```bash
python3 -m pytest src/agt_inspection/test/test_schema.py src/agt_inspection/test/test_repository.py -q
```

- [ ] **Step 6: Commit**

```bash
git add src/agt_inspection
git commit -m "feat(inspection): add strict map-bound inspection assets"
```

---

### Task 3: Implement hardware-independent inspection execution core and evidence

**Files:**
- Create/modify: `agt_inspection/execution.py`, `evidence.py`, `test_execution.py`.

**Interfaces:**

Define Protocols:

```python
class NavigationRunner(Protocol):
    async def run(self, point: InspectionPoint) -> ChildResult: ...
    async def cancel(self) -> bool: ...

class GimbalRunner(Protocol):
    async def move(self, point: InspectionPoint) -> ChildResult: ...
    async def cancel(self) -> bool: ...

class CameraRunner(Protocol):
    async def capture(self, point: InspectionPoint, capture_index: int) -> CaptureResult: ...

class VisionRunner(Protocol):
    async def inspect(self, point: InspectionPoint, capture: CaptureResult) -> VisionResult: ...
    async def cancel(self) -> bool: ...

class StationaryProvider(Protocol):
    def sample(self) -> tuple[float, float, float]: ...
```

`sample()` returns `(stamp_monotonic_s, linear_x_mps, angular_z_radps)`.

- [ ] **Step 1: Write ordering/retry/cancel RED tests**

Use fake runners that append stage names to a list. Require exact order `navigate -> stationary -> gimbal -> gimbal_settle -> capture -> vision -> persist`. Test that unstable velocity cannot reach capture, stale stationary samples fail, each retry budget is finite, canceled vision/navigation is confirmed before task returns canceled, and evidence is written only for captures that were actually obtained.

- [ ] **Step 2: Run RED**

```bash
python3 -m pytest src/agt_inspection/test/test_execution.py -q
```

- [ ] **Step 3: Implement `InspectionExecutor`**

Stationary acceptance requires all samples during a continuous `stable_duration_s` window to be under linear/angular thresholds and each sample freshness <= 0.5 s; timeout fails `ERROR_NOT_STATIONARY`. Gimbal settle uses injected sleep and does not consume a camera frame. Capture/inference requests use deterministic request ids `<session_id>:<point_id>:<capture_index>`.

- [ ] **Step 4: Implement evidence writer**

Store `session.json` and per-capture JSON under a safe Runtime-relative root. For unit tests, image evidence may be a binary/JSON placeholder supplied by `CaptureResult`; real ROS adapters handle actual encoded image bytes later. Use atomic replace for JSON metadata.

- [ ] **Step 5: Run GREEN**

```bash
python3 -m pytest src/agt_inspection/test/test_execution.py -q
```

- [ ] **Step 6: Commit**

```bash
git add src/agt_inspection
git commit -m "feat(inspection): add deterministic inspection execution core"
```

---

### Task 4: Add mock gimbal/camera/vision and ROS inspection Action server

**Files:**
- Create scripts/launch/ROS contract test listed in file structure.
- Modify `agt_inspection/CMakeLists.txt`, `package.xml`, `README.md`.

**Interfaces:**
- Mock gimbal serves `/agt/gimbal/move`.
- Mock camera serves `/agt/camera/capture` and returns deterministic `rgb8` 16x16 image.
- Mock vision serves `/agt/vision/inspect` and returns model `mock-vision`, version `1`, confidence `0.93`, `{"class":"test_target","confidence":0.93}`.
- `inspection_task_server.py` serves `/agt/inspection/execute_task`.

- [ ] **Step 1: Write static ROS contract RED test**

Require exact endpoint names, `ActionServer`/`Service` types, no imports from `nav2_msgs`, and installation of all scripts.

- [ ] **Step 2: Implement mocks**

Mock delays are parameters and finite. Cancel is acknowledged by Action servers. Camera rejects empty `request_id`/`camera_id`.

- [ ] **Step 3: Implement ROS adapters for gimbal/camera/vision child clients**

Translate Action/Service results into the pure execution core types. Do not put retry logic in adapters; retry remains in `InspectionExecutor`.

- [ ] **Step 4: Add TaskGroup navigation adapter**

For each point, submit `ExecuteWaypointTask.Goal` using the inspection goal's `map_id/map_version_id`, point navigation `task_group_id/task_revision/expected_content_sha256`, `loop_count=1`, and unique client request id. Do not populate deprecated `task_file`, `poses`, or `loop` fields. Cancel calls `cancel_goal_async()` and waits for confirmation.

- [ ] **Step 5: Add chassis-odometry stationary provider**

Subscribe `/agt/chassis/odometry`; expose last monotonic receive stamp plus `twist.twist.linear.x` and `angular.z`. No message before first sample means not stationary.

- [ ] **Step 6: Run build/tests**

```bash
colcon build --packages-select agt_interfaces agt_inspection --symlink-install
source install/setup.bash
python3 -m pytest src/agt_inspection/test -q
colcon test --packages-select agt_inspection
colcon test-result --verbose
```

- [ ] **Step 7: Commit**

```bash
git add src/agt_inspection
git commit -m "feat(inspection): add mock leaf servers and task action"
```

---

### Task 5: Integrate `INSPECTION_TASK` into Mission Manager

**Files:**
- Modify MissionStatus, mission model/schema/executor/node/package/tests/README listed above.

**Interfaces:**
- Add `STEP_INSPECTION_TASK=4` to `MissionStatus.msg` and `StepType.INSPECTION_TASK=4`.
- `MissionStep` gains `inspection_task_id`, `inspection_task_revision`, `expected_content_sha256`.
- Add `InspectionRunner` protocol with `run(...)` and `cancel()` analogous to `WaypointRunner`.

- [ ] **Step 1: Extend schema tests RED**

A valid step:

```yaml
- id: inspect_greenhouse
  type: INSPECTION_TASK
  inspection_task_id: greenhouse_camera_route_01
  inspection_task_revision: 1
  expected_content_sha256: sha256:...
```

Reject revision <= 0, invalid ids/hash and unknown keys.

- [ ] **Step 2: Extend executor tests RED**

Prove delegation to `InspectionRunner`, child failure mapping, pause/cancel cancellation confirmation, and gate revalidation before resume.

- [ ] **Step 3: Implement model/schema/executor changes**

Do not alter behavior of the existing three step types. Inspection child failure maps to `CHILD_REJECTED` for invalid/map/revision/hash rejection and `CHILD_FAILED` for runtime leaf failures.

- [ ] **Step 4: Wire ROS Action client in mission manager node**

Use `/agt/inspection/execute_task`. Parent mission map binding supplies map id/version; the step supplies inspection task id/revision/hash.

- [ ] **Step 5: Run regression**

```bash
python3 -m pytest src/agt_mission_manager/test -q
colcon build --packages-select agt_interfaces agt_inspection agt_mission_manager --symlink-install
source install/setup.bash
colcon test --packages-select agt_interfaces agt_inspection agt_mission_manager
colcon test-result --verbose
```

- [ ] **Step 6: Commit**

```bash
git add src/agt_interfaces/msg/MissionStatus.msg src/agt_mission_manager
git commit -m "feat(mission): delegate inspection task steps"
```

---

### Task 6: Mock end-to-end inspection acceptance without robot hardware

**Files:**
- Add example inspection/task/mission fixtures under `src/agt_inspection/test/fixtures/` or package test assets.
- Create `src/agt_inspection/launch/mock_inspection.launch.py` if not already complete.
- Create report `docs/superpowers/reports/2026-08-27-inspection-mission-i0-i6.md`.

**Interfaces:**
- Runs two inspection points with mock gimbal/camera/vision and a controlled fake `ExecuteWaypointTask` server.
- Does not require Nav2, BUNKER, CAN or a real map server.

- [ ] **Step 1: Add a fake navigation Action server for test launch only**

It accepts formal `ExecuteWaypointTask` goals, verifies deprecated fields remain empty, emits one waypoint feedback and succeeds after a finite delay.

- [ ] **Step 2: Add two-point fixture**

Each inspection point references a different single-point TaskGroup id/revision/hash. The mock mission contains exactly one `INSPECTION_TASK` step.

- [ ] **Step 3: Execute mock end-to-end acceptance on Runtime machine**

```bash
ros2 launch agt_inspection mock_inspection.launch.py
```

In another shell submit the fixture goal/mission. Verify both points produce evidence JSON and the stage sequence reaches `SUCCEEDED`.

- [ ] **Step 4: Full affected regression**

```bash
colcon build --symlink-install
source install/setup.bash
python3 -m pytest src/agt_interfaces/test/test_inspection_interfaces.py -q
python3 -m pytest src/agt_inspection/test -q
python3 -m pytest src/agt_mission_manager/test -q
colcon test --packages-select agt_interfaces agt_inspection agt_mission_manager agt_navigation
colcon test-result --verbose
```

- [ ] **Step 5: Record acceptance report**

Initial report states:

```text
INTERFACE_CONTRACT: pending local build
ASSET_SCHEMA: pending local tests
MOCK_EXECUTION: pending local tests
MISSION_INTEGRATION: pending local tests
MOCK_E2E: pending launch evidence
REAL_GIMBAL: not started
REAL_CAMERA: not started
REAL_VISION: not started
REAL_BUNKER: not started
```

Promote only with fresh evidence.

- [ ] **Step 6: Commit**

```bash
git add src/agt_inspection docs/superpowers/reports/2026-08-27-inspection-mission-i0-i6.md
git commit -m "test(inspection): add hardware-free end-to-end acceptance"
```

---

## Deferred I7: Real adapters and mission console

Do not implement before I0-I6 are green.

Real-adapter prerequisites from the vision/gimbal/camera owners:

```text
vision: model artifact + runnable inference + input/output contract + environment + latency + test images
camera: ROS topic/SDK + encoding/resolution + capture semantics + intrinsic requirement
 gimbal: SDK/protocol + pan/tilt units/ranges + feedback/arrival semantics + timeout/error behavior
```

After those are supplied, implement adapters behind the frozen interfaces. Then create `agt_mission_console` as a separate repository that uses map/task/inspection/mission services and Actions but never publishes chassis velocity.

## Self-Review

- Spec coverage: I0-I6 cover interface freeze, strict inspection assets, mock execution, formal TaskGroup navigation reuse, mission delegation and hardware-free end-to-end testing. Real adapters and console are intentionally deferred to I7.
- Placeholder scan: no executable step depends on an unspecified API; real hardware details are explicitly deferred rather than guessed.
- Type consistency: `sensor_msgs/Image` is used only in capture/vision leaf interfaces; inspection task navigation references the existing Task Registry by id/revision/hash; mission integration references inspection tasks by id/revision/hash.
- Safety: no direct Nav2/cmd_vel/TF publication is introduced; stationary and gimbal-settle gates precede capture; retries/cancel are finite/fail-closed.