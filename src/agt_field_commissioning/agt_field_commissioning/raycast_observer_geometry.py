from __future__ import annotations

import math
from pathlib import Path
from typing import Sequence

import yaml


Vector3 = tuple[float, float, float]
Quaternion = tuple[float, float, float, float]


def _finite_vector(values: Sequence[float], *, size: int, name: str) -> tuple[float, ...]:
    if len(values) != size:
        raise ValueError(f"{name} must contain exactly {size} values")
    converted = tuple(float(value) for value in values)
    if not all(math.isfinite(value) for value in converted):
        raise ValueError(f"{name} values must be finite")
    return converted


def load_lidar_to_imu_translation(params_file: str | Path) -> Vector3:
    path = Path(params_file).expanduser().resolve()
    if not path.is_file():
        raise ValueError(f"FAST-LIVO2 params file does not exist: {path}")

    payload = yaml.safe_load(path.read_text(encoding="utf-8"))
    if not isinstance(payload, dict):
        raise ValueError(f"FAST-LIVO2 params file must contain a YAML mapping: {path}")

    parameter_blocks = []
    for node_config in payload.values():
        if isinstance(node_config, dict):
            ros_parameters = node_config.get("ros__parameters")
            if isinstance(ros_parameters, dict):
                parameter_blocks.append(ros_parameters)

    if not parameter_blocks and isinstance(payload.get("ros__parameters"), dict):
        parameter_blocks.append(payload["ros__parameters"])

    for ros_parameters in parameter_blocks:
        extrin_calib = ros_parameters.get("extrin_calib")
        if not isinstance(extrin_calib, dict):
            continue
        translation = extrin_calib.get("extrinsic_T")
        if not isinstance(translation, (list, tuple)):
            continue
        x, y, z = _finite_vector(
            translation,
            size=3,
            name="extrin_calib.extrinsic_T",
        )
        return x, y, z

    raise ValueError(
        "FAST-LIVO2 params file is missing ros__parameters.extrin_calib.extrinsic_T"
    )


def lidar_origin_world(
    *,
    position_xyz: Sequence[float],
    orientation_xyzw: Sequence[float],
    lidar_to_imu_translation_xyz: Sequence[float],
) -> Vector3:
    px, py, pz = _finite_vector(position_xyz, size=3, name="position")
    qx, qy, qz, qw = _finite_vector(
        orientation_xyzw,
        size=4,
        name="quaternion",
    )
    tx, ty, tz = _finite_vector(
        lidar_to_imu_translation_xyz,
        size=3,
        name="lidar-to-imu translation",
    )

    norm = math.sqrt(qx * qx + qy * qy + qz * qz + qw * qw)
    if norm <= 1e-12:
        raise ValueError("quaternion norm must be non-zero")
    qx /= norm
    qy /= norm
    qz /= norm
    qw /= norm

    r00 = 1.0 - 2.0 * (qy * qy + qz * qz)
    r01 = 2.0 * (qx * qy - qz * qw)
    r02 = 2.0 * (qx * qz + qy * qw)
    r10 = 2.0 * (qx * qy + qz * qw)
    r11 = 1.0 - 2.0 * (qx * qx + qz * qz)
    r12 = 2.0 * (qy * qz - qx * qw)
    r20 = 2.0 * (qx * qz - qy * qw)
    r21 = 2.0 * (qy * qz + qx * qw)
    r22 = 1.0 - 2.0 * (qx * qx + qy * qy)

    return (
        px + r00 * tx + r01 * ty + r02 * tz,
        py + r10 * tx + r11 * ty + r12 * tz,
        pz + r20 * tx + r21 * ty + r22 * tz,
    )
