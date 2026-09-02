# agt_hardware_bringup

`agt_hardware_bringup` is the read-only first-vehicle acceptance layer for BUNKER + MID360 and the frozen C1 camera/gimbal inspection path. It composes existing Runtime owners and collects evidence; it does not own navigation, publish chassis commands, enable Safety motion, configure SocketCAN, start missions, or command the gimbal.

## 1. First vehicle launch: monitor mode

Start with motion disabled at the orchestration layer:

```bash
ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  sensor_profile:=hardware_check \
  can_interface:=can0 \
  expected_can_bitrate:=0
```

The launch now also starts the canonical `agt_description` BUNKER description owner by default. It publishes the migrated CAD-backed fixed chain:

```text
base_footprint -> base_link -> lidar_link -> livox_frame / imu_link
```

`expected_can_bitrate:=0` means **do not assert a bitrate**. This is intentional before the real BUNKER bitrate is verified. The launch-time SocketCAN preflight is a fast read-only snapshot; it checks that the interface exists, is CAN, is UP, is ERROR-ACTIVE when the kernel exposes controller state, and is not misconfigured against an explicitly supplied bitrate.

After the actual bitrate is confirmed on the physical vehicle, pass it explicitly.

## 2. Sensor profiles

- `hardware_check`: raw MID360 CustomMsg + MID360 IMU are required. Filtered lidar and camera inputs are disabled so low-level hardware testing is not blocked by perception nodes that have not started yet.
- `navigation`: raw MID360 + filtered lidar + IMU are required. Camera and gimbal remain outside navigation readiness by default.

The authoritative stream-quality source is `agt_sensor_monitor` on `/diagnostics`. The preflight consumes its existing per-stream metrics rather than duplicating rate measurement with shell polling:

- `received_count`
- `rate_hz` / `min_rate_hz` / `rate_ok`
- `message_age_sec` / `receive_age_sec`
- stale state
- timestamp monotonicity
- rollback count
- duplicate timestamp count
- final stream health

## 3. SocketCAN acceptance

The CLI performs a read-only observation window by default so transient CAN errors are not hidden by a single snapshot:

```bash
ros2 run agt_hardware_bringup socketcan_preflight.py \
  --interface can0 \
  --expected-bitrate 0 \
  --observation-sec 5 \
  --json-output can_preflight.json
```

After the bitrate is verified, replace `0` with the verified value.

The observation compares before/after values for:

- CAN controller state;
- `berr-counter` TX/RX;
- RX/TX errors;
- RX/TX dropped packets.

Any newly accumulating CAN error/drop counter is a blocker. Ordinary RX/TX packet growth is not an error. The tool never changes link state or bitrate.

SocketCAN interface configuration belongs to the OS/systemd layer and may require root/CAP_NET_ADMIN. Do not start the ROS Runtime with `sudo` just to obtain CAN configuration privileges.

## 4. ROS + sensor + environment preflight

After `bunker_mid360.launch.py` has reached steady state:

```bash
ros2 run agt_hardware_bringup vehicle_preflight.py \
  --json-output hardware_preflight.json
```

The standard field CLI checks:

- ROS 2 CLI availability;
- BUNKER raw status and `connected=true`;
- BUNKER RC state is present and live;
- MID360 lidar and IMU stream quality from `agt_sensor_monitor`;
- canonical fixed TF topology on `/tf_static`;
- BUNKER/MID360 calibration verification state;
- CPU count/load evidence;
- available memory;
- free disk space;
- thermal-zone temperature when exposed by the kernel.

Host resource thresholds are **warning thresholds only**. They can produce `PASS_WITH_WARNINGS` but do not grant or revoke chassis motion. Defaults are 1024 MiB available memory, 5 GiB free disk and 90 C maximum observed thermal-zone temperature; override them when the target computer has a documented deployment profile.

Possible final results are:

```text
PASS
PASS_WITH_WARNINGS
BLOCKED
```

`ready=true` means no required preflight blocker was observed. It does **not** enable Safety motion and does not mean field navigation has been accepted.

## 5. MID360 physical-extrinsic gate

`agt_description/config/cad_alignment.initial_guess.yaml` is the authoritative persisted BUNKER/MID360 geometry source. The fixed TF topology and the physical calibration verdict are deliberately separate checks:

- fixed TF topology present: software wiring is complete;
- `calibration_verified: true`: physical installation has been measured/accepted.

For a wiring/bench check, an unverified calibration is reported as a warning.

Before declaring the robot ready for a mapping acceptance run, use the strict gate:

```bash
ros2 run agt_hardware_bringup vehicle_preflight.py \
  --require-calibration-verified \
  --json-output mapping_preflight.json
```

