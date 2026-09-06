# Commissioning Raycast Free-Space Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add commissioning-only raycast free-space evidence and conservatively fuse it with RTAB-Map point classification so observed traversable corridors become continuous while unseen space remains unknown.

**Architecture:** FAST-LIVO2 remains the authoritative 3D mapping/localization source. A new ROS2 observer consumes global registered clouds plus mapped odometry and accumulates a compact run-scoped log-odds raster. `CommissioningService.project()` discovers valid evidence and the Python projection backend fuses it with the existing C++ RTAB point map; missing or invalid evidence explicitly falls back to the current PCD-only map.

**Tech Stack:** ROS 2 Humble, Python 3.10+, rclpy, sensor_msgs_py, nav_msgs, C++17 RTAB-Map/PCL projector, pytest, YAML/JSON/PGM runtime artifacts.

**Spec:** `docs/superpowers/specs/2026-08-30-commissioning-raycast-free-space-design.md`

## Global Constraints

- FAST-LIVO2 remains 3D map/localization authority; raycasting must never publish TF authority, chassis commands, or AUTO permit.
- Finalized `localization_map.pcd` remains mandatory for projection.
- Truly unobserved cells remain unknown; occupied evidence always overrides free evidence.
- Missing/corrupt raycast evidence must produce explicit `pcd_fallback`, never silently claim fused quality.
- Observation state is run-scoped under `runtime/commissioning/<site>/<run>/observation/` and saved atomically on normal shutdown.
- The observer must not retain PointCloud2 history; it stores only bounded cell evidence and a short pose deque.
- Initial rollout keeps `start_raycast_observer:=false`; change the default only after `Benchmark-BAG-260725` acceptance.

---

### Task 1: Pure-Python raycast grid and evidence artifact

**Files:**
- Create: `src/agt_field_commissioning/agt_field_commissioning/raycast_free_space.py`
- Create: `src/agt_field_commissioning/config/raycast_free_space.yaml`
- Create: `tests/commissioning/test_raycast_free_space.py`

**Interfaces:**
- Produces `RaycastConfig`, `RaycastEvidenceGrid`, `RaycastEvidenceArtifact`, `grid_ray_cells()`, `save_evidence()`, and `load_evidence()`.
- `RaycastEvidenceGrid.observe_ray(origin_xy, endpoint_xy)` updates free cells before the endpoint and hit evidence at the endpoint.
- Artifact format is `AGTRAY01` + little-endian uint32 JSON-header length + UTF-8 JSON header + row-major float32 log-odds + row-major uint16 observation counts.
- Header fields include schema/version, frame, resolution, origin, width/height, thresholds/deltas/clamps, and statistics.

- [ ] **Step 1: Write deterministic failing traversal/log-odds tests**

```python
from agt_field_commissioning.raycast_free_space import RaycastConfig, RaycastEvidenceGrid, grid_ray_cells


def test_grid_ray_excludes_endpoint_from_free_cells():
    cells = grid_ray_cells((0, 0), (3, 0))
    assert cells == [(0, 0), (1, 0), (2, 0), (3, 0)]


def test_observe_ray_marks_passage_free_and_endpoint_hit():
    grid = RaycastEvidenceGrid(RaycastConfig(resolution_m=1.0, min_observation_count=1))
    grid.observe_ray((0.2, 0.2), (3.2, 0.2))
    assert grid.classify_world((1.2, 0.2)) == "free"
    assert grid.classify_world((3.2, 0.2)) == "occupied"
    assert grid.classify_world((9.2, 9.2)) == "unknown"
```

- [ ] **Step 2: Run the tests and verify RED**

Run:

```bash
PYTHONPATH=src/agt_field_commissioning PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 \
python -m pytest -q tests/commissioning/test_raycast_free_space.py
```

Expected: collection/import failure because `raycast_free_space.py` does not exist.

- [ ] **Step 3: Implement traversal, bounded log-odds, dynamic sparse accumulation, and dense snapshot materialization**

