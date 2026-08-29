from __future__ import annotations

from agt_interfaces.msg import RobotState
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy

from .contract import build_mission_view, build_navigation_view, build_robot_snapshot
from .state_store import GatewayStateStore

DEFAULT_ROBOT_STATE_TOPIC = '/agt/system/robot_state'


class RobotStateAdapter(Node):
    """Read-only projection adapter for the authoritative system-manager RobotState."""

    def __init__(self) -> None:
        super().__init__('agt_operator_gateway')

        self._host = str(self.declare_parameter('host', '0.0.0.0').value).strip()
        self._port = int(self.declare_parameter('port', 8765).value)
        self._robot_id = str(
            self.declare_parameter('robot_id', 'agt-robot').value
        ).strip()
        self._robot_name = str(
            self.declare_parameter('robot_name', 'AGT Robot').value
        ).strip()
        self._robot_state_topic = str(
            self.declare_parameter(
                'robot_state_topic', DEFAULT_ROBOT_STATE_TOPIC
            ).value
        ).strip()
        freshness_ms = int(
            self.declare_parameter('runtime_freshness_ms', 1500).value
        )
        self._offline_after_ms = int(
            self.declare_parameter('offline_after_ms', 5000).value
        )
        self._stream_poll_s = float(
            self.declare_parameter('stream_poll_s', 0.05).value
        )
        raw_origins = self.declare_parameter(
            'cors_allowed_origins', ['*']
        ).value
        self._cors_allowed_origins = tuple(
            dict.fromkeys(
                str(origin).strip()
                for origin in raw_origins
                if str(origin).strip()
            )
        )

        if (
            not self._host
            or not self._robot_id
            or not self._robot_name
            or not self._robot_state_topic
        ):
            raise ValueError(
                'gateway host, robot identity and robot_state_topic must be non-empty'
            )
        if self._port <= 0 or self._port > 65535:
            raise ValueError('port must be in 1..65535')
        if self._offline_after_ms <= freshness_ms:
            raise ValueError(
                'offline_after_ms must be greater than runtime_freshness_ms'
            )
        if self._stream_poll_s <= 0.0:
            raise ValueError('stream_poll_s must be > 0')

        self._store = GatewayStateStore(freshness_ms=freshness_ms)

        latched = QoSProfile(depth=1)
        latched.reliability = ReliabilityPolicy.RELIABLE
        latched.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self.create_subscription(
            RobotState,
            self._robot_state_topic,
            self._robot_state_callback,
            latched,
        )

    @property
    def store(self) -> GatewayStateStore:
        return self._store

    @property
    def host(self) -> str:
        return self._host

    @property
    def port(self) -> int:
        return self._port

    @property
    def offline_after_ms(self) -> int:
        return self._offline_after_ms

    @property
    def stream_poll_s(self) -> float:
        return self._stream_poll_s

    @property
    def cors_allowed_origins(self) -> tuple[str, ...]:
        return self._cors_allowed_origins

    def _robot_state_callback(self, message: RobotState) -> None:
        self._store.update(
            source_revision=int(message.revision),
            robot_snapshot=build_robot_snapshot(
                message,
                robot_id=self._robot_id,
                robot_name=self._robot_name,
            ),
            navigation=build_navigation_view(message),
            mission=build_mission_view(message),
        )
