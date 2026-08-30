# Hardware First-Vehicle Acceptance Checklist

This is the first ROS 2 Humble / bench / vehicle acceptance procedure for the Runtime product branch. It is deliberately split into read-only hardware acceptance and later low-speed motion acceptance.

Remote CI does **not** satisfy any item marked `UNVERIFIED`. Record evidence on the actual robot before promoting the item to PASS.

## Safety boundary

Gates 0–5 are read-only. During these gates:

- use `operation_mode:=monitor`;
- do not publish `cmd_vel`;
- do not start a Mission;
- do not call `/agt/safety/set_motion_enabled`;
- do not command the gimbal;
- do not configure SocketCAN from ROS;
- do not run the ROS Runtime with `sudo`.

SocketCAN interface setup belongs to the OS/systemd layer and may require root/CAP_NET_ADMIN. ROS should consume an already configured CAN interface as a normal user.

## Gate 0 — ROS 2 workspace build

Vehicle-side values/dependencies to verify:

- [ ] `UNVERIFIED` Ubuntu 22.04 / ROS 2 Humble environment is sourced.
- [ ] `UNVERIFIED` vendor dependencies such as `bunker_base` and `livox_ros_driver2` resolve on the target computer.
- [ ] `UNVERIFIED` target build succeeds:

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install --packages-up-to agt_hardware_bringup
source install/setup.bash
```

- [ ] `UNVERIFIED` package tests succeed:

```bash
colcon test --packages-select agt_description agt_hardware_bringup
colcon test-result --verbose
```

CI also builds/tests `agt_description` + `agt_hardware_bringup` in a Humble container and executes installed CLI smoke checks. That is software evidence only; it does not replace this target-computer gate.

## Gate 1 — SocketCAN read-only evidence

Determine on the actual vehicle:

- [ ] `UNVERIFIED` actual CAN interface name (`can0` is only the software default).
- [ ] `UNVERIFIED` actual BUNKER CAN bitrate.

First inspect without modifying the interface:

```bash
ip -details -statistics link show <verified-interface>
```

Then run the dynamic read-only check:

```bash
ros2 run agt_hardware_bringup socketcan_preflight.py \
  --interface <verified-interface> \
  --expected-bitrate <verified-bitrate> \
  --observation-sec 5 \
  --json-output can_preflight.json
```

For initial wiring-only work, `--expected-bitrate 0` means the bitrate is intentionally not asserted. Do not treat `0` as a real CAN bitrate.

Acceptance:

- [ ] interface exists and is a CAN link;
- [ ] operational state is `UP`;
- [ ] controller state is `ERROR-ACTIVE` when exposed by the kernel;
- [ ] bitrate matches the verified vehicle value when explicitly asserted;
- [ ] no `berr_tx` / `berr_rx` increase during the observation window;
- [ ] no RX/TX error counter increase;
- [ ] no RX/TX dropped counter increase;
- [ ] JSON before/after/delta evidence is retained.

Any newly accumulating CAN error/drop counter is a blocker. Normal RX/TX packet growth is not an error.

The preflight must not configure, restart or change the bitrate of SocketCAN.

## Gate 2 — Unified BUNKER + MID360 bringup in monitor mode

Start the integrated hardware stack without command execution:

```bash
ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  sensor_profile:=hardware_check \
  can_interface:=<verified-interface> \
  expected_can_bitrate:=<verified-bitrate-or-0>
```

The canonical `agt_description` owner starts by default and should publish:

```text
base_footprint -> base_link -> lidar_link -> livox_frame
                                     \-----> imu_link
