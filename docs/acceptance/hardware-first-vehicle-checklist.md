# Hardware First-Vehicle Acceptance Checklist

This checklist is the first ROS2 Humble / bench / vehicle acceptance procedure for `agt_hardware_bringup`.

Remote development does **not** satisfy any item marked `UNVERIFIED`. Record evidence on the actual robot before promoting the item to PASS.

## Gate 0 — ROS2 workspace build

- [ ] `UNVERIFIED` Ubuntu/ROS2 Humble environment is sourced.
- [ ] `UNVERIFIED` vendor dependencies (`bunker_base`, `livox_ros_driver2`) resolve.
- [ ] `UNVERIFIED` build succeeds:

```bash
colcon build --symlink-install --packages-up-to agt_hardware_bringup
source install/setup.bash
```

- [ ] `UNVERIFIED` package tests succeed:

```bash
colcon test --packages-select agt_hardware_bringup
colcon test-result --verbose
```

Do not continue to vehicle motion if build/test is not clean.

## Gate 1 — SocketCAN read-only evidence

Vehicle values to determine:

- [ ] `UNVERIFIED` actual CAN interface name (`can0` is only the current software default).
- [ ] `UNVERIFIED` actual BUNKER CAN bitrate.
- [ ] `UNVERIFIED` expected normal RX/TX error counters under idle/load.

First inspect without modifying the interface:

```bash
ros2 run agt_hardware_bringup socketcan_preflight.py \
  --interface <verified-interface> \
  --expected-bitrate <verified-bitrate> \
  --json-output can_preflight.json
```

Acceptance:

- [ ] interface exists;
- [ ] link type is CAN;
- [ ] interface state is UP;
- [ ] bitrate matches the verified vehicle value;
- [ ] CAN state is not BUS-OFF;
- [ ] RX/TX/berr counters are captured as evidence.

The preflight must not configure or restart SocketCAN. Interface setup remains an explicit vehicle/platform operation.

## Gate 2 — Unified bringup in monitor mode

Start the integrated hardware stack **without control mode**:

```bash
ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  sensor_profile:=hardware_check \
  can_interface:=<verified-interface> \
  expected_can_bitrate:=<verified-bitrate>
```

Acceptance before any motion:

- [ ] `/agt/chassis/status/raw` exists and updates;
- [ ] `/agt/chassis/connected` becomes `true`;
- [ ] BUNKER diagnostic is not `status_timeout`;
- [ ] BUNKER `error_code == 0` during normal idle;
- [ ] no unexpected chassis motion occurs.

## Gate 3 — MID360 network and stream evidence

Current repository configuration is a candidate only:

- host-side IP candidate: `192.168.1.5` — `UNVERIFIED` on installed robot;
- MID360 IP candidate: `192.168.1.157` — `UNVERIFIED` on installed robot.

Record:

- [ ] `UNVERIFIED` actual Ethernet interface name/address;
- [ ] `UNVERIFIED` MID360 reachability from the vehicle computer;
- [ ] `UNVERIFIED` raw lidar observed rate;
- [ ] `UNVERIFIED` IMU observed rate;
- [ ] `UNVERIFIED` message timestamp monotonicity/age.

Runtime acceptance thresholds in the hardware-check profile:

- raw lidar: at least 8 Hz, stale timeout 0.5 s;
- IMU: at least 150 Hz, stale timeout 0.2 s.

Expected AGT topics:

```text
/agt/sensors/lidar/custom
/agt/sensors/imu/data
```

## Gate 4 — Runtime hardware health evidence

Run the observational vehicle preflight:

```bash
ros2 run agt_hardware_bringup vehicle_preflight.py \
  --json-output hardware_preflight.json
```

Acceptance:

- [ ] required MID360 topics are present and produce messages;
- [ ] BUNKER raw status produces messages;
- [ ] `/agt/chassis/connected == true`;
- [ ] `/diagnostics` contains `agt_sensor_monitor/summary`;
- [ ] `required_streams_healthy == true`;
- [ ] generated JSON evidence is retained with the test record.

