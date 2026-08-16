# V3-03 Navigation / Safety / Chassis Execution Implementation Plan

Date: 2026-08-16
Design: `docs/superpowers/specs/2026-08-16-v3-03-execution-chain-design.md`
Base: `v3-02/acceptance-freeze`
Work branch: `v3-03/execution-chain`

## Goal

Implement the frozen V3-03 command-execution boundary without changing Nav2 planning algorithms. Preserve BUNKER behavior, make safety/chassis generic, create a proper MK-mini Ackermann adapter, and leave physical MK-mini CAN transport for the next task.

## Task 1 — Freeze V3-03 source contracts

Create `tests/execution/test_v3_03_execution_contract.py` and extend `.github/workflows/runtime-contracts.yml` for `v3-03/**`.

RED assertions:

- `navigation.launch.py` must not reference `agt_bringup`
- Nav2 controller/behavior publish to `/agt/navigation/cmd_vel_raw`
- Collision Monitor maps raw -> filtered command
- safety maps filtered navigation command -> `/agt/safety/cmd_vel`
- chassis guard maps safety -> `/agt/chassis/cmd_vel`
- generic `agt_chassis/package.xml` must not depend on BUNKER
- `agt_safety` must not contain tracked kinematic projection
- `agt_chassis_bunker` and `agt_chassis_mk_mini` must exist

## Task 2 — Move localization lifecycle gate into agt_navigation

Tests first:

- migrate/adapt the existing V2.5 unit tests for localization readiness and lifecycle behavior
- verify fail-closed semantics

Implementation:

- add `src/agt_navigation/scripts/localization_navigation_gate.py`
- install it via CMake
- update `navigation.launch.py` to package `agt_navigation`
- keep lifecycle service/topic names unchanged

## Task 3 — Make agt_safety vehicle-independent

Tests first:

- generic clamp/slew behavior
- localization valid/invalid
- sensor ready/unready
- E-stop and motion-disabled immediate zero
- manual priority
- non-finite command rejection

Implementation:

- rename or replace `tracked_safety_controller.py` with `safety_controller.py`
- remove `project_track_speeds`
- remove `max_track_speed` and `effective_track_width`
- remove hard-coded BUNKER hardware identity
- preserve generic safety arbitration and fail-closed output
- add a generic `safety.launch.py`
- keep a BUNKER-compatible safety config under the backend package if needed

## Task 4 — Split generic chassis from BUNKER backend

Tests first:

- generic package manifest contains no `bunker_base` / `bunker_msgs`
- generic command guard keeps timeout and finite-value behavior
- BUNKER backend owns BUNKER dependencies and launch/status bridge

Implementation:

- keep `src/agt_chassis/scripts/chassis_command_guard.py`
- make `src/agt_chassis/package.xml` generic
- create `src/agt_chassis_bunker`
- move/copy BUNKER status bridge, config and launch into backend package
- backend subscribes only to `/agt/chassis/cmd_vel`
- preserve `bunker_base` remapping behavior

## Task 5 — Add protocol-independent AckermannCommand interface

RED:

- interface serialization/shape test expects `AckermannCommand`

Implementation:

- add `src/agt_interfaces/msg/AckermannCommand.msg`
- fields: `std_msgs/Header header`, `float64 speed_mps`, `float64 steering_angle_rad`
- register in `agt_interfaces/CMakeLists.txt`
- document units and semantics

## Task 6 — Implement MK-mini Ackermann adapter

Tests first in `src/agt_chassis_mk_mini/test/`:

- straight forward -> zero steering
- forward curvature -> `atan(L*w/v)`
- left/right sign
- excessive curvature -> clamp to `atan(L/Rmin)`
- reverse -> signed speed and consistent steering relation
- near-zero speed + yaw request -> zero command
- non-finite input -> zero/rejected
- stale input -> zero command

Implementation:

- create `src/agt_chassis_mk_mini`
- pure math module separate from ROS node
- ROS node subscribes `/agt/chassis/cmd_vel`
- publishes `/agt/chassis/backend/ackermann_command`
- defaults derived from frozen MK-mini profile: wheelbase 0.600 m, min turning radius 1.500 m
- do not use VCU 34 degree field as road-wheel angle
- no SocketCAN code and no YHS protocol messages in this milestone

## Task 7 — Documentation and historical provenance

Document:

- old `agt_navigation_stack` YHS packages as historical implementation evidence
- logical CAN IDs `0x18C4D2D0` / `0x18C4D2EF`
- old SocketCAN source IDs include the Linux extended-frame flag as `0x98...`
- old steering field resolution is 0.01 degree
- old wheel odometry uses `omega=v*tan(delta)/L`
- old Twist adapter shortcut is intentionally not reused

## Task 8 — Execution-chain ROS smoke

Add a smoke harness/launch that does not require physical chassis hardware.

Validate:

1. accepted localization + sensor-ready + motion-enabled + navigation command -> nonzero `/agt/chassis/cmd_vel`
2. navigation timeout -> zero
3. invalid localization -> zero
4. sensor unhealthy -> zero
5. E-stop -> immediate zero
6. motion disabled -> zero
7. manual command overrides navigation
8. non-finite input -> zero/rejected

The smoke stops at `/agt/chassis/cmd_vel`; backend-specific math can be tested independently.

## Task 9 — Final regression and local acceptance

Cloud:

```bash
python -m pytest -q tests/contracts
python -m pytest -q tests/odometry
python -m pytest -q tests/execution
```

Local ROS 2 Humble:

```bash
rm -rf build install log
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
colcon test --packages-select agt_interfaces agt_navigation agt_safety agt_chassis agt_chassis_bunker agt_chassis_mk_mini --event-handlers console_direct+
colcon test-result --verbose
```

Expected package count: 25.

Launch resolution:

```bash
ros2 launch agt_navigation navigation.launch.py --show-args
ros2 launch agt_chassis_bunker bunker.launch.py --show-args
ros2 launch agt_chassis_mk_mini mk_mini_adapter.launch.py --show-args
```

Acceptance requires zero test failures and no dependency on the V2.5 workspace overlay.
