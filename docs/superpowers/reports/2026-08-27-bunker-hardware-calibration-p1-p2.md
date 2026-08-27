# BUNKER Hardware + Calibration Capture P1/P2 Acceptance Report

Date: 2026-08-27
Branch: `feat/bunker-rtabmap-slope-nav`
Plan: `docs/superpowers/plans/2026-08-27-bunker-hardware-calibration-capture-p1-p2.md`
Spec: `docs/superpowers/specs/2026-08-27-bunker-rtabmap-slope-nav-design.md`

## Status

```text
CODE_LANDED: PASS
LOCAL_BUILD: PASS (user Runtime evidence: 24/24 packages)
SOFTWARE_TESTS: rerun pending after sensor-monitor contract fix
HARDWARE_TOPICS: pending
TF_CONTRACT: pending hardware echo
CALIBRATION_BAG: pending
BAG_METADATA_GATE: pending real bag
```

`CODE_LANDED` means the P1/P2 implementation is present on the feature branch and has completed branch-level static review. `LOCAL_BUILD` is based on fresh user Runtime evidence showing `Summary: 24 packages finished`. Hardware and real-bag states remain pending until measured on the robot.

## Implemented scope

- Added provisional `base_link -> gps_link` static frame with six launch-overridable GNSS extrinsic parameters. All GNSS extrinsic defaults remain zero and explicitly unverified.
- Added vendor-neutral `sensor_msgs/msg/NavSatFix` adapter. It preserves timestamp, status, coordinates, altitude, covariance and covariance type, and changes only the canonical frame id.
- Added optional Runtime GNSS wiring and sensor-monitor override. GNSS remains disabled and non-required by default.
- Made BUNKER `operation_mode=monitor` command-inert by remapping the driver's `/cmd_vel` input to `/agt/chassis/monitor_only_cmd_vel_disabled` while retaining wheel odometry and status.
- Added an explicit `calibration` rosbag profile under `agt_experiment_manager`; recording remains manager-owned and never uses record-all.
- Added `tools/calibration/validate_calibration_bag.py` as a metadata-only structural gate.
- Added `calibration_capture.launch.py` with fixed MID360/sensor-monitor/FAST-LIVO2/BUNKER-monitor composition and no Nav2/localization/perception/control-mode override.
- Added operator workflow and hardware acceptance commands to `src/agt_bringup/README.md`.
- Repaired the sensor-monitor contract test so it checks the current readiness consumer (`agt_safety`) rather than the removed `agt_system_manager` package.

## Execution rulings

### GNSS antenna extrinsic

The repository does not contain a physically verified GNSS antenna position. The implementation therefore creates the frame contract with zero placeholders and keeps `calibration_verified: false` / `extrinsic_verified: false`. No antenna translation or orientation was invented.

### Description launch propagation

The original P1 plan named the xacro/config/profile files but omitted the generic `description.launch.py` propagation layer. Review found that adding `gps_*` only to xacro/YAML would leave future measured values unused. The implementation therefore also extends the shared XACRO argument list and gives the mk_mini shared description zero GNSS defaults so launch composition remains complete.

### Command topic in calibration bags

The plan listed `/agt/navigation/cmd_vel` in the calibration recording profile and also required calibration capture to be command-inert. Requiring non-zero command messages would make a correct monitor-mode bag fail validation. Ruling: keep `/agt/navigation/cmd_vel` in the explicit recording profile for auditability, but do not require non-zero command messages in the metadata acceptance gate. GNSS is similarly optional unless `--require-gnss` is requested.

### Motion source during safe capture

`calibration_capture.launch.py` intentionally provides no ROS motion command path. Dynamic excitation must use an independently validated manual/RC chassis control path. If such a path is unavailable, do not change this capture launch to control mode as an implicit workaround; validate a separate controlled-motion procedure first.

### MID360 IMU frame naming

