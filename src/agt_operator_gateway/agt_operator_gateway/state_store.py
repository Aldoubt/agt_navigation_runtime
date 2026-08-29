from __future__ import annotations

from copy import deepcopy
from dataclasses import dataclass
from threading import RLock
from time import time
from typing import Any, Callable


@dataclass(frozen=True)
class GatewayRuntimeSnapshot:
    gateway_revision: int
    source_revision: int
    received_at_ms: int
    robot_snapshot: dict[str, Any]
    navigation: dict[str, Any]
    mission: dict[str, Any]


class GatewayStateStore:
    def __init__(
        self,
        *,
        freshness_ms: int = 1500,
        now_ms: Callable[[], int] | None = None,
    ) -> None:
        if freshness_ms <= 0:
            raise ValueError('freshness_ms must be > 0')
        self._freshness_ms = int(freshness_ms)
        self._now_ms = now_ms or (lambda: int(time() * 1000))
        self._lock = RLock()
        self._snapshot: GatewayRuntimeSnapshot | None = None
        self._gateway_revision = 0

    @property
    def freshness_ms(self) -> int:
        return self._freshness_ms

    def update(
        self,
        *,
        robot_snapshot: dict[str, Any],
        navigation: dict[str, Any],
        mission: dict[str, Any],
        source_revision: int = 0,
        received_at_ms: int | None = None,
    ) -> GatewayRuntimeSnapshot:
        with self._lock:
            self._gateway_revision += 1
            snapshot = GatewayRuntimeSnapshot(
                gateway_revision=self._gateway_revision,
                source_revision=max(0, int(source_revision)),
                received_at_ms=int(self._now_ms() if received_at_ms is None else received_at_ms),
                robot_snapshot=deepcopy(robot_snapshot),
                navigation=deepcopy(navigation),
                mission=deepcopy(mission),
            )
            self._snapshot = snapshot
            return deepcopy(snapshot)

    def snapshot(self) -> GatewayRuntimeSnapshot | None:
        with self._lock:
            return deepcopy(self._snapshot)

    def age_ms(self, now_ms: int | None = None) -> int | None:
        with self._lock:
            if self._snapshot is None:
                return None
            now = int(self._now_ms() if now_ms is None else now_ms)
            return max(0, now - self._snapshot.received_at_ms)

    def is_runtime_connected(self, now_ms: int | None = None) -> bool:
        age = self.age_ms(now_ms)
        return age is not None and age <= self._freshness_ms
