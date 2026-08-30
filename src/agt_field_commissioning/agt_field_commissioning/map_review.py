from __future__ import annotations

from dataclasses import dataclass
import json
from pathlib import Path
from typing import Iterable


_WHITESPACE = b" \t\r\n\v\f"
_EDIT_VALUES = {
    "erase_to_free": 254,
    "paint_occupied": 0,
}


def _next_token(data: bytes, offset: int) -> tuple[bytes, int]:
    size = len(data)
    while offset < size:
        value = data[offset]
        if value in _WHITESPACE:
            offset += 1
            continue
        if value == ord("#"):
            newline = data.find(b"\n", offset)
            if newline < 0:
                raise ValueError("unterminated PGM comment")
            offset = newline + 1
            continue
        break
    start = offset
    while offset < size and data[offset] not in _WHITESPACE and data[offset] != ord("#"):
        offset += 1
    if start == offset:
        raise ValueError("unexpected end of PGM header")
    return data[start:offset], offset


def _replace_yaml_image(raw_yaml: str, image_name: str) -> str:
    lines = raw_yaml.splitlines()
    replaced = False
    output: list[str] = []
    for line in lines:
        if line.lstrip().startswith("image:") and not replaced:
            prefix = line[: len(line) - len(line.lstrip())]
            output.append(f"{prefix}image: {image_name}")
            replaced = True
        else:
            output.append(line)
    if not replaced:
        output.insert(0, f"image: {image_name}")
    return "\n".join(output) + "\n"


