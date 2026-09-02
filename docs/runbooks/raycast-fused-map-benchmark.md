# Raycast-Fused Commissioning Map Benchmark

This runbook validates the commissioning free-space reconstruction path against a known MID360 bag before `start_raycast_observer` becomes a normal field-mapping default.

## Authority and safety boundaries

- FAST-LIO is the commissioning 3D mapping frontend and localization-map authority.
- `raycast_free_space_node.py` is observation-only. It subscribes to registered global point clouds and mapped odometry and publishes no TF, velocity, AUTO permit, or chassis command.
- RTAB-Map remains the finalized-PDC ground/obstacle classifier.
- Raycast evidence may promote observed unknown cells to free. It never overrides an RTAB occupied cell.
- A ray endpoint alone does not create a final occupied navigation cell.
- Missing, incomplete, checksum-invalid, frame-invalid, or resolution-invalid evidence produces `projection_quality=pcd_fallback`.
- This benchmark is offline and requires no BUNKER motion.

## Benchmark input

Known dataset on the field workstation:

```text
~/agt_navigation_v2/runtime/rosbag/Benchmark-BAG-260725
```

Required raw topics:

```text
/agt/sensors/lidar/custom
/agt/sensors/imu/data
```

The historical bag topic `/agt/map/mapping_occupancy` is reference-only. Do not replay it into the new mapping run.

## 1. Pull and build the current Runtime branch

```bash
cd ~/agt_navigation_runtime
git checkout feat/field-real-vehicle-integration
git pull --ff-only

source /opt/ros/humble/setup.bash

colcon build \
  --symlink-install \
  --packages-select agt_field_commissioning

source install/setup.bash

ros2 pkg executables agt_field_commissioning | grep -E \
  'raycast_free_space_node.py|compare_commissioning_maps.py|rtabmap_grid_projector|finalize_mapping_run.py'
```

The installed package must expose all four commissioning executables before the replay begins.

## 2. Start a fresh offline mapping run with raycasting enabled

Use a new run ID. Never reuse a populated mapping directory.

```bash
cd ~/agt_navigation_runtime
source /opt/ros/humble/setup.bash
source install/setup.bash

export SITE_ID=benchmark_260725
export RUN_ID=raycast_replay_01
export RUNTIME_DIR="$PWD/runtime"

ros2 launch agt_field_commissioning field_mapping.launch.py \
  site_id:=$SITE_ID \
  run_id:=$RUN_ID \
  runtime_dir:=$RUNTIME_DIR \
  start_hardware:=false \
  start_lidar_self_filter:=false \
  start_operator_gateway:=false \
  operation_mode:=monitor \
  use_sim_time:=true \
  start_rviz:=true \
  start_raycast_observer:=true
```

Expected startup includes both:

```text
fast_lio_commissioning_mapper
agt_commissioning_raycast_free_space
```

The observer defaults to:

```text
cloud=/agt/commissioning/mapping/registered_points
pose=/aft_mapped_to_init
frame=camera_init
resolution=0.05 m
```

## 3. Replay only raw MID360 + IMU data

In a second terminal:

```bash
source /opt/ros/humble/setup.bash
source ~/agt_navigation_runtime/install/setup.bash

ros2 bag play \
  ~/agt_navigation_v2/runtime/rosbag/Benchmark-BAG-260725 \
  --clock \
  --topics \
  /agt/sensors/lidar/custom \
  /agt/sensors/imu/data
```

Do not replay the historical mapping outputs into this run.

## 4. Observe live health during replay

In a third terminal:

```bash
source /opt/ros/humble/setup.bash
source ~/agt_navigation_runtime/install/setup.bash

ros2 topic hz /agt/sensors/lidar/custom
ros2 topic hz /agt/sensors/imu/data
ros2 topic hz /agt/commissioning/mapping/registered_points
ros2 topic info /aft_mapped_to_init -v
```

Expected approximate rates:

```text
LiDAR raw        ~10 Hz
IMU              ~200 Hz
registered cloud ~10 Hz
```

`/agt/commissioning/mapping/odometry` must exist and use `nav_msgs/msg/Odometry`. It is the
FAST-LIO `/Odometry` output remapped by `field_mapping.launch.py`.

## 5. Normal shutdown saves both authorities

After bag playback reaches the end, use normal `Ctrl+C` in the mapping launch terminal. Do not SIGKILL the mapper or observer.

