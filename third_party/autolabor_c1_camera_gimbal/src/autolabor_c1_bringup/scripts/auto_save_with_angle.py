#!/usr/bin/env python3
"""ROS2 版 - 每隔 N 帧自动保存一张照片，文件名带云台角度。"""
import rclpy
from rclpy.node import Node
import cv2
import os
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import rclpy.qos as qos_mod
from pantilt_camera_serial.msg import PantiltAngleInfo

class AutoSaveWithAngle(Node):
    def __init__(self):
        super().__init__('auto_save_with_angle')
        self.bridge = CvBridge()
        self.latest_image = None
        self.angle = [0.0, 0.0, 0.0]
        self.frame_count = 0
        self.save_count = 0
        self.has_angle = False
        self.save_interval = 60
        self.save_dir = "/home/lu/autolabor_c1_capture/saved_images_with_angle"
        if not os.path.exists(self.save_dir):
            os.makedirs(self.save_dir)
        self.create_subscription(Image, '/cv_camera0/image_raw', self.image_callback, 10)
        self.create_subscription(PantiltAngleInfo, '/pantilt_camera_serial0/pantilt_angle_info', self.angle_callback, rclpy.qos.qos_profile_sensor_data)
        self.get_logger().info("=" * 50)
        self.get_logger().info("Auto Save With Angle Started (ROS2)")
        self.get_logger().info(f"Save interval: {self.save_interval} frames")
        self.get_logger().info(f"Save directory: {self.save_dir}")
        self.get_logger().info("=" * 50)

    def image_callback(self, msg):
        self.latest_image = msg
        self.frame_count += 1
        if self.frame_count % self.save_interval == 0:
            self.save_image()

    def angle_callback(self, msg):
        self.angle = [msg.heading, msg.roll, msg.pitch]
        self.has_angle = True

    def save_image(self):
        if self.latest_image is None:
            return
        try:
            cv_image = self.bridge.imgmsg_to_cv2(self.latest_image, "bgr8")
            h, r, p = self.angle
            filename = os.path.join(self.save_dir, f"photo_H{h:.1f}_R{r:.1f}_P{p:.1f}_{self.frame_count:06d}.png")
            cv2.imwrite(filename, cv_image)
            self.save_count += 1
            self.get_logger().info(f"[{self.save_count}] Saved: H={h:.1f} R={r:.1f} P={p:.1f}")
        except Exception as e:
            self.get_logger().error(f"Save failed: {e}")

def main(args=None):
    rclpy.init(args=args)
    node = AutoSaveWithAngle()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
