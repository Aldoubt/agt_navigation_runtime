# V3-04 MK-mini CAN Backend Design

## Goal

Connect the V3-03 protocol-independent `agt_interfaces/AckermannCommand` boundary to the physical MK-mini VCU over Linux SocketCAN without changing the upstream Navigation -> Safety -> Chassis execution contract.

```text
/agt/chassis/cmd_vel
  -> agt_chassis_mk_mini/mk_mini_adapter
  -> /agt/chassis/backend/ackermann_command
  -> agt_chassis_mk_mini/mk_mini_can_backend
  -> SocketCAN can0
  -> MK-mini VCU
```

Feedback returns through the same backend and is exposed as canonical AGT status, battery, Ackermann feedback, and wheel-velocity observations. The CAN backend must never publish `map -> odom`, `odom -> base_*`, or an authoritative localization pose.

## Source and licensing decision

The user supplied the vendor/legacy ROS2 archive `MK-mini-ros2(1).zip` containing `yhs_can_control` and `yhs_can_interfaces`. It is useful implementation evidence, but both package manifests contain `TODO: License declaration` and the archive contains no LICENSE/COPYING/NOTICE file.

Therefore V3-04 does **not** vendor or copy the supplied source into the public Apache-2.0 AGT repository. The supplied code is treated only as behavioral evidence for:

- Linux SocketCAN extended-frame handling,
- command/feedback field packing,
- wheel/BMS feedback field interpretation,
- topic-level expectations.

The protocol implementation in AGT is written independently from the MK-mini V1.1.0 manufacturer manual and carries the repository license.

## Authoritative protocol facts

Manufacturer manual V1.1.0 freezes these facts for V3-04:

- CAN 2.0B extended frame, Intel/little-endian signal layout.
- Bus bitrate: 500 kbit/s.
- `ctrl_cmd` logical ID: `0x18C4D2D0`, period: 10 ms, DLC: 8.
- `ctrl_fb` logical ID: `0x18C4D2EF`, period: 10 ms, DLC: 8.
- left rear wheel feedback: `0x18C4D7EF`, period: 10 ms.
- right rear wheel feedback: `0x18C4D8EF`, period: 10 ms.
- odometer feedback: `0x18C4DEEF`.
- BMS information: `0x18C4E1EF`.
- BMS flags: `0x18C4E2EF`.
- velocity resolution: `0.001 m/s/bit` and the command field is unsigned; direction is selected by gear.
- steering resolution: signed `0.01 deg/bit`.
- target gear nibble: `0=disable`, `1=P`, `2=R`, `3=N`, `4=D`.
- AliveCounter occupies bits 52..55 and cycles `0..15`.
- BCC checksum is `Byte0 XOR ... XOR Byte6` and is written to Byte7.
- VCU steering soft limit is `[-34 deg, +34 deg]`.

Linux SocketCAN represents the extended-frame flag separately from the 29-bit logical ID. The legacy driver therefore appears to use `0x98C4D2D0`; V3 keeps the logical protocol ID `0x18C4D2D0` and adds `CAN_EFF_FLAG` only in the transport boundary.

## Package ownership

V3-04 keeps all MK-mini-specific code in the existing vehicle backend package:

```text
agt_chassis_mk_mini/
├── agt_chassis_mk_mini/
│   ├── ackermann_math.py          # existing Twist -> bicycle-model setpoint
│   ├── mk_mini_protocol.py        # pure codec, no ROS/socket
│   ├── mk_mini_command_state.py   # pure fail-safe/gear state machine
│   └── socketcan_transport.py     # Linux SocketCAN only
├── scripts/
│   ├── mk_mini_adapter.py         # existing generic Twist adapter
│   └── mk_mini_can_backend.py     # ROS2 physical backend
├── config/mk_mini.yaml
└── launch/mk_mini.launch.py
```

No `yhs_can_interfaces` package is introduced. `agt_interfaces/AckermannCommand` remains the only command contract between AGT and the vehicle-specific transport.

## Command model

`AckermannCommand.speed_mps` is signed. The CAN command field is unsigned, therefore the backend maps:

```text
speed > deadband  -> D, velocity = abs(speed)
speed < -deadband -> R, velocity = abs(speed)
```

