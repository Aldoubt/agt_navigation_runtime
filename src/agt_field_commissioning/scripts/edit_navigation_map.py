#!/usr/bin/env python3

"""Tiny bitmap editor for a generated Nav2 occupancy map.

Controls:
  LEFT: obstacle (draw black)
  RIGHT: free (erase to white)
  S: save
  Q: quit
  + / -: increase / decrease brush width

The tool intentionally edits only the bitmap referenced by map.yaml. It never
rewrites resolution, origin, thresholds, or any other YAML metadata.
"""

from __future__ import annotations

import argparse
from pathlib import Path
import shutil

import yaml


def resolve_map_image(yaml_path: Path | str) -> Path:
    yaml_path = Path(yaml_path).expanduser().resolve()
    document = yaml.safe_load(yaml_path.read_text(encoding="utf-8")) or {}
    image_value = str(document.get("image", "")).strip()
    if not image_value:
        raise ValueError(f"map YAML has no image entry: {yaml_path}")
    image_path = Path(image_value).expanduser()
    if not image_path.is_absolute():
        image_path = yaml_path.parent / image_path
    image_path = image_path.resolve()
    if not image_path.is_file():
        raise FileNotFoundError(f"navigation map image does not exist: {image_path}")
    if image_path.suffix.lower() not in (".pgm", ".png"):
        raise ValueError("navigation map editor supports only .pgm and .png images")
    return image_path


def ensure_backup(image_path: Path | str) -> Path:
    image_path = Path(image_path).expanduser().resolve()
    backup = image_path.with_name(f"{image_path.stem}.original{image_path.suffix}")
    if not backup.exists():
        shutil.copy2(image_path, backup)
    return backup


def _save_bitmap(image_path: Path, image, cv2) -> None:
    ensure_backup(image_path)
    temporary = image_path.with_name(
        f".{image_path.stem}.editing{image_path.suffix}"
    )
    if not cv2.imwrite(str(temporary), image):
        raise RuntimeError(f"failed to write edited map image: {temporary}")
    try:
        temporary.chmod(image_path.stat().st_mode)
    except OSError:
        pass
    temporary.replace(image_path)


def run_editor(yaml_path: Path | str, *, brush_width: int = 7) -> Path:
    # OpenCV is deliberately imported only for interactive execution so map
    # metadata/backup contract tests do not require a display or cv2 import.
    import cv2

    image_path = resolve_map_image(yaml_path)
    image = cv2.imread(str(image_path), cv2.IMREAD_GRAYSCALE)
    if image is None:
        raise RuntimeError(f"OpenCV cannot read navigation map image: {image_path}")

    state = {
        "drawing": False,
        "last": None,
        "value": 0,
        "brush": max(1, int(brush_width)),
        "dirty": False,
    }

    def draw_segment(x: int, y: int) -> None:
        current = (int(x), int(y))
        previous = state["last"] or current
        cv2.line(
            image,
            previous,
            current,
            int(state["value"]),
            thickness=int(state["brush"]),
            lineType=cv2.LINE_8,
        )
        state["last"] = current
        state["dirty"] = True

    def mouse(event, x, y, _flags, _param):
        if event == cv2.EVENT_LBUTTONDOWN:
            state["drawing"] = True
            state["value"] = 0
            state["last"] = (x, y)
            draw_segment(x, y)
        elif event == cv2.EVENT_RBUTTONDOWN:
            state["drawing"] = True
            state["value"] = 254
            state["last"] = (x, y)
            draw_segment(x, y)
        elif event == cv2.EVENT_MOUSEMOVE and state["drawing"]:
            draw_segment(x, y)
        elif event in (cv2.EVENT_LBUTTONUP, cv2.EVENT_RBUTTONUP):
            if state["drawing"]:
                draw_segment(x, y)
            state["drawing"] = False
            state["last"] = None

    window = "AGT Navigation Map Editor"
    cv2.namedWindow(window, cv2.WINDOW_NORMAL)
    cv2.setMouseCallback(window, mouse)

    print(f"Map image: {image_path}")
    print("LEFT: obstacle | RIGHT: free | S: save | Q: quit | +/-: brush")
    while True:
        preview = cv2.cvtColor(image, cv2.COLOR_GRAY2BGR)
        status = (
            f"brush={state['brush']}  "
            f"{'UNSAVED' if state['dirty'] else 'saved'}  "
            "L=obstacle R=free S=save Q=quit"
        )
        cv2.putText(
            preview,
            status,
            (12, 28),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.65,
            (0, 0, 255) if state["dirty"] else (0, 180, 0),
            2,
            cv2.LINE_AA,
        )
        cv2.imshow(window, preview)
        key = cv2.waitKey(20) & 0xFF
        if key in (ord("s"), ord("S")):
            _save_bitmap(image_path, image, cv2)
            state["dirty"] = False
            print(f"Saved: {image_path}")
            print(f"Backup: {ensure_backup(image_path)}")
        elif key in (ord("q"), ord("Q"), 27):
            break
        elif key in (ord("+"), ord("=")):
            state["brush"] = min(101, int(state["brush"]) + 2)
        elif key in (ord("-"), ord("_")):
            state["brush"] = max(1, int(state["brush"]) - 2)

    cv2.destroyWindow(window)
    if state["dirty"]:
        print("Exited with unsaved edits; original map file was not changed.")
    return image_path


def _parse_args():
    parser = argparse.ArgumentParser(
        description="Draw/erase directly on the bitmap referenced by a Nav2 map YAML"
    )
    parser.add_argument("map_yaml", type=Path, help="Nav2 map YAML to edit")
    parser.add_argument(
        "--brush-width",
        type=int,
        default=7,
        help="initial stroke width in pixels (default: 7)",
    )
    return parser.parse_args()


def main() -> int:
    args = _parse_args()
    run_editor(args.map_yaml, brush_width=args.brush_width)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
