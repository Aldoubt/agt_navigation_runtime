# P1-06 Field Navigation Commissioning Runbook

Status: software/static commissioning path. ROS 2 Humble and BUNKER + MID360 field evidence are still pending.

This runbook selectively ports the useful field workflow from `feat/field-navigation-baseline` into the canonical `feat/runtime-navigation-convergence-p1` architecture. It does **not** restore the old `agt_bringup` ownership model or manual `global_map_pcd/navigation_map` wiring.

Authority rules are fixed:

- `agt_experiment_manager` is the only rosbag recorder owner.
- `agt_field_commissioning` owns commissioning entry points and mutable source artifacts only.
- `agt_site_runtime` owns deployed Site discovery, validation, persistence of the active Site, and `/agt/maps/active`.
- `agt_site_navigation` consumes the active Site and publishes navigation binding/runtime readiness evidence.
- GlobalCorrectionManager remains the only `map -> odom` owner.
- Nav2 owns planning/control after the navigation gate is satisfied.

The boundary is intentional: **commissioning output is mutable**; **Site Package is immutable**; **changing tasks never rebuilds the Site Package**. Mutable tasks remain under `runtime/tasks/<site_id>/<revision>/`. **do not navigate directly from commissioning output**.

## 0. Shell and IDs

```bash
cd ~/agt_navigation_runtime
source /opt/ros/humble/setup.bash
source install/setup.bash

export SITE_ID=greenhouse_01
export RUN_ID=20260829T160000
export SITE_REVISION=r01
export RUNTIME_DIR="$PWD/runtime"
export SITES_ROOT=/opt/agt/sites
export STATE_ROOT="$HOME/.local/state/agt_navigation_runtime"
export VEHICLE_PROFILE=/opt/agt/profiles/bunker.yaml
```

Use a new `RUN_ID` for every attempt. Never overwrite a previous commissioning run or a deployed Site revision.

## 1. Start the single recorder owner

```bash
ros2 launch agt_experiment_manager experiment_manager.launch.py \
  runtime_dir:=$RUNTIME_DIR \
  repository_root:=$PWD
```

Create one experiment for this mapping run:

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 5,
  experiment_title: '${SITE_ID}_${RUN_ID}',
  objective: 'P1-06 field navigation commissioning',
  tags_json: '[\"commissioning\",\"field-mapping\"]',
  operator_note: 'one run_id and one evidence bag per mapping attempt',
  map_id: '${SITE_ID}',
  map_version_id: '${SITE_REVISION}',
  launch_profile: 'agt_field_commissioning/field_mapping',
  start_experiment: true
}"
```

Copy the returned experiment ID:

```bash
export EXP_ID=<returned_experiment_id>
```

## 2. Phase A mapping

Start the dedicated mapper in a second terminal:

```bash
ros2 launch agt_field_commissioning field_mapping.launch.py \
  site_id:=$SITE_ID \
  run_id:=$RUN_ID \
  runtime_dir:=$RUNTIME_DIR \
  operation_mode:=monitor \
  start_hardware:=true \
  start_lidar_self_filter:=true
```

The only accepted mapping output root is:

```text
runtime/commissioning/<site_id>/<run_id>/mapping/
```

The launch refuses to reuse a non-empty mapping directory. It starts FAST-LIVO2 directly with PCD persistence enabled only for commissioning; normal Runtime odometry keeps PCD persistence disabled.

### 2.1 Start the commissioning rosbag

The explicit recorder profile is `field_mapping_commissioning`. It records raw/filtered MID360 input, IMU, commissioning registered points, chassis odometry/status and diagnostics; it deliberately does not record the normal Runtime `/agt/odometry/registered_points` topic as mapping evidence.

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 1,
  experiment_id: '${EXP_ID}',
  profile_id: 'field_mapping_commissioning'
}"
```

