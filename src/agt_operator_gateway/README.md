# agt_operator_gateway

`agt_operator_gateway` 是 AGT Operator HMI 与 ROS 2 Runtime 之间的唯一 Web 边界。它把 `agt_system_manager` 发布的权威 `/agt/system/robot_state` 投影为稳定的 HTTP/WebSocket 合同，同时提供受保护的任务生命周期命令。

当前配套分支：

```text
feat/operator-gateway-control-lease
```

## 架构边界

```text
HMI / Browser
      |
      | HTTP + WebSocket
      v
agt_operator_gateway
      |
      | authoritative RobotState + mission command adapters
      v
ROS 2 Runtime
```

Gateway 不拥有：

- readiness 决策策略；
- Nav2 内部状态机；
- 相机/PTZ 业务逻辑；
- 浏览器 UI 状态。

Runtime 是机器人与任务真值来源。

## Read API

```text
GET /api/v1/health
GET /api/v1/capabilities
GET /api/v1/robot
GET /api/v1/mission
GET /api/v1/stream      WebSocket
GET /api/v1/control     current Control Lease status
```

Contract versions:

```text
API:    agt.operator.gateway/v1
Stream: agt.operator.stream/v1
```

在新的 RobotState 到来前，`/robot`、`/mission`、`/stream` 不会伪造可用状态。RobotState 过期后 Gateway 停止提供新的有效 Runtime 状态，使 HMI 能正确进入 `STALE/OFFLINE`。

## Mission Write API

当且仅当同时满足：

1. ROS 参数 `write_api_enabled: true`；
2. 环境变量 `AGT_OPERATOR_COMMAND_TOKEN` 非空；

Gateway 才进入 read-write 模式。

任务命令：

```text
POST /api/v1/mission/start
POST /api/v1/mission/pause
POST /api/v1/mission/resume
POST /api/v1/mission/cancel
```

写请求必须通过 Bearer token 校验。

### Idempotency

每个任务命令带：

```text
clientRequestId
```

Gateway 使用有界 `CommandReplayStore`：

- 相同 request ID + 相同 payload：不重复执行；
- 已完成请求可返回缓存结果；
- 正在执行请求返回 `IN_PROGRESS`；
- 相同 ID + 不同 payload 返回冲突；
- 不会为了腾空间驱逐 in-flight 请求。

因此 HMI 在网络不确定时不需要通过重复创建任务来“赌一次成功”。

## Control Lease

P6 新增单控制端 Lease。

API：

```text
POST /api/v1/control/acquire
POST /api/v1/control/renew
POST /api/v1/control/release
```

请求体：

```json
{
  "clientId": "hmi-device-id"
}
```

特性：

- 同一时刻只有一个 `controllerId`；
- 默认 Lease TTL 约 15 s；
- owner 可以 renew；
- owner release 后其他客户端可立即 acquire；
- 客户端异常退出且不 renew 时，Lease 自动过期；
- 多个客户端仍可同时读取状态；
- 控制权检查在 Gateway 服务端强制执行，不依赖 React 是否把按钮设为 disabled。

`operator_gateway_node.py` 在实际 write API 被启用时自动设置：

```text
control_lease_required = true
```

任务写请求还必须带：

```text
clientId
clientRequestId
```

## Development launch

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_system_manager system_manager.launch.py
ros2 launch agt_operator_gateway operator_gateway.launch.py
```

默认开发配置：

```text
config/operator_gateway.yaml
```

它仍适合开发/调试，不代表最终机器人网络暴露策略。

## Robot production launch

生产配置：

```text
config/operator_gateway_robot.yaml
```

它默认：

```text
host: 127.0.0.1
port: 8765
write_api_enabled: true
```

并假定局域网入口由 HMI 仓库提供的 Caddy same-origin 代理承担：

```text
LAN Browser
   |
Caddy :80
   |
/api/*
   |
127.0.0.1:8765
   |
Gateway
```

这样端口 8765 不需要直接暴露给局域网，更不需要暴露到公网。

启动：

```bash
export AGT_OPERATOR_COMMAND_TOKEN='<robot-local-secret>'

source /opt/ros/humble/setup.bash
source install/setup.bash

ros2 launch agt_operator_gateway operator_gateway.launch.py \
  config_file:=$(ros2 pkg prefix agt_operator_gateway)/share/agt_operator_gateway/config/operator_gateway_robot.yaml
```

如果 token 未设置，即使 production YAML 请求启用 write API，节点也会记录错误并保持 read-only，而不是无认证开放写接口。

## CORS / Origin

生产配置当前列出计划中的 HMI origin：

```text
http://127.0.0.1
http://localhost
http://192.168.50.10
http://agt-robot.local
```

如果最终机器人 IP/hostname 改变，应同步修改 production YAML。

## Hardware-free ROS acceptance

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_operator_gateway operator_gateway_mock.launch.py
```

然后：

```bash
ros2 run agt_operator_gateway operator_gateway_preflight.py \
  --gateway http://127.0.0.1:8765 \
  --json-output /tmp/operator_gateway_preflight.json
```

这只能证明 Runtime read-model / Web 合同，不证明导航安全或实车运动行为。

## Vehicle preflight

```bash
ros2 run agt_operator_gateway operator_gateway_preflight.py \
  --gateway http://127.0.0.1:8765 \
  --robot-state-topic /agt/system/robot_state \
  --timeout-s 5 \
  --json-output runtime/acceptance/operator_gateway_preflight.json
```

HTTP-only diagnosis：

```bash
ros2 run agt_operator_gateway operator_gateway_preflight.py \
  --skip-ros \
  --gateway http://127.0.0.1:8765
```

## No-ROS contract verification

GitHub Actions 在当前分支验证：

- contract/state store；
- HTTP/CORS；
- ROS static contract；
- mock gateway/preflight；
- interface compatibility；
- command token / idempotency；
- mission HTTP writes；
- Control Lease store + HTTP enforcement；
- Python compile checks。

本地可运行：

```bash
PYTHONPATH=src/agt_operator_gateway \
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 \
python -m pytest -q src/agt_operator_gateway/test
```

ROS 2 Humble 环境还应运行：

```bash
colcon build --packages-select agt_interfaces agt_system_manager agt_operator_gateway --symlink-install
source install/setup.bash
colcon test --packages-select agt_operator_gateway
colcon test-result --verbose
```

不要把 no-ROS CI 通过等同于实车验收完成。最终仍需验证 Runtime、Nav2、HMI、局域网、4G/ToDesk 和机器人安全链路的真实行为。
