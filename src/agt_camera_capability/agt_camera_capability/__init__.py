from .interfaces.camera import CaptureRequest, CaptureResult, CameraBackend
from .strategy import CaptureStrategy, CaptureView, FixedOverviewCaptureStrategy


def __getattr__(name):
    # Keep strategy/backend utilities importable in non-ROS tooling. The
    # capability itself is loaded lazily because it requires generated ROS srv
    # Python modules.
    if name == "CameraCapability":
        from .capability.camera_capability import CameraCapability
        return CameraCapability
    raise AttributeError(name)

__all__ = [
    "CaptureRequest", "CaptureResult", "CameraBackend", "CameraCapability",
    "CaptureStrategy", "CaptureView", "FixedOverviewCaptureStrategy",
]
