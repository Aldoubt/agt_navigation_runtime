# agt_hardware_bringup

`agt_hardware_bringup` is an orchestration-only package for first-vehicle BUNKER + MID360 checks. It composes existing Runtime owners and adds read-only evidence tools; it does not own navigation, motion commands, safety policy, or vendor drivers.

## First vehicle launch: monitor mode

Start with motion disabled at the orchestration layer:

```bash
ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  sensor_profile:=hardware_check \
  can_interface:=can0 \
  expected_can_bitrate:=0
```

`expected_can_bitrate:=0` means **do not assert a bitrate**. It is intentional for the remote-preparation phase and must not be interpreted as a real CAN bitrate. The preflight still checks that the interface exists, is a CAN link, is UP, and is not BUS-OFF when the kernel exposes that state.

After the real BUNKER bitrate is confirmed on the vehicle, pass it explicitly, for example `expected_can_bitrate:=<verified value>`.

## Sensor profiles

- `hardware_check`: raw MID360 CustomMsg + MID360 IMU are required. Filtered lidar and camera inputs are disabled so low-level hardware testing is not blocked by perception nodes that have not started yet.
- `navigation`: raw MID360 + filtered lidar + IMU are required. Camera and gimbal remain outside navigation readiness by default.

## Read-only preflight tools

SocketCAN evidence:

```bash
ros2 run agt_hardware_bringup socketcan_preflight.py \
  --interface can0 \
  --expected-bitrate 0 \
  --json-output can_preflight.json
```

Runtime topic evidence:

```bash
ros2 run agt_hardware_bringup vehicle_preflight.py \
  --json-output hardware_preflight.json
```

When the visual subsystem is available:

```bash
ros2 run agt_hardware_bringup vehicle_preflight.py \
  --require-camera \
  --require-gimbal \
  --json-output inspection_hardware_preflight.json
```

The preflight tools never configure SocketCAN, publish chassis commands, start missions, or command the gimbal.

## Inspection opt-in: frozen C1 camera + gimbal capability

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

This composes:

```text
autolabor_c1_bringup
  -> opencv_camera_node
  -> pantilt_camera_serial
  -> camera_gimbal_capability
       /camera_gimbal/acquire_view
       /camera_gimbal/health

agt_inspection
  view_backend=camera_gimbal
  -> /agt/inspection/execute_task
```

The real inspection backend is fail-closed at task admission: a new inspection goal is rejected until `/camera_gimbal/health` is fresh and READY with camera alive, gimbal serial connected, gimbal feedback alive, move action ready, and not busy.

`start_inspection:=true` must **not** be combined with the legacy `start_camera:=true` or `start_gimbal:=true` hooks; the launch rejects that combination to avoid double ownership of the same hardware.

For the first field deployment, use schema-v2 inspection tasks with `vision.execution_mode: "DEFERRED"`. The real C1 backend uses atomic `AcquireView` for motion + settle + post-settle image capture and stores the resulting image timestamp and measured gimbal angles into inspection evidence. Online flower inference is intentionally outside this frozen Runtime MVP.

## Legacy camera/gimbal hooks

The generic camera/gimbal hooks remain available for other hardware integrations, but are not the frozen C1 inspection path:

```bash
ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  start_camera:=true camera_launch_file:=/absolute/path/to/camera.launch.py \
  start_gimbal:=true gimbal_launch_file:=/absolute/path/to/gimbal.launch.py
```

Do not use these legacy hooks together with `start_inspection:=true`.

## Vehicle-only values: UNVERIFIED

The following remain **UNVERIFIED** until a ROS2 Humble machine and the physical robot are available:

- actual SocketCAN interface name;
- BUNKER CAN bitrate and bus error behavior under load;
- MID360 host NIC address and reachability of the configured lidar IP;
- real lidar/IMU rates and timestamp behavior;
- `base_link -> livox_frame` translation/orientation on the installed frame;
- BUNKER forward/angular sign and odometry sign;
- camera `/dev/video*`, VID/PID, resolution/FPS/exposure;
- gimbal serial device, VID/PID, baudrate, zero, direction, limits, command tolerance, and settle time;
- camera calibration identity/hash used by inspection evidence;
- ROS2 `colcon build`/`colcon test` and DDS behavior;
- real `/camera_gimbal/health` freshness and transition behavior under disconnect/reconnect;
- real `AcquireView` timing and image/gimbal timestamp consistency.

Do not replace these with guessed values during remote development. Record them as evidence during bench/vehicle acceptance.
