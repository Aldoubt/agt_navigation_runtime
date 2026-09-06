from __future__ import annotations

from abc import ABC, abstractmethod
from dataclasses import dataclass
from typing import Any


@dataclass(frozen=True)
class CaptureView:
    """One view planned by a strategy; angles are radians."""

    yaw: float
    pitch: float = 0.0
    roll: float = 0.0
    name: str = "overview"


class CaptureStrategy(ABC):
    """Plan views only; camera execution remains owned by CameraCapability."""

    @abstractmethod
    def generate_views(self, waypoint: Any) -> list[CaptureView]:
        raise NotImplementedError
