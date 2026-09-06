import importlib.util
from pathlib import Path

import yaml


ROOT = Path(__file__).resolve().parents[2]
SCRIPT = ROOT / "src" / "agt_field_commissioning" / "scripts" / "edit_navigation_map.py"
SPEC = importlib.util.spec_from_file_location("edit_navigation_map", SCRIPT)
EDITOR = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(EDITOR)


def test_editor_resolves_relative_image_without_rewriting_yaml(tmp_path):
    image = tmp_path / "map.pgm"
    image.write_bytes(b"original-map-bytes")
    map_yaml = tmp_path / "map.yaml"
    document = {
        "image": "map.pgm",
        "resolution": 0.05,
        "origin": [-2.0, -3.0, 0.0],
        "negate": 0,
        "occupied_thresh": 0.65,
        "free_thresh": 0.196,
    }
    original_yaml = yaml.safe_dump(document, sort_keys=False)
    map_yaml.write_text(original_yaml, encoding="utf-8")

    resolved = EDITOR.resolve_map_image(map_yaml)

    assert resolved == image.resolve()
    assert map_yaml.read_text(encoding="utf-8") == original_yaml


def test_first_save_backup_is_idempotent(tmp_path):
    image = tmp_path / "map.pgm"
    image.write_bytes(b"v1")

    backup = EDITOR.ensure_backup(image)
    image.write_bytes(b"v2")
    backup_again = EDITOR.ensure_backup(image)

    assert backup == tmp_path / "map.original.pgm"
    assert backup_again == backup
    assert backup.read_bytes() == b"v1"


def test_editor_contract_keeps_controls_small_and_explicit():
    text = SCRIPT.read_text(encoding="utf-8")

    assert "LEFT: obstacle" in text
    assert "RIGHT: free" in text
    assert "S: save" in text
    assert "Q: quit" in text
    assert "cv2.line" in text
    assert "ensure_backup" in text
    assert "yaml_path.write_text" not in text
