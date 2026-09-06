#!/usr/bin/env python3

from __future__ import annotations

from math import cos, sin

from agt_interfaces.msg import (
    LocalizationStatus,
    MapVersionSummary,
    MissionStatus,
    RobotState,
    SystemHealth,
    TaskReadiness,
)
import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy


class MockRobotStatePublisher(Node):
    """Publish a deterministic RobotState for hardware-free gateway/HMI acceptance."""

    def __init__(self) -> None:
        super().__init__('agt_operator_gateway_mock_robot_state')

        self._publish_rate_hz = float(self.declare_parameter('publish_rate_hz', 5.0).value)
        self._map_id = str(self.declare_parameter('map_id', 'mock_map').value)
        self._map_version_id = str(self.declare_parameter('map_version_id', 'v1').value)
        self._mission_id = str(self.declare_parameter('mission_id', 'mock_inspection').value)
        self._x = float(self.declare_parameter('x', 2.0).value)
        self._y = float(self.declare_parameter('y', 1.0).value)
        self._yaw = float(self.declare_parameter('yaw', 0.35).value)

        if self._publish_rate_hz <= 0.0:
            raise ValueError('publish_rate_hz must be > 0')

        qos = QoSProfile(depth=1)
        qos.reliability = ReliabilityPolicy.RELIABLE
        qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self._publisher = self.create_publisher(
            RobotState,
            '/agt/system/robot_state',
            qos,
        )
        self._revision = 0
        self.create_timer(1.0 / self._publish_rate_hz, self._publish)
        self._publish()

    def _publish(self) -> None:
        self._revision += 1
        now = self.get_clock().now().to_msg()

        state = RobotState()
        state.header.stamp = now
        state.header.frame_id = 'map'
        state.revision = self._revision
        state.system_mode = RobotState.MODE_NAVIGATION
        state.active_profile = 'mock_hardware_free'
        state.managed_process_count = 1
        state.running_process_count = 1

        state.system_health_known = True
        state.system_health_freshness_s = 0.0
        state.system_health = SystemHealth()
        state.system_health.header.stamp = now
        state.system_health.overall_state = SystemHealth.STATE_OK
        state.system_health.revision = self._revision

        state.task_readiness_known = True
        state.task_readiness_freshness_s = 0.0
        state.task_readiness = TaskReadiness()
        state.task_readiness.header.stamp = now
        state.task_readiness.ready = True
        state.task_readiness.active_mode = 'NAVIGATION'
        state.task_readiness.map_id = self._map_id
        state.task_readiness.map_version_id = self._map_version_id
        state.task_readiness.localization_state = 'TRACKING'
        state.task_readiness.health_revision = self._revision

        state.active_map_known = True
        state.active_map_freshness_s = 0.0
        state.active_map = MapVersionSummary()
        state.active_map.header.stamp = now
        state.active_map.map_id = self._map_id
        state.active_map.map_version_id = self._map_version_id
        state.active_map.state = MapVersionSummary.STATE_READY
        state.active_map.active = True
        state.active_map.valid = True
        state.active_map.map_hash = 'sha256:mock-map'
        state.active_map.manifest_sha256 = 'sha256:mock-manifest'

        state.localization_status_known = True
        state.localization_freshness_s = 0.0
        state.localization = LocalizationStatus()
        state.localization.header.stamp = now
        state.localization.header.frame_id = 'map'
        state.localization.state = LocalizationStatus.STATE_TRACKING
        state.localization.pose_valid = True
        state.localization.localization_accepted = True
        state.localization.has_converged = True
        state.localization.error_code = LocalizationStatus.ERROR_NONE
        state.localization.backend = 'mock_localization'
        state.localization.map_id = self._map_id
        state.localization.map_hash = 'sha256:mock-map'
        state.localization.global_pose.header.stamp = now
        state.localization.global_pose.header.frame_id = 'map'
        state.localization.global_pose.pose.pose.position.x = self._x
        state.localization.global_pose.pose.pose.position.y = self._y
        state.localization.global_pose.pose.pose.orientation.z = sin(self._yaw * 0.5)
        state.localization.global_pose.pose.pose.orientation.w = cos(self._yaw * 0.5)

        state.mission_status_known = True
        state.mission_freshness_s = 0.0
        state.mission = MissionStatus()
        state.mission.header.stamp = now
        state.mission.state = MissionStatus.STATE_RUNNING
        state.mission.mission_id = self._mission_id
        state.mission.mission_version = 'v1'
        state.mission.content_sha256 = 'sha256:mock-mission'
        state.mission.map_id = self._map_id
        state.mission.map_version_id = self._map_version_id
        state.mission.current_step_index = 0
        state.mission.total_steps = 3
        state.mission.current_step_id = 'P001'
        state.mission.current_waypoint = 1
        state.mission.total_waypoints = 3

        state.nav2_state = RobotState.NAV2_ACTIVE
        state.nav2_freshness_s = 0.0
        state.safety_status_known = True
        state.safety_motion_enabled = True
        state.emergency_stop = False
        state.estop_latched = False
        state.navigation_ready = True
        state.safety_freshness_s = 0.0
        state.chassis_status_known = True
        state.chassis_connected = True
        state.chassis_control_mode = RobotState.CHASSIS_MODE_CONTROL
        state.chassis_status_freshness_s = 0.0
        state.chassis_odometry_freshness_s = 0.0
        state.bag_status_known = False
        state.error_code = 0
        state.message = 'hardware-free mock runtime state'

        self._publisher.publish(state)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MockRobotStatePublisher()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
