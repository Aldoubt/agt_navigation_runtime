from __future__ import annotations

from dataclasses import dataclass
from typing import Mapping


STATE_UNKNOWN = 0
STATE_STARTING = 1
STATE_READY = 2
STATE_BLOCKED = 3
STATE_ERROR = 4

REQUIRED_LIFECYCLE_NODES = (
    "map_server",
    "planner_server",
    "smoother_server",
    "controller_server",
    "behavior_server",
    "bt_navigator",
    "waypoint_follower",
    "collision_monitor",
)


@dataclass(frozen=True)
class LifecycleEvidence:
    known: bool
    active: bool


@dataclass(frozen=True)
class RuntimeStatusEvidence:
    binding_known: bool
    binding_ready: bool
    binding_error: bool
    binding_blocker_codes: tuple[str, ...]
    site_id: str
    site_revision: str
    site_hash: str
    localization_pcd_sha256: str
    localization_known: bool
    localization_tracking: bool
    localization_map_id: str
    localization_map_hash: str
    lifecycles: Mapping[str, LifecycleEvidence]


@dataclass(frozen=True)
class RuntimeStatusResult:
    state: int
    localization_bound: bool
    map_identity_known: bool
    map_identity_match: bool
    blocker_codes: tuple[str, ...]
    blocker_messages: tuple[str, ...]


_MESSAGES = {
    "SITE_BINDING_UNKNOWN": "authoritative Site navigation binding has not been established",
    "SITE_BINDING_NOT_READY": "the authoritative Site navigation binding is not READY",
    "SITE_BINDING_ERROR": "the authoritative Site navigation binding is in ERROR",
    "LOCALIZATION_UNKNOWN": "localization status has not been established",
    "LOCALIZATION_NOT_TRACKING": "localization is not accepted TRACKING",
    "LOCALIZATION_IDENTITY_UNKNOWN": "localization map identity/hash has not been established",
    "LOCALIZATION_MAP_MISMATCH": "localization is not bound to the active Site localization asset",
}


def _message(code: str) -> str:
    if code in _MESSAGES:
        return _MESSAGES[code]
    if code.startswith("NAV2_") and code.endswith("_UNKNOWN"):
        return f"required Nav2 lifecycle state is unknown: {code[5:-8].lower()}"
    if code.startswith("NAV2_") and code.endswith("_INACTIVE"):
        return f"required Nav2 lifecycle node is not ACTIVE: {code[5:-9].lower()}"
    return code


def _lifecycle_code(node_name: str, suffix: str) -> str:
    return f"NAV2_{node_name.upper()}_{suffix}"


def _binding_result(evidence: RuntimeStatusEvidence) -> RuntimeStatusResult | None:
    if not evidence.binding_known:
        return RuntimeStatusResult(
            state=STATE_UNKNOWN,
            localization_bound=False,
            map_identity_known=False,
            map_identity_match=False,
            blocker_codes=("SITE_BINDING_UNKNOWN",),
            blocker_messages=(_MESSAGES["SITE_BINDING_UNKNOWN"],),
        )

    if evidence.binding_error:
        codes = ("SITE_BINDING_ERROR",) + tuple(evidence.binding_blocker_codes)
        return RuntimeStatusResult(
            state=STATE_ERROR,
            localization_bound=False,
            map_identity_known=False,
            map_identity_match=False,
            blocker_codes=codes,
            blocker_messages=tuple(_message(code) for code in codes),
        )

    if not evidence.binding_ready:
        codes = ("SITE_BINDING_NOT_READY",) + tuple(evidence.binding_blocker_codes)
        return RuntimeStatusResult(
            state=STATE_BLOCKED,
            localization_bound=False,
            map_identity_known=False,
            map_identity_match=False,
            blocker_codes=codes,
            blocker_messages=tuple(_message(code) for code in codes),
        )

    return None


def evaluate_runtime_status(evidence: RuntimeStatusEvidence) -> RuntimeStatusResult:
    """Aggregate Site binding, localization binding and required Nav2 lifecycle evidence.

    This policy is read-only. It never changes lifecycle state, publishes TF, executes
    a Mission or mutates Site assets. Unknown evidence is fail-closed and is reported
    as STARTING only after a valid authoritative Site binding exists.
    """

    binding_result = _binding_result(evidence)
    if binding_result is not None:
        return binding_result

    starting_codes: list[str] = []
    blocked_codes: list[str] = []

    map_identity_known = False
    map_identity_match = False
    localization_bound = False

    if not evidence.localization_known:
        starting_codes.append("LOCALIZATION_UNKNOWN")
    elif not evidence.localization_tracking:
        blocked_codes.append("LOCALIZATION_NOT_TRACKING")
    else:
        map_identity_known = bool(
            evidence.localization_map_id and evidence.localization_map_hash
        )
        if not map_identity_known:
            starting_codes.append("LOCALIZATION_IDENTITY_UNKNOWN")
        else:
            map_identity_match = bool(
                evidence.localization_map_id == evidence.site_id
                and evidence.localization_map_hash == evidence.localization_pcd_sha256
            )
            if not map_identity_match:
                blocked_codes.append("LOCALIZATION_MAP_MISMATCH")
            else:
                localization_bound = True

    for node_name in REQUIRED_LIFECYCLE_NODES:
        lifecycle = evidence.lifecycles.get(node_name)
        if lifecycle is None or not lifecycle.known:
            starting_codes.append(_lifecycle_code(node_name, "UNKNOWN"))
        elif not lifecycle.active:
            blocked_codes.append(_lifecycle_code(node_name, "INACTIVE"))

    if blocked_codes:
        codes = tuple(blocked_codes + starting_codes)
        state = STATE_BLOCKED
    elif starting_codes:
        codes = tuple(starting_codes)
        state = STATE_STARTING
    else:
        codes = ()
        state = STATE_READY

    return RuntimeStatusResult(
        state=state,
        localization_bound=localization_bound,
        map_identity_known=map_identity_known,
        map_identity_match=map_identity_match,
        blocker_codes=codes,
        blocker_messages=tuple(_message(code) for code in codes),
    )
