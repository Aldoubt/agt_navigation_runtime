from pathlib import Path


ACTION = Path(__file__).resolve().parents[1] / "action" / "InspectImage.action"


def test_inspect_image_result_exposes_visual_evidence_payloads():
    source = ACTION.read_text(encoding="utf-8")
    parts = source.split("---")
    assert len(parts) == 3
    result = parts[1]

    assert "string weights_sha256" in result
    assert "sensor_msgs/Image overlay_image" in result
    assert "sensor_msgs/Image mask_image" in result


def test_inspect_image_keeps_existing_level1_result_fields():
    source = ACTION.read_text(encoding="utf-8")
    result = source.split("---")[1]

    for field in (
        "bool success",
        "uint16 error_code",
        "string model_id",
        "string model_version",
        "float64 inference_time_ms",
        "float64 primary_confidence",
        "string result_json",
        "string message",
    ):
        assert field in result
