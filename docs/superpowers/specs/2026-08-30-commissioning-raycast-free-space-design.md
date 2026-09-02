# Commissioning Raycast Free-Space Design

## Status

Approved direction: **方案 C — 建图阶段同步生成 raycast free-space evidence，最终 2D 栅格融合 RTAB-Map ground/obstacle evidence 与 raycast free-space evidence；旧 PCD 保留保守 fallback。**

## Problem

The current commissioning projector can successfully classify a finalized FAST-LIVO2 PCD with RTAB-Map and generate a PGM, but its semantics are point-only:

- ground point cell -> free;
- obstacle point cell -> occupied;
- all other cells -> unknown.

On the validated Benchmark map this produces a geometrically recognizable map but an unusably sparse navigation grid, with most of the area remaining unknown and free cells fragmented into many tiny components. The 3D mapping itself is consistent; the missing capability is free-space reconstruction.

## Goals

1. Preserve FAST-LIVO2 as the authoritative 3D mapping/localization source.
2. During mapping, accumulate compact, run-scoped free-space evidence from registered LiDAR observations and the current LIO sensor pose.
3. Use ray traversal to mark observed free cells and endpoints as observed hits, accumulated with log-odds/probabilistic evidence.
4. During final 2D projection, fuse raycast free-space evidence with RTAB-Map ground/obstacle classification from the finalized PCD.
5. Keep truly unobserved cells unknown.
6. Give occupied evidence precedence over free evidence.
7. Keep existing PCD-only runs usable through an explicit conservative `pcd_fallback` projection mode.
8. Record the projection quality/mode and source hashes in commissioning evidence and frozen Site artifacts.
9. Do not alter autonomous-motion safety, localization authority, or Nav2 control behavior.

## Non-Goals

- No online local costmap replacement.
- No semantic tree-row reconstruction in this change.
- No automatic corridor inference or route generation.
- No change to FAST-LIVO2 state estimation.
- No blanket conversion of unknown cells to free.
- No requirement to retain a multi-gigabyte rosbag for normal field operation.

## Architecture

### Mapping phase

The existing `field_mapping.launch.py` continues to start FAST-LIVO2 and publish:

- `/agt/commissioning/mapping/registered_points` (`sensor_msgs/msg/PointCloud2`);
- `/aft_mapped_to_init` (`nav_msgs/msg/Odometry` or equivalent current FAST-LIVO2 mapped pose stream).

A new commissioning-only node, `raycast_free_space_node.py`, subscribes to those two streams and owns a 2D probabilistic observation grid in the FAST-LIVO2 global frame (`camera_init`). It never publishes velocity, TF authority, or localization state.

For each accepted observation:

1. Resolve the LiDAR origin from the synchronized/nearest valid LIO pose.
2. Downsample endpoints for bounded CPU/memory cost.
3. Reject non-finite points and points outside configurable range limits.
4. Project sensor origin and endpoints to XY grid coordinates.
5. Traverse each ray with an integer grid traversal algorithm (Bresenham/Amanatides-Woo equivalent):
   - traversed cells before endpoint receive free evidence;
   - endpoint receives hit/observed evidence.
6. Accumulate evidence as bounded log-odds values.

The node writes compact run-scoped artifacts under:

```text
runtime/commissioning/<site>/<run>/observation/
├── free_space_evidence.bin
└── raycast_record.json
```

`free_space_evidence.bin` is a versioned binary grid containing geometry, log-odds values, and observation counts. `raycast_record.json` records schema version, frame, resolution, origin/bounds, update parameters, accepted/rejected observation statistics, and a SHA-256 of the binary artifact.

The observation node saves atomically on normal shutdown. Mapping finalization must remain valid when observation evidence is absent, so legacy/PCD-only workflows continue to work.

### Projection phase

The RTAB-Map projector remains responsible for classifying finalized PCD geometry into ground and obstacle evidence. It must not become localization authority.

Projection becomes two-stage:

```text
localization_map.pcd
        -> RTAB-Map ground / obstacle evidence

free_space_evidence.bin
        -> raycast free / observed-hit evidence

both
        -> conservative fusion
        -> raw_map.pgm / raw_map.yaml
```

Fusion rules:

1. RTAB obstacle evidence is occupied.
2. Strong raycast occupied/hit evidence is occupied only when supported by final-map obstacle evidence or configured endpoint policy; transient endpoints must not automatically dominate the finalized obstacle model.
3. RTAB ground evidence is free unless occupied evidence exists in the same cell.
4. Raycast free evidence marks cells free once it crosses the configured free threshold.
5. Unobserved or ambiguous cells remain unknown.
6. Occupied always overrides free.

The primary expected production mode is `raycast_fused`. If no valid observation artifact exists, projection falls back to the existing PCD-only path and records `projection_quality: pcd_fallback`.

### Coordinate/grid handling

The observation grid and projector share one explicit raster convention:

- frame: FAST-LIVO2 global gravity-aligned frame (`camera_init` during commissioning);
- resolution: default `0.05 m/cell`;
- integer cell indices derived from a fixed grid origin stored in the evidence artifact;
- final PGM origin written in ROS map-server YAML convention;
- no static fake `map -> camera_init` TF is introduced.

The fusion implementation must support different extents between the raycast evidence and RTAB PCD bounds by constructing the union raster and translating both sources into that raster.

