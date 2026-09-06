#!/usr/bin/env python3
from __future__ import annotations

import argparse
from collections import deque
import json
from pathlib import Path
from typing import Any

from agt_field_commissioning.map_review import PgmMap


_FREE = 254
_OCCUPIED = 0


def _free_components(pgm: PgmMap) -> tuple[int, int]:
    width = pgm.width
    height = pgm.height
    pixels = pgm.pixels
    visited = bytearray(width * height)
    component_count = 0
    largest = 0

    for seed in range(width * height):
        if visited[seed] or pixels[seed] != _FREE:
            continue
        component_count += 1
        size = 0
        queue: deque[int] = deque([seed])
        visited[seed] = 1
        while queue:
            cell = queue.popleft()
            size += 1
            x = cell % width
            y = cell // width
            if x > 0:
                neighbor = cell - 1
                if not visited[neighbor] and pixels[neighbor] == _FREE:
                    visited[neighbor] = 1
                    queue.append(neighbor)
            if x + 1 < width:
                neighbor = cell + 1
                if not visited[neighbor] and pixels[neighbor] == _FREE:
                    visited[neighbor] = 1
                    queue.append(neighbor)
            if y > 0:
                neighbor = cell - width
                if not visited[neighbor] and pixels[neighbor] == _FREE:
                    visited[neighbor] = 1
                    queue.append(neighbor)
            if y + 1 < height:
                neighbor = cell + width
                if not visited[neighbor] and pixels[neighbor] == _FREE:
                    visited[neighbor] = 1
                    queue.append(neighbor)
        largest = max(largest, size)
    return component_count, largest


def compute_map_metrics(path: str | Path) -> dict[str, int | float | str]:
    source = Path(path).expanduser().resolve()
    pgm = PgmMap.load(source)
    occupied = sum(1 for value in pgm.pixels if value == _OCCUPIED)
    free = sum(1 for value in pgm.pixels if value == _FREE)
    unknown = len(pgm.pixels) - free - occupied
    components, largest = _free_components(pgm)
    total = len(pgm.pixels)
    return {
        "path": str(source),
        "width": pgm.width,
        "height": pgm.height,
        "cell_count": total,
        "free_cells": free,
        "occupied_cells": occupied,
        "unknown_cells": unknown,
        "free_ratio": free / total,
        "occupied_ratio": occupied / total,
        "unknown_ratio": unknown / total,
        "free_component_count": components,
        "largest_free_component": largest,
    }


def compare_maps(
    point_map: str | Path,
    fused_map: str | Path,
    reference_map: str | Path | None = None,
) -> dict[str, Any]:
    point = compute_map_metrics(point_map)
    fused = compute_map_metrics(fused_map)
    maps: dict[str, dict[str, int | float | str]] = {
        "point": point,
        "fused": fused,
    }
    if reference_map is not None:
        maps["reference"] = compute_map_metrics(reference_map)
    return {
        "schema_version": 1,
        "maps": maps,
        "delta": {
            "unknown_ratio_fused_minus_point": (
                float(fused["unknown_ratio"]) - float(point["unknown_ratio"])
            ),
            "free_ratio_fused_minus_point": (
                float(fused["free_ratio"]) - float(point["free_ratio"])
            ),
            "largest_free_component_fused_minus_point": (
                int(fused["largest_free_component"])
                - int(point["largest_free_component"])
            ),
            "free_component_count_fused_minus_point": (
                int(fused["free_component_count"])
                - int(point["free_component_count"])
            ),
        },
    }


def _parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Compare commissioning point-only, raycast-fused and optional reference PGM maps."
    )
    parser.add_argument("--point-map", required=True)
    parser.add_argument("--fused-map", required=True)
    parser.add_argument("--reference-map")
    parser.add_argument("--json-output")
    return parser


def main() -> int:
    args = _parser().parse_args()
    report = compare_maps(args.point_map, args.fused_map, args.reference_map)
    text = json.dumps(report, indent=2, sort_keys=True) + "\n"
    if args.json_output:
        destination = Path(args.json_output).expanduser().resolve()
        destination.parent.mkdir(parents=True, exist_ok=True)
        temporary = destination.with_name(destination.name + ".tmp")
        temporary.write_text(text, encoding="utf-8")
        temporary.replace(destination)
    print(text, end="")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
