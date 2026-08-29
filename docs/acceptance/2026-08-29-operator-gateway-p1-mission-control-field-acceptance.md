# Operator Gateway P1 Mission Control Field Acceptance

P1 adds guarded Mission lifecycle commands only. It does **not** give the HMI direct access to Nav2, `/cmd_vel`, chassis control, or safety ownership.

## A. ROS workspace gate

Run on Ubuntu 22.04 / ROS 2 Humble:

```bash
source /opt/ros/humble/setup.bash
colcon build --packages-select \
  agt_interfaces \
  agt_mission_manager \
  agt_system_manager \
  agt_operator_gateway \
  --symlink-install
source install/setup.bash
colcon test --packages-select agt_operator_gateway
colcon test-result --verbose
```

Acceptance:

- [ ] build exits 0;
- [ ] `agt_operator_gateway` has zero test failures;
- [ ] `action_msgs`, `agt_interfaces`, and `rclpy` dependencies resolve;
- [ ] no Gateway code imports Nav2/chassis command interfaces.

## B. Read-only default gate

Keep the shipped default:

```yaml
write_api_enabled: false
```

Start Gateway normally and run:

```bash
ros2 run agt_operator_gateway operator_gateway_preflight.py \
  --gateway http://127.0.0.1:8765 \
  --json-output runtime/acceptance/operator_gateway_p1_readonly_preflight.json
```

Acceptance:

- [ ] the four write probes return HTTP `403`;
- [ ] preflight reports `gateway_write_surface.state=disabled`;
- [ ] no Mission action/service request is emitted;
- [ ] all P0 read endpoints still pass.

The preflight sends unauthenticated `{}` POST probes only. Authentication/write gating occurs before request parsing and ROS dispatch, so this gate must not start, pause, resume, or cancel a Mission.

## C. Write-surface armed but non-dispatching gate

Before this step, replace wildcard CORS with the explicit HMI origin(s).

Enable the ROS parameter and set a secret in the Gateway process environment:

```bash
export AGT_OPERATOR_COMMAND_TOKEN='<robot-local-secret>'
ros2 launch agt_operator_gateway operator_gateway.launch.py \
  write_api_enabled:=true
```

If the launch file does not expose this argument yet, set `write_api_enabled: true` in the robot-specific parameter file instead; do not change the repository default.

Run the safe preflight **without supplying the token**:

```bash
ros2 run agt_operator_gateway operator_gateway_preflight.py \
  --gateway http://127.0.0.1:8765 \
  --expect-write-enabled \
  --json-output runtime/acceptance/operator_gateway_p1_armed_preflight.json
```

Acceptance:

- [ ] all four write probes return HTTP `401`;
- [ ] preflight reports `gateway_write_surface.state=enabled_auth_required`;
- [ ] the preflight has no CLI option for command credentials;
- [ ] no Mission state changes while this probe runs.

## D. Mission command static bench gate

Use a known non-motion test Mission or a bench Runtime configuration where actuator/navigation output is inhibited.

Use one unique `clientRequestId` per logical operator command. Verify in order:

1. `START` with the correct token and mission identity;
2. exact retry of the same `START` request;
3. `PAUSE`;
4. `RESUME`;
5. `CANCEL`.

Acceptance:

- [ ] first START is accepted once by `/agt/missions/execute`;
- [ ] exact retry returns the stored response and does not create a second goal;
- [ ] reusing the request ID with a different payload returns HTTP `409`;
- [ ] PAUSE/RESUME reach `/agt/missions/set_run_state` with the requested Mission ID;
- [ ] CANCEL is rejected if requested Mission ID does not match fresh authoritative RobotState;
- [ ] matching CANCEL is accepted by the Mission action cancel service;
- [ ] Gateway never publishes `/cmd_vel` and never calls Nav2 directly.

## E. Restart-safe cancel gate

Start a bench-safe Mission, then restart only `agt_operator_gateway` while leaving Mission Manager and Runtime running.

After Gateway reconnects to a fresh `/agt/system/robot_state`, issue CANCEL for the active Mission ID.

Acceptance:

- [ ] Gateway can cancel the active Mission after its own restart;
- [ ] cancellation does not depend on an in-memory pre-restart action goal handle;
- [ ] a mismatched Mission ID is rejected before cancel-all is sent;
- [ ] Mission Manager remains the single active-Mission owner.

## F. Fault gate

Repeat command attempts under these conditions:

- wrong/missing Bearer token;
- Runtime RobotState stale/offline;
- Mission action server unavailable;
- SetMissionRunState unavailable;
- command response timeout;
- transient LAN retry with the same `clientRequestId`.

Acceptance:

- [ ] wrong/missing token -> HTTP `401`, zero ROS dispatch;
- [ ] write API disabled/no effective secret -> HTTP `403`;
- [ ] stale Runtime -> HTTP `503` before cancel authority decisions;
- [ ] unavailable ROS command endpoint -> HTTP `503`;
- [ ] timeout -> HTTP `504`;
- [ ] duplicate in-flight request -> `IN_PROGRESS` without second dispatch;
- [ ] exact completed retry replays the stored result.

## G. Vehicle motion acceptance (later)

Only after A-F pass on the ROS 2 target should the same lifecycle be tested with a real navigation Mission on the vehicle.

Keep a physical E-stop available and begin at low speed in a clear test area.

Acceptance:

- [ ] START begins the intended Runtime-owned Mission only;
- [ ] PAUSE visibly stops Mission progression through the Runtime path;
- [ ] RESUME continues the same Mission;
- [ ] CANCEL terminates the active Mission and Runtime reaches the expected safe state;
- [ ] HMI disconnect/reconnect never creates a duplicate START;
- [ ] Gateway restart followed by CANCEL works as in section E.

## H. Evidence to keep

```text
runtime/acceptance/operator_gateway_p1_readonly_preflight.json
runtime/acceptance/operator_gateway_p1_armed_preflight.json
runtime/acceptance/operator_gateway_p1_command_log.txt
runtime/acceptance/operator_gateway_p1_restart_cancel.txt
colcon-test-result.txt
mission-manager-log.txt
hmi-command-state.png
```

Do not mark P1 vehicle acceptance complete until sections A-G are executed on the target ROS 2 environment. No-ROS CI proves contracts and Python behavior only; it does not prove DDS/action/service integration or vehicle safety.
