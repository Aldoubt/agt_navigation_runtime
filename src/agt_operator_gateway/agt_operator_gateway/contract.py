from __future__ import annotations

from math import atan2
from time import time
from typing import Any

GATEWAY_API_VERSION = 'agt.operator.gateway/v1'
GATEWAY_STREAM_SCHEMA = 'agt.operator.stream/v1'
NO_ACTIVE_MISSION_ID = '__none__'


def _attr(value: Any, name: str, default: Any = None) -> Any:
    if value is None:
        return default
    if isinstance(value, dict):
        return value.get(name, default)
    return getattr(value, name, default)


def _finite_number(value: Any, default: float = 0.0) -> float:
    try:
        result = float(value)
    except (TypeError, ValueError):
        return default
    if result != result or result in (float('inf'), float('-inf')):
        return default
    return result


def _age_ms(seconds: Any) -> int | None:
    try:
        value = float(seconds)
    except (TypeError, ValueError):
        return None
    if value < 0.0 or value != value:
        return None
    return int(round(value * 1000.0))


def _timestamp_ms(state: Any) -> int:
    header = _attr(state, 'header')
    stamp = _attr(header, 'stamp')
    sec = _attr(stamp, 'sec')
    nanosec = _attr(stamp, 'nanosec')
    if isinstance(sec, int) and isinstance(nanosec, int):
        return sec * 1000 + nanosec // 1_000_000
    return int(time() * 1000)


def _yaw_from_quaternion(q: Any) -> float:
    x = _finite_number(_attr(q, 'x'))
    y = _finite_number(_attr(q, 'y'))
    z = _finite_number(_attr(q, 'z'))
    w = _finite_number(_attr(q, 'w'), 1.0)
    siny_cosp = 2.0 * (w * z + x * y)
    cosy_cosp = 1.0 - 2.0 * (y * y + z * z)
    return atan2(siny_cosp, cosy_cosp)


def _pose2d(state: Any) -> dict[str, float]:
    if not bool(_attr(state, 'localization_status_known', False)):
        return {'x': 0.0, 'y': 0.0, 'yawRad': 0.0}
    localization = _attr(state, 'localization')
    if not bool(_attr(localization, 'pose_valid', False)):
        return {'x': 0.0, 'y': 0.0, 'yawRad': 0.0}
    pose = _attr(_attr(_attr(localization, 'global_pose'), 'pose'), 'pose')
    if pose is None:
        return {'x': 0.0, 'y': 0.0, 'yawRad': 0.0}
    position = _attr(pose, 'position')
    orientation = _attr(pose, 'orientation')
    return {
        'x': _finite_number(_attr(position, 'x')),
        'y': _finite_number(_attr(position, 'y')),
        'yawRad': _yaw_from_quaternion(orientation),
    }


def _robot_mode(system_mode: Any) -> str:
    mode = int(system_mode) if isinstance(system_mode, (int, float)) else -1
    if mode == 5:
        return 'AUTO'
    if mode in (2, 3, 4):
        return 'ASSISTED'
    if mode == 1:
        return 'MANUAL'
    return 'UNKNOWN'


def _localization_state(state: Any) -> str:
    if not bool(_attr(state, 'localization_status_known', False)):
        return 'UNKNOWN'
    runtime_state = _attr(_attr(state, 'localization'), 'state', 0)
    mapping = {
        0: 'INITIALIZING',
        1: 'INITIALIZING',
        2: 'INITIALIZING',
        3: 'TRACKING',
        4: 'DEGRADED',
        5: 'DEGRADED',
        6: 'LOST',
        7: 'LOST',
    }
    return mapping.get(runtime_state, 'UNKNOWN')


def _notices(codes: Any, messages: Any) -> list[dict[str, str]]:
    code_list = list(codes or [])
    message_list = list(messages or [])
    count = max(len(code_list), len(message_list))
    result: list[dict[str, str]] = []
    for index in range(count):
        code = str(code_list[index]) if index < len(code_list) else 'UNKNOWN'
        message = str(message_list[index]) if index < len(message_list) else ''
        result.append({'code': code, 'message': message})
    return result


def _readiness(state: Any) -> tuple[str, list[dict[str, str]], list[dict[str, str]]]:
    if not bool(_attr(state, 'task_readiness_known', False)):
        return 'UNKNOWN', [], []
    readiness = _attr(state, 'task_readiness')
    blockers = _notices(
        _attr(readiness, 'blocker_codes', []),
        _attr(readiness, 'blocker_messages', []),
    )
    warnings = _notices(
        _attr(readiness, 'warning_codes', []),
        _attr(readiness, 'warning_messages', []),
    )
    if not bool(_attr(readiness, 'ready', False)):
        return 'BLOCKED', blockers, warnings
    if warnings:
        return 'DEGRADED', blockers, warnings
    return 'READY', blockers, warnings


