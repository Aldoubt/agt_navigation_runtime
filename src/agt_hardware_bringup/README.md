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

## Camera and gimbal hooks

The unified launch deliberately does not invent a camera/gimbal driver. A delivered ROS2 launch can be attached explicitly:

```bash
ros2 launch agt_hardware_bringup bunker_mid360.launch.py \
  operation_mode:=monitor \
  start_camera:=true camera_launch_file:=/absolute/path/to/camera.launch.py \
  start_gimbal:=true gimbal_launch_file:=/absolute/path/to/gimbal.launch.py
```

Runtime-facing interface targets for the future adapter are:

- `/agt/sensors/camera/image`
- `/agt/sensors/camera/camera_info`
- `/agt/gimbal/state`

These names are integration boundaries only; P0 does not claim the vendor driver currently publishes them.

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
- ROS2 `colcon build`/`colcon test` and DDS behavior.

Do not replace these with guessed values during remote development. Record them as evidence during bench/vehicle acceptance.
