from __future__ import annotations

from threading import Event, Lock
from typing import Any

from agt_interfaces.action import Relocalize
from agt_interfaces.msg import ComponentHealth, LocalizationStatus, RobotState
from rclpy.action import ActionClient
from rclpy.node import Node


class RunRosAdapter:
    """Authoritative Run readiness plus explicit bounded relocalization.

    AUTO permit deliberately remains false until a dedicated physical/operator
    permit source is integrated. It is not inferred from system mode or software
    safety enable.
    """

    def __init__(
        self,
        node: Node,
        *,
        robot_state_provider,
        timeout_s: float = 5.0,
        relocalize_timeout_s: float = 15.0,
        max_candidates: int = 64,
        lidar_component_id: str = "lidar",
        camera_gimbal_component_id: str = "camera_gimbal",
        localization_freshness_s: float = 2.0,
        health_freshness_s: float = 2.0,
    ) -> None:
        if timeout_s <= 0.0 or relocalize_timeout_s <= 0.0:
            raise ValueError("run adapter timeouts must be > 0")
        if max_candidates <= 0:
            raise ValueError("max_candidates must be > 0")
        if localization_freshness_s <= 0.0 or health_freshness_s <= 0.0:
            raise ValueError("readiness freshness thresholds must be > 0")
        self._node = node
        self._robot_state_provider = robot_state_provider
        self._timeout_s = float(timeout_s)
        self._relocalize_timeout_s = float(relocalize_timeout_s)
        self._max_candidates = int(max_candidates)
        self._lidar_component_id = str(lidar_component_id).strip()
        self._camera_gimbal_component_id = str(camera_gimbal_component_id).strip()
        self._localization_freshness_s = float(localization_freshness_s)
        self._health_freshness_s = float(health_freshness_s)
        self._lock = Lock()
        self._relocalize_client = ActionClient(
            node,
            Relocalize,
            '/agt/localization/relocalize',
        )

    def _wait_future(self, future: Any) -> Any:
        event = Event()
        future.add_done_callback(lambda _future: event.set())
        if not event.wait(self._timeout_s):
            raise TimeoutError("ROS run-control future timed out")
        if future.cancelled():
            raise RuntimeError("ROS run-control future was canceled")
        exception = future.exception()
        if exception is not None:
            raise RuntimeError(f"ROS run-control future failed: {exception}")
        return future.result()

    @staticmethod
    def _component_ready(state: RobotState, component_id: str) -> bool:
        if not component_id or not bool(state.system_health_known):
            return False
        for component in state.system_health.components:
            if component.component_id == component_id:
                return bool(component.present) and int(component.state) == ComponentHealth.STATE_OK
        return False

    def readiness(self) -> dict[str, Any]:
        state = self._robot_state_provider()
        blockers: list[str] = []
        if state is None:
            return {
                "ready": False,
                "autoPermit": False,
                "siteReady": False,
                "localizationReady": False,
                "navigationReady": False,
                "lidarReady": False,
                "cameraGimbalReady": False,
                "blockers": ["ROBOT_STATE_UNAVAILABLE", "AUTO_PERMIT_SOURCE_UNAVAILABLE"],
            }

        site_ready = bool(state.active_map_known and state.active_map.active)
        localization_ready = bool(
            state.localization_status_known
            and float(state.localization_freshness_s) <= self._localization_freshness_s
            and int(state.localization.state) == LocalizationStatus.STATE_TRACKING
            and state.localization.pose_valid
            and state.localization.localization_accepted
            and not state.localization.status_stale
        )
        navigation_ready = bool(
            int(state.nav2_state) == RobotState.NAV2_ACTIVE
            and state.navigation_ready
            and state.safety_status_known
            and state.safety_motion_enabled
            and not state.emergency_stop
            and not state.estop_latched
        )
        health_fresh = bool(
            state.system_health_known
            and float(state.system_health_freshness_s) <= self._health_freshness_s
        )
        lidar_ready = health_fresh and self._component_ready(state, self._lidar_component_id)
        camera_gimbal_ready = health_fresh and self._component_ready(
            state,
            self._camera_gimbal_component_id,
        )

        if not site_ready:
            blockers.append("SITE_NOT_READY")
        if not localization_ready:
            blockers.append("LOCALIZATION_NOT_TRACKING")
        if not navigation_ready:
            blockers.append("NAVIGATION_NOT_READY")
        if not lidar_ready:
            blockers.append("LIDAR_HEALTH_NOT_READY")
        if not camera_gimbal_ready:
            blockers.append("CAMERA_GIMBAL_HEALTH_NOT_READY")

        # Physical RC/operator AUTO permit is intentionally not represented by
        # RobotState yet. Never substitute system mode or safety_motion_enabled.
        blockers.append("AUTO_PERMIT_SOURCE_UNAVAILABLE")
        auto_permit = False

        for code in list(state.blocker_codes):
            normalized = str(code).strip()
            if normalized and normalized not in blockers:
                blockers.append(normalized)

        return {
            "ready": False,
            "autoPermit": False,
            "siteReady": site_ready,
            "localizationReady": localization_ready,
            "navigationReady": navigation_ready,
            "lidarReady": lidar_ready,
            "cameraGimbalReady": camera_gimbal_ready,
            "blockers": blockers,
        }

    def relocalize(self) -> dict[str, Any]:
        with self._lock:
            if not self._relocalize_client.wait_for_server(timeout_sec=self._timeout_s):
                raise RuntimeError("Relocalize action server is unavailable")

            goal = Relocalize.Goal()
            goal.mode = Relocalize.Goal.MODE_AUTO_SEARCH
            goal.use_initial_pose = False
            goal.use_last_valid_pose = True
            goal.use_configured_candidates = True
            goal.use_external_coarse_pose = True
            goal.max_candidates = self._max_candidates
            goal.publish_debug = False
            goal.timeout_s = self._relocalize_timeout_s

            try:
                goal_handle = self._wait_future(
                    self._relocalize_client.send_goal_async(goal)
                )
            except TimeoutError as exc:
                raise RuntimeError("Relocalize goal acceptance timed out") from exc

            if goal_handle is None or not bool(goal_handle.accepted):
                raise ValueError("Relocalize goal rejected by localization Runtime")
            return {
                "accepted": True,
                "state": "REQUESTED",
                "message": "bounded AUTO_SEARCH relocalization accepted",
            }
