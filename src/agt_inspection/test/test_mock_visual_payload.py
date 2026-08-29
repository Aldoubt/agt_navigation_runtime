import json

from agt_inspection.mock_visual import (
    MOCK_MODEL_ID,
    MOCK_MODEL_VERSION,
    MOCK_WEIGHTS_SHA256,
    build_mock_level1_payload,
)
from agt_inspection.vision_result import parse_level1_result


def test_mock_level1_payload_is_deterministic_and_canonical():
    payload = build_mock_level1_payload()

    assert payload == build_mock_level1_payload()
    assert payload["schema_version"] == 1
    assert payload["model"] == {
        "model_id": MOCK_MODEL_ID,
        "model_version": MOCK_MODEL_VERSION,
        "weights_sha256": MOCK_WEIGHTS_SHA256,
    }
    assert payload["raw_count"] == 3
    assert [item["local_instance_id"] for item in payload["instances"]] == [
        "I0001",
        "I0002",
        "I0003",
    ]
    assert isinstance(payload["quality"], dict)
    assert payload["quality"]["valid"] is True
    assert payload["warnings"] == []

    validated = parse_level1_result(
        json.dumps(payload, separators=(",", ":")),
        model_id=MOCK_MODEL_ID,
        model_version=MOCK_MODEL_VERSION,
        weights_sha256=MOCK_WEIGHTS_SHA256,
    )
    assert validated.raw_count == 3
    assert validated.weights_sha256 == MOCK_WEIGHTS_SHA256


def test_mock_weights_hash_is_canonical_sha256():
    assert MOCK_WEIGHTS_SHA256.startswith("sha256:")
    assert len(MOCK_WEIGHTS_SHA256) == len("sha256:") + 64
    assert MOCK_WEIGHTS_SHA256 == MOCK_WEIGHTS_SHA256.lower()
