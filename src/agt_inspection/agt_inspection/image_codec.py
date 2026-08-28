from __future__ import annotations

import cv2
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image


class ImageCodecError(ValueError):
    """Raised when a ROS Image cannot be safely encoded as evidence."""


_SUPPORTED_ENCODINGS = {"rgb8", "bgr8", "mono8"}
_BRIDGE = CvBridge()


def _validate(image: Image) -> None:
    encoding = str(image.encoding)
    if encoding not in _SUPPORTED_ENCODINGS:
        raise ImageCodecError(f"unsupported image encoding: {encoding}")
    if int(image.width) <= 0 or int(image.height) <= 0:
        raise ImageCodecError("image width and height must be positive")

    channels = 1 if encoding == "mono8" else 3
    minimum_step = int(image.width) * channels
    if int(image.step) < minimum_step:
        raise ImageCodecError(
            f"image step is too small for {encoding}: {image.step} < {minimum_step}"
        )
    expected_minimum = int(image.step) * int(image.height)
    if len(image.data) < expected_minimum:
        raise ImageCodecError(
            f"image payload is too short: {len(image.data)} < {expected_minimum}"
        )


def _cv_image(image: Image):
    _validate(image)
    try:
        frame = _BRIDGE.imgmsg_to_cv2(image, desired_encoding="passthrough")
    except CvBridgeError as exc:
        raise ImageCodecError(f"failed to convert ROS image: {exc}") from exc

    if image.encoding == "rgb8":
        frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
    return frame


def _encode(image: Image, suffix: str, params: list[int] | None = None) -> bytes:
    frame = _cv_image(image)
    ok, encoded = cv2.imencode(suffix, frame, params or [])
    if not ok:
        raise ImageCodecError(f"failed to encode image as {suffix}")
    return encoded.tobytes()


def encode_jpeg(image: Image, quality: int = 95) -> bytes:
    quality = int(quality)
    if not 1 <= quality <= 100:
        raise ImageCodecError("jpeg quality must be in [1, 100]")
    return _encode(image, ".jpg", [cv2.IMWRITE_JPEG_QUALITY, quality])


def encode_png(image: Image) -> bytes:
    return _encode(image, ".png", [cv2.IMWRITE_PNG_COMPRESSION, 3])
