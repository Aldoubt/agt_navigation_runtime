# V3-03 Navigation / Safety / Chassis Execution Acceptance

Date: 2026-08-16

## Status

**PASS**

V3-03 freezes the runtime execution chain and separates generic safety/chassis responsibilities from vehicle-specific backends.

## Frozen execution chain

```text
Nav2 Controller / Behavior
  -> /agt/navigation/cmd_vel_raw
  -> Collision Monitor
  -> /agt/navigation/cmd_vel
  -> agt_safety
  -> /agt/safety/cmd_vel
  -> agt_chassis command guard
  -> /agt/chassis/cmd_vel
  -> vehicle backend
```

No runtime vehicle backend may bypass `agt_safety` or the generic `agt_chassis` guard.

## Vehicle backend boundary

- `agt_chassis` is vehicle-agnostic.
- `agt_chassis_bunker` owns BUNKER-specific launch, status bridge, safety envelope, and BUNKER driver dependencies.
- `agt_chassis_mk_mini` owns MK-mini Ackermann command adaptation.
- MK-mini CAN transport/protocol is intentionally deferred to V3-04.

## Navigation policy boundary

`agt_navigation/launch/navigation.launch.py` requires `params_file` explicitly. It has no BUNKER or MK-mini default policy.

Vehicle-specific Nav2 policy is injected from the selected vehicle/bringup layer.

## Local ROS 2 Humble evidence

User-local acceptance on Ubuntu / ROS 2 Humble reported:

```text
agt_navigation: 14/14 tests passed
selected package test build: 6 packages finished
colcon test-result: 133 tests, 0 errors, 0 failures, 0 skipped
```

Launch argument resolution passed for:

```text
ros2 launch agt_navigation navigation.launch.py --show-args
ros2 launch agt_chassis_bunker bunker.launch.py --show-args
ros2 launch agt_chassis_mk_mini mk_mini_adapter.launch.py --show-args
```

The final navigation-policy cleanup was additionally protected by the V3-03 source contract and verified by GitHub Actions after removing the implicit `nav2_bunker.yaml` default.

## Acceptance result

V3-03 is accepted as the baseline for V3-04 MK-mini CAN backend integration.
