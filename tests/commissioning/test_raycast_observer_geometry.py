import math
from pathlib import Path

import pytest

from agt_field_commissioning.raycast_observer_geometry import (
    lidar_origin_world,
    load_lidar_to_imu_translation,
)


def test_load_lidar_to_imu_translation_from_fast_livo_ros_yaml(tmp_path: Path):
    params = tmp_path / "lio.yaml"
    params.write_text(
        "/**:\n"
        "  ros__parameters:\n"
        "    extrin_calib:\n"
        "      extrinsic_T: [0.011, 0.02329, -0.04412]\n",
        encoding="utf-8",
    )

    assert load_lidar_to_imu_translation(params) == pytest.approx(
        (0.011, 0.02329, -0.04412)
    )


def test_lidar_origin_world_applies_translation_in_imu_orientation():
    translation = (0.011, 0.02329, -0.04412)

    identity = lidar_origin_world(
        position_xyz=(1.0, 2.0, 3.0),
        orientation_xyzw=(0.0, 0.0, 0.0, 1.0),
        lidar_to_imu_translation_xyz=translation,
    )
    assert identity == pytest.approx((1.011, 2.02329, 2.95588))

    half = math.sqrt(0.5)
    yaw_90 = lidar_origin_world(
        position_xyz=(1.0, 2.0, 3.0),
        orientation_xyzw=(0.0, 0.0, half, half),
        lidar_to_imu_translation_xyz=(0.05, 0.0, 0.0),
    )
    assert yaw_90 == pytest.approx((1.0, 2.05, 3.0), abs=1e-9)


def test_lidar_origin_world_normalizes_quaternion_and_rejects_invalid_inputs():
    normalized = lidar_origin_world(
        position_xyz=(0.0, 0.0, 0.0),
        orientation_xyzw=(0.0, 0.0, 0.0, 2.0),
        lidar_to_imu_translation_xyz=(0.1, 0.2, 0.3),
    )
    assert normalized == pytest.approx((0.1, 0.2, 0.3))

    with pytest.raises(ValueError, match="quaternion"):
        lidar_origin_world(
            position_xyz=(0.0, 0.0, 0.0),
            orientation_xyzw=(0.0, 0.0, 0.0, 0.0),
            lidar_to_imu_translation_xyz=(0.0, 0.0, 0.0),
        )

    with pytest.raises(ValueError, match="finite"):
        lidar_origin_world(
            position_xyz=(float("nan"), 0.0, 0.0),
            orientation_xyzw=(0.0, 0.0, 0.0, 1.0),
            lidar_to_imu_translation_xyz=(0.0, 0.0, 0.0),
        )
