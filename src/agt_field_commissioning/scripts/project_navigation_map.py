#!/usr/bin/env python3

"""Project one finalized field-mapping run into an editable Nav2 map.

This is the canonical field CLI between FAST-LIVO2 PCD finalization and optional
manual map editing. It intentionally uses only the lightweight PCD grid backend;
RTAB-Map remains an opt-in archived experiment and is not reachable here.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path

from agt_field_commissioning.map_review import MapReviewDraft
from agt_field_commissioning.projection import LightweightPcdGridBackend, ProjectionRequest


def _parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Project a finalized FAST-LIVO2 PCD into a lightweight Nav2 map"
    )
    parser.add_argument("--runtime-dir", required=True)
    parser.add_argument("--site-id", required=True)
    parser.add_argument("--run-id", required=True)
    parser.add_argument("--resolution", type=float, default=0.05)
    parser.add_argument("--min-vertical-span", type=float, default=0.15)
    parser.add_argument("--chunk-points", type=int, default=500_000)
    parser.add_argument("--max-cells", type=int, default=20_000_000)
    return parser


def _safe_id(value: str, label: str) -> str:
    text = str(value).strip()
    if not text or any(char not in "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-" for char in text):
        raise ValueError(f"unsafe {label}: {value!r}")
    return text


def project_run(args: argparse.Namespace) -> dict[str, object]:
    runtime_dir = Path(args.runtime_dir).expanduser().resolve()
    site_id = _safe_id(args.site_id, "site_id")
    run_id = _safe_id(args.run_id, "run_id")
    run_root = runtime_dir / "commissioning" / site_id / run_id
    mapping_dir = run_root / "mapping"
    source_pcd = mapping_dir / "localization_map.pcd"
    processing_record = mapping_dir / "localization_map.processing.yaml"

    if not source_pcd.is_file() or source_pcd.stat().st_size <= 0:
        raise RuntimeError(
            f"finalized localization_map.pcd is missing or empty: {source_pcd}"
        )
    if not processing_record.is_file() or processing_record.stat().st_size <= 0:
        raise RuntimeError(
            "localization_map.processing.yaml is required; run finalize_mapping_run.py first"
        )

    projection_dir = run_root / "projection"
    backend = LightweightPcdGridBackend(
        min_vertical_span_m=float(args.min_vertical_span),
        chunk_points=int(args.chunk_points),
        max_cells=int(args.max_cells),
    )
    result = backend.project(
        ProjectionRequest(
            source_pcd=source_pcd,
            output_dir=projection_dir,
            resolution_m=float(args.resolution),
        )
    )

    review = MapReviewDraft.create(
        result.pgm,
        result.yaml,
        run_root / "map_review",
    ).materialize()

    return {
        "status": "MAP_READY",
        "backend": result.backend,
        "site_id": site_id,
        "run_id": run_id,
        "source_pcd": str(source_pcd),
        "processing_record": str(processing_record),
        "projection_pgm": str(result.pgm),
        "projection_yaml": str(result.yaml),
        "projection_record": str(result.record),
        "review_pgm": str(review.pgm),
        "review_yaml": str(review.yaml),
        "edit_log": str(review.edit_log),
    }


def main(argv=None) -> int:
    args = _parser().parse_args(argv)
    output = project_run(args)
    print(json.dumps(output, ensure_ascii=False, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
