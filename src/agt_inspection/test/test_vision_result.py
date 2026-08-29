import json

import pytest

from agt_inspection.vision_result import Level1VisionResultError, parse_level1_result


WEIGHTS = "sha256:" + "a" * 64
_BASE_INSTANCES = [
    {"local_instance_id": "I0001", "confidence": 0.91},
    {"local_instance_id": "I0002", "confidence": 0.87},
]


def _payload(
    *,
    raw_count=2,
    count_target="litchi_flower",
    model_id="flower-seg",
    model_version="1.2.3",
    weights_sha256=WEIGHTS,
):
    # The fixture must be able to construct malformed raw_count values so the
    # production parser, rather than Python list slicing, is what rejects them.
    if isinstance(raw_count, int) and not isinstance(raw_count, bool) and 0 <= raw_count <= len(_BASE_INSTANCES):
        instances = _BASE_INSTANCES[:raw_count]
    else:
        instances = list(_BASE_INSTANCES)

    return {
        "schema_version": 1,
        "count_target": count_target,
        "model": {
            "model_id": model_id,
            "model_version": model_version,
            "weights_sha256": weights_sha256,
        },
        "raw_count": raw_count,
        "instances": instances,
        "quality": {"valid": True, "reason": ""},
        "warnings": [],
    }


def _parse(payload):
    return parse_level1_result(
        json.dumps(payload),
        model_id="flower-seg",
        model_version="1.2.3",
        weights_sha256=WEIGHTS,
    )


def test_valid_level1_result_is_parsed_and_preserves_model_identity():
    result = _parse(_payload())

    assert result.count_target == "litchi_flower"
    assert result.raw_count == 2
    assert result.model_id == "flower-seg"
    assert result.model_version == "1.2.3"
    assert result.weights_sha256 == WEIGHTS
    assert len(result.instances) == 2
    assert result.quality == {"valid": True, "reason": ""}
    assert result.warnings == ()


def test_zero_count_is_a_valid_success_result_not_an_inference_failure():
    result = _parse(_payload(raw_count=0))

    assert result.raw_count == 0
    assert result.instances == ()
    assert result.quality["valid"] is True


@pytest.mark.parametrize(
    "text, message",
    [
        ("not-json", "valid JSON"),
        (json.dumps([]), "JSON object"),
        (json.dumps({"schema_version": 1}), "count_target"),
    ],
)
def test_malformed_level1_result_is_rejected(text, message):
    with pytest.raises(Level1VisionResultError, match=message):
        parse_level1_result(
            text,
            model_id="flower-seg",
            model_version="1.2.3",
            weights_sha256=WEIGHTS,
        )


@pytest.mark.parametrize("count_target", ["", None, False, 123])
def test_count_target_must_be_a_nonempty_string(count_target):
    with pytest.raises(Level1VisionResultError, match="count_target"):
        _parse(_payload(count_target=count_target))


def test_raw_count_and_instances_length_are_independent_contract_fields():
    payload = _payload(raw_count=2)
    payload["instances"] = payload["instances"][:1]

    result = _parse(payload)

    assert result.raw_count == 2
    assert len(result.instances) == 1


@pytest.mark.parametrize("raw_count", [-1, True, 1.5, "2"])
def test_raw_count_must_be_a_non_negative_integer(raw_count):
    with pytest.raises(Level1VisionResultError, match="raw_count"):
        _parse(_payload(raw_count=raw_count))


@pytest.mark.parametrize(
    "field, actual",
    [
        ("model_id", "other-model"),
        ("model_version", "9.9.9"),
        ("weights_sha256", "sha256:" + "b" * 64),
    ],
)
def test_json_model_identity_must_match_typed_action_result(field, actual):
    payload = _payload()
    payload["model"][field] = actual

    with pytest.raises(Level1VisionResultError, match=field):
        _parse(payload)


@pytest.mark.parametrize(
    "weights_sha256",
    [
        "",
        "abc",
        "sha256:1234",
        "sha256:" + "G" * 64,
        "SHA256:" + "a" * 64,
    ],
)
def test_typed_weights_sha256_must_be_canonical(weights_sha256):
    with pytest.raises(Level1VisionResultError, match="weights_sha256"):
        parse_level1_result(
            json.dumps(_payload(weights_sha256=weights_sha256)),
            model_id="flower-seg",
            model_version="1.2.3",
            weights_sha256=weights_sha256,
        )


def test_instances_quality_and_warnings_have_strict_container_types():
    bad_instances = _payload()
    bad_instances["instances"] = {}
    with pytest.raises(Level1VisionResultError, match="instances"):
        _parse(bad_instances)

    bad_quality = _payload()
    bad_quality["quality"] = []
    with pytest.raises(Level1VisionResultError, match="quality"):
        _parse(bad_quality)

    bad_warnings = _payload()
    bad_warnings["warnings"] = "blurred"
    with pytest.raises(Level1VisionResultError, match="warnings"):
        _parse(bad_warnings)


def test_schema_version_must_be_one():
    payload = _payload()
    payload["schema_version"] = 2

    with pytest.raises(Level1VisionResultError, match="schema_version"):
        _parse(payload)
