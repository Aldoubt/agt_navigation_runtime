#!/usr/bin/env python3
from __future__ import annotations

from collections import deque
from dataclasses import dataclass
import json
import math
from pathlib import Path
from typing import Iterable

import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from nav_msgs.msg import Odometry
from sensor_msgs.msg import PointCloud2
from sensor_msgs_py import point_cloud2

from agt_field_commissioning.raycast_free_space import (
    RaycastEvidenceGrid,
    load_config,
    save_evidence,
    world_to_cell,
)
from agt_field_commissioning.raycast_observer_geometry import (
    lidar_origin_world,
    load_lidar_to_imu_translation,
)


@dataclass(frozen=True)
class PoseSample:
    stamp_ns: int
    x: float
    y: float
    z: float
    qx: float
    qy: float
    qz: float
    qw: float


def _stamp_ns(stamp) -> int:
    return int(stamp.sec) * 1_000_000_000 + int(stamp.nanosec)


def _finite_xy(x: float, y: float) -> bool:
    return math.isfinite(x) and math.isfinite(y)


def _finite_pose(sample: PoseSample) -> bool:
    values = (
        sample.x,
        sample.y,
        sample.z,
        sample.qx,
        sample.qy,
        sample.qz,
        sample.qw,
    )
    if not all(math.isfinite(value) for value in values):
        return False
    quaternion_norm_sq = (
        sample.qx * sample.qx
        + sample.qy * sample.qy
        + sample.qz * sample.qz
        + sample.qw * sample.qw
    )
    return quaternion_norm_sq > 1e-24


