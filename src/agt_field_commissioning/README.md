# agt_field_commissioning

Commissioning-only entry points for producing field map source assets and validating them before they become immutable Site Package data.

This package is intentionally separate from normal Runtime odometry. `agt_odometry/launch/fast_livo2_odometry.launch.py` keeps runtime PCD persistence disabled; `field_mapping.launch.py` uses the vendored FAST-LIO frontend and enables commissioning map persistence.

## Phase A mapping

```bash
ros2 launch agt_field_commissioning field_mapping.launch.py \
  site_id:=greenhouse_01 \
  run_id:=20260829T150000 \
  runtime_dir:=runtime
```

The run writes only below:

```text
runtime/commissioning/<site_id>/<run_id>/mapping/
```

Stop the launch normally so FAST-LIVO2 can execute its shutdown save path. Then verify the output with:

```bash
ros2 run agt_field_commissioning finalize_mapping_run.py \
  --runtime-dir runtime \
  --site-id greenhouse_01 \
  --run-id 20260829T150000
```

`SIGKILL` or a crash is not an accepted successful save path. The finalizer requires a non-empty `localization_map.pcd`, `localization_map.processing.yaml`, no leftover `*.tmp`, and writes SHA256 evidence under the run's `evidence/` directory.

The requested `pcd2pgm` tool is an independent offline conversion step. It runs only
after FAST-LIO has finalized the PCD:

```bash
ros2 launch agt_field_commissioning pcd_to_nav_map.launch.py \
  pcd_path:=runtime/commissioning/greenhouse_01/20260829T150000/mapping/localization_map.pcd \
  output_dir:=runtime/commissioning/greenhouse_01/20260829T150000/navigation_map \
  save_map_name:=navigation
```

Review `navigation.pgm` and `navigation.yaml` before registering the map version.
The project-owned map review/activation gate remains the final authority for the map
consumed by Nav2.

Use `agt_experiment_manager` with the explicit `field_mapping_commissioning` bag profile for Phase A evidence. `agt_field_commissioning` never starts a second recorder owner.

## Phase C frozen-Site navigation

Phase C never consumes a commissioning PCD directly. First export a complete Site Package 1.0 through the offline reconstruction pipeline, deploy and validate it through `agt_site_runtime`, and explicitly activate the revision. Then launch:

```bash
ros2 launch agt_field_commissioning field_navigation.launch.py \
  site_id:=greenhouse_01 \
  site_revision:=r01 \
  sites_root:=/opt/agt/sites \
  state_root:=$HOME/.local/state/agt_navigation_runtime \
  site_vehicle_profile:=/opt/agt/profiles/bunker.yaml \
  operation_mode:=monitor
```

The wrapper re-resolves and revalidates the persisted Active Site and injects only Site-derived navigation/localization paths and hashes into the current Runtime stack. It exposes no manual `global_map_pcd` or `navigation_map` launch argument.

Full operator sequence and acceptance gates are frozen in `docs/runbooks/field-navigation-commissioning.md`.
