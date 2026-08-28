# Visual Evidence + Level-1 Vision Bridge Design

Status: **FROZEN FOR IMPLEMENTATION**

Branch: `feat/inspection-multiview-evidence`

## Goal

Replace temporary `original.bin` inspection evidence with reviewable visual artifacts while keeping the vision implementation replaceable behind `/agt/vision/inspect`.

Per successful view the Runtime evidence contract becomes:

```text
view_<id>/
├── original.jpg
├── overlay.jpg
├── mask.png
└── result.json
```

## Ownership

- Mission Manager owns mission sequencing only.
- Inspection Runtime owns capture/inference orchestration and evidence paths.
- Camera provider owns `sensor_msgs/Image` capture only.
- Vision bridge owns Level-1 inference only.
- Vision bridge must not publish cmd_vel, own Nav2, localization, TF, mission state, or arbitrary Runtime filesystem paths.
- Runtime Evidence Store creates and validates all final artifact paths.

## Level-1 ROS contract

Keep the public Action endpoint:

```text
/agt/vision/inspect
agt_interfaces/action/InspectImage
```

The goal remains one captured image plus task/model metadata.

The result is extended with:

```text
string weights_sha256
sensor_msgs/Image overlay_image
sensor_msgs/Image mask_image
```

Existing fields remain:

```text
success
error_code
model_id
model_version
inference_time_ms
primary_confidence
result_json
message
```

The bridge returns image payloads rather than arbitrary output file paths. Runtime persists them.

## Canonical result_json

A successful Level-1 result must be JSON object schema version 1 with at least:

```json
{
  "schema_version": 1,
  "count_target": "litchi_flower",
  "model": {
    "model_id": "litchi_flower_instance_seg",
    "model_version": "v1.0",
    "weights_sha256": "sha256:..."
  },
  "raw_count": 83,
  "instances": [],
  "quality": {},
  "warnings": []
}
```

Rules:

- `raw_count` is a non-negative integer.
- `instances` is an array.
- model identity in JSON must match the typed Action result.
- `weights_sha256` must be canonical `sha256:<64 lowercase hex>` for non-mock production profiles.
- a valid `raw_count=0` means a successful inference with zero accepted instances; inference failure must use `success=false` and an error code.

## Evidence codec policy

Runtime converts image messages to files with deterministic policy:

```text
original.jpg  JPEG, quality 95
overlay.jpg   JPEG, quality 95
mask.png      PNG, lossless
```

Supported initial ROS image encodings:

```text
rgb8
bgr8
mono8
```

Unsupported encodings fail the evidence persistence step explicitly; they are not silently reinterpreted.

The codec implementation may use `cv_bridge` + OpenCV on ROS 2 Humble. Encoding logic stays inside a focused adapter module so the evidence store itself remains filesystem/metadata oriented.

## Evidence metadata

Each `view/result.json` preserves:

- capture timestamp;
- actual accepted capture-time robot pose in map;
- gimbal pan/tilt feedback;
- camera id/calibration id/calibration sha256;
- `model_id`;
- `model_version`;
- `weights_sha256`;
- inference latency;
- `raw_count` and instance list;
- evidence filenames for original/overlay/mask.

## Compatibility

- Existing Inspection Schema v2 and Mission schema do not change.
- MultiView aggregation remains optional and consumes Level-1 observations.
- Level-2 failure remains non-blocking.
- The mock visual server must implement the same result shape with a deterministic mock weight hash and deterministic overlay/mask images.
- Legacy `InspectImage` clients must be rebuilt because the Action result definition changes, but endpoint ownership and goal semantics remain unchanged.

## Acceptance

Software acceptance requires:

```text
agt_interfaces + agt_inspection build
all existing selected regression tests green
new visual contract/codec/evidence tests green
hardware-free inspection E2E green
hardware-free mission+RETURN_HOME E2E green
```

Filesystem acceptance requires six mock views to contain `original.jpg`, `overlay.jpg`, `mask.png`, and `result.json`, with no new `original.bin` in the new Schema-v2 mock run.

Real camera/model hardware is not required for this milestone.
