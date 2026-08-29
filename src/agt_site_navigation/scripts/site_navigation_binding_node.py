#!/usr/bin/env python3

"""Publish a fail-closed navigation asset binding for the authoritative Active Site."""

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from agt_interfaces.msg import MapVersionSummary, SiteNavigationBinding
from agt_site_navigation.resolver import (
    ActiveSiteNavigationResolver,
    SiteNavigationBindingError,
)
import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy


_EXPECTED_BLOCKERS = {
    "NO_ACTIVE_SITE",
    "ACTIVE_SITE_NOT_READY",
    "ACTIVE_SITE_NOT_DEPLOYED",
    "ACTIVE_SITE_IDENTITY_MISMATCH",
    "SITE_ASSET_INVALID",
}


class SiteNavigationBindingNode(Node):
    def __init__(self) -> None:
        super().__init__("agt_site_navigation_binding")
        sites_root = Path(
            str(self.declare_parameter("sites_root", "/opt/agt/sites").value)
        ).expanduser()
        vehicle_profile = Path(
            str(
                self.declare_parameter(
                    "site_vehicle_profile", "/opt/agt/profiles/bunker.yaml"
                ).value
            )
        ).expanduser()
        schema_root = Path(get_package_share_directory("agt_runtime_contracts")) / "schemas"
        self._resolver = ActiveSiteNavigationResolver(
            sites_root=sites_root,
            vehicle_profile=vehicle_profile,
            vehicle_schema=schema_root / "vehicle_profile.schema.json",
            site_schema=schema_root / "site_package.schema.json",
        )

        qos = QoSProfile(depth=1)
        qos.reliability = ReliabilityPolicy.RELIABLE
        qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self._publisher = self.create_publisher(
            SiteNavigationBinding, "/agt/navigation/site_binding", qos
        )
        self.create_subscription(
            MapVersionSummary,
            "/agt/maps/active",
            self._active_site_callback,
            qos,
        )
        self._publish_unknown()

    def _base_message(self, state: int) -> SiteNavigationBinding:
        message = SiteNavigationBinding()
        message.header.stamp = self.get_clock().now().to_msg()
        message.header.frame_id = "map"
        message.state = int(state)
        return message

    def _publish_unknown(self) -> None:
        message = self._base_message(SiteNavigationBinding.STATE_UNKNOWN)
        message.blocker_codes = ["ACTIVE_SITE_UNKNOWN"]
        message.messages = ["No Active Site authority has been observed yet."]
        self._publisher.publish(message)

    def _active_site_callback(self, active_site: MapVersionSummary) -> None:
        try:
            binding = self._resolver.resolve(active_site)
            message = self._base_message(SiteNavigationBinding.STATE_READY)
            message.site_id = binding.site_id
            message.site_revision = binding.site_revision
            message.site_hash = binding.site_hash
            message.manifest_sha256 = binding.manifest_sha256
            message.navigation_yaml = str(binding.navigation_yaml)
            message.navigation_yaml_sha256 = binding.navigation_yaml_sha256
            message.navigation_image = str(binding.navigation_image)
            message.navigation_image_sha256 = binding.navigation_image_sha256
            message.localization_pcd = str(binding.localization_pcd)
            message.localization_pcd_sha256 = binding.localization_pcd_sha256
            message.processing_record = (
                str(binding.processing_record) if binding.processing_record else ""
            )
            message.blocker_codes = []
            message.messages = []
        except SiteNavigationBindingError as exc:
            state = (
                SiteNavigationBinding.STATE_BLOCKED
                if exc.code in _EXPECTED_BLOCKERS
                else SiteNavigationBinding.STATE_ERROR
            )
            # Build a fresh message so a tombstone or changed Site cannot retain
            # any asset path from the previous transient-local READY binding.
            message = self._base_message(state)
            message.site_id = str(getattr(active_site, "map_id", ""))
            message.site_revision = str(getattr(active_site, "map_version_id", ""))
            message.site_hash = str(getattr(active_site, "map_hash", ""))
            message.blocker_codes = [exc.code]
            message.messages = [exc.message]
        except Exception as exc:
            message = self._base_message(SiteNavigationBinding.STATE_ERROR)
            message.site_id = str(getattr(active_site, "map_id", ""))
            message.site_revision = str(getattr(active_site, "map_version_id", ""))
            message.blocker_codes = ["SITE_NAVIGATION_BINDING_ERROR"]
            message.messages = [str(exc)]

        self._publisher.publish(message)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = SiteNavigationBindingNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
