# P1-09A IPC Offline Acceptance

Acceptance record for the `feat/runtime-navigation-convergence-p1` branch.
This record covers software-only IPC acceptance with the offline simulator;
it does not claim hardware or field behavior.

## Evidence Identity

```text
Accepted runtime code state:
5106995521c73855b606d448befdbb8a6ff42f45

Platform:
Ubuntu 22.04
ROS 2 Humble

Local evidence root:
results/p1_09a_ipc_offline/
```

The acceptance evidence was generated against the runtime code state above.
The follow-up acceptance-document / `.gitignore` hygiene commit does not change
runtime behavior and therefore does not invalidate that evidence.

GitHub remote CI is not claimed as PASS for this code state unless a matching
workflow run is explicitly recorded. P1-09A acceptance is currently grounded
in the local Humble IPC evidence described here.

## Final Status

```text
[x] Gate A — Ubuntu 22.04 / ROS 2 Humble / selected-core build
[x] Gate B — selected-core regression
[x] Gate C — production direct-goal guard
[x] Gate D — Nav2 offline closed-loop
[x] Gate E — Collision Monitor synthetic obstacle
[x] Gate F — Site Runtime fail-closed
[~] Gate G — real Site Package validate/activate
    Deferred: no real deployed Site Package required for IPC offline acceptance

Final regression:
508 tests, 0 errors, 0 failures, 0 skipped

Overall:
P1-09A = PASS
```

## Gate D -> Gate E Interpretation

Gate E is interpreted together with the Gate D no-obstacle closed-loop
baseline; Gate E alone is not a mobility baseline.

The pair establishes the intended offline safety behavior:

```text
Gate D: no synthetic obstacle -> command pipeline can move the simulator
Gate E: synthetic obstacle    -> Collision Monitor / Safety stop the simulator
```

This prevents a permanently-zero downstream velocity pipeline from being
mistaken for successful obstacle stopping when the full P1-09A gate sequence is
used.

## Gate E Canonical Command

With the offline navigation launch already running, including the synthetic
obstacle at `x=0.7`, `y=0.0`, run:

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash

ros2 run agt_navigation p1_09a_collision_monitor_gate.py
```

The checker publishes a fixed `Twist` to
`/agt/navigation/cmd_vel_raw` at approximately 15 Hz for 2.5 seconds. It
observes the raw command, Collision Monitor output, Safety Controller output,
odometry, and obstacle cloud, then emits machine-readable `GATE_E_*` results
and measured values. It always sends a burst of zero commands during cleanup,
including exception paths.

The required PASS lines are:

```text
GATE_E_OBSTACLE_PRESENT=PASS
GATE_E_RAW_COMMAND=PASS
GATE_E_COLLISION_STOP=PASS
GATE_E_SAFETY_STOP=PASS
GATE_E_ODOM_STOP=PASS
GATE_E=PASS
```

## PASS Criteria

- The obstacle cloud contains at least one point.
- Observed raw `linear.x` reaches at least `0.15 m/s`.
- After the settle interval, Collision Monitor output has
  `abs(linear.x) <= 0.02 m/s` and `abs(angular.z) <= 0.02 rad/s`.
- After the settle interval, Safety Controller output has the same stop
  limits.
- Odometry planar displacement during the test is at most `0.05 m`.
- Any failed criterion or checker exception returns a non-zero exit code.

## Not Claimed

- BUNKER hardware acceptance
- MID360 / IMU field acceptance
- FAST-LIVO2 real sensor acceptance
- real localization / map->odom acceptance
- field braking-distance acceptance
- real Mission execution acceptance
