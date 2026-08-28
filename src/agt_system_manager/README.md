# agt_system_manager

`agt_system_manager` is the authoritative read-model owner for operator clients and runtime task gates.
It aggregates existing Runtime evidence; it does **not** start algorithms, publish motion commands, load maps,
or provide a Web/Gateway transport.

## Published read models

```text
/agt/system/health          agt_interfaces/SystemHealth
/agt/system/task_readiness  agt_interfaces/TaskReadiness
/agt/system/robot_state     agt_interfaces/RobotState
```

All three publishers are reliable, transient-local snapshots. The default publication rate is 5 Hz.

Read services expose the same authoritative snapshots:

```text
/agt/system/health/get
/agt/system/task_readiness/evaluate
/agt/system/robot_state/get
```

## P0 task-readiness policy

Navigation task readiness is fail-closed. It becomes READY only when all of the following are true:

1. required sensor-health evidence is fresh and not in ERROR;
2. an active map has been received and is `active + valid + STATE_READY`;
3. localization status is fresh, accepted `TRACKING`, and bound to the active map identity;
4. the canonical `agt_safety/controller` status is fresh, motion is explicitly enabled, and no E-stop is latched;
5. chassis connectivity evidence is fresh and connected.

Unknown/stale required evidence produces stable blocker codes rather than being treated as healthy.
The pure policy lives in `agt_system_manager/readiness.py` so it can be regression-tested without ROS.

`EvaluateTaskReadiness` P0 implements `PROFILE_TASK_EXECUTION`. Other gate profiles are rejected with an
explicit blocker. `validate_task:=true` is also rejected in P0 because task-file/revision/hash validation remains
owned by the navigation task registry; the system manager must not create a second task-storage authority.

## Inputs

The P0 node consumes:

```text
/diagnostics
/agt/maps/active
/agt/localization/status
/agt/missions/status
/agt/safety/status
/agt/chassis/status
/agt/chassis/connected
/agt/data/bags/status
```

State-like inputs such as active map, mission and bag summary remain known after receipt and expose their age.
Heartbeat-like inputs used as safety gates (sensor health, localization, safety, chassis connectivity) must remain
within their configured freshness windows.

## Start

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_system_manager system_manager.launch.py
```

Inspect the read model:

```bash
ros2 topic echo /agt/system/robot_state
ros2 topic echo /agt/system/task_readiness
ros2 service call /agt/system/robot_state/get agt_interfaces/srv/GetRobotState "{include_details: true}"
```

The standalone P0 package is expected to report BLOCKED until upstream map/localization/safety/chassis evidence
is actually present. That startup state is intentional.

## Explicitly deferred

- Site Package activation and ownership of `/agt/maps/active`;
- unified BUNKER bringup;
- Nav2 lifecycle aggregation into `RobotState.nav2_state`;
- LIO/wheel/GNSS fusion;
- WebSocket/HTTP/operator gateway transport;
- operator command/write API.

The future operator gateway should translate this read model; it must not duplicate the readiness policy.
