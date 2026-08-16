# agt_chassis_mk_mini

MK-mini Ackermann adapter and fail-safe ROS 2 SocketCAN backend for AGT Navigation Runtime.

## Runtime boundary

```text
/agt/chassis/cmd_vel
        |
        v
agt_mk_mini_adapter
        |
        v
/agt/chassis/backend/ackermann_command
        |
        v
agt_mk_mini_can_backend
        |
        v
Linux SocketCAN can0
        |
        v
MK-mini VCU
```

The upstream execution boundary remains:

```text
Nav2 -> Collision Monitor -> agt_safety -> agt_chassis -> MK-mini backend
```

`agt_chassis_mk_mini` owns only vehicle-specific Ackermann conversion, MK-mini protocol encoding/decoding, SocketCAN transport, feedback and diagnostics. It does not publish localization TF and does not own site assets or navigation policy.

## Ackermann conversion

For nonzero longitudinal velocity:

```text
kappa = omega / v
delta = atan(L * kappa)
```

Curvature is limited by the vehicle-level minimum turning radius:

```text
|kappa| <= 1 / R_min
|delta| <= atan(L / R_min)
```

Frozen MK-mini reference geometry:

- wheelbase `L = 0.600 m`
- track width `0.517 m`
- wheel diameter `0.240 m`
- ground clearance `0.111 m`
- minimum turning radius `R_min = 1.500 m`
- equivalent navigation steering bound `atan(0.600 / 1.500) ~= 0.3805 rad ~= 21.8 deg`

The manufacturer VCU steering soft limit is `+/-34 deg`. It is **not** assumed to be the equivalent bicycle road-wheel angle and is not used to derive `R_min`.

Ackermann cannot execute an in-place rotation. A yaw-rate request with longitudinal speed inside the configured deadband produces a zero setpoint.

## MK-mini CAN protocol

The backend independently implements the MK-mini V1.1.0 manufacturer protocol:

- CAN 2.0B extended frame
- Intel/little-endian signal layout
- bitrate `500000 bit/s`
- `ctrl_cmd`: logical CAN ID `0x18C4D2D0`, 10 ms, 8 bytes
- `ctrl_fb`: logical CAN ID `0x18C4D2EF`, 10 ms, 8 bytes
- left rear wheel feedback: `0x18C4D7EF`
- right rear wheel feedback: `0x18C4D8EF`
- BMS information: `0x18C4E1EF`
- velocity resolution: `0.001 m/s/bit`
- steering resolution: signed `0.01 deg/bit`
- gear: `0=disable`, `1=P`, `2=R`, `3=N`, `4=D`
- AliveCounter: bits 52..55, cycles `0..15`
- BCC: `Byte0 XOR ... XOR Byte6 -> Byte7`

Linux `CAN_EFF_FLAG` is added only inside `socketcan_transport.py`. Protocol code and tests use the logical manufacturer IDs such as `0x18C4D2D0`, not `0x98C4D2D0`.

Manufacturer golden vectors are covered by tests, including:

```text
D, 0 m/s, counter=1:
04 00 00 00 00 00 10 14

D, 1.000 m/s, counter=0:
84 3E 00 00 00 00 00 BA

-25.00 deg steering, counter=0:
00 00 C0 63 0F 00 00 AC
```

## Supplied legacy driver and licensing

The supplied `MK-mini-ros2` archive and the historical `Aldoubt/agt_navigation_stack` YHS implementation were used as behavioral evidence for SocketCAN framing, feedback layout and legacy integration semantics.

The supplied archive does not contain a usable LICENSE/COPYING/NOTICE and its two package manifests contain `TODO: License declaration`. Therefore those packages are **not vendored or copied** into this public repository. V3-04 implements the manufacturer protocol independently under the AGT repository license and does not depend on `yhs_can_control` or `yhs_can_interfaces`.

## Operation modes

`mk_mini.launch.py` defaults to:

```text
operation_mode=monitor
steering_calibration_confirmed=false
allow_uncalibrated_control=false
```

### monitor

- opens SocketCAN
- receives and decodes VCU/wheel/BMS feedback
- publishes diagnostics and canonical feedback
- transmits **no** `ctrl_cmd`

This is the required first hardware test mode.

### control

- transmits `ctrl_cmd` at the protocol period, default `10 ms / 100 Hz`
- consumes `/agt/chassis/backend/ackermann_command`
- applies command freshness, feedback freshness, D/R shift interlock, VCU gear-feedback interlock, VCU mode gate and steering calibration gate

A moving command is blocked unless either:

```text
steering_calibration_confirmed=true
```

