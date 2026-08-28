# Runtime Convergence P0 — Waypoint Action Stability Follow-up

Date: 2026-08-28
Branch: `feat/runtime-convergence-p0`

## Context

A local ROS 2 Humble package rerun previously observed one failure in:

```text
agt_navigation/test_waypoint_task_server
  test_project_action_uses_follow_waypoints_result[missed0-True]
```

The failure occurred at:

```python
client.wait_for_server(timeout_sec=2.0)
```

The same `colcon test-result` summary reported two failure records because the same pytest case was represented once by the CTest wrapper result and once by the pytest xUnit result. This was one independent failing case, not two separate Runtime failures.

## Investigation result

The production `WaypointTaskServer` constructs `/agt/navigation/execute_waypoint_task` synchronously during node initialization. The failure could not be reproduced when the exact case was isolated.

Observed local evidence:

```text
Exact failed pytest case:
  5 repeated quiet runs: 5/5 PASS
  1 DEBUG run:           PASS

Complete test_waypoint_task_server.py:
  10 repeated runs
  13 tests each run
  result: 10/10 PASS

CTest target:
  ctest -R '^test_waypoint_task_server$' --repeat until-fail:20
  result: 20/20 PASS
```

Typical timings:

```text
isolated pytest case: ~0.32-0.36 s
complete pytest file: ~0.56-0.84 s
CTest target:         ~1.35-1.96 s
```

## Classification

Current classification:

```text
LOW-FREQUENCY ROS/DDS TEST FLAKE — NOT REPRODUCED
```

There is no current evidence that the production ActionServer fails to initialize or that the Runtime navigation behavior is defective.

No timeout change, ROS_DOMAIN_ID change, production ActionServer change, or navigation behavior change is justified by the available evidence. In particular, this follow-up intentionally does **not** change the test discovery timeout from 2 s to 5 s merely to mask a non-reproducible symptom.

## Remaining P0 local gates

The waypoint action target is considered stable enough to proceed to the final P0 local gates:

1. rerun the complete selected package gate:

```bash
colcon test \
  --packages-select agt_system_manager agt_navigation agt_safety \
  --event-handlers console_direct+
colcon test-result --verbose
```

Expected result: zero errors and zero failures.

2. perform the no-motion system-manager smoke:

```bash
ros2 launch agt_system_manager system_manager.launch.py
```

Then from another terminal:

```bash
source ~/agt_navigation_runtime/install/setup.bash
ros2 topic echo /agt/system/robot_state --once
ros2 topic echo /agt/system/task_readiness --once
ros2 service call /agt/system/robot_state/get \
  agt_interfaces/srv/GetRobotState \
  "{include_details: true}"
```

With no upstream map/localization/safety/chassis evidence started, the authoritative read model must remain fail-closed and report BLOCKED/unknown evidence. It must not claim READY.
