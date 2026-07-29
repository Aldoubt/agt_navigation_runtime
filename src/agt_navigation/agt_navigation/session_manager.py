from __future__ import annotations

import copy
from dataclasses import dataclass
from typing import Iterable
from uuid import uuid4

from agt_interfaces.msg import NavigationSessionStatus
from agt_interfaces.srv import GetNavigationSession
from agt_navigation.navigation_errors import Blocker, blocker
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy


STATE_NAMES = {
    NavigationSessionStatus.STATE_IDLE: "IDLE",
    NavigationSessionStatus.STATE_VALIDATING: "VALIDATING",
    NavigationSessionStatus.STATE_REJECTED: "REJECTED",
    NavigationSessionStatus.STATE_ACCEPTED: "ACCEPTED",
    NavigationSessionStatus.STATE_RUNNING: "RUNNING",
    NavigationSessionStatus.STATE_CANCELING: "CANCELING",
    NavigationSessionStatus.STATE_SUCCEEDED: "SUCCEEDED",
    NavigationSessionStatus.STATE_FAILED: "FAILED",
    NavigationSessionStatus.STATE_CANCELED: "CANCELED",
}

TERMINAL_STATES = {
    NavigationSessionStatus.STATE_REJECTED,
    NavigationSessionStatus.STATE_SUCCEEDED,
    NavigationSessionStatus.STATE_FAILED,
    NavigationSessionStatus.STATE_CANCELED,
}

_ALLOWED_TRANSITIONS = {
    NavigationSessionStatus.STATE_IDLE: {
        NavigationSessionStatus.STATE_VALIDATING,
        NavigationSessionStatus.STATE_REJECTED,
    },
    NavigationSessionStatus.STATE_VALIDATING: {
        NavigationSessionStatus.STATE_REJECTED,
        NavigationSessionStatus.STATE_ACCEPTED,
        NavigationSessionStatus.STATE_FAILED,
    },
    NavigationSessionStatus.STATE_ACCEPTED: {
        NavigationSessionStatus.STATE_RUNNING,
        NavigationSessionStatus.STATE_CANCELING,
        NavigationSessionStatus.STATE_FAILED,
        NavigationSessionStatus.STATE_CANCELED,
    },
    NavigationSessionStatus.STATE_RUNNING: {
        NavigationSessionStatus.STATE_RUNNING,
        NavigationSessionStatus.STATE_CANCELING,
        NavigationSessionStatus.STATE_SUCCEEDED,
        NavigationSessionStatus.STATE_FAILED,
        NavigationSessionStatus.STATE_CANCELED,
    },
    NavigationSessionStatus.STATE_CANCELING: {
        NavigationSessionStatus.STATE_FAILED,
        NavigationSessionStatus.STATE_CANCELED,
    },
    NavigationSessionStatus.STATE_REJECTED: {NavigationSessionStatus.STATE_VALIDATING},
    NavigationSessionStatus.STATE_SUCCEEDED: {NavigationSessionStatus.STATE_VALIDATING},
    NavigationSessionStatus.STATE_FAILED: {NavigationSessionStatus.STATE_VALIDATING},
    NavigationSessionStatus.STATE_CANCELED: {NavigationSessionStatus.STATE_VALIDATING},
}


@dataclass(frozen=True)
class SessionSpec:
    client_request_id: str
    map_id: str
    map_version_id: str
    task_group_id: str
    task_revision: int
    task_content_sha256: str


class NavigationSessionManager:
    def __init__(self, node: Node) -> None:
        self.node = node
        qos = QoSProfile(depth=1)
        qos.reliability = ReliabilityPolicy.RELIABLE
        qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self.publisher = node.create_publisher(
            NavigationSessionStatus, "/agt/navigation/session_status", qos
        )
        self.status = self._idle_status()

    def _stamp(self):
        return self.node.get_clock().now().to_msg()

    def _idle_status(self) -> NavigationSessionStatus:
        status = NavigationSessionStatus()
        status.header.stamp = self._stamp()
        status.state = NavigationSessionStatus.STATE_IDLE
        status.started_at = status.header.stamp
        status.updated_at = status.header.stamp
        status.terminal = True
        return status

    @staticmethod
    def state_name(value: int) -> str:
        return STATE_NAMES.get(int(value), "UNKNOWN")

    def start(self, spec: SessionSpec) -> NavigationSessionStatus:
        status = NavigationSessionStatus()
        status.header.stamp = self._stamp()
        status.session_id = uuid4().hex
        status.client_request_id = spec.client_request_id
        status.map_id = spec.map_id
        status.map_version_id = spec.map_version_id
        status.task_group_id = spec.task_group_id
        status.task_revision = int(spec.task_revision)
        status.task_content_sha256 = spec.task_content_sha256
        status.state = NavigationSessionStatus.STATE_VALIDATING
        status.started_at = status.header.stamp
        status.updated_at = status.header.stamp
        status.terminal = False
        self.status = status
        self.publish()
        return self.status

    def transition(
        self,
        state: int,
        *,
        current_waypoint: int | None = None,
        total_waypoints: int | None = None,
        loop_index: int | None = None,
        missed_waypoints: Iterable[int] | None = None,
        problem: Blocker | None = None,
        success: bool | None = None,
    ) -> NavigationSessionStatus:
        if state not in _ALLOWED_TRANSITIONS.get(int(self.status.state), set()):
            raise ValueError(
                f"illegal navigation session transition {self.state_name(self.status.state)} -> {self.state_name(state)}"
            )
        status = copy.deepcopy(self.status)
        status.header.stamp = self._stamp()
        status.updated_at = status.header.stamp
        status.state = int(state)
        if current_waypoint is not None:
            status.current_waypoint = max(0, int(current_waypoint))
        if total_waypoints is not None:
            status.total_waypoints = max(0, int(total_waypoints))
        if loop_index is not None:
            status.loop_index = max(0, int(loop_index))
        if missed_waypoints is not None:
            status.missed_waypoints = [max(0, int(value)) for value in missed_waypoints]
        if problem is not None:
            status.error_code = int(problem.error_code)
            status.blocker_code = problem.code
            status.operator_message = problem.operator_message
            status.technical_message = problem.technical_message
        status.terminal = int(state) in TERMINAL_STATES
        if success is not None:
            status.success = bool(success)
        elif int(state) == NavigationSessionStatus.STATE_SUCCEEDED:
            status.success = True
        elif status.terminal:
            status.success = False
        self.status = status
        self.publish()
        return self.status

    def fail(self, code: str, technical: str, *, error_code: int = 0) -> NavigationSessionStatus:
        state = (
            NavigationSessionStatus.STATE_REJECTED
            if self.status.state == NavigationSessionStatus.STATE_VALIDATING
            else NavigationSessionStatus.STATE_FAILED
        )
        return self.transition(state, problem=blocker(code, technical, error_code=error_code), success=False)

    def publish(self) -> None:
        self.publisher.publish(self.status)

    def fill_get_response(self, request, response):
        if request.session_id and request.session_id != self.status.session_id:
            response.success = False
            response.error_code = GetNavigationSession.Response.ERROR_NOT_FOUND
            response.status = self.status
            response.message = "navigation session was not found"
            return response
        if request.client_request_id and request.client_request_id != self.status.client_request_id:
            response.success = False
            response.error_code = GetNavigationSession.Response.ERROR_NOT_FOUND
            response.status = self.status
            response.message = "navigation session was not found"
            return response
        response.success = True
        response.error_code = GetNavigationSession.Response.ERROR_NONE
        response.status = self.status
        response.message = self.state_name(self.status.state)
        return response
