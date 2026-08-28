# Visual Evidence + Level-1 Vision Bridge Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Persist reviewable `original.jpg`, `overlay.jpg`, `mask.png`, and canonical Level-1 inference metadata for every inspection view while preserving `/agt/vision/inspect` as the replaceable vision boundary.

**Architecture:** Extend the typed `InspectImage` result with model weight identity and image payloads, add a focused ROS-image codec in `agt_inspection`, then let the existing inspection server persist those payloads through `InspectionEvidenceStore`. The mock vision server implements the exact same contract so the entire two-point/three-view Mission remains hardware-free testable.

**Tech Stack:** ROS 2 Humble, `rclpy`, `sensor_msgs/Image`, `cv_bridge`, OpenCV, Python 3.10, pytest, ament/colcon.

**Spec:** `docs/superpowers/specs/2026-08-28-visual-evidence-level1-bridge-design.md`

## Global Constraints

- Runtime owns all final evidence file paths.
- Vision bridge never owns Mission/Nav2/localization/TF/cmd_vel.
- Level 1 remains mandatory; Level 2 aggregation remains optional/non-blocking.
- Preserve Inspection Schema v2 and Mission schema.
- New visual evidence must be explicit opt-in only through the existing inspection flow; no new motion authority.
- No assistant-side ROS success claim without fresh user-machine evidence.

---

### Task 1: Freeze the typed Level-1 vision result

**Files:**
- Modify: `src/agt_interfaces/action/InspectImage.action`
- Test: `src/agt_interfaces/test/test_visual_evidence_interfaces.py`

**Interfaces:**
- Consumes: existing `/agt/vision/inspect` goal and result fields.
- Produces: result fields `weights_sha256`, `overlay_image`, and `mask_image`.

- [ ] **Step 1: Write the failing interface test**

```python
from pathlib import Path

ACTION = Path(__file__).resolve().parents[1] / "action" / "InspectImage.action"


def test_inspect_image_result_exposes_visual_evidence_payloads():
    source = ACTION.read_text(encoding="utf-8")
    result = source.split("---")[1]
    assert "string weights_sha256" in result
    assert "sensor_msgs/Image overlay_image" in result
    assert "sensor_msgs/Image mask_image" in result
```

- [ ] **Step 2: Run test and verify RED**

Run:

```bash
python3 -m pytest src/agt_interfaces/test/test_visual_evidence_interfaces.py -q
```

Expected: FAIL because the three result fields do not yet exist.

- [ ] **Step 3: Extend `InspectImage.action` minimally**

Add after `model_version`:

```text
string weights_sha256
sensor_msgs/Image overlay_image
sensor_msgs/Image mask_image
```

- [ ] **Step 4: Rebuild interface and verify GREEN**

```bash
colcon build --packages-select agt_interfaces --symlink-install
source install/setup.bash
python3 -m pytest src/agt_interfaces/test/test_visual_evidence_interfaces.py -q
ros2 interface show agt_interfaces/action/InspectImage
```

- [ ] **Step 5: Commit**

```bash
git add src/agt_interfaces/action/InspectImage.action src/agt_interfaces/test/test_visual_evidence_interfaces.py
git commit -m "feat(vision): expose level1 visual evidence payloads"
```

---

### Task 2: Add deterministic ROS image codec

**Files:**
- Create: `src/agt_inspection/agt_inspection/image_codec.py`
- Create: `src/agt_inspection/test/test_image_codec.py`
- Modify: `src/agt_inspection/package.xml`

**Interfaces:**
- Consumes: `sensor_msgs.msg.Image`.
- Produces: `encode_jpeg(image, quality=95) -> bytes` and `encode_png(image) -> bytes`.

- [ ] **Step 1: Write failing codec tests**

Tests create small `rgb8`, `bgr8`, and `mono8` Image messages and assert JPEG starts with `FF D8`, PNG starts with `89 50 4E 47`, and unsupported encoding raises `ImageCodecError`.

- [ ] **Step 2: Run test and verify RED**

```bash
python3 -m pytest src/agt_inspection/test/test_image_codec.py -q
```

Expected: FAIL because `agt_inspection.image_codec` does not exist.

- [ ] **Step 3: Implement codec**

