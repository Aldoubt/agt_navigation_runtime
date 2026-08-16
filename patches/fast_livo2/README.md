# FAST-LIVO2 Local Patch Provenance

These patch records describe project-local changes applied to the vendored FAST-LIVO2 ROS 2 backend during the V2.5 lineage and retained by the V3 runtime.

They are stored at repository level rather than under `agt_odometry` because they modify the third-party backend, not the AGT odometry adapter package.

Current records:

- `fast_livo2_cmake_portability.patch` — replace workspace-relative Vikit shared-library paths with imported CMake targets
- `fast_livo2_lidar_frame_cloud.patch` — add a LiDAR-frame registered-cloud publisher used by validation/debug workflows
- `fast_livo2_publish_tf.patch` — make backend TF publication configurable so AGT can keep a unique runtime TF authority

`agt_odometry` launches the vendored backend with backend TF disabled and owns the canonical `odom -> base_footprint` transform itself.

These files are provenance records. Before reapplying a patch, compare it against the pinned source under `third_party/fast_livo2_ros2`, because the vendored snapshot may already contain the corresponding change.
