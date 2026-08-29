from __future__ import annotations

from math import isfinite
from typing import Any

EXPECTED_API_VERSION = 'agt.operator.gateway/v1'
EXPECTED_ROBOT_STATE_TYPE = 'agt_interfaces/msg/RobotState'


def _record(value: Any) -> dict[str, Any] | None:
    return value if isinstance(value, dict) else None


def _api_error(label: str, payload: Any) -> str | None:
    record = _record(payload)
    if record is None:
        return f'{label} response must be a JSON object'
    version = record.get('apiVersion')
    if version != EXPECTED_API_VERSION:
        return (
            f'{label} apiVersion mismatch: expected {EXPECTED_API_VERSION}, '
            f'got {version!r}'
        )
    return None


def validate_robot_state_topic_type(actual_type: str) -> list[str]:
    actual = str(actual_type).strip()
    if actual == EXPECTED_ROBOT_STATE_TYPE:
        return []
    return [
        f'robot state topic type mismatch: expected {EXPECTED_ROBOT_STATE_TYPE}, got {actual}'
    ]


def classify_write_probe_status(status_code: int) -> tuple[str, list[str]]:
    status = int(status_code)
    if status == 401:
        return 'enabled_auth_required', []
    if status == 403:
        return 'disabled', []
    return (
        'unsafe_or_unexpected',
        [f'unauthenticated write probe returned unexpected HTTP {status}'],
    )


def validate_gateway_payloads(
    health: Any,
    capabilities: Any,
    robot: Any,
    mission: Any,
) -> list[str]:
    errors: list[str] = []
    payloads = {
        'health': health,
        'capabilities': capabilities,
        'robot': robot,
        'mission': mission,
    }
    for label, payload in payloads.items():
        error = _api_error(label, payload)
        if error:
            errors.append(error)

    health_record = _record(health)
    if health_record is not None:
        runtime = _record(health_record.get('runtime'))
        if runtime is None:
            errors.append('health.runtime must be an object')
        elif runtime.get('connected') is not True:
            errors.append('gateway runtime is not connected')

    capabilities_record = _record(capabilities)
    if capabilities_record is not None:
        values = _record(capabilities_record.get('capabilities'))
        if values is None:
            errors.append('capabilities.capabilities must be an object')
        else:
            for required in ('localization', 'navigation'):
                if values.get(required) is not True:
                    errors.append(f'capability {required} is not enabled')

    robot_record = _record(robot)
    if robot_record is not None:
        snapshot = _record(robot_record.get('snapshot'))
        identity = _record(snapshot.get('identity')) if snapshot else None
        robot_id = identity.get('id') if identity else None
        if not isinstance(robot_id, str) or not robot_id:
            errors.append('snapshot.identity.id must be a non-empty string')

        navigation = _record(robot_record.get('navigation'))
        pose = _record(navigation.get('robotPose')) if navigation else None
        if pose is None:
            errors.append('navigation.robotPose must be an object')
        else:
            for field in ('x', 'y', 'yawRad'):
                value = pose.get(field)
                if not isinstance(value, (int, float)) or not isfinite(float(value)):
                    errors.append(f'navigation.robotPose.{field} must be finite')

    mission_record = _record(mission)
    if mission_record is not None:
        mission_view = _record(mission_record.get('mission'))
        mission_id = mission_view.get('id') if mission_view else None
        if not isinstance(mission_id, str) or not mission_id:
            errors.append('mission.id must be a non-empty string')

    return errors
