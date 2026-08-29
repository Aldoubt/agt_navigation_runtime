from __future__ import annotations

from dataclasses import dataclass
from typing import Protocol


@dataclass(frozen=True)
class MissionCommandResult:
    accepted: bool
    error_code: int = 0
    message: str = ''
    unavailable: bool = False
    timed_out: bool = False

    @classmethod
    def accepted_result(cls, message: str = 'accepted') -> 'MissionCommandResult':
        return cls(True, error_code=0, message=message)

    @classmethod
    def rejected_result(cls, error_code: int, message: str) -> 'MissionCommandResult':
        return cls(False, error_code=int(error_code), message=message)

    @classmethod
    def unavailable_result(cls, message: str) -> 'MissionCommandResult':
        return cls(False, error_code=0, message=message, unavailable=True)

    @classmethod
    def timeout_result(cls, message: str) -> 'MissionCommandResult':
        return cls(False, error_code=0, message=message, timed_out=True)


class MissionCommandPort(Protocol):
    def start(
        self,
        mission_id: str,
        mission_version: str,
        expected_hash: str,
    ) -> MissionCommandResult:
        ...

    def pause(self, mission_id: str) -> MissionCommandResult:
        ...

    def resume(self, mission_id: str) -> MissionCommandResult:
        ...

    def cancel(self, mission_id: str) -> MissionCommandResult:
        ...
