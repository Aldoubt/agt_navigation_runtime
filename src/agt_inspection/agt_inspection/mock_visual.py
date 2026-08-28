from __future__ import annotations

import hashlib
from typing import Any


MOCK_MODEL_ID = "mock-vision"
MOCK_MODEL_VERSION = "1"
MOCK_WEIGHTS_SHA256 = "sha256:" + hashlib.sha256(
    b"agt-inspection-mock-vision-v1"
).hexdigest()


def build_mock_level1_payload() -> dict[str, Any]:
    """Return the deterministic canonical Level-1 payload used by ROS mocks."""
    return {
        "schema_version": 1,
        "count_target": "litchi_flower",
        "model": {
            "model_id": MOCK_MODEL_ID,
            "model_version": MOCK_MODEL_VERSION,
            "weights_sha256": MOCK_WEIGHTS_SHA256,
        },
        "raw_count": 3,
        "instances": [
            {"local_instance_id": "I0001", "confidence": 0.93},
            {"local_instance_id": "I0002", "confidence": 0.91},
            {"local_instance_id": "I0003", "confidence": 0.89},
        ],
        "quality": {
            "valid": True,
            "reason": "",
        },
        "warnings": [],
    }
