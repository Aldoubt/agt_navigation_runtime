#!/usr/bin/env python3
import argparse
import json
from pathlib import Path
import sys


def validate_summary(data, require_images=True):
    errors = []
    if data.get('schema_version') != 1:
        errors.append('unsupported schema_version')
    if data.get('kind') != 'camera_gimbal_capability_acceptance':
        errors.append('unexpected acceptance kind')
    if data.get('passed') is not True:
        errors.append('top-level acceptance is not PASS')

    tests = data.get('tests')
    if not isinstance(tests, list) or not tests:
        errors.append('tests list is missing or empty')
        return errors

    names = {item.get('name') for item in tests if isinstance(item, dict)}
    required = {'invalid_goal', 'center', 'left', 'right', 'return_center'}
    missing = sorted(required - names)
    if missing:
        errors.append('missing required cases: ' + ', '.join(missing))

    for item in tests:
        if not isinstance(item, dict):
            errors.append('test entry is not an object')
            continue
        name = str(item.get('name', '<unnamed>'))
        if item.get('pass') is not True:
            errors.append(f'case {name} is not PASS')
        if name == 'invalid_goal':
            if item.get('success') is not False or int(item.get('error_code', -1)) != 100:
                errors.append('invalid_goal did not fail with ERROR_INVALID_GOAL=100')
            continue
        if item.get('success') is not True or int(item.get('error_code', -1)) != 0:
            errors.append(f'case {name} did not return success/error_code=0')
        reached = int(item.get('reached_stamp_ns', 0) or 0)
        image = int(item.get('image_stamp_ns', 0) or 0)
        if reached <= 0:
            errors.append(f'case {name} has invalid reached timestamp')
        if image <= reached:
            errors.append(f'case {name} image timestamp is not newer than reached timestamp')
        if item.get('fresh_after_reached') is not True:
            errors.append(f'case {name} freshness flag is false')
        if require_images:
            path_text = str(item.get('image_path', '') or '')
            if not path_text:
                errors.append(f'case {name} image_path is empty')
            elif not Path(path_text).is_file():
                errors.append(f'case {name} image file does not exist: {path_text}')
    return errors


def main(argv=None):
    parser = argparse.ArgumentParser(description='Strict validator for camera-gimbal acceptance JSON.')
    parser.add_argument('summary', type=Path)
    parser.add_argument('--no-require-images', action='store_true')
    parser.add_argument('--report', type=Path, default=None)
    args = parser.parse_args(argv)

    try:
        data = json.loads(args.summary.read_text(encoding='utf-8'))
    except Exception as exc:
        print(f'FAIL: cannot read summary: {exc}', file=sys.stderr)
        return 2

    errors = validate_summary(data, require_images=not args.no_require_images)
    report = {
        'source': str(args.summary),
        'passed': not errors,
        'errors': errors,
    }
    if args.report:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding='utf-8')

    if errors:
        print('FAIL: strict acceptance validation failed')
        for error in errors:
            print(f'  - {error}')
        return 1
    print('PASS: strict acceptance validation passed')
    return 0


if __name__ == '__main__':
    sys.exit(main())