Confirm recorder state before moving:

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{operation: 0}"
ros2 topic hz /agt/sensors/lidar/custom
ros2 topic hz /agt/sensors/imu/data
ros2 topic hz /agt/commissioning/mapping/registered_points
ros2 topic hz /agt/chassis/odometry
ros2 topic echo --once /agt/chassis/status
ros2 run tf2_ros tf2_echo odom base_footprint
```

Do not move if the required topics/TF are absent or unstable. Keep the chassis in monitor mode for this software commissioning step.

### 2.2 Mapping trajectory and shutdown

Collect a representative route: static start, forward/reverse, left/right large turns, S-turn/figure-eight where safe, representative row entrances/exits and static end. A failed run gets a new `RUN_ID`.

Finish Phase A with **normal Ctrl+C / ROS shutdown** in the `field_mapping.launch.py` terminal. Do not use `SIGKILL`; FAST-LIVO2 needs the shutdown path to persist the final PCD.

After the mapper exits, stop recording:

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 2,
  experiment_id: '${EXP_ID}'
}"
```

## 3. Finalize the mutable mapping source

Run the packaged finalizer:

```bash
ros2 run agt_field_commissioning finalize_mapping_run.py \
  --runtime-dir "$RUNTIME_DIR" \
  --site-id "$SITE_ID" \
  --run-id "$RUN_ID"
```

`finalize_mapping_run.py` must find a non-empty:

```text
runtime/commissioning/<site_id>/<run_id>/mapping/localization_map.pcd
runtime/commissioning/<site_id>/<run_id>/mapping/localization_map.processing.yaml
```

It rejects leftover `*.tmp` files and atomically writes:

```text
runtime/commissioning/<site_id>/<run_id>/evidence/mapping_metadata.json
```

Treat this as source/evidence only. It is still mutable commissioning data and is not a navigation authority.

## 4. offline reconstruction/export

Offline map reconstruction is intentionally outside the Runtime repository. Consume the finalized PCD/bag evidence in the map-reconstruction pipeline and export a complete **Site Package 1.0** directory. Runtime does not invent a hidden PCD-to-PGM command here.

The exported revision must at minimum satisfy the canonical contract represented by `schemas/site_package.schema.json` and contain the manifest-declared assets, e.g.:

```text
<SITE_EXPORT>/
├── manifest.yaml
├── hashes.yaml
├── map/
│   ├── navigation.yaml
│   ├── navigation.pgm        # or the image referenced by navigation.yaml
│   └── localization_map.pcd
├── semantic/
│   └── semantic_map.yaml
└── routes/
    └── route_graph.yaml
```

`manifest.yaml` owns Site identity (`site.id`, `site.revision`), asset paths and vehicle compatibility. `hashes.yaml` owns SHA256 integrity for every contract asset. If the localization map needs a processing record, include it in the exported package and manifest-compatible metadata used by the runtime.

Example boundary variables:

```bash
export SITE_EXPORT=/absolute/path/to/offline/export/$SITE_ID/$SITE_REVISION
test -f "$SITE_EXPORT/manifest.yaml"
test -f "$SITE_EXPORT/hashes.yaml"
test -f "$SITE_EXPORT/map/navigation.yaml"
test -f "$SITE_EXPORT/map/localization_map.pcd"
```

Do not point Phase C at `$RUNTIME_DIR/commissioning/.../localization_map.pcd`.

## 5. deploy under sites_root

Deployment creates a new immutable revision. Refuse overwrite:

```bash
export DEPLOY_DIR="$SITES_ROOT/$SITE_ID/$SITE_REVISION"
test ! -e "$DEPLOY_DIR"
mkdir -p "$SITES_ROOT/$SITE_ID"
cp -a "$SITE_EXPORT" "$DEPLOY_DIR"
```

After deployment, do not edit files in place. If any map asset, hash, frame declaration or compatibility field changes, export a new `SITE_REVISION` and deploy that revision instead.

## 6. Runtime validation

Start the canonical Site Runtime using the same roots/profile that Phase C will use:

```bash
ros2 run agt_site_runtime site_runtime_node.py --ros-args \
  -p sites_root:="$SITES_ROOT" \
  -p state_root:="$STATE_ROOT" \
  -p vehicle_profile:="$VEHICLE_PROFILE"
```

Validate the deployed revision through `/agt/maps/validate` using `agt_interfaces/srv/ValidateMapVersion`:

```bash
ros2 service call /agt/maps/validate agt_interfaces/srv/ValidateMapVersion "{
  map_id: '${SITE_ID}',
  map_version_id: '${SITE_REVISION}'
}"
```

Required result before activation:

