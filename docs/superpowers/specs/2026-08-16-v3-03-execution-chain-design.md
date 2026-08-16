# V3-03 Navigation / Safety / Chassis Execution Design

Date: 2026-08-16
Status: Approved
Base milestone: V3-02 Acceptance PASS

## 1. Goal

V3-03 freezes and validates the only legal robot motion command chain in `agt_navigation_runtime`, removes the remaining V2.5 bringup dependency, separates vehicle-independent safety/chassis responsibilities from vehicle-specific backends, preserves the BUNKER runtime backend, and prepares a correct MK-mini Ackermann adapter before the physical CAN transport is integrated.

This milestone does not retune Nav2 planning/controller algorithms and does not claim MK-mini CAN hardware control is complete.

## 2. Canonical execution chain

```text
Route / Planner
      -> Nav2 Controller / Behavior
      -> /agt/navigation/cmd_vel_raw
      -> Nav2 Collision Monitor
      -> /agt/navigation/cmd_vel
      -> agt_safety
      -> /agt/safety/cmd_vel
      -> agt_chassis command guard
      -> /agt/chassis/cmd_vel
      -> vehicle backend adapter
      -> vehicle driver / CAN transport
```

Manual commands enter only through `/agt/cmd_vel_manual -> agt_safety`.

No runtime component may bypass `agt_safety` and publish a motion command directly to `/agt/chassis/cmd_vel` or a backend hardware command topic.

## 3. Navigation ownership

`agt_navigation` owns the Nav2 runtime execution chain and the localization lifecycle gate.

The inherited `navigation.launch.py` reference to `agt_bringup/localization_navigation_gate.py` is invalid in V3 because `agt_bringup` is not part of the runtime repository. The existing fail-closed gate behavior is migrated into `agt_navigation` without changing its lifecycle semantics:

- subscribe `/agt/localization/status`
- operate `/lifecycle_manager_navigation/manage_nodes`
- STARTUP after accepted fresh localization
- PAUSE when localization becomes invalid after the configured grace period
- RESUME after recovery
- RESET after a rejected startup when required

## 4. Vehicle-independent safety

`agt_safety` becomes kinematics-agnostic.

It owns:

- physical and latched E-stop handling
- explicit motion enable/disable
- manual/navigation arbitration
- input freshness timeouts
- localization readiness gate
- sensor-health readiness gate
- finite-value validation
- generic linear/angular envelope limits
- acceleration/deceleration slew limiting
- fail-closed zero output

It does not own:

- tracked left/right velocity projection
- Ackermann steering conversion
- vehicle CAN protocol
- vehicle-specific hardware identity

The existing BUNKER-specific `project_track_speeds`, `max_track_speed`, `effective_track_width`, and hard-coded `hardware_id=bunker` leave the generic safety controller.

## 5. Generic chassis core

`agt_chassis` remains the backend-independent final Twist guard.

Contract:

- input: `/agt/safety/cmd_vel`
- output: `/agt/chassis/cmd_vel`
- reject non-finite commands
- command timeout produces zero
- enforce final generic hard linear/angular bounds

`agt_chassis/package.xml` must not depend on `bunker_base` or `bunker_msgs`.

## 6. BUNKER backend

Create `agt_chassis_bunker` and move BUNKER-specific runtime ownership into it:

- BUNKER launch
- BUNKER status bridge
- `bunker_base` and `bunker_msgs` dependencies
- BUNKER backend configuration

The backend consumes `/agt/chassis/cmd_vel`. Existing BUNKER behavior remains the compatibility baseline.

## 7. MK-mini adapter before CAN integration

Create `agt_chassis_mk_mini` as an Ackermann kinematic adapter without SocketCAN/VCU transport.

The adapter consumes the canonical backend input:

```text
/agt/chassis/cmd_vel     geometry_msgs/Twist
```

and publishes a protocol-independent Ackermann setpoint:

```text
/agt/chassis/backend/ackermann_command    agt_interfaces/AckermannCommand
```

`AckermannCommand` contains signed longitudinal speed and equivalent bicycle-model steering angle in radians. The later MK-mini CAN driver will translate this setpoint into VCU gear, velocity and steering protocol fields.

### 7.1 Twist to Ackermann conversion

For a valid nonzero longitudinal velocity:

```text
delta = atan(L * omega / v)
```

where:

