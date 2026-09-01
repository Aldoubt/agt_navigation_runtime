from __future__ import annotations

import json
from pathlib import Path
from typing import Any


class InspectionStorage:
    """Small, backend-neutral evidence writer for image plus robot state."""

    def __init__(self, root: str | Path):
        self.root = Path(root).expanduser()

    def write_capture(self, capture_dir: str | Path, image: bytes, suffix: str, robot_state: dict[str, Any]):
        directory = Path(capture_dir)
        directory.mkdir(parents=True, exist_ok=True)
        image_path = directory / ("image" + (suffix if str(suffix).startswith(".") else "." + str(suffix)))
        image_path.write_bytes(bytes(image))
        (directory / "robot_state.json").write_text(json.dumps(robot_state, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        return image_path
