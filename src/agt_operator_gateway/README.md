# agt_operator_gateway

`agt_operator_gateway` is the read-only Web transport for operator clients. It translates the authoritative `/agt/system/robot_state` snapshot owned by `agt_system_manager`; it does not own readiness policy and does not expose write APIs in P0.

## API

- `GET /api/v1/health`
- `GET /api/v1/capabilities`
- `GET /api/v1/robot`
- `GET /api/v1/mission`
- `GET /api/v1/stream` (WebSocket)

Contract versions:

- API: `agt.operator.gateway/v1`
- stream: `agt.operator.stream/v1`

## Start with the real Runtime

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_system_manager system_manager.launch.py
ros2 launch agt_operator_gateway operator_gateway.launch.py
```

The gateway defaults to `0.0.0.0:8765`. Its only Runtime source is reliable/transient-local `/agt/system/robot_state`.

Before a fresh RobotState is available, `/robot`, `/mission` and `/stream` reject hydration. If RobotState stops updating, the gateway stops emitting stream envelopes so the HMI freshness logic can transition LIVE -> STALE -> OFFLINE instead of receiving fake heartbeats.

P0 deliberately has no mission, map, navigation, chassis or motion command endpoint.

## Hardware-free ROS acceptance

When a ROS 2 Humble workspace is available but the robot is not, start the deterministic RobotState fixture and the gateway together:

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_operator_gateway operator_gateway_mock.launch.py
```

Then run the same preflight used on the vehicle:

```bash
ros2 run agt_operator_gateway operator_gateway_preflight.py \
  --gateway http://127.0.0.1:8765 \
  --json-output /tmp/operator_gateway_preflight.json
```

Expected exit code is `0`. The report checks the authoritative RobotState topic type and one received sample, then validates health/capabilities/robot/mission against `agt.operator.gateway/v1`.

## Vehicle preflight

On the robot, start the normal Runtime and gateway first, then run:

```bash
ros2 run agt_operator_gateway operator_gateway_preflight.py \
  --gateway http://127.0.0.1:8765 \
  --robot-state-topic /agt/system/robot_state \
  --timeout-s 5 \
  --json-output runtime/acceptance/operator_gateway_preflight.json
```

For HTTP-only diagnosis when ROS CLI is unavailable:

```bash
ros2 run agt_operator_gateway operator_gateway_preflight.py \
  --skip-ros \
  --gateway http://127.0.0.1:8765
```

A successful report is necessary but not sufficient for vehicle acceptance: it proves the read-model and HMI transport chain, not navigation safety or motion behavior.

## No-ROS checks

The branch CI runs the pure projection/store/HTTP/static contracts without a ROS installation. Locally, with Python 3.10 and `aiohttp` installed:

```bash
PYTHONPATH=src/agt_operator_gateway \
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 \
python -m pytest -q \
  src/agt_operator_gateway/test/test_contract.py \
  src/agt_operator_gateway/test/test_state_store.py \
  src/agt_operator_gateway/test/test_server_contract.py \
  src/agt_operator_gateway/test/test_ros_contract.py \
  src/agt_operator_gateway/test/test_mock_gateway_contract.py \
  src/agt_operator_gateway/test/test_preflight.py

python -m compileall -q \
  src/agt_operator_gateway/agt_operator_gateway \
  src/agt_operator_gateway/scripts \
  src/agt_operator_gateway/launch
```

## ROS workspace verification deferred until a Humble environment is available

```bash
colcon build --packages-select agt_interfaces agt_system_manager agt_operator_gateway --symlink-install
source install/setup.bash
colcon test --packages-select agt_operator_gateway
colcon test-result --verbose
```

Do not mark P0 ROS acceptance complete until these commands and the mock or vehicle preflight have actually run in a ROS 2 Humble environment.
