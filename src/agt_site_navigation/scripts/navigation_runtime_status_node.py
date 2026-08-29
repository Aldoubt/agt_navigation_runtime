#!/usr/bin/env python3

"""Publish authoritative, fail-closed navigation runtime readiness evidence."""

from __future__ import annotations

import time

from agt_interfaces.msg import (
    LocalizationStatus,
    NavigationRuntimeStatus,
    SiteNavigationBinding,
)
from agt_site_navigation.runtime_status import (
    REQUIRED_LIFECYCLE_NODES,
    LifecycleEvidence,
    RuntimeStatusEvidence,
    evaluate_runtime_status,
)
from lifecycle_msgs.msg import State
from lifecycle_msgs.srv import GetState
import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy


class NavigationRuntimeStatusNode(Node):
    """Read Site/localization/lifecycle evidence and publish one runtime status.

    This node is deliberately observational. It uses only lifecycle ``GetState``
    services; lifecycle transitions remain owned by Nav2's lifecycle manager.
    """

    def __init__(self) -> None:
        super().__init__("agt_navigation_runtime_status")

        self._localization_timeout_s = float(
            self.declare_parameter("localization_timeout_s", 2.0).value
        )
        self._lifecycle_timeout_s = float(
            self.declare_parameter("lifecycle_timeout_s", 3.0).value
        )
        self._lifecycle_poll_period_s = float(
            self.declare_parameter("lifecycle_poll_period_s", 0.5).value
        )
        for name, value in (
            ("localization_timeout_s", self._localization_timeout_s),
            ("lifecycle_timeout_s", self._lifecycle_timeout_s),
            ("lifecycle_poll_period_s", self._lifecycle_poll_period_s),
        ):
            if value <= 0.0:
                raise ValueError(f"{name} must be > 0")

        latched_qos = QoSProfile(depth=1)
        latched_qos.reliability = ReliabilityPolicy.RELIABLE
        latched_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL

        self._publisher = self.create_publisher(
            NavigationRuntimeStatus,
            "/agt/navigation/runtime_status",
            latched_qos,
        )
        self.create_subscription(
            SiteNavigationBinding,
            "/agt/navigation/site_binding",
            self._binding_callback,
            latched_qos,
        )
        self.create_subscription(
            LocalizationStatus,
            "/agt/localization/status",
            self._localization_callback,
            10,
        )

        self._binding: SiteNavigationBinding | None = None
        self._localization: LocalizationStatus | None = None
        self._localization_seen_s: float | None = None

        self._lifecycle_clients = {
            name: self.create_client(GetState, f"/{name}/get_state")
            for name in REQUIRED_LIFECYCLE_NODES
        }
        self._lifecycle_cache: dict[str, LifecycleEvidence] = {}
        self._lifecycle_seen_s: dict[str, float] = {}
        self._lifecycle_pending = {}

        self.create_timer(self._lifecycle_poll_period_s, self._poll_lifecycles)
        self._publish_status()

    @staticmethod
    def _now_s() -> float:
        return time.monotonic()

    def _binding_callback(self, message: SiteNavigationBinding) -> None:
        self._binding = message
        self._publish_status()

    def _localization_callback(self, message: LocalizationStatus) -> None:
        self._localization = message
        self._localization_seen_s = self._now_s()
        self._publish_status()

    def _poll_lifecycles(self) -> None:
        for node_name in REQUIRED_LIFECYCLE_NODES:
            pending = self._lifecycle_pending.get(node_name)
            if pending is not None and not pending.done():
                continue

            client = self._lifecycle_clients[node_name]
            if not client.service_is_ready():
                continue

            future = client.call_async(GetState.Request())
            self._lifecycle_pending[node_name] = future
            future.add_done_callback(
                lambda completed, name=node_name: self._lifecycle_response(name, completed)
            )

        # Periodic publication keeps downstream freshness explicit even when the
        # underlying states remain unchanged.
        self._publish_status()

    def _lifecycle_response(self, node_name: str, future) -> None:
        try:
            response = future.result()
            active = int(response.current_state.id) == int(State.PRIMARY_STATE_ACTIVE)
            self._lifecycle_cache[node_name] = LifecycleEvidence(
                known=True,
                active=active,
            )
            self._lifecycle_seen_s[node_name] = self._now_s()
        except Exception as exc:
            self.get_logger().warning(
                f"failed to read lifecycle state for {node_name}: {exc}"
            )
        finally:
            self._lifecycle_pending.pop(node_name, None)
        self._publish_status()

    def _fresh_localization(self, now_s: float) -> LocalizationStatus | None:
        if self._localization is None or self._localization_seen_s is None:
            return None
        if now_s - self._localization_seen_s > self._localization_timeout_s:
            return None
        return self._localization

    def _lifecycle_evidence(self, now_s: float) -> dict[str, LifecycleEvidence]:
        evidence: dict[str, LifecycleEvidence] = {}
        for node_name in REQUIRED_LIFECYCLE_NODES:
            seen_s = self._lifecycle_seen_s.get(node_name)
            cached = self._lifecycle_cache.get(node_name)
            if (
                cached is None
                or seen_s is None
                or now_s - seen_s > self._lifecycle_timeout_s
            ):
                evidence[node_name] = LifecycleEvidence(known=False, active=False)
            else:
                evidence[node_name] = cached
        return evidence

    def _build_evidence(self) -> RuntimeStatusEvidence:
        now_s = self._now_s()
        binding = self._binding
        binding_known = bool(
            binding is not None and binding.state != SiteNavigationBinding.STATE_UNKNOWN
        )
        binding_ready = bool(
            binding_known and binding is not None
            and binding.state == SiteNavigationBinding.STATE_READY
        )
        binding_error = bool(
            binding_known and binding is not None
            and binding.state == SiteNavigationBinding.STATE_ERROR
        )

        localization = self._fresh_localization(now_s)
        localization_known = localization is not None
        localization_tracking = bool(
            localization_known
            and localization is not None
            and localization.state == LocalizationStatus.STATE_TRACKING
        )

        return RuntimeStatusEvidence(
            binding_known=binding_known,
            binding_ready=binding_ready,
            binding_error=binding_error,
            binding_blocker_codes=(
                tuple(binding.blocker_codes) if binding is not None else ()
            ),
            site_id=str(binding.site_id) if binding is not None else "",
            site_revision=str(binding.site_revision) if binding is not None else "",
            site_hash=str(binding.site_hash) if binding is not None else "",
            localization_pcd_sha256=(
                str(binding.localization_pcd_sha256) if binding is not None else ""
            ),
            localization_known=localization_known,
            localization_tracking=localization_tracking,
            localization_map_id=(
                str(localization.map_id) if localization is not None else ""
            ),
            localization_map_hash=(
                str(localization.map_hash) if localization is not None else ""
            ),
            lifecycles=self._lifecycle_evidence(now_s),
        )

    def _publish_status(self) -> None:
        evidence = self._build_evidence()
        result = evaluate_runtime_status(evidence)

        message = NavigationRuntimeStatus()
        message.header.stamp = self.get_clock().now().to_msg()
        message.header.frame_id = "map"
        message.state = int(result.state)
        message.site_id = evidence.site_id
        message.site_revision = evidence.site_revision
        message.site_hash = evidence.site_hash

        lifecycle_fields = {
            "map_server": "map_server_active",
            "planner_server": "planner_server_active",
            "smoother_server": "smoother_server_active",
            "controller_server": "controller_server_active",
            "behavior_server": "behavior_server_active",
            "bt_navigator": "bt_navigator_active",
            "waypoint_follower": "waypoint_follower_active",
            "collision_monitor": "collision_monitor_active",
        }
        for node_name, field_name in lifecycle_fields.items():
            lifecycle = evidence.lifecycles.get(node_name)
            setattr(
                message,
                field_name,
                bool(lifecycle is not None and lifecycle.known and lifecycle.active),
            )

        message.localization_bound = bool(result.localization_bound)
        message.map_identity_known = bool(result.map_identity_known)
        message.map_identity_match = bool(result.map_identity_match)
        message.localization_map_id = evidence.localization_map_id
        message.localization_map_hash = evidence.localization_map_hash
        message.blocker_codes = list(result.blocker_codes)
        message.blocker_messages = list(result.blocker_messages)
        self._publisher.publish(message)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = NavigationRuntimeStatusNode()
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
