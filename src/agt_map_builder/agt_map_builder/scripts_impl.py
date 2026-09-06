import argparse
from pathlib import Path
import yaml
from .cloud_loader import load_pcd
from .terrain_analysis import TerrainParameters, build_terrain_grid
from .map_exporter import export_map_package


def main() -> int:
    parser = argparse.ArgumentParser(description="Build a terrain-aware Nav2 map package from an ASCII PCD")
    parser.add_argument("--input", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--config", type=Path, default=None)
    args = parser.parse_args()
    config = yaml.safe_load(args.config.read_text(encoding="utf-8")) if args.config else {}
    config = config or {}
    params = TerrainParameters(**{k: v for k, v in config.items() if k in TerrainParameters.__dataclass_fields__})
    export_map_package(build_terrain_grid(load_pcd(args.input), params), args.output, str(args.input), params)
    print(f"Generated Nav2 map package: {args.output}")
    return 0
