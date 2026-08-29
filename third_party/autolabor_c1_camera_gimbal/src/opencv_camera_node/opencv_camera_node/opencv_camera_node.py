#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, CameraInfo, CompressedImage
from std_msgs.msg import Header
from cv_bridge import CvBridge
import cv2

class OpenCVCameraNode(Node):
    def __init__(self):
        super().__init__('opencv_camera_node')
        self.declare_parameter('device_path', '/dev/video0')
        self.declare_parameter('image_width', 1920)
        self.declare_parameter('image_height', 1080)
        self.declare_parameter('rate', 30.0)
        self.declare_parameter('frame_id', 'camera_link')
        self.device_path = self.get_parameter('device_path').value
        self.image_width = self.get_parameter('image_width').value
        self.image_height = self.get_parameter('image_height').value
        self.rate = self.get_parameter('rate').value
        self.frame_id = self.get_parameter('frame_id').value
        self.image_pub = self.create_publisher(Image, 'image_raw', 10)
        self.compressed_pub = self.create_publisher(CompressedImage, 'image_raw/compressed', 10)
        self.info_pub = self.create_publisher(CameraInfo, 'camera_info', 10)
        self.bridge = CvBridge()
        self.cap = cv2.VideoCapture(self.device_path, cv2.CAP_V4L2)
        if not self.cap.isOpened():
            self.get_logger().error(f'Cannot open camera: {self.device_path}')
            return
        self.cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc('M', 'J', 'P', 'G'))
        self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, float(self.image_width))
        self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, float(self.image_height))
        self.cap.set(cv2.CAP_PROP_FPS, float(self.rate))
        aw = int(self.cap.get(cv2.CAP_PROP_FRAME_WIDTH))
        ah = int(self.cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
        af = self.cap.get(cv2.CAP_PROP_FPS)
        self.get_logger().info(f'Camera: {self.device_path} {aw}x{ah} @ {af:.1f} fps (MJPG)')
        self.actual_w = aw
        self.actual_h = ah
        self.timer = self.create_timer(1.0 / self.rate, self.timer_callback)
        self.frame_count = 0

    def timer_callback(self):
        ret, frame = self.cap.read()
        if not ret:
            self.get_logger().warning('Failed to grab frame', throttle_duration_sec=2.0)
            return
        stamp = self.get_clock().now().to_msg()
        header = Header(stamp=stamp, frame_id=self.frame_id)
        # Publish compressed JPEG (no decode overhead)
        msg = CompressedImage(header=header, format='jpeg')
        msg.data = cv2.imencode('.jpg', frame)[1].tobytes()
        self.compressed_pub.publish(msg)
        # Also publish raw (best-effort, may be slow at 4K)
        try:
            img_msg = self.bridge.cv2_to_imgmsg(frame, encoding='bgr8')
            img_msg.header = header
            self.image_pub.publish(img_msg)
        except Exception:
            pass
        info = CameraInfo(header=header, height=self.actual_h, width=self.actual_w)
        self.info_pub.publish(info)
        self.frame_count += 1
        if self.frame_count % 150 == 0:
            self.get_logger().info(f'Published {self.frame_count} frames')

    def destroy_node(self):
        if self.cap.isOpened():
            self.cap.release()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = OpenCVCameraNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