Use centralized defaults from `config/raycast_free_space.yaml`:

```yaml
schema_version: 1
frame_id: camera_init
resolution_m: 0.05
free_logodds_delta: -0.45
hit_logodds_delta: 0.85
min_logodds: -4.0
max_logodds: 4.0
free_threshold: -0.9
occupied_threshold: 1.7
min_observation_count: 2
min_ray_range_m: 0.5
max_ray_range_m: 40.0
cloud_stride: 1
point_stride: 8
pose_max_age_s: 0.15
```

The in-memory grid uses `dict[(ix, iy)] -> [log_odds, count]` and therefore grows only with observed cells. `snapshot()` converts the observed bounding rectangle to dense arrays at save time.

- [ ] **Step 4: Add binary round-trip/checksum tests**

```python
def test_evidence_round_trip_preserves_geometry_values_and_checksum(tmp_path):
    ...
    artifact = save_evidence(grid, tmp_path / "free_space_evidence.bin", tmp_path / "raycast_record.json")
    loaded = load_evidence(artifact.binary, artifact.record)
    assert loaded.frame_id == "camera_init"
    assert loaded.cell_state(0, 0) == "free"
```

Also test corrupt binary checksum and unsupported magic/schema rejection.

- [ ] **Step 5: Run Task 1 tests GREEN and commit**

Run the Task 1 test command; expected `0 failed`.

Commit message:

```text
feat: add commissioning raycast evidence core
```

---

### Task 2: ROS2 commissioning observer and mapping launch integration

**Files:**
- Create: `src/agt_field_commissioning/scripts/raycast_free_space_node.py`
- Modify: `src/agt_field_commissioning/CMakeLists.txt`
- Modify: `src/agt_field_commissioning/package.xml`
- Modify: `src/agt_field_commissioning/launch/field_mapping.launch.py`
- Modify: `src/agt_field_commissioning/agt_field_commissioning/mapping_artifacts.py`
- Modify: `tests/commissioning/test_field_mapping_contract.py`
- Create: `tests/commissioning/test_raycast_observer_contract.py`

**Interfaces:**
- Node executable: `raycast_free_space_node.py`.
- Parameters: `output_dir`, `config_file`, `cloud_topic`, `pose_topic`.
- Default topics: `/agt/commissioning/mapping/registered_points` and `/aft_mapped_to_init`.
- Launch args: `start_raycast_observer:=false`, `raycast_pose_topic:=/aft_mapped_to_init`, `raycast_config_file:=<package>/config/raycast_free_space.yaml`.
- `CommissioningRunPaths` gains `observation_dir`.

- [ ] **Step 1: Write failing mapping/packaging contract tests**

Assert:

```python
assert 'DeclareLaunchArgument("start_raycast_observer", default_value="false")' in launch
assert 'executable="raycast_free_space_node.py"' in launch
assert '"/agt/commissioning/mapping/registered_points"' in launch
assert 'DeclareLaunchArgument("raycast_pose_topic", default_value="/aft_mapped_to_init")' in launch
assert "scripts/raycast_free_space_node.py" in cmake
assert "rclpy" in package_xml
assert "sensor_msgs_py" in package_xml
assert "nav_msgs" in package_xml
```

- [ ] **Step 2: Run commissioning contracts and verify RED**

```bash
PYTHONPATH=src/agt_field_commissioning:src/agt_operator_gateway:src/agt_site_runtime:src/agt_runtime_contracts \
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q \
  tests/commissioning/test_field_mapping_contract.py \
  tests/commissioning/test_raycast_observer_contract.py
```

Expected: failures for missing observer executable/launch args/path fields.

- [ ] **Step 3: Implement observer**

The node:

```python
class RaycastFreeSpaceNode(Node):
    # keep deque[(timestamp_ns, x, y)] with bounded length
    # cloud callback chooses nearest pose within pose_max_age_s
    # read x/y/z using sensor_msgs_py.point_cloud2.read_points(..., field_names=("x","y","z"), skip_nans=True)
    # apply cloud_stride/point_stride/range limits
    # registered cloud points are already in camera_init global frame
    # call grid.observe_ray((pose_x, pose_y), (point_x, point_y))
    # normal shutdown -> save_evidence() atomically to output_dir
```

