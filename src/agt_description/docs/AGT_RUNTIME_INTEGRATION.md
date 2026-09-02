# Integration into `agt_navigation_runtime`

The corrected package is intentionally standalone so the CAD source can be reviewed before it
changes the runtime repository. For production integration, keep the runtime TF contract:

```text
map -> odom -> base_footprint -> base_link -> chassis_cad_link -> lidar_mount_link -> lidar_link
```

`map -> odom` remains owned by `GlobalCorrectionManager`, while the continuous odometry backend
owns `odom -> base_footprint`. The description package publishes only fixed transforms below
`base_footprint`.

Recommended integration steps:

1. Copy `meshes/chassis_cad.stl` and `meshes/mid360_cad.stl` under
   `src/agt_description/meshes/bunker/`.
2. Add `chassis_cad_link` and `lidar_mount_link` to the BUNKER-specific Xacro rather than replacing
   the repository's `base_footprint/base_link` contract.
3. Move the verified transform values into the BUNKER description calibration YAML.
4. Keep `calibration_verified: false` until the visual + real-vehicle procedure is complete.
5. Add `gnss_link` only when the antenna APC lever arm is measured.
6. Verify there is exactly one parent for every frame and no second `map -> odom` publisher.
