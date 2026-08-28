#!/usr/bin/env python3

from __future__ import annotations

from collections import OrderedDict
from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from agt_interfaces.msg import MapVersionSummary
from agt_interfaces.srv import ActivateMapVersion, ListMapVersions, ValidateMapVersion
from agt_site_runtime.activation_store import ActivationStore
from agt_site_runtime.models import SiteKey, SiteSummary
from agt_site_runtime.registry import SiteRegistry
from agt_site_runtime.runtime_policy import (
    ERROR_INTERNAL,
    ERROR_INVALID_REQUEST,
    ERROR_NONE,
    ActivationResult,
    SiteRuntimePolicy,
)
from agt_site_runtime.validator import SiteValidator
import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy


class SiteRuntimeNode(Node):
    """Own the read-only deployed Site registry and authoritative active Site."""

    def __init__(self) -> None:
        super().__init__("agt_site_runtime")

        sites_root = Path(
            str(self.declare_parameter("sites_root", "/opt/agt/sites").value)
        ).expanduser()
        state_root = Path(
            str(
                self.declare_parameter(
                    "state_root", "~/.local/state/agt_navigation_runtime"
                ).value
            )
        ).expanduser()
        vehicle_profile = Path(
            str(
                self.declare_parameter(
                    "vehicle_profile", "/opt/agt/profiles/bunker.yaml"
                ).value
            )
        ).expanduser()
        recent_request_limit = int(
            self.declare_parameter("recent_request_limit", 128).value
        )

        contract_share = Path(get_package_share_directory("agt_runtime_contracts"))
        vehicle_schema = contract_share / "schemas" / "vehicle_profile.schema.json"
        site_schema = contract_share / "schemas" / "site_package.schema.json"

        registry = SiteRegistry(sites_root)
        validator = SiteValidator(vehicle_profile, vehicle_schema, site_schema)
        store = ActivationStore(state_root)
        self._policy = SiteRuntimePolicy(
            registry,
            validator,
            store,
            recent_request_limit=recent_request_limit,
        )
        self._published_requests: OrderedDict[str, SiteKey] = OrderedDict()
        self._published_request_limit = recent_request_limit

        latched = QoSProfile(depth=1)
        latched.reliability = ReliabilityPolicy.RELIABLE
        latched.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self._active_pub = self.create_publisher(
            MapVersionSummary,
            "/agt/maps/active",
            latched,
        )

        self.create_service(
            ListMapVersions,
            "/agt/maps/list",
            self._list_versions,
        )
        self.create_service(
            ValidateMapVersion,
            "/agt/maps/validate",
            self._validate_version,
        )
        self.create_service(
            ActivateMapVersion,
            "/agt/maps/activate",
            self._activate_version,
        )

        self._restore_on_startup()

    def _to_message(self, summary: SiteSummary) -> MapVersionSummary:
        message = MapVersionSummary()
        message.header.stamp = self.get_clock().now().to_msg()
        message.map_id = summary.map_id
        message.map_version_id = summary.map_version_id
        message.parent_map_version_id = summary.parent_map_version_id
        message.state = int(summary.state)
        message.active = bool(summary.active)
        message.pinned = bool(summary.pinned)
        message.deleted = bool(summary.deleted)
        message.valid = bool(summary.valid)
        message.map_hash = summary.map_hash
        message.manifest_sha256 = summary.manifest_sha256
        message.navigation_yaml_sha256 = summary.navigation_yaml_sha256
        message.navigation_image_sha256 = summary.navigation_image_sha256
        message.localization_pcd_sha256 = summary.localization_pcd_sha256
        message.navigation_yaml = summary.navigation_yaml
        message.localization_pcd = summary.localization_pcd
        message.processing_record = summary.processing_record
        message.tasks_directory = summary.tasks_directory
        message.storage_bytes = int(summary.storage_bytes)
        message.created_at = summary.created_at
        message.validation_errors = list(summary.validation_errors)
        message.validation_warnings = list(summary.validation_warnings)
        return message

    @staticmethod
    def _state_name(summary: SiteSummary | None) -> str:
        if summary is None:
            return "UNKNOWN"
        return {
            MapVersionSummary.STATE_READY: "READY",
            MapVersionSummary.STATE_INVALID: "INVALID",
        }.get(int(summary.state), "UNKNOWN")

    def _publish_tombstone(self) -> None:
        message = MapVersionSummary()
        message.header.stamp = self.get_clock().now().to_msg()
        message.state = MapVersionSummary.STATE_UNKNOWN
        message.active = False
        message.valid = False
        self._active_pub.publish(message)

    def _publish_active(self, summary: SiteSummary) -> None:
        self._active_pub.publish(self._to_message(summary))

    def _restore_on_startup(self) -> None:
        try:
            result = self._policy.restore()
        except Exception as exc:  # fail closed at the ROS process boundary
            self._publish_tombstone()
            self.get_logger().error(f"active Site restore failed: {exc}")
            return

        if result.success and result.summary is not None:
            self._publish_active(result.summary)
            self.get_logger().info(
                "restored active Site "
                f"{result.summary.map_id}/{result.summary.map_version_id}"
            )
            return

        if result.revoke_active:
            self._publish_tombstone()
        if result.success:
            self.get_logger().info("no persisted active Site selection")
        else:
            details = ", ".join(result.blocker_codes) or result.message
            self.get_logger().warning(f"active Site restore blocked: {details}")

    def _list_versions(self, request, response):
        try:
            summaries = self._policy.list_versions(
                map_id=request.map_id,
                state=int(request.state),
            )
            response.success = True
            response.error_code = ListMapVersions.Response.ERROR_NONE
            response.versions = [self._to_message(item) for item in summaries]
            response.message = f"{len(summaries)} deployed Site version(s)"
        except Exception as exc:
            response.success = False
            response.error_code = ListMapVersions.Response.ERROR_INTERNAL
            response.versions = []
            response.message = "failed to list deployed Site versions"
            self.get_logger().error(f"Site list failed: {exc}")
        return response

    @staticmethod
    def _valid_identity(map_id: str, map_version_id: str) -> bool:
        return bool(map_id and map_id.strip() and map_version_id and map_version_id.strip())

    def _validate_version(self, request, response):
        if not self._valid_identity(request.map_id, request.map_version_id):
            response.success = False
            response.error_code = ValidateMapVersion.Response.ERROR_INVALID_REQUEST
            response.blocker_codes = ["INVALID_REQUEST"]
            response.blocker_messages = ["map_id and map_version_id must be non-empty"]
            response.message = "invalid map identity"
            return response

        try:
            result = self._policy.validate(
                SiteKey(request.map_id, request.map_version_id)
            )
        except Exception as exc:
            result = ActivationResult(
                success=False,
                error_code=ERROR_INTERNAL,
                blocker_codes=("SITE_VALIDATION_FAILED",),
                blocker_messages=(str(exc),),
                message="site validation failed internally",
            )
            self.get_logger().error(f"Site validation failed internally: {exc}")

        response.success = result.success
        response.error_code = int(result.error_code)
        if result.summary is not None:
            response.version = self._to_message(result.summary)
        response.blocker_codes = list(result.blocker_codes)
        response.blocker_messages = list(result.blocker_messages)
        response.message = result.message
        return response

    def _remember_published_request(self, request_id: str, key: SiteKey) -> None:
        self._published_requests[request_id] = key
        self._published_requests.move_to_end(request_id)
        while len(self._published_requests) > self._published_request_limit:
            self._published_requests.popitem(last=False)

    def _activate_version(self, request, response):
        key = SiteKey(request.map_id, request.map_version_id)
        if not self._valid_identity(request.map_id, request.map_version_id):
            result = ActivationResult(
                success=False,
                error_code=ERROR_INVALID_REQUEST,
                blocker_codes=("INVALID_REQUEST",),
                blocker_messages=("map_id and map_version_id must be non-empty",),
                message="invalid map identity",
            )
        else:
            try:
                result = self._policy.activate(key, request.client_request_id)
            except Exception as exc:
                result = ActivationResult(
                    success=False,
                    error_code=ERROR_INTERNAL,
                    blocker_codes=("SITE_ACTIVATION_FAILED",),
                    blocker_messages=(str(exc),),
                    message="site activation failed internally",
                )
                self.get_logger().error(f"Site activation failed internally: {exc}")

        already_published = self._published_requests.get(request.client_request_id) == key
        if result.success and result.summary is not None and not already_published:
            self._publish_active(result.summary)
            self._remember_published_request(request.client_request_id, key)
            self.get_logger().info(
                "activated Site "
                f"{result.summary.map_id}/{result.summary.map_version_id}"
            )
        elif not result.success:
            details = ", ".join(result.blocker_codes) or result.message
            self.get_logger().warning(
                f"Site activation rejected for {key.site_id}/{key.revision}: {details}"
            )

        response.success = result.success
        response.error_code = int(result.error_code)
        response.map_id = request.map_id
        response.map_version_id = request.map_version_id
        response.state = self._state_name(result.summary)
        response.blocker_codes = list(result.blocker_codes)
        response.blocker_messages = list(result.blocker_messages)
        response.operator_messages = [result.message] if result.message else []
        response.technical_messages = list(result.blocker_messages)
        if result.summary is not None:
            response.version = self._to_message(result.summary)
        return response


def main(args=None) -> None:
    rclpy.init(args=args)
    node = SiteRuntimeNode()
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