```

Acceptance before any motion:

- [ ] `/agt/chassis/status/raw` exists and updates;
- [ ] `/agt/chassis/connected` becomes `true`;
- [ ] `/agt/chassis/rc_state` exists and updates;
- [ ] `/agt/sensors/lidar/custom` exists and updates;
- [ ] `/agt/sensors/imu/data` exists and updates;
- [ ] `/diagnostics` contains `agt_sensor_monitor/*`;
- [ ] no unexpected chassis motion occurs.

## Gate 3 — MID360 stream quality

The authoritative quality source is `agt_sensor_monitor`; do not accept a sensor merely because a topic name exists.

Current persisted network configuration contains candidate values that must still be verified on the installed robot:

- host-side IP: `192.168.1.5` — `UNVERIFIED` physically;
- MID360 IP: `192.168.1.157` — `UNVERIFIED` physically.

Record:

- [ ] `UNVERIFIED` actual Ethernet interface/address matches the selected Livox config;
- [ ] `UNVERIFIED` MID360 is reachable through the installed network path;
- [ ] lidar messages are received continuously;
- [ ] IMU messages are received continuously;
- [ ] timestamps are monotonic;
- [ ] no rollback is observed;
- [ ] stream age remains within the configured stale threshold.

Hardware-check profile acceptance thresholds:

- raw lidar: `rate_hz >= 8 Hz`, stale timeout `0.5 s`;
- IMU: `rate_hz >= 150 Hz`, stale timeout `0.2 s`.

The preflight report must retain at least:

```text
received_count
rate_hz
min_rate_hz
rate_ok
message_age_sec
receive_age_sec
stale
timestamp_monotonic
rollback_count
duplicate_stamp_count
healthy
```

## Gate 4 — Runtime hardware/environment preflight

Run after the monitor stack has reached steady state:

```bash
ros2 run agt_hardware_bringup vehicle_preflight.py \
  --json-output hardware_preflight.json
```

Required acceptance:

- [ ] ROS 2 CLI is available;
- [ ] BUNKER status is live;
- [ ] `/agt/chassis/connected == true`;
- [ ] RC state is live;
- [ ] `agt_sensor_monitor/summary.required_streams_healthy == true`;
- [ ] lidar stream quality is healthy;
- [ ] IMU stream quality is healthy;
- [ ] canonical `/tf_static` topology is present.

The command also records host CPU/load, available memory, free disk and thermal-zone temperature when available. Host threshold violations are `WARN`, not permission to move or an automatic motion blocker.

Final result vocabulary:

```text
PASS
PASS_WITH_WARNINGS
BLOCKED
```

`ready=true` means that no required preflight blocker was observed. It does **not** enable Safety motion and does not mean navigation has been field-accepted.

## Gate 5 — MID360 physical extrinsic / coordinate validation

Software TF topology and physical extrinsic acceptance are separate gates.

The current authoritative file is:

```text
src/agt_description/config/bunker_mid360.yaml
```

It currently carries `calibration_verified: false` until the installed geometry is physically checked.

Verify on the real robot:

- [ ] `UNVERIFIED` `base_link -> lidar_link` x/y/z is measured against the declared base datum;
- [ ] `UNVERIFIED` lidar roll/pitch/yaw matches the installed mount;
- [ ] `base_footprint -> base_link -> lidar_link -> livox_frame/imu_link` is the intended frame chain;
- [ ] RViz confirms +X forward, +Y left, +Z up as intended;
- [ ] point cloud orientation/motion agrees with physical robot motion.

After the persisted values are physically verified, update the configuration and only then set:

```yaml
calibration_verified: true
```

Before a mapping acceptance run, require the strict gate:

```bash
ros2 run agt_hardware_bringup vehicle_preflight.py \
  --require-calibration-verified \
  --json-output mapping_preflight.json
```

With `calibration_verified: false`, `mapping_preflight.json` is expected to be `BLOCKED`. Do not bypass this by using `--skip-static-tf` or by silently compensating in SLAM parameters.

## Gate 6 — Camera + gimbal bench acceptance

The frozen C1 inspection path is already integrated. Start it explicitly while remaining in monitor mode:

```bash
ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  sensor_profile:=hardware_check \
  can_interface:=<verified-interface> \
  expected_can_bitrate:=<verified-bitrate-or-0> \
  start_inspection:=true \
  inspection_camera_device_path:=<verified-/dev/video*> \
  inspection_camera_gimbal_port:=<verified-serial-device> \
  inspection_camera_calibration_id:=<verified-id> \
  inspection_camera_calibration_sha256:=<verified-sha256>
```

Run:

```bash
ros2 run agt_hardware_bringup vehicle_preflight.py \
  --require-camera \
  --require-gimbal \
  --json-output inspection_hardware_preflight.json
```

Camera acceptance:

- [ ] image topic exists;
- [ ] CameraInfo topic exists and is live;
- [ ] device path/VID/PID, resolution/FPS/exposure are recorded;
- [ ] camera calibration identity/hash is recorded.

Frozen gimbal health source is `/camera_gimbal/health`, not legacy `/agt/gimbal/state`.

Required READY semantics:

```text
state == 1
camera_alive == true
gimbal_serial_connected == true
gimbal_feedback_alive == true
move_action_ready == true
busy == false
```

The preflight does not command the gimbal. Gimbal motion/settle/capture timing is accepted later through controlled `AcquireView` testing.

## Gate 7 — BUNKER low-speed motion acceptance

Only after Gates 0–5 pass, and only through the existing authorized Runtime safety path, progress to low-speed motion. Do not bypass `agt_safety` or `agt_chassis_command_guard`.

First discover the physical RC AUTO-permit mapping instead of guessing it:

```bash
ros2 topic echo /agt/chassis/rc_state
```

Move the intended hardware switch and record its real field/value before configuring the AUTO permit adapter.

At very low speed validate:

- [ ] `UNVERIFIED` positive linear command moves the robot forward;
- [ ] `UNVERIFIED` positive angular command turns in the expected ROS direction;
- [ ] command timeout/stop behavior works;
- [ ] `UNVERIFIED` odometry linear sign is correct;
- [ ] `UNVERIFIED` odometry yaw sign is correct;
- [ ] BUNKER status remains connected and healthy under motion;
- [ ] a second dynamic CAN observation shows no abnormal error/drop growth.

Stop immediately if direction, odometry, Safety, RC priority or CAN behavior is ambiguous.

## Gate 8 — Mapping/navigation promotion

Only after the strict mapping preflight passes:

1. run the first FAST-LIVO2 mapping trial;
2. stop normally and verify the PCD is persisted;
3. generate/review the 2D map;
4. verify localization;
5. then progress to one short navigation goal;
6. only after that proceed to multi-point inspection Mission + RETURN_HOME.

Do not treat a successful static preflight as navigation field acceptance.

## Evidence bundle

After the monitor stack has reached steady state, prefer the packaged collector so every bench/vehicle attempt uses one traceable directory:

```bash
ros2 run agt_hardware_bringup acceptance_session.py \
  --output-root vehicle_acceptance \
  --label <session-label> \
  --can-interface <verified-interface> \
  --expected-can-bitrate <verified-bitrate-or-0>
```

Add `--require-camera --require-gimbal` only when the frozen inspection hardware stack is intentionally running.

The collector is read-only: it does not launch the robot stack, configure SocketCAN, enable Safety motion, publish `cmd_vel`, start a Mission, or command the gimbal. Keep one immutable directory per bench/vehicle session:

```text
vehicle_acceptance/<utc-time>-<label>/
├── session.json
├── can_preflight.json
├── hardware_preflight.json
├── mapping_preflight.json
├── inspection_hardware_preflight.json   # when visual hardware is required
├── ros2_topic_list.txt
├── diagnostics.txt
├── tf_snapshot.txt
└── notes.md
```

`session.json.collection_complete=true` means the evidence commands completed and the outputs were retained; it is not a vehicle acceptance verdict. A strict `mapping_preflight.json` may still correctly report `BLOCKED` while `calibration_verified: false`.

For physical checklist items use: `PASS`, `FAIL`, `UNVERIFIED`, `NOT_APPLICABLE`.
For automated preflight JSON use: `PASS`, `PASS_WITH_WARNINGS`, `BLOCKED`.
