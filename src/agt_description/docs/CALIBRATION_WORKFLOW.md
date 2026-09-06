# Calibration workflow

## Frame ownership

```text
base_footprint
  -> base_link
    -> chassis_cad_link
      -> lidar_mount_link
        -> lidar_link
          -> livox_frame
          -> imu_link
      -> gnss_mount_link (optional)
        -> gnss_link / antenna APC
```

- `base_footprint`: 2D vehicle kinematic reference projected onto the ground.
- `base_link`: rigid ROS vehicle datum, same X/Y as `base_footprint`.
- `chassis_cad_link`: the legacy SolidWorks coordinate system from the supplied export.
- `lidar_mount_link`: nominal SolidWorks MID360 mount pose.
- `lidar_link`: calibrated LiDAR sensing frame used by navigation/localization.
- `gnss_link`: antenna phase center (APC), not the plastic shell top.

## What was fixed

The original export used the SolidWorks `base` coordinate system directly as ROS `base_link`.
That datum is far from the chassis geometric/ground reference, and the package also published
`base_link -> base_footprint`, opposite the intended runtime contract. The corrected wrapper
keeps the CAD datum intact as `chassis_cad_link` and creates explicit ROS vehicle frames above it.

The original chassis STL is visual-only. A primitive box is used as collision geometry so the
338k-triangle CAD mesh is not fed into normal collision/self-filter processing.

## Initial candidate only

The supplied STL has approximate bounds:

```text
X [-0.799902, +0.304000] m
Y [-0.419400, +0.419400] m
Z [-0.823786, +0.075304] m
```

The initial YAML therefore chooses the X/Y bounding-box center and lowest Z as a visualization
candidate for `base_footprint`. This is NOT proof of the true tracked-vehicle kinematic center.

## Recommended real calibration sequence

1. Mechanically define `base_footprint`: tracked chassis effective kinematic center on the ground.
2. Define a repeatable rigid `base_link` datum on the vehicle, keeping the same X/Y.
3. Measure/estimate `base_link -> chassis_cad_link` from CAD + physical references.
4. Preserve `chassis_cad_link -> lidar_mount_link` as the nominal CAD transform.
5. Estimate the real LiDAR extrinsic. If CAD alignment is trusted, place the residual in
   `lidar_mount_to_lidar`. If the estimator directly returns `T_base_lidar`, compute:

   `T_base_cad = T_base_lidar * inverse(T_cad_lidar_mount * T_lidar_mount_lidar)`

   or, when `T_base_cad` is fixed, compute:

   `T_lidar_mount_lidar = inverse(T_base_cad * T_cad_lidar_mount) * T_base_lidar`

6. Add the GNSS APC coordinate in CAD or measure the lever arm, then enable GNSS only after
   filling `gnss.cad_to_mount` / `gnss.mount_to_apc`.
7. Mark `calibration_verified: true` only after static TF checks and vehicle validation.

## Suggested joint calibration observations

Use at least two independent sources so an axis/sign error is observable:

- physical dimensions / known chassis reference points;
- LiDAR ground-plane normal and wall/target geometry;
- IMU gravity direction for roll/pitch consistency;
- visual target or surveyed target pose for yaw/translation;
- straight-line vehicle motion to validate X axis and yaw;
- GNSS lever-arm behavior during rotation to validate antenna offset.

Do not optimize all transforms freely at once unless the experiment provides enough independent
constraints; otherwise CAD alignment and sensor residual can trade off against each other.
