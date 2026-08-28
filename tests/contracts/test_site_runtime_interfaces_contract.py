from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[2]


def test_validate_map_version_service_is_narrow_and_registered():
    service_path = REPO_ROOT / "src/agt_interfaces/srv/ValidateMapVersion.srv"
    assert service_path.is_file(), "ValidateMapVersion.srv must exist before Site Runtime is exposed"

    text = service_path.read_text(encoding="utf-8")
    expected_tokens = (
        "string map_id",
        "string map_version_id",
        "uint16 ERROR_NONE=0",
        "uint16 ERROR_INVALID_REQUEST=1",
        "uint16 ERROR_NOT_FOUND=2",
        "uint16 ERROR_VALIDATION_FAILED=3",
        "uint16 ERROR_INTERNAL=255",
        "bool success",
        "uint16 error_code",
        "agt_interfaces/MapVersionSummary version",
        "string[] blocker_codes",
        "string[] blocker_messages",
        "string message",
    )
    for token in expected_tokens:
        assert token in text

    forbidden_tokens = (
        "candidate_map_yaml",
        "localization_pcd",
        "processing_record",
        "OP_IMPORT_CANDIDATE",
        "OP_PURGE",
        "confirm_destructive",
    )
    for token in forbidden_tokens:
        assert token not in text

    cmake = (REPO_ROOT / "src/agt_interfaces/CMakeLists.txt").read_text(encoding="utf-8")
    assert '"srv/ValidateMapVersion.srv"' in cmake
