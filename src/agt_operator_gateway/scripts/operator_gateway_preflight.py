#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
from pathlib import Path
import subprocess
import sys
from time import time
from typing import Any
from urllib.error import HTTPError, URLError
from urllib.request import Request, urlopen

from agt_operator_gateway.preflight import (
    EXPECTED_API_VERSION,
    validate_gateway_payloads,
    validate_robot_state_topic_type,
)


def _http_json(base_url: str, path: str, timeout_s: float) -> dict[str, Any]:
    url = f"{base_url.rstrip('/')}{path}"
    request = Request(url, headers={'Accept': 'application/json'})
    try:
        with urlopen(request, timeout=timeout_s) as response:
            status = int(getattr(response, 'status', 200))
            if status != 200:
                raise RuntimeError(f'HTTP {status} from {path}')
            return json.loads(response.read().decode('utf-8'))
    except HTTPError as error:
        raise RuntimeError(f'HTTP {error.code} from {path}') from error
    except URLError as error:
        raise RuntimeError(f'cannot reach {path}: {error.reason}') from error


def _run(command: list[str], timeout_s: float) -> subprocess.CompletedProcess[str]:
    try:
        return subprocess.run(
            command,
            capture_output=True,
            text=True,
            timeout=timeout_s,
            check=False,
        )
    except FileNotFoundError as error:
        raise RuntimeError(f'command not found: {command[0]}') from error
    except subprocess.TimeoutExpired as error:
        raise RuntimeError(f'command timed out: {" ".join(command)}') from error


def _check_ros(topic: str, timeout_s: float) -> tuple[list[dict[str, Any]], list[str]]:
    checks: list[dict[str, Any]] = []
    errors: list[str] = []

    type_result = _run(['ros2', 'topic', 'type', topic], timeout_s)
    actual_type = type_result.stdout.strip()
    type_errors = (
        validate_robot_state_topic_type(actual_type)
        if type_result.returncode == 0
        else [f'ros2 topic type failed: {type_result.stderr.strip()}']
    )
    checks.append({
        'name': 'robot_state_topic_type',
        'ok': not type_errors,
        'actual': actual_type,
    })
    errors.extend(type_errors)

    echo_result = _run(['ros2', 'topic', 'echo', topic, '--once'], timeout_s)
    echo_ok = echo_result.returncode == 0 and bool(echo_result.stdout.strip())
    checks.append({
        'name': 'robot_state_message',
        'ok': echo_ok,
        'detail': 'received one RobotState sample' if echo_ok else echo_result.stderr.strip(),
    })
    if not echo_ok:
        errors.append('no RobotState sample received within preflight timeout')

    return checks, errors


def _check_http(gateway: str, timeout_s: float) -> tuple[list[dict[str, Any]], list[str]]:
    paths = {
        'health': '/api/v1/health',
        'capabilities': '/api/v1/capabilities',
        'robot': '/api/v1/robot',
        'mission': '/api/v1/mission',
    }
    payloads: dict[str, dict[str, Any]] = {}
    checks: list[dict[str, Any]] = []
    errors: list[str] = []

    for name, path in paths.items():
        try:
            payload = _http_json(gateway, path, timeout_s)
            payloads[name] = payload
            checks.append({
                'name': f'gateway_{name}',
                'ok': True,
                'apiVersion': payload.get('apiVersion'),
            })
        except (RuntimeError, ValueError, json.JSONDecodeError) as error:
            checks.append({'name': f'gateway_{name}', 'ok': False, 'detail': str(error)})
            errors.append(f'{name} endpoint failed: {error}')

    if len(payloads) == len(paths):
        contract_errors = validate_gateway_payloads(
            payloads['health'],
            payloads['capabilities'],
            payloads['robot'],
            payloads['mission'],
        )
        checks.append({
            'name': 'gateway_contract',
            'ok': not contract_errors,
            'expectedApiVersion': EXPECTED_API_VERSION,
        })
        errors.extend(contract_errors)

    return checks, errors


def _write_report(path: str | None, report: dict[str, Any]) -> None:
    encoded = json.dumps(report, ensure_ascii=False, indent=2, sort_keys=True)
    if path:
        destination = Path(path)
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_text(encoded + '\n', encoding='utf-8')
    print(encoded)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description='Field preflight for AGT operator gateway before HMI/vehicle acceptance.'
    )
    parser.add_argument('--gateway', default='http://127.0.0.1:8765')
    parser.add_argument('--robot-state-topic', default='/agt/system/robot_state')
    parser.add_argument('--timeout-s', type=float, default=5.0)
    parser.add_argument('--skip-ros', action='store_true')
    parser.add_argument('--json-output', default='')
    args = parser.parse_args(argv)

    if args.timeout_s <= 0.0:
        parser.error('--timeout-s must be > 0')

    checks: list[dict[str, Any]] = []
    errors: list[str] = []

    if not args.skip_ros:
        try:
            ros_checks, ros_errors = _check_ros(args.robot_state_topic, args.timeout_s)
            checks.extend(ros_checks)
            errors.extend(ros_errors)
        except RuntimeError as error:
            checks.append({'name': 'ros_environment', 'ok': False, 'detail': str(error)})
            errors.append(str(error))

    http_checks, http_errors = _check_http(args.gateway, args.timeout_s)
    checks.extend(http_checks)
    errors.extend(http_errors)

    report = {
        'schema': 'agt.operator.gateway.preflight/v1',
        'timestampMs': int(time() * 1000),
        'gateway': args.gateway,
        'robotStateTopic': args.robot_state_topic,
        'rosChecksSkipped': bool(args.skip_ros),
        'success': not errors,
        'checks': checks,
        'errors': errors,
    }
    _write_report(args.json_output or None, report)
    return 0 if not errors else 1


if __name__ == '__main__':
    sys.exit(main())
