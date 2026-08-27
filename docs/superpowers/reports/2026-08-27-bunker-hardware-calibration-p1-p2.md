# BUNKER Hardware + Calibration Capture P1/P2 Acceptance Report

Date: 2026-08-27
Branch: `feat/bunker-rtabmap-slope-nav`
Plan: `docs/superpowers/plans/2026-08-27-bunker-hardware-calibration-capture-p1-p2.md`
Spec: `docs/superpowers/specs/2026-08-27-bunker-rtabmap-slope-nav-design.md`

## Status

```text
CODE_LANDED: PASS
LOCAL_BUILD: pending
HARDWARE_TOPICS: pending
TF_CONTRACT: pending
CALIBRATION_BAG: pending
BAG_METADATA_GATE: pending
```

`CODE_LANDED` means the P1/P2 implementation is present on the feature branch and has completed branch-level static review. It does not claim a ROS 2 build or hardware result. Do not promote any local/hardware state to PASS without fresh evidence from the Runtime machine.

## Implemented scope

- Added provisional `base_link -> gps_link` static frame with six launch-overridable GNSS extrinsic parameters. All GNSS extrinsic defaults remain zero and explicitly unverified.
- Added vendor-neutral `sensor_msgs/msg/NavSatFix` adapter. It preserves timestamp, status, coordinates, altitude, covariance and covariance type, and changes only the canonical frame id.
- Added optional Runtime GNSS wiring and sensor-monitor override. GNSS remains disabled and non-required by default.
- Made BUNKER `operation_mode=monitor` command-inert by remapping the driver's `/cmd_vel` input to `/agt/chassis/monitor_only_cmd_vel_disabled` while retaining wheel odometry and status.
- Added an explicit `calibration` rosbag profile under `agt_experiment_manager`; recording remains manager-owned and never uses record-all.
- Added `tools/calibration/validate_calibration_bag.py` as a metadata-only structural gate.
- Added `calibration_capture.launch.py` with fixed MID360/sensor-monitor/FAST-LIVO2/BUNKER-monitor composition and no Nav2/localization/perception/control-mode override.
- Added operator workflow and hardware acceptance commands to `src/agt_bringup/README.md`.

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

## Required local regression

Run from a clean Runtime shell without sourcing V2:

```bash
cd ~/agt_navigation_runtime
git checkout feat/bunker-rtabmap-slope-nav
git pull
source /opt/ros/humble/setup.bash

colcon build --symlink-install
source install/setup.bash

python3 -m pytest src/agt_bringup/test -q
python3 -m pytest tools/calibration/test_validate_calibration_bag.py -q

colcon test --packages-select \
  agt_description agt_sensor_adapters agt_sensor_monitor \
  agt_chassis agt_bringup agt_experiment_manager
colcon test-result --verbose

ros2 launch agt_bringup calibration_capture.launch.py --show-args
```

Expected before hardware acceptance: zero build/test failures, and the calibration launch must expose only acquisition knobs (`use_sim_time`, `can_interface`, `start_gnss`, `gnss_input_topic`, `runtime_dir`) rather than a navigation/control-mode enable path.

## Hardware gate

With the robot powered and `can0` configured, follow `src/agt_bringup/README.md`. Capture one continuous dataset containing static, straight forward/backward, large-radius left/right turns, figure eight, approximate +/-90 and +/-180 degree turns, gentle slope up/down when available, then static end. Retain spin/slip segments only as diagnostic evidence for later P3 weighting.

After the manager completes the bag, run:

```bash
python3 tools/calibration/validate_calibration_bag.py \
  runtime/experiments/<experiment_id>/rosbag/<calibration_bag_directory>
```

Use `--require-gnss` only for a run whose acceptance explicitly requires GNSS.

## P1/P2 exit condition

P1/P2 remains open until the Runtime machine supplies fresh clean-build/test evidence plus one usable hardware calibration bag whose required canonical topics and TF evidence pass the metadata/preflight gates. Extrinsic estimation, wheel scale estimation, wheel/LIO time-offset estimation, RTAB-Map, GNSS global correction, slope perception, and Nav2 field acceptance are not part of this phase.
