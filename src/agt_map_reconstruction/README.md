# agt_map_reconstruction

2.5D BUNKER terrain mapper. The mapping frontend is the vendored FAST-LIO ROS 2 node;
the normal runtime odometry backend remains FAST-LIVO2. The default realtime inputs are `/cloud_registered`
and `/Odometry`; bag-specific names are configured in `reconstruction_realbag.yaml`.

Each grid cell stores `height_mean`, `height_variance`, `min_z`, `max_z`,
`slope`, `roughness`, and `occupancy_probability`. Odometry supplies the
per-frame sensor pose. Ray-traced intermediate cells are free evidence and a
return is occupied only when the cell's height difference/roughness indicates
an obstacle, so ground returns and travelled corridors remain free.

Published topics are `/elevation_map`, `/traversability_map`,
`/navigation_map`, and compatibility `/map`. The output directory contains
`navigation_map.pgm`, `navigation_map.yaml`, `terrain.yaml`, and NPY layers
for every 2.5D field.

Example bag validation:

```bash
ros2 launch agt_map_reconstruction reconstruction.launch.py \
  config:=.../config/reconstruction_realbag.yaml \
  bag:=.../runtime/rosbag/bunker_mid360_mapping_20260901_211105 \
  play_bag:=true
```