def _atomic_write_bytes(path: Path, data: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_bytes(data)
    temporary.replace(path)


def _atomic_write_text(path: Path, text: str) -> None:
    _atomic_write_bytes(path, text.encode("utf-8"))


@dataclass(frozen=True)
class PgmMap:
    width: int
    height: int
    max_value: int
    pixels: bytes

    def __post_init__(self) -> None:
        if self.width <= 0 or self.height <= 0:
            raise ValueError("PGM dimensions must be positive")
        if self.max_value <= 0 or self.max_value > 255:
            raise ValueError("only 8-bit PGM maps are supported")
        if len(self.pixels) != self.width * self.height:
            raise ValueError("PGM pixel count does not match dimensions")

    @classmethod
    def load(cls, path: str | Path) -> "PgmMap":
        source = Path(path)
        data = source.read_bytes()
        magic, offset = _next_token(data, 0)
        width_token, offset = _next_token(data, offset)
        height_token, offset = _next_token(data, offset)
        max_token, offset = _next_token(data, offset)
        try:
            width = int(width_token)
            height = int(height_token)
            max_value = int(max_token)
        except ValueError as exc:
            raise ValueError("invalid numeric PGM header") from exc

        expected = width * height
        if magic == b"P2":
            values: list[int] = []
            while len(values) < expected:
                token, offset = _next_token(data, offset)
                try:
                    value = int(token)
                except ValueError as exc:
                    raise ValueError("invalid P2 pixel") from exc
                if value < 0 or value > max_value:
                    raise ValueError("P2 pixel outside declared range")
                values.append(round(value * 255 / max_value) if max_value != 255 else value)
            return cls(width=width, height=height, max_value=255, pixels=bytes(values))

        if magic != b"P5":
            raise ValueError(f"unsupported PGM magic: {magic.decode('ascii', errors='replace')}")
        if max_value > 255:
            raise ValueError("only 8-bit P5 maps are supported")
        if offset >= len(data) or data[offset] not in _WHITESPACE:
            raise ValueError("P5 header is missing raster delimiter")
        if data[offset : offset + 2] == b"\r\n":
            offset += 2
        else:
            offset += 1
        raster = data[offset : offset + expected]
        if len(raster) != expected:
            raise ValueError("P5 raster is truncated")
        if max_value != 255:
            raster = bytes(round(value * 255 / max_value) for value in raster)
        return cls(width=width, height=height, max_value=255, pixels=raster)

    def to_p5(self) -> bytes:
        header = f"P5\n{self.width} {self.height}\n255\n".encode("ascii")
        return header + self.pixels

    def write(self, path: str | Path) -> Path:
        destination = Path(path)
        _atomic_write_bytes(destination, self.to_p5())
        return destination


@dataclass(frozen=True)
class MapEdit:
    kind: str
    cells: tuple[int, ...]

    def __post_init__(self) -> None:
        object.__setattr__(self, "kind", str(self.kind))
        object.__setattr__(self, "cells", tuple(int(cell) for cell in self.cells))


@dataclass(frozen=True)
class MaterializedMapReview:
    pgm: Path
    yaml: Path
    edit_log: Path


@dataclass(frozen=True)
class _AppliedEdit:
    edit: MapEdit
    changes: tuple[tuple[int, int, int], ...]


class MapReviewDraft:
    def __init__(
        self,
        raw_pgm: Path,
        raw_yaml: Path,
        draft_dir: Path,
        raw_map: PgmMap,
    ) -> None:
        self.raw_pgm = raw_pgm
        self.raw_yaml = raw_yaml
        self.draft_dir = draft_dir
        self._raw_map = raw_map
        self._pixels = bytearray(raw_map.pixels)
        self._history: list[_AppliedEdit] = []
        self._redo: list[_AppliedEdit] = []

    @classmethod
    def create(
        cls,
        raw_pgm: str | Path,
        raw_yaml: str | Path,
        draft_dir: str | Path,
    ) -> "MapReviewDraft":
        pgm = Path(raw_pgm).resolve()
        yaml = Path(raw_yaml).resolve()
        if not pgm.is_file():
            raise RuntimeError(f"raw commissioning PGM is missing: {pgm}")
        if not yaml.is_file():
            raise RuntimeError(f"raw commissioning YAML is missing: {yaml}")
        target = Path(draft_dir).resolve()
        target.mkdir(parents=True, exist_ok=True)
        return cls(pgm, yaml, target, PgmMap.load(pgm))

    @property
    def revision(self) -> int:
        return len(self._history)

    @property
    def map(self) -> PgmMap:
        return PgmMap(
            width=self._raw_map.width,
            height=self._raw_map.height,
            max_value=255,
            pixels=bytes(self._pixels),
        )

    def _validate_cells(self, cells: Iterable[int]) -> tuple[int, ...]:
        normalized = tuple(dict.fromkeys(int(cell) for cell in cells))
        limit = self._raw_map.width * self._raw_map.height
        for cell in normalized:
            if cell < 0 or cell >= limit:
                raise ValueError(f"map edit cell out of bounds: {cell}")
        return normalized

    def apply(self, edit: MapEdit) -> None:
        if edit.kind not in _EDIT_VALUES:
            raise ValueError(f"unsupported map edit: {edit.kind}")
        cells = self._validate_cells(edit.cells)
        new_value = _EDIT_VALUES[edit.kind]
        changes: list[tuple[int, int, int]] = []
        for cell in cells:
            old_value = self._pixels[cell]
            if old_value == new_value:
                continue
            self._pixels[cell] = new_value
            changes.append((cell, old_value, new_value))
        self._history.append(
            _AppliedEdit(MapEdit(edit.kind, cells), tuple(changes))
        )
        self._redo.clear()

    def undo(self) -> bool:
        if not self._history:
            return False
        applied = self._history.pop()
        for cell, old_value, _new_value in applied.changes:
            self._pixels[cell] = old_value
        self._redo.append(applied)
        return True

    def redo(self) -> bool:
        if not self._redo:
            return False
        applied = self._redo.pop()
        for cell, _old_value, new_value in applied.changes:
            self._pixels[cell] = new_value
        self._history.append(applied)
        return True

    def reset(self) -> None:
        self._pixels = bytearray(self._raw_map.pixels)
        self._history.clear()
        self._redo.clear()

    def materialize(self) -> MaterializedMapReview:
        reviewed_pgm = self.draft_dir / "reviewed_map.pgm"
        reviewed_yaml = self.draft_dir / "reviewed_map.yaml"
        edit_log = self.draft_dir / "map_edits.json"

        self.map.write(reviewed_pgm)
        _atomic_write_text(
            reviewed_yaml,
            _replace_yaml_image(
                self.raw_yaml.read_text(encoding="utf-8"),
                reviewed_pgm.name,
            ),
        )
        payload = {
            "schema_version": 1,
            "raw_pgm": str(self.raw_pgm),
            "raw_yaml": str(self.raw_yaml),
            "revision": self.revision,
            "operations": [
                {"kind": applied.edit.kind, "cells": list(applied.edit.cells)}
                for applied in self._history
            ],
        }
        _atomic_write_text(
            edit_log,
            json.dumps(payload, indent=2, sort_keys=True) + "\n",
        )
        return MaterializedMapReview(reviewed_pgm, reviewed_yaml, edit_log)
