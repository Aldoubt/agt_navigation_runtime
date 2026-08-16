# agt_chassis_mk_mini

Protocol-independent Ackermann adapter for the MK-mini drive-by-wire chassis.

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
future MK-mini CAN transport
```

This package does **not** open SocketCAN and does not pack YHS VCU frames. Its only job in V3-03 is to translate the canonical runtime `geometry_msgs/Twist` command into a signed longitudinal speed plus equivalent bicycle-model steering angle.

## Kinematic conversion

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

With the frozen MK-mini profile:

- wheelbase `L = 0.600 m`
- track width `0.517 m`
- wheel diameter `0.240 m`
- ground clearance `0.111 m`
- minimum turning radius `R_min = 1.500 m`
- equivalent navigation steering bound `atan(0.600 / 1.500) ~= 0.3805 rad ~= 21.8 deg`

The manufacturer/VCU `34 deg` steering value is retained in `profiles/platforms/mk_mini.yaml` as `vcu_target_steering_soft_limit`. It is **not** assumed to be the equivalent bicycle road-wheel angle and is therefore not used to derive `R_min`.

Ackermann cannot execute an in-place rotation. A yaw-rate request with longitudinal speed inside the configured deadband produces a zero setpoint.

## Historical implementation evidence

The legacy repository `Aldoubt/agt_navigation_stack` contains the earlier YHS implementation under:

```text
agt_ws/src/agt_chassis_base/yhs_can_control
agt_ws/src/agt_chassis_base/yhs_can_interfaces
```

Useful evidence retained from that implementation:

- command logical CAN ID: `0x18C4D2D0`
- feedback logical CAN ID: `0x18C4D2EF`
- velocity field resolution: `0.001 m/s`
- steering field resolution: `0.01 deg`
- wheel odometry used `omega = v * tan(delta) / L`
- the old SocketCAN code included the Linux extended-frame flag in IDs, appearing as `0x98C4D2D0` / `0x98C4D2EF`

The old `twist_to_yhs_cmd_node.cpp` directly mapped `angular.z * steering_gain` into the steering field. V3 deliberately does not copy that shortcut; the adapter now uses the bicycle-model conversion above.

## Default topics

```text
input:  /agt/chassis/cmd_vel                    geometry_msgs/Twist
output: /agt/chassis/backend/ackermann_command  agt_interfaces/AckermannCommand
```

## Deferred work

The next MK-mini task is the physical CAN transport/backend:

```text
AckermannCommand
  -> gear selection
  -> m/s to VCU velocity field
  -> equivalent steering setpoint to verified VCU steering command mapping
  -> counter/checksum
  -> CAN 2.0B extended frame send/receive
  -> feedback/status/odometry validation
```

That integration must use the actual MK-mini CAN driver and on-vehicle steering calibration rather than adding protocol assumptions to this adapter.
