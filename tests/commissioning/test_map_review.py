from pathlib import Path

import pytest

from agt_field_commissioning.map_review import MapEdit, MapReviewDraft, PgmMap


def _write_p2(path: Path) -> None:
    path.write_text(
        "P2\n# test map\n3 2\n255\n0 205 254\n254 205 0\n",
        encoding="ascii",
    )


def _write_yaml(path: Path, image: str) -> None:
    path.write_text(
        f"image: {image}\nresolution: 0.10\norigin: [1.0, 2.0, 0.0]\n"
        "negate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\nmode: trinary\n",
        encoding="utf-8",
    )


def test_pgm_load_supports_p2_and_p5(tmp_path: Path) -> None:
    p2 = tmp_path / "map_ascii.pgm"
    _write_p2(p2)
    ascii_map = PgmMap.load(p2)
    assert (ascii_map.width, ascii_map.height) == (3, 2)
    assert list(ascii_map.pixels) == [0, 205, 254, 254, 205, 0]

    p5 = tmp_path / "map_binary.pgm"
    p5.write_bytes(b"P5\n2 2\n255\n" + bytes([0, 254, 205, 0]))
    binary_map = PgmMap.load(p5)
    assert (binary_map.width, binary_map.height) == (2, 2)
    assert list(binary_map.pixels) == [0, 254, 205, 0]


def test_map_review_is_non_destructive_and_supports_undo_redo_reset(tmp_path: Path) -> None:
    raw_pgm = tmp_path / "raw_map.pgm"
    raw_yaml = tmp_path / "raw_map.yaml"
    _write_p2(raw_pgm)
    _write_yaml(raw_yaml, raw_pgm.name)
    raw_before = raw_pgm.read_bytes()

    draft = MapReviewDraft.create(raw_pgm, raw_yaml, tmp_path / "review")
    assert draft.revision == 0

    draft.apply(MapEdit(kind="erase_to_free", cells=(0, 1)))
    assert draft.revision == 1
    assert draft.map.pixels[0] == 254
    assert draft.map.pixels[1] == 254

    draft.apply(MapEdit(kind="paint_occupied", cells=(1,)))
    assert draft.map.pixels[1] == 0
    assert draft.revision == 2

    assert draft.undo() is True
    assert draft.map.pixels[1] == 254
    assert draft.redo() is True
    assert draft.map.pixels[1] == 0

    materialized = draft.materialize()
    assert materialized.pgm.name == "reviewed_map.pgm"
    assert materialized.yaml.name == "reviewed_map.yaml"
    assert PgmMap.load(materialized.pgm).pixels[1] == 0
    assert raw_pgm.read_bytes() == raw_before

    draft.reset()
    assert draft.revision == 0
    assert list(draft.map.pixels) == [0, 205, 254, 254, 205, 0]
    assert raw_pgm.read_bytes() == raw_before


def test_map_edit_rejects_unknown_kind_and_out_of_bounds_cell(tmp_path: Path) -> None:
    raw_pgm = tmp_path / "raw_map.pgm"
    raw_yaml = tmp_path / "raw_map.yaml"
    _write_p2(raw_pgm)
    _write_yaml(raw_yaml, raw_pgm.name)
    draft = MapReviewDraft.create(raw_pgm, raw_yaml, tmp_path / "review")

    with pytest.raises(ValueError, match="unsupported map edit"):
        draft.apply(MapEdit(kind="make_magic", cells=(0,)))

    with pytest.raises(ValueError, match="out of bounds"):
        draft.apply(MapEdit(kind="paint_occupied", cells=(999,)))
