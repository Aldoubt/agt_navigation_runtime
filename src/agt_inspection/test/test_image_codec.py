import pytest
from sensor_msgs.msg import Image

from agt_inspection.image_codec import ImageCodecError, encode_jpeg, encode_png


def _image(encoding: str, width: int, height: int, data: bytes, step: int) -> Image:
    message = Image()
    message.width = width
    message.height = height
    message.encoding = encoding
    message.is_bigendian = 0
    message.step = step
    message.data = list(data)
    return message


def test_encode_jpeg_accepts_rgb8_and_bgr8():
    rgb = _image(
        "rgb8",
        2,
        2,
        bytes(
            [
                255,
                0,
                0,
                0,
                255,
                0,
                0,
                0,
                255,
                255,
                255,
                255,
            ]
        ),
        6,
    )
    bgr = _image("bgr8", 2, 2, bytes(reversed(bytes(rgb.data))), 6)

    assert encode_jpeg(rgb).startswith(b"\xff\xd8")
    assert encode_jpeg(bgr).startswith(b"\xff\xd8")


def test_encode_png_accepts_mono8_losslessly():
    mono = _image("mono8", 2, 2, bytes([0, 64, 128, 255]), 2)

    assert encode_png(mono).startswith(b"\x89PNG\r\n\x1a\n")


def test_codec_rejects_unsupported_encoding():
    unsupported = _image("16UC1", 1, 1, bytes([0, 0]), 2)

    with pytest.raises(ImageCodecError, match="unsupported image encoding"):
        encode_png(unsupported)
