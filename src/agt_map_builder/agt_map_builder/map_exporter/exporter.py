from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import numpy as np
import yaml
from .. import __version__
from ..terrain_analysis import TerrainGrid, TerrainParameters


def _write_pgm(path: Path, values: np.ndarray) -> None:
    path.write_bytes(f"P5\n{values.shape[1]} {values.shape[0]}\n255\n".encode() + values.astype(np.uint8).tobytes())


def export_map_package(grid: TerrainGrid, output: str | Path, source_pcd: str, parameters: TerrainParameters) -> Path:
    output = Path(output)
    output.mkdir(parents=True, exist_ok=True)
    # PGM row zero is the top of the image; map origin remains the lower-left corner.
    occupancy = np.flipud(grid.occupancy)
    image = np.full(occupancy.shape, 205, dtype=np.uint8)
    image[occupancy == 0] = 254
    image[occupancy == 100] = 0
    _write_pgm(output / "map.pgm", image)
    elevation = np.flipud(grid.height)
    known = np.isfinite(elevation)
    emin, emax = (float(np.nanmin(elevation)), float(np.nanmax(elevation))) if known.any() else (0.0, 1.0)
    encoded = np.full(elevation.shape, 205, dtype=np.uint8)
    if emax > emin:
        encoded[known] = np.clip((elevation[known] - emin) * 254 / (emax - emin), 0, 254)
    else:
        encoded[known] = 127
    _write_pgm(output / "elevation_map.pgm", encoded)
    trav = np.full(occupancy.shape, 205, dtype=np.uint8)
    slope = np.flipud(grid.slope_deg)
    trav[occupancy == 0] = np.clip(254 * (1 - slope[occupancy == 0] / max(parameters.unknown_slope_deg, 1e-9)), 0, 254)
    trav[occupancy == 100] = 0
    _write_pgm(output / "traversability_map.pgm", trav)
    map_yaml = {"image": "map.pgm", "resolution": grid.resolution, "origin": [grid.origin_xy[0], grid.origin_xy[1], 0.0], "negate": 0, "occupied_thresh": 0.65, "free_thresh": 0.196, "mode": "trinary"}
    (output / "map.yaml").write_text(yaml.safe_dump(map_yaml, sort_keys=False), encoding="utf-8")
    created = datetime.now(timezone.utc).isoformat()
    metadata = {"source_pcd": str(Path(source_pcd).resolve()), "resolution": grid.resolution, "frame_id": parameters.frame_id, "creation_time": created, "algorithm_version": __version__, "parameters": parameters.__dict__}
    (output / "metadata.yaml").write_text(yaml.safe_dump(metadata, sort_keys=False), encoding="utf-8")
    digest = hashlib.sha256((output / "map.pgm").read_bytes() + (output / "map.yaml").read_bytes()).hexdigest()
    manifest = {"map_id": output.name, "hash": {"sha256": digest}, "files": ["map.yaml", "map.pgm", "metadata.yaml", "elevation_map.pgm", "traversability_map.pgm"]}
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    return output