- `v` is signed longitudinal speed
- `omega` is desired yaw rate
- `L` is wheelbase
- `delta` is equivalent bicycle-model steering angle

Ackermann cannot execute an in-place turn. When `abs(v)` is below the configured deadband, output speed and steering are both zero even if `omega != 0`.

The navigation curvature limit is derived from the verified manufacturer minimum turning radius rather than assuming the VCU 34 degree soft limit is an equivalent road-wheel angle:

```text
|kappa| <= 1 / R_min
|delta| <= atan(L / R_min)
```

For the frozen MK-mini profile, `L=0.600 m` and `R_min=1.500 m`, so the equivalent navigation steering bound is about 0.381 rad (21.8 deg).

Reverse motion uses the same bicycle equation with signed `v`; the steering sign therefore changes naturally for the requested yaw-rate sign.

The adapter also has its own freshness timeout and publishes a zero setpoint when input becomes stale. This is defense in depth after the generic chassis guard.

### 7.2 Historical evidence and deliberate correction

The legacy `Aldoubt/agt_navigation_stack` contains:

- `agt_chassis_base/yhs_can_control`
- `yhs_can_interfaces`
- `twist_to_yhs_cmd_node.cpp`
- `yhs_can_control_node.cpp`
- `agt_chassis_bridge`

The old CAN layer proves the protocol command/feedback fields use 0.001 m/s velocity resolution and 0.01 degree steering resolution. Feedback steering was converted to radians and used in `omega = v * tan(delta) / L` for wheel odometry. The old Twist adapter, however, assigned `angular.z * steering_gain` directly to the steering field. V3 does not preserve that shortcut; it uses the Ackermann bicycle conversion above.

The old SocketCAN source uses IDs with the Linux extended-frame flag embedded (`0x98C4D2D0`, `0x98C4D2EF`), consistent with the logical VCU IDs frozen in the Vehicle Profile (`0x18C4D2D0`, `0x18C4D2EF`).

## 8. Interfaces

Add:

```text
agt_interfaces/msg/AckermannCommand.msg
```

Required fields:

```text
std_msgs/Header header
float64 speed_mps
float64 steering_angle_rad
```

The message deliberately excludes CAN gear, byte packing, counter and checksum fields. Those belong to the future MK-mini transport implementation.

## 9. Package topology after V3-03

```text
agt_navigation
  -> agt_safety
  -> agt_chassis
       -> agt_chassis_bunker
       -> agt_chassis_mk_mini
```

Expected workspace package count after adding both backend packages: 25, assuming no other package is added or removed.

## 10. Tests

### Source contracts

Assert:

- controller/behavior output only to `/agt/navigation/cmd_vel_raw`
- Collision Monitor owns `/agt/navigation/cmd_vel_raw -> /agt/navigation/cmd_vel`
- safety owns `/agt/navigation/cmd_vel -> /agt/safety/cmd_vel`
- chassis guard owns `/agt/safety/cmd_vel -> /agt/chassis/cmd_vel`
- no `agt_bringup` reference remains in runtime navigation launch
- generic `agt_chassis` has no BUNKER dependencies
- generic safety contains no tracked kinematics helper/parameters

### Pure math tests

MK-mini adapter must test:

- straight forward
- forward left/right curvature
- excessive curvature clamps to `R_min`
- reverse curvature sign behavior
- zero-speed yaw request produces zero setpoint
- non-finite input rejected/fails closed
- timeout output is zero

### ROS smoke

Execution-chain smoke verifies:

- valid navigation command reaches `/agt/chassis/cmd_vel`
- navigation timeout -> zero
- localization invalid -> zero
- sensor unhealthy -> zero
- E-stop -> immediate zero
- motion disabled -> zero
- manual command has priority
- non-finite command is rejected

## 11. Acceptance

V3-03 passes only when:

- V3-01 and V3-02 regressions remain green
- V3-03 source contracts pass
- generic safety tests pass
- MK-mini Ackermann adapter math tests pass
- BUNKER backend package resolves
- navigation launch no longer depends on `agt_bringup`
- full ROS 2 Humble workspace builds independently
- expected package count is 25
- relevant package tests report zero failures
- navigation, BUNKER backend and MK-mini adapter launch files resolve with `--show-args`

Physical MK-mini CAN send/receive is explicitly deferred to the next CAN-driver integration task.