The existing Livox launch supplies a single `frame_id=livox_frame` to the driver for both LiDAR and built-in IMU messages, while the robot description also exposes identity-linked `lidar_link` and `imu_link`. The BUNKER profile now records both the physical frame and `driver_frame: livox_frame`. Hardware acceptance must still record the actual message header and TF chain before a later phase promotes a different IMU frame convention. P1/P2 does not silently rewrite MID360 IMU measurements.

### Sensor-monitor readiness ownership

The old `test_sensor_monitor_contract.py` still tried to read `agt_system_manager/config/health_contracts.yaml` and `agt_system_manager/readiness.py`, but `agt_system_manager` is no longer part of this Runtime tree. The current production consumer is `agt_safety`: `bunker_safety.yaml` requires sensor input readiness from `/diagnostics` using summary `agt_sensor_monitor/summary`, and `tracked_safety_controller.py` interprets `required_streams_healthy` and fails closed with `sensor_input_unhealthy`. The test now checks that real path instead of depending on a removed package.

### `launch --show-args` interpretation

ROS 2 recursively displays arguments declared by included launch descriptions. Therefore `calibration_capture.launch.py --show-args` legitimately shows arguments from `system.launch.py`, description, mapping, localization, navigation and chassis sub-launches. This is not evidence that the calibration entry exposes those values as top-level overrides. The safety contract is verified from `calibration_capture.launch.py` itself: it fixes `start_perception=false`, `start_localization=false`, `start_navigation=false`, `start_chassis=true`, and `chassis_operation_mode=monitor` when including the Runtime system launch.

## User Runtime verification round

Observed before the sensor-monitor test repair:

```text
Summary: 24 packages finished
agt_bringup pytest: 17 passed
calibration validator pytest: 7 passed
colcon selected packages: one logical failure in agt_sensor_monitor
```

The failing test attempted to open the removed path:

```text
src/agt_system_manager/config/health_contracts.yaml
```

That test has now been repaired on the feature branch. A focused rerun is required before hardware deployment.

The build also printed stale `AMENT_PREFIX_PATH` / `CMAKE_PREFIX_PATH` warnings because the shell still contained paths from an earlier Runtime `install/` tree after a clean rebuild. These warnings did not prevent the 24-package build. For future clean builds, open a fresh shell, source only `/opt/ros/humble/setup.bash`, build, then source the newly generated `install/setup.bash`.

## Required pre-deployment regression

From a fresh shell:

```bash
cd ~/agt_navigation_runtime
git checkout feat/bunker-rtabmap-slope-nav
git pull
source /opt/ros/humble/setup.bash

# Existing build is sufficient for this test-only change; no full rebuild is required.
python3 -m pytest src/agt_sensor_monitor/test/test_sensor_monitor_contract.py -q

source install/setup.bash
colcon test --packages-select \
  agt_sensor_monitor agt_description agt_sensor_adapters \
  agt_chassis agt_bringup agt_experiment_manager
colcon test-result --verbose
```

Expected before hardware deployment: zero test failures.

## Hardware gate

With the robot powered and `can0` configured, follow `src/agt_bringup/README.md`. Capture one continuous dataset containing static, straight forward/backward, large-radius left/right turns, figure eight, approximate +/-90 and +/-180 degree turns, gentle slope up/down when available, then static end. Retain spin/slip segments only as diagnostic evidence for later P3 weighting.

After the manager completes the bag, run:

```bash
python3 tools/calibration/validate_calibration_bag.py \
  runtime/experiments/<experiment_id>/rosbag/<calibration_bag_directory>
```

Use `--require-gnss` only for a run whose acceptance explicitly requires GNSS.

## P1/P2 exit condition

P1/P2 remains open until the repaired software test suite is green plus one usable hardware calibration bag whose required canonical topics and TF evidence pass the metadata/preflight gates. Extrinsic estimation, wheel scale estimation, wheel/LIO time-offset estimation, RTAB-Map, GNSS global correction, slope perception, and Nav2 field acceptance are not part of this phase.
