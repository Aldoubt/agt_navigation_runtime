from __future__ import annotations

from collections.abc import Mapping
from typing import Any, Protocol


class TaskAuthoringPort(Protocol):
    """Gateway-facing adapter for Site-bound task authoring and planner preview."""

    def context(self) -> Mapping[str, Any]: ...

    def map_image(self) -> bytes: ...

    def preview(self, payload: Mapping[str, Any]) -> Mapping[str, Any]: ...

    def save(self, task_id: str, payload: Mapping[str, Any]) -> Mapping[str, Any]: ...


class RunControlPort(Protocol):
    """Gateway-facing adapter for read-only readiness and explicit relocalization."""

    def readiness(self) -> Mapping[str, Any]: ...

    def relocalize(self) -> Mapping[str, Any]: ...
