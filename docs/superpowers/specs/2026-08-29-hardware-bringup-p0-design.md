# Hardware Bringup P0 Design

## Goal

Prepare the Runtime repository for first BUNKER + MID360 + future gimbal-camera vehicle tests without guessing hardware-dependent parameters. The remote phase must leave a single launch entry point, safe CAN preflight, sensor-monitor profiles, camera/gimbal adapter contracts, and an executable acceptance script. Real hardware remains authoritative for IP, device names, bitrate, TF orientation, gimbal limits, and motion validation.

## Scope

### In scope
- New `agt_hardware_bringup` package.
- One BUNKER + MID360 launch entry point with optional camera/gimbal hooks.
- SocketCAN preflight that checks interface existence/state and reports kernel CAN health when available.
- Separate `hardware_check` and `navigation` sensor-monitor profiles.
- Camera/gimbal adapter contract skeletons that do not claim a driver exists.
- Vehicle preflight script that checks ROS topics/diagnostics and never sends motion or mission commands.
- Static/no-ROS contract tests and CI wiring.

### Out of scope
- Choosing the real CAN bitrate without vehicle evidence.
- Bringing `can0` up automatically.
- Writing or vendoring the visual team's camera/gimbal drivers.
- Guessing `/dev/video*`, `/dev/ttyUSB*`, USB VID/PID, gimbal zero/limits, or settling time.
- Changing Nav2, localization, mission manager, BUNKER driver internals, or safety policy ownership.
- Automatically enabling motion.

## Architecture

```text
agt_hardware_bringup
├── socketcan_preflight.py
├── vehicle_preflight.py
├── config/
│   ├── sensor_monitor.hardware_check.yaml
│   └── sensor_monitor.navigation.yaml
└── launch/
    └── bunker_mid360.launch.py

bunker_mid360.launch.py
├── optional SocketCAN preflight
├── agt_chassis_bunker/bunker.launch.py
├── agt_sensor_adapters/mid360.launch.py
├── agt_sensor_monitor/sensor_monitor.launch.py
├── optional camera include (external launch path)
└── optional gimbal include (external launch path)
```

The new package composes existing owners. It must not duplicate BUNKER status policy, sensor stream health policy, or safety readiness policy.

## SocketCAN preflight

The preflight is read-only and fail-closed. It checks:
- `/sys/class/net/<iface>` exists.
- Interface operational state is `up` or `unknown` only when the kernel exposes a usable CAN link.
- `ip -details -statistics link show <iface>` succeeds.
- Link type contains `can`.
- If the operator supplied `expected_bitrate`, the observed bitrate must match exactly.
- Reject `BUS-OFF` when exposed in link details.
- Surface RX/TX error counters and restart count as evidence when available.

It must never run `ip link set`, set bitrate, restart the bus, or modify networking.

## Sensor monitor profiles

### `hardware_check`
Required:
- raw MID360 CustomMsg
- MID360 IMU

Disabled/non-required:
- filtered lidar
- camera
- camera_info
- GNSS

Purpose: prove essential physical sensors are online before perception/navigation is running.

### `navigation`
Required:
- raw MID360 CustomMsg
- filtered lidar
- MID360 IMU

Optional by default:
- camera
- camera_info
- GNSS

Purpose: preserve the current navigation safety expectation without causing false failure during low-level hardware checks.

Camera can later become required through a site/profile override for inspection missions; P0 does not hard-code that policy.

## Camera/gimbal integration boundary

P0 does not create fake drivers. It freezes adapter-facing names for future visual-team delivery:
- `/agt/sensors/camera/image`
- `/agt/sensors/camera/camera_info`
- `/agt/gimbal/state`

The unified bringup accepts optional external camera/gimbal launch file paths. Empty paths mean disabled. This lets the visual team's package be included later without changing Runtime orchestration.

The future gimbal adapter must translate the delivered feedback (`heading`, `roll`, `pitch`) into an AGT-owned state contract only after the actual ROS2 driver/message is available. P0 must not invent that message type.

## Unified launch behavior

`bunker_mid360.launch.py` exposes:
- `use_sim_time=false`
- `operation_mode=monitor|control`
- `can_interface=can0`
- `expected_can_bitrate=0` (`0` means do not assert bitrate)
- `run_can_preflight=true`
- `mid360_user_config_path=<existing default>`
- `sensor_profile=hardware_check|navigation`
- `start_camera=false`
- `camera_launch_file=`
- `start_gimbal=false`
- `gimbal_launch_file=`

For first vehicle tests, `operation_mode=monitor` is the recommended default. Control mode remains an explicit operator choice and the existing BUNKER launch/safety stack retains authority.

## Vehicle preflight

The executable preflight is observational only. It checks, when ROS2 is available:
- expected MID360 topics exist and produce at least one message;
- `/agt/chassis/status/raw` exists and produces data;
- `/agt/chassis/connected` is `true`;
- `/diagnostics` contains `agt_sensor_monitor/summary`;
- optional camera/gimbal topics when explicitly requested.

It writes a JSON evidence file and returns non-zero on required failures. It never publishes `/cmd_vel`, sends missions, or commands the gimbal.

## Testing strategy

Because the current development environment has no ROS2 installation, current acceptance consists of:
- pure Python tests for SocketCAN parsing/evaluation;
- static launch/config/package contract tests;
- static checks that the preflight contains no motion/mission publish paths;
- YAML/config semantic tests;
- `compileall` for Python/launch files;
- branch isolation check relative to `feat/operator-gateway-p1-mission-control`.

Deferred vehicle acceptance:
- ROS2 Humble `colcon build` and `colcon test`;
- actual `can0` state/bitrate/BUS-OFF evidence;
- MID360 IP and topic-rate verification;
- BUNKER status and low-speed direction tests;
- TF orientation validation in RViz;
- camera/gimbal USB/serial, angle direction, limits, and settling-time measurements.

## Safety invariants

1. Remote code must not infer unknown hardware values and mark them verified.
2. Preflight is read-only and cannot enable or move the chassis.
3. First vehicle launch defaults to BUNKER monitor mode.
4. Missing required evidence fails closed.
5. Camera/gimbal absence cannot be silently reported healthy.
6. Existing `agt_sensor_monitor`, `agt_safety`, and `agt_chassis_bunker` remain policy owners.
