#!/usr/bin/env python3

import rclpy
from nav_msgs.msg import Odometry
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy

from agt_interfaces.msg import LocalizationStatus, MapVersionSummary, TaskReadiness


MAP_ID = "mock_map"
MAP_VERSION_ID = "v1"
MANIFEST_SHA256 = "sha256:" + "a" * 64


class MockRuntimeContext(Node):
    def __init__(self) -> None:
        super().__init__("agt_mock_runtime_context")
        latched = QoSProfile(depth=1)
        latched.reliability = ReliabilityPolicy.RELIABLE
        latched.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self._map_pub = self.create_publisher(
            MapVersionSummary, "/agt/maps/active", latched
        )
        self._localization_pub = self.create_publisher(
            LocalizationStatus, "/agt/localization/status", 10
        )
        self._readiness_pub = self.create_publisher(
            TaskReadiness, "/agt/system/task_readiness", 10
        )
        self._odom_pub = self.create_publisher(
            Odometry, "/agt/chassis/odometry", 20
        )
        self._publish_map()
        self._timer = self.create_timer(0.05, self._tick)

    def _publish_map(self) -> None:
        message = MapVersionSummary()
        message.header.stamp = self.get_clock().now().to_msg()
        message.map_id = MAP_ID
        message.map_version_id = MAP_VERSION_ID
        message.state = MapVersionSummary.STATE_READY
        message.active = True
        message.valid = True
        message.manifest_sha256 = MANIFEST_SHA256
        self._map_pub.publish(message)

    def _tick(self) -> None:
        stamp = self.get_clock().now().to_msg()

        localization = LocalizationStatus()
        localization.header.stamp = stamp
        localization.state = LocalizationStatus.STATE_TRACKING
        localization.pose_valid = True
        localization.localization_accepted = True
        localization.has_converged = True
        localization.status_stale = False
        localization.error_code = LocalizationStatus.ERROR_NONE
        localization.map_id = MAP_ID
        localization.global_pose.header.stamp = stamp
        localization.global_pose.header.frame_id = "map"
        localization.global_pose.pose.pose.position.x = 12.3
        localization.global_pose.pose.pose.position.y = 4.8
        localization.global_pose.pose.pose.position.z = 0.0
        localization.global_pose.pose.pose.orientation.w = 1.0
        localization.message = "mock localization tracking"
        self._localization_pub.publish(localization)

        readiness = TaskReadiness()
        readiness.header.stamp = stamp
        readiness.ready = True
        readiness.active_mode = "mock_inspection"
        readiness.map_id = MAP_ID
        readiness.map_version_id = MAP_VERSION_ID
        readiness.localization_state = "TRACKING"
        readiness.health_revision = 1
        self._readiness_pub.publish(readiness)

        odometry = Odometry()
        odometry.header.stamp = stamp
        odometry.header.frame_id = "bunker_odom"
        odometry.child_frame_id = "base_footprint"
        odometry.twist.twist.linear.x = 0.0
        odometry.twist.twist.angular.z = 0.0
        self._odom_pub.publish(odometry)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MockRuntimeContext()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
