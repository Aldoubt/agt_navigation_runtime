# agt_field_commissioning

Commissioning-only entry points for producing field map source assets and validating them before they become immutable Site Package data.

This package is intentionally separate from normal Runtime odometry. `agt_odometry/launch/fast_livo2_odometry.launch.py` keeps PCD persistence disabled; only `field_mapping.launch.py` enables FAST-LIVO2 map persistence.

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
