from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class MapBinding:
    map_id: str
    map_version_id: str
    manifest_sha256: str


@dataclass(frozen=True)
class NavigationBinding:
    task_group_id: str
    task_revision: int
    expected_content_sha256: str


@dataclass(frozen=True)
class StabilizationPolicy:
    linear_velocity_max_mps: float
    angular_velocity_max_radps: float
    stable_duration_s: float
    timeout_s: float


@dataclass(frozen=True)
class GimbalPose:
    pan_rad: float
    tilt_rad: float
    timeout_s: float
    settle_duration_s: float


@dataclass(frozen=True)
class InspectionView:
    id: str
    gimbal: GimbalPose


@dataclass(frozen=True)
class CameraPolicy:
    camera_id: str
    capture_count: int
    capture_interval_s: float


@dataclass(frozen=True)
class VisionPolicy:
    task_id: str
    model_profile: str
    minimum_confidence: float
    timeout_s: float


@dataclass(frozen=True)
class RetryPolicy:
    navigation: int
    gimbal: int
    capture: int
    inference: int


@dataclass(frozen=True)
class AggregationPolicy:
    enabled: bool
    aggregation_profile: str


@dataclass(frozen=True)
class InspectionPoint:
    id: str
    navigation: NavigationBinding
    stabilization: StabilizationPolicy
    gimbal: GimbalPose | None
    camera: CameraPolicy
    vision: VisionPolicy
    retry: RetryPolicy
    views: tuple[InspectionView, ...] = ()
    aggregation: AggregationPolicy | None = None


@dataclass(frozen=True)
class InspectionTask:
    inspection_task_id: str
    name: str
    description: str
    revision: int
    content_sha256: str
    map_binding: MapBinding
    points: tuple[InspectionPoint, ...]
    count_target: str = ""
    schema_version: int = 1