Do not switch to the navigation sensor profile until the filtered lidar producer is running and validated.

## Gate 5 — Installed TF / coordinate validation

The following cannot be accepted remotely:

- [ ] `UNVERIFIED` `base_link -> livox_frame` translation;
- [ ] `UNVERIFIED` lidar mounting roll/pitch/yaw;
- [ ] `UNVERIFIED` physical frame convention matches robot convention;
- [ ] RViz confirms +X forward, +Y left, +Z up as intended;
- [ ] point cloud moves consistently with physical robot motion.

Do not compensate an incorrect physical/URDF transform by silently changing SLAM parameters.

## Gate 6 — BUNKER low-speed motion acceptance

Only after Gates 0–5 pass, explicitly start/control through the existing authorized Runtime safety path. Do not bypass `agt_safety` or `agt_chassis_command_guard`.

Validate at very low speed:

- [ ] `UNVERIFIED` positive linear command moves robot forward;
- [ ] `UNVERIFIED` positive angular command turns in the expected ROS direction;
- [ ] stop/timeout behavior works;
- [ ] `UNVERIFIED` odometry linear sign is correct;
- [ ] `UNVERIFIED` odometry yaw sign is correct;
- [ ] BUNKER status remains connected and error-free during motion;
- [ ] CAN counters do not show abnormal growth / BUS-OFF.

Stop here if any direction, odometry, safety, or CAN behavior is ambiguous.

## Gate 7 — Navigation profile and navigation

Only after the filtered lidar pipeline is available:

```bash
ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  sensor_profile:=navigation \
  can_interface:=<verified-interface> \
  expected_can_bitrate:=<verified-bitrate>
```

Acceptance before Nav2 motion:

- [ ] `/agt/sensors/lidar/custom_filtered` exists and satisfies monitor thresholds;
- [ ] `agt_sensor_monitor/summary` remains healthy;
- [ ] localization/TF is valid;
- [ ] Runtime readiness is not blocked by hardware health.

Then progress separately: localization → one short goal → short controlled path → multi-point mission.

## Gate 8 — Camera / gimbal integration (after visual-team delivery)

The legacy evidence only proves these ROS1 interfaces existed:

```text
/cv_camera0/image_raw
/pantilt_camera_serial0/pantilt_angle_info
  fields: heading, roll, pitch
```

Runtime integration targets are frozen in:

```text
src/agt_hardware_bringup/config/visual_interface_contract.yaml
```

Vehicle values still `UNVERIFIED`:

- [ ] actual ROS2 camera driver/launch;
- [ ] `/dev/video*` / VID/PID;
- [ ] resolution, FPS, exposure;
- [ ] CameraInfo/calibration source;
- [ ] actual ROS2 gimbal driver/launch;
- [ ] serial device / VID/PID / baudrate;
- [ ] angle units;
- [ ] heading/pitch/roll sign conventions;
- [ ] zero definition;
- [ ] mechanical limits;
- [ ] command interface;
- [ ] command-to-feedback tolerance;
- [ ] settle time before image capture.

When available, run:

```bash
ros2 run agt_hardware_bringup vehicle_preflight.py \
  --require-camera \
  --require-gimbal \
  --json-output inspection_hardware_preflight.json
```

A camera image stream alone does not prove the gimbal is controllable or healthy.

## Promotion record

Do not mark the hardware stack vehicle-ready until all required gates for the intended mode are PASS.

Suggested evidence bundle:

```text
vehicle_acceptance/<date>/
├── can_preflight.json
├── hardware_preflight.json
├── inspection_hardware_preflight.json   # when applicable
├── ros2_topic_list.txt
├── diagnostics.txt
├── tf_snapshot.txt
└── notes.md
```

Status vocabulary: `PASS`, `FAIL`, `UNVERIFIED`, `NOT_APPLICABLE`.