Direction changes are interlocked. A D<->R transition is not issued while the latest valid vehicle-speed feedback is above the configured gear-shift threshold. Until the chassis is observed stationary the backend transmits zero velocity in the current motion gear.

A fresh zero-speed command retains the current motion gear; on startup with no motion gear the backend remains P.

## Command freshness and safe stop

The CAN frame is transmitted at the protocol period (default 10 ms / 100 Hz) independently of the ROS input publication rate.

If the `AckermannCommand` becomes stale:

1. request zero velocity while retaining the current D/R gear and steering setpoint to avoid an abrupt steering jump while moving;
2. when valid feedback reports speed below the park threshold for the configured hold time, command zero steering and P;
3. if vehicle feedback is missing/stale, do not perform an automatic D/R/P gear transition that assumes the vehicle is stationary; continue the zero-velocity request in the last known motion gear (or P if no motion gear was ever selected).

This is deliberately more conservative than blindly switching to P on a ROS timeout.

## Steering calibration boundary

The adapter publishes an **equivalent bicycle-model steering angle**. The VCU consumes a manufacturer-defined steering target in degrees. V3 does not assume the two are physically identical.

The CAN backend therefore owns an explicit invertible affine mapping:

```text
vcu_deg = equivalent_deg * steering_scale + steering_offset_deg
```

and clamps only at the VCU soft limit. The default `steering_scale=1.0`, `steering_offset_deg=0.0` is a conservative compatibility setting matching the legacy driver semantics, not a field calibration claim. With the existing adapter's `R_min=1.5 m` clamp, the uncalibrated default never requests the full +/-34 deg VCU range.

Runtime configuration includes `steering_calibration_confirmed`. `operation_mode=control` must refuse to transmit moving commands unless this flag is explicitly true or `allow_uncalibrated_control` is explicitly enabled for raised-wheel bench testing.

## Operation modes

`operation_mode` mirrors the BUNKER backend:

- `monitor` (default): open CAN, decode and publish feedback, transmit no control frame.
- `control`: enable periodic `ctrl_cmd` transmission subject to command freshness, calibration gate and fail-safe state machine.

No launch file configures `can0` with privileged shell commands. Host setup remains explicit:

```bash
sudo ip link set can0 up type can bitrate 500000
```

## Feedback contract

The backend publishes:

```text
/agt/chassis/backend/ackermann_feedback  agt_interfaces/AckermannCommand
/agt/chassis/connected                   std_msgs/Bool
/agt/chassis/status                      diagnostic_msgs/DiagnosticArray
/agt/chassis/wheel_twist                 geometry_msgs/TwistWithCovarianceStamped
/battery                                 sensor_msgs/BatteryState
```

`ackermann_feedback` uses the inverse configured steering mapping and a signed longitudinal speed reconstructed from gear.

`wheel_twist` is a chassis velocity observation only. It must not publish TF. Linear velocity is formed from the rear-wheel feedback when fresh; yaw rate is derived using the equivalent steering feedback and the frozen wheelbase. This observation can be evaluated for a future localization-fusion input without becoming authoritative in V3-04.

## Protocol tests / golden vectors

The pure codec must reproduce manufacturer examples exactly, including:

```text
D gear, zero velocity, zero steering, counter=1:
04 00 00 00 00 00 10 14

D gear, 1.000 m/s, zero steering, counter=0:
84 3E 00 00 00 00 00 BA

zero gear/speed, -25.00 deg steering, counter=0:
00 00 C0 63 0F 00 00 AC
```

Tests must also cover BCC rejection, signed steering decode, wheel speed/pulse decode, AliveCounter wrap and direction-change/state-timeout behavior.

## V3-04 acceptance boundary

V3-04 is accepted when:

- V3-01/V3-02/V3-03 source contracts remain green.
- MK-mini codec golden vectors pass.
- the backend contains no dependency on `yhs_can_control` or `yhs_can_interfaces`.
- `operation_mode=monitor` is the default.
- control frames are periodic at the configured 10 ms protocol period.
- stale command behavior is fail-safe and tested.
- D/R direction changes are interlocked on observed standstill.
- checksum and feedback freshness diagnostics are exposed.
- `colcon build` and `colcon test --packages-select agt_chassis_mk_mini` pass on ROS2 Humble.
- launch argument parsing succeeds without a physical CAN device.
- a later raised-wheel/vcan/physical-CAN smoke test is performed before autonomous field motion.
