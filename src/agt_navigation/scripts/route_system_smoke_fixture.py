#!/usr/bin/env python3

"""Prepare and publish a synthetic READY map/task/route fixture for V25-09B.

The fixture writes only below a caller-provided temporary maps root and publishes
matching active-map metadata. It is intentionally software-only and must never be
used as field acceptance evidence.
"""

from __future__ import annotations

from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

from agt_interfaces.msg import MapVersionSummary
from agt_navigation.route_task_binding import sha256_file
from agt_navigation.task_group import MapBinding, TaskGroup, Waypoint
from nav_msgs.msg import OccupancyGrid
import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy
import yaml


def _digest(label: str) -> str:
    return "sha256:" + hashlib.sha256(label.encode("utf-8")).hexdigest()


class RouteSystemSmokeFixture(Node):
    def __init__(self) -> None:
        super().__init__("agt_route_system_smoke_fixture")
        self.maps_root = Path(
            str(self.declare_parameter("maps_root", "/tmp/agt_route_system_smoke/maps").value)
        ).expanduser().resolve()
        self.vehicle_profile = Path(
            str(self.declare_parameter("vehicle_profile", "").value)
        ).expanduser().resolve()
        self.map_id = str(self.declare_parameter("map_id", "route_smoke_site").value)
        self.map_version_id = str(
            self.declare_parameter("map_version_id", "route_smoke_v1").value
        )
        self.task_group_id = str(
            self.declare_parameter("task_group_id", "route_smoke_task").value
        )
        self.route_id = str(self.declare_parameter("route_id", "route_smoke_main").value)
        self.distance_m = float(self.declare_parameter("distance_m", 2.0).value)
        self.resolution = float(self.declare_parameter("resolution", 0.05).value)
        self.width = int(self.declare_parameter("width", 160).value)
        self.height = int(self.declare_parameter("height", 120).value)
        self.origin_x = float(self.declare_parameter("origin_x", -2.0).value)
        self.origin_y = float(self.declare_parameter("origin_y", -2.0).value)
        if not self.vehicle_profile.is_file():
            raise ValueError(f"vehicle_profile does not exist: {self.vehicle_profile}")
        if self.distance_m <= 0.0 or self.resolution <= 0.0 or self.width <= 0 or self.height <= 0:
            raise ValueError("synthetic route fixture dimensions must be positive")

        qos = QoSProfile(depth=1)
        qos.reliability = ReliabilityPolicy.RELIABLE
        qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self._map_pub = self.create_publisher(
            OccupancyGrid, "/agt/map/global_occupancy", qos
        )
        self._active_pub = self.create_publisher(
            MapVersionSummary, "/agt/maps/active", qos
        )

        self.map_yaml_sha = _digest("route-smoke-map-yaml")
        self.map_image_sha = _digest("route-smoke-map-image")
        self.localization_pcd_sha = _digest("route-smoke-localization-pcd")
        self.map_content_sha = _digest("route-smoke-map-content")
        self._task = self._prepare_assets()
        self.create_timer(0.5, self._publish)
        self._publish()
        self.get_logger().info(
            "Synthetic READY route fixture prepared at "
            f"{self._version_root()} task_hash={self._task.content_sha256}"
        )

    def _version_root(self) -> Path:
        return self.maps_root / self.map_id / "versions" / self.map_version_id

    def _prepare_assets(self) -> TaskGroup:
        version = self._version_root()
        tasks = version / "tasks"
        route_dir = version / "routes" / self.route_id / "1"
        tasks.mkdir(parents=True, exist_ok=True)
        route_dir.mkdir(parents=True, exist_ok=True)

        (version / "manifest.yaml").write_text(
            yaml.safe_dump(
                {
                    "schema_version": 1,
                    "map_id": self.map_id,
                    "map_version_id": self.map_version_id,
                    "state": "READY",
                    "map_content_sha256": self.map_content_sha,
                },
                sort_keys=False,
            ),
            encoding="utf-8",
        )

        now = datetime.now(timezone.utc).isoformat()
        task = TaskGroup(
            task_group_id=self.task_group_id,
            name="Route system smoke",
            description="Software-only full ROUTE runtime smoke fixture",
            created_at=now,
            updated_at=now,
            revision=1,
            map_binding=MapBinding(
                map_id=self.map_id,
                map_version_id=self.map_version_id,
                map_yaml_path="navigation/map.yaml",
                map_yaml_sha256=self.map_yaml_sha,
                map_image_sha256=self.map_image_sha,
                localization_pcd_sha256=self.localization_pcd_sha,
                resolution=self.resolution,
                width=self.width,
                height=self.height,
                origin=(self.origin_x, self.origin_y, 0.0),
            ),
            points=[Waypoint("route_start", "Route start", 0.0, 0.0, 0.0)],
        )
        task.content_sha256 = task.canonical_hash()
        (tasks / f"{self.task_group_id}.json").write_text(
            json.dumps(task.to_dict(), ensure_ascii=False, indent=2) + "\n",
            encoding="utf-8",
        )

        route_csv = route_dir / "route.csv"
        sample_spacing = 0.10
        samples = max(2, int(round(self.distance_m / sample_spacing)) + 1)
        lines = [
            "seq,segment_id,x,y,yaw,direction,v_ref,curvature,clearance,semantic_ref,event_ref"
        ]
        for index in range(samples):
            x = self.distance_m * index / (samples - 1)
            event_ref = "route_smoke_complete" if index == samples - 1 else ""
            lines.append(
                f"{index},s000,{x:.6f},0.000000,0.000000,F,0.15,0.0,2.0,smoke_lane,{event_ref}"
            )
        route_csv.write_text("\n".join(lines) + "\n", encoding="utf-8")

        profile_sha = sha256_file(self.vehicle_profile)
        route_yaml = route_dir / "route.yaml"
        route_yaml.write_text(
            yaml.safe_dump(
                {
                    "schema_version": 1,
                    "route_id": self.route_id,
                    "revision": 1,
                    "frame_id": "map",
                    "map_binding": {
                        "map_id": self.map_id,
                        "map_version_id": self.map_version_id,
                        "map_content_sha256": self.map_content_sha,
                    },
                    "vehicle_binding": {
                        "platform_id": "route_smoke_diff",
                        "platform_profile_sha256": profile_sha,
                    },
                    "route_csv_sha256": sha256_file(route_csv),
                    "status": "READY",
                },
                sort_keys=False,
            ),
            encoding="utf-8",
        )
        (tasks / f"{self.task_group_id}.route.yaml").write_text(
            yaml.safe_dump(
                {
                    "schema_version": 1,
                    "status": "READY",
                    "backend": "ROUTE",
                    "task_binding": {
                        "task_group_id": self.task_group_id,
                        "task_revision": 1,
                        "task_content_sha256": task.content_sha256,
                    },
                    "route_binding": {
                        "route_id": self.route_id,
                        "revision": 1,
                        "route_manifest_sha256": sha256_file(route_yaml),
                    },
                },
                sort_keys=False,
            ),
            encoding="utf-8",
        )
        return task

    def _publish(self) -> None:
        stamp = self.get_clock().now().to_msg()
        grid = OccupancyGrid()
        grid.header.stamp = stamp
        grid.header.frame_id = "map"
        grid.info.resolution = self.resolution
        grid.info.width = self.width
        grid.info.height = self.height
        grid.info.origin.position.x = self.origin_x
        grid.info.origin.position.y = self.origin_y
        grid.info.origin.orientation.w = 1.0
        grid.data = [0] * (self.width * self.height)
        self._map_pub.publish(grid)

        active = MapVersionSummary()
        active.header.stamp = stamp
        active.active = True
        active.valid = True
        active.state = MapVersionSummary.STATE_READY
        active.map_id = self.map_id
        active.map_version_id = self.map_version_id
        active.navigation_yaml_sha256 = self.map_yaml_sha
        active.navigation_image_sha256 = self.map_image_sha
        active.localization_pcd_sha256 = self.localization_pcd_sha
        self._active_pub.publish(active)


def main(args=None) -> None:
    rclpy.init(args=args)
    node = RouteSystemSmokeFixture()
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