With the repository's current `calibration_verified: false`, this command must return `BLOCKED`. Do not change the flag to `true` until the installed BUNKER `base_link` datum and MID360 x/y/z/roll/pitch/yaw have been physically checked and the persisted values updated.

The TF existence check can be skipped only for isolated sensor-driver debugging:

```bash
ros2 run agt_hardware_bringup vehicle_preflight.py --skip-static-tf
```

Do not use `--skip-static-tf` as mapping acceptance evidence.

## 6. Inspection camera + gimbal acceptance

Normal BUNKER/MID360 bringup keeps inspection **disabled by default**. For the inspection MVP, explicitly opt in to the vendored C1 camera/gimbal stack and `agt_inspection` server:

```bash
ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  sensor_profile:=hardware_check \
  can_interface:=can0 \
  expected_can_bitrate:=<verified-bitrate-or-0-for-monitor-only> \
  start_inspection:=true \
  inspection_camera_device_path:=/dev/video0 \
  inspection_camera_gimbal_port:=/dev/ttyUSB0 \
  inspection_camera_calibration_id:=<verified-calibration-id> \
  inspection_camera_calibration_sha256:=<verified-calibration-sha256>
```

Then require both visual devices in preflight:

```bash
ros2 run agt_hardware_bringup vehicle_preflight.py \
  --require-camera \
  --require-gimbal \
  --json-output inspection_hardware_preflight.json
```

The frozen gimbal acceptance source is `/camera_gimbal/health`, not the legacy `/agt/gimbal/state`. A required gimbal passes only when:

```text
state == READY (1)
camera_alive == true
gimbal_serial_connected == true
gimbal_feedback_alive == true
move_action_ready == true
busy == false
```

The preflight does not issue a gimbal move. The inspection task backend remains responsible for atomic `AcquireView` during an actual mission.

`start_inspection:=true` must **not** be combined with legacy `start_camera:=true` or `start_gimbal:=true` hooks; the launch rejects that combination to avoid double ownership.

For first field deployment, use schema-v2 inspection tasks with `vision.execution_mode: "DEFERRED"`. Online flower inference remains outside the frozen front-half Runtime MVP.

## 7. Repeatable evidence session

Once the monitor-mode hardware stack is steady, collect the read-only acceptance evidence as one immutable session instead of running and copying each command manually:

```bash
ros2 run agt_hardware_bringup acceptance_session.py \
  --output-root vehicle_acceptance \
  --label bench-01 \
  --can-interface <verified-interface> \
  --expected-can-bitrate <verified-bitrate-or-0>
```

When the camera/gimbal stack is intentionally running, add `--require-camera --require-gimbal`.

The session CLI only invokes the existing read-only preflight and ROS inspection commands. It does not launch the robot stack, publish `cmd_vel`, enable Safety motion, start a Mission, command the gimbal, or configure SocketCAN. Each invocation creates a new UTC timestamped directory and retains:

```text
vehicle_acceptance/<utc-time>-<label>/
├── session.json
├── can_preflight.json
├── hardware_preflight.json
├── mapping_preflight.json
├── inspection_hardware_preflight.json   # only when requested
├── ros2_topic_list.txt
├── diagnostics.txt
├── tf_snapshot.txt
└── notes.md
```

`session.json.collection_complete=true` means the evidence commands completed and their outputs were retained. It does **not** mean every preflight passed. In particular, the strict mapping preflight may legitimately be recorded as `BLOCKED` while `calibration_verified: false`; that blocker must remain visible until the physical extrinsic is verified.

The generated `notes.md` deliberately leaves physical observations as `UNVERIFIED`. An operator must change those items only from real bench/vehicle evidence using `PASS`, `FAIL`, `UNVERIFIED`, or `NOT_APPLICABLE`.

## 8. What this preflight proves

A green software/bench preflight proves only the evidence it actually measured. It does not replace physical field acceptance.

Still **UNVERIFIED** until checked on the real vehicle:

- actual SocketCAN interface name;
- BUNKER CAN bitrate and error behavior under real bus load;
- MID360 host NIC address and reachability of the installed lidar;
- real lidar/IMU rates and timestamp behavior;
- physical `base_link -> lidar_link` translation/orientation;
- BUNKER forward/angular sign and odometry sign;
- camera `/dev/video*`, VID/PID, resolution/FPS/exposure;
- gimbal serial device, VID/PID, baudrate, zero, direction, limits, command tolerance and settle time;
- camera calibration identity/hash used by inspection evidence;
- real `/camera_gimbal/health` disconnect/reconnect behavior;
- real `AcquireView` timing and image/gimbal timestamp consistency.

Do not replace these values with guesses during remote development. Record them as evidence during bench/vehicle acceptance.
