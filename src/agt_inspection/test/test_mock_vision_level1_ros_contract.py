from pathlib import Path


PACKAGE = Path(__file__).resolve().parents[1]


def _compact(text: str) -> str:
    return "".join(text.split())


def test_mock_vision_server_emits_canonical_level1_visual_action_result():
    server = (PACKAGE / "scripts" / "mock_vision_server.py").read_text(encoding="utf-8")
    compact = _compact(server)

    assert "agt_inspection.mock_visual" in server
    for symbol in (
        "MOCK_MODEL_ID",
        "MOCK_MODEL_VERSION",
        "MOCK_WEIGHTS_SHA256",
        "build_mock_level1_payload",
    ):
        assert symbol in server

    assert "result.model_id=MOCK_MODEL_ID" in compact
    assert "result.model_version=MOCK_MODEL_VERSION" in compact
    assert "result.weights_sha256=MOCK_WEIGHTS_SHA256" in compact
    assert "payload=build_mock_level1_payload()" in compact
    assert "result.result_json=json.dumps(payload" in compact

    assert "result.overlay_image=" in compact
    assert "result.mask_image=" in compact
    assert 'encoding="mono8"' in compact
    assert "goal_handle.request.image" in compact


def test_mock_vision_server_no_longer_builds_ad_hoc_legacy_result_json():
    server = (PACKAGE / "scripts" / "mock_vision_server.py").read_text(encoding="utf-8")

    assert '"class": "test_target"' not in server
    assert '"overlay_uri"' not in server
    assert '"mask_uri"' not in server
