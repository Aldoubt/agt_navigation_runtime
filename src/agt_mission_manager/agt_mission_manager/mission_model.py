from __future__ import annotations

from dataclasses import dataclass, field
from enum import IntEnum
from pathlib import PurePosixPath
import re


SCHEMA_VERSION = 1
SAFE_COMPONENT_RE = re.compile(r"^[A-Za-z0-9][A-Za-z0-9._-]{0,127}$")
SHA256_RE = re.compile(r"^sha256:[0-9a-f]{64}$")


class MissionError(ValueError):
    pass


class StepType(IntEnum):
    UNKNOWN = 0
    WAYPOINT_TASK = 1
    WAIT_DURATION = 2
    WAIT_EVENT = 3
    INSPECTION_TASK = 4
    RETURN_HOME = 5


class MissionState(IntEnum):
    IDLE = 0
    VALIDATING = 1
    RUNNING = 2
    WAITING_DURATION = 3
    WAITING_EVENT = 4
    PAUSING = 5
    PAUSED = 6
    RESUMING = 7
    CANCELING = 8
    SUCCEEDED = 9
    FAILED = 10
    CANCELED = 11
    INTERRUPTED = 12


class MissionErrorCode(IntEnum):
    NONE = 0
    INVALID_MISSION = 1
    MAP_MISMATCH = 2
    READINESS_LOST = 3
    LOCALIZATION_LOST = 4
    CHILD_REJECTED = 5
    CHILD_FAILED = 6
    EVENT_TIMEOUT = 7
    CANCELED = 8
    RESUME_BLOCKED = 9
    INTERNAL = 255


@dataclass(frozen=True)
class MapBinding:
    map_id: str
    map_version_id: str
    manifest_sha256: str


@dataclass(frozen=True)
class MissionStep:
    id: str
    type: StepType
    task_file: str = ""
    duration_s: float = 0.0
    event_type: str = ""
    event_source: str = ""
    correlation_id: str = ""
    timeout_s: float = 0.0
    inspection_task_id: str = ""
    inspection_task_revision: int = 0
    expected_content_sha256: str = ""
    task_group_id: str = ""
    task_group_revision: int = 0


@dataclass(frozen=True)
class Mission:
    mission_id: str
    mission_version: str
    content_sha256: str
    map_binding: MapBinding
    steps: tuple[MissionStep, ...]
    schema_version: int = SCHEMA_VERSION


@dataclass(frozen=True)
class MissionEventRecord:
    stamp_s: float
    event_type: str
    source: str = ""
    correlation_id: str = ""
    mission_id: str = ""


@dataclass(frozen=True)
class GateSnapshot:
    map_id: str = ""
    map_version_id: str = ""
    manifest_sha256: str = ""
    localization_ready: bool = False
    task_ready: bool = False
    blocker_codes: tuple[str, ...] = ()
    blocker_messages: tuple[str, ...] = ()

    def validate(self, binding: MapBinding) -> tuple[bool, MissionErrorCode, str]:
        if (
            self.map_id != binding.map_id
            or self.map_version_id != binding.map_version_id
            or self.manifest_sha256 != binding.manifest_sha256
        ):
            return False, MissionErrorCode.MAP_MISMATCH, "active map binding does not match mission"
        if not self.localization_ready:
            return False, MissionErrorCode.LOCALIZATION_LOST, "localization is not accepted and fresh"
        if not self.task_ready:
            return False, MissionErrorCode.READINESS_LOST, "TaskReadiness is stale or blocked"
        return True, MissionErrorCode.NONE, "mission gates are ready"


@dataclass
class MissionRuntimeStatus:
    state: MissionState = MissionState.IDLE
    mission_id: str = ""
    mission_version: str = ""
    content_sha256: str = ""
    map_id: str = ""
    map_version_id: str = ""
    map_manifest_sha256: str = ""
    current_step_index: int = 0
    total_steps: int = 0
    current_step_id: str = ""
    current_step_type: StepType = StepType.UNKNOWN
    current_waypoint: int = 0
    total_waypoints: int = 0
    step_elapsed_s: float = 0.0
    step_remaining_s: float = 0.0
    error_code: MissionErrorCode = MissionErrorCode.NONE
    blocker_codes: list[str] = field(default_factory=list)
    blocker_messages: list[str] = field(default_factory=list)
    message: str = "idle"

    @classmethod
    def for_mission(cls, mission: Mission) -> "MissionRuntimeStatus":
        return cls(
            state=MissionState.VALIDATING,
            mission_id=mission.mission_id,
            mission_version=mission.mission_version,
            content_sha256=mission.content_sha256,
            map_id=mission.map_binding.map_id,
            map_version_id=mission.map_binding.map_version_id,
            map_manifest_sha256=mission.map_binding.manifest_sha256,
            total_steps=len(mission.steps),
            message="validating mission",
        )


def validate_component(value: object, name: str) -> str:
    if not isinstance(value, str) or not SAFE_COMPONENT_RE.fullmatch(value):
        raise MissionError(f"{name} must be a portable identifier")
    return value


def validate_sha256(value: object, name: str) -> str:
    if not isinstance(value, str) or not SHA256_RE.fullmatch(value):
        raise MissionError(f"{name} must be sha256:<64 lowercase hex>")
    return value


def validate_task_path(value: object) -> str:
    if not isinstance(value, str) or not value or "\\" in value:
        raise MissionError("task_file must be a relative POSIX path")
    path = PurePosixPath(value)
    if path.is_absolute() or any(part in {"", ".", ".."} for part in path.parts):
        raise MissionError("task_file must not be absolute or contain dot segments")
    if not path.parts or path.parts[0] != "tasks" or path.suffix.lower() != ".json":
        raise MissionError("task_file must reference a JSON asset below tasks/")
    return path.as_posix()