Expected files:

```text
runtime/commissioning/benchmark_260725/raycast_replay_01/
├── mapping/
│   ├── localization_map.pcd
│   └── localization_map.processing.yaml
└── observation/
    ├── free_space_evidence.bin
    └── raycast_record.json
```

Check them:

```bash
RUN_ROOT="$RUNTIME_DIR/commissioning/$SITE_ID/$RUN_ID"
find "$RUN_ROOT" -maxdepth 2 -type f -printf '%p %k KB\n' | sort
cat "$RUN_ROOT/observation/raycast_record.json"
```

The record must show nonzero `accepted_rays`. A missing observation pair means the run is not a raycast acceptance result.

## 6. Finalize the mapping run

```bash
ros2 run agt_field_commissioning finalize_mapping_run.py \
  --runtime-dir "$RUNTIME_DIR" \
  --site-id "$SITE_ID" \
  --run-id "$RUN_ID"
```

Inspect:

```bash
cat "$RUN_ROOT/evidence/mapping_metadata.json"
```

For a valid raycast run, the optional `observation` block must report:

```text
state: READY
projection_quality_candidate: raycast_fused
```

A corrupt/incomplete observation block does not invalidate the authoritative PCD; it is recorded as `INVALID` and projection must fall back to PCD-only semantics.

## 7. Generate the fused navigation map

Start the commissioning review Gateway or use the normal HMI `Generate 2D map` action. The API surface is unchanged.

After projection inspect:

```bash
cat "$RUN_ROOT/projection/projection_record.json"
```

Required for this acceptance run:

```text
schema_version = 2
projection_quality = raycast_fused
fallback_reason = null
fusion.occupied_precedence = true
fusion.endpoint_hit_requires_final_obstacle = true
```

Artifacts include:

```text
projection/rtab_point_map.pgm
projection/rtab_point_map.yaml
projection/raw_map.pgm
projection/raw_map.yaml
projection/projection_record.json
```

`rtab_point_map.pgm` is the point-only baseline generated in the same projection call. `raw_map.pgm` is the fused candidate shown to the HMI.

## 8. Compute objective point-only vs fused metrics

```bash
ros2 run agt_field_commissioning compare_commissioning_maps.py \
  --point-map "$RUN_ROOT/projection/rtab_point_map.pgm" \
  --fused-map "$RUN_ROOT/projection/raw_map.pgm" \
  --json-output "$RUN_ROOT/evidence/raycast_map_comparison.json"
```

The report contains, per map:

```text
free_cells
occupied_cells
unknown_cells
free_ratio
occupied_ratio
unknown_ratio
free_component_count
largest_free_component
```

and fused-minus-point deltas.

The desired benchmark direction is:

```text
unknown_ratio                 decreases substantially
largest_free_component        increases substantially
free corridor fragmentation   decreases
RTAB occupied boundaries      remain occupied
unseen regions                remain unknown
```

Do not accept a map merely because it contains more white cells.

## 9. Optional historical reference

The bag contains historical `/agt/map/mapping_occupancy`. It is useful as a visual/reference baseline, not as the authority for the new Site.

If exported to a PGM with matching semantics, pass it as:

```bash
ros2 run agt_field_commissioning compare_commissioning_maps.py \
  --point-map "$RUN_ROOT/projection/rtab_point_map.pgm" \
  --fused-map "$RUN_ROOT/projection/raw_map.pgm" \
  --reference-map /path/to/historical_reference.pgm \
  --json-output "$RUN_ROOT/evidence/raycast_map_comparison.json"
```

The comparison CLI does not align or resample maps; reference geometry must be interpreted separately if origins/resolutions differ.

## 10. Rollout gate

Keep this launch default until the benchmark is reviewed:

```text
start_raycast_observer:=false
```

Only switch the normal field-mapping default to `true` after all of these are observed on `Benchmark-BAG-260725`:

- registered points remain near the expected mapper rate;
- observer writes a valid evidence pair with nonzero rays;
- projection record reports `raycast_fused`;
- observed roads/corridors become materially more connected;
- known tree rows/walls/structures are not opened by fusion;
- unseen regions remain unknown;
- CPU/memory remains acceptable for the industrial PC.

Until then, production field mapping remains explicitly opt-in for raycast evidence.
