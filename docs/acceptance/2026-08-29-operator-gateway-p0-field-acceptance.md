# Operator Gateway P0 Field Acceptance

This acceptance is intentionally read-only. Passing it proves the operator transport can observe the authoritative Runtime read model; it does **not** authorize or validate vehicle motion.

## A. ROS workspace gate

Run on Ubuntu 22.04 / ROS 2 Humble:

```bash
source /opt/ros/humble/setup.bash
colcon build --packages-select agt_interfaces agt_system_manager agt_operator_gateway --symlink-install
source install/setup.bash
colcon test --packages-select agt_operator_gateway
colcon test-result --verbose
```

Acceptance:

- [ ] build exits 0;
- [ ] gateway tests have zero failures;
- [ ] no new build warning indicates a missing Runtime interface or dependency.

## B. Hardware-free ROS gate

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_operator_gateway operator_gateway_mock.launch.py
```

In a second shell:

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 run agt_operator_gateway operator_gateway_preflight.py \
  --gateway http://127.0.0.1:8765 \
  --json-output /tmp/operator_gateway_mock_preflight.json
```

Acceptance:

- [ ] `/agt/system/robot_state` type is `agt_interfaces/msg/RobotState`;
- [ ] one RobotState sample is received;
- [ ] `/api/v1/health` reports `runtime.connected=true`;
- [ ] capabilities/robot/mission all use `agt.operator.gateway/v1`;
- [ ] preflight exits 0.

## C. Vehicle static gate

Start the real Runtime without dispatching a navigation mission, then start:

```bash
ros2 launch agt_operator_gateway operator_gateway.launch.py
```

Run:

```bash
ros2 run agt_operator_gateway operator_gateway_preflight.py \
  --gateway http://127.0.0.1:8765 \
  --robot-state-topic /agt/system/robot_state \
  --timeout-s 5 \
  --json-output runtime/acceptance/operator_gateway_preflight.json
```

Acceptance:

- [ ] RobotState comes from the real `agt_system_manager`;
- [ ] active map identity shown by Gateway matches Runtime;
- [ ] localization state shown by Gateway matches Runtime;
- [ ] readiness blocker/warning state is not upgraded or hidden by Gateway;
- [ ] robot pose in `/api/v1/robot` is consistent with the accepted localization pose;
- [ ] preflight exits 0.

## D. LAN/HMI gate

From a second computer on the robot LAN:

```bash
curl -fsS http://<robot-ip>:8765/api/v1/health
curl -fsS http://<robot-ip>:8765/api/v1/robot
```

Connect `agt_operator_hmi` to `http://<robot-ip>:8765`.

Acceptance:

- [ ] HMI becomes LIVE only after the stream opens;
- [ ] displayed robot identity/map/localization/mission match the REST payloads;
- [ ] HMI does not need direct DDS/ROS access;
- [ ] no browser action can publish `/cmd_vel` or invoke Nav2 through P0 Gateway.

## E. Freshness/failure gate

With HMI connected, stop the RobotState source while leaving Gateway running.

Acceptance:

- [ ] Gateway stops sending new telemetry instead of inventing heartbeat state;
- [ ] HMI leaves LIVE and reaches STALE after its freshness threshold;
- [ ] HMI reaches OFFLINE after its offline threshold / stream closure;
- [ ] restarting the Runtime source can restore the read path after reconnect;
- [ ] no motion command is produced during any disconnect/reconnect step.

## F. Evidence to keep

Archive together:

```text
runtime/acceptance/operator_gateway_preflight.json
colcon-test-result.txt
hmi-live.png
hmi-stale.png
hmi-offline.png
runtime-topic-snapshot.txt
```

Do not mark P0 vehicle acceptance complete until sections A-E have been executed on the target ROS 2 environment. The current no-ROS CI is only a pre-integration gate.
