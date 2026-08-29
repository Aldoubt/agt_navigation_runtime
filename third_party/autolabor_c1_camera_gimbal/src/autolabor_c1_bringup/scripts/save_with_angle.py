#!/usr/bin/env python3
"""ROS2 版 - 拍一张照片并保存，文件名带云台角度。"""
import rclpy
from rclpy.node import Node
import cv2
import time
import os
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import rclpy.qos as qos_mod
from pantilt_camera_serial.msg import PantiltAngleInfo

class SaveImageWithAngle(Node):
    def __init__(self):
        super().__init__('save_with_angle')
        self.bridge = CvBridge()
        self.latest_image = None
        self.angle = [0.0, 0.0, 0.0]
        self.has_angle = False
        self.save_dir = "/home/lu/autolabor_c1_capture/saved_images_with_angle"
        if not os.path.exists(self.save_dir):
            os.makedirs(self.save_dir)
        self.create_subscription(Image, '/cv_camera0/image_raw', self.image_callback, 10)
        self.create_subscription(PantiltAngleInfo, '/pantilt_camera_serial0/pantilt_angle_info', self.angle_callback, rclpy.qos.qos_profile_sensor_data)
        self.get_logger().info("Waiting for image and angle data...")

    def image_callback(self, msg):
        self.latest_image = msg

    def angle_callback(self, msg):
        self.angle = [msg.heading, msg.roll, msg.pitch]
        self.has_angle = True

    def save_image(self):
        if self.latest_image is None:
            self.get_logger().warning("No image received yet")
            return
        try:
            cv_image = self.bridge.imgmsg_to_cv2(self.latest_image, "bgr8")
            h, r, p = self.angle
            timestamp = int(time.time())
            filename = os.path.join(self.save_dir, f"photo_H{h:.1f}_R{r:.1f}_P{p:.1f}_{timestamp}.png")
            cv2.imwrite(filename, cv_image)
            self.get_logger().info(f"Saved: {filename}")
            self.get_logger().info(f"Angle: Heading={h:.1f}, Roll={r:.1f}, Pitch={p:.1f}")
        except Exception as e:
            self.get_logger().error(f"Save failed: {e}")

def main(args=None):
    rclpy.init(args=args)
    node = SaveImageWithAngle()
    start = time.time()
    while time.time() - start < 2.0 and rclpy.ok():
        rclpy.spin_once(node, timeout_sec=0.1)
    node.save_image()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