class RaycastFreeSpaceNode(Node):
    def __init__(self) -> None:
        super().__init__("agt_commissioning_raycast_free_space")
        self.declare_parameter("output_dir", "")
        self.declare_parameter("config_file", "")
        self.declare_parameter("lio_params_file", "")
        self.declare_parameter(
            "cloud_topic", "/agt/commissioning/mapping/registered_points"
        )
        self.declare_parameter("pose_topic", "/aft_mapped_to_init")

        output_dir = str(self.get_parameter("output_dir").value).strip()
        config_file = str(self.get_parameter("config_file").value).strip()
        lio_params_file = str(self.get_parameter("lio_params_file").value).strip()
        cloud_topic = str(self.get_parameter("cloud_topic").value).strip()
        pose_topic = str(self.get_parameter("pose_topic").value).strip()
        if not output_dir:
            raise RuntimeError("output_dir parameter is required")
        if not config_file:
            raise RuntimeError("config_file parameter is required")
        if not lio_params_file:
            raise RuntimeError("lio_params_file parameter is required")
        if not cloud_topic or not pose_topic:
            raise RuntimeError("cloud_topic and pose_topic must be non-empty")

        self.output_dir = Path(output_dir).expanduser().resolve()
        self.output_dir.mkdir(parents=True, exist_ok=True)
        self.config = load_config(config_file)
        self.lidar_to_imu_translation = load_lidar_to_imu_translation(lio_params_file)
        self.grid = RaycastEvidenceGrid(self.config)
        self.pose_history: deque[PoseSample] = deque(maxlen=512)
        self.cloud_index = 0
        self.processed_frames = 0
        self.skipped_stride_frames = 0
        self.skipped_no_pose_frames = 0
        self.skipped_frame_mismatch = 0
        self.points_considered = 0
        self._saved = False

        self.pose_subscription = self.create_subscription(
            Odometry,
            pose_topic,
            self._on_pose,
            qos_profile_sensor_data,
        )
        self.cloud_subscription = self.create_subscription(
            PointCloud2,
            cloud_topic,
            self._on_cloud,
            qos_profile_sensor_data,
        )
        self.get_logger().info(
            "raycast free-space observer ready: "
            f"cloud={cloud_topic} pose={pose_topic} output={self.output_dir} "
            f"resolution={self.config.resolution_m:.3f}m "
            f"point_stride={self.config.point_stride} "
            f"max_range={self.config.max_ray_range_m:.1f}m "
            f"lidar_to_imu_translation={self.lidar_to_imu_translation}"
        )

    def _on_pose(self, message: Odometry) -> None:
        pose = message.pose.pose
        sample = PoseSample(
            stamp_ns=_stamp_ns(message.header.stamp),
            x=float(pose.position.x),
            y=float(pose.position.y),
            z=float(pose.position.z),
            qx=float(pose.orientation.x),
            qy=float(pose.orientation.y),
            qz=float(pose.orientation.z),
            qw=float(pose.orientation.w),
        )
        if not _finite_pose(sample):
            return
        self.pose_history.append(sample)

    def _nearest_pose(self, stamp_ns: int) -> PoseSample | None:
        if not self.pose_history:
            return None
        nearest = min(
            self.pose_history,
            key=lambda sample: abs(sample.stamp_ns - int(stamp_ns)),
        )
        max_age_ns = int(self.config.pose_max_age_s * 1_000_000_000)
        if abs(nearest.stamp_ns - int(stamp_ns)) > max_age_ns:
            return None
        return nearest

    def _iter_endpoints(self, message: PointCloud2) -> Iterable[tuple[float, float]]:
        point_stride = self.config.point_stride
        seen_cells: set[tuple[int, int]] = set()
        for point_index, point in enumerate(
            point_cloud2.read_points(
                message,
                field_names=("x", "y", "z"),
                skip_nans=True,
            )
        ):
            if point_index % point_stride != 0:
                continue
            x = float(point[0])
            y = float(point[1])
            if not _finite_xy(x, y):
                continue
            cell = world_to_cell((x, y), self.config.resolution_m)
            if cell in seen_cells:
                continue
            seen_cells.add(cell)
            yield x, y

    def _on_cloud(self, message: PointCloud2) -> None:
        self.cloud_index += 1
        if (self.cloud_index - 1) % self.config.cloud_stride != 0:
            self.skipped_stride_frames += 1
            return

        expected_frame = self.config.frame_id.lstrip("/")
        actual_frame = str(message.header.frame_id).lstrip("/")
        if actual_frame and expected_frame and actual_frame != expected_frame:
            self.skipped_frame_mismatch += 1
            if self.skipped_frame_mismatch == 1:
                self.get_logger().warning(
                    "registered cloud frame does not match raycast global frame: "
                    f"cloud={message.header.frame_id!r} expected={self.config.frame_id!r}"
                )
            return

        pose = self._nearest_pose(_stamp_ns(message.header.stamp))
        if pose is None:
            self.skipped_no_pose_frames += 1
            return

        origin_xyz = lidar_origin_world(
            position_xyz=(pose.x, pose.y, pose.z),
            orientation_xyzw=(pose.qx, pose.qy, pose.qz, pose.qw),
            lidar_to_imu_translation_xyz=self.lidar_to_imu_translation,
        )
        origin = (origin_xyz[0], origin_xyz[1])
        endpoints = list(self._iter_endpoints(message))
        if not endpoints:
            return
        self.points_considered += len(endpoints)
        self.grid.observe_rays(origin, endpoints)
        self.processed_frames += 1

    def save(self) -> None:
        if self._saved:
            return
        self._saved = True
        if self.grid.stats.accepted_rays <= 0:
            self.get_logger().warning(
                "raycast free-space observer has no accepted rays; no evidence artifact written"
            )
            return
        artifact = save_evidence(
            self.grid,
            self.output_dir / "free_space_evidence.bin",
            self.output_dir / "raycast_record.json",
        )
        record = json.loads(artifact.record.read_text(encoding="utf-8"))
        record["observer"] = {
            "processed_frames": self.processed_frames,
            "skipped_stride_frames": self.skipped_stride_frames,
            "skipped_no_pose_frames": self.skipped_no_pose_frames,
            "skipped_frame_mismatch": self.skipped_frame_mismatch,
            "points_considered": self.points_considered,
        }
        record["observer"]["lidar_to_imu_translation_m"] = list(
            self.lidar_to_imu_translation
        )
        temporary = artifact.record.with_name(artifact.record.name + ".tmp")
        temporary.write_text(
            json.dumps(record, indent=2, sort_keys=True) + "\n",
            encoding="utf-8",
        )
        temporary.replace(artifact.record)
        self.get_logger().info(
            "raycast free-space evidence saved: "
            f"frames={self.processed_frames} rays={self.grid.stats.accepted_rays} "
            f"binary={artifact.binary}"
        )


def main(args=None) -> None:
    rclpy.init(args=args)
    node: RaycastFreeSpaceNode | None = None
    try:
        node = RaycastFreeSpaceNode()
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        if node is not None:
            node.save()
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
