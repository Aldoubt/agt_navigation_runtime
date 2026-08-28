from __future__ import annotations

from dataclasses import dataclass


STATE_UNKNOWN = 0
STATE_OK = 1
STATE_WARN = 2
STATE_ERROR = 3


@dataclass(frozen=True)
class ComponentEvidence:
    component_id: str
    required: bool
    known: bool
    state: int


@dataclass(frozen=True)
class Evidence:
    health_known: bool
    health_ok: bool
    map_known: bool
    map_ready: bool
    map_id: str
    map_version_id: str
    localization_known: bool
    localization_tracking: bool
    localization_map_id: str
    safety_known: bool
    motion_enabled: bool
    estop_latched: bool
    chassis_known: bool
    chassis_connected: bool


@dataclass(frozen=True)
class ReadinessResult:
    ready: bool
    blocker_codes: tuple[str, ...]
    blocker_messages: tuple[str, ...]
    map_id: str
    map_version_id: str


_MESSAGES = {
    "SYSTEM_HEALTH_UNKNOWN": "required system health has not been established",
    "SYSTEM_HEALTH_BLOCKED": "one or more required runtime components are unhealthy",
    "ACTIVE_MAP_UNKNOWN": "no authoritative active map has been received",
    "ACTIVE_MAP_NOT_READY": "the active map is not valid and READY",
    "LOCALIZATION_UNKNOWN": "localization status has not been established",
    "LOCALIZATION_NOT_TRACKING": "localization is not accepted TRACKING",
    "LOCALIZATION_MAP_MISMATCH": "localization map identity does not match the active map",
    "SAFETY_UNKNOWN": "safety status has not been established",
    "MOTION_DISABLED": "motion is not explicitly enabled by the safety controller",
    "ESTOP_LATCHED": "the emergency-stop latch is active",
    "CHASSIS_UNKNOWN": "chassis connectivity has not been established",
    "CHASSIS_DISCONNECTED": "the chassis backend is disconnected",
}


def overall_health_state(components: tuple[ComponentEvidence, ...]) -> int:
    if not components:
        return STATE_UNKNOWN

    required = tuple(component for component in components if component.required)
    if not required:
        return STATE_UNKNOWN

    if any(not component.known for component in required):
        return STATE_ERROR
    if any(component.state == STATE_ERROR for component in required):
        return STATE_ERROR
    if any(component.state == STATE_WARN for component in required):
        return STATE_WARN

    optional = tuple(component for component in components if not component.required)
    if any(
        component.known and component.state in (STATE_WARN, STATE_ERROR)
        for component in optional
    ):
        return STATE_WARN
    return STATE_OK


def evaluate_navigation_readiness(evidence: Evidence) -> ReadinessResult:
    blockers: list[str] = []

    if not evidence.health_known:
        blockers.append("SYSTEM_HEALTH_UNKNOWN")
    elif not evidence.health_ok:
        blockers.append("SYSTEM_HEALTH_BLOCKED")

    if not evidence.map_known:
        blockers.append("ACTIVE_MAP_UNKNOWN")
    elif not evidence.map_ready:
        blockers.append("ACTIVE_MAP_NOT_READY")

    if not evidence.localization_known:
        blockers.append("LOCALIZATION_UNKNOWN")
    elif not evidence.localization_tracking:
        blockers.append("LOCALIZATION_NOT_TRACKING")
    elif (
        evidence.map_known
        and evidence.map_id
        and evidence.localization_map_id
        and evidence.localization_map_id != evidence.map_id
    ):
        blockers.append("LOCALIZATION_MAP_MISMATCH")

    if not evidence.safety_known:
        blockers.append("SAFETY_UNKNOWN")
    elif evidence.estop_latched:
        blockers.append("ESTOP_LATCHED")
    elif not evidence.motion_enabled:
        blockers.append("MOTION_DISABLED")

    if not evidence.chassis_known:
        blockers.append("CHASSIS_UNKNOWN")
    elif not evidence.chassis_connected:
        blockers.append("CHASSIS_DISCONNECTED")

    return ReadinessResult(
        ready=not blockers,
        blocker_codes=tuple(blockers),
        blocker_messages=tuple(_MESSAGES[code] for code in blockers),
        map_id=evidence.map_id if evidence.map_known else "",
        map_version_id=evidence.map_version_id if evidence.map_known else "",
    )