Use `CvBridge().imgmsg_to_cv2(..., desired_encoding="passthrough")`, normalize only `rgb8/bgr8/mono8`, then `cv2.imencode` with JPEG quality 95 or PNG lossless. Reject other encodings with `ImageCodecError`.

- [ ] **Step 4: Declare runtime dependencies**

Add:

```xml
<exec_depend>cv_bridge</exec_depend>
<exec_depend>python3-opencv</exec_depend>
```

- [ ] **Step 5: Run GREEN gate and commit**

```bash
python3 -m pytest src/agt_inspection/test/test_image_codec.py -q
git add src/agt_inspection/agt_inspection/image_codec.py src/agt_inspection/test/test_image_codec.py src/agt_inspection/package.xml
git commit -m "feat(inspection): add deterministic image evidence codec"
```

---

### Task 3: Validate canonical Level-1 result JSON

**Files:**
- Create: `src/agt_inspection/agt_inspection/vision_result.py`
- Create: `src/agt_inspection/test/test_vision_result.py`

**Interfaces:**
- Consumes: typed Action result fields plus `result_json`.
- Produces: validated `Level1VisionResult` with `raw_count`, `instances`, model identity, and canonical weight hash.

- [ ] **Step 1: Write failing validation tests**

Cover valid result, zero-target success, malformed JSON, negative/bool raw count, model identity mismatch, malformed weight hash, and inference failure versus valid zero count.

- [ ] **Step 2: Verify RED**

```bash
python3 -m pytest src/agt_inspection/test/test_vision_result.py -q
```

- [ ] **Step 3: Implement strict parser**

Require JSON object `schema_version=1`, matching `model.model_id/model_version/weights_sha256`, non-negative integer `raw_count`, array `instances`, object `quality`, and array `warnings`.

- [ ] **Step 4: Verify GREEN and commit**

```bash
python3 -m pytest src/agt_inspection/test/test_vision_result.py -q
git add src/agt_inspection/agt_inspection/vision_result.py src/agt_inspection/test/test_vision_result.py
git commit -m "feat(inspection): validate canonical level1 vision result"
```

---

### Task 4: Carry overlay/mask/model hash through the inspection executor

**Files:**
- Modify: `src/agt_inspection/agt_inspection/execution.py`
- Modify: `src/agt_inspection/scripts/inspection_task_server.py`
- Modify: `src/agt_inspection/test/test_multiview_execution.py`
- Modify: `src/agt_inspection/test/test_multiview_v2_ros_contract.py`

**Interfaces:**
- Consumes: extended `InspectImage.Result`.
- Produces: `VisionResult` containing `weights_sha256`, `overlay_bytes`, and `mask_bytes` plus validated canonical result JSON.

- [ ] **Step 1: Write failing executor/ROS adapter tests**

Assert the Action adapter copies typed model identity, validates `result_json`, and image-cache/evidence handoff exposes overlay/mask payloads.

- [ ] **Step 2: Verify RED**

```bash
python3 -m pytest \
  src/agt_inspection/test/test_multiview_execution.py \
  src/agt_inspection/test/test_multiview_v2_ros_contract.py -q
```

- [ ] **Step 3: Extend `VisionResult` and ROS adapter minimally**

Add fields:

```python
weights_sha256: str = ""
overlay_bytes: bytes = b""
mask_bytes: bytes = b""
```

Use the codec only at the ROS boundary. Keep pure executor independent of ROS message types.

- [ ] **Step 4: Verify GREEN and commit**

```bash
python3 -m pytest \
  src/agt_inspection/test/test_multiview_execution.py \
  src/agt_inspection/test/test_multiview_v2_ros_contract.py -q
git add src/agt_inspection
git commit -m "feat(inspection): carry visual evidence through level1 inference"
```

---

### Task 5: Persist JPG/PNG evidence instead of temporary BIN artifacts

**Files:**
- Modify: `src/agt_inspection/agt_inspection/multiview_evidence.py`
- Modify: `src/agt_inspection/test/test_multiview_evidence.py`

**Interfaces:**
- Consumes: original JPEG bytes, overlay JPEG bytes, mask PNG bytes, validated Level-1 result.
- Produces: `original.jpg`, `overlay.jpg`, `mask.png`, and `result.json` with filenames and model hash.