def _active_map(state: Any) -> dict[str, str] | None:
    if not bool(_attr(state, 'active_map_known', False)):
        return None
    active_map = _attr(state, 'active_map')
    map_id = str(_attr(active_map, 'map_id', '') or '')
    version = str(_attr(active_map, 'map_version_id', '') or '')
    if not map_id or not bool(_attr(active_map, 'active', True)):
        return None
    return {'id': map_id, 'version': version}


def _mission_state(runtime_state: Any) -> str:
    mapping = {
        0: 'READY',
        1: 'READY',
        2: 'RUNNING',
        3: 'RUNNING',
        4: 'RUNNING',
        5: 'RUNNING',
        6: 'PAUSED',
        7: 'READY_TO_RESUME',
        8: 'RUNNING',
        9: 'SUCCEEDED',
        10: 'FAILED',
        11: 'CANCELED',
        12: 'FAILED',
    }
    return mapping.get(runtime_state, 'READY')


def _active_mission(state: Any) -> dict[str, str] | None:
    if not bool(_attr(state, 'mission_status_known', False)):
        return None
    mission = _attr(state, 'mission')
    mission_id = str(_attr(mission, 'mission_id', '') or '')
    if not mission_id:
        return None
    return {
        'id': mission_id,
        'name': mission_id,
        'state': _mission_state(_attr(mission, 'state', 0)),
    }


def build_capabilities() -> dict[str, bool]:
    return {
        'mapping': False,
        'localization': True,
        'navigation': True,
        'pointCloud': False,
        'globalMap': False,
        'localObstacles': False,
        'missionEdit': False,
        'inspection': False,
        'manipulator': False,
    }


def build_robot_snapshot(state: Any, *, robot_id: str, robot_name: str) -> dict[str, Any]:
    readiness, blockers, warnings = _readiness(state)
    localization = _attr(state, 'localization')
    backend_name = (
        str(_attr(localization, 'backend', '') or 'unknown') if localization else 'unknown'
    )
    return {
        'identity': {'id': robot_id, 'name': robot_name},
        'timestampMs': _timestamp_ms(state),
        'mode': _robot_mode(_attr(state, 'system_mode', 0)),
        'readiness': readiness,
        'blockers': blockers,
        'warnings': warnings,
        'pose': _pose2d(state),
        'motion': {'linearMps': 0.0, 'angularRadps': 0.0},
        'imu': {
            'rollDeg': 0.0,
            'pitchDeg': 0.0,
            'yawDeg': 0.0,
            'rateHz': 0.0,
            'ageMs': 0,
            'status': 'UNKNOWN',
        },
        'localization': {
            'state': _localization_state(state),
            'quality': None,
            'ageMs': _age_ms(_attr(state, 'localization_freshness_s')),
        },
        'backend': {
            'odometry': 'agt_odometry',
            'localization': backend_name,
            'mapping': 'disabled',
        },
        'batteryPercent': None,
        'activeMap': _active_map(state),
        'activeMission': _active_mission(state),
    }


def build_navigation_view(state: Any) -> dict[str, Any]:
    return {
        'map': None,
        'robotPose': _pose2d(state),
        'globalPath': [],
        'localTrajectory': [],
        'localObstacles': [],
        'robotFootprint': [],
        'terrainProfile': [],
        'pointCloud': None,
    }


def build_mission_view(state: Any) -> dict[str, Any]:
    if not bool(_attr(state, 'mission_status_known', False)):
        return _no_active_mission()
    mission = _attr(state, 'mission')
    mission_id = str(_attr(mission, 'mission_id', '') or '')
    if not mission_id:
        return _no_active_mission()
    total_steps = max(0, int(_attr(mission, 'total_steps', 0) or 0))
    current_index = max(0, int(_attr(mission, 'current_step_index', 0) or 0))
    runtime_state = _attr(mission, 'state', 0)
    if runtime_state == 9 and total_steps > 0:
        progress = 1.0
    elif total_steps > 0:
        progress = max(0.0, min(1.0, current_index / total_steps))
    else:
        progress = 0.0
    return {
        'id': mission_id,
        'name': mission_id,
        'state': _mission_state(runtime_state),
        'currentStep': min(total_steps, current_index + 1) if total_steps > 0 else 0,
        'totalSteps': total_steps,
        'progress': progress,
        'route': [],
        'loop': {'enabled': False, 'count': 1},
    }


def _no_active_mission() -> dict[str, Any]:
    return {
        'id': NO_ACTIVE_MISSION_ID,
        'name': 'No active mission',
        'state': 'READY',
        'currentStep': 0,
        'totalSteps': 0,
        'progress': 0.0,
        'route': [],
        'loop': {'enabled': False, 'count': 1},
    }