Do not add TF publishers or command publishers.

- [ ] **Step 4: Stage/install the script with executable permissions and add ROS dependencies**

Use the same CMake build-tree copy pattern already used for `finalize_mapping_run.py` so `--symlink-install` preserves executability.

- [ ] **Step 5: Integrate observer behind explicit launch flag**

When enabled, pass `observation_dir` from the same commissioning run and start after the FAST-LIVO2 node definition. Mapping must still run when the observer exits/fails independently.

- [ ] **Step 6: Run Task 2 contracts GREEN, compile Python, and commit**

```bash
python -m compileall -q \
  src/agt_field_commissioning/agt_field_commissioning \
  src/agt_field_commissioning/scripts \
  src/agt_field_commissioning/launch
```

Expected: contract tests pass, compile exits 0.

Commit message:

```text
feat: capture raycast evidence during mapping
```

---

### Task 3: Conservative fusion and explicit fallback in projection service

**Files:**
- Create: `src/agt_field_commissioning/agt_field_commissioning/raycast_fusion.py`
- Modify: `src/agt_field_commissioning/agt_field_commissioning/projection.py`
- Modify: `src/agt_field_commissioning/agt_field_commissioning/service.py`
- Create: `tests/commissioning/test_raycast_fusion.py`
- Modify: `tests/commissioning/test_projection_backend.py`
- Modify: `tests/commissioning/test_commissioning_service.py`

**Interfaces:**
- `fuse_point_map_with_evidence(point_pgm, point_yaml, evidence) -> FusedMapResult`.
- `ProjectionRequest` gains optional `raycast_evidence: Path | None` and `raycast_record: Path | None`.
- Backend first renders C++ RTAB output to `rtab_point_map.pgm/yaml`, then either fuses or copies it to final `raw_map.pgm/yaml`.
- `ProjectionResult` gains `projection_quality` and optional `fallback_reason`.
- `CommissioningService.project()` discovers `<run>/observation/free_space_evidence.bin` + `raycast_record.json` and passes them only if both exist.

- [ ] **Step 1: Write failing fusion tests for union raster and precedence**

```python
def test_raycast_free_turns_observed_unknown_into_free_without_opening_obstacle():
    # point map: [unknown, occupied, unknown]
    # raycast:   [free,    free,     unknown]
    # result:    [free,    occupied, unknown]
    ...
```

Also test differing origins/extents and unknown preservation.

- [ ] **Step 2: Run fusion/projection tests and verify RED**

```bash
PYTHONPATH=src/agt_field_commissioning:src/agt_site_runtime:src/agt_runtime_contracts \
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q \
  tests/commissioning/test_raycast_fusion.py \
  tests/commissioning/test_projection_backend.py \
  tests/commissioning/test_commissioning_service.py
```

- [ ] **Step 3: Implement raster fusion**

Rules in code:

```text
point occupied -> occupied
else evidence occupied + point occupied support policy -> occupied
else point free -> free
else evidence free -> free
else unknown
```

For the first production version, endpoint hit evidence alone does **not** create final occupied cells; finalized RTAB obstacle geometry remains occupied authority. This prevents transient foliage/endpoints from punching false black barriers into the map.

- [ ] **Step 4: Extend projection backend and records**

`projection_record.json` schema version becomes `2` and records:

```json
{
  "projection_quality": "raycast_fused",
  "fallback_reason": null,
  "raycast_evidence_sha256": "sha256:...",
  "cell_counts": {"free": 0, "occupied": 0, "unknown": 0},
  "cell_ratios": {"free": 0.0, "occupied": 0.0, "unknown": 0.0},
  "fusion": {"occupied_precedence": true, "endpoint_hit_requires_final_obstacle": true}
}
```