or, for raised-wheel bench testing only:

```text
allow_uncalibrated_control=true
```

## Fail-safe command behavior

The adapter preserves freshness semantics across the transport boundary. When upstream `/agt/chassis/cmd_vel` becomes stale, the adapter **stops publishing** instead of manufacturing a fresh zero Ackermann command.

The physical CAN backend continues the mandatory 100 Hz VCU heartbeat and owns the fail-safe sequence:

```text
fresh command lost
    -> zero velocity in current D/R gear
    -> keep steering while vehicle is still moving
    -> require fresh feedback proving standstill
    -> hold stationary for park_hold_sec
    -> command P and center steering
```

If vehicle feedback is stale, the backend does not blindly change gear based on an assumed standstill.

For startup and D/R direction changes:

```text
requested D/R
    -> fresh speed feedback must prove standstill
    -> stationary hold
    -> send new gear with zero velocity
    -> ctrl_fb must confirm the same VCU gear
    -> only then allow nonzero velocity
```

This prevents a nonzero command from being sent while the physical VCU is still in the previous gear.

## Steering calibration boundary

The adapter output is an equivalent bicycle-model steering angle. The backend converts it to the VCU steering request with an explicit affine mapping:

```text
vcu_deg = equivalent_deg * steering_scale + steering_offset_deg
```

and applies the VCU `+/-34 deg` soft limit.

Defaults are:

```text
steering_scale: 1.0
steering_offset_deg: 0.0
steering_calibration_confirmed: false
```

`1.0 / 0.0` is a compatibility starting point, **not a field calibration claim**. Ground autonomous operation should remain blocked until the steering mapping has been measured on the real chassis.

## Topics

Commands:

```text
/agt/chassis/cmd_vel                    geometry_msgs/Twist
/agt/chassis/backend/ackermann_command  agt_interfaces/AckermannCommand
```

Feedback:

```text
/agt/chassis/backend/ackermann_feedback  agt_interfaces/AckermannCommand
/agt/chassis/connected                   std_msgs/Bool
/agt/chassis/status                      diagnostic_msgs/DiagnosticArray
/agt/chassis/wheel_twist                 geometry_msgs/TwistWithCovarianceStamped
/battery                                 sensor_msgs/BatteryState
```

`/agt/chassis/wheel_twist` is an observation only. It does not publish TF and is not an authoritative odometry source in V3-04.

## Host CAN setup

The ROS launch intentionally does not run privileged network commands. Configure the host explicitly:

```bash
sudo ip link set can0 down 2>/dev/null || true
sudo ip link set can0 up type can bitrate 500000
ip -details link show can0
```

For raw inspection:

```bash
candump can0
```

## Safe bringup sequence

### 1. Build and test

```bash
colcon build --symlink-install --packages-select agt_interfaces agt_chassis_mk_mini
source install/setup.bash
colcon test --packages-select agt_chassis_mk_mini --event-handlers console_direct+
colcon test-result --verbose
```

### 2. Monitor only — wheels must not be commanded

```bash
ros2 launch agt_chassis_mk_mini mk_mini.launch.py \
  operation_mode:=monitor \
  start_adapter:=false
```

Check:

```bash
ros2 topic echo /agt/chassis/connected
ros2 topic echo /agt/chassis/status
ros2 topic echo /agt/chassis/backend/ackermann_feedback
ros2 topic echo /agt/chassis/wheel_twist
ros2 topic echo /battery
```

Confirm with `candump` that the VCU feedback is present and the AGT node is not transmitting `ctrl_cmd` in monitor mode.

### 3. Raised-wheel control test only

Before control testing:

- physically raise the drive wheels as recommended by the manufacturer
- keep the remote controller available for immediate takeover
- ensure the remote is in the intended autonomous/automatic mode when testing CAN control
- begin with zero-speed commands

Only for this bench phase:

```bash
ros2 launch agt_chassis_mk_mini mk_mini.launch.py \
  operation_mode:=control \
  allow_uncalibrated_control:=true
```

Do not use this override for normal ground autonomy.

### 4. Steering calibration

Measure the relation between VCU target steering and the real vehicle turning geometry. Fit or otherwise validate `steering_scale` and `steering_offset_deg`. If the measured relation is materially nonlinear, replace the affine model with a calibrated lookup/model rather than forcing an affine fit.

After calibration is validated, set:

```text
steering_calibration_confirmed=true
allow_uncalibrated_control=false
```

### 5. Ground low-speed acceptance

Only after monitor, raised-wheel control and steering calibration pass should the vehicle be placed on the ground for low-speed D/R, braking, steering and autonomous execution-chain validation.