## Probabilistic Policy

Use bounded log-odds to avoid unlimited accumulation:

```text
L(cell) = clamp(L(cell) + delta, L_min, L_max)
```

Initial state is unknown (`L = 0`, observation_count = 0).

Initial defaults:

- free update: negative log-odds delta;
- hit update: positive log-odds delta;
- clamp range: symmetric bounded interval;
- free threshold: negative;
- occupied threshold: positive;
- minimum observation count: configurable and greater than zero.

Exact numeric defaults must be centralized in one configuration file and recorded in `raycast_record.json`. They are tuning parameters, not hidden constants in the projection backend.

## Runtime Artifacts

A commissioning run becomes:

```text
runtime/commissioning/<site>/<run>/
├── mapping/
│   ├── localization_map.pcd
│   └── localization_map.processing.yaml
├── observation/
│   ├── free_space_evidence.bin
│   └── raycast_record.json
├── projection/
│   ├── raw_map.pgm
│   ├── raw_map.yaml
│   └── projection_record.json
├── map_review/
└── evidence/
```

The existing mapping artifacts remain mandatory. Observation artifacts are optional for compatibility, but production-quality projection should report whether they were used.

## Commissioning Service Contract

`CommissioningService.project()` remains the HMI/Gateway entry point. The service discovers observation evidence in the same run and passes it to the projection backend when valid.

`projection_record.json` must record at least:

- schema version;
- backend;
- `projection_quality`: `raycast_fused` or `pcd_fallback`;
- source PCD path/hash;
- raycast evidence path/hash when used;
- output PGM/YAML hashes;
- width/height/resolution/origin;
- RTAB parameters;
- fusion thresholds/policy;
- free/occupied/unknown cell counts and ratios.

The HMI does not need a new API to generate the map. Existing `Generate 2D map` continues to call the same commissioning endpoint; the descriptor/status may expose projection quality later if useful.

## Frozen Site Contract

When a reviewed Site revision is saved, the current navigation map remains:

```text
map/navigation.pgm
map/navigation.yaml
```

The immutable Site also preserves the projection record. If raycast evidence was used, the projection record contains its hash and mode. The large mutable observation grid does not need to be copied into every deployed Site unless later reproducibility requirements demand it; the run-scoped commissioning evidence remains the reconstruction source.

## Failure and Safety Behavior

- Missing/invalid raycast evidence: fail over to explicit `pcd_fallback`, never silently claim fused quality.
- Corrupt evidence checksum/schema: ignore it for fusion, record fallback reason, and keep projection conservative.
- Missing PCD: projection still fails closed; raycast evidence cannot replace the finalized localization map.
- Observation-node crash: FAST-LIVO2 mapping must continue; the node is non-authoritative and isolated.
- Mapping normal shutdown: save raycast artifacts atomically; partial `.tmp` files are not considered valid evidence.
- No component introduced here can publish chassis commands or grant AUTO permit.

## Performance Constraints

The field IPC must remain responsive during mapping. The observation node therefore must:

- downsample endpoints before ray traversal;
- enforce maximum ray range;
- optionally process every Nth registered cloud;
- keep a bounded 2D grid rather than per-point history;
- avoid retaining full PointCloud2 messages after processing;
- expose processed/skipped ray and frame counts in diagnostics/evidence.

The first implementation targets deterministic CPU execution; GPU acceleration is out of scope.

## Validation

### Unit/contract validation

- Grid traversal marks origin-to-endpoint cells correctly.
- Occupied precedence is enforced.
- Unknown remains unknown without observations.
- Log-odds clamping and thresholds are deterministic.
- Evidence binary/record round-trip validates schema and checksum.
- `CommissioningService.project()` chooses `raycast_fused` when evidence is valid and `pcd_fallback` otherwise.
- Projection record reports cell counts/ratios and quality mode.
- Mapping launch starts the raycast observer only when explicitly enabled/configured and never starts navigation.

### Benchmark acceptance

Use `Benchmark-BAG-260725` as the initial acceptance dataset and compare:

1. current RTAB point-only map;
2. new `raycast_fused` map;
3. bag-provided `/agt/map/mapping_occupancy` as a reference, not authority.

Acceptance criteria:

- FAST-LIVO2 reconstructed PCD remains geometrically consistent with the existing baseline;
- free-space largest connected component increases substantially over point-only output;
- unknown ratio decreases substantially in actually traversed/observed corridors;
- known walls/tree rows/obstacle structures are not opened by free-space filling;
- unseen regions remain unknown;
- slopes that were traversed remain connected when their observations support free space;
- map can still be reviewed/edited in the existing HMI and frozen into a validated Site revision.

No production Site is activated solely because image appearance improves; final acceptance still requires operator review and later Nav2 no-motion/low-speed validation.

## Rollout

1. Add pure-Python raycast/grid/evidence library with deterministic tests.
2. Add ROS2 observation node and mapping-launch integration behind a launch flag.
3. Generate evidence from `Benchmark-BAG-260725` replay.
4. Add fusion backend and service discovery with fallback.
5. Add projection metrics/records and HMI-visible quality if needed.
6. Compare point-only, fused, and historical occupancy outputs.
7. Only after the benchmark passes, make raycast evidence generation the default for normal field mapping.
