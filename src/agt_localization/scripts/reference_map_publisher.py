#!/usr/bin/env python3
"""Publish a read-only binary PCD as a latched map-frame point cloud."""
import struct

import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy
from sensor_msgs.msg import PointCloud2, PointField
from sensor_msgs_py import point_cloud2
from std_msgs.msg import Header


class ReferenceMapPublisher(Node):
    def __init__(self):
        super().__init__("agt_localization_reference_map_publisher")
        self.declare_parameter("pcd", "")
        self.declare_parameter("topic", "/agt/localization/reference_map")
        self.declare_parameter("max_points", 300000)
        map_qos = QoSProfile(depth=1)
        map_qos.reliability = ReliabilityPolicy.RELIABLE
        map_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self.publisher = self.create_publisher(PointCloud2, self.get_parameter("topic").value, map_qos)
        self.publish_map()

    def publish_map(self):
        path = str(self.get_parameter("pcd").value)
        try:
            with open(path, "rb") as stream:
                header = bytearray()
                while b"DATA " not in header:
                    line = stream.readline()
                    if not line:
                        raise ValueError("PCD header has no DATA declaration")
                    header.extend(line)
                    if len(header) > 65536:
                        raise ValueError("PCD header is too large")
                data_kind = header.split(b"DATA ", 1)[1].splitlines()[0].strip().lower()
                if data_kind != b"binary":
                    raise ValueError("reference map publisher supports binary PCD only")
                fields_line = next(line for line in header.splitlines() if line.startswith(b"FIELDS "))
                fields = fields_line.split()[1:]
                sizes = next(line for line in header.splitlines() if line.startswith(b"SIZE ")).split()[1:]
                counts = next(line for line in header.splitlines() if line.startswith(b"COUNT ")).split()[1:]
                point_step = sum(int(s) * int(c) for s, c in zip(sizes, counts))
                x_index, y_index, z_index = (fields.index(name) for name in (b"x", b"y", b"z"))
                offsets = []
                offset = 0
                for size, count in zip(sizes, counts):
                    offsets.append(offset)
                    offset += int(size) * int(count)
                payload = stream.read()
            stride = max(1, len(payload) // point_step // int(self.get_parameter("max_points").value))
            points = []
            for index in range(0, len(payload) // point_step, stride):
                base = index * point_step
                points.append(struct.unpack_from("<fff", payload, base + offsets[x_index])[:3])
                # PCD layouts used by FAST-LIVO2 store x/y/z as contiguous float32 fields.
                if len(points) >= int(self.get_parameter("max_points").value):
                    break
            fields_msg = [
                PointField(name=name, offset=4 * i, datatype=PointField.FLOAT32, count=1)
                for i, name in enumerate(("x", "y", "z"))
            ]
            message = point_cloud2.create_cloud(Header(frame_id="map"), fields_msg, points)
            self.publisher.publish(message)
            self.get_logger().info("Published %d reference points from %s" % (len(points), path))
        except Exception as error:
            self.get_logger().error("Reference map unavailable: %s" % error)


def main(args=None):
    rclpy.init(args=args)
    node = ReferenceMapPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
