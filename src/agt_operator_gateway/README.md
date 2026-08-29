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

## Start

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_operator_gateway operator_gateway.launch.py
```

Defaults to `0.0.0.0:8765`. The runtime source is reliable/transient-local `/agt/system/robot_state`.

Before a fresh RobotState is available, `/robot`, `/mission` and `/stream` reject hydration. If RobotState stops updating, the gateway stops emitting stream envelopes so the HMI freshness logic can transition LIVE -> STALE -> OFFLINE instead of receiving fake heartbeats.

P0 deliberately has no mission, map, navigation, chassis or motion command endpoint.

## Local checks

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q \
  src/agt_operator_gateway/test/test_contract.py \
  src/agt_operator_gateway/test/test_state_store.py \
  src/agt_operator_gateway/test/test_server_contract.py \
  src/agt_operator_gateway/test/test_ros_contract.py
```

ROS workspace verification:

```bash
colcon build --packages-select agt_interfaces agt_system_manager agt_operator_gateway --symlink-install
source install/setup.bash
colcon test --packages-select agt_operator_gateway
colcon test-result --verbose
```