If validation/checksum/schema fails, copy the RTAB point map to `raw_map.*`, set `projection_quality=pcd_fallback`, and record the reason.

- [ ] **Step 5: Update service discovery and preserve HMI API**

No endpoint changes. `Generate 2D map` continues to call `CommissioningService.project()`; only backend inputs and record metadata change.

- [ ] **Step 6: Run Task 3 tests GREEN and commit**

Commit message:

```text
feat: fuse raycast free space into commissioning maps
```

---

### Task 4: Evidence/finalization records, benchmark inspection tooling, and rollout gate

**Files:**
- Modify: `src/agt_field_commissioning/agt_field_commissioning/mapping_artifacts.py`
- Create: `src/agt_field_commissioning/scripts/compare_commissioning_maps.py`
- Modify: `src/agt_field_commissioning/CMakeLists.txt`
- Modify: `docs/runbooks/lychee-inspection-field-e2e.md`
- Create: `tests/commissioning/test_compare_commissioning_maps.py`
- Modify: `tests/commissioning/test_mapping_artifacts.py`

**Interfaces:**
- Finalizer keeps observation artifacts optional, but when a valid record exists it adds hashes/summary under `mapping_metadata.json["observation"]`.
- Comparison CLI accepts `--point-map`, `--fused-map`, optional `--reference-map`, and prints/writes free/occupied/unknown counts plus free-cell connected-component metrics.

- [ ] **Step 1: Write failing tests for optional observation metadata and map metrics**

Expected metrics include:

```json
{
  "width": 100,
  "height": 100,
  "free_cells": 1000,
  "occupied_cells": 500,
  "unknown_cells": 8500,
  "unknown_ratio": 0.85,
  "largest_free_component": 800,
  "free_component_count": 12
}
```

- [ ] **Step 2: Verify RED**

Run the new tests plus existing mapping-artifact tests.

- [ ] **Step 3: Implement comparison CLI and finalization evidence summary**

The CLI is analysis-only and must never activate a Site or write motion state.

- [ ] **Step 4: Update runbook with Benchmark replay command**

Document the accepted replay sequence:

```bash
ros2 launch agt_field_commissioning field_mapping.launch.py \
  site_id:=benchmark_260725 run_id:=raycast_replay_01 \
  runtime_dir:=$PWD/runtime \
  start_hardware:=false start_lidar_self_filter:=false \
  start_operator_gateway:=false use_sim_time:=true \
  start_rviz:=true start_raycast_observer:=true

ros2 bag play ~/agt_navigation_v2/runtime/rosbag/Benchmark-BAG-260725 \
  --clock --topics /agt/sensors/lidar/custom /agt/sensors/imu/data
```

After normal shutdown/finalize/project, compare the point-only baseline and fused map. The historical `/agt/map/mapping_occupancy` remains reference-only.

- [ ] **Step 5: Run the full commissioning no-ROS suite and Python compile**

```bash
PYTHONPATH=src/agt_field_commissioning:src/agt_operator_gateway:src/agt_inspection:src/agt_mission_manager:src/agt_navigation:src/agt_site_runtime:src/agt_runtime_contracts \
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q tests/commissioning

python -m compileall -q \
  src/agt_field_commissioning/agt_field_commissioning \
  src/agt_field_commissioning/scripts \
  src/agt_field_commissioning/launch
```

Expected: `0 failed`, compile exit 0.

- [ ] **Step 6: Commit**

Commit message:

```text
feat: add raycast commissioning acceptance evidence
```

- [ ] **Step 7: Field/offline Benchmark gate before changing default**

On the user workstation, verify:

```text
registered_points ≈ 10 Hz
observer saves free_space_evidence.bin + raycast_record.json
projection_record projection_quality == raycast_fused
unknown ratio decreases substantially in observed corridors
largest free component increases substantially
known obstacle rows/walls remain closed
unseen regions remain unknown
```

Only after this evidence is reviewed should a follow-up commit change:

```python
DeclareLaunchArgument("start_raycast_observer", default_value="false")
```

to `true` for normal field mapping.