```text
success: true
version.state: READY
version.valid: true
```

Record the returned `map_hash`, `manifest_sha256`, `navigation_yaml_sha256`, `navigation_image_sha256`, and `localization_pcd_sha256` in the experiment notes/acceptance evidence. Any blocker means this Site revision is rejected; fix the offline export and create a new revision rather than patching the deployed directory.

## 7. Explicit Site activation

Activation uses `/agt/maps/activate` and `agt_interfaces/srv/ActivateMapVersion` with a unique idempotency key:

```bash
export ACTIVATE_REQUEST_ID="commission-${SITE_ID}-${SITE_REVISION}-${RUN_ID}"

ros2 service call /agt/maps/activate agt_interfaces/srv/ActivateMapVersion "{
  map_id: '${SITE_ID}',
  map_version_id: '${SITE_REVISION}',
  client_request_id: '${ACTIVATE_REQUEST_ID}'
}"
```

The canonical policy is fail-closed: **activation revalidates the current deployed Site before persisting it**. Therefore activation is not a blind promotion of the earlier validation result. Reusing the same `client_request_id` for another Site/revision is rejected.

Confirm the transient-local active authority:

```bash
ros2 topic echo --once /agt/maps/active
```

Required evidence is the exact requested `map_id/map_version_id`, `active=true`, `valid=true`, READY state, plus the same `map_hash`, `manifest_sha256`, `navigation_yaml_sha256`, `navigation_image_sha256`, and `localization_pcd_sha256` that were validated.

## 8. Phase C navigation

Stop the standalone Site Runtime process above, then use the commissioning wrapper so there is one Site Runtime process in the composed stack:

```bash
ros2 launch agt_field_commissioning field_navigation.launch.py \
  site_id:=$SITE_ID \
  site_revision:=$SITE_REVISION \
  sites_root:=$SITES_ROOT \
  state_root:=$STATE_ROOT \
  site_vehicle_profile:=$VEHICLE_PROFILE \
  runtime_dir:=$RUNTIME_DIR \
  operation_mode:=monitor \
  start_hardware:=true \
  start_rviz:=true
```

`field_navigation.launch.py` resolves the persisted Active Site, re-runs the Site validator, checks identity/hash/path equality, and only then injects Site-derived navigation YAML/PCD/hash values into localization and Nav2. There are no `global_map_pcd` or `navigation_map` operator launch arguments.

P1-06 acceptance is readiness observation only; do not send a motion goal merely because RViz is open. Direct RViz-goal guarding is P1-07 and full BUNKER + MID360 motion acceptance is P1-09.

Observe:

```bash
ros2 topic echo --once /agt/maps/active
ros2 topic echo --once /agt/navigation/site_binding
ros2 topic echo --once /agt/localization/status
ros2 topic echo --once /agt/navigation/runtime_status
ros2 topic echo --once /agt/system/task_readiness
ros2 lifecycle get /map_server
ros2 lifecycle get /planner_server
ros2 lifecycle get /controller_server
ros2 run tf2_ros tf2_echo map odom
ros2 run tf2_ros tf2_echo odom base_footprint
```

Do not mark field readiness from this document alone. HUMBLE and FIELD remain separate acceptance gates until fresh build/runtime/hardware evidence exists.

## 9. P1-06 evidence checklist

```text
[ ] unique SITE_ID/RUN_ID/SITE_REVISION recorded
[ ] one ExperimentManager experiment created
[ ] field_mapping_commissioning bag started and stopped normally
[ ] Phase A mapper ended through normal ROS shutdown
[ ] finalize_mapping_run.py accepted the mapping artifacts
[ ] mapping_metadata.json stored with SHA256 evidence
[ ] offline exporter produced a complete Site Package 1.0
[ ] new revision deployed without overwriting an existing revision
[ ] /agt/maps/validate returned success + READY + valid
[ ] /agt/maps/activate returned success for a unique client_request_id
[ ] /agt/maps/active matches the requested immutable Site revision
[ ] Phase C consumes Site-derived assets, not commissioning paths
[ ] NavigationRuntimeStatus/SystemManager evidence captured
[ ] HUMBLE acceptance recorded separately
[ ] BUNKER + MID360 FIELD acceptance recorded separately
```