- [ ] **Step 1: Write failing persistence tests**

Assert a Schema-v2 view directory contains all four files, result JSON references them, and a new Schema-v2 write path does not produce `original.bin`.

- [ ] **Step 2: Verify RED**

```bash
python3 -m pytest src/agt_inspection/test/test_multiview_evidence.py -q
```

- [ ] **Step 3: Implement minimal persistence update**

Keep the store generic, but call it with explicit suffixes `.jpg/.jpg/.png` and preserve `weights_sha256` in `vision` metadata.

- [ ] **Step 4: Verify GREEN and commit**

```bash
python3 -m pytest src/agt_inspection/test/test_multiview_evidence.py -q
git add src/agt_inspection/agt_inspection/multiview_evidence.py src/agt_inspection/test/test_multiview_evidence.py
git commit -m "feat(evidence): persist reviewable inspection images"
```

---

### Task 6: Upgrade mock Level-1 vision to the real contract

**Files:**
- Modify: `src/agt_inspection/scripts/mock_vision_server.py`
- Modify: `src/agt_inspection/test/test_mock_action_executor_contract.py`
- Create: `src/agt_inspection/test/test_mock_visual_evidence_contract.py`

**Interfaces:**
- Consumes: one captured mock image.
- Produces: deterministic canonical JSON, mock weight hash, deterministic overlay image, deterministic mono8 mask.

- [ ] **Step 1: Write failing mock contract test**

Assert mock code sets `weights_sha256`, `overlay_image`, `mask_image`, `schema_version`, `raw_count`, and `instances`.

- [ ] **Step 2: Verify RED**

```bash
python3 -m pytest src/agt_inspection/test/test_mock_visual_evidence_contract.py -q
```

- [ ] **Step 3: Implement deterministic mock result**

Use a fixed mock weight hash, copy the input as overlay with a deterministic pixel modification, create a 16x16 mono8 mask, and return `raw_count=3` with three local instance records.

- [ ] **Step 4: Verify GREEN and commit**

```bash
python3 -m pytest \
  src/agt_inspection/test/test_mock_action_executor_contract.py \
  src/agt_inspection/test/test_mock_visual_evidence_contract.py -q
git add src/agt_inspection/scripts/mock_vision_server.py src/agt_inspection/test
git commit -m "feat(mock-vision): emit level1 visual evidence contract"
```

---

### Task 7: Re-run hardware-free Inspection and Mission acceptance

**Files:**
- Modify: `src/agt_inspection/README.md`
- Modify: `src/agt_mission_manager/README.md`
- Create: `docs/superpowers/reports/2026-08-28-visual-evidence-level1-bridge.md`

**Interfaces:**
- Consumes: all previous tasks.
- Produces: user-machine acceptance evidence and frozen operator commands.

- [ ] **Step 1: Run selected software gate**

```bash
colcon build --packages-select agt_interfaces agt_inspection agt_mission_manager --symlink-install
source install/setup.bash
python3 -m pytest src/agt_interfaces/test src/agt_inspection/test src/agt_mission_manager/test -q
colcon test --packages-select agt_interfaces agt_inspection agt_mission_manager
colcon test-result --verbose
```

- [ ] **Step 2: Run the existing mock Mission E2E**

Launch `agt_mission_manager/mock_inspection_return.launch.py`, send the frozen `mock_inspection_return/v1` Mission goal, and require `Goal finished with status: SUCCEEDED`.

- [ ] **Step 3: Inspect visual filesystem acceptance**

Require exactly six Schema-v2 view directories and for every one:

```text
original.jpg
overlay.jpg
mask.png
result.json
```

Also require Mission `report_uri`, `home_returned=true`, and unchanged `POINT_SUM_ESTIMATE` semantics.

- [ ] **Step 4: Record evidence boundary**

Report user-machine commands/results verbatim enough to distinguish user-run ROS evidence from assistant-side static implementation work.

- [ ] **Step 5: Commit docs/report**

```bash
git add src/agt_inspection/README.md src/agt_mission_manager/README.md docs/superpowers/reports/2026-08-28-visual-evidence-level1-bridge.md
git commit -m "docs(vision): record level1 visual evidence acceptance"
```
