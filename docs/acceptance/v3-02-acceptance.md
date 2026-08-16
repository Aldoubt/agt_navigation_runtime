# V3-02 Acceptance Evidence

## Milestone

**V3-02 Odometry / Localization Separation**

Acceptance date: 2026-08-16

Acceptance branch: `v3-02/acceptance-freeze`

Implementation source branch: `v3-02/odometry-separation`

Implementation source commit before acceptance-record updates: `92f43fd283ae0d370178bd19189721922fd2ac14`

## Acceptance Result

**PASS**

The V3 runtime has replaced the inherited runtime `agt_mapping` responsibility with `agt_odometry` while preserving the FAST-LIVO2 adapter behavior and separating continuous local odometry from global localization ownership.

## Verified Runtime Boundary

- `agt_odometry` owns continuous runtime odometry adaptation
- canonical odometry topic: `/agt/odometry/odometry`
- canonical registered cloud: `/agt/odometry/registered_points`
- backend-private registered cloud: `/agt/odometry/backend/registered_points`
- odometry owns `odom -> base_footprint`
- localization/global correction remains responsible for `map -> odom`
- `src/agt_mapping` is absent from the V3 runtime source tree
- runtime FAST-LIVO2 launch does not expose PCD/map-production controls
- FAST-LIVO2 PCD saving is forced off in runtime launch/configuration
- FAST-LIVO2 local patch provenance is retained under `patches/fast_livo2/`

## Cloud Contract Evidence

GitHub Actions `Runtime Contracts` passed on implementation commit `92f43fd283ae0d370178bd19189721922fd2ac14`.

The workflow executes:

```bash
python -m pytest -q tests/contracts
python -m pytest -q tests/odometry
```

## Local ROS 2 Humble Build Evidence

The independent workspace was built after sourcing ROS 2 Humble and without relying on the V2.5 workspace overlay.

Observed build result:

```text
Summary: 23 packages finished [2min 24s]
  5 packages had stderr output: fast_livo livox_ros_driver2 ndt_omp_ros2 relocalization_core vikit_common
```

`agt_odometry` built successfully:

```text
Starting >>> agt_odometry
Finished <<< agt_odometry [1.31s]
```

The reported FAST-LIVO2 stderr is the existing CMake developer warning for policy `CMP0074` and `PCL_ROOT=/usr`; it is non-fatal and did not prevent `fast_livo` or the complete workspace from building.

## agt_odometry Test Evidence

Command:

```bash
colcon test \
  --packages-select agt_odometry \
  --event-handlers console_direct+

colcon test-result --verbose
```

Observed result:

```text
collected 5 items
../../src/agt_odometry/test/test_fast_livo2_adapter.py ..... [100%]
5 passed in 0.44s

100% tests passed, 0 tests failed out of 1
Summary: 1 package finished [2.36s]
Summary: 6 tests, 0 errors, 0 failures, 0 skipped
```

The adapter regression suite covers sensor/base extrinsic translation, orientation conversion, invalid quaternion rejection, sensor lever-arm twist conversion, and identity-transform handling.

## Launch Resolution Evidence

Command:

```bash
ros2 launch agt_odometry fast_livo2_odometry.launch.py --show-args
```

The command resolved successfully and listed the runtime launch arguments, including installed `agt_odometry` configuration paths and `agt_sensor_adapters` self-filter configuration paths. No package-resolution, import, or missing-file error was reported.

## Acceptance Gate

V3-02 is accepted when all of the following are true:

- cloud runtime-contract tests pass
- independent ROS 2 Humble workspace builds all 23 packages
- `agt_odometry` package tests report zero failures
- `fast_livo2_odometry.launch.py --show-args` resolves successfully
- no V3 runtime source package named `agt_mapping` remains
- no runtime PCD/map-production ownership is reintroduced into `agt_odometry`

All gates above were satisfied by the recorded acceptance evidence.

## Deferred Warning

The FAST-LIVO2 CMake warning for policy `CMP0074` remains intentionally deferred because it is a third-party developer-policy warning, not a runtime or build failure. It may be cleaned later without changing V3-02 behavior.
